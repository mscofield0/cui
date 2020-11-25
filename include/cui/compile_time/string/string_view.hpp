#ifndef CUI_STRING_VIEW_HPP
#define CUI_STRING_VIEW_HPP

#include <type_traits>
#include <iterator>
#include <exception>
#include <limits>

#include <compile_time/string/char_traits.hpp>
#include <aliases.hpp>

namespace cui::ct {

template <typename CharT, typename Traits = BasicCharTraits<CharT>>
class BasicStringView
{
	static_assert(!std::is_array_v<CharT>);
	static_assert(std::is_trivial_v<CharT> && std::is_standard_layout_v<CharT>);
	static_assert(std::is_same_v<CharT, typename Traits::char_type>);

public:
	using traits_type = Traits;
	using value_type = CharT;
	using pointer = value_type*;
	using const_pointer = const value_type*;
	using reference = value_type&;
	using const_reference = const value_type&;
	using const_iterator = const value_type*;
	using iterator = const_iterator;
	using const_reverse_iterator = std::reverse_iterator<const_iterator>;
	using reverse_iterator = const_reverse_iterator;
	using size_type = u64;
	using difference_type = i64;

	static constexpr size_type npos = size_type(-1);

	constexpr BasicStringView() : length_{0}, str_{nullptr} {}
	template <size_type N>
	constexpr BasicStringView(const value_type (&str)[N]) : length_{N}, str_{str} {}
	constexpr BasicStringView(const_pointer str) : length_{Traits::length(str)}, str_{str} {}
	constexpr BasicStringView(const_pointer str, size_type length) : length_{length}, str_{str} {}

	[[nodiscard]] constexpr auto begin() const noexcept -> const_iterator {
		return str_;
	}

	[[nodiscard]] constexpr auto end() const noexcept -> const_iterator {
		return str_ + length_;
	}

	[[nodiscard]] constexpr auto cbegin() const noexcept -> const_iterator {
		return str_;
	}

	[[nodiscard]] constexpr auto cend() const noexcept -> const_iterator {
		return str_ + length_;
	}

	[[nodiscard]] constexpr auto rbegin() const noexcept -> const_reverse_iterator {
		return const_reverse_iterator(end());
	}

	[[nodiscard]] constexpr auto rend() const noexcept -> const_reverse_iterator {
		return const_reverse_iterator(begin());
	}

	[[nodiscard]] constexpr auto crbegin() const noexcept -> const_reverse_iterator {
		return rbegin();
	}

	[[nodiscard]] constexpr auto crend() const noexcept -> const_reverse_iterator {
		return rend();
	}

	[[nodiscard]] constexpr auto size() const noexcept -> size_type {
		return length_;
	}

	[[nodiscard]] constexpr auto max_size() const noexcept -> size_type {
		return (npos - sizeof(size_type) - sizeof(void*)) / (sizeof(value_type) * 4);
	}

	[[nodiscard]] constexpr bool empty() const noexcept {
		return length_ == 0;
	}

	[[nodiscard]] constexpr auto operator[](size_type pos) const noexcept -> const_reference {
		return *(str_ + pos);
	}

	[[nodiscard]] constexpr auto at(size_type pos) const -> const_reference {
		if (pos >= length_) throw std::length_error("Out of range");
		return *(str_ + pos);
	}

	[[nodiscard]] constexpr auto front() const noexcept -> const_reference {
		return *str_;
	}

	[[nodiscard]] constexpr auto back() const noexcept -> const_reference {
		return *(str_ + length_ - 1);
	}

	[[nodiscard]] constexpr auto data() const noexcept -> const_pointer {
		return str_;
	}

	constexpr void remove_prefix(size_type n) {
		if (length_ == 0) return;
		if (n > length_) throw std::length_error("Out of range");
		str_ += n;
		length_ -= n;
	}

	constexpr void remove_suffix(size_type n) {
		if (length_ == 0) return;
		if (n > length_) throw std::length_error("Out of range");
		length_ -= n;
	}

	constexpr void swap(BasicStringView& sv) noexcept {
		auto tmp = *this;
		*this = sv;
		sv = tmp;
	}

