#ifndef CUI_NARY_TREE_HPP
#define CUI_NARY_TREE_HPP

#include <algorithm>
#include <functional>
#include <vector>

#include <aliases.hpp>
#include <containers/detail/nary_tree/node.hpp>

namespace cui {

template <typename T>
class NaryTree
{
public:
	using node_type = nary::Node<T>;
	using size_type = std::size_t;
	using data_type = typename node_type::data_type;
	using iterator = typename std::vector<node_type>::iterator;
	using const_iterator = typename std::vector<node_type>::const_iterator;

	[[nodiscard]] auto length() const noexcept -> size_type {
		return vec_.size();
	}

	[[nodiscard]] auto begin() noexcept -> iterator {
		return vec_.begin();
	}

	[[nodiscard]] auto begin() const noexcept -> const_iterator {
		return vec_.cbegin();
	}

	[[nodiscard]] auto cbegin() const noexcept -> const_iterator {
		return vec_.cbegin();
	}

	[[nodiscard]] auto end() noexcept -> iterator {
		return vec_.end();
	}

	[[nodiscard]] auto end() const noexcept -> const_iterator {
		return vec_.cend();
	}

	[[nodiscard]] auto cend() const noexcept -> const_iterator {
		return vec_.cend();
	}

	[[nodiscard]] auto front() noexcept -> node_type& {
		return vec_.front();
	}

	[[nodiscard]] auto front() const noexcept -> const node_type& {
		return vec_.front();
	}

	[[nodiscard]] auto back() noexcept -> node_type& {
		return vec_.back();
	}

	[[nodiscard]] auto back() const noexcept -> const node_type& {
		return vec_.back();
	}

	[[nodiscard]] auto operator[](const size_type idx) noexcept -> node_type& {
		return vec_[idx];
	}

	[[nodiscard]] auto operator[](const size_type idx) const noexcept -> const node_type& {
		return vec_[idx];
	}

	auto at(const size_type idx) noexcept -> node_type& {
		return vec_.at(idx);
	}

	auto at(const size_type idx) const noexcept -> const node_type& {
		return vec_.at(idx);
	}

	template <typename... Args>
	void emplace_back(Args&&... args) {
		vec_.emplace_back(std::move(args)...);
	}

	void add_node(const data_type& val) {
		vec_.emplace_back(val);
	}

	void add_node(data_type&& val) {
		vec_.emplace_back(std::move(val));
	}

	void add_node(const data_type& val, const size_type idx) {
		vec_[idx].add_child(length());
		vec_.emplace_back(val, vec_[idx].depth() + 1);
	}

	void add_node(data_type&& val, const size_type idx) {
		vec_[idx].add_child(length());
		vec_.emplace_back(std::move(val), vec_[idx].depth() + 1);
	}

	void remove_node(const size_type idx) {
		vec_[idx].erase(vec_.begin() + idx);
		for (auto it = vec_.begin(); it != vec_.end(); ++it) {
			std::remove(it->begin(), it->end(), idx);
		}
	}

	void pop_node() {
		vec_.pop_back();
		const auto idx = length().size();
		for (auto it = vec_.begin(); it != vec_.end(); ++it) {
			std::remove(it->begin(), it->end(), idx);
		}
	}

protected:
	std::vector<node_type> vec_;
};

}	 // namespace cui

#endif	  // CUI_NARY_TREE_HPP