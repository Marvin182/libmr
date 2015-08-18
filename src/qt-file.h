#ifndef MR_QT_FILE_H
#define MR_QT_FILE_H

#include <QFile>
#include <QStringList>
#include <QTextStream>
#include <QTextCodec>
#include "assert.h"
#include "qt-string.h"

namespace mr {
namespace io {

template <typename F>
void readTextFile(cqstring filename, F func);

template <typename F>
void parseCsvFile(cqstring filename, cqstring delimiter, cqstring textQualifier, bool skipFirstLine, F lineFunc);

template <typename F>
inline void readTextFile(cqstring filename, F func) {
	QFile file(filename);

	// verify that the file is opened correctly
	if (!file.exists()) {
		throw std::invalid_argument(QString("File '%1' does not exist.").arg(filename).toStdString());
	}
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		throw std::runtime_error(QString("Could not open file '%1'").arg(filename).toStdString());
	}
	assert_warning(!file.atEnd(), "file '%s' is empty", cstr(filename));

	auto data = file.readAll();
	assert_error(file.atEnd(), "not all data read from file '%s'", cstr(filename));

	QTextStream in(data);
	in.setCodec(QTextCodec::codecForUtfText(data));

	func(in);

	assert_warning(in.atEnd(), "did not read whole file '%s'", cstr(filename));
}

template <typename F>
inline void parseCsvFile(cqstring filename, cqstring delimiter, cqstring textQualifier, bool skipFirstLine, F lineFunc) {
	readTextFile(filename, [&](QTextStream& in) {
		if (skipFirstLine && !in.atEnd()) {
			in.readLine();
		}
		int lineNumber = skipFirstLine ? 1 : 0;
		while (!in.atEnd()) {
			lineNumber++;
			auto line = QString(in.readLine()).trimmed();
			auto fields = mr::split(line, delimiter, textQualifier);
			lineFunc(lineNumber, fields);
		}
	});
}

} // namespace io
} // namespace mr

#endif // MR_QT_FILE_H
