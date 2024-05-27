#pragma once

#ifndef __SQLC_SRC_DL_LOADER_HPP__
#define __SQLC_SRC_DL_LOADER_HPP__

#include <sqlcore/sdk/system.hpp>
#include <sqlcore/types.hpp>

#if defined(SQLC_SDK_WINDOWS)
#include <Windows.h>
#elif defined(SQLC_SDK_UNIX)
#include <dlfcn.h>
#endif

#if defined(SQLC_SDK_MSVC)
#define SQLC_DL_EXPORT __declspec(dllexport)
#define SQLC_DL_CALL_TYPE __stdcall
#elif defined(SQLC_SDK_GCC) || defined(SQLC_SDK_CLANG)
#define SQLC_DL_EXPORT __attribute__((visibility("default")))
#define SQLC_DL_CALL_TYPE
#endif

#define SQLC_DL_FUNC(return_type, func_name) extern "C"  return_type SQLC_SDK_DL_CALL_TYPE func_name

namespace SQLCore {
    namespace DL {
        #if defined(SQLC_SDK_WINDOWS)
        using Handle = HMODULE;
        using FuncHandle = FARPROC;
        #elif defined(SQLC_SDK_UNIX)
        using Handle = void*;
        using FuncHandle = void*;
        #endif

        SQLCore::DL::Handle Load(SQLCore::Types::String _fileName) noexcept;
        SQLCore::DL::FuncHandle GetFunc(SQLCore::DL::Handle _handle, SQLCore::Types::String _funcName) noexcept;
        SQLCore::Types::Void Unload(SQLCore::DL::Handle _handle) noexcept;
    }
}

#endif