	#include "version.h"

#include <iostream>
#include <QRegExp>
#include <QStringList>

namespace mr {
namespace util {

const Version& Version::lib() {
	static Version* v = new Version(LIB_VERSION);
	assert_fatal(v != nullptr);
	return *v;
}

Version::Version(cqstring gitVersion) {
	assert_error(!gitVersion.isEmpty());
	QRegExp rx("^v?(\\d+)\\.(\\d+)\\.?(\\d*).(\\d+)-?(a\\d|b\\d|rc\\d|alpha\\d|beta\\d)?-\\d+-(\\w+)");
	rx.indexIn(gitVersion);

	assert_error(rx.pos() == 0, "version regexp did not match correctly (pos: %d)", rx.pos());

	bool ok = true;
	major = rx.cap(1).toInt(&ok);
	assert_error(ok, "could not parse major version");	
	minor = rx.cap(2).toInt(&ok);
	assert_error(ok, "could not parse minor version");	
	revision = rx.cap(3).toInt(&ok);
	if (!ok) revision = 0;
	build = rx.cap(4).toInt(&ok);
	assert_error(ok, "could not parse build number");

	status = rx.cap(5);
	commitId = rx.cap(6);

	assert_error(major >= 0);
	assert_error(minor >= 0);
	assert_error(revision >= 0);
	assert_error(build >= 0);
	assert_error(commitId.length() >= 6, "invalid commit id '%s'", cstr(commitId));
}

bool Version::isStable() const {
	return status.isEmpty();
}

QString Version::shortStr() const {
	if (isStable()) {
		return QString("%1.%2%3").arg(major).arg(minor).arg(rev());
	}
	return QString("%1.%2%3-%4").arg(major).arg(minor).arg(rev()).arg(status);
}

QString Version::longStr() const {
	return shortStr() + QString(" (commit id: %1, build: %2)").arg(commitId).arg(build);
}

} // namespace util
} // namespace mr
