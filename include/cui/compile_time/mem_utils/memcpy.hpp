#ifndef CUI_CT_MEMCPY_HPP
#define CUI_CT_MEMCPY_HPP

#include <cstdint>

namespace cui {

template <typename T, typename R>
constexpr void memcpy(T* first, const T* last, R* result) {
	R* result_ = result;
	while (first < last) *result_++ = *first++;
}

template <typename T, typename R>
constexpr void memcpy_s(T* first, const T* last, R* result, std::size_t length) {
	R* result_ = result;
	std::size_t i = 0;
	while (i++ < length && first < last) *result_++ = *first++;
}

}	 // namespace cui

#endif	  // CUI_CT_MEMCPY_HPP