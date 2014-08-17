#include "Observable.h"

namespace Lupus {
    ObservableObject::~ObservableObject()
    {
        OnComplete();
    }

    ObservableObject::PropertyChangedEvent& ObservableObject::PropertyChanged()
    {
        return mPropertyChanged;
    }
}
