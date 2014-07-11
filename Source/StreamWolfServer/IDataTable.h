#pragma once

#include <vector>
#include <string>
#include <memory>
#include <boost/noncopyable.hpp>

namespace StreamWolf {
    namespace Data {
        class IDataReader;
        class IDataColumn;
        class IDataRow;

        class IDataTable : public boost::noncopyable
        {
        public:

            virtual ~IDataTable() = default;

            virtual void Load(std::shared_ptr<IDataReader>) = 0;
            virtual std::vector<std::shared_ptr<IDataRow>> Rows() const = 0;
            virtual std::vector<std::shared_ptr<IDataColumn>> Columns() const = 0;
        };
    }
}
