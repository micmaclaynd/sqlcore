#pragma once

#ifndef __SQLC_SRC_FACTORY_MULTI_THREAD_HPP__
#define __SQLC_SRC_FACTORY_MULTI_THREAD_HPP__

#include <sqlcore/factory.hpp>
#include <sqlcore/sdk/plugin.hpp>
#include <sqlcore/logger.hpp>
#include <sqlcore/database.hpp>
#include <sqlcore/types.hpp>

#include <filesystem>
#include <vector>
#include <atomic>
#include <mutex>
#include <list>

namespace SQLCore {
    class MultiThreadFactory : public SQLCore::IFactory {
    public:
        explicit MultiThreadFactory() noexcept;

        SQLCore::SDK::IPlugin* GetPlugin(SQLCore::Types::String _driver) noexcept;
        SQLCore::Types::Bool LoadPluginFromAbsolutePath(SQLCore::Types::Path _path) noexcept;
        SQLCore::Types::Bool LoadPluginFromRelativePath(SQLCore::Types::Path _path) noexcept;

        SQLCore::Types::Array<SQLCore::IPlugin*> GetPlugins() noexcept override final;

        SQLCore::Types::Void AddPluginsDirectory(SQLCore::Types::Path _directory) noexcept override final;
        SQLCore::Types::Bool LoadPlugin(SQLCore::Types::Path _path) noexcept override final;
        SQLCore::Types::Void EnablePreloadPlugins() noexcept override final;
        SQLCore::Types::Void DisablePreloadPlugins() noexcept override final;

        SQLCore::IDatabase* Connect(SQLCore::Types::String _uri) noexcept override final;

        SQLCore::Types::Void Release() noexcept override final;

    private:
        SQLCore::Types::Array<SQLCore::Types::Path> _PluginDirectories;
        std::mutex _PluginDirectoriesMutex;

        SQLCore::Types::List<SQLCore::SDK::IPlugin*> _Plugins;
        std::mutex _PluginsMutex;

        std::atomic<SQLCore::Types::Bool> _IsPreloadPlugins;

        SQLCore::ILogger* _Logger;
    };
}

#endif