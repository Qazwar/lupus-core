/**
 * Copyright (C) 2014 David Wolf <d.wolf@live.at>
 *
 * This file is part of Lupus.
 * Lupus is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Lupus is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Lupus. If not, see <http://www.gnu.org/licenses/>.
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
