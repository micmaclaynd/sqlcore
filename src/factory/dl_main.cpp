#ifndef __SQLC_SRC_FACTORY_DL_MAIN_CPP__
#define __SQLC_SRC_FACTORY_DL_MAIN_CPP__

#include <sqlcore/factory.hpp>

#include <src/factory/multi_thread.hpp>
#include <src/factory/single_thread.hpp>
#include <src/dl/loader.hpp>

namespace SQLCore {
    SQLC_SDK_DL_FUNC(SQLCore::IFactory*, DL__CreateFactory)(SQLCore::FactoryType _factoryType) {
        switch (_factoryType) {
            case SQLCore::FactoryType::SingleThreaded: {
                return new SQLCore::SingleThreadFactory();
            } case SQLCore::FactoryType::MultiThreaded: {
                return new SQLCore::MultiThreadFactory();
            } default: {
                return nullptr;
            }
        }
    }
}

#endif