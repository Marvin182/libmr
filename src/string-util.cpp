#include "string-util.h"
#include "assert.h"
#include <QLocale>

std::ostream& operator<<(std::ostream& os, cqstring s) {
	return (os << s.toStdString());
}

const char* cstr(cqstring s) {
	return s.toUtf8().constData();
}

std::string str(cqstring s) {
	return s.toStdString();
}

QString qstr(const std::string& s) {
	return QString::fromStdString(s);
}

namespace mr {
namespace string {

QString trim(QString& s, cqstring prefix, cqstring suffix) {
	int a = s.startsWith(prefix) ? prefix.length() : 0;
	int b = s.length() - a - (s.endsWith(suffix) ? suffix.length() : 0);
	return QStringRef(&s, a, b).toString();
}

void trim(QStringList& list, cqstring prefix, cqstring suffix) {
	for (auto& s : list) {
		if (!s.isEmpty()) {
			s = trim(s, prefix, suffix);
		}
	}
}

QStringList splitAndTrim(cqstring line, cqstring delimiter, cqstring textQualifier) {
	auto list = line.split(delimiter);
	trim(list, textQualifier, textQualifier);
	return list;
}

} // namespace string
} // namespace mr

QString currency(int amount, cqstring symbol) {
	return QLocale().toCurrencyString(amount / 100.0, symbol);
}

bool fuzzyMatch(cqstring text, cqstring needle) {
	int j = 0;
	for (const auto& chr : needle) {
		const auto c = chr.toLower();
		while (j < text.length() && text[j].toLower() != c) {
			j++;
		}
		if (j >= text.length()) {
			return false;
		}
	}
	return true;
}
