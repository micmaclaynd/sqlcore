#pragma once

#ifndef __SQLC_SDK_DL_HPP__
#define __SQLC_SDK_DL_HPP__

#include <sqlcore/sdk/compiler.hpp>
#include <sqlcore/factory.hpp>

#if defined(SQLC_SDK_MSVC)
#define SQLC_SDK_DL_EXPORT __declspec(dllexport)
#define SQLC_SDK_DL_CALL_TYPE __stdcall
#elif defined(SQLC_SDK_GCC) || defined(SQLC_SDK_CLANG)
#define SQLC_SDK_DL_EXPORT __attribute__((visibility("default")))
#define SQLC_SDK_DL_CALL_TYPE
#endif

#define SQLC_SDK_DL_FUNC(return_type, func_name) extern "C" SQLC_SDK_DL_EXPORT return_type SQLC_SDK_DL_CALL_TYPE func_name

#endif