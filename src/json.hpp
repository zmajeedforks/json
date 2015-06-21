/*!
@file
@copyright The code is licensed under the MIT License
           <http://opensource.org/licenses/MIT>,
           Copyright (c) 2013-2015 Niels Lohmann.
@author Niels Lohmann <http://nlohmann.me>
@see https://github.com/nlohmann/json
*/

#ifndef NLOHMANN_JSON_HPP
#define NLOHMANN_JSON_HPP

#include <algorithm>
#include <array>
#include <ciso646>
#include <cmath>
#include <cstdio>
#include <functional>
#include <initializer_list>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <limits>
#include <map>
#include <memory>
#include <sstream>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

// enable ssize_t on MinGW
#ifdef __GNUC__
    #ifdef __MINGW32__
        #include <sys/types.h>
    #endif
#endif

// enable ssize_t for MSVC
#ifdef _MSC_VER
    #include <basetsd.h>
    using ssize_t = SSIZE_T;
#endif

/*!
@brief namespace for Niels Lohmann
@see https://github.com/nlohmann
*/
namespace nlohmann
{


/// namespace with internal helper functions
namespace internals
{
// Helper to determine whether there's a key_type for T.
// http://stackoverflow.com/a/7728728/266378
template<typename T>
struct has_mapped_type
{
  private:
    template<typename C> static char test(typename C::mapped_type*);
    template<typename C> static int  test(...);
  public:
    enum { value = sizeof(test<T>(0)) == sizeof(char) };
};
}

/*!
@brief a class to store JSON values

@tparam ObjectType         type for JSON objects
                           (@c std::map by default)
@tparam ArrayType          type for JSON arrays
                           (@c std::vector by default)
@tparam StringType         type for JSON strings and object keys
                           (@c std::string by default)
@tparam BooleanType        type for JSON booleans
                           (@c bool by default)
@tparam NumberIntegerType  type for JSON integer numbers
                           (@c int64_t by default)
@tparam NumberFloatType    type for JSON floating-point numbers
                           (@c double by default)
@tparam AllocatorType      type of the allocator to use
                           (@c std::allocator by default)

@requirement This class satisfies the Container requirements (see http://en.cppreference.com/w/cpp/concept/Container):
- @ref basic_json()
- @ref basic_json(const basic_json&)
- @ref reference& operator=(basic_json)
- @ref ~basic_json()
- @ref iterator begin(), @ref const_iterator begin(), @ref const_iterator cbegin()
- @ref iterator end(), @ref const_iterator end(), @ref const_iterator cend()
- @ref bool operator==(const_reference, const_reference), @ref bool operator!=(const_reference, const_reference)
- @ref void swap(reference other)
- @ref size_type size(), @ref size_type max_size()
- @ref bool empty()

@note ObjectType trick from http://stackoverflow.com/a/9860911

@see RFC 7159 <http://rfc7159.net/rfc7159>
@see ECMA 404 <http://www.ecma-international.org/publications/standards/Ecma-404.htm>
*/
template <
    template<typename U, typename V, typename... Args> class ObjectType = std::map,
    template<typename U, typename... Args> class ArrayType = std::vector,
    class StringType = std::string,
    class BooleanType = bool,
    class NumberIntegerType = int64_t,
    class NumberFloatType = double,
    template<typename U> class AllocatorType = std::allocator
    >
class basic_json
{
  public:
    /////////////////////
    // container types //
    /////////////////////

    /// @name container types
    /// @{

    using __basic_json =
        basic_json<ObjectType, ArrayType, StringType, BooleanType, NumberIntegerType, NumberFloatType, AllocatorType>;

    /// the type of elements in a basic_json container
    using value_type = basic_json;

    /// the type of an element reference
    using reference = value_type&;

    /// the type of an element const reference
    using const_reference = const value_type&;

    /// a type to represent differences between iterators
    using difference_type = std::ptrdiff_t;

    /// a type to represent container sizes
    using size_type = std::size_t;

    /// the allocator type
    using allocator_type = AllocatorType<basic_json>;

    /// the type of an element pointer
    using pointer = typename std::allocator_traits<allocator_type>::pointer;
    /// the type of an element const pointer
    using const_pointer = typename std::allocator_traits<allocator_type>::const_pointer;

    /// an iterator for a basic_json container
    class iterator;
    /// a const iterator for a basic_json container
    class const_iterator;
    /// a reverse iterator for a basic_json container
    class reverse_iterator;
    /// a const reverse iterator for a basic_json container
    class const_reverse_iterator;

    /// @}


    /*!
    @brief returns the allocator associated with the container
    */
    static allocator_type get_allocator()
    {
        return allocator_type();
    }


    ///////////////////////////
    // JSON value data types //
    ///////////////////////////

    /// @name JSON value data types
    /// @{

    /// a type for an object
    using object_t =
        ObjectType<StringType, basic_json, std::less<StringType>, AllocatorType<std::pair<const StringType, basic_json>>>;
    /// a type for an array
    using array_t = ArrayType<basic_json, AllocatorType<basic_json>>;
    /// a type for a string
    using string_t = StringType;
    /// a type for a boolean
    using boolean_t = BooleanType;
    /// a type for a number (integer)
    using number_integer_t = NumberIntegerType;
    /// a type for a number (floating-point)
    using number_float_t = NumberFloatType;
    /// a type for list initialization
    using list_init_t = std::initializer_list<basic_json>;

    /// @}


    /////////////////////////////////
    // JSON value type enumeration //
    /////////////////////////////////

    /*!
    @brief the JSON value type enumeration

    This enumeration collects the different JSON value types. It is used to
    distinguish the stored values in the union @ref json_value.
    */
    enum class value_t : uint8_t
    {
        null,           ///< null value
        object,         ///< object (unordered set of name/value pairs)
        array,          ///< array (ordered collection of values)
        string,         ///< string value
        boolean,        ///< boolean value
        number_integer, ///< number value (integer)
        number_float,   ///< number value (floating-point)
        discarded       ///< (internal) indicates the parser callback chose not to keep the value
    };


    ////////////////////////
    // JSON value storage //
    ////////////////////////

    /// a JSON value
    union json_value
    {
        /// object (stored with pointer to save storage)
        object_t* object;
        /// array (stored with pointer to save storage)
        array_t* array;
        /// string (stored with pointer to save storage)
        string_t* string;
        /// boolean
        boolean_t boolean;
        /// number (integer)
        number_integer_t number_integer;
        /// number (floating-point)
        number_float_t number_float;

        /// default constructor (for null values)
        json_value() noexcept = default;
        /// constructor for booleans
        json_value(boolean_t v) noexcept : boolean(v) {}
        /// constructor for numbers (integer)
        json_value(number_integer_t v) noexcept : number_integer(v) {}
        /// constructor for numbers (floating-point)
        json_value(number_float_t v) noexcept : number_float(v) {}
        /// constructor for empty values of a given type
        json_value(value_t t)
        {
            switch (t)
            {
                case (value_t::null):
                case (value_t::discarded):
                {
                    break;
                }

                case (value_t::object):
                {
                    AllocatorType<object_t> alloc;
                    object = alloc.allocate(1);
                    alloc.construct(object);
                    break;
                }

                case (value_t::array):
                {
                    AllocatorType<array_t> alloc;
                    array = alloc.allocate(1);
                    alloc.construct(array);
                    break;
                }

                case (value_t::string):
                {
                    AllocatorType<string_t> alloc;
                    string = alloc.allocate(1);
                    alloc.construct(string, "");
                    break;
                }

                case (value_t::boolean):
                {
                    boolean = boolean_t(false);
                    break;
                }

                case (value_t::number_integer):
                {
                    number_integer = number_integer_t(0);
                    break;
                }

                case (value_t::number_float):
                {
                    number_float = number_float_t(0.0);
                    break;
                }
            }
        }

        /// constructor for strings
        json_value(const string_t& value)
        {
            AllocatorType<string_t> alloc;
            string = alloc.allocate(1);
            alloc.construct(string, value);
        }

        /// constructor for objects
        json_value(const object_t& value)
        {
            AllocatorType<object_t> alloc;
            object = alloc.allocate(1);
            alloc.construct(object, value);
        }

        /// constructor for arrays
        json_value(const array_t& value)
        {
            AllocatorType<array_t> alloc;
            array = alloc.allocate(1);
            alloc.construct(array, value);
        }
    };

    //////////////////////////
    // JSON parser callback //
    //////////////////////////

    /// JSON callback event enumeration
    enum class parse_event_t : uint8_t
    {
        object_start,  ///< start an object scope (found a '{' token)
        object_end,    ///< end of an object scope (found '}' token)
        array_start,   ///< start of an array scope (found '[' token)
        array_end,     ///< end of an array scope (found ']' token)
        key,           ///< found an object key within an object scope
        value          ///< a value in an appropriate context (i.e., following a tag in an object scope)
    };

    /// per-element parser callback type
    using parser_callback_t = std::function<bool(int depth, parse_event_t event,
                              const basic_json& parsed)>;

    /*!
    @brief comparison operator for JSON value types

    Returns an ordering that is similar to Python:
    - order: null < boolean < number < object < array < string
    - furthermore, each type is not smaller than itself
    */
    friend bool operator<(const value_t lhs, const value_t rhs)
    {
        static constexpr std::array<uint8_t, 7> order = {{
                0, // null
                3, // object
                4, // array
                5, // string
                1, // boolean
                2, // integer
                2  // float
            }
        };

        // discarded values are not comparable
        if (lhs == value_t::discarded or rhs == value_t::discarded)
        {
            return false;
        }

        return order[static_cast<std::size_t>(lhs)] < order[static_cast<std::size_t>(rhs)];
    }


    //////////////////
    // constructors //
    //////////////////

    /*!
    @brief create an empty value with a given type

    Create an empty JSON value with a given type. The value will be default
    initialized with an empty value which depends on the type:

    Value type  | initial value
    ----------- | -------------
    null        | `null`
    boolean     | `false`
    string      | `""`
    number      | `0`
    object      | `{}`
    array       | `[]`

    @param value  the type of the value to create

    @complexity Constant.

    @exception std::bad_alloc if allocation for object, array, or string value
    fails (thrown by the constructors of @ref json_value)

    @liveexample{The following code shows the constructor for different @ref
    value_t values,basic_json__value_t}
    */
    basic_json(const value_t value)
        : m_type(value), m_value(value)
    {}

    /*!
    @brief create a null object (implicitly)

    Create a `null` JSON value. This is the implicit version of the `null`
    value constructor as it takes no parameters.

    @complexity Constant.

    @requirement This function satisfies the Container requirements:
    - The complexity is constant.
    - As postcondition, it holds: `basic_json().empty() == true`.

    @liveexample{The following code shows the constructor for a `null` JSON
    value.,basic_json}

    @sa basic_json(std::nullptr_t)
    @ingroup container
    */
    basic_json() noexcept = default;

    /*!
    @brief create a null object (explicitly)

    Create a `null` JSON value. This is the explicitly version of the `null`
    value constructor as it takes a null pointer as parameter. It allows to
    create `null` values by explicitly assigning a @c nullptr to a JSON value.
    The passed null pointer itself is not read - it is only used to choose the
    right constructor.

    @complexity Constant.

    @liveexample{The following code shows the constructor with null pointer
    parameter.,basic_json__nullptr_t}

    @sa basic_json()
    */
    basic_json(std::nullptr_t) noexcept
        : basic_json(value_t::null)
    {}

    /*!
    @brief create an object (explicit)

    Create an object JSON value with a given content.

    @param value  a value for the object

    @complexity Linear in the size of the passed @a value.

    @exception std::bad_alloc if allocation for object value fails (thrown by
    the constructor of @ref json_value)

    @liveexample{The following code shows the constructor with an @ref object_t
    parameter.,basic_json__object_t}

    @sa basic_json(const CompatibleObjectType&)
    */
    basic_json(const object_t& value)
        : m_type(value_t::object), m_value(value)
    {}

    /*!
    @brief create an object (implicit)

    Create an object JSON value with a given content. This constructor allows
    any type that can be used to construct values of type @ref object_t.
    Examples include the types `std::map` and `std::unordered_map`.

    @tparam CompatibleObjectType an object type whose `key_type` and
    `value_type` is compatible to @ref object_t

    @param value  a value for the object

    @complexity Linear in the size of the passed @a value.

    @exception std::bad_alloc if allocation for object value fails (thrown by
    the constructor of @ref json_value)

    @liveexample{The following code shows the constructor with several
    compatible object type parameters.,basic_json__CompatibleObjectType}

    @sa basic_json(const object_t&)
    */
    template <class CompatibleObjectType, typename
              std::enable_if<
                  std::is_constructible<typename object_t::key_type, typename CompatibleObjectType::key_type>::value and
                  std::is_constructible<basic_json, typename CompatibleObjectType::mapped_type>::value, int>::type
              = 0>
    basic_json(const CompatibleObjectType& value)
        : m_type(value_t::object)
    {
        AllocatorType<object_t> alloc;
        m_value.object = alloc.allocate(1);
        using std::begin;
        using std::end;
        alloc.construct(m_value.object, begin(value), end(value));
    }

    /*!
    @brief create an array (explicit)

    Create an array JSON value with a given content.

    @param value  a value for the array

    @complexity Linear in the size of the passed @a value.

    @exception std::bad_alloc if allocation for array value fails (thrown by
    the constructor of @ref json_value)

    @liveexample{The following code shows the constructor with an @ref array_t
    parameter.,basic_json__array_t}

    @sa basic_json(const CompatibleArrayType&)
    */
    basic_json(const array_t& value)
        : m_type(value_t::array), m_value(value)
    {}

    /*!
    @brief create an array (implicit)

    Create an array JSON value with a given content. This constructor allows
    any type that can be used to construct values of type @ref array_t.
    Examples include the types `std::vector`, `std::list`, and `std::set`.

    @tparam CompatibleArrayType an object type whose `value_type` is compatible
    to @ref array_t

    @param value  a value for the array

    @complexity Linear in the size of the passed @a value.

    @exception std::bad_alloc if allocation for array value fails (thrown by
    the constructor of @ref json_value)

    @liveexample{The following code shows the constructor with several
    compatible array type parameters.,basic_json__CompatibleArrayType}

    @sa basic_json(const array_t&)
    */
    template <class CompatibleArrayType, typename
              std::enable_if<
                  not std::is_same<CompatibleArrayType, typename __basic_json::iterator>::value and
                  not std::is_same<CompatibleArrayType, typename __basic_json::const_iterator>::value and
                  not std::is_same<CompatibleArrayType, typename __basic_json::reverse_iterator>::value and
                  not std::is_same<CompatibleArrayType, typename __basic_json::const_reverse_iterator>::value and
                  not std::is_same<CompatibleArrayType, typename array_t::iterator>::value and
                  not std::is_same<CompatibleArrayType, typename array_t::const_iterator>::value and
                  std::is_constructible<basic_json, typename CompatibleArrayType::value_type>::value, int>::type
              = 0>
    basic_json(const CompatibleArrayType& value)
        : m_type(value_t::array)
    {
        AllocatorType<array_t> alloc;
        m_value.array = alloc.allocate(1);
        using std::begin;
        using std::end;
        alloc.construct(m_value.array, begin(value), end(value));
    }

    /// create a string (explicit)
    basic_json(const string_t& value)
        : m_type(value_t::string), m_value(value)
    {}

    /// create a string (explicit)
    basic_json(const typename string_t::value_type* value)
        : basic_json(string_t(value))
    {}

    /// create a string (implicit)
    template <class V, typename
              std::enable_if<
                  std::is_constructible<string_t, V>::value, int>::type
              = 0>
    basic_json(const V& value)
        : basic_json(string_t(value))
    {}

    /// create a boolean (explicit)
    basic_json(boolean_t value)
        : m_type(value_t::boolean), m_value(value)
    {}

    /*!
    @brief create an integer number (explicit)

    @tparam T  helper type to compare number_integer_t and int
    @param value  an integer to create a JSON number from

    This constructor takes care about explicitly passed values of type
    number_integer_t. However, this constructor would have the same signature
    as the existing one for const int values, so we need to switch this one off
    in case number_integer_t is the same as int.
    */
    template<typename T,
             typename std::enable_if<
                 not (std::is_same<T, int>::value)
                 and std::is_same<T, number_integer_t>::value
                 , int>::type = 0>
    basic_json(const number_integer_t value)
        : m_type(value_t::number_integer), m_value(value)
    {}

