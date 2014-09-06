#pragma once

#include "String.h"
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
		static String ToString(int8_t value, IntegerBase base = IntegerBase::Decimal) NOEXCEPT;
		//! \sa Integer::ToString(int, IntegerBase)
        static String ToString(short value, IntegerBase base = IntegerBase::Decimal) NOEXCEPT;
		/**
		 * Konvertiert eine Ganzzahl zu ihrer entsprechenden Zeichenkette.
		 *
		 * \param[in] value Ganzzahl für die Konvertierung
		 * \param[in] base Basis der Ganzzahl (8, 10, 16)
		 * \returns Entsprechende Zeichenkette der Ganzzahl
		 */
        static String ToString(int value, IntegerBase base = IntegerBase::Decimal) NOEXCEPT;
		//! \sa Integer::ToString(int, IntegerBase)
        static String ToString(long value, IntegerBase base = IntegerBase::Decimal) NOEXCEPT;
		//! \sa Integer::ToString(int, IntegerBase)
        static String ToString(long long value, IntegerBase base = IntegerBase::Decimal) NOEXCEPT;
		//! \sa Integer::ToString(int, IntegerBase)
        static String ToString(uint8_t value, IntegerBase base = IntegerBase::Decimal) NOEXCEPT;
		//! \sa Integer::ToString(int, IntegerBase)
        static String ToString(unsigned short value, IntegerBase base = IntegerBase::Decimal) NOEXCEPT;
		//! \sa Integer::ToString(int, IntegerBase)
        static String ToString(unsigned int value, IntegerBase base = IntegerBase::Decimal) NOEXCEPT;
		//! \sa Integer::ToString(int, IntegerBase)
        static String ToString(unsigned long value, IntegerBase base = IntegerBase::Decimal) NOEXCEPT;
		//! \sa Integer::ToString(int, IntegerBase)
        static String ToString(unsigned long long value, IntegerBase base = IntegerBase::Decimal) NOEXCEPT;
		//! \sa Integer::TryParse(const String&, int, IntegerBase)
        static bool TryParse(const String& String, int8_t& result, IntegerBase base = IntegerBase::Decimal) NOEXCEPT;
		//! \sa Integer::TryParse(const String&, int, IntegerBase)
        static bool TryParse(const String& String, short& result, IntegerBase base = IntegerBase::Decimal) NOEXCEPT;
		/**
		 * Versucht eine Zeichenkette zu ihrer entsprechenden Ganzzahl zu 
		 * konvertieren.
		 *
		 * \param[in] String Zeichenkette die konvertiert werden soll.
		 * \param[out] result Variable in der das Ergebnis gespeichert wird.
		 * \param[in] base Basis der Ganzzahl (8, 10, 16)
		 * \returns TRUE wenn die Konvertierung erfolgreich war. 
					FALSE im Fehlerfall.
		 */
        static bool TryParse(const String& String, int& result, IntegerBase base = IntegerBase::Decimal) NOEXCEPT;
		//! \sa Integer::TryParse(const String&, int, IntegerBase)
        static bool TryParse(const String& String, long& result, IntegerBase base = IntegerBase::Decimal) NOEXCEPT;
		//! \sa Integer::TryParse(const String&, int, IntegerBase)
        static bool TryParse(const String& String, long long& result, IntegerBase base = IntegerBase::Decimal) NOEXCEPT;
		//! \sa Integer::TryParse(const String&, int, IntegerBase)
        static bool TryParse(const String& String, uint8_t& result, IntegerBase base = IntegerBase::Decimal) NOEXCEPT;
		//! \sa Integer::TryParse(const String&, int, IntegerBase)
        static bool TryParse(const String& String, unsigned short& result, IntegerBase base = IntegerBase::Decimal) NOEXCEPT;
		//! \sa Integer::TryParse(const String&, int, IntegerBase)
        static bool TryParse(const String& String, unsigned int& result, IntegerBase base = IntegerBase::Decimal) NOEXCEPT;
		//! \sa Integer::TryParse(const String&, int, IntegerBase)
        static bool TryParse(const String& String, unsigned long& result, IntegerBase base = IntegerBase::Decimal) NOEXCEPT;
		//! \sa Integer::TryParse(const String&, int, IntegerBase)
        static bool TryParse(const String& String, unsigned long long& result, IntegerBase base = IntegerBase::Decimal) NOEXCEPT;

        static int8_t ParseByte(const String& String, IntegerBase base = IntegerBase::Decimal) throw(std::invalid_argument);
        static short ParseShort(const String& String, IntegerBase base = IntegerBase::Decimal) throw(std::invalid_argument);
        static int ParseInt(const String& String, IntegerBase base = IntegerBase::Decimal) throw(std::invalid_argument);
        static long ParseLong(const String& String, IntegerBase base = IntegerBase::Decimal) throw(std::invalid_argument);
        static long long ParseLongLong(const String& String, IntegerBase base = IntegerBase::Decimal) throw(std::invalid_argument);

        static uint8_t ParseUByte(const String& String, IntegerBase base = IntegerBase::Decimal) throw(std::invalid_argument);
        static unsigned short ParseUShort(const String& String, IntegerBase base = IntegerBase::Decimal) throw(std::invalid_argument);
        static unsigned int ParseUInt(const String& String, IntegerBase base = IntegerBase::Decimal) throw(std::invalid_argument);
        static unsigned long ParseULong(const String& String, IntegerBase base = IntegerBase::Decimal) throw(std::invalid_argument);
        static unsigned long long ParseULongLong(const String& String, IntegerBase base = IntegerBase::Decimal) throw(std::invalid_argument);
	};
}
