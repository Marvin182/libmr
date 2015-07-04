#include <iostream>
#include <vector>

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec) { 
	if (vec.empty()) return os << "[]";
	os << "[" << vec[0];
	for (int i = 1; i < vec.size(); i++) {
		os << " " << vec[i];
	}
	return os << "]";
}
