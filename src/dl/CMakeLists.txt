cmake_minimum_required(VERSION 3.8)

project(SQLCore.DL)

set(SQLC_DL_SRC loader.cpp)

add_library(SQLCore.DL 
    STATIC ${SQLC_DL_SRC})

target_include_directories(SQLCore.DL 
    PUBLIC ${SQLC_INCLUDE_DIR} 
    PUBLIC ${SQLC_SRC_INCLUDE_DIR})

if(WIN32)
    set_target_properties(SQLCore.DL 
        PROPERTIES OUTPUT_NAME "SQLCore.DL")

    set(SQLC_DL_LIBS "SQLCore.Dl")
elseif(UNIX)
    set_target_properties(SQLCore.DL 
        PROPERTIES OUTPUT_NAME "sqlcore-dl")

    set(SQLC_DL_LIBS "sqlcore-dl")
endif()