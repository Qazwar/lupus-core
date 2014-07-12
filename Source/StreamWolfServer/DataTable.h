#pragma once

#include <vector>
#include <string>
#include <memory>
#include <boost/noncopyable.hpp>

namespace StreamWolf {
    namespace Data {
        class IDataReader;
        class DataColumn;
        class DataRow;

        class DataTable : public boost::noncopyable
        {
        public:

            virtual ~DataTable() = default;

            virtual void Load(std::shared_ptr<IDataReader>);
            virtual std::vector<std::shared_ptr<DataRow>> Rows() const;
            virtual size_t RowCount() const;
            virtual std::vector<std::shared_ptr<DataColumn>> Columns() const;
            virtual size_t ColumnCount() const;
            virtual std::vector<std::shared_ptr<DataRow>> Fetch(unsigned, unsigned) const;

        private:

            std::vector<std::shared_ptr<DataColumn>> mColumns;
            std::vector<std::shared_ptr<DataRow>> mRows;
        };
    }
}
