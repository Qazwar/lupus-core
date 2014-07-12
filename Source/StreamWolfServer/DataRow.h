#pragma once

#include <string>
#include <memory>
#include <unordered_map>
#include <boost/any.hpp>
#include <boost/noncopyable.hpp>

namespace StreamWolf {
    namespace Data {
        class DataColumn;

        class DataRow : public boost::noncopyable
        {
        public:

            explicit DataRow(std::unordered_map<std::string, boost::any>&);
            virtual ~DataRow() = default;

            virtual boost::any& operator[](unsigned);
            virtual const boost::any& operator[](unsigned) const;

            virtual boost::any& operator[](const std::string&);
            virtual const boost::any& operator[](const std::string&) const;

            virtual boost::any& operator[](std::shared_ptr<DataColumn>);
            virtual const boost::any& operator[](std::shared_ptr<DataColumn>) const;

            virtual size_t Count() const;
            virtual bool IsEmpty() const;
            virtual std::unordered_map<std::string, boost::any> Items() const;

        private:

            std::unordered_map<std::string, boost::any> mItems;
            std::vector<boost::any*> mRefItems;
        };
    }
}
