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
#ifndef _MSC_VER
#include "Library.h"
#include <dlfcn.h>
#include <cstdio>

namespace Lupus {
    namespace System {
        Library::Library(String path)
        {
            if (!(mHandle = force_cast<uintptr_t>(dlopen(path.ToUTF8().c_str(), RTLD_NOW)))) {
                // TODO: Information eintragen sobald String::Format implementiert ist.
                throw io_error();
            }
        }

        Library::~Library()
        {
            if (mHandle) {
                dlclose(force_cast<void*>(mHandle));
                mHandle = 0;
            }
        }

        void* Library::GetFunctionHandle(String name)
        {
            if (!mHandle) {
                return nullptr;
            }

            return dlsym(force_cast<void*>(mHandle), name.ToUTF8().c_str());
        }
    }
}
#endif
