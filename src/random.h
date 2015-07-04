#include <random>

namespace mr {
namespace random {

// #define STATIC_SEED 1729; // useful for testing

uint64_t getSeed();

std::mt19937_64& getGenerator();

int integer(int lowerBound, int upperBound);

double probability();

} // namespace random
} // namespace mr
