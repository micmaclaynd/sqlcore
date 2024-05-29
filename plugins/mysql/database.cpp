#ifndef __SQLC_PLUGINS_MYSQL_DATABASE_CPP__
#define __SQLC_PLUGINS_MYSQL_DATABASE_CPP__

#include <plugins/mysql/database.hpp>
#include <plugins/mysql/query.hpp>

#include <format>

namespace SQLCore::MySQL {
    Database::Database(SQLCore::Types::String _host, SQLCore::Types::String _dbName, SQLCore::Types::String _user, SQLCore::Types::String _password) noexcept {
        _Logger = SQLCore::GetLogger();

        _IsConnect = false;

        _Host = _host;
        _DbName = _dbName;
        _User = _user;
        _Password = _password;

        _Connection = ::mysql_init(nullptr);

        if (!_Connection) {
            _Logger->Error("Failed init mysql");
            return;
        }

        if (::mysql_real_connect(_Connection, _Host.c_str(), _User.c_str(), _Password.c_str(), _DbName.c_str(), 0, nullptr, 0) == nullptr) {
            _Logger->Error(::mysql_error(_Connection));
            return;
        }

        _IsConnect = true;
    }

    SQLCore::Types::Bool Database::IsConnect() noexcept {
        return _IsConnect;
    }

    // SQLCore::Types::String Database::GetCollation() noexcept {
    //     auto query = this->ExecuteQuery("SHOW VARIABLES LIKE 'collation_database'");
    //     auto collation = query->GetValue(0, 1);
    //     query->Release();
    //     return collation;
    // }

    // SQLCore::Types::String Database::GetEncoding() noexcept {
    //     auto query = this->ExecuteQuery("SHOW VARIABLES LIKE 'character_set_database'");
    //     auto encoding = query->GetValue(0, 1);
    //     query->Release();
    //     return encoding;
    // }

    SQLCore::IQueryResult* Database::ExecuteQuery(SQLCore::Types::String _sqlQuery) noexcept {
        if (!_IsConnect) {
            _Logger->Error(std::format("Not connected to {}", _Host));
            return nullptr;
        }

        if (::mysql_query(_Connection, _sqlQuery.c_str())) {
            _Logger->Error(::mysql_error(_Connection));
            return reinterpret_cast<SQLCore::IQueryResult*>(new SQLCore::MySQL::QueryResult(::mysql_error(_Connection)));
        }

        MYSQL_RES* result = ::mysql_store_result(_Connection);

        if (!result && ::mysql_errno(_Connection)) {
            _Logger->Error(::mysql_error(_Connection));
            return reinterpret_cast<SQLCore::IQueryResult*>(new SQLCore::MySQL::QueryResult(::mysql_error(_Connection)));
        }

        return reinterpret_cast<SQLCore::IQueryResult*>(new SQLCore::MySQL::QueryResult(result));
    }

    SQLCore::Types::Void Database::Release() noexcept {
        if (_IsConnect) {
            ::mysql_close(_Connection);
        }

        delete this;
    }
}

#endif