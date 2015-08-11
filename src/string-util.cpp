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

QStringList split(cqstring s, QChar sep, QChar tq, QString::SplitBehavior behavior) {
	return split(s, sep, tq.isNull() ? QString("") : tq, behavior);
}

QStringList split(cqstring s, cqstring sep, cqstring tq, QString::SplitBehavior behavior) {
	QStringList parts;

	int len = s.length();
	int tqLen = tq.length();
	int i = 0;

	while (i < len) {
		int start, end;
		if (QStringRef(&s, i, len - i).startsWith(tq)) {
			// part with text qualifier
			start = i + tqLen;
			end = s.indexOf(tq, start);
			i = end + tqLen; // point i to the beginning of the separator
		} else {
			// part without text qualifier
			start = i;
			end = s.indexOf(sep, i);
			if (end == -1) end = len;
			i = end; // point i to the beginning of the separator
		}

		// add part
		if (end - start > 0 || behavior == QString::KeepEmptyParts) {
			// add part, even it is empty
			parts << QStringRef(&s, start, end - start).toString();
		} // else part is empty and behavior was set to QString::SkipEmptyParts
		
		// if we are not at the end of the string, there must be a separator
		if (i < len && !QStringRef(&s, i, len - i).startsWith(sep)) {
			// incorrect formatted input string
			throw std::invalid_argument(QString("Missing separator at position %1 of '%2', last part2: '%3'").arg(i).arg(s).arg(QStringRef(&s, start, end - start).toString()).toStdString());
		}
		// skip the separator
		i += sep.length();
	}

	return parts;
}

QString separateGroups(cqstring s, int groupSize, QChar separator) {
	assert_error(groupSize > 0, "groupSize: %d", groupSize);
	int groupCount = (s.length() - 1) / groupSize + 1;
	int len = s.length() + groupCount - 1;
	QString grouped(len, separator);

	int j = 0;
	for (int i = 0; i < s.length(); i++) {
		grouped[j++] = s[i];
		if ((j + 1) % (groupSize + 1) == 0) j++;
	}

	return grouped;
}

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
