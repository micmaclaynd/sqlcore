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
            _Logger->Error(std::format("Failed open {} error {}", _DbName, sqlite3_errmsg(_DbFile)));
            _IsConnect = false;
        }
    }

    bool Database::IsConnect() noexcept {
        return _IsConnect;
    }
    SQLCore::IQueryResult* Database::ExecuteQuery(std::string _sqlQuery) noexcept {
        if (!_IsConnect) {
            _Logger->Error(std::format("Not opened {}", _DbName));
            return nullptr;
        }

        sqlite3_stmt* statement = nullptr;
        int status = ::sqlite3_prepare_v3(_DbFile, _sqlQuery.c_str(), static_cast<int>(_sqlQuery.size()), SQLITE_PREPARE_PERSISTENT, &statement, nullptr);

        if (status != SQLITE_OK) {
            _Logger->Error(sqlite3_errmsg(_DbFile));
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