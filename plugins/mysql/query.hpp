#pragma once

#ifndef __SQLC_PLUGINS_MYSQL_QUERY_HPP__
#define __SQLC_PLUGINS_MYSQL_QUERY_HPP__

#include <sqlcore/query.hpp>
#include <sqlcore/logger.hpp>

#include <mysql.h>

namespace SQLCore::MySQL {
    class QueryResult : public SQLCore::IQueryResult {
    public:
        explicit QueryResult(MYSQL_RES* _result) noexcept;

        SQLCore::Types::UInt32 GetColumnCount() noexcept override final;
        SQLCore::Types::UInt32 GetRowCount() noexcept override final;

        SQLCore::Types::String GetColumnLabel(SQLCore::Types::UInt32 _index) noexcept override final;

        SQLCore::Types::String GetValue(SQLCore::Types::UInt32 _row, SQLCore::Types::UInt32 _column) noexcept override final;

        SQLCore::Types::Void Release() noexcept override final;

    private:
        SQLCore::ILogger* _Logger;

        MYSQL_RES* _Result;

        SQLCore::Types::UInt32 _ColumnCount;
        SQLCore::Types::UInt32 _RowCount;
    };
}

#endif