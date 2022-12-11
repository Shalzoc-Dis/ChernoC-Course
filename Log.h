#pragma once // Makes sure that this header file is only included once to make sure there are no re-declairation errors

#include <iostream>

// The old way of makeing a header guard is wil #ifndef, like this:
// #ifndef _LOG_H
// #define _LOG_H
// Body
// #endif


class Log 
{
public:
	// Using an enum instead of defines, keeping it cleaner
	enum Level : unsigned char
	{
		LevelError = 0, LevelWarning, LevelInfo
	};
private:
	Level m_LogLevel = LevelInfo;	// the m_ convention says that this is a class member that is private
public:
	void setLevel(Level level)
	{
		m_LogLevel = level;
	}

	void warn(const char* message)
	{
		if (m_LogLevel >= LevelWarning)
			std::cout << "[WARNING]: " << message << std::endl;
	}

	void info(const char* message)
	{
		if (m_LogLevel >= LevelInfo)
			std::cout << "[INFO]: " << message << std::endl;
	}

	void error(const char* message)
	{
		if (m_LogLevel >= LevelError)
			std::cout << "[ERROR]: " << message << std::endl;
	}
};
