#pragma once

#ifndef __SQLC_SDK_PLUGIN_HPP__
#define __SQLC_SDK_PLUGIN_HPP__

#include <sqlcore/sdk/dl.hpp>
#include <sqlcore/database.hpp>
#include <sqlcore/factory.hpp>
#include <sqlcore/plugin.hpp>
#include <sqlcore/types.hpp>

namespace SQLCore::SDK {
    SQLC_API_INTERFACE(IPlugin, SQLCore::IPlugin) {
        SQLC_API_METHOD(SQLCore::IDatabase*, Connect(std::string _uri));
    };

    typedef SQLCore::Types::Void (SQLC_SDK_DL_CALL_TYPE* InitPluginFunc)(SQLCore::IFactory*);
    typedef SQLCore::SDK::IPlugin* (SQLC_SDK_DL_CALL_TYPE* GetPluginFunc)();
    typedef SQLCore::Types::Void (SQLC_SDK_DL_CALL_TYPE* ReleasePluginFunc)();
}

#define SQLC_SDK_PLUGIN_INIT_FUNC SQLC_SDK_DL_FUNC(SQLCore::Types::Void, DL__InitPlugin)
#define SQLC_SDK_PLUGIN_GET_FUNC SQLC_SDK_DL_FUNC(SQLCore::SDK::IPlugin*, DL__GetPlugin)
#define SQLC_SDK_PLUGIN_RELEASE_FUNC SQLC_SDK_DL_FUNC(SQLCore::Types::Void, DL__ReleasePlugin)

#endif