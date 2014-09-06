#include "Library.h"

using namespace std;

#ifdef _MSC_VER
#include <Windows.h>
#include "String.h"

namespace Lupus {
    namespace System {
        Library::~Library()
        {
            Unload();
        }

        void* Library::GetFunctionHandle(const String& name)
        {
            if (!mHandle) {
                return nullptr;
            }

            return force_cast<void*>(GetProcAddress(force_cast<HMODULE>(mHandle), name.ToUTF8().c_str()));
        }
        
        void Library::Load(const String& path)
        {
            if (!(mHandle = force_cast<uintptr_t>(LoadLibraryW(path.Data())))) {
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
