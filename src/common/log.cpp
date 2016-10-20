#include "log.h"

#include <iostream>
#include <QFile>
#include <QDateTime>
#include "assert.h"
#include "../qt/qt-string.h"

namespace mr {
namespace log {

const char* filenames[] = {
	"debug.txt", // QtDebugMsg
	"debug.txt", // QtWarningMsg
	"errors.txt", // QtCriticalMsg
	"errors.txt", // QtFatalMsg
	"log.txt" // QtInfoMsg
};

const char* messageTypeToStr(QtMsgType type) {
	switch (type) {
		case QtDebugMsg: return "Debug";
		case QtInfoMsg: return "Info"; // QtInfoMsg was added in Qt 5.5
		case QtWarningMsg: return "Warning";
		case QtCriticalMsg: return "Critical";
		case QtFatalMsg: return "Fatal";
		default: return "";
	}
}

void customMessageHandler(QtMsgType type, const QMessageLogContext&, const QString& msg) {
	// print to standard output
	auto m = QString("%1: %2\n").arg(messageTypeToStr(type)).arg(msg);
	if (type == QtWarningMsg || type == QtCriticalMsg || type == QtFatalMsg) {
		std::cerr << m;
		std::flush(std::cerr);
	} else {
		std::cout << m;
		std::flush(std::cout);
	}

	// write message into log file
	QFile messageLog(filenames[type]);
	if (messageLog.open(QIODevice::Append | QIODevice::Text)) {
		auto dt = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
		messageLog.write(QString("%1\t%2\t%3\n").arg(dt).arg(messageTypeToStr(type)).arg(msg).toUtf8());
		messageLog.close();
	}
}

void init() {
	qInstallMessageHandler(customMessageHandler);
}

void setLogfile(QtMsgType type, const char* filename) {
	filenames[type] = filename;
}

} // namespace log
} // namespace mr
