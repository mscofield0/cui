#ifndef CUI_CT_FMT_FORMAT_HPP
#define CUI_CT_FMT_FORMAT_HPP

#include <array>
#include <exception>
#include <limits>

#include <aliases.hpp>
#include <compile_time/format/detail/log10.hpp>
#include <compile_time/format/detail/pow.hpp>
#include <utils/abs.hpp>

namespace cui::ct {

template <std::size_t Size>
class Format
{
public:
	using size_type = std::size_t;
	using data_type = std::array<char, Size>;
	using value_type = char;
	using reference = data_type&;
	using const_reference = const data_type&;
	using iterator = typename data_type::iterator;
	using const_iterator = typename data_type::const_iterator;

	constexpr Format() : data_{}, pos_{0} {}

	constexpr auto size() const noexcept -> size_type {
		return pos_;
	}

	constexpr auto max_size() const noexcept -> size_type {
		return Size;
	}

	constexpr auto data() noexcept -> reference {
		return data_;
	}

	constexpr auto data() const noexcept -> const_reference {
		return data_;
	}

	constexpr auto get_str() const noexcept -> const_iterator {
		return data_.data();
	}

	constexpr void append(const value_type& el) {
		if (size() == max_size()) throw std::length_error{"Exceeded maximum size"};
		data_[pos_++] = el;
	}

	constexpr auto operator<<(i64 x) -> Format<Size>& {
		const auto minus = x < 0 ? true : false;
		x = cui::abs(x);
		auto digits = cui::ct::log10(x) + 1;
		if (minus) append('-');
		do {
			const u16 digit = x / cui::ct::pow(10, digits - 1);
			const auto div = static_cast<u64>(cui::ct::pow(10, --digits));
			x %= div;
			append(digit + '0');
		} while (digits > 0);

		return (*this);
	}

	constexpr auto operator<<(u64 x) -> Format<Size>& {
		auto digits = cui::ct::log10(x) + 1;
		do {
			const u16 digit = x / cui::ct::pow(10, digits - 1);
			const auto div = static_cast<u64>(cui::ct::pow(10, --digits));
			x %= div;
			append(digit + '0');
		} while (digits > 0);

		return (*this);
	}

	template <std::size_t N>
	constexpr auto operator<<(const char (&s)[N]) -> Format<Size>& {
		std::size_t i = 0;
		while (i < N - 1) {
			append(s[i++]);
		}

		return (*this);
	}

private:
	std::array<char, Size> data_;
	size_type pos_;
};

}	 // namespace cui::ct

#endif	  // CUI_CT_FMT_FORMAT_HPP