#ifndef CUI_CT_STYLES_COUNT_DEFINITIONS_HPP
#define CUI_CT_STYLES_COUNT_DEFINITIONS_HPP

#include <cstdint>

#include <compile_time/stream/stream.hpp>
#include <compile_time/stream/stream_utils.hpp>
#include <compile_time/string/string_view.hpp>

namespace cui::ct::styles {

constexpr auto count_definitions(const StringView str) -> std::size_t {
	CharStream stream{str};
	std::size_t count = 0;

	while (stream.good()) {
		if (*stream.current() == '}') ++count;
		stream.next();
	}
	return count;
}

}	 // namespace cui::ct::styles

#endif	  // CUI_CT_STYLES_DETAIL_COUNT_DEFINITIONS_HPP