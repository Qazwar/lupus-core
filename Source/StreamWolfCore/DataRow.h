#pragma once

#include <string>
#include <memory>
#include <unordered_map>
#include <boost/any.hpp>
#include <boost/noncopyable.hpp>

#include "Utility.h"

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4251)
#endif

namespace Lupus {
    namespace Data {
        class DataColumn;

        class SWC_API DataRow : public boost::noncopyable
        {
        public:

            explicit DataRow(std::unordered_map<std::string, boost::any>&);
            virtual ~DataRow() = default;

            virtual boost::any& operator[](unsigned) throw(std::out_of_range);
            virtual const boost::any& operator[](unsigned) const throw(std::out_of_range);

            virtual boost::any& operator[](const std::string&) throw(std::invalid_argument);
            virtual const boost::any& operator[](const std::string&) const throw(std::invalid_argument);

            virtual boost::any& operator[](std::shared_ptr<DataColumn>) throw(std::invalid_argument, null_pointer);
            virtual const boost::any& operator[](std::shared_ptr<DataColumn>) const throw(std::invalid_argument, null_pointer);

            virtual size_t Count() const NOEXCEPT;
            virtual bool IsEmpty() const NOEXCEPT;
            virtual std::unordered_map<std::string, boost::any> Items() const NOEXCEPT;

        private:

            std::unordered_map<std::string, boost::any> mItems;
            std::vector<boost::any*> mRefItems;
        };
    }
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif
