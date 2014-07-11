#pragma once

namespace StreamWolf {
    namespace Data {
        enum class IsolationLevel {
            Uncommitted,
            Committed,
            Repeatable,
            Serializable
        };
    }
}
