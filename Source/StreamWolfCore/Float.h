#pragma once

#include <string>
#include "Utility.h"

namespace Lupus {
	//! provides conversion routines for floating-point numbers
    class SWC_API Float
	{
	public:
		/**
		 * convert a single precision floating-point numbers to a string
		 *
		 * @param f floating-point number
		 * @return conversion result as a string
		 */
		static std::string ToString(float f) NOEXCEPT;
		/**
	 	 * convert a double precision floating-point numbers to a string
 		 * 
		 * @param d double precision floating-point number
		 * @return conversion result as a string
		 */
        static std::string ToString(double d) NOEXCEPT;
		/**
		 * convert a 128-bit floating-point numbers to a string
		 *
		 * @param r 128-bit floating-point number
		 * @return conversion result as a string
		 */
        static std::string ToString(long double r) NOEXCEPT;
		/**
		 * convert a string to a single precision floating-point number
		 *
		 * @param string string for conversion
		 * @param result output argument for conversion
		 * @return true if successful, otherwise false
		 */
        static bool TryParse(const std::string& string, float& result) NOEXCEPT;
		/**
		 * convert a string to a double precision floating-point number
		 *
		 * @param string string for conversion
		 * @param result output argument for conversion
		 * @return true if successful, otherwise false
		 */
        static bool TryParse(const std::string& string, double& result) NOEXCEPT;
		/**
		 * convert a string to a 128-bit floating-point numbers
		 *
		 * @param string string for conversion
		 * @param result output argument for conversion
		 * @return true if successful, otherwise false
		 */
        static bool TryParse(const std::string& string, long double& result) NOEXCEPT;

        static float ParseFloat(const std::string&) throw(std::invalid_argument);
        static double ParseDouble(const std::string&) throw(std::invalid_argument);
        static long double ParseLongDouble(const std::string&) throw(std::invalid_argument);
	};
}
