#pragma once

#ifndef __SQLC_SRC_LOGGER_LOGGER_HPP__
#define __SQLC_SRC_LOGGER_LOGGER_HPP__

#include <sqlcore/logger.hpp>

namespace SQLCore {
	class Logger : public SQLCore::ILogger {
	public:
		SQLCore::Types::Void Info(SQLCore::Types::String _message) noexcept override final;
		SQLCore::Types::Void Warning(SQLCore::Types::String _message) noexcept override final;
		SQLCore::Types::Void Error(SQLCore::Types::String _message) noexcept override final;

		SQLCore::Types::Void Message(SQLCore::Types::String _messageType, SQLCore::Types::String _message) noexcept;

		SQLCore::Types::Void Release() noexcept override final;
	};

    extern SQLCore::Logger* AppLogger;
}

#endif