    /*!
    @brief create an int number to support enum type (implicit)

    @param value  an integer to create a JSON number from

    This constructor allows to pass enums directly to a constructor. As C++ has
    no way of specifying the type of an anonymous enum explicitly, we can only
    rely on the fact that such values implicitly convert to int. As int may
    already be the same type of number_integer_t, we may need to switch off
    that constructor, which is done above.
    */
    basic_json(const int value)
        : m_type(value_t::number_integer),
          m_value(static_cast<number_integer_t>(value))
    {}

    /// create an integer number (implicit)
    template<typename T, typename
             std::enable_if<
                 std::is_constructible<number_integer_t, T>::value and
                 std::numeric_limits<T>::is_integer, T>::type
             = 0>
    basic_json(const T value) noexcept
        : m_type(value_t::number_integer),
          m_value(static_cast<number_integer_t>(value))
    {}

    /// create a floating-point number (explicit)
    basic_json(const number_float_t value)
        : m_type(value_t::number_float), m_value(value)
    {
        // replace infinity and NAN by null
        if (not std::isfinite(value))
        {
            m_type = value_t::null;
            m_value = json_value();
        }
    }

    /// create a floating-point number (implicit)
    template<typename T, typename = typename
             std::enable_if<
                 std::is_constructible<number_float_t, T>::value and
                 std::is_floating_point<T>::value>::type
             >
    basic_json(const T value) noexcept
        : basic_json(number_float_t(value))
    {}

    /*!
    @brief create a container (array or object) from an initializer list

    Creates a JSON value of type array or object from the passed initializer
    list @a init. In case @a type_deduction is `true` (default), the type of
    the JSON value to be created is deducted from the initializer list @a init
    according to the following rules:

    1. If the list is empty, an empty JSON object value `{}` is created.
    2. If the list consists of pairs whose first element is a string, a JSON
    object value is created where the first elements of the pairs are treated
    as keys and the second elements are as values.
    3. In all other cases, an array is created.

    The rules aim to create the best fit between a C++ initializer list and
    JSON values. The ratioinale is as follows:

    1. The empty initializer list is written as `{}` which is exactly an empty
    JSON object.
    2. C++ has now way of describing mapped types other than to list a list of
    pairs. As JSON requires that keys must be of type string, rule 2 is the
    weakest constraint one can pose on initializer lists to interpret them as
    an object.
    3. In all other cases, the initializer list could not be interpreted as
    JSON object type, so interpreting it as JSON array type is safe.

    With the rules described above, the following JSON values cannot be expressed by an initializer list:

    - the empty array (`[]`): use @ref array(list_init_t) with an empty
      initializer list in this case
    - arrays whose elements satisfy rule 2: use @ref array(list_init_t) with
      the same initializer list in this case

    @note When used without parentheses around an empty initializer list, @ref
    basic_json() is called instead of this function, yielding the JSON null
    value.

    @param init  initializer list with JSON values

    @param type_deduction  internal parameter; when set to `true`, the type of
    the JSON value is deducted from the initializer list @a init; when set to
    `false`, the type provided via @a manual_type is forced. This mode is used
    by the functions @ref array(list_init_t) and @ref object(list_init_t).

    @param manual_type  internal parameter; when @a type_deduction is set to
    `false`, the created JSON value will use the provided type (only @ref
    value_t::array and @ref value_t::object are valid); when @a type_deduction
    is set to `true`, this parameter has no effect

    @throw std::domain_error if @a type_deduction is `false`, @a manual_type is
    `value_t::object`, but @a init contains an element which is not a pair
    whose first element is a string

    @complexity Linear in the size of the initializer list @a init.

    @liveexample{The example below shows how JSON values are created from
    initializer lists,basic_json__list_init_t}

    @sa basic_json array(list_init_t) - create a JSON array value from an
    initializer list
    @sa basic_json object(list_init_t) - create a JSON object value from an
    initializer list
    */
    basic_json(list_init_t init, bool type_deduction = true,
               value_t manual_type = value_t::array)
    {
        // the initializer list could describe an object
        bool is_object = true;

        // check if each element is an array with two elements whose first element
        // is a string
        for (const auto& element : init)
        {
            if (element.m_type != value_t::array or element.size() != 2
                    or element[0].m_type != value_t::string)
            {
                // we found an element that makes it impossible to use the
                // initializer list as object
                is_object = false;
                break;
            }
        }

        // adjust type if type deduction is not wanted
        if (not type_deduction)
        {
            // if array is wanted, do not create an object though possible
            if (manual_type == value_t::array)
            {
                is_object = false;
            }

            // if object is wanted but impossible, throw an exception
            if (manual_type == value_t::object and not is_object)
            {
                throw std::domain_error("cannot create object from initializer list");
            }
        }

        if (is_object)
        {
            // the initializer list is a list of pairs -> create object
            m_type = value_t::object;
            m_value = value_t::object;

            for (auto& element : init)
            {
                m_value.object->emplace(std::move(*(element[0].m_value.string)), std::move(element[1]));
            }
        }
        else
        {
            // the initializer list describes an array -> create array
            m_type = value_t::array;
            AllocatorType<array_t> alloc;
            m_value.array = alloc.allocate(1);
            alloc.construct(m_value.array, std::move(init));
        }
    }

    /*!
    @brief explicitly create an array from an initializer list

    Creates a JSON array value from a given initializer list. That is, given a
    list of values `a, b, c`, creates the JSON value `[a, b, c]`. If the
    initializer list is empty, the empty array `[]` is created.

    @note This function is only needed to express two edge cases that cannot be
    realized with the initializer list constructor (@ref
    basic_json(list_init_t, bool, value_t)). These cases are:
    1. creating an array whose elements are all pairs whose first element is a
    string - in this case, the initializer list constructor would create an
    object, taking the first elements as keys
    2. creating an empty array - passing the empty initializer list to the
    initializer list constructor yields an empty object

    @param init  initializer list with JSON values to create an array from
    (optional)

    @return JSON array value

    @complexity Linear in the size of @a init.

    @liveexample{The following code shows an example for the @ref array
    function.,array}

    @sa basic_json(list_init_t, bool, value_t) - create a JSON value from an
    initializer list
    @sa basic_json object(list_init_t) - create a JSON object value from an
    initializer list
    */
    static basic_json array(list_init_t init = list_init_t())
    {
        return basic_json(init, false, value_t::array);
    }

    /*!
    @brief explicitly create an object from an initializer list

    Creates a JSON object value from a given initializer list. The initializer
    lists elements must be pairs, and their first elments must be strings. If
    the initializer list is empty, the empty object `{}` is created.

    @note This function is only added for symmetry reasons. In contrast to the
    related function @ref basic_json array(list_init_t), there are no cases
    which can only be expressed by this function. That is, any initializer list
    @a init can also be passed to the initializer list constructor @ref
    basic_json(list_init_t, bool, value_t).

    @param init  initializer list to create an object from (optional)

    @return JSON object value

    @throw std::domain_error if @a init is not a pair whose first elements are
    strings; thrown by @ref basic_json(list_init_t, bool, value_t)

    @complexity Linear in the size of @a init.

    @liveexample{The following code shows an example for the @ref object
    function.,object}

    @sa basic_json(list_init_t, bool, value_t) - create a JSON value from an
    initializer list
    @sa basic_json array(list_init_t) - create a JSON array value from an
    initializer list
    */
    static basic_json object(list_init_t init = list_init_t())
    {
        return basic_json(init, false, value_t::object);
    }

    /*!
    @brief construct an array with count copies of given value

    Constructs a JSON array value by creating @a count copies of a passed
    value. In case @a count is `0`, an empty array is created. As postcondition,
    `std::distance(begin(),end()) == count` holds.

    @param count  the number of JSON copies of @a value to create
    @param value  the JSON value to copy

    @complexity Linear in @a count.

    @liveexample{The following code shows examples for the @ref
    basic_json(size_type\, const basic_json&)
    constructor.,basic_json__size_type_basic_json}
    */
    basic_json(size_type count, const basic_json& value)
        : m_type(value_t::array)
    {
        AllocatorType<array_t> alloc;
        m_value.array = alloc.allocate(1);
        alloc.construct(m_value.array, count, value);
    }

    /// construct a JSON container given an iterator range
    template <class T, typename
              std::enable_if<
                  std::is_same<T, typename __basic_json::iterator>::value or
                  std::is_same<T, typename __basic_json::const_iterator>::value
                  , int>::type
              = 0>
    basic_json(T first, T last)
    {
        // make sure iterator fits the current value
        if (first.m_object != last.m_object or
                first.m_object->m_type != last.m_object->m_type)
        {
            throw std::domain_error("iterators are not compatible");
        }

        // set the type
        m_type = first.m_object->m_type;

        // check if iterator range is complete for non-compound values
        switch (m_type)
        {
            case value_t::number_integer:
            case value_t::number_float:
            case value_t::boolean:
            case value_t::string:
            {
                if (first.m_it.generic_iterator != 0 or last.m_it.generic_iterator != 1)
                {
                    throw std::out_of_range("iterators out of range");
                }
                break;
            }

            default:
            {
                break;
            }
        }

        switch (m_type)
        {
            case value_t::number_integer:
            {
                m_value.number_integer = first.m_object->m_value.number_integer;
                break;
            }

            case value_t::number_float:
            {
                m_value.number_float = first.m_object->m_value.number_float;
                break;
            }

            case value_t::boolean:
            {
                m_value.boolean = first.m_object->m_value.boolean;
                break;
            }

            case value_t::string:
            {
                m_value = *first.m_object->m_value.string;
                break;
            }

            case value_t::object:
            {
                AllocatorType<object_t> alloc;
                m_value.object = alloc.allocate(1);
                alloc.construct(m_value.object, first.m_it.object_iterator, last.m_it.object_iterator);
                break;
            }

            case value_t::array:
            {
                AllocatorType<array_t> alloc;
                m_value.array = alloc.allocate(1);
                alloc.construct(m_value.array, first.m_it.array_iterator, last.m_it.array_iterator);
                break;
            }

            default:
            {
                throw std::domain_error("cannot use construct with iterators from " + first.m_object->type_name());
            }
        }
    }

    ///////////////////////////////////////
    // other constructors and destructor //
    ///////////////////////////////////////

    /*!
    @brief copy constructor

    Creates a copy of a given JSON value.

    @param other  the JSON value to copy

    @complexity Linear in the size of @a other.

    @requirement This function satisfies the Container requirements:
    - The complexity is linear.
    - As postcondition, it holds: `other == basic_json(other)`.

    @exception std::bad_alloc if allocation for object, array, or string fails.

    @liveexample{The following code shows an example for the copy
    constructor.,basic_json__basic_json}

    @ingroup container
    */
    basic_json(const basic_json& other)
        : m_type(other.m_type)
    {
        switch (m_type)
        {
            case (value_t::null):
            case (value_t::discarded):
            {
                break;
            }

            case (value_t::object):
            {
                m_value = *other.m_value.object;
                break;
            }

            case (value_t::array):
            {
                m_value = *other.m_value.array;
                break;
            }

            case (value_t::string):
            {
                m_value = *other.m_value.string;
                break;
            }

            case (value_t::boolean):
            {
                m_value = other.m_value.boolean;
                break;
            }

            case (value_t::number_integer):
            {
                m_value = other.m_value.number_integer;
                break;
            }

            case (value_t::number_float):
            {
                m_value = other.m_value.number_float;
                break;
            }
        }
    }

    /// move constructor
    basic_json(basic_json&& other) noexcept
        : m_type(std::move(other.m_type)),
          m_value(std::move(other.m_value))
    {
        // invalidate payload
        other.m_type = value_t::null;
        other.m_value = {};
    }

    /*!
    @brief copy assignment

    The copy assignment operator is expressed in terms of the copy constructor,
    destructor, and the swap() member function.

    @complexity Linear.

    @requirement This function satisfies the Container requirements:
    - The complexity is linear.

    @ingroup container
    */
    reference& operator=(basic_json other) noexcept (
        std::is_nothrow_move_constructible<value_t>::value and
        std::is_nothrow_move_assignable<value_t>::value and
        std::is_nothrow_move_constructible<json_value>::value and
        std::is_nothrow_move_assignable<json_value>::value
    )
    {
        using std::swap;
        std::swap(m_type, other.m_type);
        std::swap(m_value, other.m_value);
        return *this;
    }

    /*!
    @brief destructor

    Destroys the JSON value and frees all memory.

    @complexity Linear.

    @requirement This function satisfies the Container requirements:
    - The complexity is linear.
    - All stored elements are destroyed and all memory is freed.

    @ingroup container
    */
    ~basic_json() noexcept
    {
        switch (m_type)
        {
            case (value_t::object):
            {
                AllocatorType<object_t> alloc;
                alloc.destroy(m_value.object);
                alloc.deallocate(m_value.object, 1);
                m_value.object = nullptr;
                break;
            }

            case (value_t::array):
            {
                AllocatorType<array_t> alloc;
                alloc.destroy(m_value.array);
                alloc.deallocate(m_value.array, 1);
                m_value.array = nullptr;
                break;
            }

            case (value_t::string):
            {
                AllocatorType<string_t> alloc;
                alloc.destroy(m_value.string);
                alloc.deallocate(m_value.string, 1);
                m_value.string = nullptr;
                break;
            }

            default:
            {
                // all other types need no specific destructor
                break;
            }
        }
    }


  public:
    ///////////////////////
    // object inspection //
    ///////////////////////

    /// @name object inspection
    /// @{

    /*!
    @brief serialization

    Serialization function for JSON objects. The function tries to mimick
    Python's @p json.dumps() function, and currently supports its @p indent
    parameter.

    @param indent  if indent is nonnegative, then array elements and object
    members will be pretty-printed with that indent level. An indent level of 0
    will only insert newlines. -1 (the default) selects the most compact
    representation

    @see https://docs.python.org/2/library/json.html#json.dump
    */
    string_t dump(const int indent = -1) const noexcept
    {
        std::stringstream ss;

        if (indent >= 0)
        {
            dump(ss, true, static_cast<unsigned int>(indent));
        }
        else
        {
            dump(ss, false, 0);
        }

        return ss.str();
    }

    /// return the type of the object (explicit)
    value_t type() const noexcept
    {
        return m_type;
    }

    /*!
    @brief return whether value is null

    This function returns true iff the JSON value is null.

    @return `true` if value type is null, `false` otherwise.

    @complexity Constant.

    @liveexample{The following code exemplifies @ref is_null for all JSON
    value types.,is_null}
    */
    bool is_null() const noexcept
    {
        return m_type == value_t::null;
    }

    /*!
    @brief return whether value is a boolean

    This function returns true iff the JSON value is a boolean.

    @return `true` if value type is boolean, `false` otherwise.

    @complexity Constant.

    @liveexample{The following code exemplifies @ref is_boolean for all JSON
    value types.,is_boolean}
    */
    bool is_boolean() const noexcept
    {
        return m_type == value_t::boolean;
    }

    /*!
    @brief return whether value is a number

    This function returns true iff the JSON value is a number. This includes
    both integer and floating-point values.

    @return `true` if value type is number, `false` otherwise.

    @complexity Constant.

    @liveexample{The following code exemplifies @ref is_number for all JSON
    value types.,is_number}
    */
    bool is_number() const noexcept
    {
        return (m_type == value_t::number_integer) or (m_type == value_t::number_float);
    }

    /*!
    @brief return whether value is an integer number

    This function returns true iff the JSON value is an integer number. This
    excludes floating-point values.

    @return `true` if value type is an integer number, `false` otherwise.

    @complexity Constant.

    @liveexample{The following code exemplifies @ref is_number_integer for all
    JSON value types.,is_number_integer}
    */
    bool is_number_integer() const noexcept
    {
        return m_type == value_t::number_integer;
    }

