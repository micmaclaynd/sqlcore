cmake_minimum_required(VERSION 3.8)

project(SQLCore.Plugins.SQLite3 VERSION 0.2.0)

set(SQLC_PLUGINS_SQLITE3_SRC 
    database.cpp plugin.cpp query.cpp ${SQLC_SQLITE3_SRC})

add_library(SQLCore.Plugins.SQLite3 
    SHARED ${SQLC_PLUGINS_SQLITE3_SRC})

target_include_directories(SQLCore.Plugins.SQLite3 
    PUBLIC ${SQLC_INCLUDE_DIR}
    PUBLIC ${SQLC_SRC_INCLUDE_DIR}
    PUBLIC ${SQLC_SQLITE3_INCLUDE_DIR})

target_link_libraries(SQLCore.Plugins.SQLite3 
    PUBLIC ${SQLC_SQLITE3_LIBS} 
    PUBLIC SQLCore.Logger.Loader 
    PUBLIC SQLCore.DL)

if(WIN32)
    set_target_properties(SQLCore.Plugins.SQLite3 
        PROPERTIES OUTPUT_NAME "SQLCore.Plugins.SQLite3")
elseif(UNIX)
    set_target_properties(SQLCore.Plugins.SQLite3 
        PROPERTIES OUTPUT_NAME "sqlcore-plugins-sqlite3")
endif()