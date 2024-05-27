cmake_minimum_required(VERSION 3.8)

project(SQLCore.Plugins)

set(SQLC_UNIX_LIB_PATHS 
    /usr/lib /usr/local/lib /lib /usr/share)

set(SQLC_UNIX_INCLUDE_PATHS 
    /usr/include /usr/local/include)

find_package(PkgConfig)

find_package(PostgreSQL)
if(NOT PostgreSQL_FOUND)
    pkg_check_modules(LIBPQ libpq)
endif()
if(PostgreSQL_FOUND)
    message(STATUS "PostgreSQL package found.")

    set(SQLC_POSTGRESQL_INCLUDE_DIR ${PostgreSQL_INCLUDE_DIRS})
    set(SQLC_POSTGRESQL_LIBS ${PostgreSQL_LIBRARIES})

    add_subdirectory(postgresql)
elseif(LIBPQ_FOUND)
    message(STATUS "PostgreSQL pkg package found.")

    set(SQLC_POSTGRESQL_INCLUDE_DIR ${LIBPQ_INCLUDE_DIRS})
    set(SQLC_POSTGRESQL_LIBS ${LIBPQ_LIBRARIES})

    add_subdirectory(postgresql)
else()
    if(UNIX)
        find_library(SQLC_POSTGRESQL_LIBS
            HINTS ${SQLC_UNIX_INCLUDE_PATHS}
            NAMES libpq.so)
    elseif(WIN32)
        find_library(SQLC_POSTGRESQL_LIBS
            HINTS ${SQLC_POSTGRESQL_DIR}/lib
            NAMES libpq.lib)
    endif()

    if(SQLC_POSTGRESQL_LIBS)
        message(STATUS "PostgreSQL libs found at ${SQLC_POSTGRESQL_LIBS}")
    else()
        message(STATUS "PostgreSQL libs not found.")
    endif()

    if(UNIX)
        find_path(SQLC_POSTGRESQL_INCLUDE_DIR
            HINTS ${SQLC_UNIX_INCLUDE_PATHS}
            NAMES postgresql)

        set(SQLC_POSTGRESQL_INCLUDE_DIR ${SQLC_POSTGRESQL_INCLUDE_DIR}/postgresql)
    elseif(WIN32)
        find_path(SQLC_POSTGRESQL_INCLUDE_DIR
            HINTS ${SQLC_POSTGRESQL_DIR}
            NAMES include)

        set(SQLC_POSTGRESQL_INCLUDE_DIR ${SQLC_POSTGRESQL_INCLUDE_DIR}/include)
    endif()

    if(SQLC_POSTGRESQL_INCLUDE_DIR)
        message(STATUS "PostgreSQL include path found at ${SQLC_POSTGRESQL_INCLUDE_DIR}")
    else()
        message(STATUS "PostgreSQL include path not found.")
    endif()

    if(SQLC_POSTGRESQL_LIBS AND SQLC_POSTGRESQL_INCLUDE_DIR)
        add_subdirectory(postgresql)
    endif()
endif()

find_package(MySQL)
if (NOT MySQL_FOUND)
    pkg_check_modules(MYSQLCLIENT mysqlclient)
endif()
if(MySQL_FOUND)
    message(STATUS "MySQL package found")

    set(SQLC_MYSQL_INCLUDE_DIR ${MySQL_INCLUDE_DIRS})
    set(SQLC_MYSQL_LIBS ${MySQL_LIBRARIES})

    add_subdirectory(mysql)
elseif(MYSQLCLIENT_FOUND)
    message(STATUS "MySQL pkg package found.")

    set(SQLC_MYSQL_INCLUDE_DIR ${MYSQLCLIENT_INCLUDE_DIRS})
    set(SQLC_MYSQL_LIBS ${MYSQLCLIENT_LIBRARIES})

    add_subdirectory(mysql)
