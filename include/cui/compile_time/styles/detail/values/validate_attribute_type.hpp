#ifndef CUI_CT_STYLES_VALIDATE_ATTRIBUTE_TYPE_HPP
#define CUI_CT_STYLES_VALIDATE_ATTRIBUTE_TYPE_HPP

#include <compile_time/styles/detail/constants.hpp>
#include <compile_time/string/string_view.hpp>

namespace cui::ct::styles::detail {

constexpr bool validate_attribute_type(const StringView p_type) {
	for (const auto type : attribute_names) {
		if (type == p_type) return true;
	}
	return false;
}

}	 // namespace cui::ct::styles::detail

#endif	  // CUI_CT_STYLES_VALIDATE_ATTRIBUTE_TYPE_HPP