#ifndef CUI_SCENE_STATE_HPP
#define CUI_SCENE_STATE_HPP

#include <functional>
#include <string>
#include <string_view>
#include <utility>

#include <aliases.hpp>
#include <tsl/hopscotch_map.h>
#include <visual/scene_graph.hpp>

namespace cui {

/// \brief Encapsulated \sa cui::SceneGraph that provides registering events
/// \details Holds global and node-local events attached to be inspected on a specific
/// outer event in a map
/// \tparam TEventFunction Type of event function to be stored
/// \tparam TEvent Type of outer event
template <typename TEventFunction, typename TEvent>
class SceneState
{
public:
	using graph_t = SceneGraph;
	using outer_event_t = TEvent;
	using event_t = TEventFunction;
	using event_map_t = tsl::hopscotch_map<std::string, event_t>;
	using event_marker_map_t = tsl::hopscotch_map<outer_event_t, std::pair<event_map_t, event_map_t>>;

	SceneState(const graph_t& p_graph) : graph_(p_graph) {}

	SceneState(graph_t&& p_graph) : graph_(std::move(p_graph)) {}

	void register_event(const outer_event_t& type, const std::string& name, event_t&& event);
	void register_event(const outer_event_t& type, std::string&& name, event_t&& event);

	void register_global_event(const outer_event_t& type, const std::string& name, event_t&& event);
	void register_global_event(const outer_event_t& type, std::string&& name, event_t&& event);

	void unregister_event(const outer_event_t& type, const std::string& name);
	void unregister_event(const outer_event_t& type, std::string&& name);

	void unregister_global_event(const outer_event_t& type, const std::string& name);
	void unregister_global_event(const outer_event_t& type, std::string&& name);

	[[nodiscard]] auto get_event(const outer_event_t& type, const std::string& name) const -> const event_t&;
	[[nodiscard]] auto get_event(const outer_event_t& type, std::string&& name) const -> const event_t&;

	[[nodiscard]] auto get_global_event(const outer_event_t& type, const std::string& name) const -> const event_t&;
	[[nodiscard]] auto get_global_event(const outer_event_t& type, std::string&& name) const -> const event_t&;

	[[nodiscard]] auto graph() noexcept -> graph_t&;
	[[nodiscard]] auto graph() const noexcept -> const graph_t&;

	[[nodiscard]] auto marked_sections() const noexcept -> const event_marker_map_t&;

	[[nodiscard]] auto registered_events(const outer_event_t& event_type) const -> const event_map_t&;

