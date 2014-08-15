#pragma once

#include <string>
#include "Utility.h"

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
		static std::string ToString(float f) NOEXCEPT;
		/// \sa Float::ToString(float)
		static std::string ToString(double d) NOEXCEPT;
		/// \sa Float::ToString(float)
        static std::string ToString(long double r) NOEXCEPT;
		/**
		 * Versucht eine Zeichenkette in ihre entsprechende Gleitpunktzahl zu
		 * konvertieren.
		 *
		 * \param[in] string Zeichenkette die konvertiert werden soll.
		 * \param[out] result Variable in der das Ergebnis gespeichert wird.
		 * \returns TRUE wenn die Konvertierung erfolgreich war. FALSE im
		 *			Fehlerfall.
		 */
        static bool TryParse(const std::string& string, float& result) NOEXCEPT;
		/// \sa Float::TryParse(const std::string&, float&)
		static bool TryParse(const std::string& string, double& result) NOEXCEPT;
		/// \sa Float::TryParse(const std::string&, float&)
        static bool TryParse(const std::string& string, long double& result) NOEXCEPT;

        static float ParseFloat(const std::string&) throw(std::invalid_argument);
        static double ParseDouble(const std::string&) throw(std::invalid_argument);
        static long double ParseLongDouble(const std::string&) throw(std::invalid_argument);
	};
}
