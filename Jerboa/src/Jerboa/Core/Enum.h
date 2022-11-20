#pragma once
#include <type_traits>

namespace Jerboa
{
    // Enum Flag operator templates
    template<typename EnumType>
    struct enum_flag_operators {
        static constexpr bool enabled = false;
    };

    template<typename EnumType, class = std::enable_if<enum_flag_operators<EnumType>::enabled>::type>
    constexpr EnumType operator|(EnumType a, EnumType b) { return static_cast<EnumType>(static_cast<std::underlying_type<EnumType>::type>(a) | static_cast<std::underlying_type<EnumType>::type>(b)); }

    template<typename EnumType, class = std::enable_if<enum_flag_operators<EnumType>::enabled>::type>
    constexpr EnumType operator|=(EnumType a, EnumType b) { return a | b; }

    template<typename EnumType, class = std::enable_if<enum_flag_operators<EnumType>::enabled>::type>
    constexpr EnumType operator&(EnumType a, EnumType b) { return static_cast<EnumType>(static_cast<std::underlying_type<EnumType>::type>(a) & static_cast<std::underlying_type<EnumType>::type>(b)); }

    template<typename EnumType, class = std::enable_if<enum_flag_operators<EnumType>::enabled>::type>
    constexpr EnumType operator&=(EnumType a, EnumType b) { return a & b; }

    template<typename EnumType, class = std::enable_if<enum_flag_operators<EnumType>::enabled>::type>
    constexpr EnumType operator~(EnumType a) { return static_cast<EnumType>(~static_cast<std::underlying_type<EnumType>::type>(a)); }

    template<typename EnumType, class = std::enable_if<enum_flag_operators<EnumType>::enabled>::type>
    constexpr EnumType operator^(EnumType a, EnumType b) { return static_cast<EnumType>(static_cast<std::underlying_type<EnumType>::type>(a) ^ static_cast<std::underlying_type<EnumType>::type>(b)); }

    template<typename EnumType, class = std::enable_if<enum_flag_operators<EnumType>::enabled>::type>
    constexpr EnumType operator^=(EnumType a, EnumType b) { return a ^ b; }

    // Utility functions and macros
#define JERBOA_ENABLE_ENUM_FLAG_OPERATORS(EnumType) \
    static_assert(std::is_enum<EnumType>::value, "Type '" #EnumType "' is not an enum. JERBOA_ENABLE_ENUM_FLAG_OPERATORS() only accepts enums."); \
    template<> \
    struct Jerboa::enum_flag_operators<EnumType> { \
        static constexpr bool enabled = true; \
    };

    template<typename IntType, typename EnumType, class = std::enable_if<std::is_enum<EnumType>::value && std::is_integral<IntType>::value>::type>
    constexpr IntType EnumToInt(EnumType arg)
    {
        return static_cast<IntType>(arg);
    }

    template<typename EnumType, class = std::enable_if<std::is_enum<EnumType>::value>>
    constexpr typename std::underlying_type<EnumType>::type EnumToInt(EnumType arg)
    {
        return static_cast<typename std::underlying_type<EnumType>::type>(arg);
    }

    template<typename EnumType, typename IntType, class = std::enable_if<std::is_enum<EnumType>::value && std::is_integral<IntType>::value>::type>
    constexpr EnumType IntToEnum(IntType arg)
    {
        return static_cast<EnumType>(arg);
    }

    // JERBOA_ENABLE_ENUM_FLAG_OPERATORS(EnumType) must be declared in order to use this function
    template<typename EnumType, class = std::enable_if<enum_flag_operators<EnumType>::enabled>::type>
    constexpr bool EnumHasFlags(EnumType arg, EnumType flags)
    {
        return (arg & flags) == flags;
    }
}