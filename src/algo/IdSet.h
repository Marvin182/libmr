#ifndef MR_ID_SET_H
#define MR_ID_SET_H

#include <vector>
#include "BoolFlags.h"

namespace mr {
namespace algo {

template <bool fastRemove = false>
class IdSet {
public:
	typedef std::vector<int>::const_iterator const_iterator;

	IdSet(int n);

	void clear();

	int size() const { return ids.size(); }

	bool contains(int id);
	void insert(int id);
	void remove(int id);

	const_iterator begin() const { return ids.begin(); }
	const_iterator end() const { return ids.end(); };

private:
	std::vector<bool> contained;
	std::vector<int> ids;
	std::vector<int> idToPos;

	void removeAll();
};

} // namespace algo
} // namespace mr

#endif /* MR_ID_SET_H */