    /*!
    @brief return whether value is a floating-point number

    This function returns true iff the JSON value is a floating-point number.
    This excludes integer values.

    @return `true` if value type is a floating-point number, `false` otherwise.

    @complexity Constant.

    @liveexample{The following code exemplifies @ref is_number_float for all
    JSON value types.,is_number_float}
    */
    bool is_number_float() const noexcept
    {
        return m_type == value_t::number_float;
    }

    /*!
    @brief return whether value is an object

    This function returns true iff the JSON value is an object.

    @return `true` if value type is object, `false` otherwise.

    @complexity Constant.

    @liveexample{The following code exemplifies @ref is_object for all JSON
    value types.,is_object}
    */
    bool is_object() const noexcept
    {
        return m_type == value_t::object;
    }

    /*!
    @brief return whether value is an array

    This function returns true iff the JSON value is an array.

    @return `true` if value type is array, `false` otherwise.

    @complexity Constant.

    @liveexample{The following code exemplifies @ref is_array for all JSON
    value types.,is_array}
    */
    bool is_array() const noexcept
    {
        return m_type == value_t::array;
    }

    /*!
    @brief return whether value is a string

    This function returns true iff the JSON value is a string.

    @return `true` if value type is string, `false` otherwise.

    @complexity Constant.

    @liveexample{The following code exemplifies @ref is_string for all JSON
    value types.,is_string}
    */
    bool is_string() const noexcept
    {
        return m_type == value_t::string;
    }

    // return whether value is discarded
    bool is_discarded() const noexcept
    {
        return m_type == value_t::discarded;
    }

    /// return the type of the object (implicit)
    operator value_t() const noexcept
    {
        return m_type;
    }

    /// @}

  private:
    //////////////////
    // value access //
    //////////////////

    /// get an object (explicit)
    template <class T, typename
              std::enable_if<
                  std::is_convertible<typename object_t::key_type, typename T::key_type>::value and
                  std::is_convertible<__basic_json, typename T::mapped_type>::value
                  , int>::type = 0>
    T get_impl(T*) const
    {
        switch (m_type)
        {
            case (value_t::object):
            {
                return T(m_value.object->begin(), m_value.object->end());
            }
            default:
            {
                throw std::domain_error("value type must be object, but is " + type_name());
            }
        }
    }

    /// get an object (explicit)
    object_t get_impl(object_t*) const
    {
        switch (m_type)
        {
            case (value_t::object):
            {
                return *(m_value.object);
            }
            default:
            {
                throw std::domain_error("value type must be object, but is " + type_name());
            }
        }
    }

    /// get an array (explicit)
    template <class T, typename
              std::enable_if<
                  std::is_convertible<__basic_json, typename T::value_type>::value and
                  not std::is_same<__basic_json, typename T::value_type>::value and
                  not std::is_arithmetic<T>::value and
                  not std::is_convertible<std::string, T>::value and
                  not internals::has_mapped_type<T>::value
                  , int>::type = 0>
    T get_impl(T*) const
    {
        switch (m_type)
        {
            case (value_t::array):
            {
                T to_vector;
                std::transform(m_value.array->begin(), m_value.array->end(),
                               std::inserter(to_vector, to_vector.end()), [](basic_json i)
                {
                    return i.get<typename T::value_type>();
                });
                return to_vector;
            }
            default:
            {
                throw std::domain_error("value type must be array, but is " + type_name());
            }
        }
    }

    /// get an array (explicit)
    template <class T, typename
              std::enable_if<
                  std::is_convertible<__basic_json, T>::value and
                  not std::is_same<__basic_json, T>::value
                  , int>::type = 0>
    std::vector<T> get_impl(std::vector<T>*) const
    {
        switch (m_type)
        {
            case (value_t::array):
            {
                std::vector<T> to_vector;
                to_vector.reserve(m_value.array->size());
                std::transform(m_value.array->begin(), m_value.array->end(),
                               std::inserter(to_vector, to_vector.end()), [](basic_json i)
                {
                    return i.get<T>();
                });
                return to_vector;
            }
            default:
            {
                throw std::domain_error("value type must be array, but is " + type_name());
            }
        }
    }

    /// get an array (explicit)
    template <class T, typename
              std::enable_if<
                  std::is_same<basic_json, typename T::value_type>::value and
                  not internals::has_mapped_type<T>::value
                  , int>::type = 0>
    T get_impl(T*) const
    {
        switch (m_type)
        {
            case (value_t::array):
            {
                return T(m_value.array->begin(), m_value.array->end());
            }
            default:
            {
                throw std::domain_error("value type must be array, but is " + type_name());
            }
        }
    }

    array_t get_impl(array_t*) const
    {
        switch (m_type)
        {
            case (value_t::array):
            {
                return *(m_value.array);
            }
            default:
            {
                throw std::domain_error("value type must be array, but is " + type_name());
            }
        }
    }

    /// get a string (explicit)
    template <typename T, typename
              std::enable_if<
                  std::is_convertible<string_t, T>::value
                  , int>::type = 0>
    T get_impl(T*) const
    {
        switch (m_type)
        {
            case (value_t::string):
            {
                return *m_value.string;
            }
            default:
            {
                throw std::domain_error("value type must be string, but is " + type_name());
            }
        }
    }

    /// get a number (explicit)
    template<typename T, typename
             std::enable_if<
                 std::is_arithmetic<T>::value
                 , int>::type = 0>
    T get_impl(T*) const
    {
        switch (m_type)
        {
            case (value_t::number_integer):
            {
                return static_cast<T>(m_value.number_integer);
            }
            case (value_t::number_float):
            {
                return static_cast<T>(m_value.number_float);
            }
            default:
            {
                throw std::domain_error("value type must be number, but is " + type_name());
            }
        }
    }

    /// get a boolean (explicit)
    boolean_t get_impl(boolean_t*) const
    {
        switch (m_type)
        {
            case (value_t::boolean):
            {
                return m_value.boolean;
            }
            default:
            {
                throw std::domain_error("value type must be boolean, but is " + type_name());
            }
        }
    }

  public:

    /// @name value access
    /// @{

    /// get a value (explicit)
    // <http://stackoverflow.com/a/8315197/266378>
    template<typename T>
    T get() const
    {
        return get_impl(static_cast<T*>(nullptr));
    }

    /// get a value (implicit)
    template<typename T>
    operator T() const
    {
        return get<T>();
    }

    /// @}


    ////////////////////
    // element access //
    ////////////////////

    /// @name element access
    /// @{

    /// access specified element with bounds checking
    reference at(size_type idx)
    {
        // at only works for arrays
        if (m_type != value_t::array)
        {
            throw std::domain_error("cannot use at() with " + type_name());
        }

        return m_value.array->at(idx);
    }

    /// access specified element with bounds checking
    const_reference at(size_type idx) const
    {
        // at only works for arrays
        if (m_type != value_t::array)
        {
            throw std::domain_error("cannot use at() with " + type_name());
        }

        return m_value.array->at(idx);
    }

    /// access specified element with bounds checking
    reference at(const typename object_t::key_type& key)
    {
        // at only works for objects
        if (m_type != value_t::object)
        {
            throw std::domain_error("cannot use at() with " + type_name());
        }

        return m_value.object->at(key);
    }

    /// access specified element with bounds checking
    const_reference at(const typename object_t::key_type& key) const
    {
        // at only works for objects
        if (m_type != value_t::object)
        {
            throw std::domain_error("cannot use at() with " + type_name());
        }

        return m_value.object->at(key);
    }

    /// access specified element
    reference operator[](size_type idx)
    {
        // implicitly convert null to object
        if (m_type == value_t::null)
        {
            m_type = value_t::array;
            AllocatorType<array_t> alloc;
            m_value.array = alloc.allocate(1);
            alloc.construct(m_value.array);
        }

        // [] only works for arrays
        if (m_type != value_t::array)
        {
            throw std::domain_error("cannot use operator[] with " + type_name());
        }

        for (size_t i = m_value.array->size(); i <= idx; ++i)
        {
            m_value.array->push_back(basic_json());
        }

        return m_value.array->operator[](idx);
    }

    /// access specified element
    const_reference operator[](size_type idx) const
    {
        // at only works for arrays
        if (m_type != value_t::array)
        {
            throw std::domain_error("cannot use operator[] with " + type_name());
        }

        return m_value.array->operator[](idx);
    }

    /// access specified element
    reference operator[](const typename object_t::key_type& key)
    {
        // implicitly convert null to object
        if (m_type == value_t::null)
        {
            m_type = value_t::object;
            AllocatorType<object_t> alloc;
            m_value.object = alloc.allocate(1);
            alloc.construct(m_value.object);
        }

        // [] only works for objects
        if (m_type != value_t::object)
        {
            throw std::domain_error("cannot use operator[] with " + type_name());
        }

        return m_value.object->operator[](key);
    }

    /// access specified element
    const_reference operator[](const typename object_t::key_type& key) const
    {
        // at only works for objects
        if (m_type != value_t::object)
        {
            throw std::domain_error("cannot use operator[] with " + type_name());
        }

        return m_value.object->operator[](key);
    }

    /// access specified element (needed for clang)
    template<typename T, std::size_t n>
    reference operator[](const T (&key)[n])
    {
        // implicitly convert null to object
        if (m_type == value_t::null)
        {
            m_type = value_t::object;
            m_value = value_t::object;
        }

        // at only works for objects
        if (m_type != value_t::object)
        {
            throw std::domain_error("cannot use operator[] with " + type_name());
        }

        return m_value.object->operator[](key);
    }

    /// access specified element (needed for clang)
    template<typename T, std::size_t n>
    const_reference operator[](const T (&key)[n]) const
    {
        // at only works for objects
        if (m_type != value_t::object)
        {
            throw std::domain_error("cannot use operator[] with " + type_name());
        }

        return m_value.object->operator[](key);
    }

    /*!
    @brief access the first element

    Returns a reference to the first element in the container. For a JSON
    container `c`, the expression `c.front()` is equivalent to `*c.begin()`.

    @return In case of a compound value (array or object), a reference to the
    first element is returned. In cast of number, string, or boolean values, a
    reference to the value is returned.

    @complexity Constant.

    @note Calling `front` on an empty container is undefined.

    @throw std::out_of_range when called on null value.

    @liveexample{The following code shows an example for @ref front.,front}
    */
    reference front()
    {
        return *begin();
    }

    /*!
    @copydoc basic_json::front()
    */
    const_reference front() const
    {
        return *cbegin();
    }

    /*!
    @brief access the last element

    Returns a reference to the last element in the container. For a JSON
    container `c`, the expression `c.back()` is equivalent to `{ auto tmp =
    c.end(); --tmp; return *tmp; }`.

    @return In case of a compound value (array or object), a reference to the
    last element is returned. In cast of number, string, or boolean values, a
    reference to the value is returned.

    @complexity Constant.

    @note Calling `back` on an empty container is undefined.

    @throw std::out_of_range when called on null value.

    @liveexample{The following code shows an example for @ref back.,back}
    */
    reference back()
    {
        auto tmp = end();
        --tmp;
        return *tmp;
    }

    /*!
    @copydoc basic_json::back()
    */
    const_reference back() const
    {
        auto tmp = cend();
        --tmp;
        return *tmp;
    }

    /// remove element given an iterator
    template <class T, typename
              std::enable_if<
                  std::is_same<T, typename __basic_json::iterator>::value or
                  std::is_same<T, typename __basic_json::const_iterator>::value
                  , int>::type
              = 0>
    T erase(T pos)
    {
        // make sure iterator fits the current value
        if (this != pos.m_object or m_type != pos.m_object->m_type)
        {
            throw std::domain_error("iterator does not fit current value");
        }

        T result = end();

        switch (m_type)
        {
            case value_t::number_integer:
            case value_t::number_float:
            case value_t::boolean:
            case value_t::string:
            {
                if (pos.m_it.generic_iterator != 0)
                {
                    throw std::out_of_range("iterator out of range");
                }

                if (m_type == value_t::string)
                {
                    delete m_value.string;
                    m_value.string = nullptr;
                }

                m_type = value_t::null;
                break;
            }

            case value_t::object:
            {
                result.m_it.object_iterator = m_value.object->erase(pos.m_it.object_iterator);
                break;
            }

            case value_t::array:
            {
                result.m_it.array_iterator = m_value.array->erase(pos.m_it.array_iterator);
                break;
            }

            default:
            {
                throw std::domain_error("cannot use erase() with " + type_name());
            }
        }

        return result;
    }

    /// remove elements given an iterator range
    template <class T, typename
              std::enable_if<
                  std::is_same<T, typename basic_json::iterator>::value or
                  std::is_same<T, typename basic_json::const_iterator>::value
                  , int>::type
              = 0>
    T erase(T first, T last)
    {
        // make sure iterator fits the current value
        if (this != first.m_object or this != last.m_object or
                m_type != first.m_object->m_type or m_type != last.m_object->m_type)
        {
            throw std::domain_error("iterators do not fit current value");
        }

        T result = end();

        switch (m_type)
        {
            case value_t::number_integer:
            case value_t::number_float:
            case value_t::boolean:
            case value_t::string:
            {
                if (first.m_it.generic_iterator != 0 or last.m_it.generic_iterator != 1)
                {
                    throw std::out_of_range("iterators out of range");
                }

                if (m_type == value_t::string)
                {
                    delete m_value.string;
                    m_value.string = nullptr;
                }

                m_type = value_t::null;
                break;
            }

            case value_t::object:
            {
                result.m_it.object_iterator = m_value.object->erase(first.m_it.object_iterator,
                                              last.m_it.object_iterator);
                break;
            }

            case value_t::array:
            {
                result.m_it.array_iterator = m_value.array->erase(first.m_it.array_iterator,
                                             last.m_it.array_iterator);
                break;
            }

            default:
            {
                throw std::domain_error("cannot use erase with " + type_name());
            }
        }

        return result;
    }

    /// remove element from an object given a key
    size_type erase(const typename object_t::key_type& key)
    {
        // this erase only works for objects
        if (m_type != value_t::object)
        {
            throw std::domain_error("cannot use erase() with " + type_name());
        }

        return m_value.object->erase(key);
    }

    /// remove element from an array given an index
    void erase(const size_type idx)
    {
        // this erase only works for arrays
        if (m_type != value_t::array)
        {
            throw std::domain_error("cannot use erase() with " + type_name());
        }

        if (idx >= size())
        {
            throw std::out_of_range("index out of range");
        }

        m_value.array->erase(m_value.array->begin() + static_cast<difference_type>(idx));
    }

    /// find an element in an object
    iterator find(typename object_t::key_type key)
    {
        auto result = end();

        if (m_type == value_t::object)
        {
            result.m_it.object_iterator = m_value.object->find(key);
        }

        return result;
    }

    /// find an element in an object
    const_iterator find(typename object_t::key_type key) const
    {
        auto result = cend();

        if (m_type == value_t::object)
        {
            result.m_it.object_iterator = m_value.object->find(key);
        }

        return result;
    }

    /// returns the number of occurrences of a key in an object
    size_type count(typename object_t::key_type key) const
    {
        // return 0 for all nonobject types
        return (m_type == value_t::object) ? m_value.object->count(key) : 0;
    }

    /// @}


    ///////////////
    // iterators //
    ///////////////

    /// @name iterators
    /// @{

    /*!
    @brief returns an iterator to the first element

    Returns an iterator to the first element.

    @image html range-begin-end.svg "Illustration from cppreference.com"

    @return iterator to the first element

    @complexity Constant.

    @requirement This function satisfies the Container requirements:
    - The complexity is constant.

    @liveexample{The following code shows an example for @ref begin.,begin}

    @ingroup container
    */
    iterator begin() noexcept
    {
        iterator result(this);
        result.set_begin();
        return result;
    }

    /*!
    @copydoc basic_json::cbegin()
    @ingroup container
    */
    const_iterator begin() const noexcept
    {
        return cbegin();
    }

    /*!
    @brief returns a const iterator to the first element

    Returns a const iterator to the first element.

    @image html range-begin-end.svg "Illustration from cppreference.com"

    @return const iterator to the first element

    @complexity Constant.

    @requirement This function satisfies the Container requirements:
    - The complexity is constant.
    - Has the semantics of `const_cast<const basic_json&>(*this).begin()`.

    @liveexample{The following code shows an example for @ref cbegin.,cbegin}

    @ingroup container
    */
    const_iterator cbegin() const noexcept
    {
        const_iterator result(this);
        result.set_begin();
        return result;
    }

