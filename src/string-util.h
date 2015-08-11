#ifndef MR_STRING_UTIL_H
#define MR_STRING_UTIL_H

#include <QString>

#define cqstring const QString&
// using cqstring = const QString&;

// qPrintable(str) = str.toLocal8Bit().constData()
// cstr(str) = str.toUtf8().constData()
const char* cstr(cqstring s);
std::string str(cqstring s);
QString qstr(const std::string& s);

std::ostream& operator<<(std::ostream& os, cqstring s);

namespace mr {

QStringList split(cqstring s, QChar separator, QChar textQualifier = QChar(), QString::SplitBehavior behavior = QString::KeepEmptyParts);
QStringList split(cqstring s, cqstring separator, cqstring textQualifier, QString::SplitBehavior behavior = QString::KeepEmptyParts);
QString separateGroups(cqstring s, int groupSize, QChar separator = ' ');

} // namespace mr

QString currency(int amount, cqstring symbol = "€");

bool fuzzyMatch(cqstring text, cqstring needle);

#endif // MR_STRING_UTIL_H
