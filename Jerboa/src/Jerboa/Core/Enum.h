
#include <type_traits>

namespace Jerboa
{
    /*
        Declare the following to enable operators for speicifc enum:
        template<>
        struct Jerboa::enum_operators<BufferClearBits> {
            static constexpr bool enableBitWiseOperators = true;
        };
    */
    template<typename E>
    struct enum_operator_enabler {
        static constexpr bool enableBitWiseOperators = false;
    };

    template<typename E, class = std::enable_if<enum_operator_enabler<E>::enableBitWiseOperators && std::is_enum<E>::value>::type>
    E operator|(E lhs, E rhs) {
        typedef typename std::underlying_type<E>::type underlying;
        return static_cast<E>(
            static_cast<underlying>(lhs)
            | static_cast<underlying>(rhs));
    }

    template<typename E, class = std::enable_if<enum_operator_enabler<E>::enableBitWiseOperators && std::is_enum<E>::value>::type>
    E operator&(E lhs, E rhs) {
        typedef typename std::underlying_type<E>::type underlying;
        return static_cast<E>(
            static_cast<underlying>(lhs)
            & static_cast<underlying>(rhs));
    }

    template<typename T, typename E, class = std::enable_if<std::is_enum<E>::value && std::is_integral<T>::value>::type>
    T EnumToInt(E arg)
    {
        return static_cast<T>(arg);
    }
}