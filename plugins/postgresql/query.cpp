#ifndef __SQLC_PLUGINS_POSTGRESQL_QUERY_CPP__
#define __SQLC_PLUGINS_POSTGRESQL_QUERY_CPP__

#include <plugins/postgresql/query.hpp>

namespace SQLCore::PostgreSQL {
    QueryResult::QueryResult(PGresult* _result) noexcept {
        _Result = _result;
        _IsSuccess = true;

        if (_Result) {
            _ColumnCount = ::PQnfields(_Result);
            _RowCount = ::PQntuples(_Result);
        } else {
            _ColumnCount = 0;
            _RowCount = 0;
        }
    }
    QueryResult::QueryResult(SQLCore::Types::String _error) noexcept {
        _Result = nullptr;
        _IsSuccess = false;
        _Error = _error;

        _ColumnCount = 0;
        _RowCount = 0;
    }
    SQLCore::Types::UInt32 QueryResult::GetColumnCount() noexcept {
        return ::PQnfields(_Result);
    }
    SQLCore::Types::UInt32 QueryResult::GetRowCount() noexcept {
        return ::PQntuples(_Result);
    }
    SQLCore::Types::String QueryResult::GetColumnLabel(SQLCore::Types::UInt32 _index) noexcept {
        return ::PQfname(_Result, _index);
    }
    SQLCore::Types::String QueryResult::GetValue(SQLCore::Types::UInt32 _row, SQLCore::Types::UInt32 _column) noexcept {
        return ::PQgetvalue(_Result, _row, _column);
    }
    SQLCore::Types::Bool QueryResult::IsSuccess() noexcept {
        return _IsSuccess;
    }
    SQLCore::Types::String QueryResult::GetError() noexcept {
        return _Error;
    }
    SQLCore::Types::Void QueryResult::Release() noexcept {
        if (_Result) {
            ::PQclear(_Result);
        }

        delete this;
    }
}

#endif