#ifndef CUI_CT_STYLES_LOOKUP_STRING_HPP
#define CUI_CT_STYLES_LOOKUP_STRING_HPP

#include <compile_time/string/string_view.hpp>
#include <compile_time/styles/detail/constants.hpp>
#include <compile_time/value_data.hpp>

namespace cui::ct::styles::detail {

constexpr auto lookup_string(const StringView str) -> ValueData {
	for (std::size_t i = 0; i < string_names.size(); ++i) {
		if (string_names[i] == str) {
			return string_values[i];
		}
	}
	return ValueData{};
}

}	 // namespace cui::ct::styles::detail

#endif	  // CUI_CT_STYLES_LOOKUP_STRING_HPP