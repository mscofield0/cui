#ifndef CUI_CT_STYLES_PARSE_URL_HPP
#define CUI_CT_STYLES_PARSE_URL_HPP

#include <compile_time/string/string_view.hpp>
#include <compile_time/value_data.hpp>

namespace cui::ct::styles::detail {

constexpr auto parse_url(const StringView str) -> ValueData {
	const auto open_parenthesis_idx = str.find_first_of('(');
	if (open_parenthesis_idx == StringView::npos) return {};
	auto fn_name = str.substr(0, open_parenthesis_idx);
	if (fn_name.compare("url") != 0) return {};
	const auto closed_parenthesis_idx = str.find_last_of(')');
	if (closed_parenthesis_idx == StringView::npos) return {};

	return str.substr(open_parenthesis_idx + 1, closed_parenthesis_idx - open_parenthesis_idx - 1);
}

}	 // namespace cui::ct::styles::detail

#endif	  // CUI_CT_STYLES_PARSE_URL_HPP