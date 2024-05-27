#pragma once

#ifndef __SQLC_TYPES_HPP__
#define __SQLC_TYPES_HPP__

#include <filesystem>
#include <string>
#include <vector>
#include <list>

namespace SQLCore::Types {
    using Void = void;

    using Int8 = char;
    using UInt8 = unsigned char;

    using Int16 = short;
    using UInt16 = unsigned short;

    using Int32 = int;
    using UInt32 = unsigned int;

    using Int64 = long long;
    using UInt64 = unsigned long long;

    using Double = double;
    using Float = float;

    using Bool = bool;

    using String = std::string;
    using WString = std::wstring;

    using Uri = std::string;
    using WUri = std::wstring;

    using Path = std::filesystem::path;

    template <class Type>
    using Array = std::vector<Type>;

    template <class Type>
    using List = std::list<Type>;
}

#endif