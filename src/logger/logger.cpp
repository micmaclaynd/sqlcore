#ifndef __SQLC_SRC_LOGGER_LOGGER_CPP__
#define __SQLC_SRC_LOGGER_LOGGER_CPP__

#include <sqlcore/sdk/dl.hpp>

#include <src/logger/logger.hpp>
#include <src/dl/loader.hpp>

#include <iostream>
#include <iomanip>
#include <chrono>
#include <format>

namespace SQLCore {
	SQLCore::Types::Void Logger::Info(SQLCore::Types::String _message) noexcept {
		this->Message("Info", _message);
	}
	SQLCore::Types::Void Logger::Warning(SQLCore::Types::String _message) noexcept {
		this->Message("Warning", _message);
	}
	SQLCore::Types::Void Logger::Error(SQLCore::Types::String _message) noexcept {
		this->Message("Error", _message);
	}

	SQLCore::Types::Void Logger::Message(SQLCore::Types::String _messageType, SQLCore::Types::String _message) noexcept {
		auto now = std::chrono::system_clock::now();
		auto now_time_t = std::chrono::system_clock::to_time_t(now);
		std::stringstream time_stream;
		time_stream << std::put_time(std::localtime(&now_time_t), "%Y.%m.%d %H:%M:%S");

		std::cout << std::format("[{}][{}]->{}", time_stream.str(), _messageType, _message) << std::endl;
	}

	SQLCore::Types::Void Logger::Release() noexcept {
		delete this;
	}

    SQLCore::Logger* AppLogger = new Logger();

    SQLC_SDK_DL_FUNC(SQLCore::ILogger*, DL__GetLogger)() noexcept {
        return reinterpret_cast<SQLCore::ILogger*>(AppLogger);
    }
}

#endif
