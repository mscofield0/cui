#ifndef CUI_STATIC_STACK_HPP
#define CUI_STATIC_STACK_HPP

#include <cstdint>

#include <containers/static_vector.hpp>

namespace cui {

template <typename T, std::size_t MaxSize>
class StaticStack
{
public:
	using value_type = T;
	using size_type = std::size_t;
	using reference = value_type&;
	using const_reference = const value_type&;

	constexpr StaticStack() : data_{} {}

	[[nodiscard]] constexpr auto size() const noexcept -> size_type {
		return data_.size();
	}

	[[nodiscard]] constexpr auto max_size() const noexcept -> size_type {
		return data_.max_size();
	}

	[[nodiscard]] constexpr auto top() noexcept -> reference {
		return data_.back();
	}

	[[nodiscard]] constexpr auto top() const noexcept -> const_reference {
		return data_.back();
	}

	constexpr void push(const_reference item) {
		data_.push_back(item);
	}

	constexpr auto pop() -> value_type {
		const auto t = data_.back();
		data_.pop_back();
		return t;
	}

	constexpr void clear() noexcept {
		data_.clear();
	}

	[[nodiscard]] constexpr bool empty() const noexcept {
		return size() == 0;
	}

private:
	StaticVector<T, MaxSize> data_;
};

}	 // namespace cui

#endif	  // CUI_STATIC_STACK_HPP