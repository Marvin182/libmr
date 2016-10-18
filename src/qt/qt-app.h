#ifndef MR_QT_APP_H
#define MR_QT_APP_H

#include <QString>
#include <QStringList>
#include <QMap>
#include "../common/assert.h"
#include "qt-string.h"

namespace mr {
namespace qt {

QString appLocalDataLocation();

// very simple serialization as the Qt serialization to non-ASCII
template <typename K, typename L>
QString serialize(const QMap<K, L>& m);

template <typename K, typename L>
QMap<K, L>& deserialize(cqstring s, QMap<K, L>& m);

template <typename K, typename L>
inline QString serialize(const QMap<K, L>& m) {
	QString s;
	s.reserve(20 * m.size());
	for (auto it = m.begin(); it != m.end(); it++) {
		s += QString("%1:%2;").arg(it.key()).arg(it.value());
	}
	return s;
}

template<typename K, typename L>
inline QMap<K, L>& deserialize(cqstring s, QMap<K, L>& m) {
	for (auto kvStr : s.split(';', QString::SkipEmptyParts)) {
		assert_debug(!kvStr.isEmpty());
		auto kv = kvStr.split(':');
		assert_debug(kv.size() == 2);
		m[kv[0]] = kv[1];
	}
	return m;
}

template<>
inline QMap<QString, QString>& deserialize<QString, QString>(cqstring s, QMap<QString, QString>& m) {
	for (auto kvStr : s.split(';', QString::SkipEmptyParts)) {
		assert_debug(!kvStr.isEmpty());
		auto kv = kvStr.split(':');
		assert_debug(kv.size() == 2);
		m[kv[0]] = kv[1];
	}
	return m;
}

template<>
inline QMap<QString, int>& deserialize<QString, int>(cqstring s, QMap<QString, int>& m) {
	for (auto kvStr : s.split(';', QString::SkipEmptyParts)) {
		assert_debug(!kvStr.isEmpty());
		auto kv = kvStr.split(':');
		assert_debug(kv.size() == 2);
		m[kv[0]] = kv[1].toInt();
	}
	return m;
}

} // namespace qt
} // namespace mr

#endif // MR_QT_APP_H
