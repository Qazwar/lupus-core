#include "Library.h"

using namespace std;

#ifdef _MSC_VER
#include <Windows.h>

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

            return force_cast<void*>(GetProcAddress(force_cast<HMODULE>(mHandle), name.c_str()));
        }
        
        void Library::Load(const string& path)
        {
            if (!(mHandle = force_cast<uintptr_t>(LoadLibrary(path.c_str())))) {
                throw io_error();
            }
        }
        
        void Library::Unload()
        {
            if (mHandle) {
                FreeLibrary(force_cast<HMODULE>(mHandle));
                mHandle = 0;
            }
        }
    }
}
#endif
