#ifndef __SQLC_PLUGINS_MYSQL_PLUGIN_CPP__
#define __SQLC_PLUGINS_MYSQL_PLUGIN_CPP__

#include <plugins/mysql/plugin.hpp>
#include <plugins/mysql/database.hpp>

namespace SQLCore::MySQL {
    Plugin::Plugin(SQLCore::IFactory* _factory) noexcept {
        _Logger = SQLCore::GetLogger();
        _Factory = _factory;
    }
    SQLCore::IDatabase* Plugin::Connect(SQLCore::Types::Uri _uri) noexcept {
        SQLCore::Types::String driver, user, password, host, database;

        size_t start = 0, end = _uri.find("://");
        driver = _uri.substr(start, end - start);

        start = end + 3, end = _uri.find(":", start);
        user = _uri.substr(start, end - start);

        start = end + 1, end = _uri.find("@", start);
        password = _uri.substr(start, end - start);

        start = end + 1, end = _uri.find("/", start);
        host = _uri.substr(start, end - start);

        start = end + 1, end = _uri.size();
        database = _uri.substr(start, end - start);

        return new SQLCore::MySQL::Database(host, database, user, password);
    }
    SQLCore::Types::String Plugin::GetDialect() noexcept {
        return "MySQL";
    }
    SQLCore::Types::String Plugin::GetConnector() noexcept {
        return "MySQL С API";
    }
    SQLCore::Types::String Plugin::GetVersion() noexcept {
        return "0.0.1";
    }
    SQLCore::Types::Path Plugin::GetPath() noexcept {
        return std::filesystem::current_path();
    }
    SQLCore::Types::Void Plugin::Release() noexcept {
        delete this;
    }

    SQLCore::MySQL::Plugin* AppPlugin = nullptr;

    SQLC_SDK_PLUGIN_INIT_FUNC(SQLCore::IFactory* _factory) noexcept {
        SQLCore::MySQL::AppPlugin = new SQLCore::MySQL::Plugin(_factory);
    }

    SQLC_SDK_PLUGIN_GET_FUNC() noexcept {
        return reinterpret_cast<SQLCore::SDK::IPlugin*>(SQLCore::MySQL::AppPlugin);
    }

    SQLC_SDK_PLUGIN_RELEASE_FUNC() noexcept {
        if (SQLCore::MySQL::AppPlugin) {
            SQLCore::MySQL::AppPlugin->Release();
        }
    }
}

#endif