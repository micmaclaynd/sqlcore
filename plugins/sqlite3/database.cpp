#ifndef __SQLC_PLUGINS_SQLITE3_DATABASE_CPP__
#define __SQLC_PLUGINS_SQLITE3_DATABASE_CPP__

#include <plugins/sqlite3/database.hpp>
#include <plugins/sqlite3/query.hpp>

#include <iostream>
#include <format>

namespace SQLCore::SQLite3 {
    Database::Database(std::string _dbName) noexcept {
        _Logger = SQLCore::GetLogger();

        _IsConnect = true;

        _DbName = _dbName;

        int status = ::sqlite3_open(_DbName.c_str(), &_DbFile);

        if (status) {
            _Logger->Error(std::format("Failed open {} error {}", _DbName, ::sqlite3_errmsg(_DbFile)));
            _IsConnect = false;
        }
    }

    bool Database::IsConnect() noexcept {
        return _IsConnect;
    }

    SQLCore::Types::String Database::GetCollation() noexcept {
        auto query = this->ExecuteQuery("PRAGMA encoding");
        auto collation = query->GetValue(0, 0);
        query->Release();
        return collation;
    }
    SQLCore::Types::String Database::GetEncoding() noexcept {
        auto query = this->ExecuteQuery("PRAGMA encoding");
        auto encoding = query->GetValue(0, 0);
        query->Release();
        return encoding;
    }

    SQLCore::Types::Array<SQLCore::Types::String> Database::GetSchemas() noexcept {
        SQLCore::Types::Array<SQLCore::Types::String> schemas = { "scheme" };
        return schemas;
    }
    SQLCore::Types::Array<SQLCore::Types::String> Database::GetTables(SQLCore::Types::String _scheme) noexcept {
        SQLCore::Types::Array<SQLCore::Types::String> tables;
        auto query = this->ExecuteQuery("SELECT name FROM sqlite_master WHERE type='table'");
        for (SQLCore::Types::UInt32 row = 0; row < query->GetRowCount(); row++) {
            tables.push_back(query->GetValue(row, 0));
        }
        query->Release();
        return tables;
    }
    SQLCore::Types::Array<SQLCore::Types::String> Database::GetFields(SQLCore::Types::String _scheme, SQLCore::Types::String _table) noexcept {
        SQLCore::Types::Array<SQLCore::Types::String> fields;
        auto query = this->ExecuteQuery(std::format("PRAGMA table_info('{}')", _table));
        for (SQLCore::Types::UInt32 row = 0; row < query->GetRowCount(); row++) {
            fields.push_back(query->GetValue(row, 1));
        }
        query->Release();
        return fields;
    }

    SQLCore::IQueryResult* Database::ExecuteQuery(std::string _sqlQuery) noexcept {
        if (!_IsConnect) {
            _Logger->Error(std::format("Not opened {}", _DbName));
            return nullptr;
        }

        sqlite3_stmt* statement = nullptr;
        int status = ::sqlite3_prepare_v3(_DbFile, _sqlQuery.c_str(), static_cast<int>(_sqlQuery.size()), SQLITE_PREPARE_PERSISTENT, &statement, nullptr);

        if (status != SQLITE_OK) {
            _Logger->Error(::sqlite3_errmsg(_DbFile));
            return reinterpret_cast<SQLCore::IQueryResult*>(new SQLCore::SQLite3::QueryResult(::sqlite3_errmsg(_DbFile)));
        }

        return reinterpret_cast<SQLCore::IQueryResult*>(new SQLCore::SQLite3::QueryResult(statement));
    }

    void Database::Release() noexcept {
        if (_IsConnect) {
            ::sqlite3_close(_DbFile);
        }

        delete this;
    }
}

#endif