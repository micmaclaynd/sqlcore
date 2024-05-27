#pragma once

#ifndef __SQLC_CORE_QUERY_HPP__
#define __SQLC_CORE_QUERY_HPP__

#include <sqlcore/unknown.hpp>
#include <sqlcore/types.hpp>

namespace SQLCore {
    SQLC_API_INTERFACE(IQueryResult, SQLCore::IUnknown) {
        SQLC_API_METHOD(SQLCore::Types::UInt32, GetColumnCount());
        SQLC_API_METHOD(SQLCore::Types::UInt32, GetRowCount());

        SQLC_API_METHOD( SQLCore::Types::String, GetColumnLabel(SQLCore::Types::UInt32 _index));

        SQLC_API_METHOD(SQLCore::Types::String, GetValue(SQLCore::Types::UInt32 _row, SQLCore::Types::UInt32 _column));
    };
}

#endif