	constexpr auto copy(pointer str, size_type n, size_type pos = 0) const -> size_type {
		if (traits_type::length(str) == n) throw std::length_error("String length and the value of n must be equal.");
		pos = pos <= n ? pos : throw std::length_error("Out of range");
		const size_type rlen = std::min(n, length_ - pos);

		traits_type::copy(str, data() + pos, rlen);
		return rlen;
	}

	constexpr auto substr(size_type pos = 0, size_type n = npos) const -> BasicStringView {
		pos = size() > pos ? pos : throw std::length_error("Out of range");
		const size_type rlen = std::min(n, length_ - pos);
		return BasicStringView{str_ + pos, rlen};
	}

	constexpr auto compare(BasicStringView str) const noexcept -> i32 {
		const size_type rlen = std::min(length_, str.length_);
		int ret = traits_type::compare(str_, str.str_, rlen);
		if (ret == 0) {
			ret = length_compare(length_, str.length_);
		}
		return ret;
	}

	constexpr auto compare(size_type pos1, size_type n1, BasicStringView str) const noexcept -> i32 {
		return substr(pos1, n1).compare(str);
	}

	constexpr auto
	compare(size_type pos1, size_type n1, BasicStringView str, size_type pos2, size_type n2) const noexcept -> i32 {
		return substr(pos1, n1).compare(str.substr(pos2, n2));
	}

	constexpr auto compare(const_pointer str) const noexcept -> i32 {
		return compare(BasicStringView{str});
	}

	constexpr auto compare(size_type pos1, size_type n1, const_pointer str) const noexcept -> i32 {
		return substr(pos1, n1).compare(BasicStringView{str});
	}

	constexpr auto compare(size_type pos1, size_type n1, const_pointer str, size_type n2) const noexcept -> i32 {
		return substr(pos1, n1).compare(BasicStringView{str, n2});
	}

	constexpr bool starts_with(BasicStringView str) const noexcept {
		return substr(0, str.size()) == str;
	}

	constexpr bool starts_with(value_type x) const noexcept {
		return !empty() && traits_type::eq(front(), x);
	}

	constexpr bool starts_with(const_pointer str) const noexcept {
		return starts_with(BasicStringView{str});
	}

	constexpr bool ends_with(BasicStringView str) const noexcept {
		return size() >= str.size() && compare(size() - str.size(), npos, str) == 0;
	}

	constexpr bool ends_with(value_type x) const noexcept {
		return !empty() && traits_type::eq(back(), x);
	}

	constexpr bool ends_with(const_pointer str) const noexcept {
		return ends_with(BasicStringView{str});
	}

	// find

	constexpr auto find(const_pointer str, size_type pos, size_type n) const -> size_type {
		if (traits_type::length(str) != n) throw std::length_error("String length and the value of n must be equal.");
		if (n == 0) {
			return pos <= length_ ? pos : npos;
		}

		if (n <= length_) {
			for (; pos <= length_ - n; ++pos) {
				if (traits_type::eq(str_[pos], str[0]) && traits_type::compare(str_ + pos + 1, str + 1, n - 1) == 0) {
					return pos;
				}
			}
		}
		return npos;
	}

	constexpr auto find(BasicStringView str, size_type pos = 0) const -> size_type {
		return find(str.str_, pos, str.length_);
	}

	constexpr auto find(value_type c, size_type pos = 0) const noexcept -> size_type {
		size_type ret = npos;
		if (pos < length_) {
			const size_type n = length_ - pos;
			const value_type* p = traits_type::find(str_ + pos, n, c);
			if (p != nullptr) {
				ret = p - str_;
			}
		}
		return ret;
	}

	constexpr auto find(const_pointer str, size_type pos = 0) const noexcept -> size_type {
		return find(str, pos, traits_type::length(str));
	}

	// rfind

	constexpr auto rfind(const_pointer str, size_type pos, size_type n) const -> size_type {
		if (traits_type::length(str) != n) throw std::length_error("String length and the value of n must be equal.");

		if (n <= length_) {
			pos = std::min(size_type(length_ - n), pos);
			do {
				if (traits_type::compare(str_ + pos, str_, n) == 0) {
					return pos;
				}
			} while (pos-- > 0);
		}
		return npos;
	}

