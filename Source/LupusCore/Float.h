#pragma once

#include "String.h"

namespace Lupus {
	//! Klasse für die Konvertierung von Gleitpunktzahlen
    class LUPUS_API Float
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
        static bool TryParse(const String& String, float& result) NOEXCEPT;
		/// \sa Float::TryParse(const String&, float&)
		static bool TryParse(const String& String, double& result) NOEXCEPT;
		/// \sa Float::TryParse(const String&, float&)
        static bool TryParse(const String& String, long double& result) NOEXCEPT;

        static float ParseFloat(const String&) throw(std::invalid_argument);
        static double ParseDouble(const String&) throw(std::invalid_argument);
        static long double ParseLongDouble(const String&) throw(std::invalid_argument);
	};
}
