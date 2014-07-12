#pragma once

#include <vector>
#include <string>
#include <memory>
#include <functional>
#include <unordered_map>
#include <boost/any.hpp>
#include <boost/noncopyable.hpp>

namespace StreamWolf {
    namespace Data {
        class Parameter;
        class ITransaction;
        class IDataReader;

        class ICommand : public boost::noncopyable
        {
        public:

            virtual ~ICommand() = default;

            virtual void ExecuteNonQueryAsync(std::function<void(ICommand*, int)>) = 0;
            virtual void ExecuteReaderAsync(std::function<void(ICommand*, std::shared_ptr<IDataReader>)>) = 0;
            virtual void ExecuteScalarAsync(std::function<void(ICommand*, const std::vector<std::unordered_map<std::string, boost::any>>&)>) = 0;

            virtual void Text(const std::string&) = 0;
            virtual std::string& Text() = 0;
            virtual const std::string& Text() const = 0;
            virtual std::vector<std::shared_ptr<Parameter>>& Parameters() = 0;
            virtual const std::vector<std::shared_ptr<Parameter>>& Parameters() const = 0;

            virtual std::shared_ptr<Parameter> CreateParameter() = 0;
            virtual int ExecuteNonQuery() = 0;
            virtual std::shared_ptr<IDataReader> ExecuteReader() = 0;
            virtual std::vector<std::unordered_map<std::string, boost::any>> ExecuteScalar() = 0;
            virtual bool Prepare() = 0;
        };
    }
}
