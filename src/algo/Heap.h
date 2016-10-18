#ifndef MR_HEAP_H
#define MR_HEAP_H

#include <cassert>
#include <vector>
#include <functional>
#include "BoolFlags.h"

namespace mr {
namespace algo {

template <typename KeyType, typename KeyOrderType, typename BoolFlagsType, int K>
class Heap {
private:
	typedef int node;
	typedef int index;
	typedef int count;

	struct NodeKeyPair {
		node nodeId;
		KeyType key;
	};

	count n;
	count heapEnd;
	std::vector<NodeKeyPair> heap;
	std::vector<index> nodePos;
	BoolFlagsType nodeContained;
	KeyOrderType order;

	bool checkInvariants() const {
		// nodes
		for (index i = 0; i < heapEnd; i++) {
			assert(heap[i].nodeId < n);
			assert(nodePos[heap[i].nodeId] == i);
		}

		for (node i = 0; i < n; i++) {
			if (contains(i)) {
				assert(heap[nodePos[i]].nodeId == i);
			}
		}

		// order
		for (index i = 1; i < heapEnd; i++) {
			assert(!order(heap[i].key, heap[parent(i)].key));
		}

		return true;
	}

	index parent(index pos) const {
		assert(pos != 0);
		assert(pos < n);
		return (pos - 1) / K;
	}

	index childrenBegin(index pos) const {
		assert(pos < n);
		return std::min(heapEnd, K * pos + 1);
	}

	index childrenEnd(index pos) const {
		assert(pos < n);
		return std::min(heapEnd, K * (pos + 1) + 1);
	}

	void rebuild() {
		for (index i = heapEnd - 1; i >= 0; i--) {
			moveDown(i);
		}
	}

	void moveUp(index pos) {
		assert(pos < n);
		if (pos == 0) {
			// already at the root
			return;
		}

		// copy entry
		auto v = heap[pos].nodeId;
		auto key = std::move(heap[pos].key);

		auto parentPos = parent(pos);
		while (order(key, heap[parentPos].key)) {
			heap[pos].nodeId = heap[parentPos].nodeId;
			heap[pos].key = std::move(heap[parentPos].key);
			nodePos[heap[parentPos].nodeId] = pos;

			pos = parentPos;
			if (pos == 0) {
				// reached root
				break;
			} else {
				parentPos = parent(pos);
			}
		}

		// save entry at new position
		heap[pos].nodeId = v;
		heap[pos].key = key;
		nodePos[v] = pos;
	}

	void moveDown(index pos) {
		assert(pos < n);

		// copy entry
		auto key = std::move(heap[pos].key);
		auto v = heap[pos].nodeId;

		while (1) {
			auto begin = childrenBegin(pos);
			auto end = childrenEnd(pos);

			if (begin == end) {
				// no children
				break;
			}

			// find smallest child
			auto minChildPos = begin;
			for (index i = begin + 1; i < end; i++) {
				if (order(heap[i].key, heap[minChildPos].key)) {
					minChildPos = i;
				}
			}

			if (!order(heap[minChildPos].key, key)) {
				// done
				break;
			}

			heap[pos].nodeId = heap[minChildPos].nodeId;
			heap[pos].key = std::move(heap[minChildPos].key);
			nodePos[heap[minChildPos].nodeId] = pos;

			pos = minChildPos;
		}

		// save entry at new position
		heap[pos].nodeId = v;
		heap[pos].key = std::move(key);
		nodePos[v] = pos;
	}

public:
	typedef KeyType key_type;
	typedef KeyOrderType key_order_type;

	Heap(count n):
		n(n),
		heapEnd(0),
		heap(n),
		nodePos(n),
		nodeContained(n)
	{}

	void reset(count n) {
		this->n = n;
		heap.resize(n);
		nodePos.resize(n);
		nodeContained.assign(n, false);

		clear();

		assert(heapEnd == 0);
		for (auto v = n - 1; v >= 0; v--) {
			assert(!contains(v));
		}
		assert(checkInvariants());
	}

	void clear() {
		heapEnd = 0;
		nodeContained.unsetAll();
		assert(checkInvariants());
	}

	bool contains(node v) const {
		assert(v < n);
		return nodeContained.isSet(v);
	}

	count size() const { return heapEnd; }

	node upperNodeIdBound() const { return n; }

	bool empty() const { return heapEnd == 0; }

	void push(node v, KeyType key) {
		assert(v < n);
		assert(!contains(v) && "can't push an already existing id");
		
		index newPos = heapEnd;
		heapEnd++;
		heap[newPos].nodeId = v;
		heap[newPos].key = std::move(key);
		nodePos[v] = newPos;
		nodeContained.set(v);
		moveUp(newPos);

		assert(checkInvariants());
	}

	bool pushOrImprove(node v, KeyType key) {
		assert(v <= n);

		if (contains(v)) {
			auto pos = nodePos[v];
			if (order(key, heap[pos].key)) {
				heap[pos].key = std::move(key);
				moveUp(pos);
				assert(checkInvariants());
				return false;
			}
		} else {
			push(v, key);
			assert(contains(v));
			return true;
		}

		// not pushed and not increased
		assert(false && "use pushOrSet");
		return false;
	}

	bool pushOrWorsen(node v, KeyType key) {
		assert(v <= n);

		if (contains(v)) {
			auto pos = nodePos[v];
			if (order(heap[pos].key, key)) {
				heap[pos].key = std::move(key);
				moveDown(pos);
				assert(checkInvariants());
				return false;
			}
		} else {
			push(v, key);
			assert(contains(v));
			return true;
		}

		// not pushed and not decreased
		assert(false && "use pushOrSet");
		return false;
	}

	bool pushOrSet(node v, KeyType key) {
		assert(v <= n);

		if (contains(v)) {
			int pos = nodePos[v];
			bool improve = order(key, heap[pos].key);
			heap[pos].key = std::move(key);
			if (improve) {
				moveUp(pos);
			} else {
				moveDown(pos);
			}
			assert(checkInvariants());
			return false;
		} else {
			push(v, key);
			assert(contains(v));
			return true;
		}

		assert(false && "code should be unreachable");
		return false;
	}

	node top() const {
		assert(!empty());
		assert(contains(heap[0].nodeId));
		return heap[0].nodeId;
	}

	KeyType topKey() const {
		assert(!empty());
		assert(contains(heap[0].nodeId));
		return heap[0].key;
	}

	node pop() {
		assert(!empty() && "heap is empty");
		assert(checkInvariants());

		// remove root
		node v = heap[0].nodeId;
		nodeContained.unset(heap[0].nodeId);
		heapEnd--;

		if (heapEnd > 0) {
			// maintain heap by putting the last element to the top and move it down
			heap[0].nodeId = heap[heapEnd].nodeId;
			heap[0].key = std::move(heap[heapEnd].key);
			nodePos[heap[0].nodeId] = 0;
			moveDown(0);
		}

		assert(checkInvariants());
		return v;
	}
};

template <typename KeyType, typename BoolFlagsType = BoolFlags<int>, int K = 4>
using MinHeap = Heap<KeyType, std::less<KeyType>, BoolFlagsType, K>;
template <typename KeyType, typename BoolFlagsType = BoolFlags<int>, int K = 4>
using MaxHeap = Heap<KeyType, std::greater<KeyType>, BoolFlagsType, K>;

} // namespace algo
} // namespace mr

#endif /* MR_HEAP_H */