    /*!
    @brief returns an iterator to one past the last element

    Returns an iterator to one past the last element.

    @image html range-begin-end.svg "Illustration from cppreference.com"

    @return iterator one past the last element

    @complexity Constant.

    @requirement This function satisfies the Container requirements:
    - The complexity is constant.

    @liveexample{The following code shows an example for @ref end.,end}

    @ingroup container
    */
    iterator end() noexcept
    {
        iterator result(this);
        result.set_end();
        return result;
    }

    /*!
    @copydoc basic_json::cend()
    @ingroup container
    */
    const_iterator end() const noexcept
    {
        return cend();
    }

    /*!
    @brief returns a const iterator to one past the last element

    Returns a const iterator to one past the last element.

    @image html range-begin-end.svg "Illustration from cppreference.com"

    @return const iterator one past the last element

    @complexity Constant.

    @requirement This function satisfies the Container requirements:
    - The complexity is constant.
    - Has the semantics of `const_cast<const basic_json&>(*this).end()`.

    @liveexample{The following code shows an example for @ref cend.,cend}

    @ingroup container
    */
    const_iterator cend() const noexcept
    {
        const_iterator result(this);
        result.set_end();
        return result;
    }

    /*!
    @brief returns an iterator to the reverse-beginning

    Returns an iterator to the reverse-beginning; that is, the last element.

    @image html range-rbegin-rend.svg "Illustration from cppreference.com"

    @complexity Constant.

    @requirement This function satisfies the ReversibleContainer requirements:
    - The complexity is constant.
    - Has the semantics of `reverse_iterator(end())`.

    @liveexample{The following code shows an example for @ref rbegin.,rbegin}

    @ingroup reversiblecontainer
    */
    reverse_iterator rbegin() noexcept
    {
        return reverse_iterator(end());
    }

    /*!
    @copydoc basic_json::crbegin()
    @ingroup reversiblecontainer
    */
    const_reverse_iterator rbegin() const noexcept
    {
        return crbegin();
    }

    /*!
    @brief returns an iterator to the reverse-end

    Returns an iterator to the reverse-end; that is, one before the first
    element.

    @image html range-rbegin-rend.svg "Illustration from cppreference.com"

    @complexity Constant.

    @requirement This function satisfies the ReversibleContainer requirements:
    - The complexity is constant.
    - Has the semantics of `reverse_iterator(begin())`.

    @liveexample{The following code shows an example for @ref rend.,rend}

    @ingroup reversiblecontainer
    */
    reverse_iterator rend() noexcept
    {
        return reverse_iterator(begin());
    }

    /*!
    @copydoc basic_json::crend()
    @ingroup reversiblecontainer
    */
    const_reverse_iterator rend() const noexcept
    {
        return crend();
    }

    /*!
    @brief returns a const reverse iterator to the last element

    Returns a const iterator to the reverse-beginning; that is, the last
    element.

    @image html range-rbegin-rend.svg "Illustration from cppreference.com"

    @complexity Constant.

    @requirement This function satisfies the ReversibleContainer requirements:
    - The complexity is constant.
    - Has the semantics of `const_cast<const basic_json&>(*this).rbegin()`.

    @liveexample{The following code shows an example for @ref crbegin.,crbegin}

    @ingroup reversiblecontainer
    */
    const_reverse_iterator crbegin() const noexcept
    {
        return const_reverse_iterator(cend());
    }

    /*!
    @brief returns a const reverse iterator to one before the first

    Returns a const reverse iterator to the reverse-end; that is, one before
    the first element.

    @image html range-rbegin-rend.svg "Illustration from cppreference.com"

    @complexity Constant.

    @requirement This function satisfies the ReversibleContainer requirements:
    - The complexity is constant.
    - Has the semantics of `const_cast<const basic_json&>(*this).rend()`.

    @liveexample{The following code shows an example for @ref crend.,crend}

    @ingroup reversiblecontainer
    */
    const_reverse_iterator crend() const noexcept
    {
        return const_reverse_iterator(cbegin());
    }

    /// @}


    //////////////
    // capacity //
    //////////////

    /// @name capacity
    /// @{

    /*!
    @brief checks whether the container is empty

    Checks if a JSON value has no elements.

    @return The return value depends on the different value types and is
            defined as follows:
            Value type  | return value
            ----------- | -------------
            null        | @c true
            boolean     | @c false
            string      | @c false
            number      | @c false
            object      | result of function object_t::empty()
            array       | result of function array_t::empty()

    @complexity Constant, as long as @ref array_t and @ref object_t satisfy the
                Container concept; that is, their empty() functions have
                constant complexity.

    @requirement This function satisfies the Container requirements:
    - The complexity is constant.
    - Has the semantics of `begin() == end()`.

    @liveexample{The following code uses @ref empty to check if a @ref json
    object contains any elements.,empty}

    @ingroup container
    */
    bool empty() const noexcept
    {
        switch (m_type)
        {
            case (value_t::null):
            {
                return true;
            }

            case (value_t::array):
            {
                return m_value.array->empty();
            }

            case (value_t::object):
            {
                return m_value.object->empty();
            }

            default:
            {
                // all other types are nonempty
                return false;
            }
        }
    }

    /*!
    @brief returns the number of elements

    Returns the number of elements in a JSON value.

    @return The return value depends on the different value types and is
            defined as follows:
            Value type  | return value
            ----------- | -------------
            null        | @c 0
            boolean     | @c 1
            string      | @c 1
            number      | @c 1
            object      | result of function object_t::size()
            array       | result of function array_t::size()

    @complexity Constant, as long as @ref array_t and @ref object_t satisfy the
                Container concept; that is, their size() functions have
                constant complexity.

    @requirement This function satisfies the Container requirements:
    - The complexity is constant.
    - Has the semantics of `std::distance(begin(), end())`.

    @liveexample{The following code calls @ref size on the different value
    types.,size}

    @ingroup container
    */
    size_type size() const noexcept
    {
        switch (m_type)
        {
            case (value_t::null):
            {
                return 0;
            }

            case (value_t::array):
            {
                return m_value.array->size();
            }

            case (value_t::object):
            {
                return m_value.object->size();
            }

            default:
            {
                // all other types have size 1
                return 1;
            }
        }
    }

    /*!
    @brief returns the maximum possible number of elements

    Returns the maximum number of elements a JSON value is able to hold due to
    system or library implementation limitations, i.e. `std::distance(begin(),
    end())` for the JSON value.

    @return The return value depends on the different value types and is
            defined as follows:
            Value type  | return value
            ----------- | -------------
            null        | @c 0
            boolean     | @c 1
            string      | @c 1
            number      | @c 1
            object      | result of function object_t::max_size()
            array       | result of function array_t::max_size()

    @complexity Constant, as long as @ref array_t and @ref object_t satisfy the
                Container concept; that is, their max_size() functions have
                constant complexity.

    @requirement This function satisfies the Container requirements:
    - The complexity is constant.
    - Has the semantics of returning `b.size()` where `b` is the largest
      possible JSON value.

    @liveexample{The following code calls @ref max_size on the different value
    types. Note the output is implementation specific.,max_size}

    @ingroup container
    */
    size_type max_size() const noexcept
    {
        switch (m_type)
        {
            case (value_t::null):
            {
                return 0;
            }

            case (value_t::array):
            {
                return m_value.array->max_size();
            }

            case (value_t::object):
            {
                return m_value.object->max_size();
            }

            default:
            {
                // all other types have max_size 1
                return 1;
            }
        }
    }

    /// @}


    ///////////////
    // modifiers //
    ///////////////

    /// @name modifiers
    /// @{

    /*!
    @brief clears the contents

    Clears the content of a JSON value and resets it to the default value as
    if @ref basic_json(value_t) would have been called:

    Value type  | initial value
    ----------- | -------------
    null        | `null`
    boolean     | `false`
    string      | `""`
    number      | `0`
    object      | `{}`
    array       | `[]`

    @note Floating-point numbers are set to `0.0` which will be serialized to
    `0`. The vale type remains @ref number_float_t.

    @complexity Linear in the size of the JSON value.

    @liveexample{The example below shows the effect of @ref clear to different
    JSON value types.,clear}
    */
    void clear() noexcept
    {
        switch (m_type)
        {
            case (value_t::null):
            case (value_t::discarded):
            {
                break;
            }

            case (value_t::number_integer):
            {
                m_value.number_integer = 0;
                break;
            }

            case (value_t::number_float):
            {
                m_value.number_float = 0.0;
                break;
            }

            case (value_t::boolean):
            {
                m_value.boolean = false;
                break;
            }

            case (value_t::string):
            {
                m_value.string->clear();
                break;
            }

            case (value_t::array):
            {
                m_value.array->clear();
                break;
            }

            case (value_t::object):
            {
                m_value.object->clear();
                break;
            }
        }
    }

    /// add an object to an array
    void push_back(basic_json&& value)
    {
        // push_back only works for null objects or arrays
        if (not(m_type == value_t::null or m_type == value_t::array))
        {
            throw std::domain_error("cannot use push_back() with " + type_name());
        }

        // transform null object into an array
        if (m_type == value_t::null)
        {
            m_type = value_t::array;
            m_value = value_t::array;
        }

        // add element to array (move semantics)
        m_value.array->push_back(std::move(value));
        // invalidate object
        value.m_type = value_t::null;
    }

    /// add an object to an array
    reference operator+=(basic_json&& value)
    {
        push_back(std::move(value));
        return *this;
    }

    /// add an object to an array
    void push_back(const basic_json& value)
    {
        // push_back only works for null objects or arrays
        if (not(m_type == value_t::null or m_type == value_t::array))
        {
            throw std::domain_error("cannot use push_back() with " + type_name());
        }

        // transform null object into an array
        if (m_type == value_t::null)
        {
            m_type = value_t::array;
            m_value = value_t::array;
        }

        // add element to array
        m_value.array->push_back(value);
    }

    /// add an object to an array
    reference operator+=(const basic_json& value)
    {
        push_back(value);
        return *this;
    }

    /// add an object to an object
    void push_back(const typename object_t::value_type& value)
    {
        // push_back only works for null objects or objects
        if (not(m_type == value_t::null or m_type == value_t::object))
        {
            throw std::domain_error("cannot use push_back() with " + type_name());
        }

        // transform null object into an object
        if (m_type == value_t::null)
        {
            m_type = value_t::object;
            m_value = value_t::object;
        }

        // add element to array
        m_value.object->insert(value);
    }

    /// add an object to an object
    reference operator+=(const typename object_t::value_type& value)
    {
        push_back(value);
        return operator[](value.first);
    }

    /*!
    @brief exchanges the values
    @ingroup container
    */
    void swap(reference other) noexcept (
        std::is_nothrow_move_constructible<value_t>::value and
        std::is_nothrow_move_assignable<value_t>::value and
        std::is_nothrow_move_constructible<json_value>::value and
        std::is_nothrow_move_assignable<json_value>::value
    )
    {
        std::swap(m_type, other.m_type);
        std::swap(m_value, other.m_value);
    }

    /// swaps the contents
    void swap(array_t& other)
    {
        // swap only works for arrays
        if (m_type != value_t::array)
        {
            throw std::domain_error("cannot use swap() with " + type_name());
        }

        // swap arrays
        std::swap(*(m_value.array), other);
    }

    /// swaps the contents
    void swap(object_t& other)
    {
        // swap only works for objects
        if (m_type != value_t::object)
        {
            throw std::domain_error("cannot use swap() with " + type_name());
        }

        // swap arrays
        std::swap(*(m_value.object), other);
    }

    /// swaps the contents
    void swap(string_t& other)
    {
        // swap only works for strings
        if (m_type != value_t::string)
        {
            throw std::domain_error("cannot use swap() with " + type_name());
        }

        // swap arrays
        std::swap(*(m_value.string), other);
    }

    /// @}


    //////////////////////////////////////////
    // lexicographical comparison operators //
    //////////////////////////////////////////

    /// @name lexicographical comparison operators
    /// @{

    /*!
    @brief comparison: equal
    @ingroup container
    */
    friend bool operator==(const_reference lhs, const_reference rhs) noexcept
    {
        const auto lhs_type = lhs.type();
        const auto rhs_type = rhs.type();

        if (lhs_type == rhs_type)
        {
            switch (lhs_type)
            {
                case (value_t::array):
                    return *lhs.m_value.array == *rhs.m_value.array;
                case (value_t::object):
                    return *lhs.m_value.object == *rhs.m_value.object;
                case (value_t::null):
                    return true;
                case (value_t::string):
                    return *lhs.m_value.string == *rhs.m_value.string;
                case (value_t::boolean):
                    return lhs.m_value.boolean == rhs.m_value.boolean;
                case (value_t::number_integer):
                    return lhs.m_value.number_integer == rhs.m_value.number_integer;
                case (value_t::number_float):
                    return approx(lhs.m_value.number_float, rhs.m_value.number_float);
                case (value_t::discarded):
                    return false;
            }
        }
        else if (lhs_type == value_t::number_integer and rhs_type == value_t::number_float)
        {
            return approx(static_cast<number_float_t>(lhs.m_value.number_integer),
                          rhs.m_value.number_float);
        }
        else if (lhs_type == value_t::number_float and rhs_type == value_t::number_integer)
        {
            return approx(lhs.m_value.number_float,
                          static_cast<number_float_t>(rhs.m_value.number_integer));
        }
        return false;
    }

    /*!
    @brief comparison: not equal
    @ingroup container
    */
    friend bool operator!=(const_reference lhs, const_reference rhs) noexcept
    {
        return not (lhs == rhs);
    }

    /// comparison: less than
    friend bool operator<(const_reference lhs, const_reference rhs) noexcept
    {
        const auto lhs_type = lhs.type();
        const auto rhs_type = rhs.type();

        if (lhs_type == rhs_type)
        {
            switch (lhs_type)
            {
                case (value_t::array):
                    return *lhs.m_value.array < *rhs.m_value.array;
                case (value_t::object):
                    return *lhs.m_value.object < *rhs.m_value.object;
                case (value_t::null):
                    return false;
                case (value_t::string):
                    return *lhs.m_value.string < *rhs.m_value.string;
                case (value_t::boolean):
                    return lhs.m_value.boolean < rhs.m_value.boolean;
                case (value_t::number_integer):
                    return lhs.m_value.number_integer < rhs.m_value.number_integer;
                case (value_t::number_float):
                    return lhs.m_value.number_float < rhs.m_value.number_float;
                case (value_t::discarded):
                    return false;
            }
        }
        else if (lhs_type == value_t::number_integer and rhs_type == value_t::number_float)
        {
            return static_cast<number_float_t>(lhs.m_value.number_integer) <
                   rhs.m_value.number_float;
        }
        else if (lhs_type == value_t::number_float and rhs_type == value_t::number_integer)
        {
            return lhs.m_value.number_float <
                   static_cast<number_float_t>(rhs.m_value.number_integer);
        }

        // We only reach this line if we cannot compare values. In that case,
        // we compare types.
        return lhs_type < rhs_type;
    }

    /// comparison: less than or equal
    friend bool operator<=(const_reference lhs, const_reference rhs) noexcept
    {
        return not (rhs < lhs);
    }

    /// comparison: greater than
    friend bool operator>(const_reference lhs, const_reference rhs) noexcept
    {
        return not (lhs <= rhs);
    }

    /// comparison: greater than or equal
    friend bool operator>=(const_reference lhs, const_reference rhs) noexcept
    {
        return not (lhs < rhs);
    }

    /// @}


    ///////////////////
    // serialization //
    ///////////////////

    /// @name serialization
    /// @{

    /// serialize to stream
    friend std::ostream& operator<<(std::ostream& o, const basic_json& j)
    {
        // read width member and use it as indentation parameter if nonzero
        const bool pretty_print = (o.width() > 0);
        const auto indentation = (pretty_print ? o.width() : 0);

        // reset width to 0 for subsequent calls to this stream
        o.width(0);

        // do the actual serialization
        j.dump(o, pretty_print, static_cast<unsigned int>(indentation));
        return o;
    }

