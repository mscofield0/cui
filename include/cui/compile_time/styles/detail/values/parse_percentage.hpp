#ifndef CUI_CT_STYLES_PARSE_PERCENTAGE_HPP
#define CUI_CT_STYLES_PARSE_PERCENTAGE_HPP

#include <compile_time/string/string_view.hpp>
#include <compile_time/styles/detail/values/pow.hpp>
#include <compile_time/value_data.hpp>

namespace cui::ct::styles::detail {

constexpr auto parse_percentage(const StringView str) -> ValueData {
	const bool minus = (str[0] == '-') ? true : false;
	const auto point_comma = str.find('.');
	const auto point_colon = str.find(',');
	auto point_idx = point_comma > point_colon ? point_colon : point_comma;
	point_idx = (point_idx == StringView::npos) ? str.size() - 1 : point_idx;
	float num = 0;
	for (std::size_t i = minus ? 1 : 0; i < point_idx; ++i) {
		const auto n = str[i] - '0';
		const auto size = point_idx;
		num += n * pow(10, size - i - 1);
	}
	if (point_idx == str.size() - 1) {
		return (num / 100) * (minus ? -1 : 1);
	}
	for (std::size_t i = point_idx + 1 + (minus ? 1 : 0); i < str.size() - 1; ++i) {
		auto const n = str[i] - '0';
		num += n * pow(0.1f, i - point_idx);
	}
	return (num / 100) * (minus ? -1 : 1);
}

}	 // namespace cui::ct::styles::detail

#endif	  // CUI_CT_STYLES_PARSE_PERCENTAGE_HPP