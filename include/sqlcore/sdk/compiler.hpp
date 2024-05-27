#pragma once

#ifndef __SQLC_SDK_COMPILER_HPP__
#define __SQLC_SDK_COMPILER_HPP__

#if defined(_MSC_VER)
#define SQLC_SDK_MSVC
#elif defined(__clang__)
#define SQLC_SDK_CLANG
#elif defined(__GNUC__)
#define SQLC_SDK_GCC
#else
#error "This compiler is not support yet."
#endif

#endif