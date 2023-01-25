#include "Utility/Debug.h"
#include <Windows.h> // @TODO OS guards and variations - only Windows compatible atm

std::stringstream   Debug::logs                         = std::stringstream{};
bool                Debug::reportingEventFocus          = false;
bool                Debug::reportingEventMouseEntered   = false;
bool                Debug::reportingScriptUpdates       = false;

void Debug::wait()
{
	std::cin.get();
}

void Debug::saveLogs(const std::string& path, const std::string& fileName)
{
	// @TODO
}

void debug::printLogs()
{
	std::cout << Debug::logs.str();
}

void Debug::clearLogs()
{
	Debug::logs.clear();
}

void Debug::show()
{
	::ShowWindow(::GetConsoleWindow(), SW_SHOW);
}

void Debug::hide()
{
	::ShowWindow(::GetConsoleWindow(), SW_HIDE);
}

bool Debug::isShowing()
{
	return ::IsWindowVisible(::GetConsoleWindow()) != FALSE;
}

void Debug::setPosition(int x, int y)
{
	SetWindowPos(GetConsoleWindow(), 0, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
}

bool Debug::isReportingEventFocus()
{
	return Debug::reportingEventFocus;
}

bool Debug::isReportingEventMouseEntered()
{
	return Debug::reportingEventMouseEntered;
}

bool Debug::isReportingScriptUpdates()
{
	return Debug::reportingScriptUpdates;
}

void Debug::setReportingEventFocus(bool reportingEventFocus)
{
	Debug::reportingEventFocus = reportingEventFocus;
}

void Debug::setReportingEventMouseEntered(bool reportingEventMouseEntered)
{
	Debug::reportingEventMouseEntered = reportingEventMouseEntered;
}

void Debug::setReportingScriptUpdates(bool reportingScriptUpdates)
{
	Debug::reportingScriptUpdates = reportingScriptUpdates;
}
