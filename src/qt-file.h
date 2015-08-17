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
bool readTextFile(cqstring filename, F func);

template <typename F>
void parseCsvFile(cqstring filename, cqstring delimiter, cqstring textQualifier, bool skipFirstLine, F lineFunc);

template <typename F>
inline bool readTextFile(cqstring filename, F func) {
	QFile file(filename);

	// verify that the file is opened correctly
	assert_error(file.exists(), "file '%s' does not exists", cstr(filename));
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		assert_error(false, "Could not open file '%s'", cstr(filename));
		return false;
	}
	assert_debug(!file.atEnd(), "statement file '%s' is empty", cstr(filename));

	auto data = file.readAll();
	assert_error(file.atEnd(), "not all data read from file %s'", cstr(filename));

	QTextStream in(data);
	in.setCodec(QTextCodec::codecForUtfText(data));

	func(in);

	assert_warning(in.atEnd(), "did not parse whole file '%s'", cstr(filename));

	return true;
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