    /// serialize to stream
    friend std::ostream& operator>>(const basic_json& j, std::ostream& o)
    {
        return o << j;
    }

    /// @}


    /////////////////////
    // deserialization //
    /////////////////////

    /// @name deserialization
    /// @{

    /// deserialize from string
    static basic_json parse(const string_t& s, parser_callback_t cb = nullptr)
    {
        return parser(s, cb).parse();
    }

    /// deserialize from stream
    static basic_json parse(std::istream& i, parser_callback_t cb = nullptr)
    {
        return parser(i, cb).parse();
    }

    /// deserialize from stream
    friend std::istream& operator>>(std::istream& i, basic_json& j)
    {
        j = parser(i).parse();
        return i;
    }

    /// deserialize from stream
    friend std::istream& operator<<(basic_json& j, std::istream& i)
    {
        j = parser(i).parse();
        return i;
    }

    /// @}


  private:
    ///////////////////////////
    // convenience functions //
    ///////////////////////////

    /// return the type as string
    string_t type_name() const noexcept
    {
        switch (m_type)
        {
            case (value_t::null):
            {
                return "null";
            }

            case (value_t::object):
            {
                return "object";
            }

            case (value_t::array):
            {
                return "array";
            }

            case (value_t::string):
            {
                return "string";
            }

            case (value_t::boolean):
            {
                return "boolean";
            }

            case (value_t::discarded):
            {
                return "discarded";
            }

            default:
            {
                return "number";
            }
        }
    }

    /*!
    @brief escape a string

    Escape a string by replacing certain special characters by a sequence of an
    escape character (backslash) and another character and other control
    characters by a sequence of "\u" followed by a four-digit hex
    representation.

    @param o  the stream to write the escaped string to
    @param s  the string to escape
    */
    static void escape_string(std::ostream& o, const string_t& s) noexcept
    {
        for (const auto c : s)
        {
            switch (c)
            {
                // quotation mark (0x22)
                case '"':
                {
                    o << "\\\"";
                    break;
                }

                // reverse solidus (0x5c)
                case '\\':
                {
                    o << "\\\\";
                    break;
                }

                // backspace (0x08)
                case '\b':
                {
                    o << "\\b";
                    break;
                }

                // formfeed (0x0c)
                case '\f':
                {
                    o << "\\f";
                    break;
                }

                // newline (0x0a)
                case '\n':
                {
                    o << "\\n";
                    break;
                }

                // carriage return (0x0d)
                case '\r':
                {
                    o << "\\r";
                    break;
                }

                // horizontal tab (0x09)
                case '\t':
                {
                    o << "\\t";
                    break;
                }

                default:
                {
                    if (c >= 0 and c <= 0x1f)
                    {
                        // control characters (everything between 0x00 and 0x1f)
                        // -> create four-digit hex representation
                        o << "\\u" << std::hex << std::setw(4) << std::setfill('0') << int(c);
                    }
                    else
                    {
                        // all other characters are added as-is
                        o << c;
                    }
                    break;
                }
            }
        }
    }

    /*!
    @brief internal implementation of the serialization function

    This function is called by the public member function dump and organizes
    the serializaion internally. The indentation level is propagated as
    additional parameter. In case of arrays and objects, the function is called
    recursively. Note that

    - strings and object keys are escaped using escape_string()
    - integer numbers are converted implictly via operator<<
    - floating-point numbers are converted to a string using "%g" format

    @param o               stream to write to
    @param pretty_print    whether the output shall be pretty-printed
    @param indent_step     the indent level
    @param current_indent  the current indent level (only used internally)
    */
    void dump(std::ostream& o, const bool pretty_print, const unsigned int indent_step,
              const unsigned int current_indent = 0) const noexcept
    {
        // variable to hold indentation for recursive calls
        unsigned int new_indent = current_indent;

        switch (m_type)
        {
            case (value_t::object):
            {
                if (m_value.object->empty())
                {
                    o << "{}";
                    return;
                }

                o << "{";

                // increase indentation
                if (pretty_print)
                {
                    new_indent += indent_step;
                    o << "\n";
                }

                for (auto i = m_value.object->cbegin(); i != m_value.object->cend(); ++i)
                {
                    if (i != m_value.object->cbegin())
                    {
                        o << (pretty_print ? ",\n" : ",");
                    }
                    o << string_t(new_indent, ' ') << "\"";
                    escape_string(o, i->first);
                    o << "\":" << (pretty_print ? " " : "");
                    i->second.dump(o, pretty_print, indent_step, new_indent);
                }

                // decrease indentation
                if (pretty_print)
                {
                    new_indent -= indent_step;
                    o << "\n";
                }

                o << string_t(new_indent, ' ') + "}";
                return;
            }

            case (value_t::array):
            {
                if (m_value.array->empty())
                {
                    o << "[]";
                    return;
                }

                o << "[";

                // increase indentation
                if (pretty_print)
                {
                    new_indent += indent_step;
                    o << "\n";
                }

                for (auto i = m_value.array->cbegin(); i != m_value.array->cend(); ++i)
                {
                    if (i != m_value.array->cbegin())
                    {
                        o << (pretty_print ? ",\n" : ",");
                    }
                    o << string_t(new_indent, ' ');
                    i->dump(o, pretty_print, indent_step, new_indent);
                }

                // decrease indentation
                if (pretty_print)
                {
                    new_indent -= indent_step;
                    o << "\n";
                }

                o << string_t(new_indent, ' ') << "]";
                return;
            }

            case (value_t::string):
            {
                o << string_t("\"");
                escape_string(o, *m_value.string);
                o << "\"";
                return;
            }

            case (value_t::boolean):
            {
                o << (m_value.boolean ? "true" : "false");
                return;
            }

            case (value_t::number_integer):
            {
                o << m_value.number_integer;
                return;
            }

            case (value_t::number_float):
            {
                // 15 digits of precision allows round-trip IEEE 754
                // string->double->string; to be safe, we read this value from
                // std::numeric_limits<number_float_t>::digits10
                o << std::setprecision(std::numeric_limits<number_float_t>::digits10) << m_value.number_float;
                return;
            }

            case (value_t::discarded):
            {
                o << "<discarded>";
                return;
            }

            default:
            {
                o << "null";
                return;
            }
        }
    }

    /// "equality" comparison for floating point numbers
    template<typename T>
    static bool approx(const T a, const T b)
    {
        return not (a > b or a < b);
    }


  private:
    //////////////////////
    // member variables //
    //////////////////////

    /// the type of the current element
    value_t m_type = value_t::null;

    /// the value of the current element
    json_value m_value = {};


  private:
    ///////////////
    // iterators //
    ///////////////

    /// an iterator value
    union internal_iterator
    {
        /// iterator for JSON objects
        typename object_t::iterator object_iterator;
        /// iterator for JSON arrays
        typename array_t::iterator array_iterator;
        /// generic iterator for all other value types
        difference_type generic_iterator;

        /// default constructor
        internal_iterator() : generic_iterator(-1) {}
    };

  public:
    /// a random access iterator for the basic_json class
    class iterator : public std::iterator<std::random_access_iterator_tag, basic_json>
    {
        // allow basic_json class to access m_it
        friend class basic_json;

      public:
        /// the type of the values when the iterator is dereferenced
        using value_type = typename basic_json::value_type;
        /// a type to represent differences between iterators
        using difference_type = typename basic_json::difference_type;
        /// defines a pointer to the type iterated over (value_type)
        using pointer = typename basic_json::pointer;
        /// defines a reference to the type iterated over (value_type)
        using reference = typename basic_json::reference;
        /// the category of the iterator
        using iterator_category = std::bidirectional_iterator_tag;

        /// default constructor
        iterator() = default;

        /// constructor for a given JSON instance
        iterator(pointer object) noexcept : m_object(object)
        {
            switch (m_object->m_type)
            {
                case (basic_json::value_t::object):
                {
                    m_it.object_iterator = typename object_t::iterator();
                    break;
                }
                case (basic_json::value_t::array):
                {
                    m_it.array_iterator = typename array_t::iterator();
                    break;
                }
                default:
                {
                    m_it.generic_iterator = -1;
                    break;
                }
            }
        }

        /// copy constructor
        iterator(const iterator& other) noexcept
            : m_object(other.m_object), m_it(other.m_it)
        {}

        /// copy assignment
        iterator& operator=(iterator other) noexcept (
            std::is_nothrow_move_constructible<pointer>::value and
            std::is_nothrow_move_assignable<pointer>::value and
            std::is_nothrow_move_constructible<internal_iterator>::value and
            std::is_nothrow_move_assignable<internal_iterator>::value
        )
        {
            std::swap(m_object, other.m_object);
            std::swap(m_it, other.m_it);
            return *this;
        }

      private:
        /// set the iterator to the first value
        void set_begin() noexcept
        {
            switch (m_object->m_type)
            {
                case (basic_json::value_t::object):
                {
                    m_it.object_iterator = m_object->m_value.object->begin();
                    break;
                }

                case (basic_json::value_t::array):
                {
                    m_it.array_iterator = m_object->m_value.array->begin();
                    break;
                }

                case (basic_json::value_t::null):
                {
                    // set to end so begin()==end() is true: null is empty
                    m_it.generic_iterator = 1;
                    break;
                }

                default:
                {
                    m_it.generic_iterator = 0;
                    break;
                }
            }
        }

        /// set the iterator past the last value
        void set_end() noexcept
        {
            switch (m_object->m_type)
            {
                case (basic_json::value_t::object):
                {
                    m_it.object_iterator = m_object->m_value.object->end();
                    break;
                }

                case (basic_json::value_t::array):
                {
                    m_it.array_iterator = m_object->m_value.array->end();
                    break;
                }

                default:
                {
                    m_it.generic_iterator = 1;
                    break;
                }
            }
        }

      public:
        /// return a reference to the value pointed to by the iterator
        reference operator*()
        {
            switch (m_object->m_type)
            {
                case (basic_json::value_t::object):
                {
                    return m_it.object_iterator->second;
                }

                case (basic_json::value_t::array):
                {
                    return *m_it.array_iterator;
                }

                case (basic_json::value_t::null):
                {
                    throw std::out_of_range("cannot get value");
                }

                default:
                {
                    if (m_it.generic_iterator == 0)
                    {
                        return *m_object;
                    }
                    else
                    {
                        throw std::out_of_range("cannot get value");
                    }
                }
            }
        }

        /// dereference the iterator
        pointer operator->()
        {
            switch (m_object->m_type)
            {
                case (basic_json::value_t::object):
                {
                    return &(m_it.object_iterator->second);
                }

                case (basic_json::value_t::array):
                {
                    return &*m_it.array_iterator;
                }

                case (basic_json::value_t::null):
                {
                    throw std::out_of_range("cannot get value");
                }

                default:
                {
                    if (m_it.generic_iterator == 0)
                    {
                        return m_object;
                    }
                    else
                    {
                        throw std::out_of_range("cannot get value");
                    }
                }
            }
        }

        /// post-increment (it++)
        iterator operator++(int)
        {
            auto result = *this;

            switch (m_object->m_type)
            {
                case (basic_json::value_t::object):
                {
                    m_it.object_iterator++;
                    break;
                }

                case (basic_json::value_t::array):
                {
                    m_it.array_iterator++;
                    break;
                }

                default:
                {
                    m_it.generic_iterator++;
                    break;
                }
            }

            return result;
        }

        /// pre-increment (++it)
        iterator& operator++()
        {
            switch (m_object->m_type)
            {
                case (basic_json::value_t::object):
                {
                    ++m_it.object_iterator;
                    break;
                }

                case (basic_json::value_t::array):
                {
                    ++m_it.array_iterator;
                    break;
                }

                default:
                {
                    ++m_it.generic_iterator;
                    break;
                }
            }

            return *this;
        }

        /// post-decrement (it--)
        iterator operator--(int)
        {
            auto result = *this;

            switch (m_object->m_type)
            {
                case (basic_json::value_t::object):
                {
                    m_it.object_iterator--;
                    break;
                }

                case (basic_json::value_t::array):
                {
                    m_it.array_iterator--;
                    break;
                }

                default:
                {
                    m_it.generic_iterator--;
                    break;
                }
            }

            return result;
        }

        /// pre-decrement (--it)
        iterator& operator--()
        {
            switch (m_object->m_type)
            {
                case (basic_json::value_t::object):
                {
                    --m_it.object_iterator;
                    break;
                }

                case (basic_json::value_t::array):
                {
                    --m_it.array_iterator;
                    break;
                }

                default:
                {
                    --m_it.generic_iterator;
                    break;
                }
            }

            return *this;
        }

        /// comparison: equal
        bool operator==(const iterator& other) const
        {
            // if objects are not the same, the comparison is undefined
            if (m_object != other.m_object)
            {
                throw std::domain_error("cannot compare iterators of different containers");
            }

            switch (m_object->m_type)
            {
                case (basic_json::value_t::object):
                {
                    return (m_it.object_iterator == other.m_it.object_iterator);
                }

                case (basic_json::value_t::array):
                {
                    return (m_it.array_iterator == other.m_it.array_iterator);
                }

                default:
                {
                    return (m_it.generic_iterator == other.m_it.generic_iterator);
                }
            }
        }

        /// comparison: not equal
        bool operator!=(const iterator& other) const
        {
            return not operator==(other);
        }

        /// comparison: smaller
        bool operator<(const iterator& other) const
        {
            // if objects are not the same, the comparison is undefined
            if (m_object != other.m_object)
            {
                throw std::domain_error("cannot compare iterators of different containers");
            }

            switch (m_object->m_type)
            {
                case (basic_json::value_t::object):
                {
                    throw std::domain_error("cannot use operator< for object iterators");
                }

                case (basic_json::value_t::array):
                {
                    return (m_it.array_iterator < other.m_it.array_iterator);
                }

                default:
                {
                    return (m_it.generic_iterator < other.m_it.generic_iterator);
                }
            }
        }

        /// comparison: less than or equal
        bool operator<=(const iterator& other) const
        {
            return not other.operator < (*this);
        }

        /// comparison: greater than
        bool operator>(const iterator& other) const
        {
            return not operator<=(other);
        }

        /// comparison: greater than or equal
        bool operator>=(const iterator& other) const
        {
            return not operator<(other);
        }

        /// add to iterator
        iterator& operator+=(difference_type i)
        {
            switch (m_object->m_type)
            {
                case (basic_json::value_t::object):
                {
                    throw std::domain_error("cannot use operator+= for object iterators");
                }

                case (basic_json::value_t::array):
                {
                    m_it.array_iterator += i;
                    break;
                }

                default:
                {
                    m_it.generic_iterator += i;
                    break;
                }
            }

            return *this;
        }

        /// subtract from iterator
        iterator& operator-=(difference_type i)
        {
            return operator+=(-i);
        }

        /// add to iterator
        iterator operator+(difference_type i)
        {
            auto result = *this;
            result += i;
            return result;
        }

        /// subtract from iterator
        iterator operator-(difference_type i)
        {
            auto result = *this;
            result -= i;
            return result;
        }

        /// return difference
        difference_type operator-(const iterator& other) const
        {
            switch (m_object->m_type)
            {
                case (basic_json::value_t::object):
                {
                    throw std::domain_error("cannot use operator- for object iterators");
                    return 0;
                }

                case (basic_json::value_t::array):
                {
                    return m_it.array_iterator - other.m_it.array_iterator;
                }

                default:
                {
                    return m_it.generic_iterator - other.m_it.generic_iterator;
                }
            }
        }

        /// access to successor
        reference operator[](difference_type n)
        {
            switch (m_object->m_type)
            {
                case (basic_json::value_t::object):
                {
                    throw std::domain_error("cannot use operator[] for object iterators");
                }

                case (basic_json::value_t::array):
                {
                    return *(m_it.array_iterator + n);
                }

                case (basic_json::value_t::null):
                {
                    throw std::out_of_range("cannot get value");
                }

                default:
                {
                    if (m_it.generic_iterator == -n)
                    {
                        return *m_object;
                    }
                    else
                    {
                        throw std::out_of_range("cannot get value");
                    }
                }
            }
        }

