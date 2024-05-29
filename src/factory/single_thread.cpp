#ifndef __SQLC_SRC_FACTORY_SINGLE_THREAD_CPP__
#define __SQLC_SRC_FACTORY_SINGLE_THREAD_CPP__

#include <src/factory/single_thread.hpp>
#include <src/dl/loader.hpp>

#include <format>
#include <regex>
#pragma warning(disable : 4996)
#include <locale>
#include <codecvt>

namespace SQLCore {
    SingleThreadFactory::SingleThreadFactory() noexcept {
        _Logger = SQLCore::GetLogger();
        _IsPreloadPlugins = false;
    }
    SQLCore::SDK::IPlugin* SingleThreadFactory::GetPlugin(SQLCore::Types::String _dialect) noexcept {
        for (auto& plugin : _Plugins) {
            auto dialect = plugin->GetDialect();
            auto lower_dialect = plugin->GetDialect();
            std::transform(lower_dialect.begin(), lower_dialect.end(), lower_dialect.begin(), [](char _symbol) {
                return std::tolower(_symbol);
            });
            if (_dialect == dialect || _dialect == lower_dialect) {
                return plugin;
            }
        }

        return nullptr;
    }
    SQLCore::Types::Bool SingleThreadFactory::LoadPluginFromAbsolutePath(SQLCore::Types::Path _path) noexcept {
        SQLCore::DL::Handle plugin_file = SQLCore::DL::Load(_path.string().c_str());
        if (!plugin_file) {
            _Logger->Error(std::format("Failed load plugin from {}", _path.string()));
            return false;
        }

        SQLCore::SDK::InitPluginFunc init_func = reinterpret_cast<SQLCore::SDK::InitPluginFunc>(SQLCore::DL::GetFunc(plugin_file, "DL__InitPlugin"));
        if (!init_func) {
            _Logger->Error(std::format("Failed load init func from {}", _path.string()));
        }
        init_func(this);

        SQLCore::SDK::GetPluginFunc get_func = reinterpret_cast<SQLCore::SDK::GetPluginFunc>(SQLCore::DL::GetFunc(plugin_file, "DL__GetPlugin"));
        if (!get_func) {
            _Logger->Error(std::format("Failed load function from {}", _path.string()));
            return false;
        }

        SQLCore::SDK::IPlugin* plugin = get_func();
        if (!plugin) {
            _Logger->Error(std::format("Failed load plugin object from {}", _path.string()));
            return false;
        }
        _Plugins.push_back(plugin);
        return true;
    }
    SQLCore::Types::Bool SingleThreadFactory::LoadPluginFromRelativePath(SQLCore::Types::Path _path) noexcept {
        for (auto& directory : _PluginDirectories) {
            if (this->LoadPluginFromAbsolutePath(directory.append(_path.string()))) {
                return true;
            }
        }

        return false;
    }
    SQLCore::Types::Array<SQLCore::IPlugin*> SingleThreadFactory::GetPlugins() noexcept {
        SQLCore::Types::Array<SQLCore::IPlugin*> buffer;
        for (auto plugin : _Plugins) {
            buffer.push_back(reinterpret_cast<SQLCore::IPlugin*>(plugin));
        }
        return buffer;
    }
    SQLCore::Types::List<SQLCore::IDatabase*> SingleThreadFactory::GetConnections() noexcept {
        return _Connections;
    }

    SQLCore::Types::Void SingleThreadFactory::AddConnection(SQLCore::IDatabase* _database) noexcept {
        _Connections.push_back(_database);
    }
    SQLCore::Types::Void SingleThreadFactory::AddPluginsDirectory(SQLCore::Types::Path _directory) noexcept {
        if (_IsPreloadPlugins) {
            #if defined(SQLC_SDK_WINDOWS)
            std::regex pattern("^SQLCore\\.Plugins\\..*\\.dll$");
            #elif defined(SQLC_SDK_APPLE)
            std::regex pattern("^libsqlcore-plugins-.*\\.dylib$");
            #elif defined(SQLC_SDK_LINUX)
            std::regex pattern("^libsqlcore-plugins-.*\\.so$");
            #endif
            for (const auto& file : std::filesystem::directory_iterator(_directory)) {
                auto file_path = file.path();
                if (std::regex_match(file_path.filename().string(), pattern)) {
                    _Logger->Info(std::format("{} is a SQLCore plugin", file_path.string()));
                    this->LoadPlugin(file_path);
                } else {
                    _Logger->Warning(std::format("{} is not a SQLCore plugin", file_path.string()));
                }
            }
        }

        _PluginDirectories.push_back(_directory);
    }
    SQLCore::Types::Bool SingleThreadFactory::LoadPlugin(SQLCore::Types::Path _path) noexcept {
        if (_path.is_absolute()) {
            return this->LoadPluginFromAbsolutePath(_path);
        } else {
            return this->LoadPluginFromRelativePath(_path);
        }
    }
    SQLCore::Types::Void SingleThreadFactory::EnablePreloadPlugins() noexcept {
        _IsPreloadPlugins = true;
    }
    SQLCore::Types::Void SingleThreadFactory::DisablePreloadPlugins() noexcept {
        _IsPreloadPlugins = false;
    }
    SQLCore::IDatabase* SingleThreadFactory::Connect(SQLCore::Types::String _uri) noexcept {
        std::string driver = _uri.substr(0, _uri.find("://"));
        auto plugin = this->GetPlugin(driver);
        return plugin ? plugin->Connect(_uri) : nullptr;
    }
    SQLCore::Types::Void SingleThreadFactory::Release() noexcept {
        for (auto connection : _Connections) {
            connection->Release();
        }

        for (auto plugin : _Plugins) {
            plugin->Release();
        }

        delete this;
    }
}

#endif