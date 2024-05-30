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

    SQLCore::Types::String Database::GetCollation() noexcept {
        auto query = this->ExecuteQuery("SELECT datcollate FROM pg_database WHERE datname = current_database()");
        auto collation = query->GetValue(0, 0);
        query->Release();
        return collation;
    }
    SQLCore::Types::String Database::GetEncoding() noexcept {
        auto query = this->ExecuteQuery("SELECT pg_encoding_to_char(encoding) FROM pg_database WHERE datname = current_database()");
        auto encoding = query->GetValue(0, 0);
        query->Release();
        return encoding;
    }

    SQLCore::Types::Array<SQLCore::Types::String> Database::GetSchemas() noexcept {
        SQLCore::Types::Array<SQLCore::Types::String> schemas;
        auto query = this->ExecuteQuery("SELECT datname FROM pg_database WHERE datistemplate = false");
        for (SQLCore::Types::UInt32 row = 0; row < query->GetRowCount(); row++) {
            schemas.push_back(query->GetValue(row, 0));
        }
        query->Release();
        return schemas;
    }
    SQLCore::Types::Array<SQLCore::Types::String> Database::GetTables(SQLCore::Types::String _scheme) noexcept {
        SQLCore::Types::Array<SQLCore::Types::String> tables;
        auto query = this->ExecuteQuery(std::format("SELECT table_name FROM information_schema.tables WHERE table_schema = '{}'", _scheme));
        for (SQLCore::Types::UInt32 row = 0; row < query->GetRowCount(); row++) {
            tables.push_back(query->GetValue(row, 0));
        }
        query->Release();
        return tables;
    }
    SQLCore::Types::Array<SQLCore::Types::String> Database::GetFields(SQLCore::Types::String _scheme, SQLCore::Types::String _table) noexcept {
        SQLCore::Types::Array<SQLCore::Types::String> fields;
        auto query = this->ExecuteQuery(std::format("SELECT column_name FROM information_schema.columns WHERE table_schema = '{}' AND table_name = '{}'", _scheme, _table));
        for (SQLCore::Types::UInt32 row = 0; row < query->GetRowCount(); row++) {
            fields.push_back(query->GetValue(row, 0));
        }
        query->Release();
        return fields;
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