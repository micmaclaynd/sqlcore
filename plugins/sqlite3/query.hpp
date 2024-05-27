#pragma once

#ifndef __SQLC_PLUGINS_SQLITE3_QUERY_HPP__
#define __SQLC_PLUGINS_SQLITE3_QUERY_HPP__

#include <sqlcore/query.hpp>

#include <sqlite3.h>

namespace SQLCore::SQLite3 {
    class QueryResult : public SQLCore::IQueryResult {
    public:
        explicit QueryResult(sqlite3_stmt* _result) noexcept;

        SQLCore::Types::UInt32 GetColumnCount() noexcept override final;
        SQLCore::Types::UInt32 GetRowCount() noexcept override final;

        SQLCore::Types::String GetColumnLabel(SQLCore::Types::UInt32 _index) noexcept override final;

        SQLCore::Types::String GetValue(SQLCore::Types::UInt32 _row, SQLCore::Types::UInt32 _column) noexcept override final;

        SQLCore::Types::Void Release() noexcept override final;

    private:
        sqlite3_stmt* _Result;

        SQLCore::Types::UInt32 _ColumnCount;
        SQLCore::Types::UInt32 _RowCount;
    };
}

#endif