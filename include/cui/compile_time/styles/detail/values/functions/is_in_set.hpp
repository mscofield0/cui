#ifndef CUI_CT_STYLES_FUNCTIONS_IS_IN_SET_HPP
#define CUI_CT_STYLES_FUNCTIONS_IS_IN_SET_HPP

#include <initializer_list>

namespace cui::ct::styles::detail {

template <typename T1, typename T2>
constexpr bool is_in_set(const T1& val, const std::initializer_list<T2>& ilist) {
	for (const auto& el : ilist) {
		if (val != static_cast<T1>(el)) return false;
	}
	return true;
}

}	 // namespace cui::ct::styles::detail

#endif	  // CUI_CT_STYLES_FUNCTIONS_IS_IN_SET_HPP