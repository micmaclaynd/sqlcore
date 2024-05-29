#pragma once

#ifndef __SQLC_FACTORY_HPP__
#define __SQLC_FACTORY_HPP__

#include <sqlcore/unknown.hpp>
#include <sqlcore/database.hpp>
#include <sqlcore/types.hpp>
#include <sqlcore/plugin.hpp>

#include <filesystem>

namespace SQLCore {
    enum class FactoryType : uint8_t {
        SingleThreaded, MultiThreaded
    };

    SQLC_API_INTERFACE(IFactory, SQLCore::IUnknown) {
        SQLC_API_METHOD(SQLCore::Types::Array<SQLCore::IPlugin*>, GetPlugins());
        SQLC_API_METHOD(SQLCore::Types::List<SQLCore::IDatabase*>, GetConnections());
        SQLC_API_METHOD(SQLCore::Types::Void, AddConnection(SQLCore::IDatabase* _database));
        SQLC_API_METHOD(SQLCore::Types::Void, AddPluginsDirectory(SQLCore::Types::Path _directory));
        SQLC_API_METHOD(SQLCore::Types::Bool, LoadPlugin(SQLCore::Types::Path _path));
        SQLC_API_METHOD(SQLCore::Types::Void, EnablePreloadPlugins());
        SQLC_API_METHOD(SQLCore::Types::Void, DisablePreloadPlugins());
        SQLC_API_METHOD(SQLCore::IDatabase*, Connect(SQLCore::Types::Uri _uri));
    };

    SQLCore::IFactory* CreateFactory(SQLCore::FactoryType _factoryType = SQLCore::FactoryType::SingleThreaded) noexcept;
}

#endif