        /// return the key of an object iterator
        typename object_t::key_type key() const
        {
            switch (m_object->m_type)
            {
                case (basic_json::value_t::object):
                {
                    return m_it.object_iterator->first;
                }

                default:
                {
                    throw std::domain_error("cannot use key() for non-object iterators");
                }
            }
        }

        /// return the key of an iterator
        reference value()
        {
            return operator*();
        }

      private:
        /// associated JSON instance
        pointer m_object = nullptr;
        /// the actual iterator of the associated instance
        internal_iterator m_it = internal_iterator();
    };

    /// a const random access iterator for the basic_json class
    class const_iterator : public std::iterator<std::random_access_iterator_tag, const basic_json>
    {
        // allow basic_json class to access m_it
        friend class basic_json;

      public:
        /// the type of the values when the iterator is dereferenced
        using value_type = typename basic_json::value_type;
        /// a type to represent differences between iterators
        using difference_type = typename basic_json::difference_type;
        /// defines a pointer to the type iterated over (value_type)
        using pointer = typename basic_json::const_pointer;
        /// defines a reference to the type iterated over (value_type)
        using reference = typename basic_json::const_reference;
        /// the category of the iterator
        using iterator_category = std::bidirectional_iterator_tag;

        /// default constructor
        const_iterator() = default;

        /// constructor for a given JSON instance
        const_iterator(pointer object) noexcept : m_object(object)
        {
            switch (m_object->m_type)
            {
                case (basic_json::value_t::object):
                {
                    m_it.object_iterator = typename object_t::iterator();
                    break;
                }
                case (basic_json::value_t::array):
                {
                    m_it.array_iterator = typename array_t::iterator();
                    break;
                }
                default:
                {
                    m_it.generic_iterator = -1;
                    break;
                }
            }
        }

        /// copy constructor given a nonconst iterator
        const_iterator(const iterator& other) noexcept : m_object(other.m_object)
        {
            switch (m_object->m_type)
            {
                case (basic_json::value_t::object):
                {
                    m_it.object_iterator = other.m_it.object_iterator;
                    break;
                }

                case (basic_json::value_t::array):
                {
                    m_it.array_iterator = other.m_it.array_iterator;
                    break;
                }

                default:
                {
                    m_it.generic_iterator = other.m_it.generic_iterator;
                    break;
                }
            }
        }

        /// copy constructor
        const_iterator(const const_iterator& other) noexcept
            : m_object(other.m_object), m_it(other.m_it)
        {}

        /// copy assignment
        const_iterator& operator=(const_iterator other) noexcept(
            std::is_nothrow_move_constructible<pointer>::value and
            std::is_nothrow_move_assignable<pointer>::value and
            std::is_nothrow_move_constructible<internal_iterator>::value and
            std::is_nothrow_move_assignable<internal_iterator>::value
        )
        {
            std::swap(m_object, other.m_object);
            std::swap(m_it, other.m_it);
            return *this;
        }

      private:
        /// set the iterator to the first value
        void set_begin() noexcept
        {
            switch (m_object->m_type)
            {
                case (basic_json::value_t::object):
                {
                    m_it.object_iterator = m_object->m_value.object->begin();
                    break;
                }

                case (basic_json::value_t::array):
                {
                    m_it.array_iterator = m_object->m_value.array->begin();
                    break;
                }

                case (basic_json::value_t::null):
                {
                    // set to end so begin()==end() is true: null is empty
                    m_it.generic_iterator = 1;
                    break;
                }

                default:
                {
                    m_it.generic_iterator = 0;
                    break;
                }
            }
        }

        /// set the iterator past the last value
        void set_end() noexcept
        {
            switch (m_object->m_type)
            {
                case (basic_json::value_t::object):
                {
                    m_it.object_iterator = m_object->m_value.object->end();
                    break;
                }

                case (basic_json::value_t::array):
                {
                    m_it.array_iterator = m_object->m_value.array->end();
                    break;
                }

                default:
                {
                    m_it.generic_iterator = 1;
                    break;
                }
            }
        }

      public:
        /// return a reference to the value pointed to by the iterator
        reference operator*() const
        {
            switch (m_object->m_type)
            {
                case (basic_json::value_t::object):
                {
                    return m_it.object_iterator->second;
                }

                case (basic_json::value_t::array):
                {
                    return *m_it.array_iterator;
                }

                case (basic_json::value_t::null):
                {
                    throw std::out_of_range("cannot get value");
                }

                default:
                {
                    if (m_it.generic_iterator == 0)
                    {
                        return *m_object;
                    }
                    else
                    {
                        throw std::out_of_range("cannot get value");
                    }
                }
            }
        }

        /// dereference the iterator
        pointer operator->() const
        {
            switch (m_object->m_type)
            {
                case (basic_json::value_t::object):
                {
                    return &(m_it.object_iterator->second);
                }

                case (basic_json::value_t::array):
                {
                    return &*m_it.array_iterator;
                }

                default:
                {
                    if (m_it.generic_iterator == 0)
                    {
                        return m_object;
                    }
                    else
                    {
                        throw std::out_of_range("cannot get value");
                    }
                }
            }
        }

        /// post-increment (it++)
        const_iterator operator++(int)
        {
            auto result = *this;
            ++(*this);

            return result;
        }

        /// pre-increment (++it)
        const_iterator& operator++()
        {
            switch (m_object->m_type)
            {
                case (basic_json::value_t::object):
                {
                    ++m_it.object_iterator;
                    break;
                }

                case (basic_json::value_t::array):
                {
                    ++m_it.array_iterator;
                    break;
                }

                default:
                {
                    ++m_it.generic_iterator;
                    break;
                }
            }

            return *this;
        }

        /// post-decrement (it--)
        const_iterator operator--(int)
        {
            auto result = *this;
            --(*this);

            return result;
        }

        /// pre-decrement (--it)
        const_iterator& operator--()
        {
            switch (m_object->m_type)
            {
                case (basic_json::value_t::object):
                {
                    --m_it.object_iterator;
                    break;
                }

                case (basic_json::value_t::array):
                {
                    --m_it.array_iterator;
                    break;
                }

                default:
                {
                    --m_it.generic_iterator;
                    break;
                }
            }

            return *this;
        }

        /// comparison: equal
        bool operator==(const const_iterator& other) const
        {
            // if objects are not the same, the comparison is undefined
            if (m_object != other.m_object)
            {
                throw std::domain_error("cannot compare iterators of different containers");
            }

            switch (m_object->m_type)
            {
                case (basic_json::value_t::object):
                {
                    return (m_it.object_iterator == other.m_it.object_iterator);
                }

                case (basic_json::value_t::array):
                {
                    return (m_it.array_iterator == other.m_it.array_iterator);
                }

                default:
                {
                    return (m_it.generic_iterator == other.m_it.generic_iterator);
                }
            }
        }

        /// comparison: not equal
        bool operator!=(const const_iterator& other) const
        {
            return not operator==(other);
        }

        /// comparison: smaller
        bool operator<(const const_iterator& other) const
        {
            // if objects are not the same, the comparison is undefined
            if (m_object != other.m_object)
            {
                throw std::domain_error("cannot compare iterators of different containers");
            }

            switch (m_object->m_type)
            {
                case (basic_json::value_t::object):
                {
                    throw std::domain_error("cannot use operator< for object iterators");
                }

                case (basic_json::value_t::array):
                {
                    return (m_it.array_iterator < other.m_it.array_iterator);
                }

                default:
                {
                    return (m_it.generic_iterator < other.m_it.generic_iterator);
                }
            }
        }

        /// comparison: less than or equal
        bool operator<=(const const_iterator& other) const
        {
            return not other.operator < (*this);
        }

        /// comparison: greater than
        bool operator>(const const_iterator& other) const
        {
            return not operator<=(other);
        }

        /// comparison: greater than or equal
        bool operator>=(const const_iterator& other) const
        {
            return not operator<(other);
        }

        /// add to iterator
        const_iterator& operator+=(difference_type i)
        {
            switch (m_object->m_type)
            {
                case (basic_json::value_t::object):
                {
                    throw std::domain_error("cannot use operator+= for object iterators");
                }

                case (basic_json::value_t::array):
                {
                    m_it.array_iterator += i;
                    break;
                }

                default:
                {
                    m_it.generic_iterator += i;
                    break;
                }
            }

            return *this;
        }

        /// subtract from iterator
        const_iterator& operator-=(difference_type i)
        {
            return operator+=(-i);
        }

        /// add to iterator
        const_iterator operator+(difference_type i)
        {
            auto result = *this;
            result += i;
            return result;
        }

        /// subtract from iterator
        const_iterator operator-(difference_type i)
        {
            auto result = *this;
            result -= i;
            return result;
        }

        /// return difference
        difference_type operator-(const const_iterator& other) const
        {
            switch (m_object->m_type)
            {
                case (basic_json::value_t::object):
                {
                    throw std::domain_error("cannot use operator- for object iterators");
                }

                case (basic_json::value_t::array):
                {
                    return m_it.array_iterator - other.m_it.array_iterator;
                }

                default:
                {
                    return m_it.generic_iterator - other.m_it.generic_iterator;
                }
            }
        }

        /// access to successor
        reference operator[](difference_type n) const
        {
            switch (m_object->m_type)
            {
                case (basic_json::value_t::object):
                {
                    throw std::domain_error("cannot use operator[] for object iterators");
                }

                case (basic_json::value_t::array):
                {
                    return *(m_it.array_iterator + n);
                }

                case (basic_json::value_t::null):
                {
                    throw std::out_of_range("cannot get value");
                }

                default:
                {
                    if (m_it.generic_iterator == -n)
                    {
                        return *m_object;
                    }
                    else
                    {
                        throw std::out_of_range("cannot get value");
                    }
                }
            }
        }

        /// return the key of an object iterator
        typename object_t::key_type key() const
        {
            switch (m_object->m_type)
            {
                case (basic_json::value_t::object):
                {
                    return m_it.object_iterator->first;
                }

                default:
                {
                    throw std::domain_error("cannot use key() for non-object iterators");
                }
            }
        }

        /// return the value of an iterator
        reference value() const
        {
            return operator*();
        }

      private:
        /// associated JSON instance
        pointer m_object = nullptr;
        /// the actual iterator of the associated instance
        internal_iterator m_it = internal_iterator();
    };

    /// a reverse random access iterator for the basic_json class
    class reverse_iterator : public std::reverse_iterator<typename basic_json::iterator>
    {
      public:
        reverse_iterator(const typename
                         std::reverse_iterator<typename basic_json::iterator>::iterator_type&
                         it)
            : std::reverse_iterator<basic_json::iterator>(it) {}

        /// return the key of an object iterator
        typename object_t::key_type key() const
        {
            return this->base().key();
        }

        /// return the value of an iterator
        reference value() const
        {
            return this->base().operator * ();
        }
    };

    /// a const reverse random access iterator for the basic_json class
    class const_reverse_iterator : public std::reverse_iterator<typename basic_json::const_iterator>
    {
      public:
        const_reverse_iterator(const typename
                               std::reverse_iterator<typename basic_json::const_iterator>::iterator_type& it)
            : std::reverse_iterator<basic_json::const_iterator>(it) {}

        /// return the key of an object iterator
        typename object_t::key_type key() const
        {
            return this->base().key();
        }

        /// return the value of an iterator
        const_reference value() const
        {
            return this->base().operator * ();
        }
    };


  private:
    //////////////////////
    // lexer and parser //
    //////////////////////

    /*!
    @brief lexical analysis

    This class organizes the lexical analysis during JSON deserialization. The
    core of it is a scanner generated by re2c <http://re2c.org> that processes
    a buffer and recognizes tokens according to RFC 7159 and ECMA-404.
    */
    class lexer
    {
      public:
        /// token types for the parser
        enum class token_type
        {
            uninitialized,    ///< indicating the scanner is uninitialized
            literal_true,     ///< the "true" literal
            literal_false,    ///< the "false" literal
            literal_null,     ///< the "null" literal
            value_string,     ///< a string - use get_string() for actual value
            value_number,     ///< a number - use get_number() for actual value
            begin_array,      ///< the character for array begin "["
            begin_object,     ///< the character for object begin "{"
            end_array,        ///< the character for array end "]"
            end_object,       ///< the character for object end "}"
            name_separator,   ///< the name separator ":"
            value_separator,  ///< the value separator ","
            parse_error,      ///< indicating a parse error
            end_of_input      ///< indicating the end of the input buffer
        };

        /// the char type to use in the lexer
        using lexer_char_t = unsigned char;

        /// constructor with a given buffer
        lexer(const string_t& s) noexcept
            : m_stream(nullptr), m_buffer(s)
        {
            m_content = reinterpret_cast<const lexer_char_t*>(s.c_str());
            m_start = m_cursor = m_content;
            m_limit = m_content + s.size();
        }
        lexer(std::istream* s) noexcept
            : m_stream(s), m_buffer()
        {
            getline(*m_stream, m_buffer);
            m_content = reinterpret_cast<const lexer_char_t*>(m_buffer.c_str());
            m_start = m_cursor = m_content;
            m_limit = m_content + m_buffer.size();
        }

        /// default constructor
        lexer() = default;

        // switch of unwanted functions
        lexer(const lexer&) = delete;
        lexer operator=(const lexer&) = delete;

        /*!
        @brief create a string from a Unicode code point

        @param codepoint1  the code point (can be high surrogate)
        @param codepoint2  the code point (can be low surrogate or 0)
        @return string representation of the code point
        @exception std::out_of_range if code point is >0x10ffff
        @exception std::invalid_argument if the low surrogate is invalid

        @see <http://en.wikipedia.org/wiki/UTF-8#Sample_code>
        */
        static string_t to_unicode(const std::size_t codepoint1,
                                   const std::size_t codepoint2 = 0)
        {
            string_t result;

            // calculate the codepoint from the given code points
            std::size_t codepoint = codepoint1;

            // check if codepoint1 is a high surrogate
            if (codepoint1 >= 0xD800 and codepoint1 <= 0xDBFF)
            {
                // check if codepoint2 is a low surrogate
                if (codepoint2 >= 0xDC00 and codepoint2 <= 0xDFFF)
                {
                    codepoint =
                        // high surrogate occupies the most significant 22 bits
                        (codepoint1 << 10)
                        // low surrogate occupies the least significant 15 bits
                        + codepoint2
                        // there is still the 0xD800, 0xDC00 and 0x10000 noise
                        // in the result so we have to substract with:
                        // (0xD800 << 10) + DC00 - 0x10000 = 0x35FDC00
                        - 0x35FDC00;
                }
                else
                {
                    throw std::invalid_argument("missing or wrong low surrogate");
                }
            }

            if (codepoint < 0x80)
            {
                // 1-byte characters: 0xxxxxxx (ASCII)
                result.append(1, static_cast<typename string_t::value_type>(codepoint));
            }
            else if (codepoint <= 0x7ff)
            {
                // 2-byte characters: 110xxxxx 10xxxxxx
                result.append(1, static_cast<typename string_t::value_type>(0xC0 | ((codepoint >> 6) & 0x1F)));
                result.append(1, static_cast<typename string_t::value_type>(0x80 | (codepoint & 0x3F)));
            }
            else if (codepoint <= 0xffff)
            {
                // 3-byte characters: 1110xxxx 10xxxxxx 10xxxxxx
                result.append(1, static_cast<typename string_t::value_type>(0xE0 | ((codepoint >> 12) & 0x0F)));
                result.append(1, static_cast<typename string_t::value_type>(0x80 | ((codepoint >> 6) & 0x3F)));
                result.append(1, static_cast<typename string_t::value_type>(0x80 | (codepoint & 0x3F)));
            }
            else if (codepoint <= 0x10ffff)
            {
                // 4-byte characters: 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
                result.append(1, static_cast<typename string_t::value_type>(0xF0 | ((codepoint >> 18) & 0x07)));
                result.append(1, static_cast<typename string_t::value_type>(0x80 | ((codepoint >> 12) & 0x3F)));
                result.append(1, static_cast<typename string_t::value_type>(0x80 | ((codepoint >> 6) & 0x3F)));
                result.append(1, static_cast<typename string_t::value_type>(0x80 | (codepoint & 0x3F)));
            }
            else
            {
                throw std::out_of_range("code points above 0x10FFFF are invalid");
            }

            return result;
        }

