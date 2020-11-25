#ifndef CUI_CT_STYLES_PARSE_INT_HPP
#define CUI_CT_STYLES_PARSE_INT_HPP

#include <compile_time/string/string_view.hpp>
#include <compile_time/styles/detail/values/pow.hpp>
#include <compile_time/value_data.hpp>

namespace cui::ct::styles::detail {

constexpr auto parse_int(const StringView str) -> ValueData {
	bool minus = (str[0] == '-') ? true : false;
	int num = 0;
	for (std::size_t i = minus ? 1 : 0; i < str.size(); ++i) {
		const auto n = str[i] - '0';
		num += n * pow(10, str.size() - i - 1);
	}
	return num * (minus ? -1 : 1);
}

}	 // namespace cui::ct::styles::detail

#endif	  // CUI_CT_STYLES_PARSE_INT_HPP