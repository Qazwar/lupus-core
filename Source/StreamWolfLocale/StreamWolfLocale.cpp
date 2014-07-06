// StreamWolfLocale.cpp : Defines the exported functions for the DLL application.
//

#include "StreamWolfLocale.h"
#include <mutex>

using namespace std;
using namespace pugi;

#pragma comment(lib, "pugixml.lib")

StringTable::StringTable(const string& l)
{
    mFile = make_shared<xml_document>();
    mFile->load_file(l.c_str());
}

StringTable::~StringTable()
{
}

string StringTable::GetString(const std::string& variable) const
{
    return "";
}

STREAMWOLFLOCALE_API StringTablePtr GetStringTable(const string& locale)
{
    static mutex sMutex;
    static map<string, StringTablePtr> sTable;
    auto it = sTable.find(locale);

    if (it != end(sTable)) {
        return it->second;
    }

    lock_guard<mutex> lock(sMutex);
    sTable[locale] = make_shared<StringTable>("Locale/" + locale);
    return sTable[locale];
}
