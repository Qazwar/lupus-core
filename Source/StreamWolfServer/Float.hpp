#pragma once

#include <string>

namespace StreamWolf {
	//! provides conversion routines for floating-point numbers
	class Float
	{
	public:
		/**
		 * convert a single precision floating-point numbers to a string
		 *
		 * @param f floating-point number
		 * @return conversion result as a string
		 */
		static std::string ToString(float f);
		/**
	 	 * convert a double precision floating-point numbers to a string
 		 * 
		 * @param d double precision floating-point number
		 * @return conversion result as a string
		 */
		static std::string ToString(double d);
		/**
		 * convert a 128-bit floating-point numbers to a string
		 *
		 * @param r 128-bit floating-point number
		 * @return conversion result as a string
		 */
		static std::string ToString(long double r);
		/**
		 * convert a string to a single precision floating-point number
		 *
		 * @param string string for conversion
		 * @param result output argument for conversion
		 * @return true if successful, otherwise false
		 */
		static bool TryParse(const std::string& string, float& result);
		/**
		 * convert a string to a double precision floating-point number
		 *
		 * @param string string for conversion
		 * @param result output argument for conversion
		 * @return true if successful, otherwise false
		 */
		static bool TryParse(const std::string& string, double& result);
		/**
		 * convert a string to a 128-bit floating-point numbers
		 *
		 * @param string string for conversion
		 * @param result output argument for conversion
		 * @return true if successful, otherwise false
		 */
		static bool TryParse(const std::string& string, long double& result);
	};
}
