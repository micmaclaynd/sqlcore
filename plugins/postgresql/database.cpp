#ifndef __SQLC_PLUGINS_POSTGRESQL_DATABASE_CPP__
#define __SQLC_PLUGINS_POSTGRESQL_DATABASE_CPP__

#include <plugins/postgresql/database.hpp>
#include <plugins/postgresql/query.hpp>

#include <iostream>
#include <format>

namespace SQLCore::PostgreSQL {
    Database::Database(SQLCore::Types::String _host, SQLCore::Types::String _dbName, SQLCore::Types::String _user, SQLCore::Types::String _password) noexcept {
        _Logger = SQLCore::GetLogger();

        _IsConnect = true;

        _Host = _host;
        _DbName = _dbName;
        _User = _user;
        _Password = _password;

        _Connection = ::PQconnectdb(std::format("host={} dbname={} user={} password={}", _Host, _DbName, _User, _Password).c_str());

        if (::PQstatus(_Connection) != CONNECTION_OK) {
            _Logger->Error(std::format("Failed connect to {}", _Host));
            _IsConnect = false;
            ::PQfinish(_Connection);
        }
    }

    SQLCore::Types::Bool Database::IsConnect() noexcept {
        return _IsConnect;
    }
    SQLCore::IQueryResult* Database::ExecuteQuery(SQLCore::Types::String _sqlQuery) noexcept {
        if (!_IsConnect) {
            _Logger->Error(std::format("Not connected to {}", _Host));
            return nullptr;
        }

        PGresult* result = ::PQexec(_Connection, _sqlQuery.c_str());

        if (::PQresultStatus(result) != PGRES_TUPLES_OK) {
            _Logger->Error(std::format("Failed execute query: {}, reason: {}", _sqlQuery, ::PQresultErrorMessage(result)));
            ::PQclear(result);
            return reinterpret_cast<SQLCore::IQueryResult*>(new SQLCore::PostgreSQL::QueryResult(::PQresultErrorMessage(result)));
        }

        return reinterpret_cast<SQLCore::IQueryResult*>(new SQLCore::PostgreSQL::QueryResult(result));
    }

    SQLCore::Types::Void Database::Release() noexcept {
        if (_IsConnect) {
            ::PQfinish(_Connection);
        }

        delete this;
    }
}

#endif