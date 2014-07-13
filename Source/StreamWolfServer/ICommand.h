#pragma once

#include <vector>
#include <string>
#include <memory>
#include <functional>
#include <unordered_map>
#include <boost/any.hpp>
#include <boost/noncopyable.hpp>

#include "Utility.h"

namespace StreamWolf {
    namespace Data {
        class Parameter;
        class ITransaction;
        class IDataReader;

        class ICommand : public boost::noncopyable
        {
        public:

            virtual ~ICommand() = default;

            virtual void ExecuteNonQueryAsync(std::function<void(std::exception_ptr, int)>) NOEXCEPT = 0;
            virtual void ExecuteReaderAsync(std::function<void(std::exception_ptr, std::shared_ptr<IDataReader>)>) NOEXCEPT = 0;
            virtual void ExecuteScalarAsync(std::function<void(std::exception_ptr, const std::vector<std::unordered_map<std::string, boost::any>>&)>) NOEXCEPT = 0;

            virtual void Text(const std::string&) NOEXCEPT = 0;
            virtual std::string& Text() NOEXCEPT = 0;
            virtual const std::string& Text() const NOEXCEPT = 0;
            virtual std::vector<std::shared_ptr<Parameter>>& Parameters() NOEXCEPT = 0;
            virtual const std::vector<std::shared_ptr<Parameter>>& Parameters() const NOEXCEPT = 0;

            virtual std::shared_ptr<Parameter> CreateParameter() NOEXCEPT = 0;
            virtual int ExecuteNonQuery() throw(sql_error) = 0;
            virtual std::shared_ptr<IDataReader> ExecuteReader() throw(sql_error) = 0;
            virtual std::vector<std::unordered_map<std::string, boost::any>> ExecuteScalar() throw(sql_error) = 0;
            virtual bool Prepare() throw(sql_error) = 0;
        };
    }
}
