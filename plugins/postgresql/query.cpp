#ifndef __SQLC_PLUGINS_POSTGRESQL_QUERY_CPP__
#define __SQLC_PLUGINS_POSTGRESQL_QUERY_CPP__

#include <plugins/postgresql/query.hpp>

namespace SQLCore::PostgreSQL {
    QueryResult::QueryResult(PGresult* _result) noexcept {
        _Result = _result;
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
    SQLCore::Types::Void QueryResult::Release() noexcept {
        if (_Result) {
            ::PQclear(_Result);
        }

        delete this;
    }
}

#endif