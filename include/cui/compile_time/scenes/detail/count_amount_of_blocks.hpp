#ifndef CUI_CT_SCENES_COUNT_AMOUNT_OF_BLOCKS_HPP
#define CUI_CT_SCENES_COUNT_AMOUNT_OF_BLOCKS_HPP

#include <cstdint>

#include <compile_time/stream/stream.hpp>
#include <compile_time/stream/stream_utils.hpp>
#include <compile_time/string/string_view.hpp>

namespace cui::ct::scenes::detail {

constexpr auto count_amount_of_blocks(const char* str) -> std::size_t {
	CharStream stream(StringView{str});
	std::size_t amount = 0;
	while (stream.good()) {
		const auto line = consume_line(stream);
		const auto trimmed = line.trim();
		if (trimmed.empty()) continue;
		++amount;
	}

	return amount;
}

}	 // namespace cui::ct::scenes::detail

#endif	  // CUI_CT_SCENES_COUNT_AMOUNT_OF_BLOCKS_HPP