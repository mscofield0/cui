#ifndef CUI_CT_STYLE_HPP
#define CUI_CT_STYLE_HPP

#include <compile_time/string/string_view.hpp>
#include <compile_time/styles/attribute_data.hpp>
#include <compile_time/styles/definition.hpp>
#include <compile_time/styles/detail/helper_macros.hpp>
#include <compile_time/styles/detail/values/filter_preprocessed_type.hpp>
#include <compile_time/styles/detail/values/is_correct_value_for_attr_type.hpp>
#include <compile_time/styles/detail/values/parse_url.hpp>
#include <compile_time/styles/detail/values/validate_attribute_type.hpp>
#include <compile_time/styles/detail/values/value_type.hpp>
#include <compile_time/styles/parse_attribute_value.hpp>

#include <compile_time/format/fmt.hpp>
#include <compile_time/format/fmt_string_view.hpp>
#include <compile_time/format/format.hpp>
#include <containers/static_vector.hpp>

namespace cui::ct {

/// \brief Style class that holds attribute data to be used by a CUI binding
class Style
{
public:
	using events_t = StaticVector<StringView, 64>;
	using attributes_t = StaticVector<styles::AttributeData, 64>;

	constexpr Style() : name_(), events_{}, attributes_{} {}

	[[nodiscard]] constexpr auto name() noexcept -> StringView&;

	[[nodiscard]] constexpr auto name() const noexcept -> StringView;

	[[nodiscard]] constexpr auto events() noexcept -> events_t&;

	[[nodiscard]] constexpr auto events() const noexcept -> const events_t&;

	[[nodiscard]] constexpr auto attributes() noexcept -> attributes_t&;

	[[nodiscard]] constexpr auto attributes() const noexcept -> const attributes_t&;

	[[nodiscard]] static constexpr auto create(const styles::Definition& def) -> Variant<Style, Format<256>>;

private:
	StringView name_;
	events_t events_;
	attributes_t attributes_;
};

/// \brief Gets a mutable name
/// \returns The mutable name
constexpr auto Style::name() noexcept -> StringView& {
	return name_;
}

/// \brief Gets an immutable name
/// \returns The immutable name
constexpr auto Style::name() const noexcept -> StringView {
	return name_;
}

/// \brief Gets a mutable events
/// \returns The mutable events
constexpr auto Style::events() noexcept -> events_t& {
	return events_;
}

/// \brief Gets an immutable events
/// \returns The immutable events
constexpr auto Style::events() const noexcept -> const events_t& {
	return events_;
}

/// \brief Gets a mutable attributes
/// \returns The mutable attributes
constexpr auto Style::attributes() noexcept -> attributes_t& {
	return attributes_;
}

/// \brief Gets an immutable attributes
/// \returns The immutable attributes
constexpr auto Style::attributes() const noexcept -> const attributes_t& {
	return attributes_;
}

/// \brief Creates a \sa cui::ct::Style from a \sa cui::ct::styles::Definition
/// \param def The definition with which to create the \sa cui::ct::Style
/// \returns The created \sa cui::ct::Style
constexpr auto Style::create(const styles::Definition& def) -> Variant<Style, Format<256>> {
	Style style;
	style.name() = def.identifier();
	for (const auto str : def.events()) style.events().push_back(str);

	for (const auto& attribute : def.attributes()) {
		if (!styles::detail::validate_attribute_type(attribute.type())) {
			CUI_RETURN_ERROR("ERROR: Attribute type is invalid.\nProvided: {}", attribute.type());
		}

		if (attribute.value().substr(0, attribute.value().find_first_of('(')).compare("url") == 0) {
			const auto parsed_url = styles::detail::parse_url(attribute.value().trim());
			if (parsed_url.is_none()) {
				CUI_RETURN_ERROR("ERROR: Invalid syntax while parsing URL function. Received: {}\nFunction signature "
								 "must be in this pattern: func_name(args, ...)",
								 attribute.value());
			}
			if (!styles::detail::is_correct_value_for_attr_type(attribute.type(), parsed_url)) {
				CUI_RETURN_ERROR("ERROR: Received wrong value for attribute. Attribute type was: {}\nReceived: {}", attribute.type(), attribute.value());
			}
			style.attributes().emplace_back(attribute.type(), parsed_url.string(), styles::ValueType::String);
			continue;
		}

		const auto attr_value_variant = styles::detail::parse_attribute_value(attribute.value());
		if (attr_value_variant.is_type_b()) {
			return attr_value_variant.type_b();
		}

		if (!styles::detail::is_correct_value_for_attr_type(attribute.type(), attr_value_variant.type_a().data())) {
			CUI_RETURN_ERROR("ERROR: Received wrong value for attribute. Attribute type was: {}\nReceived: {}", attribute.type(), attribute.value());
		}

		const auto pp_type = attr_value_variant.type_a().preprocessed_type();
		const auto filtered_type = styles::detail::filter_preprocessed_type(attribute.type(), pp_type);
		style.attributes().emplace_back(attribute.type(), attr_value_variant.type_a().data(), filtered_type);
	}

	return style;
}

}	 // namespace cui::ct

#endif	  // CUI_STYLES_STYLE_HPP