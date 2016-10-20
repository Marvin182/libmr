#include <stdexcept>

class const_string {
public:
	template<std::size_t N>
	constexpr const_string(const char(&s)[N]):
		p(s),
		len(N - 1)
	{}
 
	constexpr char operator[](std::size_t idx) const {
		return idx < len ? p[idx] : throw std::out_of_range("");
	}

	constexpr std::size_t size() const { return len; }

	constexpr const char* c_str() const { return p; }

	constexpr operator const char*() const { return p; }

private:
	const char* p;
	const std::size_t len;
};
