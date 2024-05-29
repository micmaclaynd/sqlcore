#ifndef __SQLC_PLUGINS_SQLITE3_QUERY_CPP__
#define __SQLC_PLUGINS_SQLITE3_QUERY_CPP__

#include <plugins/sqlite3/query.hpp>

namespace SQLCore::SQLite3 {
    QueryResult::QueryResult(sqlite3_stmt* _result) noexcept {
        _Result = _result;
        _IsSuccess = true;

        _RowCount = 0;
        _ColumnCount = sqlite3_column_count(_Result);
        while (::sqlite3_step(_Result) == SQLITE_ROW) {
            _RowCount++;
        }
    }
    QueryResult::QueryResult(SQLCore::Types::String _error) noexcept {
        _Result = nullptr;
        _IsSuccess = false;
        _Error = _error;

        _RowCount = 0;
        _ColumnCount = 0;
    }
    SQLCore::Types::UInt32 QueryResult::GetColumnCount() noexcept {
        return _ColumnCount;
    }
    SQLCore::Types::UInt32 QueryResult::GetRowCount() noexcept {
        return _RowCount;
    }
    SQLCore::Types::String QueryResult::GetColumnLabel(SQLCore::Types::UInt32 _index) noexcept {
        return ::sqlite3_column_name(_Result, _index);
    }
    SQLCore::Types::String QueryResult::GetValue(SQLCore::Types::UInt32 _row, SQLCore::Types::UInt32 _column) noexcept {
        SQLCore::Types::UInt32 row = 0;
        ::sqlite3_reset(_Result);
        while (row != _row + 1) {
            int status = ::sqlite3_step(_Result);
            if (status == SQLITE_ROW) row++;
        }
        auto value = reinterpret_cast<const char*>(::sqlite3_column_text(_Result, _column));
        return SQLCore::Types::String(value ? value : "NULL");
    }
    SQLCore::Types::Bool QueryResult::IsSuccess() noexcept {
        return _IsSuccess;
    }
    SQLCore::Types::String QueryResult::GetError() noexcept {
        return _Error;
    }
    SQLCore::Types::Void QueryResult::Release() noexcept {
        if (_Result) {
            ::sqlite3_finalize(_Result);
        }

        delete this;
    }
}

#endif