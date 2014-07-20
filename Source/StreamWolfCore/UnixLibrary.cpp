#include "Library.h"

using namespace std;

#ifndef _MSC_VER
#include <dlfcn.h>
#include <cstdio>

namespace Lupus {
    namespace System {
        Library::~Library()
        {
            Unload();
        }

        void* Library::GetFunctionHandle(const string& name)
        {
            if (!mHandle) {
                return nullptr;
            }

            return dlsym(force_cast<void*>(mHandle), name.c_str());
        }

        void Library::Load(const string& path)
        {
            if (!(mHandle = force_cast<uintptr_t>(dlopen(path.c_str(), RTLD_NOW)))) {
                throw io_error();
            }
        }

        void Library::Unload()
        {
            if (mHandle) {
                dlclose(force_cast<void*>(mHandle));
                mHandle = 0;
            }
        }
    }
}
#endif