	constexpr auto rfind(BasicStringView str, size_type pos = npos) const -> size_type {
		return rfind(str.str_, pos, str.length_);
	}

	constexpr auto rfind(value_type c, size_type pos = npos) const noexcept -> size_type {
		size_type size = length_;
		if (size > 0) {
			if (--size > pos) size = pos;
			for (++size; size-- > 0;) {
				if (traits_type::eq(str_[size], c)) {
					return size;
				}
			}
		}
		return npos;
	}

	constexpr auto rfind(const_pointer str, size_type pos = npos) const noexcept -> size_type {
		return rfind(str, pos, traits_type::length(str));
	}

	// find_first_of

	constexpr auto find_first_of(const_pointer str, size_type pos, size_type n) const noexcept -> size_type {
		if (traits_type::length(str) != n) throw std::length_error("String length and the value of n must be equal.");

		for (; n && pos < length_; ++pos) {
			const_pointer p = traits_type::find(str, n, str_[pos]);
			if (p != nullptr) return pos;
		}
		return npos;
	}

	constexpr auto find_first_of(BasicStringView str, size_type pos = 0) const noexcept -> size_type {
		return find_first_of(str.str_, pos, str.length_);
	}

	constexpr auto find_first_of(value_type c, size_type pos = 0) const noexcept -> size_type {
		return find(c, pos);
	}

	constexpr auto find_first_of(const_pointer str, size_type pos = 0) const noexcept -> size_type {
		return find_first_of(str_, pos, traits_type::length(str));
	}

	// find_last_of

	constexpr auto find_last_of(const_pointer str, size_type pos, size_type n) const noexcept -> size_type {
		if (traits_type::length(str) != n) throw std::length_error("String length and the value of n must be equal.");

		size_type s = size();
		if (s != 0 && n != 0) {
			if (--s > pos) s = pos;
			do {
				if (traits_type::find(str, n, str_[s])) return s;
			} while (s-- != 0);
		}
		return npos;
	}

	constexpr auto find_last_of(BasicStringView str, size_type pos = npos) const noexcept -> size_type {
		return find_last_of(str.str_, pos, str.length_);
	}

	constexpr auto find_last_of(value_type c, size_type pos = npos) const noexcept -> size_type {
		return rfind(c, pos);
	}

	constexpr auto find_last_of(const_pointer str, size_type pos = npos) const noexcept -> size_type {
		return find_last_of(str_, pos, traits_type::length(str));
	}

	// find_first_not_of

	constexpr auto find_first_not_of(const_pointer str, size_type pos, size_type n) const noexcept -> size_type {
		if (traits_type::length(str) != n) throw std::length_error("String length and the value of n must be equal.");

		for (; pos < length_; ++pos) {
			if (!traits_type::find(str, n, str_[pos])) return pos;
		}
		return npos;
	}

	constexpr auto find_first_not_of(BasicStringView str, size_type pos = 0) const noexcept -> size_type {
		return find_first_not_of(str.str_, pos, str.length_);
	}

	constexpr auto find_first_not_of(value_type c, size_type pos = 0) const noexcept -> size_type {
		for (; pos < length_; ++pos) {
			if (!traits_type::eq(str_[pos], c)) return pos;
		}
		return npos;
	}

	constexpr auto find_first_not_of(const_pointer str, size_type pos = 0) const noexcept -> size_type {
		return find_first_not_of(str_, pos, traits_type::length(str));
	}

	// find_last_not_of

	constexpr auto find_last_not_of(const_pointer str, size_type pos, size_type n) const noexcept -> size_type {
		if (traits_type::length(str) != n) throw std::length_error("String length and the value of n must be equal.");

		size_type size = length_;
		if (size != 0) {
			if (--size > pos) size = pos;
			do {
				if (!traits_type::find(str, n, str_[size])) return size;
			} while (size-- != 0);
		}
		return npos;
	}

	constexpr auto find_last_not_of(BasicStringView str, size_type pos = npos) const noexcept -> size_type {
		return find_last_not_of(str.str_, pos, str.length_);
	}

	constexpr auto find_last_not_of(value_type c, size_type pos = npos) const noexcept -> size_type {
		size_type size = length_;
		if (size != 0) {
			if (--size > pos) size = pos;
			do {
				if (!traits_type::eq(str_[size], c)) return size;
			} while (size-- != 0);
		}
		return npos;
	}

