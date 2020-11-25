#ifndef CUI_CT_FMT_STRING_VIEW_HPP
#define CUI_CT_FMT_STRING_VIEW_HPP

#include <compile_time/format/format.hpp>
#include <compile_time/string/string_view.hpp>

template <std::size_t Size>
constexpr cui::ct::Format<Size>& operator<<(cui::ct::Format<Size>& format, const cui::ct::StringView str) {
	for (const auto ch : str) format.append(ch);
	return format;
}

#endif	  // CUI_CT_FMT_STRING_VIEW_HPP