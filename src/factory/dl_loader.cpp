#ifndef __SQLC_SRC_FACTORY_DL_LOADER_CPP__
#define __SQLC_SRC_FACTORY_DL_LOADER_CPP__

#include <sqlcore/sdk/dl.hpp>
#include <sqlcore/factory.hpp>
#include <sqlcore/logger.hpp>

#include <src/dl/loader.hpp>
#include <format>

namespace SQLCore {
    typedef SQLCore::IFactory* (SQLC_SDK_DL_CALL_TYPE* CreateFactoryFunc)(SQLCore::FactoryType);

    SQLCore::IFactory* CreateFactory(SQLCore::FactoryType _factoryType) noexcept {
        static SQLCore::DL::Handle library = nullptr;
        static SQLCore::CreateFactoryFunc func = nullptr;
        static SQLCore::ILogger* logger = SQLCore::GetLogger();

        if (!library) {
            #if defined(SQLC_SDK_WINDOWS)
            library = SQLCore::DL::Load("SQLCore.Factory.dll");
            #elif defined(SQLC_SDK_LINUX)
            library = SQLCore::DL::Load("libsqlcore-factory.so");
            #elif defined(SQLC_SDK_APPLE)
            library = SQLCore::DL::Load("libsqlcore-factory.dylib");
            #endif
            if (!library) {
                logger->Error("Failed load SQLCore.Factory");
                return nullptr;
            }
        }

        if (!func) {
            func = reinterpret_cast<SQLCore::CreateFactoryFunc>(SQLCore::DL::GetFunc(library, "DL__CreateFactory"));
            if (!func) {
                logger->Error("Failed get DL__CreateFactory from SQLCore.Factory");
                return nullptr;
            }
        }

        return func(_factoryType);
    }
}

#endif