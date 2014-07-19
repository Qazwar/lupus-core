#pragma once

#include <string>
#include <vector>
#include <cstdint>
#include <unordered_map>

namespace StreamWolf {
    namespace Application {
        class Application
        {
        public:

            int Initialize(int, char**);
            int Execute();
            int Shutdown();

        private:
            
            uint16_t mPort = 8080;
            bool mHttp = false;
        };
    }
}
