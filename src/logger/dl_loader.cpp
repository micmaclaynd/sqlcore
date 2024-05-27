#ifndef __SQLC_SRC_LOGGER_DL_LOADER_CPP__
#define __SQLC_SRC_LOGGER_DL_LOADER_CPP__

#include <sqlcore/logger.hpp>
#include <sqlcore/sdk/dl.hpp>

#include <src/dl/loader.hpp>

#include <iostream>

namespace SQLCore {
    typedef SQLCore::ILogger* (SQLC_SDK_DL_CALL_TYPE* GetLoggerFunc)();

    SQLCore::ILogger* GetLogger() noexcept {
        static SQLCore::DL::Handle library = nullptr;
        static SQLCore::GetLoggerFunc func = nullptr;
        static SQLCore::ILogger* logger = nullptr;

        if (!library) {
            #if defined(SQLC_SDK_WINDOWS)
            library = SQLCore::DL::Load("SQLCore.Logger.dll");
            #elif defined(SQLC_SDK_LINUX)
            library = SQLCore::DL::Load("libsqlcore-logger.so");
            #elif defined(SQLC_SDK_APPLE)
            library = SQLCore::DL::Load("libsqlcore-logger.dylib");
            #endif
            if (!library) {
                std::cout << "Failed load SQLCore.Logger" << std::endl;
                return nullptr;
            }
        }

        if (!func) {
            func = reinterpret_cast<SQLCore::GetLoggerFunc>(SQLCore::DL::GetFunc(library, "DL__GetLogger"));
            if (!func) {
                std::cout << "Failed load DL_GetLogger from SQLCore.Logger" << std::endl;
                return nullptr;
            }
        }

        if (!logger) {
            logger = func();
            if (!logger) {
                std::cout << "Failed get SQLCore::ILogger*" << std::endl;
                return nullptr;
            }
        }

        return logger;
    }
}

#endif