#pragma once

#ifndef __SQLC_PLUGINS_MYSQL_PLUGIN_HPP__
#define __SQLC_PLUGINS_MYSQL_PLUGIN_HPP__

#include <sqlcore/sdk/plugin.hpp>
#include <sqlcore/factory.hpp>
#include <sqlcore/logger.hpp>
#include <sqlcore/types.hpp>

namespace SQLCore::MySQL {
    class Plugin : public SQLCore::SDK::IPlugin {
    public:
        explicit Plugin(SQLCore::IFactory* _factory) noexcept;

        SQLCore::IDatabase* Connect(SQLCore::Types::Uri _uri) noexcept override final;

        SQLCore::Types::String GetDialect() noexcept override final;
        SQLCore::Types::String GetConnector() noexcept override final;
        SQLCore::Types::String GetVersion() noexcept override final;
        SQLCore::Types::Path GetPath() noexcept override final;

        SQLCore::Types::Void Release() noexcept override final;

    private:
        SQLCore::ILogger* _Logger;
        SQLCore::IFactory* _Factory;
    };

    extern SQLCore::MySQL::Plugin* AppPlugin;
}

#endif