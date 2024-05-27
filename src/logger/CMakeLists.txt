cmake_minimum_required(VERSION 3.8)

project(SQLCore.Logger)

set(SQLC_LOGGER_SRC 
    logger.cpp)

set(SQLC_LOGGER_LOADER_SRC 
    dl_loader.cpp)

add_library(SQLCore.Logger 
    SHARED ${SQLC_LOGGER_SRC})

target_include_directories(SQLCore.Logger 
    PUBLIC ${SQLC_INCLUDE_DIR} 
    PUBLIC ${SQLC_SRC_INCLUDE_DIR})

add_library(SQLCore.Logger.Loader 
    STATIC ${SQLC_LOGGER_LOADER_SRC})

target_include_directories(SQLCore.Logger.Loader 
    PUBLIC ${SQLC_INCLUDE_DIR} 
    PUBLIC ${SQLC_SRC_INCLUDE_DIR})

target_link_libraries(SQLCore.Logger.Loader 
    PUBLIC SQLCore.DL)

if(WIN32)
    set_target_properties(SQLCore.Logger 
        PROPERTIES OUTPUT_NAME "SQLCore.Logger")

    set_target_properties(SQLCore.Logger.Loader 
        PROPERTIES OUTPUT_NAME "SQLCore.Logger.Loader")

    set(SQLC_LOGGER_LIBS "SQLCore.Logger.Loader")
elseif(UNIX)
    set_target_properties(SQLCore.Logger 
        PROPERTIES OUTPUT_NAME "sqlcore-logger")

    set_target_properties(SQLCore.Logger.Loader 
        PROPERTIES OUTPUT_NAME "sqlcore-logger-loader")

    set(SQLC_LOGGER_LIBS "sqlcore-logger-loader")
endif()