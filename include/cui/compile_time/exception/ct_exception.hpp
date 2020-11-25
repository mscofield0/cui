#ifndef CUI_CT_EXCEPTION_HPP
#define CUI_CT_EXCEPTION_HPP

#include <exception>

#include <compile_time/format/format.hpp>

namespace cui::ct {

template <std::size_t BufferSize>
class CTException : public std::exception
{
public:
	explicit CTException(const Format<BufferSize>& formatted_str) : data_(formatted_str) {}

	virtual const char* what() const noexcept {
		return data_.get_str();
	}

private:
	Format<BufferSize> data_;
};

}	 // namespace cui::ct

#endif	  // CUI_CT_FMT_EXCEPTION_HPP