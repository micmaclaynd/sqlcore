#pragma once

#ifndef __SQLC_CORE_LOGGER_HPP__
#define __SQLC_CORE_LOGGER_HPP__

#include <sqlcore/unknown.hpp>
#include <sqlcore/types.hpp>

#include <string>

namespace SQLCore {
	SQLC_API_INTERFACE(ILogger, SQLCore::IUnknown) {
        SQLC_API_METHOD(SQLCore::Types::Void, Info(SQLCore::Types::String _message));
        SQLC_API_METHOD(SQLCore::Types::Void, Warning(SQLCore::Types::String _message));
        SQLC_API_METHOD(SQLCore::Types::Void, Error(SQLCore::Types::String _message));
	};

	SQLCore::ILogger* GetLogger() noexcept;
}

#endif