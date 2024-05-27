#pragma once

#ifndef __SQLC_PLUGINS_POSTGRESQL_DATABASE_HPP__
#define __SQLC_PLUGINS_POSTGRESQL_DATABASE_HPP__

#include <sqlcore/database.hpp>
#include <sqlcore/logger.hpp>
#include <sqlcore/query.hpp>

#include <string>

#include <libpq-fe.h>

namespace SQLCore::PostgreSQL {
    class Database : public SQLCore::IDatabase {
    public:
        explicit Database(SQLCore::Types::String _host, SQLCore::Types::String _dbName, SQLCore::Types::String _user, SQLCore::Types::String _password) noexcept;

        SQLCore::Types::Bool IsConnect() noexcept override final;
        SQLCore::IQueryResult* ExecuteQuery(SQLCore::Types::String _sqlQuery) noexcept override final;

        SQLCore::Types::Void Release() noexcept override final;

    private:
        SQLCore::ILogger* _Logger;

        PGconn* _Connection;
        SQLCore::Types::Bool _IsConnect;

        SQLCore::Types::String _Host;
        SQLCore::Types::String _DbName;
        SQLCore::Types::String _User;
        SQLCore::Types::String _Password;
    };
}

#endif