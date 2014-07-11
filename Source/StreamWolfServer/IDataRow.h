#pragma once

#include <vector>
#include <string>
#include <memory>
#include <boost/any.hpp>
#include <boost/noncopyable.hpp>

namespace StreamWolf {
    namespace Data {
        class IDataColumn;

        class IDataRow : public boost::noncopyable
        {
        public:

            virtual ~IDataRow() = default;

            virtual std::shared_ptr<boost::any> operator[](unsigned) const = 0;
            virtual std::shared_ptr<boost::any> operator[](const std::string&) const = 0;
            virtual std::shared_ptr<boost::any> operator[](std::shared_ptr<IDataColumn>) const = 0;

            virtual std::vector<std::shared_ptr<boost::any>> Items() const = 0;
        };
    }
}
