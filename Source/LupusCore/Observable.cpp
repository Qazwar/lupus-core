#include "Observable.h"

using namespace std;

namespace Lupus {
    ObservableObject::~ObservableObject()
    {
        OnComplete();
    }

    ObservableObject::PropertyChangedEventHandle& ObservableObject::PropertyChanged()
    {
        return mPropertyChanged;
    }

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
}
