#ifndef CUI_CT_MEMMOVE_HPP
#define CUI_CT_MEMMOVE_HPP

#include <cstdint>

namespace cui {

template <typename T>
constexpr void memmove(T* dest, const T* src, std::size_t length) {
	std::size_t i = 0;
	while (i++ < length) *dest++ = *src++;
}

}	 // namespace cui

#endif	  // CUI_CT_MEMMOVE_HPP