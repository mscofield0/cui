#ifndef CUI_NODE_HPP
#define CUI_NODE_HPP

#include <functional>
#include <string>

#include <compile_time/string/string_view.hpp>
#include <tsl/hopscotch_map.h>
#include <tsl/hopscotch_set.h>
#include <visual/schematic.hpp>

namespace cui {

/// \brief Main GUI component
/// \details Dictates how the GUI is visually structured
class Node
{
public:
	using schematic_map_t = tsl::hopscotch_map<std::string, Schematic>;

	Node() noexcept;

	Node(const std::string& p_name, const std::string& p_text);

	Node(const std::string& p_name, const ct::StringView p_text);

	Node(const ct::StringView p_name, const std::string& p_text);

	Node(const ct::StringView p_name, const ct::StringView p_text);

	Node(const Node& rhs);

	Node(Node&& rhs);

	auto operator=(const Node& rhs) -> Node&;

	auto operator=(Node&& rhs) -> Node&;

	[[nodiscard]] auto default_schematic() noexcept -> Schematic&;

	[[nodiscard]] auto default_schematic() const noexcept -> const Schematic&;

	[[nodiscard]] auto event_schematics() noexcept -> schematic_map_t&;

	[[nodiscard]] auto event_schematics() const noexcept -> const schematic_map_t&;

	[[nodiscard]] auto active_schematic() noexcept -> std::reference_wrapper<Schematic>&;

	[[nodiscard]] auto active_schematic() const noexcept -> const std::reference_wrapper<Schematic>&;

	[[nodiscard]] auto name() noexcept -> std::string&;

	[[nodiscard]] auto name() const noexcept -> const std::string&;

	[[nodiscard]] auto text() noexcept -> std::string&;

	[[nodiscard]] auto text() const noexcept -> const std::string&;

	[[nodiscard]] auto attached_events() noexcept -> tsl::hopscotch_set<std::string>&;

	[[nodiscard]] auto attached_events() const noexcept -> const tsl::hopscotch_set<std::string>&;

	void attach_event(const std::string& name);

