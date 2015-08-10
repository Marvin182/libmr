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
namespace string {

QString trim(QString& s, cqstring prefix, cqstring suffix);
void trim(QStringList& list, cqstring prefix, cqstring suffix);
QStringList splitAndTrim(cqstring line, cqstring delimiter, cqstring textQualifier);
QString separateGroups(cqstring s, int groupSize, QChar separator = ' ');

} // namespace string
} // namespace mr

QString currency(int amount, cqstring symbol = "€");

bool fuzzyMatch(cqstring text, cqstring needle);

#endif // MR_STRING_UTIL_H
