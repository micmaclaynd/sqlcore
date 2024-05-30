#pragma once

#ifndef __SQLC_PLUGINS_MYSQL_DATABASE_HPP__
#define __SQLC_PLUGINS_MYSQL_DATABASE_HPP__

#include <sqlcore/database.hpp>
#include <sqlcore/logger.hpp>
#include <sqlcore/types.hpp>
#include <sqlcore/query.hpp>

#include <string>

#include <mysql.h>

namespace SQLCore::MySQL {
    class Database : public SQLCore::IDatabase {
    public:
        explicit Database(SQLCore::Types::String _host, SQLCore::Types::String _dbName, SQLCore::Types::String _user, SQLCore::Types::String _password) noexcept;

        SQLCore::Types::Bool IsConnect() noexcept override final;

        SQLCore::Types::String GetCollation() noexcept override final;
        SQLCore::Types::String GetEncoding() noexcept override final;

        SQLCore::Types::Array<SQLCore::Types::String> GetSchemas() noexcept override final;
        SQLCore::Types::Array<SQLCore::Types::String> GetTables(SQLCore::Types::String _scheme) noexcept override final;
        SQLCore::Types::Array<SQLCore::Types::String> GetFields(SQLCore::Types::String _scheme, SQLCore::Types::String _table) noexcept override final;

        SQLCore::IQueryResult* ExecuteQuery(SQLCore::Types::String _sqlQuery) noexcept override final;

        SQLCore::Types::Void Release() noexcept override final;

    private:
        SQLCore::ILogger* _Logger;

        MYSQL* _Connection;
        bool _IsConnect;

        SQLCore::Types::String _Host;
        SQLCore::Types::String _DbName;
        SQLCore::Types::String _User;
        SQLCore::Types::String _Password;
    };
}

#endif