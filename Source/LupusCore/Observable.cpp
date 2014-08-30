#include "Observable.h"

using namespace std;

namespace Lupus {
    void ObservableObject::Remove(const string& propertyName)
    {
        mProperties.erase(propertyName);
    }

    bool ObservableObject::HasProperty(const string& propertyName) const
    {
        return (find_if(begin(mProperties), end(mProperties), [&](const pair<string, boost::any>& it) {
            return (it.first == propertyName);
        }) != end(mProperties));
    }

    boost::any& ObservableObject::operator[](const string& propertyName)
    {
        return mProperties.at(propertyName);
    }

    const boost::any& ObservableObject::operator[](const string& propertyName) const
    {
        return mProperties.at(propertyName);
    }
}