	void detach_event(const std::string& name);

private:
	Schematic default_schematic_;
	schematic_map_t event_schematics_;
	std::reference_wrapper<Schematic> active_;
	std::string name_;
	std::string text_;
	tsl::hopscotch_set<std::string> attached_events_;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// \brief Constructs the root node
/// \details Schematics are default constructed, active schematic is set to the default schematic,
/// name is "root" and text is empty
Node::Node() noexcept : default_schematic_(), event_schematics_(), active_(std::ref(default_schematic_)), name_("root"), text_("") {}

/// \brief Constructs the node
/// \details Schematics are default constructed and active schematic is set to the default schematic
/// \param p_name The name of the node
/// \param p_text The text of the node
Node::Node(const std::string& p_name, const std::string& p_text)
	: default_schematic_(), event_schematics_(), active_(std::ref(default_schematic_)), name_(p_name), text_(p_text) {}

/// \brief Constructs the node
/// \details Schematics are default constructed and active schematic is set to the default schematic
/// \param p_name The name of the node
/// \param p_text The text of the node
Node::Node(const std::string& p_name, const ct::StringView p_text)
	: default_schematic_(), event_schematics_(), active_(std::ref(default_schematic_)), name_(p_name), text_(p_text.begin(), p_text.end()) {}

/// \brief Constructs the node
/// \details Schematics are default constructed and active schematic is set to the default schematic
/// \param p_name The name of the node
/// \param p_text The text of the node
Node::Node(const ct::StringView p_name, const std::string& p_text)
	: default_schematic_(), event_schematics_(), active_(std::ref(default_schematic_)), name_(p_name.begin(), p_name.end()), text_(p_text) {}

/// \brief Constructs the node
/// \details Schematics are default constructed and active schematic is set to the default schematic
/// \param p_name The name of the node
/// \param p_text The text of the node
Node::Node(const ct::StringView p_name, const ct::StringView p_text)
	: default_schematic_(), event_schematics_(), active_(std::ref(default_schematic_)), name_(p_name.begin(), p_name.end()),
	  text_(p_text.begin(), p_text.end()) {}

/// \brief Copy constructs the node
/// \details Reassigns the active schematic to the default schematic
Node::Node(const Node& rhs)
	: default_schematic_(rhs.default_schematic_), event_schematics_(rhs.event_schematics_), active_(std::ref(default_schematic_)), name_(rhs.name_),
	  text_(rhs.text_), attached_events_(rhs.attached_events_) {}

/// \brief Copy constructs the node
/// \details Reassigns the active schematic to the default schematic
Node::Node(Node&& rhs)
	: default_schematic_(std::move(rhs.default_schematic_)), event_schematics_(std::move(rhs.event_schematics_)), active_(std::ref(default_schematic_)),
	  name_(std::move(rhs.name_)), text_(std::move(rhs.text_)), attached_events_(std::move(rhs.attached_events_)) {}

/// \brief Copy assigns the node
/// \details Reassigns the active schematic to the default schematic
/// \param rhs Right side node
/// \returns A reference to this node
auto Node::operator=(const Node& rhs) -> Node& {
	default_schematic_ = rhs.default_schematic_;
	event_schematics_ = rhs.event_schematics_;
	active_ = default_schematic_;
	name_ = rhs.name_;
	text_ = rhs.text_;
	attached_events_ = rhs.attached_events_;
	return *this;
}

/// \brief Copy assigns the node
/// \details Reassigns the active schematic to the default schematic
/// \param rhs Right side node
/// \returns A reference to this node
auto Node::operator=(Node&& rhs) -> Node& {
	default_schematic_ = std::move(rhs.default_schematic_);
	event_schematics_ = std::move(rhs.event_schematics_);
	active_ = default_schematic_;
	name_ = std::move(rhs.name_);
	text_ = std::move(rhs.text_);
	attached_events_ = std::move(rhs.attached_events_);
	return *this;
}

/// \brief Gets a mutable default schematic
/// \returns The mutable default schematic
auto Node::default_schematic() noexcept -> Schematic& {
	return default_schematic_;
}

/// \brief Gets an immutable default schematic
/// \returns The immutable default schematic
auto Node::default_schematic() const noexcept -> const Schematic& {
	return default_schematic_;
}

/// \brief Gets a mutable event schematic map
/// \returns The mutable event schematic map
auto Node::event_schematics() noexcept -> schematic_map_t& {
	return event_schematics_;
}

/// \brief Gets an immutable event schematic map
/// \returns The immutable event schematic map
auto Node::event_schematics() const noexcept -> const schematic_map_t& {
	return event_schematics_;
}

/// \brief Gets a mutable active schematic
/// \returns The mutable active schematic
auto Node::active_schematic() noexcept -> std::reference_wrapper<Schematic>& {
	return active_;
}

/// \brief Gets an immutable active schematic
/// \returns The immutable active schematic
auto Node::active_schematic() const noexcept -> const std::reference_wrapper<Schematic>& {
	return active_;
}

/// \brief Gets a mutable name
/// \returns The mutable name
auto Node::name() noexcept -> std::string& {
	return name_;
}

/// \brief Gets an immutable name
/// \returns The immutable name
auto Node::name() const noexcept -> const std::string& {
	return name_;
}

/// \brief Gets a mutable text
/// \returns The mutable text
auto Node::text() noexcept -> std::string& {
	return text_;
}

/// \brief Gets an immutable text
/// \returns The immutable text
auto Node::text() const noexcept -> const std::string& {
	return text_;
}

/// \brief Gets a mutable attached events set
/// \returns The mutable attached events set
auto Node::attached_events() noexcept -> tsl::hopscotch_set<std::string>& {
	return attached_events_;
}

/// \brief Gets an immutable attached events set
/// \returns The immutable attached events set
auto Node::attached_events() const noexcept -> const tsl::hopscotch_set<std::string>& {
	return attached_events_;
}

/// \brief Attaches an event name to the set
void Node::attach_event(const std::string& name) {
	attached_events_.emplace(name);
}

/// \brief Detaches an event name from the set
void Node::detach_event(const std::string& name) {
	attached_events_.emplace(name);
}

}	 // namespace cui

#endif	  // CUI_VISUAL_NODE_HPP