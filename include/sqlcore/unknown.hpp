#pragma once

#ifndef __SQLC_UNKNOWN_HPP__
#define __SQLC_UNKNOWN_HPP__

#include <sqlcore/types.hpp>
#include <sqlcore/api.hpp>

namespace SQLCore {
	SQLC_API_BASE_INTERFACE(IUnknown) {
		SQLC_API_METHOD(SQLCore::Types::Void, Release());
	};
}

#endif