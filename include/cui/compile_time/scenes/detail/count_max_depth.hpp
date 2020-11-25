#ifndef CUI_CT_SCENES_COUNT_MAX_DEPTH_HPP
#define CUI_CT_SCENES_COUNT_MAX_DEPTH_HPP

#include <cstdint>

#include <compile_time/scenes/detail/count_tabs.hpp>
#include <compile_time/stream/stream.hpp>
#include <compile_time/stream/stream_utils.hpp>
#include <compile_time/string/string_view.hpp>

namespace cui::ct::scenes::detail {

constexpr auto count_max_depth(const StringView str) -> std::size_t {
	CharStream stream(str);
	std::size_t max = 0;
	while (stream.good()) {
		const auto line = consume_line(stream);
		const auto trimmed = line.trim();
		if (trimmed.empty()) continue;
		const auto t = count_tabs(line);
		if (t > max) max = t;
	}
	return max;
}

}	 // namespace cui::ct::scenes::detail

#endif	  // CUI_CT_SCENES_COUNT_MAX_DEPTH_HPP