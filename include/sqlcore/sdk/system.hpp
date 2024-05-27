#pragma once

#ifndef __SQLC_SDK_SYSTEM_HPP__
#define __SQLC_SDK_SYSTEM_HPP__

#if defined(_WIN32) || defined(_WIN64)
#define SQLC_SDK_WINDOWS
#elif defined(__linux__)
#define SQLC_SDK_UNIX
#define SQLC_SDK_LINUX
#elif defined(__APPLE__)
#define SQLC_SDK_UNIX
#define SQLC_SDK_APPLE
#else
#error "This system is not support yet."
#endif

#endif