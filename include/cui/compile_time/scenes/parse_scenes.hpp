#ifndef CUI_CT_SCENES_PARSE_SCENES_HPP
#define CUI_CT_SCENES_PARSE_SCENES_HPP

#include <algorithm>

#include <compile_time/format/fmt.hpp>
#include <compile_time/format/fmt_string_view.hpp>
#include <compile_time/format/format.hpp>
#include <compile_time/scene.hpp>
#include <compile_time/scenes/detail/count_amount_of_blocks.hpp>
#include <compile_time/scenes/detail/count_max_depth.hpp>
#include <compile_time/scenes/detail/count_tabs.hpp>
#include <compile_time/scenes/detail/find_parent.hpp>
#include <compile_time/scenes/detail/valid_block_name.hpp>
#include <compile_time/stream/stream.hpp>
#include <compile_time/stream/stream_utils.hpp>
#include <compile_time/string/string_view.hpp>
#include <compile_time/variant/variant.hpp>
#include <containers/static_stack.hpp>

#define CUI_CT_RETURN_SCENES_PARSE_ERROR(msg) return fmt_s<256>("ERROR at LINE:{}, COL:{} :: {}", stream.line(), stream.col(), msg)

#define CUI_CT_RETURN_SCENES_PARSE_ERROR_WITH_INFO(msg, info) \
	return fmt_s<256>("ERROR at LINE:{}, COL:{} :: {}; Found: |{}|", stream.line(), stream.col(), msg, info)

