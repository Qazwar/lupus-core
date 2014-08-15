#pragma once

#include <vector>
#include <string>
#include <memory>
#include <functional>
#include <unordered_map>
#include <boost/any.hpp>
#include <boost/noncopyable.hpp>

#include "Utility.h"
#include "Task.h"

namespace Lupus {
    namespace Data {
        class Parameter;
        class ITransaction;
        class IDataReader;

        class LUPUS_API Command : public boost::noncopyable
        {
        public:

            virtual ~Command() = default;

            virtual Task<int> ExecuteNonQueryAsync() NOEXCEPT;
            virtual Task<std::shared_ptr<IDataReader>> ExecuteReaderAsync() NOEXCEPT;
            virtual Task<std::vector<std::unordered_map<std::string, boost::any>>> ExecuteScalarAsync() NOEXCEPT;

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
