#pragma once

#ifndef __SQLC_SRC_FACTORY_SINGLE_THREAD_HPP__
#define __SQLC_SRC_FACTORY_SINGLE_THREAD_HPP__

#include <sqlcore/factory.hpp>
#include <sqlcore/sdk/plugin.hpp>
#include <sqlcore/logger.hpp>
#include <sqlcore/database.hpp>

#include <filesystem>
#include <vector>
#include <list>

namespace SQLCore {
    class SingleThreadFactory : public SQLCore::IFactory {
    public:
        explicit SingleThreadFactory() noexcept;

        SQLCore::SDK::IPlugin* GetPlugin(SQLCore::Types::String _driver) noexcept;
        SQLCore::Types::Bool LoadPluginFromAbsolutePath(SQLCore::Types::Path _path) noexcept;
        SQLCore::Types::Bool LoadPluginFromRelativePath(SQLCore::Types::Path _path) noexcept;

        SQLCore::Types::Array<SQLCore::IPlugin*> GetPlugins() noexcept override final;
        SQLCore::Types::List<SQLCore::IDatabase*> GetConnections() noexcept override final;

        SQLCore::Types::Void AddConnection(SQLCore::IDatabase* _database) noexcept override final;
        SQLCore::Types::Void AddPluginsDirectory(SQLCore::Types::Path _directory) noexcept override final;
        SQLCore::Types::Bool LoadPlugin(SQLCore::Types::Path _path) noexcept override final;
        SQLCore::Types::Void EnablePreloadPlugins() noexcept override final;
        SQLCore::Types::Void DisablePreloadPlugins() noexcept override final;

        SQLCore::IDatabase* Connect(SQLCore::Types::String _uri) noexcept override final;

        SQLCore::Types::Void Release() noexcept override final;

    private:
        SQLCore::Types::Array<SQLCore::Types::Path> _PluginDirectories;
        SQLCore::Types::List<SQLCore::IDatabase*> _Connections;
        SQLCore::Types::List<SQLCore::SDK::IPlugin*> _Plugins;
        SQLCore::Types::Bool _IsPreloadPlugins;

        SQLCore::ILogger* _Logger;
    };
}

#endif