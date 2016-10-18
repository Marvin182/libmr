#ifndef MR_VECTOR_H
#define MR_VECTOR_H

#include <iostream>
#include <vector>

// Print method for vectors
template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec) { 
	if (vec.empty()) return os << "[]";
	os << "[" << vec[0];
	for (int i = 1; i < vec.size(); i++) {
		os << " " << vec[i];
	}
	return os << "]";
}

#endif // MR_VECTOR_H