        /// return name of values of type token_type
        static std::string token_type_name(token_type t) noexcept
        {
            switch (t)
            {
                case (token_type::uninitialized):
                    return "<uninitialized>";
                case (token_type::literal_true):
                    return "true literal";
                case (token_type::literal_false):
                    return "false literal";
                case (token_type::literal_null):
                    return "null literal";
                case (token_type::value_string):
                    return "string literal";
                case (token_type::value_number):
                    return "number literal";
                case (token_type::begin_array):
                    return "[";
                case (token_type::begin_object):
                    return "{";
                case (token_type::end_array):
                    return "]";
                case (token_type::end_object):
                    return "}";
                case (token_type::name_separator):
                    return ":";
                case (token_type::value_separator):
                    return ",";
                case (token_type::end_of_input):
                    return "<end of input>";
                default:
                    return "<parse error>";
            }
        }

        /*!
        This function implements a scanner for JSON. It is specified using
        regular expressions that try to follow RFC 7159 and ECMA-404 as close
        as possible. These regular expressions are then translated into a
        deterministic finite automaton (DFA) by the tool re2c
        <http://re2c.org>. As a result, the translated code for this function
        consists of a large block of code with goto jumps.

        @return the class of the next token read from the buffer
        */
        token_type scan() noexcept
        {
            // pointer for backtracking information
            m_marker = nullptr;

            // remember the begin of the token
            m_start = m_cursor;


            {
                lexer_char_t yych;
                unsigned int yyaccept = 0;
                static const unsigned char yybm[] =
                {
                    0,   0,   0,   0,   0,   0,   0,   0,
                    0,  32,  32,   0,   0,  32,   0,   0,
                    64,  64,  64,  64,  64,  64,  64,  64,
                    64,  64,  64,  64,  64,  64,  64,  64,
                    96,  64,   0,  64,  64,  64,  64,  64,
                    64,  64,  64,  64,  64,  64,  64,  64,
                    192, 192, 192, 192, 192, 192, 192, 192,
                    192, 192,  64,  64,  64,  64,  64,  64,
                    64,  64,  64,  64,  64,  64,  64,  64,
                    64,  64,  64,  64,  64,  64,  64,  64,
                    64,  64,  64,  64,  64,  64,  64,  64,
                    64,  64,  64,  64,   0,  64,  64,  64,
                    64,  64,  64,  64,  64,  64,  64,  64,
                    64,  64,  64,  64,  64,  64,  64,  64,
                    64,  64,  64,  64,  64,  64,  64,  64,
                    64,  64,  64,  64,  64,  64,  64,  64,
                    64,  64,  64,  64,  64,  64,  64,  64,
                    64,  64,  64,  64,  64,  64,  64,  64,
                    64,  64,  64,  64,  64,  64,  64,  64,
                    64,  64,  64,  64,  64,  64,  64,  64,
                    64,  64,  64,  64,  64,  64,  64,  64,
                    64,  64,  64,  64,  64,  64,  64,  64,
                    64,  64,  64,  64,  64,  64,  64,  64,
                    64,  64,  64,  64,  64,  64,  64,  64,
                    64,  64,  64,  64,  64,  64,  64,  64,
                    64,  64,  64,  64,  64,  64,  64,  64,
                    64,  64,  64,  64,  64,  64,  64,  64,
                    64,  64,  64,  64,  64,  64,  64,  64,
                    64,  64,  64,  64,  64,  64,  64,  64,
                    64,  64,  64,  64,  64,  64,  64,  64,
                    64,  64,  64,  64,  64,  64,  64,  64,
                    64,  64,  64,  64,  64,  64,  64,  64,
                };

                if ((m_limit - m_cursor) < 5)
                {
                    yyfill();    // LCOV_EXCL_LINE;
                }
                yych = *m_cursor;
                if (yych <= '9')
                {
                    if (yych <= ' ')
                    {
                        if (yych <= '\n')
                        {
                            if (yych <= 0x00)
                            {
                                goto basic_json_parser_27;
                            }
                            if (yych <= 0x08)
                            {
                                goto basic_json_parser_29;
                            }
                            if (yych >= '\n')
                            {
                                goto basic_json_parser_4;
                            }
                        }
                        else
                        {
                            if (yych == '\r')
                            {
                                goto basic_json_parser_2;
                            }
                            if (yych <= 0x1F)
                            {
                                goto basic_json_parser_29;
                            }
                        }
                    }
                    else
                    {
                        if (yych <= ',')
                        {
                            if (yych == '"')
                            {
                                goto basic_json_parser_26;
                            }
                            if (yych <= '+')
                            {
                                goto basic_json_parser_29;
                            }
                            goto basic_json_parser_14;
                        }
                        else
                        {
                            if (yych <= '-')
                            {
                                goto basic_json_parser_22;
                            }
                            if (yych <= '/')
                            {
                                goto basic_json_parser_29;
                            }
                            if (yych <= '0')
                            {
                                goto basic_json_parser_23;
                            }
                            goto basic_json_parser_25;
                        }
                    }
                }
                else
                {
                    if (yych <= 'm')
                    {
                        if (yych <= '\\')
                        {
                            if (yych <= ':')
                            {
                                goto basic_json_parser_16;
                            }
                            if (yych == '[')
                            {
                                goto basic_json_parser_6;
                            }
                            goto basic_json_parser_29;
                        }
                        else
                        {
                            if (yych <= ']')
                            {
                                goto basic_json_parser_8;
                            }
                            if (yych == 'f')
                            {
                                goto basic_json_parser_21;
                            }
                            goto basic_json_parser_29;
                        }
                    }
                    else
                    {
                        if (yych <= 'z')
                        {
                            if (yych <= 'n')
                            {
                                goto basic_json_parser_18;
                            }
                            if (yych == 't')
                            {
                                goto basic_json_parser_20;
                            }
                            goto basic_json_parser_29;
                        }
                        else
                        {
                            if (yych <= '{')
                            {
                                goto basic_json_parser_10;
                            }
                            if (yych == '}')
                            {
                                goto basic_json_parser_12;
                            }
                            goto basic_json_parser_29;
                        }
                    }
                }
basic_json_parser_2:
                ++m_cursor;
                yych = *m_cursor;
                goto basic_json_parser_5;
basic_json_parser_3:
                {
                    return scan();
                }
basic_json_parser_4:
                ++m_cursor;
                if (m_limit <= m_cursor)
                {
                    yyfill();    // LCOV_EXCL_LINE;
                }
                yych = *m_cursor;
basic_json_parser_5:
                if (yybm[0 + yych] & 32)
                {
                    goto basic_json_parser_4;
                }
                goto basic_json_parser_3;
basic_json_parser_6:
                ++m_cursor;
                {
                    return token_type::begin_array;
                }
basic_json_parser_8:
                ++m_cursor;
                {
                    return token_type::end_array;
                }
basic_json_parser_10:
                ++m_cursor;
                {
                    return token_type::begin_object;
                }
basic_json_parser_12:
                ++m_cursor;
                {
                    return token_type::end_object;
                }
basic_json_parser_14:
                ++m_cursor;
                {
                    return token_type::value_separator;
                }
basic_json_parser_16:
                ++m_cursor;
                {
                    return token_type::name_separator;
                }
basic_json_parser_18:
                yyaccept = 0;
                yych = *(m_marker = ++m_cursor);
                if (yych == 'u')
                {
                    goto basic_json_parser_59;
                }
basic_json_parser_19:
                {
                    return token_type::parse_error;
                }
basic_json_parser_20:
                yyaccept = 0;
                yych = *(m_marker = ++m_cursor);
                if (yych == 'r')
                {
                    goto basic_json_parser_55;
                }
                goto basic_json_parser_19;
basic_json_parser_21:
                yyaccept = 0;
                yych = *(m_marker = ++m_cursor);
                if (yych == 'a')
                {
                    goto basic_json_parser_50;
                }
                goto basic_json_parser_19;
basic_json_parser_22:
                yych = *++m_cursor;
                if (yych <= '/')
                {
                    goto basic_json_parser_19;
                }
                if (yych <= '0')
                {
                    goto basic_json_parser_49;
                }
                if (yych <= '9')
                {
                    goto basic_json_parser_40;
                }
                goto basic_json_parser_19;
basic_json_parser_23:
                yyaccept = 1;
                yych = *(m_marker = ++m_cursor);
                if (yych <= 'D')
                {
                    if (yych == '.')
                    {
                        goto basic_json_parser_42;
                    }
                }
                else
                {
                    if (yych <= 'E')
                    {
                        goto basic_json_parser_43;
                    }
                    if (yych == 'e')
                    {
                        goto basic_json_parser_43;
                    }
                }
basic_json_parser_24:
                {
                    return token_type::value_number;
                }
basic_json_parser_25:
                yyaccept = 1;
                yych = *(m_marker = ++m_cursor);
                goto basic_json_parser_41;
basic_json_parser_26:
                yyaccept = 0;
                yych = *(m_marker = ++m_cursor);
                if (yych <= 0x0F)
                {
                    goto basic_json_parser_19;
                }
                goto basic_json_parser_31;
basic_json_parser_27:
                ++m_cursor;
                {
                    return token_type::end_of_input;
                }
basic_json_parser_29:
                yych = *++m_cursor;
                goto basic_json_parser_19;
basic_json_parser_30:
                ++m_cursor;
                if (m_limit <= m_cursor)
                {
                    yyfill();    // LCOV_EXCL_LINE;
                }
                yych = *m_cursor;
basic_json_parser_31:
                if (yybm[0 + yych] & 64)
                {
                    goto basic_json_parser_30;
                }
                if (yych <= 0x0F)
                {
                    goto basic_json_parser_32;
                }
                if (yych <= '"')
                {
                    goto basic_json_parser_34;
                }
                goto basic_json_parser_33;
basic_json_parser_32:
                m_cursor = m_marker;
                if (yyaccept == 0)
                {
                    goto basic_json_parser_19;
                }
                else
                {
                    goto basic_json_parser_24;
                }
basic_json_parser_33:
                ++m_cursor;
                if (m_limit <= m_cursor)
                {
                    yyfill();    // LCOV_EXCL_LINE;
                }
                yych = *m_cursor;
                if (yych <= 'e')
                {
                    if (yych <= '/')
                    {
                        if (yych == '"')
                        {
                            goto basic_json_parser_30;
                        }
                        if (yych <= '.')
                        {
                            goto basic_json_parser_32;
                        }
                        goto basic_json_parser_30;
                    }
                    else
                    {
                        if (yych <= '\\')
                        {
                            if (yych <= '[')
                            {
                                goto basic_json_parser_32;
                            }
                            goto basic_json_parser_30;
                        }
                        else
                        {
                            if (yych == 'b')
                            {
                                goto basic_json_parser_30;
                            }
                            goto basic_json_parser_32;
                        }
                    }
                }
                else
                {
                    if (yych <= 'q')
                    {
                        if (yych <= 'f')
                        {
                            goto basic_json_parser_30;
                        }
                        if (yych == 'n')
                        {
                            goto basic_json_parser_30;
                        }
                        goto basic_json_parser_32;
                    }
                    else
                    {
                        if (yych <= 's')
                        {
                            if (yych <= 'r')
                            {
                                goto basic_json_parser_30;
                            }
                            goto basic_json_parser_32;
                        }
                        else
                        {
                            if (yych <= 't')
                            {
                                goto basic_json_parser_30;
                            }
                            if (yych <= 'u')
                            {
                                goto basic_json_parser_36;
                            }
                            goto basic_json_parser_32;
                        }
                    }
                }
basic_json_parser_34:
                ++m_cursor;
                {
                    return token_type::value_string;
                }
basic_json_parser_36:
                ++m_cursor;
                if (m_limit <= m_cursor)
                {
                    yyfill();    // LCOV_EXCL_LINE;
                }
                yych = *m_cursor;
                if (yych <= '@')
                {
                    if (yych <= '/')
                    {
                        goto basic_json_parser_32;
                    }
                    if (yych >= ':')
                    {
                        goto basic_json_parser_32;
                    }
                }
                else
                {
                    if (yych <= 'F')
                    {
                        goto basic_json_parser_37;
                    }
                    if (yych <= '`')
                    {
                        goto basic_json_parser_32;
                    }
                    if (yych >= 'g')
                    {
                        goto basic_json_parser_32;
                    }
                }
basic_json_parser_37:
                ++m_cursor;
                if (m_limit <= m_cursor)
                {
                    yyfill();    // LCOV_EXCL_LINE;
                }
                yych = *m_cursor;
                if (yych <= '@')
                {
                    if (yych <= '/')
                    {
                        goto basic_json_parser_32;
                    }
                    if (yych >= ':')
                    {
                        goto basic_json_parser_32;
                    }
                }
                else
                {
                    if (yych <= 'F')
                    {
                        goto basic_json_parser_38;
                    }
                    if (yych <= '`')
                    {
                        goto basic_json_parser_32;
                    }
                    if (yych >= 'g')
                    {
                        goto basic_json_parser_32;
                    }
                }
basic_json_parser_38:
                ++m_cursor;
                if (m_limit <= m_cursor)
                {
                    yyfill();    // LCOV_EXCL_LINE;
                }
                yych = *m_cursor;
                if (yych <= '@')
                {
                    if (yych <= '/')
                    {
                        goto basic_json_parser_32;
                    }
                    if (yych >= ':')
                    {
                        goto basic_json_parser_32;
                    }
                }
                else
                {
                    if (yych <= 'F')
                    {
                        goto basic_json_parser_39;
                    }
                    if (yych <= '`')
                    {
                        goto basic_json_parser_32;
                    }
                    if (yych >= 'g')
                    {
                        goto basic_json_parser_32;
                    }
                }
basic_json_parser_39:
                ++m_cursor;
                if (m_limit <= m_cursor)
                {
                    yyfill();    // LCOV_EXCL_LINE;
                }
                yych = *m_cursor;
                if (yych <= '@')
                {
                    if (yych <= '/')
                    {
                        goto basic_json_parser_32;
                    }
                    if (yych <= '9')
                    {
                        goto basic_json_parser_30;
                    }
                    goto basic_json_parser_32;
                }
                else
                {
                    if (yych <= 'F')
                    {
                        goto basic_json_parser_30;
                    }
                    if (yych <= '`')
                    {
                        goto basic_json_parser_32;
                    }
                    if (yych <= 'f')
                    {
                        goto basic_json_parser_30;
                    }
                    goto basic_json_parser_32;
                }
basic_json_parser_40:
                yyaccept = 1;
                m_marker = ++m_cursor;
                if ((m_limit - m_cursor) < 3)
                {
                    yyfill();    // LCOV_EXCL_LINE;
                }
                yych = *m_cursor;
basic_json_parser_41:
                if (yybm[0 + yych] & 128)
                {
                    goto basic_json_parser_40;
                }
                if (yych <= 'D')
                {
                    if (yych != '.')
                    {
                        goto basic_json_parser_24;
                    }
                }
                else
                {
                    if (yych <= 'E')
                    {
                        goto basic_json_parser_43;
                    }
                    if (yych == 'e')
                    {
                        goto basic_json_parser_43;
                    }
                    goto basic_json_parser_24;
                }
basic_json_parser_42:
                yych = *++m_cursor;
                if (yych <= '/')
                {
                    goto basic_json_parser_32;
                }
                if (yych <= '9')
                {
                    goto basic_json_parser_47;
                }
                goto basic_json_parser_32;
basic_json_parser_43:
                yych = *++m_cursor;
                if (yych <= ',')
                {
                    if (yych != '+')
                    {
                        goto basic_json_parser_32;
                    }
                }
                else
                {
                    if (yych <= '-')
                    {
                        goto basic_json_parser_44;
                    }
                    if (yych <= '/')
                    {
                        goto basic_json_parser_32;
                    }
                    if (yych <= '9')
                    {
                        goto basic_json_parser_45;
                    }
                    goto basic_json_parser_32;
                }
basic_json_parser_44:
                yych = *++m_cursor;
                if (yych <= '/')
                {
                    goto basic_json_parser_32;
                }
                if (yych >= ':')
                {
                    goto basic_json_parser_32;
                }
basic_json_parser_45:
                ++m_cursor;
                if (m_limit <= m_cursor)
                {
                    yyfill();    // LCOV_EXCL_LINE;
                }
                yych = *m_cursor;
                if (yych <= '/')
                {
                    goto basic_json_parser_24;
                }
                if (yych <= '9')
                {
                    goto basic_json_parser_45;
                }
                goto basic_json_parser_24;
basic_json_parser_47:
                yyaccept = 1;
                m_marker = ++m_cursor;
                if ((m_limit - m_cursor) < 3)
                {
                    yyfill();    // LCOV_EXCL_LINE;
                }
                yych = *m_cursor;
                if (yych <= 'D')
                {
                    if (yych <= '/')
                    {
                        goto basic_json_parser_24;
                    }
                    if (yych <= '9')
                    {
                        goto basic_json_parser_47;
                    }
                    goto basic_json_parser_24;
                }
                else
                {
                    if (yych <= 'E')
                    {
                        goto basic_json_parser_43;
                    }
                    if (yych == 'e')
                    {
                        goto basic_json_parser_43;
                    }
                    goto basic_json_parser_24;
                }
basic_json_parser_49:
                yyaccept = 1;
                yych = *(m_marker = ++m_cursor);
                if (yych <= 'D')
                {
                    if (yych == '.')
                    {
                        goto basic_json_parser_42;
                    }
                    goto basic_json_parser_24;
                }
                else
                {
                    if (yych <= 'E')
                    {
                        goto basic_json_parser_43;
                    }
                    if (yych == 'e')
                    {
                        goto basic_json_parser_43;
                    }
                    goto basic_json_parser_24;
                }
basic_json_parser_50:
                yych = *++m_cursor;
                if (yych != 'l')
                {
                    goto basic_json_parser_32;
                }
                yych = *++m_cursor;
                if (yych != 's')
                {
                    goto basic_json_parser_32;
                }
                yych = *++m_cursor;
                if (yych != 'e')
                {
                    goto basic_json_parser_32;
                }
                ++m_cursor;
                {
                    return token_type::literal_false;
                }
basic_json_parser_55:
                yych = *++m_cursor;
                if (yych != 'u')
                {
                    goto basic_json_parser_32;
                }
                yych = *++m_cursor;
                if (yych != 'e')
                {
                    goto basic_json_parser_32;
                }
                ++m_cursor;
                {
                    return token_type::literal_true;
                }
basic_json_parser_59:
                yych = *++m_cursor;
                if (yych != 'l')
                {
                    goto basic_json_parser_32;
                }
                yych = *++m_cursor;
                if (yych != 'l')
                {
                    goto basic_json_parser_32;
                }
                ++m_cursor;
                {
                    return token_type::literal_null;
                }
            }


        }

