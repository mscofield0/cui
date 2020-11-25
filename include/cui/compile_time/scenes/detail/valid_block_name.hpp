#ifndef CUI_CT_SCENES_VALID_BLOCK_NAME_HPP
#define CUI_CT_SCENES_VALID_BLOCK_NAME_HPP

#include <compile_time/string/string_view.hpp>

namespace cui::ct::scenes::detail {

constexpr bool is_valid_block_name(const StringView str) {
	constexpr StringView valid_chars{"abcdefghijklmnopqrstuvwxyz0123456789_"};
	if (str.empty()) return false;
	if (str[0] >= '0' && str[0] <= '9') return false;
	for (auto el : str) {
		bool b = false;
		for (auto vc : valid_chars) {
			if (el == vc) {
				b = true;
				break;
			}
		}
		if (!b) return false;
	}
	return true;
}

}	 // namespace cui::ct::scenes::detail

#endif	  // CUI_CT_SCENES_VALID_BLOCK_NAME_HPP