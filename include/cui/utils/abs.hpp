#ifndef CUI_ABS_HPP
#define CUI_ABS_HPP

namespace cui {

/// \brief Applies operator- to the value
/// \details Overflow if value == INT_MIN
/// \tparam T The type that is being negated
/// \param x Value to negate
/// \returns The negated value
template <typename T>
constexpr T abs(const T& x) noexcept {
	return x < 0 ? -x : x;
}

}	 // namespace cui

#endif	  // CUI_ABS_HPP