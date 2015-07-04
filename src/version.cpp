#include "version.h"

#include "assert.h"
#include <iostream>
#include <QRegExp>
#include <QStringList>

namespace mr {

const Version& Version::get(cqstring gitVersion) {
	static Version* v = new Version(gitVersion);
	assert_fatal(v != nullptr);
	return *v;
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
	if (!ok) {
		revision = rx.cap(5).toInt(&ok);
		assert_error(ok, "could not revision number");
	}

	status = rx.cap(4);
	commitId = rx.cap(6);

	assert_error(major >= 0);
	assert_error(minor >= 0);
	assert_error(revision >= 0);
}

int Version::asNumber() const {
	int x = revision + (1000 * (minor + 100 * major));
	x *= 10;
	assert_error(x >= 10);
	if (status == "rc3") {
		x -= 1;
	} else if (status == "rc2") {
		x -= 2;
	} else if (status == "rc1") {
		x -= 3;
	} else if (status == "beta") {
		x -= 6;
	} else if (status == "alpha") {
		x -= 9;
	}
	return x;
}

bool Version::isStable() const {
	return status.isEmpty();
}

QString Version::shortStr() const {
	return QString("%1.%2.%3").arg(major).arg(minor).arg(revision);
}

QString Version::longStr() const {
	return QString("%1.%2.%3%4 (commit id: %5)").arg(major).arg(minor).arg(revision).arg(status.isEmpty() ? "" : " " + status).arg(commitId);
}

} // namespace mr
