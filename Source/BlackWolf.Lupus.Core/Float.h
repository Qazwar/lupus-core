/**
 * Copyright (C) 2014 David Wolf <d.wolf@live.at>
 *
 * This file is part of Lupus.
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#pragma once

#include "String.h"

namespace Lupus {
	//! Klasse für die Konvertierung von Gleitpunktzahlen
    class LUPUSCORE_API Float
	{
	public:
		/**
		 * Konvertiert eine Gleitpunktzahl in ihre entsprechende Zeichenkette.
		 *
		 * \param[in] f Gleitpunktzahl.
		 * \returns Zeichenkette der Gleitpunktzahl.
		 */
		static String ToString(float f) NOEXCEPT;
		/// \sa Float::ToString(float)
		static String ToString(double d) NOEXCEPT;
		/// \sa Float::ToString(float)
        static String ToString(long double r) NOEXCEPT;
		/**
		 * Versucht eine Zeichenkette in ihre entsprechende Gleitpunktzahl zu
		 * konvertieren.
		 *
		 * \param[in] String Zeichenkette die konvertiert werden soll.
		 * \param[out] result Variable in der das Ergebnis gespeichert wird.
		 * \returns TRUE wenn die Konvertierung erfolgreich war. FALSE im
		 *			Fehlerfall.
		 */
        static bool TryParse(const String& string, float& result) NOEXCEPT;
		/// \sa Float::TryParse(const String&, float&)
		static bool TryParse(const String& string, double& result) NOEXCEPT;
		/// \sa Float::TryParse(const String&, float&)
        static bool TryParse(const String& string, long double& result) NOEXCEPT;

        static float ParseFloat(const String&) throw(std::invalid_argument);
        static double ParseDouble(const String&) throw(std::invalid_argument);
        static long double ParseLongDouble(const String&) throw(std::invalid_argument);
	};
}
