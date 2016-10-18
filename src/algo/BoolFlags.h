#ifndef MR_BOOL_FLAGS_H
#define MR_BOOL_FLAGS_H

#include <vector>
#include <cassert>
#include <algorithm>

namespace mr {
namespace algo {

template <typename Underlying = int>
class BoolFlags {
private:
	std::vector<Underlying> timestamps;
	Underlying currentTimestamp;

public:
	struct FlagReference {
	private:
		Underlying* val;
		Underlying* valTrue;

		void setTrue() { *val = *valTrue; }
		void setFalse() { *val = (*valTrue) - 1; }

	public:
		FlagReference(Underlying* val, Underlying* valTrue):
			val(val),
			valTrue(valTrue)
		{}

		FlagReference():
			val(0),
			valTrue(0)
		{}

		operator bool() const { return *val == *valTrue; }

		FlagReference& operator=(bool x) {
			if (x)
				setTrue();
			else
				setFalse();
			return *this;
		}

		FlagReference& operator=(const FlagReference& x) {
			return *this = bool(x);
		}

		bool operator==(const FlagReference& x) const {
			return bool(*this) == bool(x);
		}

		bool operator<(const FlagReference& x) const {
			return !bool(*this) && bool(x);
		}

		void flip() {
			if (*val == *valTrue)
				setFalse();
			else
				setTrue();
		}
	};

	BoolFlags(size_t size):
		timestamps(size, 0),
		currentTimestamp(1)
	{}

	void assign(size_t size, bool value) {
		currentTimestamp = 1;
		timestamps.assign(size, value ? currentTimestamp : currentTimestamp - 1);
	}

	size_t size() const { return timestamps.size(); }

	FlagReference operator[](size_t pos) {
		assert(pos < size());
		return FlagReference(&timestamps[pos], &currentTimestamp);
	}

	bool operator[](size_t pos) const {
		assert(pos < size());
		return timestamps[pos] == currentTimestamp;
	}

	bool isSet(size_t pos) const {
		assert(pos < size());
		return timestamps[pos] == currentTimestamp;
	}

	void set(size_t pos) {
		assert(pos < size());
		timestamps[pos] = currentTimestamp;
	}

	void unset(size_t pos) {
		assert(pos < size());
		timestamps[pos] = currentTimestamp - 1;
	}

	void unsetAll() {
		currentTimestamp++;
	}
};

template <>
class BoolFlags<bool> : public std::vector<bool> {
public:
	BoolFlags(size_t size):
		std::vector<bool>(size)
	{}

	bool isSet(size_t pos) const {
		assert(pos < size());
		return (*this)[pos];
	}

	void set(size_t pos) {
		assert(pos < size());
		(*this)[pos] = true;
	}

	void unset(size_t pos) {
		assert(pos < size());
		(*this)[pos] = false;
	}

	void unsetAll() {
		std::fill(this->begin(), this->end(), false);
	}
};

} // namespace algo
} // namespace mr

#endif /* MR_BOOL_FLAGS_H */