else()
    if(UNIX)
        find_library(SQLC_MYSQL_LIBS
            HINTS ${SQLC_UNIX_LIB_PATHS}
            NAMES libmysqlclient.so)
    elseif(WIN32)
        find_library(SQLC_MYSQL_LIBS
            HINTS ${SQLC_MYSQL_DIR}/lib
            NAMES libmysql.lib)
    endif()

    if(SQLC_MYSQL_LIBS)
        message(STATUS "MySQL libs found at ${SQLC_MYSQL_LIBS}")
    else()
        message(STATUS "MySQL libs not found.")
    endif()

    if(UNIX)
        find_path(SQLC_MYSQL_INCLUDE_DIR
            HINTS ${SQLC_UNIX_INCLUDE_PATHS}
            NAMES mysql)

        set(SQLC_MYSQL_INCLUDE_DIR ${SQLC_MYSQL_INCLUDE_DIR}/mysql)
    elseif(WIN32)
        find_path(SQLC_MYSQL_INCLUDE_DIR
            HINTS ${SQLC_MYSQL_DIR}
            NAMES include)

        set(SQLC_MYSQL_INCLUDE_DIR ${SQLC_MYSQL_INCLUDE_DIR}/include)
    endif()

    if(SQLC_MYSQL_INCLUDE_DIR)
        message(STATUS "MySQL include path found at ${SQLC_MYSQL_INCLUDE_DIR}")
    else()
        message(STATUS "MySQL include path not found.")
    endif()

    if(SQLC_MYSQL_LIBS AND SQLC_MYSQL_INCLUDE_DIR)
        add_subdirectory(mysql)
    endif()
endif()

find_package(SQLite3)
if (NOT SQLite3_FOUND)
    pkg_check_modules(SQLITE3 sqlite3)
endif()
if(SQLite3_FOUND)
    message(STATUS "SQLite3 package found")

    set(SQLC_SQLITE3_INCLUDE_DIR ${SQLite3_INCLUDE_DIRS})
    set(SQLC_SQLITE3_LIBS ${SQLite3_LIBRARIES})

    add_subdirectory(sqlite3)
elseif(SQLITE3_FOUND)
    message(STATUS "SQLite3 pkg package found.")

    set(SQLC_SQLITE3_INCLUDE_DIR ${SQLITE3_INCLUDE_DIRS})
    set(SQLC_SQLITE3_LIBS ${SQLITE3_LIBRARIES})

    add_subdirectory(sqlite3)
else()
    if(UNIX)
        find_library(SQLC_SQLITE3_LIBS
            HINTS ${SQLC_UNIX_LIB_PATHS}
            NAMES libsqlite3.so)
    elseif(WIN32)
        find_path(SQLC_SQLITE3_SRC
            HINTS ${SQLC_SQLITE3_DIR}
            NAMES sqlite3.c)

        set(SQLC_SQLITE3_SRC ${SQLC_SQLITE3_SRC}/sqlite3.c)
    endif()

    if(SQLC_SQLITE3_LIBS)
        message(STATUS "SQLite3 libs found at ${SQLC_SQLITE3_LIBS}")
    else()
        message(STATUS "SQLite3 libs not found.")
    endif()

    if(SQLC_SQLITE3_SRC)
        message(STATUS "SQLite3 sources found at ${SQLC_SQLITE3_SRC}")
    else()
        message(STATUS "SQLite3 sources not found.")
    endif()

    if(UNIX)
        find_path(SQLC_SQLITE3_INCLUDE_DIR
            HINTS ${SQLC_UNIX_INCLUDE_PATHS}
            NAMES sqlite3.h)
    elseif(WIN32)
        find_path(SQLC_SQLITE3_INCLUDE_DIR
            HINTS ${SQLC_SQLITE3_DIR}
            NAMES sqlite3.h)
    endif()

    if(SQLC_SQLITE3_INCLUDE_DIR)
        message(STATUS "SQLite3 include path found at ${SQLC_SQLITE3_INCLUDE_DIR}")
    else()
        message(STATUS "SQLite3 include path not found.")
    endif()

    if((SQLC_SQLITE3_LIBS OR SQLC_SQLITE3_SRC) AND SQLC_SQLITE3_INCLUDE_DIR)
        add_subdirectory(sqlite3)
    endif()
endif()