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
        class IParameter;
        class ITransaction;
        class IDataReader;

        class ICommand : public boost::noncopyable
        {
        public:

            virtual ~ICommand() = default;

            virtual void BeginExecuteNonQuery(std::function<void(ICommand*, int)>) = 0;
            virtual void BeginExecuteReader(std::function<void(ICommand*, std::shared_ptr<IDataReader>)>) = 0;
            virtual void BeginExecuteScalar(std::function<void(ICommand*, std::vector<std::unordered_map<std::string, boost::any>>)>) = 0;

            virtual void Text(const std::string&) = 0;
            virtual std::string& Text() const = 0;
            virtual std::unordered_map<std::string, std::shared_ptr<IParameter>>& Parameters() const = 0;
            virtual void Transaction(std::shared_ptr<ITransaction>) = 0;
            virtual std::shared_ptr<ITransaction> Transaction() const = 0;

            virtual std::shared_ptr<IParameter> CreateParameter() = 0;
            virtual int ExecuteNonQuery() = 0;
            virtual std::shared_ptr<IDataReader> ExecuteReader() = 0;
            virtual std::vector<std::unordered_map<std::string, boost::any>> ExecuteScalar() = 0;
            virtual void Prepare() = 0;
        };
    }
}
