#include "qt-string.h"
#include "../common/assert.h"
#include <QLocale>
#include <iostream>

std::ostream& operator<<(std::ostream& os, cqstring s) {
	return (os << s.toStdString());
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

	while (i <= len) {
		int start, end;
		if (tqLen > 0 && QStringRef(&s, i, len - i).startsWith(tq)) {
			// part with text qualifier
			start = i + tqLen;
			end = s.indexOf(tq, start);
			if (end == -1) {
				// no closing text qualifier found, point i to the end of the string
				i = len - 1;
			} else {
				// point i to the beginning of the separator (there should be one after the closing text qualifier)
				i = end == -1 ? len - 1 : end + tqLen;
			}
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
			throw std::invalid_argument(QString("Missing separator at position %1 of '%2', last part2: '%3', i: %4, len: %5").arg(i).arg(s).arg(QStringRef(&s, start, end - start).toString()).arg(i).arg(len).toStdString());
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
