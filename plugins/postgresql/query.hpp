#pragma once

#ifndef __SQLC_PLUGINS_POSTGRESQL_QUERY_HPP__
#define __SQLC_PLUGINS_POSTGRESQL_QUERY_HPP__

#include <sqlcore/query.hpp>

#include <libpq-fe.h>

namespace SQLCore::PostgreSQL {
    class QueryResult : public SQLCore::IQueryResult {
    public:
        explicit QueryResult(PGresult* _result) noexcept;
        explicit QueryResult(SQLCore::Types::String _error) noexcept;

        SQLCore::Types::UInt32 GetColumnCount() noexcept override final;
        SQLCore::Types::UInt32 GetRowCount() noexcept override final;

        SQLCore::Types::String GetColumnLabel(SQLCore::Types::UInt32 _index) noexcept override final;

        SQLCore::Types::String GetValue(SQLCore::Types::UInt32 _row, SQLCore::Types::UInt32 _column) noexcept override final;

        SQLCore::Types::Bool IsSuccess() noexcept override final;
        SQLCore::Types::String GetError() noexcept override final;

        SQLCore::Types::Void Release() noexcept override final;

    private:
        PGresult* _Result;

        SQLCore::Types::UInt32 _ColumnCount;
        SQLCore::Types::UInt32 _RowCount;

        SQLCore::Types::Bool _IsSuccess;
        SQLCore::Types::String _Error;
    };
}

#endif