        /// append data from the stream to the internal buffer
        void yyfill() noexcept
        {
            if (not m_stream or not * m_stream)
            {
                return;
            }

            const ssize_t offset_start = m_start - m_content;
            const ssize_t offset_marker = m_marker - m_start;
            const ssize_t offset_cursor = m_cursor - m_start;

            m_buffer.erase(0, static_cast<size_t>(offset_start));
            std::string line;
            std::getline(*m_stream, line);
            m_buffer += "\n" + line; // add line with newline symbol

            m_content = reinterpret_cast<const lexer_char_t*>(m_buffer.c_str());
            m_start  = m_content;
            m_marker = m_start + offset_marker;
            m_cursor = m_start + offset_cursor;
            m_limit  = m_start + m_buffer.size() - 1;
        }

        /// return string representation of last read token
        string_t get_token() const noexcept
        {
            return string_t(reinterpret_cast<typename string_t::const_pointer>(m_start),
                            static_cast<size_t>(m_cursor - m_start));
        }

        /*!
        @brief return string value for string tokens

        The function iterates the characters between the opening and closing
        quotes of the string value. The complete string is the range
        [m_start,m_cursor). Consequently, we iterate from m_start+1 to
        m_cursor-1.

        We differentiate two cases:

        1. Escaped characters. In this case, a new character is constructed
           according to the nature of the escape. Some escapes create new
           characters (e.g., @c "\\n" is replaced by @c "\n"), some are copied
           as is (e.g., @c "\\\\"). Furthermore, Unicode escapes of the shape
           @c "\\uxxxx" need special care. In this case, to_unicode takes care
           of the construction of the values.
        2. Unescaped characters are copied as is.

        @return string value of current token without opening and closing quotes
        @exception std::out_of_range if to_unicode fails
        */
        string_t get_string() const
        {
            string_t result;
            result.reserve(static_cast<size_t>(m_cursor - m_start - 2));

            // iterate the result between the quotes
            for (const lexer_char_t* i = m_start + 1; i < m_cursor - 1; ++i)
            {
                // process escaped characters
                if (*i == '\\')
                {
                    // read next character
                    ++i;

                    switch (*i)
                    {
                        // the default escapes
                        case 't':
                        {
                            result += "\t";
                            break;
                        }
                        case 'b':
                        {
                            result += "\b";
                            break;
                        }
                        case 'f':
                        {
                            result += "\f";
                            break;
                        }
                        case 'n':
                        {
                            result += "\n";
                            break;
                        }
                        case 'r':
                        {
                            result += "\r";
                            break;
                        }
                        case '\\':
                        {
                            result += "\\";
                            break;
                        }
                        case '/':
                        {
                            result += "/";
                            break;
                        }
                        case '"':
                        {
                            result += "\"";
                            break;
                        }

                        // unicode
                        case 'u':
                        {
                            // get code xxxx from uxxxx
                            auto codepoint = std::strtoul(std::string(reinterpret_cast<typename string_t::const_pointer>(i + 1),
                                                          4).c_str(), nullptr, 16);

                            // check if codepoint is a high surrogate
                            if (codepoint >= 0xD800 and codepoint <= 0xDBFF)
                            {
                                // make sure there is a subsequent unicode
                                if ((i + 6 >= m_limit) or * (i + 5) != '\\' or * (i + 6) != 'u')
                                {
                                    throw std::invalid_argument("missing low surrogate");
                                }

                                // get code yyyy from uxxxx\uyyyy
                                auto codepoint2 = std::strtoul(std::string(reinterpret_cast<typename string_t::const_pointer>
                                                               (i + 7), 4).c_str(), nullptr, 16);
                                result += to_unicode(codepoint, codepoint2);
                                // skip the next 11 characters (xxxx\uyyyy)
                                i += 11;
                            }
                            else
                            {
                                // add unicode character(s)
                                result += to_unicode(codepoint);
                                // skip the next four characters (xxxx)
                                i += 4;
                            }
                            break;
                        }
                    }
                }
                else
                {
                    // all other characters are just copied to the end of the
                    // string
                    result.append(1, static_cast<typename string_t::value_type>(*i));
                }
            }

            return result;
        }

        /*!
        @brief return number value for number tokens

        This function translates the last token into a floating point number.
        The pointer m_begin points to the beginning of the parsed number. We
        pass this pointer to std::strtod which sets endptr to the first
        character past the converted number. If this pointer is not the same as
        m_cursor, then either more or less characters have been used during the
        comparison. This can happen for inputs like "01" which will be treated
        like number 0 followed by number 1.

        @return the result of the number conversion or NAN if the conversion
        read past the current token. The latter case needs to be treated by the
        caller function.

        @exception std::range_error if passed value is out of range
        */
        long double get_number() const
        {
            // conversion
            typename string_t::value_type* endptr;
            const auto float_val = std::strtold(reinterpret_cast<typename string_t::const_pointer>(m_start),
                                                &endptr);

            // return float_val if the whole number was translated and NAN
            // otherwise
            return (reinterpret_cast<lexer_char_t*>(endptr) == m_cursor) ? float_val : NAN;
        }

      private:
        /// optional input stream
        std::istream* m_stream;
        /// the buffer
        string_t m_buffer;
        /// the buffer pointer
        const lexer_char_t* m_content = nullptr;
        /// pointer to the beginning of the current symbol
        const lexer_char_t* m_start = nullptr;
        /// pointer for backtracking information
        const lexer_char_t* m_marker = nullptr;
        /// pointer to the current symbol
        const lexer_char_t* m_cursor = nullptr;
        /// pointer to the end of the buffer
        const lexer_char_t* m_limit = nullptr;
    };

    /*!
    @brief syntax analysis
    */
    class parser
    {
      public:
        /// constructor for strings
        parser(const string_t& s, parser_callback_t cb = nullptr) : callback(cb), m_lexer(s)
        {
            // read first token
            get_token();
        }

        /// a parser reading from an input stream
        parser(std::istream& _is, parser_callback_t cb = nullptr) : callback(cb),
            m_lexer(&_is)
        {
            // read first token
            get_token();
        }

        /// public parser interface
        basic_json parse()
        {
            basic_json result = parse_internal(true);

            expect(lexer::token_type::end_of_input);

            return result;
        }

      private:
        /// the actual parser
        basic_json parse_internal(bool keep)
        {
            auto result = basic_json(value_t::discarded);

            switch (last_token)
            {
                case (lexer::token_type::begin_object):
                {
                    if (keep and (not callback or (keep = callback(depth++, parse_event_t::object_start, result))))
                    {
                        // explicitly set result to object to cope with {}
                        result.m_type = value_t::object;
                        result.m_value = json_value(value_t::object);
                    }

                    // read next token
                    get_token();

                    // closing } -> we are done
                    if (last_token == lexer::token_type::end_object)
                    {
                        get_token();
                        if (keep and callback and not callback(--depth, parse_event_t::object_end, result))
                        {
                            result = basic_json(value_t::discarded);
                        }
                        return result;
                    }

                    // no comma is expected here
                    unexpect(lexer::token_type::value_separator);

                    // otherwise: parse key-value pairs
                    do
                    {
                        // ugly, but could be fixed with loop reorganization
                        if (last_token == lexer::token_type::value_separator)
                        {
                            get_token();
                        }

                        // store key
                        expect(lexer::token_type::value_string);
                        const auto key = m_lexer.get_string();

                        bool keep_tag = false;
                        if (keep)
                        {
                            keep_tag = callback ? callback(depth, parse_event_t::key, basic_json(key)) : true;
                        }

                        // parse separator (:)
                        get_token();
                        expect(lexer::token_type::name_separator);

                        // parse and add value
                        get_token();
                        auto value = parse_internal(keep);
                        if (keep and keep_tag and not value.is_discarded())
                        {
                            result[key] = std::move(value);
                        }
                    }
                    while (last_token == lexer::token_type::value_separator);

                    // closing }
                    expect(lexer::token_type::end_object);
                    get_token();
                    if (keep and callback and not callback(--depth, parse_event_t::object_end, result))
                    {
                        result = basic_json(value_t::discarded);
                    }

                    return result;
                }

                case (lexer::token_type::begin_array):
                {
                    if (keep and (not callback or (keep = callback(depth++, parse_event_t::array_start, result))))
                    {
                        // explicitly set result to object to cope with []
                        result.m_type = value_t::array;
                        result.m_value = json_value(value_t::array);
                    }

                    // read next token
                    get_token();

                    // closing ] -> we are done
                    if (last_token == lexer::token_type::end_array)
                    {
                        get_token();
                        if (callback and not callback(--depth, parse_event_t::array_end, result))
                        {
                            result = basic_json(value_t::discarded);
                        }
                        return result;
                    }

                    // no comma is expected here
                    unexpect(lexer::token_type::value_separator);

                    // otherwise: parse values
                    do
                    {
                        // ugly, but could be fixed with loop reorganization
                        if (last_token == lexer::token_type::value_separator)
                        {
                            get_token();
                        }

                        // parse value
                        auto value = parse_internal(keep);
                        if (keep and not value.is_discarded())
                        {
                            result.push_back(std::move(value));
                        }
                    }
                    while (last_token == lexer::token_type::value_separator);

                    // closing ]
                    expect(lexer::token_type::end_array);
                    get_token();
                    if (keep and callback and not callback(--depth, parse_event_t::array_end, result))
                    {
                        result = basic_json(value_t::discarded);
                    }

                    return result;
                }

                case (lexer::token_type::literal_null):
                {
                    get_token();
                    result.m_type = value_t::null;
                    break;
                }

                case (lexer::token_type::value_string):
                {
                    const auto s = m_lexer.get_string();
                    get_token();
                    result = basic_json(s);
                    break;
                }

                case (lexer::token_type::literal_true):
                {
                    get_token();
                    result.m_type = value_t::boolean;
                    result.m_value = true;
                    break;
                }

                case (lexer::token_type::literal_false):
                {
                    get_token();
                    result.m_type = value_t::boolean;
                    result.m_value = false;
                    break;
                }

                case (lexer::token_type::value_number):
                {
                    auto float_val = m_lexer.get_number();

                    // NAN is returned if token could not be translated
                    // completely
                    if (std::isnan(float_val))
                    {
                        throw std::invalid_argument(std::string("parse error - ") +
                                                    m_lexer.get_token() + " is not a number");
                    }

                    get_token();

                    // check if conversion loses precision
                    const auto int_val = static_cast<number_integer_t>(float_val);
                    if (approx(float_val, static_cast<long double>(int_val)))
                    {
                        // we basic_json not lose precision -> return int
                        result.m_type = value_t::number_integer;
                        result.m_value = int_val;
                    }
                    else
                    {
                        // we would lose precision -> returnfloat
                        result.m_type = value_t::number_float;
                        result.m_value = static_cast<number_float_t>(float_val);
                    }
                    break;
                }

                default:
                {
                    // the last token was unexpected
                    unexpect(last_token);
                }
            }

            if (keep and callback and not callback(depth, parse_event_t::value, result))
            {
                result = basic_json(value_t::discarded);
            }
            return result;
        }

        /// get next token from lexer
        typename lexer::token_type get_token()
        {
            last_token = m_lexer.scan();
            return last_token;
        }

        void expect(typename lexer::token_type t) const
        {
            if (t != last_token)
            {
                std::string error_msg = "parse error - unexpected \'";
                error_msg += m_lexer.get_token();
                error_msg += "\' (" + lexer::token_type_name(last_token);
                error_msg += "); expected " + lexer::token_type_name(t);
                throw std::invalid_argument(error_msg);
            }
        }

        void unexpect(typename lexer::token_type t) const
        {
            if (t == last_token)
            {
                std::string error_msg = "parse error - unexpected \'";
                error_msg += m_lexer.get_token();
                error_msg += "\' (";
                error_msg += lexer::token_type_name(last_token) + ")";
                throw std::invalid_argument(error_msg);
            }
        }

      private:
        /// levels of recursion
        int depth = 0;
        /// callback function
        parser_callback_t callback;
        /// the type of the last read token
        typename lexer::token_type last_token = lexer::token_type::uninitialized;
        /// the lexer
        lexer m_lexer;
    };
};


/////////////
// presets //
/////////////

/*!
@brief default JSON class

This type is the default specialization of the @ref basic_json class which uses
the standard template types.
*/
using json = basic_json<>;
}


/////////////////////////
// nonmember functions //
/////////////////////////

// specialization of std::swap, and std::hash
namespace std
{
/*!
@brief exchanges the values of two JSON objects
@ingroup container
*/
template <>
inline void swap(nlohmann::json& j1,
                 nlohmann::json& j2) noexcept(
                     is_nothrow_move_constructible<nlohmann::json>::value and
                     is_nothrow_move_assignable<nlohmann::json>::value
                 )
{
    j1.swap(j2);
}

/// hash value for JSON objects
template <>
struct hash<nlohmann::json>
{
    /// return a hash value for a JSON object
    std::size_t operator()(const nlohmann::json& j) const
    {
        // a naive hashing via the string representation
        const auto& h = hash<nlohmann::json::string_t>();
        return h(j.dump());
    }
};
}

/*!
This operator implements a user-defined string literal for JSON objects. It can
be used by adding \p "_json" to a string literal and returns a JSON object if
no parse error occurred.

@param s  a string representation of a JSON object
@return a JSON object
*/
inline nlohmann::json operator "" _json(const char* s, std::size_t)
{
    return nlohmann::json::parse(reinterpret_cast<nlohmann::json::string_t::value_type*>
                                 (const_cast<char*>(s)));
}

#endif
