#pragma once

#include <string>
#include "Utility.h"

namespace StreamWolf {
	//! conversion base for integer
	enum class IntegerBase {
		Octal,
		Decimal,
		Hexadecimal
	};

	//! conversion class for integer types
	class Integer
	{
	public:
		//! \sa Integer::ToString(int, IntegerBase)
		static std::string ToString(int8_t value, IntegerBase base = IntegerBase::Decimal);
		//! \sa Integer::ToString(int, IntegerBase)
		static std::string ToString(short value, IntegerBase base = IntegerBase::Decimal);
		/**
		 * convert an integer to its respective string
		 *
		 * @param value integer to convert
		 * @param base either octal, decimal or hexadecimal
		 * @return conversion result as a string
		 */
		static std::string ToString(int value, IntegerBase base = IntegerBase::Decimal);
		//! \sa Integer::ToString(int, IntegerBase)
		static std::string ToString(long value, IntegerBase base = IntegerBase::Decimal);
		//! \sa Integer::ToString(int, IntegerBase)
		static std::string ToString(long long value, IntegerBase base = IntegerBase::Decimal);
		//! \sa Integer::ToString(int, IntegerBase)
		static std::string ToString(uint8_t value, IntegerBase base = IntegerBase::Decimal);
		//! \sa Integer::ToString(int, IntegerBase)
		static std::string ToString(unsigned short value, IntegerBase base = IntegerBase::Decimal);
		//! \sa Integer::ToString(int, IntegerBase)
		static std::string ToString(unsigned int value, IntegerBase base = IntegerBase::Decimal);
		//! \sa Integer::ToString(int, IntegerBase)
		static std::string ToString(unsigned long value, IntegerBase base = IntegerBase::Decimal);
		//! \sa Integer::ToString(int, IntegerBase)
		static std::string ToString(unsigned long long value, IntegerBase base = IntegerBase::Decimal);
		//! \sa Integer::TryParse(std::string&, int, IntegerBase)
		static bool TryParse(const std::string& string, int8_t& result, IntegerBase base = IntegerBase::Decimal);
		//! \sa Integer::TryParse(std::string&, int, IntegerBase)
		static bool TryParse(const std::string& string, short& result, IntegerBase base = IntegerBase::Decimal);
		/**
		 * convert a string to its respective integer value
		 *
		 * @param string string to convert
		 * @param result output argument where the conversion result is written to
		 * @param base either octal, decimal or hexadecimal
		 * @return true if successful, otherwise false
		 */
		static bool TryParse(const std::string& string, int& result, IntegerBase base = IntegerBase::Decimal);
		//! \sa Integer::TryParse(std::string&, int, IntegerBase)
		static bool TryParse(const std::string& string, long& result, IntegerBase base = IntegerBase::Decimal);
		//! \sa Integer::TryParse(std::string&, int, IntegerBase)
		static bool TryParse(const std::string& string, long long& result, IntegerBase base = IntegerBase::Decimal);
		//! \sa Integer::TryParse(std::string&, int, IntegerBase)
		static bool TryParse(const std::string& string, uint8_t& result, IntegerBase base = IntegerBase::Decimal);
		//! \sa Integer::TryParse(std::string&, int, IntegerBase)
		static bool TryParse(const std::string& string, unsigned short& result, IntegerBase base = IntegerBase::Decimal);
		//! \sa Integer::TryParse(std::string&, int, IntegerBase)
		static bool TryParse(const std::string& string, unsigned int& result, IntegerBase base = IntegerBase::Decimal);
		//! \sa Integer::TryParse(std::string&, int, IntegerBase)
		static bool TryParse(const std::string& string, unsigned long& result, IntegerBase base = IntegerBase::Decimal);
		//! \sa Integer::TryParse(std::string&, int, IntegerBase)
		static bool TryParse(const std::string& string, unsigned long long& result, IntegerBase base = IntegerBase::Decimal);
	};
}
