#pragma once

#ifndef __SQLC_API_HPP__
#define __SQLC_API_HPP__

#if defined(_MSC_VER)
#define SQLC_INTERFACE __interface
#else
#define SQLC_INTERFACE struct
#endif

#define SQLC_API_BASE_INTERFACE(interface_name) SQLC_INTERFACE interface_name
#define SQLC_API_INTERFACE(interface_name, base_interface_name) SQLC_INTERFACE interface_name : public base_interface_name
#define SQLC_API_METHOD(return_type, method_name) virtual return_type method_name noexcept = 0

#endif