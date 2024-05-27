#pragma once

#ifndef __SQLC_PLUGINS_POSTGRESQL_PLUGIN_HPP__
#define __SQLC_PLUGINS_POSTGRESQL_PLUGIN_HPP__

#include <sqlcore/sdk/plugin.hpp>
#include <sqlcore/logger.hpp>
#include <sqlcore/factory.hpp>
#include <sqlcore/types.hpp>

namespace SQLCore::PostgreSQL {
    class Plugin : public SQLCore::SDK::IPlugin {
    public:
        explicit Plugin(SQLCore::IFactory* _factory) noexcept;

        SQLCore::IDatabase* Connect(SQLCore::Types::String _uri) noexcept override final;

        SQLCore::Types::String GetDialect() noexcept override final;
        SQLCore::Types::String GetConnector() noexcept override final;
        SQLCore::Types::String GetVersion() noexcept override final;
        SQLCore::Types::Path GetPath() noexcept override final;
        SQLCore::Types::String GetType() noexcept override final;

        SQLCore::Types::Void Release() noexcept override final;

    private:
        SQLCore::IFactory* _Factory;
        SQLCore::ILogger* _Logger;
    };

    extern SQLCore::PostgreSQL::Plugin* AppPlugin;
}

#endif