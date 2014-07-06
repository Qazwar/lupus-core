#pragma once

#include "IDatabase.h"

namespace StreamWolf {
    namespace Data {
        class PgDatabase : public IDatabase
        {
        public:

            virtual ~PgDatabase();
        };
    }
}
