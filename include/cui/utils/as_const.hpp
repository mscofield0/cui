#ifndef CUI_AS_CONST_HPP
#define CUI_AS_CONST_HPP

namespace cui {

/// \brief Converts an lvalue reference into a const qualified lvalue reference
/// \param v Value to constify
/// \returns A const qualified value
template <typename Type>
auto as_const(Type& v) noexcept -> const Type& {
	return v;
}

}	 // namespace cui

#endif	  // CUI_AS_CONST_HPP