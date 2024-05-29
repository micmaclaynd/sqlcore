#ifndef __SQLC_PLUGINS_POSTGRESQL_PLUGIN_CPP__
#define __SQLC_PLUGINS_POSTGRESQL_PLUGIN_CPP__

#include <plugins/postgresql/plugin.hpp>
#include <plugins/postgresql/database.hpp>

namespace SQLCore::PostgreSQL {
    Plugin::Plugin(SQLCore::IFactory* _factory) noexcept {
        _Logger = SQLCore::GetLogger();
        _Factory = _factory;
    }

    SQLCore::IDatabase* Plugin::Connect(SQLCore::Types::String _uri) noexcept {
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

        auto connection = new SQLCore::PostgreSQL::Database(host, database, user, password);
        _Factory->AddConnection(connection);
        return connection;
    }

    SQLCore::Types::String Plugin::GetDialect() noexcept {
        return "PostgreSQL";
    }
    SQLCore::Types::String Plugin::GetConnector() noexcept {
        return "PostgreSQL C API";
    }
    SQLCore::Types::String Plugin::GetVersion() noexcept {
        return "0.0.3";
    }
    SQLCore::Types::Path Plugin::GetPath() noexcept {
        return std::filesystem::current_path();
    }
    SQLCore::Types::String Plugin::GetType() noexcept {
        return "Server";
    }
    SQLCore::Types::Void Plugin::Release() noexcept {
        delete this;
    }

    SQLCore::PostgreSQL::Plugin* AppPlugin = nullptr;

    SQLC_SDK_PLUGIN_INIT_FUNC(SQLCore::IFactory* _factory) noexcept {
        SQLCore::PostgreSQL::AppPlugin = new SQLCore::PostgreSQL::Plugin(_factory);
    }

    SQLC_SDK_PLUGIN_GET_FUNC() noexcept {
        return reinterpret_cast<SQLCore::SDK::IPlugin*>(SQLCore::PostgreSQL::AppPlugin);
    }

    SQLC_SDK_PLUGIN_RELEASE_FUNC() noexcept {
        if (SQLCore::PostgreSQL::AppPlugin) {
            SQLCore::PostgreSQL::AppPlugin->Release();
        }
    }
}

#endif