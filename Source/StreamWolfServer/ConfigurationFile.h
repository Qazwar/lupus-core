#pragma once

#include <boost/noncopyable.hpp>

#include <vector>
#include <string>
#include <unordered_map>

#include "../StreamWolfCore/Utility.h"

namespace StreamWolf {
    namespace Net {
        namespace Http {
            class Request;
            class Response;
        }
    }

    namespace Application {
        class ConfigurationFile : public boost::noncopyable
        {
        public:

            virtual ~ConfigurationFile() = default;

            virtual void Load(const std::string&) throw(io_error);
            virtual const std::unordered_map<std::string, std::vector<std::string>>& Options() const NOEXCEPT;

            virtual const std::vector<std::string>& operator[](const std::string&) const NOEXCEPT;

        private:

            std::unordered_map<std::string, std::vector<std::string>> mNodes;
        };
    }
}