	[[nodiscard]] auto registered_global_events(const outer_event_t& event_type) const -> const event_map_t&;

private:
	graph_t graph_;
	event_marker_map_t marked_sections_;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// \brief Register a node-local event
/// \param type Type of outer event emitted
/// \param name Name of the event to register
/// \param event Event function that is stored to be invoked in dispatches
template <typename TEventFunction, typename TEvent>
void SceneState<TEventFunction, TEvent>::register_event(const outer_event_t& type,
														const std::string& name,
														event_t&& event) {
	auto& reged_events = marked_sections_[type].first;
	reged_events[name] = std::move(event);
}

/// \brief Register a node-local event
/// \param type Type of outer event emitted
/// \param name Name of the event to register
/// \param event Event function that is stored to be invoked in dispatches
template <typename TEventFunction, typename TEvent>
void SceneState<TEventFunction, TEvent>::register_event(const outer_event_t& type,
														std::string&& name,
														event_t&& event) {
	auto& reged_events = marked_sections_[type].first;
	reged_events[std::move(name)] = std::move(event);
}

/// \brief Register a global event
/// \param type Type of outer event emitted
/// \param name Name of the event to register
/// \param event Event function that is stored to be invoked in dispatches
template <typename TEventFunction, typename TEvent>
void SceneState<TEventFunction, TEvent>::register_global_event(const outer_event_t& type,
															   const std::string& name,
															   event_t&& event) {
	auto& reged_events = marked_sections_[type].second;
	reged_events[name] = std::move(event);
}

/// \brief Register a global event
/// \param type Type of outer event emitted
/// \param name Name of the event to register
/// \param event Event function that is stored to be invoked in dispatches
template <typename TEventFunction, typename TEvent>
void SceneState<TEventFunction, TEvent>::register_global_event(const outer_event_t& type,
															   std::string&& name,
															   event_t&& event) {
	auto& reged_events = marked_sections_[type].second;
	reged_events[std::move(name)] = std::move(event);
}

/// \brief Unregisters a node-local event
/// \param type Type of outer event emitted
/// \param name Name of the event to unregister
template <typename TEventFunction, typename TEvent>
void SceneState<TEventFunction, TEvent>::unregister_event(const outer_event_t& type, const std::string& name) {
	marked_sections_[type].first.erase(name);
}

/// \brief Unregisters a node-local event
/// \param type Type of outer event emitted
/// \param name Name of the event to unregister
template <typename TEventFunction, typename TEvent>
void SceneState<TEventFunction, TEvent>::unregister_event(const outer_event_t& type, std::string&& name) {
	marked_sections_[type].first.erase(std::move(name));
}

/// \brief Unregisters a global event
/// \param type Type of outer event emitted
/// \param name Name of the event to unregister
template <typename TEventFunction, typename TEvent>
void SceneState<TEventFunction, TEvent>::unregister_global_event(const outer_event_t& type, const std::string& name) {
	marked_sections_[type].second.erase(name);
}

/// \brief Unregisters a global event
/// \param type Type of outer event emitted
/// \param name Name of the event to unregister
template <typename TEventFunction, typename TEvent>
void SceneState<TEventFunction, TEvent>::unregister_global_event(const outer_event_t& type, std::string&& name) {
	marked_sections_[type].second.erase(std::move(name));
}

/// \brief Gets the node-local event from the event map
/// \details May throw if no event has been found
/// \param type Type of outer event emitted
/// \param name Name of the event to register
/// \returns The specified event
template <typename TEventFunction, typename TEvent>
auto SceneState<TEventFunction, TEvent>::get_event(const outer_event_t& type, const std::string& name) const
  -> const event_t& {
	return marked_sections_.at(type).first.at(name);
}

/// \brief Gets the node-local event from the event map
/// \details May throw if no event has been found
/// \param type Type of outer event emitted
/// \param name Name of the event to register
/// \returns The specified event
template <typename TEventFunction, typename TEvent>
auto SceneState<TEventFunction, TEvent>::get_event(const outer_event_t& type, std::string&& name) const
  -> const event_t& {
	return marked_sections_.at(type).first.at(std::move(name));
}

/// \brief Gets the global event from the event map
/// \details May throw if no event has been found
/// \param type Type of outer event emitted
/// \param name Name of the event to register
/// \returns The specified event
template <typename TEventFunction, typename TEvent>
auto SceneState<TEventFunction, TEvent>::get_global_event(const outer_event_t& type, const std::string& name) const
  -> const event_t& {
	return marked_sections_.at(type).second.at(name);
}

/// \brief Gets the global event from the event map
/// \details May throw if no event has been found
/// \param type Type of outer event emitted
/// \param name Name of the event to register
/// \returns The specified event
template <typename TEventFunction, typename TEvent>
auto SceneState<TEventFunction, TEvent>::get_global_event(const outer_event_t& type, std::string&& name) const
  -> const event_t& {
	return marked_sections_.at(type).second.at(std::move(name));
}

/// \brief Gets the \sa cui::SceneGraph
/// \returns The \sa cui::SceneGraph
template <typename TEventFunction, typename TEvent>
auto SceneState<TEventFunction, TEvent>::graph() noexcept -> graph_t& {
	return graph_;
}

/// \brief Gets the \sa cui::SceneGraph
/// \returns The \sa cui::SceneGraph
template <typename TEventFunction, typename TEvent>
auto SceneState<TEventFunction, TEvent>::graph() const noexcept -> const graph_t& {
	return graph_;
}

/// \brief Gets the event map
/// \returns The event map
template <typename TEventFunction, typename TEvent>
auto SceneState<TEventFunction, TEvent>::marked_sections() const noexcept -> const event_marker_map_t& {
	return marked_sections_;
}

/// \brief Gets the list of registered node-local events on a specified outer event type
/// \details May throw if no such outer event type is registered yet
/// \returns The events marked on the outer event type
template <typename TEventFunction, typename TEvent>
auto SceneState<TEventFunction, TEvent>::registered_events(const outer_event_t& event_type) const
  -> const event_map_t& {
	return marked_sections_.at(event_type).first;
}

/// \brief Gets the list of registered global events on a specified outer event type
/// \details May throw if no such outer event type is registered yet
/// \returns The events marked on the outer event type
template <typename TEventFunction, typename TEvent>
auto SceneState<TEventFunction, TEvent>::registered_global_events(const outer_event_t& event_type) const
  -> const event_map_t& {
	return marked_sections_.at(event_type).second;
}

}	 // namespace cui

#endif	  // CUI_SCENE_STATE_HPP