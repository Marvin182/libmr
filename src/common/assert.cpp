#include "assert.h"

#include <iostream>
#include <QtDebug>
#include <QFile>
#include <QApplicationStateChangeEvent>

using namespace pempek::assert::implementation;

namespace mr {
namespace assert {

int minWriteToOutputLevel = 0;
int minLogLevel = 0;
const char* errorLogFileName = "errors.txt";

// Warning = 32, Debug = 64, Error = 128, Fatal = 256
int minExitApplicationLevel = 128;
std::vector<AssertHandler> additionalAssertHandlers;

const char* levelToStr(int level) {
	switch (level) {
		case AssertLevel::Warning: return "warning";
		case AssertLevel::Debug: return "debug";
		case AssertLevel::Error: return "error";
		case AssertLevel::Fatal: return "fatal";
		default: return "[invalid assert level]";
	}
}

QtMsgType levelToQtMsgType(int level) {
	switch (level) {
		case AssertLevel::Warning: return QtDebugMsg;
		case AssertLevel::Debug: return QtDebugMsg;
		case AssertLevel::Error: return QtCriticalMsg;
		case AssertLevel::Fatal: return QtFatalMsg;
		default: return QtFatalMsg;
	}
}

AssertAction::AssertAction onAssert(const char* file,
									int line,
									const char* function,
									const char* expression,
									int level,
									const char* message) {
	// log assertion fail
	QDebug out(levelToQtMsgType(level));
	QString msg = message == nullptr ? "" : QString("\n\t\tmessage: %1").arg(message);
	out.noquote().nospace() << QString("Assertion failed (level %2, %3)").arg(level).arg(levelToStr(level))
				<< "\n\t\t" << QString("expression: %1").arg(expression)
				<< msg
				<< "\n\t\t" << QString("function %1 in file: %2 line %3").arg(function).arg(file).arg(line);

	// call additional handlers
	for (auto handler : additionalAssertHandlers) {
		auto a = handler(file, line, function, expression, level, message);
		if (a != AssertAction::AssertAction::None) {
			return a;
		}
	}

	return level < minExitApplicationLevel ? AssertAction::AssertAction::None : AssertAction::AssertAction::Abort;
}

void init() {
	setAssertHandler(onAssert);
}

void setMinExistApplicationLevel(int level) {
	minExitApplicationLevel = level;
}

void addAssertHandler(AssertHandler handler) {
	additionalAssertHandlers.push_back(handler);
}

void removeAllAsserdHandlers() {
	additionalAssertHandlers.clear();
}


} // namespace assert
} // namespace mr

