#ifndef GLOBALS_VERSION_H
#define GLOBALS_VERSION_H

#include <QString>
#include "string-util.h"

namespace mr {

struct Version {
	int major;
	int minor;
	int revision;
	QString status;
	QString commitId;

	static const Version& get(cqstring gitVersion = "");
	static const Version& lib();

	int asNumber() const;
	bool isStable() const;
	QString shortStr() const;
	QString longStr() const;

private:
	Version(cqstring gitVersion);
};

} // namespace mr

#endif // GLOBALS_VERSION_H
