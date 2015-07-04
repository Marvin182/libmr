#include "random.h"
#include <cassert>

namespace mr {
namespace random {

uint64_t getSeed() {
#ifdef STATIC_SEED
	return STATIC_SEED;
#endif
	static std::random_device gen{};
	std::uniform_int_distribution<uint64_t> dist{};
	return dist(gen);
}

std::mt19937_64& getGenerator() {
	// using thread_local makes it thread safe but doubles running time for single sequential calls
	static std::mt19937_64 generator{getSeed()};
	return generator;
}

int integer(int lowerBound, int upperBound) {
	// Creating the distribution is very cheap, only generator creation is expensive (=> static std::mt19937)
	std::uniform_int_distribution<int> dist{lowerBound, upperBound};
	return dist(getGenerator());
}

double probability() {
	static std::uniform_real_distribution<double> dist{0.0, std::nexttoward(1.0, 2.0)};
	return dist(getGenerator());
}

} // namespace random
} // namespace mr
