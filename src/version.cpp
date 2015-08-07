#include "version.h"

#include <iostream>
#include <QRegExp>
#include <QStringList>

namespace mr {

const Version* Version::get(cqstring gitVersion) {
	return new Version(gitVersion);
}

const Version& Version::lib() {
	static Version* v = new Version(LIB_VERSION);
	assert_fatal(v != nullptr);
	return *v;
}

Version::Version(cqstring gitVersion) {
	assert_error(!gitVersion.isEmpty());
	QRegExp rx("v?(\\d+)\\.(\\d+)\\.?(\\d*)\\.?(\\w*)\\.(\\d+)\\.(\\w+)");
	rx.indexIn(gitVersion);

	assert_error(rx.pos() == 0 || rx.capturedTexts().length() != 7, "version regexp did not match correctly (pos: %d)", rx.pos());

	bool ok = true;
	major = rx.cap(1).toInt(&ok);
	assert_error(ok, "could not parse major version");	
	minor = rx.cap(2).toInt(&ok);
	assert_error(ok, "could not parse minor version");	
	revision = rx.cap(3).toInt(&ok);
	if (!ok) revision = 0;
	build = rx.cap(5).toInt(&ok);
	assert_error(ok, "could not parse build number");

	status = rx.cap(4);
	commitId = rx.cap(6);

	assert_error(major >= 0);
	assert_error(minor >= 0);
	assert_error(revision >= 0);
	assert_error(build >= 0);
}

int Version::asNumber() const {
	int x = ((major * 100 + minor) * 100 + revision) * 100;
	assert_error(x >= 100);
	if (status.startsWith("rc")) {
		x -= 10;
	} else if (status.startsWith("beta")) {
		x -= 50;
	} else if (status.startsWith("alpha")) {
		x -= 99;
	}
	x += build;
	return x;
}

bool Version::isStable() const {
	return status.isEmpty() || status == "final";
}

QString Version::shortStr() const {
	if (isStable()) {
		return QString("%1.%2%3").arg(major).arg(minor).arg(rev());
	}
	return QString("%1.%2%3-%4").arg(major).arg(minor).arg(rev()).arg(status);
}

QString Version::longStr() const {
	if (build > 0) {
		return shortStr() + QString(" (commit id: %1, build: %2)").arg(commitId).arg(build);
	}
	return shortStr() + QString(" (commit id: %1)").arg(commitId);
}

} // namespace mr
