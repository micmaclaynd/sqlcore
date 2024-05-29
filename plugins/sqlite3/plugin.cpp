#ifndef __SQLC_PLUGINS_SQLITE3_PLUGIN_CPP__
#define __SQLC_PLUGINS_SQLITE3_PLUGIN_CPP__

#include <plugins/sqlite3/plugin.hpp>
#include <plugins/sqlite3/database.hpp>

namespace SQLCore::SQLite3 {
    Plugin::Plugin(SQLCore::IFactory* _factory) noexcept {
        _Logger = SQLCore::GetLogger();
        _Factory = _factory;
    }

    SQLCore::IDatabase* Plugin::Connect(SQLCore::Types::String _uri) noexcept {
        SQLCore::Types::String driver, user, password, host, database;

        size_t start = 0, end = _uri.find("://");
        driver = _uri.substr(start, end - start);

        start = end + 3, end = _uri.size();
        database = _uri.substr(start, end - start);

        auto connection = new SQLCore::SQLite3::Database(database);
        _Factory->AddConnection(connection);
        return connection;
    }

    SQLCore::Types::String Plugin::GetDialect() noexcept {
        return "SQLite3";
    }
    SQLCore::Types::String Plugin::GetConnector() noexcept {
        return "SQLite3 C API";
    }
    SQLCore::Types::String Plugin::GetVersion() noexcept {
        return "0.0.3";
    }
    SQLCore::Types::Path Plugin::GetPath() noexcept {
        return std::filesystem::current_path();
    }
    SQLCore::Types::String Plugin::GetType() noexcept {
        return "File";
    }
    void Plugin::Release() noexcept {
        delete this;
    }

    SQLCore::SQLite3::Plugin* AppPlugin = nullptr;

    SQLC_SDK_PLUGIN_INIT_FUNC(SQLCore::IFactory* _factory) noexcept {
        SQLCore::SQLite3::AppPlugin = new SQLCore::SQLite3::Plugin(_factory);
    }

    SQLC_SDK_PLUGIN_GET_FUNC() noexcept {
        return reinterpret_cast<SQLCore::SDK::IPlugin*>(SQLCore::SQLite3::AppPlugin);
    }

    SQLC_SDK_PLUGIN_RELEASE_FUNC() noexcept {
        if (SQLCore::SQLite3::AppPlugin) {
            SQLCore::SQLite3::AppPlugin->Release();
        }
    }
}

#endif