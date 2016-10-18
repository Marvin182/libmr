#ifndef MR_RANDOM_H
#define MR_RANDOM_H

#include <random>

namespace mr {
namespace random {

unsigned int getSeed();
uint64_t getSeed64();

std::mt19937& getGenerator();
std::mt19937_64& getGenerator64();

int integer(int lowerBound, int upperBound);

double probability();

} // namespace random
} // namespace mr

#endif // MR_RANDOM_H