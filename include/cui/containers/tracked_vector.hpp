#ifndef CUI_TRACKED_VECTOR_HPP
#define CUI_TRACKED_VECTOR_HPP

#include <exception>
#include <initializer_list>
#include <vector>

namespace cui {

template <typename T>
class TrackedVector : public std::vector<T>
{
public:
	using base_t = std::vector<T>;
	using value_type = typename base_t::value_type;
	using size_type = typename base_t::size_type;
	using difference_type = typename base_t::difference_type;
	using reference = typename base_t::reference;
	using const_reference = typename base_t::const_reference;
	using pointer = typename base_t::pointer;
	using const_pointer = typename base_t::const_pointer;
	using iterator = typename base_t::iterator;
	using const_iterator = typename base_t::const_iterator;

	TrackedVector() : base_t{}, tracker_{0} {}
	TrackedVector(size_type count, const_reference value = value_type()) : base_t(count, value), tracker_{0} {}
	template <typename InputIt>
	explicit TrackedVector(size_type p_tracker, InputIt first, InputIt last) : base_t(first, last), tracker_{p_tracker} {}
	TrackedVector(size_type p_tracker, std::initializer_list<T> init) : base_t(init), tracker_{p_tracker} {}
	TrackedVector(size_type p_tracker, size_type count, const_reference value = value_type()) : base_t(count, value), tracker_{p_tracker} {}
	template <typename... Args>
	TrackedVector(Args&&... args) : base_t{std::forward<Args>(args)...}, tracker_{0} {}

	reference current_item() noexcept {
		return base_t::operator[](tracker_);
	}

	const_reference current_item() const noexcept {
		return base_t::operator[](tracker_);
	}

	void change_tracked_item(size_type idx) {
		if (idx >= this->size()) throw std::length_error("Index larger than size()");
		tracker_ = idx;
	}

protected:
	size_type tracker_;
};

}	 // namespace cui

#endif	  // CUI_GLOBAL_TRACKED_VECTOR_HPP