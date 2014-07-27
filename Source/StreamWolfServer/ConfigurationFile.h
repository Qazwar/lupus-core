#pragma once

#include <boost/noncopyable.hpp>

#include <vector>
#include <string>
#include <unordered_map>

#include "../LupusCore/Utility.h"

namespace StreamWolf {
    namespace Application {
        class ConfigurationFile : public boost::noncopyable
        {
        public:

            virtual ~ConfigurationFile() = default;

            virtual void Load(const std::string&) throw(Lupus::io_error);
            virtual const std::unordered_map<std::string, std::vector<std::string>>& Options() const NOEXCEPT;

            virtual const std::vector<std::string>& operator[](const std::string&) NOEXCEPT;

        private:

            std::unordered_map<std::string, std::vector<std::string>> mNodes;
        };
    }
}
