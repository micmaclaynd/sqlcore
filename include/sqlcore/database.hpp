#pragma once

#ifndef __SQLC_DATABASE_HPP__
#define __SQLC_DATABASE_HPP__

#include <sqlcore/unknown.hpp>
#include <sqlcore/query.hpp>
#include <sqlcore/types.hpp>

#include <string>

namespace SQLCore {
    SQLC_API_INTERFACE(IDatabase, SQLCore::IUnknown) {
        SQLC_API_METHOD(SQLCore::Types::Bool, IsConnect());
        SQLC_API_METHOD(SQLCore::IQueryResult*, ExecuteQuery(SQLCore::Types::String _sqlQuery));
    };
}

#endif