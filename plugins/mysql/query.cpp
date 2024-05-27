#ifndef __SQLC_PLUGINS_MYSQL_QUERY_CPP__
#define __SQLC_PLUGINS_MYSQL_QUERY_CPP__

#include <plugins/mysql/query.hpp>

#include <format>

namespace SQLCore::MySQL {
    QueryResult::QueryResult(MYSQL_RES* _result) noexcept {
        _Logger = SQLCore::GetLogger();
        _Result = _result;

        _RowCount = static_cast<SQLCore::Types::UInt32>(::mysql_num_rows(_Result));
        _ColumnCount = static_cast<SQLCore::Types::UInt32>(::mysql_num_fields(_Result));
    }
    SQLCore::Types::UInt32 QueryResult::GetColumnCount() noexcept {
        return _ColumnCount;
    }
    SQLCore::Types::UInt32 QueryResult::GetRowCount() noexcept {
        return _RowCount;
    }
    SQLCore::Types::String QueryResult::GetColumnLabel(SQLCore::Types::UInt32 _index) noexcept {
        return SQLCore::Types::String(::mysql_fetch_field_direct(_Result, _index)->name);
    }
    SQLCore::Types::String QueryResult::GetValue(SQLCore::Types::UInt32 _row, SQLCore::Types::UInt32 _column) noexcept {
        ::mysql_data_seek(_Result, _row);
        auto field = ::mysql_fetch_row(_Result)[_column];
        return SQLCore::Types::String(field ? field : "NULL");
    }
    SQLCore::Types::Void QueryResult::Release() noexcept {
        if (_Result) {
            ::mysql_free_result(_Result);
        }

        delete this;
    }
}

#endif