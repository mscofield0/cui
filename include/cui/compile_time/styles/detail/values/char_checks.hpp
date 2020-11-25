#ifndef CUI_CT_STYLES_CHAR_CHECKS_HPP
#define CUI_CT_STYLES_CHAR_CHECKS_HPP

#include <compile_time/string/string_view.hpp>

namespace cui::ct::styles::detail {

constexpr bool is_minus(char ch) {
	return ch == '-';
}

constexpr bool is_whitespace(char ch) {
	return ch == 9 || ch == 10 || ch == 11 || ch == 12 || ch == 13 || ch == 32;
}

constexpr bool is_digit(char ch) {
	return (ch >= '0' && ch <= '9');
}

constexpr bool is_point(char ch) {
	return (ch == '.' || ch == ',');
}

constexpr bool is_percent(char ch) {
	return ch == '%';
}

constexpr bool is_open_parenthesis(char ch) {
	return ch == '(';
}

constexpr bool is_closed_parenthesis(char ch) {
	return ch == ')';
}

constexpr bool is_colon(char ch) {
	return ch == ',';
}

constexpr bool is_valid_char(char ch) {
	constexpr StringView valid_chars{"abcdefghijklmnopqrstuvwxyz_"};
	for (auto el : valid_chars) {
		if (el == ch) return true;
	}
	return false;
}

}	 // namespace cui::ct::styles::detail

#endif	  // CUI_CT_STYLES_CHAR_CHECKS_HPP