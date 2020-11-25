#ifndef CUI_MAKE_ARRAY_HPP
#define CUI_MAKE_ARRAY_HPP

#include <array>

namespace cui {

/// \brief Helper function to create an \sa std::array
/// \tparam T The explicit type to create
/// \tparam Args Template parameter pack with which to create the array
/// \param args Parameter pack with which to create the array
/// \returns The created \sa std::array
template <typename T, typename... Args>
constexpr auto make_array(const Args&... args) -> std::array<T, sizeof...(Args)> {
	return {args...};
}

/// \brief Helper function to create an \sa std::array
/// \tparam T The type to specify what the other types should be
/// \tparam Args Template parameter pack with which to create the array
/// \param arg The first element of the array
/// \param args Parameter pack with which to create the array
/// \returns The created \sa std::array
template <typename T, typename... Args>
constexpr auto make_array(const T& arg, const Args&... args) -> std::array<T, sizeof...(Args) + 1> {
	return {arg, args...};
}

}	 // namespace cui

#endif	  // CUI_MAKE_ARRAY_HPP