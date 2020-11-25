#ifndef CUI_DATA_TYPES_VEC_HPP
#define CUI_DATA_TYPES_VEC_HPP

#include <array>

namespace cui {

template <typename T, std::size_t N>
using Vec = std::array<T, N>;

using Vec2f = Vec<float, 2>;
using Vec3f = Vec<float, 3>;
using Vec4f = Vec<float, 4>;

using Vec2i = Vec<int, 2>;
using Vec3i = Vec<int, 3>;
using Vec4i = Vec<int, 4>;

}	 // namespace cui

#endif	  // CUI_DATA_TYPES_VEC_HPP