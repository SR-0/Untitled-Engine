#pragma once

#include <sstream> 
#include <iostream>

class Debug
{
private:

	static std::stringstream    logs;
	static bool                 reportingEventFocus;
	static bool                 reportingEventMouseEntered;
	static bool                 reportingScriptUpdates;

private:

	Debug() = default;
	Debug(const Debug&) = delete;
	Debug(Debug&&) = delete;
	~Debug() = default;

private:

	Debug& operator = (const Debug&) = delete;
	Debug& operator = (Debug&&) = delete;

public: // core

	static void                                     wait();
	template <typename ... Parameters> static void  log(Parameters ... parameters);
	static void                                     saveLogs(const std::string& path, const std::string& fileName);
	static void                                     printLogs();
	static void                                     clearLogs();
	template <typename ... Parameters> static void  print(Parameters ... parameters);
	template <typename ... Parameters> static void  printLine(Parameters ... parameters);
	static void                                     show();
	static void                                     hide();
	static bool                                     isShowing();
	static void                                     setPosition(int x, int y);

public: // getter(s)

	static bool isReportingEventFocus();
	static bool isReportingEventMouseEntered();
	static bool isReportingScriptUpdates();

public: // setter(s)

	static void setReportingEventFocus(bool reportingEventFocus);
	static void setReportingEventMouseEntered(bool reportingEventMouseEntered);
	static void setReportingScriptUpdates(bool reportingScriptUpdates);

};

using debug = Debug;

template<typename ...Parameters>
inline void Debug::log(Parameters ...parameters)
{
	((Debug::logs << parameters), ...);
}

template<typename ...Parameters>
inline void debug::print(Parameters ...parameters)
{
	std::stringstream ss;
	((ss << parameters), ...);
	std::cout << ss.str();
}

template<typename ...Parameters>
inline void debug::printLine(Parameters ...parameters)
{
	std::stringstream ss;
	((ss << parameters << "\n"), ...);

	if (ss.str().size() == 0)
	{
		ss << "\n";
	}

	std::cout << ss.str();
}