namespace cui::ct::scenes {

template <const char* str>
constexpr auto parse_scenes() -> Variant<Scene<detail::count_amount_of_blocks(str)>, Format<256>> {
	constexpr auto amount_of_blocks = detail::count_amount_of_blocks(str);

	constexpr char invalid_block_name[] = "Invalid block name (must consist of alphanumeric character [a-zA-Z0-9] starting with a letter)";
	constexpr char invalid_num_of_tabs[] = "Invalid number of tabs";
	constexpr char empty_child_stack[] = "The child stack was left empty";
	constexpr char invalid_styles_list[] = "Incorrect style list";
	constexpr char invalid_text_syntax[] = "Invalid text data syntax; ' > ' found before ' < '";
	constexpr char invalid_style_list_syntax[] = "Invalid style list syntax; ' < ' found before ' \" '";
	constexpr char expected_end_of_text_data[] = "Expected end of text data; Did not find ' > ' at the end";
	constexpr char expected_end_of_style_list[] = "Expected end of style list; Did not find ' \" ' at the end";

	CharStream stream(str);
	Scene<amount_of_blocks> result;
	StaticStack<std::size_t, 64> block_stack;
	std::size_t current_depth = 0;

	while (stream.good()) {
		const auto line = consume_line(stream);
		const auto trimmed = line.trim();
		if (trimmed.empty()) continue;

		// Count the amount of tabs on the beginning of the line
		const auto num_of_tabs = detail::count_tabs(line);

		// Find the first apostrophy indicating the start of a style list
		const auto idx_of_list_start = trimmed.find_first_of('\"');

		// Find the first left arrow symbol indicating the start of a text section
		const auto idx_of_text_start = trimmed.find_first_of('<');

		// Check if there is a style list
		const auto no_style_list = (idx_of_list_start > idx_of_text_start) ? (true) : (false);

		// Find the last right arrow symbol indicating the end of a text section
		const auto idx_of_text_end = trimmed.find_last_of('>');

		// If the text section end symbol is found before the text section start symbol, then return an error
		if (idx_of_text_start > idx_of_text_end) {
			CUI_CT_RETURN_SCENES_PARSE_ERROR_WITH_INFO(invalid_text_syntax, trimmed);
		}

		// Append a new block onto the scene result
		result.blocks().emplace_back();
		result.children().emplace_back();
		result.depths().emplace_back();

		//////////////////////////
		// Block name extracting
		//////////////////////////

		// Retrieve the index of either the style list start or the text section start
		// If the block definition has no style list and text section, it will retrieve npos
		const auto first_token = std::min(idx_of_list_start, idx_of_text_start);

		// Extract the block name
		const auto name = trimmed.substr(0, first_token).trim();

		// Check if the block name is valid, if it's not return an error
		if (!detail::is_valid_block_name(name)) {
			CUI_CT_RETURN_SCENES_PARSE_ERROR_WITH_INFO(invalid_block_name, name);
		}

		// Set the block's name
		result.blocks().back().name() = name;

		//////////////////////////
		// Style list extracting
		//////////////////////////

		// No need to parse a style list if the text section is first
		if (!no_style_list) {
			// Check if there is a text section
			if (idx_of_text_start == StringView::npos) {
				// Check if the last symbol is apostrophy
				if (trimmed[trimmed.size() - 1] != '"') {
					CUI_CT_RETURN_SCENES_PARSE_ERROR_WITH_INFO(expected_end_of_style_list, trimmed);
				}
			}

			// There must be a style list start
			if (idx_of_list_start != StringView::npos) {
				// Find the style list end
				const auto second_token = trimmed.find_first_of('"', idx_of_list_start + 1);
				// If the text section start is before the style list end, then there is no style list end
				if (second_token >= idx_of_text_start) {
					CUI_CT_RETURN_SCENES_PARSE_ERROR_WITH_INFO(invalid_style_list_syntax, trimmed);
				}
				// Extract the style list
				const auto style_list = trimmed.substr(first_token + 1, second_token - first_token);

				// Parse the style list | If the style list is incorrect, return an error
				if (!result.blocks().back().parse_style_list(style_list)) {
					CUI_CT_RETURN_SCENES_PARSE_ERROR_WITH_INFO(invalid_styles_list, style_list);
				}
			}
		}

		//////////////////////////
		// Text section extracting
		//////////////////////////

		// Nothing to extract if no such symbol was found
		if (idx_of_text_start != StringView::npos) {
			// Check last symbol, if there is no left arrow symbol indicating the end of the text section
			if (trimmed[trimmed.size() - 1] != '>') {
				CUI_CT_RETURN_SCENES_PARSE_ERROR_WITH_INFO(expected_end_of_text_data, trimmed);
			}

			// Calculate text section size
			const auto text_data_size = std::distance(trimmed.begin() + idx_of_text_start, trimmed.end() - 2);

			// Assign the text to the block
			result.blocks().back().text() = trimmed.substr(idx_of_text_start + 1, text_data_size);
		}

		//////////////////////////
		// Tree calculation
		//////////////////////////

		// If there are tabs, calculate depth and parent of the node
		if (num_of_tabs != 0) {
			// If the current number of tabs is 2 or more larger than the current tree depth, return an error
			if (current_depth < num_of_tabs - 1) {
				CUI_CT_RETURN_SCENES_PARSE_ERROR_WITH_INFO(invalid_num_of_tabs, num_of_tabs);
			}

			// Assign the depth to the block
			result.depths().back() = num_of_tabs;

			// Find the block's parent index
			const auto parent_idx = detail::find_parent(block_stack, result.depths(), result.index_of_last());

			// If there is no parent found, return an error
			if (parent_idx == result.depths().size()) {
				CUI_CT_RETURN_SCENES_PARSE_ERROR(empty_child_stack);
			}

			// Add the current block index to the parent's children list
			result.add_child_to(parent_idx, result.index_of_last());

			// Pushes the current block index onto the block stack
			block_stack.push(result.index_of_last());

			// Assigns the number of tabs to the current tree depth
			current_depth = num_of_tabs;
		} else {
			// Clears the block stack
			block_stack.clear();

			// Pushes the current block index onto the stack
			block_stack.push(result.index_of_last());

			// Sets the current tree depth to 0
			current_depth = 0;
		}
	}

	return result;
}

}	 // namespace cui::ct::scenes

#endif	  // CUI_CT_SCENES_PARSE_SCENES_HPP