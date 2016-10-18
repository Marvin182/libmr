#ifndef MR_CODEJAM_H
#define MR_CODEJAM_H

#include <iostream>
#include "assert.h"

namespace mr {
namespace codejam {

template <typename F>
void forEachTestCase(F solve) {
	int T;
	std::cin >> T;
	assert_fatal(T > 0);
	for (int t = 1; t <= T; t++) {
		std::cout << "Case #" << t << ": " << solve() << std::endl;
	}
}

} // namespace codejam
} // namespace mr

#endif // MR_CODEJAM_H