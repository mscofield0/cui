#ifndef CUI_CT_STYLES_DEFINITION_HPP
#define CUI_CT_STYLES_DEFINITION_HPP

#include <compile_time/string/string_view.hpp>
#include <compile_time/styles/attribute.hpp>
#include <containers/static_vector.hpp>

namespace cui::ct::styles {

/// \brief Class holding a style definition
class Definition
{
public:
	using events_t = StaticVector<StringView, 64>;
	using attributes_t = StaticVector<Attribute, 64>;

	constexpr Definition() : identifier_(), events_{}, attributes_{} {}

	[[nodiscard]] constexpr auto identifier() noexcept -> StringView& {
		return identifier_;
	}

	[[nodiscard]] constexpr auto identifier() const noexcept -> StringView {
		return identifier_;
	}

	[[nodiscard]] constexpr auto events() noexcept -> events_t& {
		return events_;
	}

	[[nodiscard]] constexpr auto events() const noexcept -> const events_t& {
		return events_;
	}

	[[nodiscard]] constexpr auto attributes() noexcept -> attributes_t& {
		return attributes_;
	}

	[[nodiscard]] constexpr auto attributes() const noexcept -> const attributes_t& {
		return attributes_;
	}

	constexpr void add_event(const StringView event_name) {
		events_.push_back(event_name);
	}

	constexpr void add_attribute_name(const StringView attr_name) {
		attributes_.emplace_back();
		attributes_.back().type() = attr_name;
	}

	constexpr void add_attribute_value(const StringView attr_value) {
		attributes_.back().value() = attr_value;
	}

	[[nodiscard]] constexpr bool parse_events(const StringView events) {
		if (events.empty()) return false;

		std::size_t prev = 0;
		std::size_t pos = events.find_first_of(',');
		while (pos != StringView::npos) {
			if (prev == pos) return false;
			const auto temp_str = events.substr(prev, pos - prev).trim();
			add_event(temp_str);
			prev = pos + 1;
			pos = events.find_first_of(',', prev);
		}
		if (prev == pos) return false;
		const auto temp_str = events.substr(prev, pos - prev).trim();
		add_event(temp_str);
		return true;
	}

private:
	StringView identifier_;
	events_t events_;
	attributes_t attributes_;
};

}	 // namespace cui::ct::styles

#endif	  // CUI_CT_STYLES_DEFINITION_HPP