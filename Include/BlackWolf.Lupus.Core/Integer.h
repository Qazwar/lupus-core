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
#include <cstdint>

namespace Lupus {
	//! Basis für die Ganzzahlkonversion.
	enum class IntegerBase {
		Octal,
		Decimal,
		Hexadecimal
	};

	//! Klasse für Ganzzahl konversionen.
    class LUPUSCORE_API Integer
	{
	public:
		//! \sa Integer::ToString(int, IntegerBase)
		static String ToString(S8 value, IntegerBase base = IntegerBase::Decimal) NOEXCEPT;
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
        static String ToString(U8 value, IntegerBase base = IntegerBase::Decimal) NOEXCEPT;
		//! \sa Integer::ToString(int, IntegerBase)
        static String ToString(unsigned short value, IntegerBase base = IntegerBase::Decimal) NOEXCEPT;
		//! \sa Integer::ToString(int, IntegerBase)
        static String ToString(unsigned int value, IntegerBase base = IntegerBase::Decimal) NOEXCEPT;
		//! \sa Integer::ToString(int, IntegerBase)
        static String ToString(unsigned long value, IntegerBase base = IntegerBase::Decimal) NOEXCEPT;
		//! \sa Integer::ToString(int, IntegerBase)
        static String ToString(unsigned long long value, IntegerBase base = IntegerBase::Decimal) NOEXCEPT;
		//! \sa Integer::TryParse(const String&, int, IntegerBase)
        static bool TryParse(const String& string, S8& result, IntegerBase base = IntegerBase::Decimal) NOEXCEPT;
		//! \sa Integer::TryParse(const String&, int, IntegerBase)
        static bool TryParse(const String& string, short& result, IntegerBase base = IntegerBase::Decimal) NOEXCEPT;
		/**
		 * Versucht eine Zeichenkette zu ihrer entsprechenden Ganzzahl zu 
		 * konvertieren.
		 *
		 * \param[in] String Zeichenkette die konvertiert werden soll.
		 * \param[out] result Variable in der das Ergebnis gespeichert wird.
		 * \param[in] base Basis der Ganzzahl (8, 10, 16)
		 * \returns TRUE wenn die Konvertierung erfolgreich war. 
         *          FALSE im Fehlerfall.
		 */
        static bool TryParse(const String& string, int& result, IntegerBase base = IntegerBase::Decimal) NOEXCEPT;
		//! \sa Integer::TryParse(const String&, int, IntegerBase)
        static bool TryParse(const String& string, long& result, IntegerBase base = IntegerBase::Decimal) NOEXCEPT;
		//! \sa Integer::TryParse(const String&, int, IntegerBase)
        static bool TryParse(const String& string, long long& result, IntegerBase base = IntegerBase::Decimal) NOEXCEPT;
		//! \sa Integer::TryParse(const String&, int, IntegerBase)
        static bool TryParse(const String& string, U8& result, IntegerBase base = IntegerBase::Decimal) NOEXCEPT;
		//! \sa Integer::TryParse(const String&, int, IntegerBase)
        static bool TryParse(const String& string, unsigned short& result, IntegerBase base = IntegerBase::Decimal) NOEXCEPT;
		//! \sa Integer::TryParse(const String&, int, IntegerBase)
        static bool TryParse(const String& string, unsigned int& result, IntegerBase base = IntegerBase::Decimal) NOEXCEPT;
		//! \sa Integer::TryParse(const String&, int, IntegerBase)
        static bool TryParse(const String& string, unsigned long& result, IntegerBase base = IntegerBase::Decimal) NOEXCEPT;
		//! \sa Integer::TryParse(const String&, int, IntegerBase)
        static bool TryParse(const String& string, unsigned long long& result, IntegerBase base = IntegerBase::Decimal) NOEXCEPT;

        static S8 ParseByte(const String& string, IntegerBase base = IntegerBase::Decimal) throw(InvalidArgument);
        static short ParseShort(const String& string, IntegerBase base = IntegerBase::Decimal) throw(InvalidArgument);
        static int ParseInt(const String& string, IntegerBase base = IntegerBase::Decimal) throw(InvalidArgument);
        static long ParseLong(const String& string, IntegerBase base = IntegerBase::Decimal) throw(InvalidArgument);
        static long long ParseLongLong(const String& string, IntegerBase base = IntegerBase::Decimal) throw(InvalidArgument);

        static U8 ParseUByte(const String& string, IntegerBase base = IntegerBase::Decimal) throw(InvalidArgument);
        static unsigned short ParseUShort(const String& string, IntegerBase base = IntegerBase::Decimal) throw(InvalidArgument);
        static unsigned int ParseUInt(const String& string, IntegerBase base = IntegerBase::Decimal) throw(InvalidArgument);
        static unsigned long ParseULong(const String& string, IntegerBase base = IntegerBase::Decimal) throw(InvalidArgument);
        static unsigned long long ParseULongLong(const String& string, IntegerBase base = IntegerBase::Decimal) throw(InvalidArgument);
	};
}
