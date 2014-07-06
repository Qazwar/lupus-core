// StreamWolfLocale.cpp : Defines the exported functions for the DLL application.
//

#include "StreamWolfLocale.h"
#include <pugixml/pugixml.hpp>
#include <map>
#include <memory>
#include <atomic>

using namespace std;
using namespace pugi;

map<string, shared_ptr<xml_document>> gFileMap;
shared_ptr<xml_document> gFile;

#pragma comment(lib, "pugixml.lib")

// This is an example of an exported function.
STREAMWOLFLOCALE_API int StreamWolfLocaleInit()
{
    xml_parse_status status;

    /// Deutsch
    gFileMap["de-AT"] = make_shared<xml_document>();
    
    if ((status = gFileMap["de-AT"]->load_file("Locale/de-AT.xml").status) != xml_parse_status::status_ok) {
        return (int)status;
    }

    /// Englisch
    gFileMap["en-US"] = make_shared<xml_document>();

    if ((status = gFileMap["en-US"]->load_file("Locale/en-US.xml").status) != xml_parse_status::status_ok) {
        return (int)status;
    }

    return 0;
}

STREAMWOLFLOCALE_API int SetStreamWolfLocale(const std::string& l)
{
    auto it = gFileMap.find(l);

    if (it == end(gFileMap)) {
        return LOCALE_NOT_FOUND;
    }

    gFile = it->second;
    return 0;
}

STREAMWOLFLOCALE_API std::string GetString(const std::string& variable)
{
    return "";
}

STREAMWOLFLOCALE_API void StreamWolfLocaleQuit()
{
    for (auto& doc : gFileMap) {
        doc.second.reset();
    }
}
