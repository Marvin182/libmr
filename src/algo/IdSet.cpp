#include "IdSet.h"

#include "../util/assert.h"

namespace mr {
namespace algo {

template <bool fastRemove>
IdSet<fastRemove>::IdSet(int n):
	contained(n),
	idToPos(fastRemove ? n : 0)
{
	assert_debug(n >= 0);
	assert_debug(n == (int) contained.size());
	ids.reserve(n);
}

template <bool fastRemove>
void IdSet<fastRemove>::clear() {
	removeAll();
	assert_debug(size() == 0);
	assert_debug(ids.capacity() >= (int) contained.size());
}

template <bool fastRemove>
bool IdSet<fastRemove>::contains(int id) {
	assert_debug(id >= 0 && id < (int) contained.size());
	return contained[id];
}

template <bool fastRemove>
void IdSet<fastRemove>::insert(int id) {
	assert_debug(id >= 0 && id < (int) contained.size());
	if (!contains(id)) {
		if (fastRemove) {
			idToPos[id] = ids.size();
		}
		ids.push_back(id);
	}
}

template <>
void IdSet<true>::remove(int id) {
	contained[id] = false;
	int pos = idToPos[id];
	ids[pos] = ids.back();
	idToPos[ids.back()] = pos;
	ids.pop_back();
}

template <>
void IdSet<false>::remove(int id) {
	assert_fatal(false, "Do not use IdSet<false>::remove() as it might be very slow");
	contained[id] = false;
	int pos = 0;
	while (ids[pos] != id) pos++;
	ids[pos] = ids.back();
	ids.pop_back();
}

template <bool fastRemove>
void IdSet<fastRemove>::removeAll() {
	for (auto id : ids) {
		contained[id] = false;
	}
	ids.clear();
}

template class IdSet<true>;
template class IdSet<false>;

} // namespace algo
} // namespace mr