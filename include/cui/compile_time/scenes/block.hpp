#ifndef CUI_CT_SCENES_BLOCK_HPP
#define CUI_CT_SCENES_BLOCK_HPP

#include <compile_time/scenes/detail/valid_block_name.hpp>
#include <compile_time/string/string_view.hpp>
#include <containers/static_vector.hpp>

namespace cui::ct::scenes {

class Block
{
public:
	using style_list_t = StaticVector<StringView, 64>;

	constexpr Block() : name_(), text_(), style_list_{} {}
	constexpr Block(const StringView p_name, const StringView p_text) : name_(p_name), text_(p_text), style_list_{} {}

	[[nodiscard]] constexpr auto name() noexcept -> StringView& {
		return name_;
	}

	[[nodiscard]] constexpr auto name() const noexcept -> StringView {
		return name_;
	}

	[[nodiscard]] constexpr auto text() noexcept -> StringView& {
		return text_;
	}

	[[nodiscard]] constexpr auto text() const noexcept -> StringView {
		return text_;
	}

	[[nodiscard]] constexpr auto style_list() noexcept -> style_list_t& {
		return style_list_;
	}

	[[nodiscard]] constexpr auto style_list() const noexcept -> const style_list_t& {
		return style_list_;
	}

	constexpr void add_style(StringView name) {
		style_list_.push_back(name);
	}

	constexpr bool parse_style_list(const StringView str) {
		if (str.empty()) return false;
		std::size_t prev = 0;
		std::size_t pos = str.find_first_of(',');
		while (pos != StringView::npos) {
			if (pos == prev) return false;
			const auto extracted = str.substr(prev, pos - prev);	// inspect later
			const auto trimmed = (extracted.substr(0, extracted.size())).trim();
			if (trimmed.empty()) return false;
			if (!detail::is_valid_block_name(trimmed)) return false;
			add_style(trimmed);
			prev = pos + 1;
			pos = str.find_first_of(',', prev);
		}
		if (prev == pos) return false;
		const auto extracted = str.substr(prev, pos - prev);
		const auto trimmed = (extracted.substr(0, extracted.size() - 1)).trim();	// inspect later
		if (trimmed.empty()) return false;
		if (!detail::is_valid_block_name(trimmed)) return false;
		add_style(trimmed);
		return true;
	}

private:
	StringView name_;
	StringView text_;
	style_list_t style_list_;
};

}	 // namespace cui::ct::scenes

#endif	  // #define CUI_CT_SCENES_BLOCK_HPP
