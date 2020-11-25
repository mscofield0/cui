#ifndef CUI_CT_STYLES_GET_ATTRIBUTE_INDEX_HPP
#define CUI_CT_STYLES_GET_ATTRIBUTE_INDEX_HPP

#include <cstdint>

#include <compile_time/string/string_view.hpp>
#include <compile_time/styles/detail/constants.hpp>

namespace cui::ct::styles::detail {

constexpr auto get_attribute_index(const StringView name) -> std::size_t {
	std::size_t i = 0;
	for (; i < attribute_names.size(); ++i) {
		if (name == attribute_names[i]) {
			break;
		}
	}
	return i;
}

}	 // namespace cui::ct::styles::detail

#endif	  // CUI_CT_STYLES_GET_ATTRIBUTE_INDEX_HPP