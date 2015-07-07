#include "assert.h"
#include <iostream>

#include <QFile>
#include <QDateTime>
#include <QApplicationStateChangeEvent>

using namespace pempek::assert::implementation;

namespace mr {
namespace assert {

// Warning = 32, Debug = 64, Error = 128, Fatal = 256
int minWriteToOutputLevel = 0;
int minLogLevel = 0;
const char* errorLogFileName = "errors.txt";
int minExitApplicationLevel = 128;

namespace {
	AssertHandler _customAssertHandler = nullptr;
}

const char* levelToStr(int level) {
	switch (level) {
		case AssertLevel::Warning: return "warning";
		case AssertLevel::Debug: return "debug";
		case AssertLevel::Error: return "error";
		case AssertLevel::Fatal: return "fatal";
		default: assert_unreachable();
	}
	return ""; // just to prevent the compiler warning
}

AssertAction::AssertAction onAssert(const char* file,
									int line,
									const char* function,
									const char* expression,
									int level,
									const char* message) {
	const char* msg = message == nullptr ? "" : message;

	if (level >= minWriteToOutputLevel) {
		// write message to output
		std::cerr << "Assertion failed: " << expression << "\n";
		if (message != nullptr) {
			std::cerr << "\tmessage: " << message << " (level: " << level << " = " << levelToStr(level) << ")\n";
		} else {
			std::cerr << "\tlevel: " << level << " = " << levelToStr(level) << "\n";
		}
		std::cerr << "\tfunction: " << function << "\n\tfile: " << file << " line " << line << std::endl;
	}

	if (level >= minLogLevel) {
		QFile errorLog(errorLogFileName);
		if (errorLog.open(QIODevice::Append | QIODevice::Text)) {
			auto dt = QString(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss") + ": Assertion failed!\n").toUtf8();
			errorLog.write(dt);
			errorLog.write(QString("\texpression: %1\n").arg(expression).toUtf8());
			errorLog.write(QString("\tmessage: %1 (level %2 (%3))\n").arg(msg).arg(levelToStr(level)).arg(level).toUtf8());
			errorLog.write(QString("\tfunction %1 in file: %2 line %3\n").arg(function).arg(file).arg(line).toUtf8());
			errorLog.close();
		} else {
			std::cerr << "failed to open error log file '" << errorLogFileName << "'" << std::endl;
		}
	}

	if (_customAssertHandler) {
		return _customAssertHandler(file, line, function, expression, level, message);
	}

	if (level >= minExitApplicationLevel) {
		return AssertAction::AssertAction::Abort;
	}
	return AssertAction::AssertAction::None;
}

void initAssertHandler() {
	setAssertHandler(onAssert);
}

void setCustomAssertHandler(AssertHandler handler) {
	_customAssertHandler = handler ? handler : _customAssertHandler;
}

} // namespace assert
} // namespace mr

