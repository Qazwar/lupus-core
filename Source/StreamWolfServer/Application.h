#pragma once

#include <string>
#include <vector>

namespace StreamWolf {
    namespace Application {
        class Application
        {
        public:
            int Initialize(const std::vector<std::string>& args);
            int Execute();
            int Shutdown();
        };
    }
}
