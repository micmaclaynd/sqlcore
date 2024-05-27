cmake_minimum_required(VERSION 3.8)

project(SQLCore.Plugins.PostgreSQL VERSION 0.2.0)

set(SQLC_PLUGINS_POSTGRESQL_SRC 
    database.cpp plugin.cpp query.cpp)

add_library(SQLCore.Plugins.PostgreSQL 
    SHARED ${SQLC_PLUGINS_POSTGRESQL_SRC})

target_include_directories(SQLCore.Plugins.PostgreSQL 
    PUBLIC ${SQLC_INCLUDE_DIR})

target_include_directories(SQLCore.Plugins.PostgreSQL 
    PUBLIC ${SQLC_SRC_INCLUDE_DIR})

target_include_directories(SQLCore.Plugins.PostgreSQL 
    PUBLIC ${SQLC_POSTGRESQL_INCLUDE_DIR})

target_link_libraries(SQLCore.Plugins.PostgreSQL 
    PUBLIC ${SQLC_POSTGRESQL_LIBS} 
    PUBLIC SQLCore.Logger.Loader 
    PUBLIC SQLCore.DL)

if(WIN32)
    set_target_properties(SQLCore.Plugins.PostgreSQL 
        PROPERTIES OUTPUT_NAME "SQLCore.Plugins.PostgreSQL")
elseif(UNIX)
    set_target_properties(SQLCore.Plugins.PostgreSQL 
        PROPERTIES OUTPUT_NAME "sqlcore-plugins-postgresql")
endif()