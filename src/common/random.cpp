#include "random.h"
#include <cassert>

namespace mr {
namespace random {

// #define STATIC_SEED 1729; // useful for testing

unsigned int getSeed() {
#ifdef STATIC_SEED
	return STATIC_SEED;
#endif
	static std::random_device gen{};
	std::uniform_int_distribution<unsigned int> dist{};
	return dist(gen);
}

uint64_t getSeed64() {
#ifdef STATIC_SEED
	return STATIC_SEED;
#endif
	static std::random_device gen{};
	std::uniform_int_distribution<uint64_t> dist{};
	return dist(gen);
}

std::mt19937& getGenerator() {
	static std::mt19937 generator{getSeed()};
	return generator;
}

std::mt19937_64& getGenerator64() {
	// using thread_local makes it thread safe but doubles running time for single sequential calls
	static std::mt19937_64 generator{getSeed64()};
	return generator;
}

int integer(int lowerBound, int upperBound) {
	// Creating the distribution is very cheap, only generator creation is expensive (=> static std::mt19937)
	std::uniform_int_distribution<int> dist{lowerBound, upperBound};
	return dist(getGenerator());
}

double probability() {
	static std::uniform_real_distribution<double> dist{0.0, std::nexttoward(1.0, 2.0)};
	return dist(getGenerator64());
}

} // namespace random
} // namespace mr
