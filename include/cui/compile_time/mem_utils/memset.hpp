#ifndef CUI_CT_MEMSET_HPP
#define CUI_CT_MEMSET_HPP

#include <cstdint>

namespace cui {

template <typename T>
constexpr void memset(T* dest, T val, std::size_t length) {
	std::size_t i = 0;
	while (i++ < length) *dest++ = val;
}

}	 // namespace cui

#endif	  // CUI_CT_MEMSET_HPP