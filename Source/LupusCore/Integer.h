#pragma once

#include "Utility.h"
#include <cstdint>

namespace Lupus {
	//! Basis für die Ganzzahlkonversion.
	enum class IntegerBase {
		Octal,
		Decimal,
		Hexadecimal
	};

	//! Klasse für Ganzzahl konversionen.
    class LUPUS_API Integer
	{
	public:
		//! \sa Integer::ToString(int, IntegerBase)
		static std::string ToString(int8_t value, IntegerBase base = IntegerBase::Decimal) NOEXCEPT;
		//! \sa Integer::ToString(int, IntegerBase)
        static std::string ToString(short value, IntegerBase base = IntegerBase::Decimal) NOEXCEPT;
		/**
		 * Konvertiert eine Ganzzahl zu ihrer entsprechenden Zeichenkette.
		 *
		 * \param[in] value Ganzzahl für die Konvertierung
		 * \param[in] base Basis der Ganzzahl (8, 10, 16)
		 * \returns Entsprechende Zeichenkette der Ganzzahl
		 */
        static std::string ToString(int value, IntegerBase base = IntegerBase::Decimal) NOEXCEPT;
		//! \sa Integer::ToString(int, IntegerBase)
        static std::string ToString(long value, IntegerBase base = IntegerBase::Decimal) NOEXCEPT;
		//! \sa Integer::ToString(int, IntegerBase)
        static std::string ToString(long long value, IntegerBase base = IntegerBase::Decimal) NOEXCEPT;
		//! \sa Integer::ToString(int, IntegerBase)
        static std::string ToString(uint8_t value, IntegerBase base = IntegerBase::Decimal) NOEXCEPT;
		//! \sa Integer::ToString(int, IntegerBase)
        static std::string ToString(unsigned short value, IntegerBase base = IntegerBase::Decimal) NOEXCEPT;
		//! \sa Integer::ToString(int, IntegerBase)
        static std::string ToString(unsigned int value, IntegerBase base = IntegerBase::Decimal) NOEXCEPT;
		//! \sa Integer::ToString(int, IntegerBase)
        static std::string ToString(unsigned long value, IntegerBase base = IntegerBase::Decimal) NOEXCEPT;
		//! \sa Integer::ToString(int, IntegerBase)
        static std::string ToString(unsigned long long value, IntegerBase base = IntegerBase::Decimal) NOEXCEPT;
		//! \sa Integer::TryParse(const std::string&, int, IntegerBase)
        static bool TryParse(const std::string& string, int8_t& result, IntegerBase base = IntegerBase::Decimal) NOEXCEPT;
		//! \sa Integer::TryParse(const std::string&, int, IntegerBase)
        static bool TryParse(const std::string& string, short& result, IntegerBase base = IntegerBase::Decimal) NOEXCEPT;
		/**
		 * Versucht eine Zeichenkette zu ihrer entsprechenden Ganzzahl zu 
		 * konvertieren.
		 *
		 * \param[in] string Zeichenkette die konvertiert werden soll.
		 * \param[out] result Variable in der das Ergebnis gespeichert wird.
		 * \param[in] base Basis der Ganzzahl (8, 10, 16)
		 * \returns TRUE wenn die Konvertierung erfolgreich war. 
					FALSE im Fehlerfall.
		 */
        static bool TryParse(const std::string& string, int& result, IntegerBase base = IntegerBase::Decimal) NOEXCEPT;
		//! \sa Integer::TryParse(const std::string&, int, IntegerBase)
        static bool TryParse(const std::string& string, long& result, IntegerBase base = IntegerBase::Decimal) NOEXCEPT;
		//! \sa Integer::TryParse(const std::string&, int, IntegerBase)
        static bool TryParse(const std::string& string, long long& result, IntegerBase base = IntegerBase::Decimal) NOEXCEPT;
		//! \sa Integer::TryParse(const std::string&, int, IntegerBase)
        static bool TryParse(const std::string& string, uint8_t& result, IntegerBase base = IntegerBase::Decimal) NOEXCEPT;
		//! \sa Integer::TryParse(const std::string&, int, IntegerBase)
        static bool TryParse(const std::string& string, unsigned short& result, IntegerBase base = IntegerBase::Decimal) NOEXCEPT;
		//! \sa Integer::TryParse(const std::string&, int, IntegerBase)
        static bool TryParse(const std::string& string, unsigned int& result, IntegerBase base = IntegerBase::Decimal) NOEXCEPT;
		//! \sa Integer::TryParse(const std::string&, int, IntegerBase)
        static bool TryParse(const std::string& string, unsigned long& result, IntegerBase base = IntegerBase::Decimal) NOEXCEPT;
		//! \sa Integer::TryParse(const std::string&, int, IntegerBase)
        static bool TryParse(const std::string& string, unsigned long long& result, IntegerBase base = IntegerBase::Decimal) NOEXCEPT;

        static int8_t ParseByte(const std::string& string, IntegerBase base = IntegerBase::Decimal) throw(std::invalid_argument);
        static short ParseShort(const std::string& string, IntegerBase base = IntegerBase::Decimal) throw(std::invalid_argument);
        static int ParseInt(const std::string& string, IntegerBase base = IntegerBase::Decimal) throw(std::invalid_argument);
        static long ParseLong(const std::string& string, IntegerBase base = IntegerBase::Decimal) throw(std::invalid_argument);
        static long long ParseLongLong(const std::string& string, IntegerBase base = IntegerBase::Decimal) throw(std::invalid_argument);

        static uint8_t ParseUByte(const std::string& string, IntegerBase base = IntegerBase::Decimal) throw(std::invalid_argument);
        static unsigned short ParseUShort(const std::string& string, IntegerBase base = IntegerBase::Decimal) throw(std::invalid_argument);
        static unsigned int ParseUInt(const std::string& string, IntegerBase base = IntegerBase::Decimal) throw(std::invalid_argument);
        static unsigned long ParseULong(const std::string& string, IntegerBase base = IntegerBase::Decimal) throw(std::invalid_argument);
        static unsigned long long ParseULongLong(const std::string& string, IntegerBase base = IntegerBase::Decimal) throw(std::invalid_argument);
	};
}
