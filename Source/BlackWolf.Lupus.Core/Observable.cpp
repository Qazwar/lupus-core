#include "Observable.h"

using namespace std;

namespace Lupus {
    void ObservableObject::Remove(const String& propertyName)
    {
        mProperties.erase(propertyName);
    }

    bool ObservableObject::HasProperty(const String& propertyName) const
    {
        return (find_if(begin(mProperties), end(mProperties), [&](const pair<String, boost::any>& it) {
            return (it.first == propertyName);
        }) != end(mProperties));
    }

    boost::any& ObservableObject::operator[](const String& propertyName)
    {
        return mProperties.at(propertyName);
    }

    const boost::any& ObservableObject::operator[](const String& propertyName) const
    {
        return mProperties.at(propertyName);
    }
}
