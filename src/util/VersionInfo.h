#ifndef MR_VERSION_INFO_H
#define MR_VERSION_INFO_H

#include <cstring>
#include <sstream>
#include "const_string.h"

namespace mr {
namespace util {

struct VersionInfo {
	const int major;
	const int minor;
	const int revision;
	const int build;
	const_string commit;
	const_string branch;

	constexpr Version(int major, int minor, int revision, int build, const_string commit, const_string branch, const_string stage_name, int stage_number):
		major(major),
		minor(minor),
		revision(revision),
		build(build),
		commit(commit),
		branch(branch),
		stage_number(stage_number),
		stage_name(stage_name)
	{}

	constexpr bool isAlpha() const {
		return !isStable() && stage_name[0] == 'a';
	}

	constexpr bool isBeta() const {
		return !isStable() && stage_name[0] == 'b';
	}

	constexpr bool isReleaseCandidate() const {
		return !isStable() && (stage_name[0] == 'r' || stage_name[0] == 'c');
	}

	constexpr bool isStable() const {
		return stage_name.size() == 0;
	}

	std::string stage() const {
		std::ostringstream os;
		if (!isStable()) {
			if (isReleaseCandidate()) {
				os << "rc";
			} else {
				os << stage_name[0];
			}
			os << stage_number;
		}
		return os.str();
	}

	std::string toString() const {
		std::ostringstream os;
		os << major << '.' << minor;
		if (revision > 0) {
			os << '.' << revision;
		}
		os << stage();
		return os.str();
	}

private:
	const_string stage_name;
	const int stage_number;
};

} //namespace util
} // namespace mr


#endif // MR_VERSION_H
