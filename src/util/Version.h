#ifndef MR_VERSION_H
#define MR_VERSION_H

#include "../common/assert.h"
#include "qt-string.h"

namespace mr {
namespace util {

struct Version {
	int major;
	int minor;
	int revision;
	int build;
	QString status;
	QString commitId;

	Version(cqstring gitVersion);

	static const Version& app();
	static const Version& lib();

	bool isStable() const;
	QString shortStr() const;
	QString longStr() const;

private:

	QString rev() const { return revision > 0 ? QString(".%1").arg(revision) : ""; }
};

inline const Version& Version::app() {
	static Version* v = new Version(GIT_VERSION);
	assert_fatal(v != nullptr);
	return *v;
}

} //namespace util
} // namespace mr

#endif // MR_VERSION_H
