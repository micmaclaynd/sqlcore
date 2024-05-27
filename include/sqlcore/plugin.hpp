#pragma once

#ifndef __SQLC_PLUGIN_HPP__
#define __SQLC_PLUGIN_HPP__

#include <sqlcore/unknown.hpp>
#include <sqlcore/types.hpp>

namespace SQLCore {
	SQLC_API_INTERFACE(IPlugin, SQLCore::IUnknown) {
        SQLC_API_METHOD(SQLCore::Types::String, GetDialect());
        SQLC_API_METHOD(SQLCore::Types::String, GetConnector());
        SQLC_API_METHOD(SQLCore::Types::String, GetVersion());
        SQLC_API_METHOD(SQLCore::Types::Path, GetPath());
	};
}

#endif