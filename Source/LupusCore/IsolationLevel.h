#pragma once

namespace Lupus {
    namespace Data {
        enum class IsolationLevel {
            Uncommitted,
            Committed,
            Repeatable,
            Serializable
        };
    }
}
