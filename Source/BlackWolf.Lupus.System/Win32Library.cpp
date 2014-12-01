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
#ifdef _MSC_VER
#include "Library.h"
#include <Windows.h>

namespace Lupus {
    namespace System {
        Library::Library(String path)
        {
            if (!(mHandle = force_cast<uintptr_t>(LoadLibraryW(path.Data())))) {
                // TODO: Information eintragen sobald String::Format implementiert ist.
                throw IOError();
            }
        }

        Library::~Library()
        {
            if (mHandle) {
                FreeLibrary(force_cast<HMODULE>(mHandle));
                mHandle = 0;
            }
        }

        void* Library::GetFunctionHandle(String name)
        {
            if (!mHandle) {
                return nullptr;
            }

            return force_cast<void*>(GetProcAddress(force_cast<HMODULE>(mHandle), name.ToUTF8().c_str()));
        }
    }
}
#endif