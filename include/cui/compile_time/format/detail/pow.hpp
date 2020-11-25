#ifndef CUI_CT_FMT_POW_HPP
#define CUI_CT_FMT_POW_HPP

#include <type_traits>

#include <aliases.hpp>

namespace cui::ct {

template <typename Type, std::enable_if_t<std::is_arithmetic_v<Type>>* = nullptr>
constexpr auto pow(Type v, int pot) -> float {
	if (pot == 0) return 1.f;
	if (pot == 1) return static_cast<float>(v);
	if (pot < 0) {
		float res = 1.f / v;
		for (int i = 1; i < pot; ++i) {
			res /= v;
		}
		return res;
	}
	float res = static_cast<float>(v);
	for (int i = 1; i < pot; ++i) {
		res *= v;
	}
	return res;
}

}	 // namespace cui::ct

#endif	  // CUI_CT_FMT_POW_HPP