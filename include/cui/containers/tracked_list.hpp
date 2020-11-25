#ifndef CUI_TRACKED_LIST_HPP
#define CUI_TRACKED_LIST_HPP

#include <exception>
#include <initializer_list>
#include <list>

namespace cui {

/// \brief A \sa std::list wrapper that tracks the active element
template <typename T>
class TrackedList : public std::list<T>
{
public:
	using base_t = std::list<T>;
	using value_type = typename base_t::value_type;
	using size_type = typename base_t::size_type;
	using difference_type = typename base_t::difference_type;
	using reference = typename base_t::reference;
	using const_reference = typename base_t::const_reference;
	using pointer = typename base_t::pointer;
	using const_pointer = typename base_t::const_pointer;
	using iterator = typename base_t::iterator;
	using const_iterator = typename base_t::const_iterator;

	TrackedList() : base_t{}, tracker_(0) {}
	TrackedList(size_type count, const_reference value = value_type()) : base_t(count, value), tracker_(0) {}
	template <typename InputIt>
	explicit TrackedList(size_type p_tracker, InputIt first, InputIt last) : base_t(first, last), tracker_(p_tracker) {}
	TrackedList(size_type p_tracker, std::initializer_list<T> init) : base_t(init), tracker_(p_tracker) {}
	TrackedList(size_type p_tracker, size_type count, const_reference value = value_type()) : base_t(count, value), tracker_(p_tracker) {}
	template <typename... Args>
	TrackedList(Args&&... args) : base_t{std::forward<Args>(args)...}, tracker_(0) {}

	[[nodiscard]] auto current_item() noexcept -> reference {
		auto it = base_t::begin();
		size_type i = 0;
		while (it != base_t::end() && i++ < tracker_) ++it;
		return *it;
	}

	[[nodiscard]] auto current_item() const noexcept -> const_reference {
		auto it = base_t::begin();
		size_type i = 0;
		while (it != base_t::end() && i++ < tracker_) ++it;
		return *it;
	}

	void change_tracked_item(size_type idx) {
		if (idx >= this->size()) throw cui::ct::CTException("Index exceeds current size! | Index: {}, Size: {}", idx, this->size());
		tracker_ = idx;
	}

private:
	size_type tracker_;
};

}	 // namespace cui

#endif	  // CUI_TRACKED_LIST_HPP