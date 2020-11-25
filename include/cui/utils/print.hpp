#ifndef CUI_PRINT_HPP
#define CUI_PRINT_HPP

#include <iostream>

namespace cui {

template <typename... Args>
void print(Args&&... args) {
	((std::cout << args << ' '), ...);
}

template <typename... Args>
void println(Args&&... args) {
	((std::cout << args << ' '), ...);
	std::cout << '\n';
}

}	 // namespace cui

#endif	  // CUI_PRINT_HPP