#ifndef MR_QT_STRING_H
#define MR_QT_STRING_H

#include <QString>

using cqstring = const QString&;

const char* cstr(cqstring s); // similar to qPrintable(str) but with utf8, qPrintable(str)=str.toLocal8Bit().constData()
std::string str(cqstring s);
QString qstr(const std::string& s);

template <typename T>
QString qnstr(T n);

std::ostream& operator<<(std::ostream& os, cqstring s);

namespace mr {

QStringList split(cqstring s, QChar separator, QChar textQualifier = QChar(), QString::SplitBehavior behavior = QString::KeepEmptyParts);
QStringList split(cqstring s, cqstring separator, cqstring textQualifier, QString::SplitBehavior behavior = QString::KeepEmptyParts);
QString separateGroups(cqstring s, int groupSize, QChar separator = ' ');

} // namespace mr

inline const char* cstr(cqstring s) { return s.toUtf8().constData(); }
inline std::string str(cqstring s) { return s.toStdString(); }
inline QString qstr(const std::string& s) { return QString::fromStdString(s); }

template <typename T>
inline QString qnstr(T n) { return QString::number(n, 10); }

// [[deprecated("currency() will soon be removed from mr-lib")]]
QString currency(int amount, cqstring symbol = "€");

// [[deprecated("fuzzyMatch() will soon be replaced by a more suitable method within mr namespace")]]
bool fuzzyMatch(cqstring text, cqstring needle);

#endif // MR_QT_STRING_H