	constexpr auto find_last_not_of(const_pointer str, size_type pos = npos) const noexcept -> size_type {
		return find_last_not_of(str_, pos, traits_type::length(str));
	}

	// trim

	constexpr auto find_end_of_whitespace() const noexcept -> size_type {
		auto it = begin();
		for (; it != end(); ++it) {
			const auto ch = *it;
			if (!(ch == 9 || ch == 10 || ch == 11 || ch == 12 || ch == 13 || ch == 32 || ch == 133 || ch == 160)) {
				break;
			}
		}
		return std::distance(begin(), it);
	}

	constexpr auto rfind_end_of_whitespace() const noexcept -> size_type {
		auto it = rbegin();
		for (; it != rend(); ++it) {
			const auto ch = *it;
			if (!(ch == 9 || ch == 10 || ch == 11 || ch == 12 || ch == 13 || ch == 32 || ch == 133 || ch == 160)) {
				break;
			}
		}
		return std::distance(rbegin(), it);
	}

	constexpr auto trim_left() noexcept -> BasicStringView {
		const auto left = find_end_of_whitespace();
		remove_prefix(left);
		return (*this);
	}

	constexpr auto trim_right() noexcept -> BasicStringView {
		const auto right = rfind_end_of_whitespace();
		remove_suffix(right);
		return (*this);
	}

	constexpr auto trim() noexcept -> BasicStringView {
		const auto left = find_end_of_whitespace();
		remove_prefix(left);
		const auto right = rfind_end_of_whitespace();
		remove_suffix(right);
		return (*this);
	}

	constexpr auto trim_left() const noexcept -> BasicStringView {
		BasicStringView str{(*this)};
		const auto left = str.find_end_of_whitespace();
		str.remove_prefix(left);
		return str;
	}

	constexpr auto trim_right() const noexcept -> BasicStringView {
		BasicStringView str{(*this)};
		const auto right = str.rfind_end_of_whitespace();
		str.remove_suffix(right);
		return str;
	}

	constexpr auto trim() const noexcept -> BasicStringView {
		BasicStringView str{(*this)};
		const auto left = str.find_end_of_whitespace();
		str.remove_prefix(left);
		const auto right = str.rfind_end_of_whitespace();
		str.remove_suffix(right);
		return str;
	}

private:
	static constexpr int length_compare(size_type n1, size_type n2) noexcept {
		const difference_type diff = n1 - n2;
		if (diff > std::numeric_limits<int>::max()) {
			return std::numeric_limits<int>::max();
		}
		if (diff < std::numeric_limits<int>::min()) {
			return std::numeric_limits<int>::min();
		}
		return static_cast<int>(diff);
	}

public:
	size_type length_;
	const_pointer str_;
};

// Free function operators

template <typename CharT, typename Traits>
constexpr bool operator==(BasicStringView<CharT, Traits> x, BasicStringView<CharT, Traits> y) noexcept {
	return x.size() == y.size() && x.compare(y) == 0;
}

template <typename CharT, typename Traits>
constexpr bool operator!=(BasicStringView<CharT, Traits> x, BasicStringView<CharT, Traits> y) noexcept {
	return !(x == y);
}

template <typename CharT, typename Traits>
constexpr bool operator<(BasicStringView<CharT, Traits> x, BasicStringView<CharT, Traits> y) noexcept {
	return x.compare(y) < 0;
}

template <typename CharT, typename Traits>
constexpr bool operator>(BasicStringView<CharT, Traits> x, BasicStringView<CharT, Traits> y) noexcept {
	return x.compare(y) > 0;
}

template <typename CharT, typename Traits>
constexpr bool operator<=(BasicStringView<CharT, Traits> x, BasicStringView<CharT, Traits> y) noexcept {
	return x.compare(y) <= 0;
}

template <typename CharT, typename Traits>
constexpr bool operator>=(BasicStringView<CharT, Traits> x, BasicStringView<CharT, Traits> y) noexcept {
	return x.compare(y) >= 0;
}

using StringView = BasicStringView<char>;

}	 // namespace cui::ct

#endif	  // CUI_STRING_VIEW_HPP