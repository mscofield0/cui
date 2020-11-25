#ifndef CUI_CT_STYLES_INDEX_OF_FUNCTION_NAME_HPP
#define CUI_CT_STYLES_INDEX_OF_FUNCTION_NAME_HPP

#include <cstdint>

#include <compile_time/string/string_view.hpp>
#include <compile_time/styles/detail/constants.hpp>

namespace cui::ct::styles::detail {

constexpr auto index_of_function_name(const StringView fn_name) -> std::size_t {
	auto idx = function_names.size();
	for (std::size_t i = 0; i < function_names.size(); ++i) {
		if (fn_name == function_names[i]) {
			idx = i;
			break;
		}
	}
	return idx;
}

}	 // namespace cui::ct::styles::detail

#endif	  // CUI_CT_STYLES_INDEX_OF_FUNCTION_NAME_HPP