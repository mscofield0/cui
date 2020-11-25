#ifndef CUI_CT_STYLES_IS_CORRECT_VALUE_FOR_ATTR_TYPE_HPP
#define CUI_CT_STYLES_IS_CORRECT_VALUE_FOR_ATTR_TYPE_HPP

#include <compile_time/string/string_view.hpp>
#include <compile_time/styles/detail/constants.hpp>
#include <compile_time/styles/detail/values/dt_to_vat.hpp>

namespace cui::ct::styles::detail {

constexpr bool is_correct_value_for_attr_type(const StringView type, const ValueData& value) {
	constexpr auto size = attribute_types.size();
	auto idx = size;

	for (std::size_t i = 0; i < attribute_names.size(); ++i) {
		if (type == attribute_names[i]) {
			idx = i;
			break;
		}
	}

	if (idx == size) return false;
	auto valid_value_types = attribute_types[idx];

	return valid_value_types & dt_to_vat(value.active());
}

}	 // namespace cui::ct::styles::detail

#endif	  // CUI_CT_STYLES_IS_CORRECT_VALUE_FOR_ATTR_TYPE_HPP
