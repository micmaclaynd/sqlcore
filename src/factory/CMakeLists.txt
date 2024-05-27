cmake_minimum_required(VERSION 3.8)

project(SQLCore.Factory)

set(SQLC_FACTORY_SRC 
    dl_main.cpp multi_thread.cpp single_thread.cpp)

set(SQLC_FACTORY_LOADER_SRC 
    dl_loader.cpp)

add_library(SQLCore.Factory 
    SHARED ${SQLC_FACTORY_SRC})

target_include_directories(SQLCore.Factory 
    PUBLIC ${SQLC_INCLUDE_DIR} 
    PUBLIC ${SQLC_SRC_INCLUDE_DIR})

target_link_libraries(SQLCore.Factory 
    PUBLIC SQLCore.Logger.Loader 
    PUBLIC SQLCore.DL)

add_library(SQLCore.Factory.Loader 
    STATIC ${SQLC_FACTORY_LOADER_SRC})

target_include_directories(SQLCore.Factory.Loader 
    PUBLIC ${SQLC_INCLUDE_DIR} 
    PUBLIC ${SQLC_SRC_INCLUDE_DIR})

target_link_libraries(SQLCore.Factory.Loader 
    PUBLIC SQLCore.Logger.Loader 
    PUBLIC SQLCore.DL)

if(WIN32)
    set_target_properties(SQLCore.Factory 
        PROPERTIES OUTPUT_NAME "SQLCore.Factory")

    set_target_properties(SQLCore.Factory.Loader 
        PROPERTIES OUTPUT_NAME "SQLCore.Factory.Loader")

    set(SQLC_FACTORY_LIBS "SQLCore.Factory.Loader")
elseif(UNIX)
    set_target_properties(SQLCore.Factory 
        PROPERTIES OUTPUT_NAME "sqlcore-factory")

    set_target_properties(SQLCore.Factory.Loader 
        PROPERTIES OUTPUT_NAME "sqlcore-factory-loader")

    set(SQLC_FACTORY_LIBS "sqlcore-factory-loader")
endif()