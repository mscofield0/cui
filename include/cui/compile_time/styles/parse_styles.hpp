#ifndef CUI_CT_STYLES_PARSE_STYLES_HPP
#define CUI_CT_STYLES_PARSE_STYLES_HPP

#include <aliases.hpp>
#include <compile_time/format/fmt.hpp>
#include <compile_time/format/format.hpp>
#include <compile_time/stream/stream.hpp>
#include <compile_time/stream/stream_utils.hpp>
#include <compile_time/string/string_view.hpp>
#include <compile_time/styles/definition.hpp>
#include <compile_time/styles/detail/styles/count_definitions.hpp>
#include <compile_time/styles/detail/styles/valid_style_name.hpp>
#include <compile_time/variant/variant.hpp>
#include <containers/static_vector.hpp>

#define CUI_CT_RETURN_STYLES_PARSE_ERROR(msg) return fmt_s<256>("ERROR at LINE:{}, COL:{} :: {}", stream.line(), stream.col(), msg)

namespace cui::ct::styles {

template <const char* str>
constexpr auto parse_styles() -> Variant<StaticVector<Definition, count_definitions(str)>, Format<256>> {
	CharStream stream(str);
	constexpr StringView delims("[]{};:");
	constexpr auto AOD = count_definitions(str);

	constexpr const char missing_styles_identifier[] = "Expected a styles identifier";
	constexpr const char expected_end_of_style[] = "Expected end of style";
	constexpr const char invalid_event_list[] = "Invalid event list";
	constexpr const char expected_identifier_or_event_list[] = "Expected a styles identifier or an event list";
	constexpr const char expected_end_of_style_or_attribute[] = "Expected an open curly brace or the end of an attribute";
	constexpr const char expected_attribute_identifier_and_colon[] = "Expected an attribute identifier and a colon";
	constexpr const char empty_attribute_value[] = "Attribute value is empty";
	constexpr const char expected_event_list_definition_symbol[] = "Expected a '[' previously";
	constexpr const char missing_event_list[] = "Expected an event list";
	constexpr const char invalid_style_name[] = "Style identifier is invalid; Must contain only [A-Za-z0-9_] not starting with a number";

	enum class States : u8
	{
		None = 0,
		OnOpenSquareBracket = '[',
		OnCloseSquareBracket = ']',
		OnSemicolon = ';',
		OnOpenCurlyBracket = '{',
		OnCloseCurlyBracket = '}',
		OnColon = ':'
	} state = States::None;

	StaticVector<Definition, AOD> defs;

	while (stream.good()) {
		const auto consumed = consume(stream, delims);
		const auto trimmed = consumed.first.trim();

		const auto temp_state = static_cast<States>(consumed.second);
		switch (temp_state) {
			case States::OnOpenSquareBracket: {
				if (state != States::None) {
					CUI_CT_RETURN_STYLES_PARSE_ERROR(expected_end_of_style);
				}
				if (trimmed.empty()) {
					CUI_CT_RETURN_STYLES_PARSE_ERROR(missing_styles_identifier);
				}
				if (!detail::is_valid_style_name(trimmed)) {
					CUI_CT_RETURN_STYLES_PARSE_ERROR(invalid_style_name);
				}

				defs.emplace_back();
				defs.back().identifier() = trimmed;
				state = States::OnOpenSquareBracket;
				break;
			}
			case States::OnCloseSquareBracket: {
				if (state != States::OnOpenSquareBracket) {
					CUI_CT_RETURN_STYLES_PARSE_ERROR(expected_event_list_definition_symbol);
				}

				if (trimmed.empty()) {
					CUI_CT_RETURN_STYLES_PARSE_ERROR(missing_event_list);
				}

				if (!defs.back().parse_events(trimmed)) {
					CUI_CT_RETURN_STYLES_PARSE_ERROR(invalid_event_list);
				}

				state = States::OnCloseSquareBracket;
				break;
			}
			case States::OnOpenCurlyBracket: {
				if (state != States::OnCloseSquareBracket && state != States::None) {
					CUI_CT_RETURN_STYLES_PARSE_ERROR(expected_identifier_or_event_list);
				}

				if (state == States::None && trimmed.empty()) {
					CUI_CT_RETURN_STYLES_PARSE_ERROR(missing_styles_identifier);
				}

				if (state == States::None) {
					if (!detail::is_valid_style_name(trimmed)) {
						CUI_CT_RETURN_STYLES_PARSE_ERROR(invalid_style_name);
					}

					defs.emplace_back();
					defs.back().identifier() = trimmed;
				}

				state = States::OnOpenCurlyBracket;
				break;
			}

			case States::OnCloseCurlyBracket: {
				if (state != States::OnOpenCurlyBracket && state != States::OnSemicolon) {
					CUI_CT_RETURN_STYLES_PARSE_ERROR(expected_end_of_style_or_attribute);
				}

				state = States::None;
				break;
			}

			case States::OnSemicolon: {
				if (state != States::OnColon) {
					CUI_CT_RETURN_STYLES_PARSE_ERROR(expected_attribute_identifier_and_colon);
				}

				if (trimmed.empty()) {
					CUI_CT_RETURN_STYLES_PARSE_ERROR(empty_attribute_value);
				}

				defs.back().add_attribute_value(trimmed);

				state = States::OnSemicolon;
				break;
			}

			case States::OnColon: {
				if (state != States::OnOpenCurlyBracket && state != States::OnSemicolon) {
					CUI_CT_RETURN_STYLES_PARSE_ERROR(expected_end_of_style_or_attribute);
				}

				if (trimmed.empty()) {
					CUI_CT_RETURN_STYLES_PARSE_ERROR(empty_attribute_value);
				}

				defs.back().add_attribute_name(trimmed);
				state = States::OnColon;
				break;
			}

			default: {
				break;	  // "No delimiters found."
			}
		}
	}

	return defs;
}

}	 // namespace cui::ct::styles

#endif	  // CUI_CT_STYLES_PARSE_STYLES_HPP