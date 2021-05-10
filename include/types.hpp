#ifndef QB_TYPES_HPP
#define QB_TYPES_HPP

#include <cstdint>

namespace qb {
    using uchar = unsigned char;
    using uint = unsigned int;
    using byte = uchar;

    using int8 = int8_t;
    using int16 = int16_t;
    using int32 = int32_t;
    using int64 = int64_t;

    using uint8 = uint8_t;
    using uint16 = uint16_t;
    using uint32 = uint32_t;
    using uint64 = uint64_t;

#ifndef INT32_MAX
    const int32 INT32_MAX = 2147483647;
#endif
#ifndef INT32_MIN
    const int32 INT32_MIN = -2147483648;
#endif
#ifndef INT64_MAX
    const int64 INT64_MAX = 9223372036854775807LL;
#endif
#ifndef INT64_MIN
    const int64 INT64_MIN = -9223372036854775808LL;
#endif
} 

#endif