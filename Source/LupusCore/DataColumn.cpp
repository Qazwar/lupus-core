#include "DataColumn.h"

using namespace std;

namespace Lupus {
    namespace Data {
        DataColumn::DataColumn(const string& s, DataType t, int i)
        {
            mName = s;
            mType = t;
            mIndex = i;
        }

        string DataColumn::Name() const
        {
            return mName;
        }

        DataType DataColumn::Type() const
        {
            return mType;
        }

        int DataColumn::Index() const
        {
            return mIndex;
        }
    }
}
