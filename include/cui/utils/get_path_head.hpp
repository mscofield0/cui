#ifndef CUI_GET_PATH_HEAD_HPP
#define CUI_GET_PATH_HEAD_HPP

#include <string>

namespace cui {

/// \brief Retrieves the path name (substring from the last '/' or '\' found)
/// \param path The path from which to retrieve the path head
/// \returns The path head
auto get_path_head(const std::string& path) -> std::string {
	const auto _1 = path.find_last_of('/');
	const auto _2 = path.find_last_of('\\');
	const auto idx = std::min(_1, _2);

	return path.substr(idx + 1);
}

}	 // namespace cui

#endif	  // CUI_GET_PATH_HEAD_HPP