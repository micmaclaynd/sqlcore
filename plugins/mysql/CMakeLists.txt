cmake_minimum_required(VERSION 3.8)

project(SQLCore.Plugins.MySQL VERSION 0.2.0)

set(SQLC_PLUGINS_MYSQL_SRC 
    database.cpp plugin.cpp query.cpp)

add_library(SQLCore.Plugins.MySQL 
    SHARED ${SQLC_PLUGINS_MYSQL_SRC})

target_include_directories(SQLCore.Plugins.MySQL 
    PUBLIC ${SQLC_INCLUDE_DIRS})

target_include_directories(SQLCore.Plugins.MySQL 
    PUBLIC ${SQLC_SRC_INCLUDE_DIR})

target_include_directories(SQLCore.Plugins.MySQL 
    PUBLIC ${SQLC_MYSQL_INCLUDE_DIR})

target_link_libraries(SQLCore.Plugins.MySQL 
    PUBLIC ${SQLC_MYSQL_LIBS} 
    PUBLIC SQLCore.Logger.Loader 
    PUBLIC SQLCore.DL)

if(WIN32)
    set_target_properties(SQLCore.Plugins.MySQL 
        PROPERTIES OUTPUT_NAME "SQLCore.Plugins.MySQL")
elseif(UNIX)
    set_target_properties(SQLCore.Plugins.MySQL 
        PROPERTIES OUTPUT_NAME "sqlcore-plugins-mysql")
endif()