#ifndef __SQLC_SRC_DL_LOADER_CPP__
#define __SQLC_SRC_DL_LOADER_CPP__

#include <src/dl/loader.hpp>

namespace SQLCore::DL {
    SQLCore::DL::Handle Load(SQLCore::Types::String _fileName) noexcept {
        #if defined(SQLC_SDK_WINDOWS)
        SQLCore::DL::Handle library = ::LoadLibraryA(_fileName.c_str());
        #elif defined(SQLC_SDK_UNIX)
        SQLCore::DL::Handle library = ::dlopen(_fileName.c_str(), RTLD_LAZY);
        #endif
        return library;
    }
    SQLCore::DL::FuncHandle GetFunc(SQLCore::DL::Handle _handle, SQLCore::Types::String _funcName) noexcept {
        #if defined(SQLC_SDK_WINDOWS)
        SQLCore::DL::FuncHandle func = ::GetProcAddress(_handle, _funcName.c_str());
        #elif defined(SQLC_SDK_UNIX)
        SQLCore::DL::FuncHandle func = ::dlsym(_handle, _funcName.c_str());
        #endif
        return func;
    }
    SQLCore::Types::Void Unload(SQLCore::DL::Handle _handle) noexcept {
        #if defined(SQLC_SDK_WINDOWS)
        ::FreeLibrary(_handle);
        #elif defined(SQLC_SDK_UNIX)
        ::dlclose(_handle);
        #endif
    }
}

#endif