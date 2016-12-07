/*
    __ _____ _____ _____
 __|  |   __|     |   | |  JSON for Modern C++ (test suite)
|  |  |__   |  |  | | | |  version 2.0.7
|_____|_____|_____|_|___|  https://github.com/nlohmann/json

Licensed under the MIT License <http://opensource.org/licenses/MIT>.
Copyright (c) 2013-2016 Niels Lohmann <http://nlohmann.me>.

Permission is hereby  granted, free of charge, to any  person obtaining a copy
of this software and associated  documentation files (the "Software"), to deal
in the Software  without restriction, including without  limitation the rights
to  use, copy,  modify, merge,  publish, distribute,  sublicense, and/or  sell
copies  of  the Software,  and  to  permit persons  to  whom  the Software  is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE  IS PROVIDED "AS  IS", WITHOUT WARRANTY  OF ANY KIND,  EXPRESS OR
IMPLIED,  INCLUDING BUT  NOT  LIMITED TO  THE  WARRANTIES OF  MERCHANTABILITY,
FITNESS FOR  A PARTICULAR PURPOSE AND  NONINFRINGEMENT. IN NO EVENT  SHALL THE
AUTHORS  OR COPYRIGHT  HOLDERS  BE  LIABLE FOR  ANY  CLAIM,  DAMAGES OR  OTHER
LIABILITY, WHETHER IN AN ACTION OF  CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE  OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "catch.hpp"

#include "json.hpp"
using nlohmann::json;

#include <fstream>

TEST_CASE("CBOR")
{
    SECTION("individual values")
    {
        SECTION("null")
        {
            json j = nullptr;
            std::vector<uint8_t> expected = {0xf6};
            const auto result = json::to_cbor(j);
            CHECK(result == expected);

            // roundtrip
            CHECK(json::from_cbor(result) == j);
        }

        SECTION("boolean")
        {
            SECTION("true")
            {
                json j = true;
                std::vector<uint8_t> expected = {0xf5};
                const auto result = json::to_cbor(j);
                CHECK(result == expected);

                // roundtrip
                CHECK(json::from_cbor(result) == j);
            }

            SECTION("false")
            {
                json j = false;
                std::vector<uint8_t> expected = {0xf4};
                const auto result = json::to_cbor(j);
                CHECK(result == expected);

                // roundtrip
                CHECK(json::from_cbor(result) == j);
            }
        }

        SECTION("number")
        {
            SECTION("signed")
            {
                SECTION("-65535..-257")
                {
                    for (int16_t i = -65535; i <= -257; ++i)
                    {
                        CAPTURE(i);

                        // create JSON value with integer number
                        json j = i;

                        // check type
                        CHECK(j.is_number_integer());

                        // create expected byte vector
                        std::vector<uint8_t> expected;
                        expected.push_back(static_cast<uint8_t>(0x39));
                        uint16_t positive = static_cast<uint16_t>(-1 - i);
                        expected.push_back(static_cast<uint8_t>((positive >> 8) & 0xff));
                        expected.push_back(static_cast<uint8_t>(positive & 0xff));

                        // compare result + size
                        const auto result = json::to_cbor(j);
                        CHECK(result == expected);
                        CHECK(result.size() == 3);

                        // check individual bytes
                        CHECK(result[0] == 0x39);
                        uint16_t restored = static_cast<uint8_t>(result[1]) * 256 + static_cast<uint8_t>(result[2]);
                        CHECK(restored == positive);
                        CHECK(-1 - restored == i);

                        // roundtrip
                        CHECK(json::from_cbor(result) == j);
                    }
                }

                SECTION("-9263 (int 16)")
                {
                    json j = -9263;
                    std::vector<uint8_t> expected = {0x39, 0x24, 0x2e};

                    const auto result = json::to_cbor(j);
                    CHECK(result == expected);

                    int16_t restored = -1 - ((result[1] << 8) + result[2]);
                    CHECK(restored == -9263);

                    // roundtrip
                    CHECK(json::from_cbor(result) == j);
                }

                SECTION("-256..-24")
                {
                    for (auto i = -256; i < -24; ++i)
                    {
                        CAPTURE(i);

                        // create JSON value with integer number
                        json j = i;

                        // check type
                        CHECK(j.is_number_integer());

                        // create expected byte vector
                        std::vector<uint8_t> expected;
                        expected.push_back(0x38);
                        expected.push_back(static_cast<uint8_t>(-1 - i));

                        // compare result + size
                        const auto result = json::to_cbor(j);
                        CHECK(result == expected);
                        CHECK(result.size() == 2);

                        // check individual bytes
                        CHECK(result[0] == 0x38);
                        CHECK(static_cast<int16_t>(-1 - result[1]) == i);

                        // roundtrip
                        CHECK(json::from_cbor(result) == j);
                    }
                }

                SECTION("-24..-1")
                {
                    for (auto i = -24; i <= -1; ++i)
                    {
                        CAPTURE(i);

                        // create JSON value with integer number
                        json j = i;

                        // check type
                        CHECK(j.is_number_integer());

                        // create expected byte vector
                        std::vector<uint8_t> expected;
                        expected.push_back(0x20 - 1 - static_cast<uint8_t>(i));

                        // compare result + size
                        const auto result = json::to_cbor(j);
                        CHECK(result == expected);
                        CHECK(result.size() == 1);

                        // check individual bytes
                        CHECK(static_cast<int8_t>(0x20 - 1 - result[0]) == i);

                        // roundtrip
                        CHECK(json::from_cbor(result) == j);
                    }
                }

                SECTION("0..23")
                {
                    for (size_t i = 0; i <= 23; ++i)
                    {
                        CAPTURE(i);

                        // create JSON value with integer number
                        json j = -1;
                        j.get_ref<json::number_integer_t&>() = static_cast<json::number_integer_t>(i);

                        // check type
                        CHECK(j.is_number_integer());

                        // create expected byte vector
                        std::vector<uint8_t> expected;
                        expected.push_back(static_cast<uint8_t>(i));

                        // compare result + size
                        const auto result = json::to_cbor(j);
                        CHECK(result == expected);
                        CHECK(result.size() == 1);

                        // check individual bytes
                        CHECK(result[0] == i);

                        // roundtrip
                        CHECK(json::from_cbor(result) == j);
                    }
                }

                SECTION("24..255")
                {
                    for (size_t i = 24; i <= 255; ++i)
                    {
                        CAPTURE(i);

                        // create JSON value with integer number
                        json j = -1;
                        j.get_ref<json::number_integer_t&>() = static_cast<json::number_integer_t>(i);

                        // check type
                        CHECK(j.is_number_integer());

                        // create expected byte vector
                        std::vector<uint8_t> expected;
                        expected.push_back(static_cast<uint8_t>(0x18));
                        expected.push_back(static_cast<uint8_t>(i));

                        // compare result + size
                        const auto result = json::to_cbor(j);
                        CHECK(result == expected);
                        CHECK(result.size() == 2);

                        // check individual bytes
                        CHECK(result[0] == 0x18);
                        CHECK(result[1] == i);

                        // roundtrip
                        CHECK(json::from_cbor(result) == j);
                    }
                }

                SECTION("256..65535")
                {
                    for (size_t i = 256; i <= 65535; ++i)
                    {
                        CAPTURE(i);

                        // create JSON value with integer number
                        json j = -1;
                        j.get_ref<json::number_integer_t&>() = static_cast<json::number_integer_t>(i);

                        // check type
                        CHECK(j.is_number_integer());

                        // create expected byte vector
                        std::vector<uint8_t> expected;
                        expected.push_back(static_cast<uint8_t>(0x19));
                        expected.push_back(static_cast<uint8_t>((i >> 8) & 0xff));
                        expected.push_back(static_cast<uint8_t>(i & 0xff));

                        // compare result + size
                        const auto result = json::to_cbor(j);
                        CHECK(result == expected);
                        CHECK(result.size() == 3);

                        // check individual bytes
                        CHECK(result[0] == 0x19);
                        uint16_t restored = static_cast<uint8_t>(result[1]) * 256 + static_cast<uint8_t>(result[2]);
                        CHECK(restored == i);

                        // roundtrip
                        CHECK(json::from_cbor(result) == j);
                    }
                }

                SECTION("65536..4294967295")
                {
                    for (uint32_t i :
                            {
                                65536u, 77777u, 1048576u
                            })
                    {
                        CAPTURE(i);

                        // create JSON value with integer number
                        json j = -1;
                        j.get_ref<json::number_integer_t&>() = static_cast<json::number_integer_t>(i);

                        // check type
                        CHECK(j.is_number_integer());

                        // create expected byte vector
                        std::vector<uint8_t> expected;
                        expected.push_back(0x1a);
                        expected.push_back(static_cast<uint8_t>((i >> 24) & 0xff));
                        expected.push_back(static_cast<uint8_t>((i >> 16) & 0xff));
                        expected.push_back(static_cast<uint8_t>((i >> 8) & 0xff));
                        expected.push_back(static_cast<uint8_t>(i & 0xff));

                        // compare result + size
                        const auto result = json::to_cbor(j);
                        CHECK(result == expected);
                        CHECK(result.size() == 5);

                        // check individual bytes
                        CHECK(result[0] == 0x1a);
                        uint32_t restored = static_cast<uint32_t>((static_cast<uint32_t>(result[1]) << 030) +
                                            (static_cast<uint32_t>(result[2]) << 020) +
                                            (static_cast<uint32_t>(result[3]) << 010) +
                                            static_cast<uint32_t>(result[4]));
                        CHECK(restored == i);

                        // roundtrip
                        CHECK(json::from_cbor(result) == j);
                    }
                }

                SECTION("4294967296..4611686018427387903")
                {
                    for (uint64_t i :
                            {
                                4294967296ul, 4611686018427387903ul
                            })
                    {
                        CAPTURE(i);

                        // create JSON value with integer number
                        json j = -1;
                        j.get_ref<json::number_integer_t&>() = static_cast<json::number_integer_t>(i);

                        // check type
                        CHECK(j.is_number_integer());

                        // create expected byte vector
                        std::vector<uint8_t> expected;
                        expected.push_back(0x1b);
                        expected.push_back(static_cast<uint8_t>((i >> 070) & 0xff));
                        expected.push_back(static_cast<uint8_t>((i >> 060) & 0xff));
                        expected.push_back(static_cast<uint8_t>((i >> 050) & 0xff));
                        expected.push_back(static_cast<uint8_t>((i >> 040) & 0xff));
                        expected.push_back(static_cast<uint8_t>((i >> 030) & 0xff));
                        expected.push_back(static_cast<uint8_t>((i >> 020) & 0xff));
                        expected.push_back(static_cast<uint8_t>((i >> 010) & 0xff));
                        expected.push_back(static_cast<uint8_t>(i & 0xff));

                        // compare result + size
                        const auto result = json::to_cbor(j);
                        CHECK(result == expected);
                        CHECK(result.size() == 9);

                        // check individual bytes
                        CHECK(result[0] == 0x1b);
                        uint64_t restored = static_cast<uint64_t>((static_cast<uint64_t>(result[1]) << 070) +
                                            (static_cast<uint64_t>(result[2]) << 060) +
                                            (static_cast<uint64_t>(result[3]) << 050) +
                                            (static_cast<uint64_t>(result[4]) << 040) +
                                            (static_cast<uint64_t>(result[5]) << 030) +
                                            (static_cast<uint64_t>(result[6]) << 020) +
                                            (static_cast<uint64_t>(result[7]) << 010) +
                                            static_cast<uint64_t>(result[8]));
                        CHECK(restored == i);

                        // roundtrip
                        CHECK(json::from_cbor(result) == j);
                    }
                }

                /*
                SECTION("-32768..-129 (int 16)")
                {
                    for (int16_t i = -32768; i <= -129; ++i)
                    {
                        CAPTURE(i);

                        // create JSON value with integer number
                        json j = i;

                        // check type
                        CHECK(j.is_number_integer());

                        // create expected byte vector
                        std::vector<uint8_t> expected;
                        expected.push_back(0xd1);
                        expected.push_back(static_cast<uint8_t>((i >> 8) & 0xff));
                        expected.push_back(static_cast<uint8_t>(i & 0xff));

                        // compare result + size
                        const auto result = json::to_msgpack(j);
                        CHECK(result == expected);
                        CHECK(result.size() == 3);

                        // check individual bytes
                        CHECK(result[0] == 0xd1);
                        int16_t restored = (result[1] << 8) + result[2];
                        CHECK(restored == i);

                        // roundtrip
                        CHECK(json::from_msgpack(result) == j);
                    }
                }
                */
            }

            SECTION("unsigned")
            {
                SECTION("0..127 (positive fixnum)")
                {
                    for (size_t i = 0; i <= 127; ++i)
                    {
                        CAPTURE(i);

                        // create JSON value with unsigned integer number
                        json j = i;

                        // check type
                        CHECK(j.is_number_unsigned());

                        // create expected byte vector
                        std::vector<uint8_t> expected;
                        expected.push_back(static_cast<uint8_t>(i));

                        // compare result + size
                        const auto result = json::to_msgpack(j);
                        CHECK(result == expected);
                        CHECK(result.size() == 1);

                        // check individual bytes
                        CHECK(result[0] == i);

                        // roundtrip
                        CHECK(json::from_msgpack(result) == j);
                    }
                }

                SECTION("128..255 (uint 8)")
                {
                    for (size_t i = 128; i <= 255; ++i)
                    {
                        CAPTURE(i);

                        // create JSON value with unsigned integer number
                        json j = i;

                        // check type
                        CHECK(j.is_number_unsigned());

                        // create expected byte vector
                        std::vector<uint8_t> expected;
                        expected.push_back(0xcc);
                        expected.push_back(static_cast<uint8_t>(i));

                        // compare result + size
                        const auto result = json::to_msgpack(j);
                        CHECK(result == expected);
                        CHECK(result.size() == 2);

                        // check individual bytes
                        CHECK(result[0] == 0xcc);
                        uint8_t restored = static_cast<uint8_t>(result[1]);
                        CHECK(restored == i);

                        // roundtrip
                        CHECK(json::from_msgpack(result) == j);
                    }
                }

                SECTION("256..65535 (uint 16)")
                {
                    for (size_t i = 256; i <= 65535; ++i)
                    {
                        CAPTURE(i);

                        // create JSON value with unsigned integer number
                        json j = i;

                        // check type
                        CHECK(j.is_number_unsigned());

                        // create expected byte vector
                        std::vector<uint8_t> expected;
                        expected.push_back(0xcd);
                        expected.push_back(static_cast<uint8_t>((i >> 8) & 0xff));
                        expected.push_back(static_cast<uint8_t>(i & 0xff));

                        // compare result + size
                        const auto result = json::to_msgpack(j);
                        CHECK(result == expected);
                        CHECK(result.size() == 3);

                        // check individual bytes
                        CHECK(result[0] == 0xcd);
                        uint16_t restored = static_cast<uint8_t>(result[1]) * 256 + static_cast<uint8_t>(result[2]);
                        CHECK(restored == i);

                        // roundtrip
                        CHECK(json::from_msgpack(result) == j);
                    }
                }

                SECTION("65536..4294967295 (uint 32)")
                {
                    for (uint32_t i :
                            {
                                65536u, 77777u, 1048576u
                            })
                    {
                        CAPTURE(i);

                        // create JSON value with unsigned integer number
                        json j = i;

                        // check type
                        CHECK(j.is_number_unsigned());

                        // create expected byte vector
                        std::vector<uint8_t> expected;
                        expected.push_back(0xce);
                        expected.push_back(static_cast<uint8_t>((i >> 24) & 0xff));
                        expected.push_back(static_cast<uint8_t>((i >> 16) & 0xff));
                        expected.push_back(static_cast<uint8_t>((i >> 8) & 0xff));
                        expected.push_back(static_cast<uint8_t>(i & 0xff));

                        // compare result + size
                        const auto result = json::to_msgpack(j);
                        CHECK(result == expected);
                        CHECK(result.size() == 5);

                        // check individual bytes
                        CHECK(result[0] == 0xce);
                        uint32_t restored = static_cast<uint32_t>((static_cast<uint32_t>(result[1]) << 030) +
                                            (static_cast<uint32_t>(result[2]) << 020) +
                                            (static_cast<uint32_t>(result[3]) << 010) +
                                            static_cast<uint32_t>(result[4]));
                        CHECK(restored == i);

                        // roundtrip
                        CHECK(json::from_msgpack(result) == j);
                    }
                }

                SECTION("4294967296..4611686018427387903")
                {
                    for (uint64_t i :
                            {
                                4294967296ul, 4611686018427387903ul
                            })
                    {
                        CAPTURE(i);

                        // create JSON value with integer number
                        json j = i;

                        // check type
                        CHECK(j.is_number_unsigned());

                        // create expected byte vector
                        std::vector<uint8_t> expected;
                        expected.push_back(0x1b);
                        expected.push_back(static_cast<uint8_t>((i >> 070) & 0xff));
                        expected.push_back(static_cast<uint8_t>((i >> 060) & 0xff));
                        expected.push_back(static_cast<uint8_t>((i >> 050) & 0xff));
                        expected.push_back(static_cast<uint8_t>((i >> 040) & 0xff));
                        expected.push_back(static_cast<uint8_t>((i >> 030) & 0xff));
                        expected.push_back(static_cast<uint8_t>((i >> 020) & 0xff));
                        expected.push_back(static_cast<uint8_t>((i >> 010) & 0xff));
                        expected.push_back(static_cast<uint8_t>(i & 0xff));

                        // compare result + size
                        const auto result = json::to_cbor(j);
                        CHECK(result == expected);
                        CHECK(result.size() == 9);

                        // check individual bytes
                        CHECK(result[0] == 0x1b);
                        uint64_t restored = static_cast<uint64_t>((static_cast<uint64_t>(result[1]) << 070) +
                                            (static_cast<uint64_t>(result[2]) << 060) +
                                            (static_cast<uint64_t>(result[3]) << 050) +
                                            (static_cast<uint64_t>(result[4]) << 040) +
                                            (static_cast<uint64_t>(result[5]) << 030) +
                                            (static_cast<uint64_t>(result[6]) << 020) +
                                            (static_cast<uint64_t>(result[7]) << 010) +
                                            static_cast<uint64_t>(result[8]));
                        CHECK(restored == i);

                        // roundtrip
                        CHECK(json::from_cbor(result) == j);
                    }
                }
            }

            SECTION("float")
            {
                SECTION("3.1415925")
                {
                    double v = 3.1415925;
                    json j = v;
                    std::vector<uint8_t> expected =
                    {
                        0xfb, 0x40, 0x09, 0x21, 0xfb, 0x3f, 0xa6, 0xde, 0xfc
                    };
                    const auto result = json::to_cbor(j);
                    CHECK(result == expected);

                    // restore value (reverse array for endianess)
                    double restored;
                    std::reverse(expected.begin(), expected.end());
                    memcpy(&restored, expected.data(), sizeof(double));
                    CHECK(restored == v);

                    // roundtrip
                    CHECK(json::from_cbor(result) == j);
                }
            }
        }

        SECTION("string")
        {
            SECTION("N = 0..23")
            {
                for (size_t N = 0; N <= 0x17; ++N)
                {
                    CAPTURE(N);

                    // create JSON value with string containing of N * 'x'
                    const auto s = std::string(N, 'x');
                    json j = s;

                    // create expected byte vector
                    std::vector<uint8_t> expected;
                    expected.push_back(static_cast<uint8_t>(0x60 + N));
                    for (size_t i = 0; i < N; ++i)
                    {
                        expected.push_back('x');
                    }

                    // compare result + size
                    const auto result = json::to_cbor(j);
                    CHECK(result == expected);
                    CHECK(result.size() == N + 1);
                    // check that no null byte is appended
                    if (N > 0)
                    {
                        CHECK(result.back() != '\x00');
                    }

                    // roundtrip
                    CHECK(json::from_cbor(result) == j);
                }
            }

            SECTION("N = 24..255")
            {
                for (size_t N = 24; N <= 255; ++N)
                {
                    CAPTURE(N);

                    // create JSON value with string containing of N * 'x'
                    const auto s = std::string(N, 'x');
                    json j = s;

                    // create expected byte vector
                    std::vector<uint8_t> expected;
                    expected.push_back(0x78);
                    expected.push_back(static_cast<uint8_t>(N));
                    for (size_t i = 0; i < N; ++i)
                    {
                        expected.push_back('x');
                    }

                    // compare result + size
                    const auto result = json::to_cbor(j);
                    CHECK(result == expected);
                    CHECK(result.size() == N + 2);
                    // check that no null byte is appended
                    CHECK(result.back() != '\x00');

                    // roundtrip
                    CHECK(json::from_cbor(result) == j);
                }
            }

            SECTION("N = 256..65535")
            {
                for (size_t N :
                        {
                            256u, 999u, 1025u, 3333u, 2048u, 65535u
                        })
                {
                    CAPTURE(N);

                    // create JSON value with string containing of N * 'x'
                    const auto s = std::string(N, 'x');
                    json j = s;

                    // create expected byte vector (hack: create string first)
                    std::vector<uint8_t> expected(N, 'x');
                    // reverse order of commands, because we insert at begin()
                    expected.insert(expected.begin(), static_cast<uint8_t>(N & 0xff));
                    expected.insert(expected.begin(), static_cast<uint8_t>((N >> 8) & 0xff));
                    expected.insert(expected.begin(), 0x79);

                    // compare result + size
                    const auto result = json::to_cbor(j);
                    CHECK(result == expected);
                    CHECK(result.size() == N + 3);
                    // check that no null byte is appended
                    CHECK(result.back() != '\x00');

                    // roundtrip
                    CHECK(json::from_cbor(result) == j);
                }
            }

            SECTION("N = 65536..4294967295")
            {
                for (size_t N :
                        {
                            65536u, 77777u, 1048576u
                        })
                {
                    CAPTURE(N);

                    // create JSON value with string containing of N * 'x'
                    const auto s = std::string(N, 'x');
                    json j = s;

                    // create expected byte vector (hack: create string first)
                    std::vector<uint8_t> expected(N, 'x');
                    // reverse order of commands, because we insert at begin()
                    expected.insert(expected.begin(), static_cast<uint8_t>(N & 0xff));
                    expected.insert(expected.begin(), static_cast<uint8_t>((N >> 8) & 0xff));
                    expected.insert(expected.begin(), static_cast<uint8_t>((N >> 16) & 0xff));
                    expected.insert(expected.begin(), static_cast<uint8_t>((N >> 24) & 0xff));
                    expected.insert(expected.begin(), 0x7a);

                    // compare result + size
                    const auto result = json::to_cbor(j);
                    CHECK(result == expected);
                    CHECK(result.size() == N + 5);
                    // check that no null byte is appended
                    CHECK(result.back() != '\x00');

                    // roundtrip
                    CHECK(json::from_cbor(result) == j);
                }
            }
        }

        SECTION("array")
        {
            SECTION("empty")
            {
                json j = json::array();
                std::vector<uint8_t> expected = {0x80};
                const auto result = json::to_cbor(j);
                CHECK(result == expected);

                // roundtrip
                CHECK(json::from_cbor(result) == j);
            }

            SECTION("[null]")
            {
                json j = {nullptr};
                std::vector<uint8_t> expected = {0x81, 0xf6};
                const auto result = json::to_cbor(j);
                CHECK(result == expected);

                // roundtrip
                CHECK(json::from_cbor(result) == j);
            }

            SECTION("[1,2,3,4,5]")
            {
                json j = json::parse("[1,2,3,4,5]");
                std::vector<uint8_t> expected = {0x85, 0x01, 0x02, 0x03, 0x04, 0x05};
                const auto result = json::to_cbor(j);
                CHECK(result == expected);

                // roundtrip
                CHECK(json::from_cbor(result) == j);
            }

            SECTION("[[[[]]]]")
            {
                json j = json::parse("[[[[]]]]");
                std::vector<uint8_t> expected = {0x81, 0x81, 0x81, 0x80};
                const auto result = json::to_cbor(j);
                CHECK(result == expected);

                // roundtrip
                CHECK(json::from_cbor(result) == j);
            }
        }

        SECTION("object")
        {
            SECTION("empty")
            {
                json j = json::object();
                std::vector<uint8_t> expected = {0xa0};
                const auto result = json::to_cbor(j);
                CHECK(result == expected);

                // roundtrip
                CHECK(json::from_cbor(result) == j);
            }

            SECTION("{\"\":null}")
            {
                json j = {{"", nullptr}};
                std::vector<uint8_t> expected = {0xa1, 0x60, 0xf6};
                const auto result = json::to_cbor(j);
                CHECK(result == expected);

                // roundtrip
                CHECK(json::from_cbor(result) == j);
            }

            SECTION("{\"a\": {\"b\": {\"c\": {}}}}")
            {
                json j = json::parse("{\"a\": {\"b\": {\"c\": {}}}}");
                std::vector<uint8_t> expected =
                {
                    0xa1, 0x61, 0x61, 0xa1, 0x61, 0x62, 0xa1, 0x61, 0x63, 0xa0
                };
                const auto result = json::to_cbor(j);
                CHECK(result == expected);

                // roundtrip
                CHECK(json::from_cbor(result) == j);
            }
        }
    }
}

// use this testcase outside [hide] to run it with Valgrind
TEST_CASE("single CBOR roundtrip")
{
    SECTION("sample.json")
    {
        std::string filename = "test/data/json_testsuite/sample.json";

        // parse JSON file
        std::ifstream f_json(filename);
        json j1 = json::parse(f_json);

        // parse MessagePack file
        std::ifstream f_cbor(filename + ".cbor", std::ios::binary);
        std::vector<uint8_t> packed((std::istreambuf_iterator<char>(f_cbor)),
                                    std::istreambuf_iterator<char>());
        json j2;
        CHECK_NOTHROW(j2 = json::from_cbor(packed));

        // compare parsed JSON values
        CHECK(j1 == j2);
    }
}

TEST_CASE("CBOR roundtrips", "[hide]")
{
    SECTION("input from flynn")
    {
        for (std::string filename :
                {
                    "test/data/json_nlohmann_tests/all_unicode.json",
                    "test/data/json.org/1.json",
                    "test/data/json.org/2.json",
                    "test/data/json.org/3.json",
                    "test/data/json.org/4.json",
                    "test/data/json.org/5.json",
                    "test/data/json_roundtrip/roundtrip01.json",
                    "test/data/json_roundtrip/roundtrip02.json",
                    "test/data/json_roundtrip/roundtrip03.json",
                    "test/data/json_roundtrip/roundtrip04.json",
                    "test/data/json_roundtrip/roundtrip05.json",
                    "test/data/json_roundtrip/roundtrip06.json",
                    "test/data/json_roundtrip/roundtrip07.json",
                    "test/data/json_roundtrip/roundtrip08.json",
                    "test/data/json_roundtrip/roundtrip09.json",
                    "test/data/json_roundtrip/roundtrip10.json",
                    "test/data/json_roundtrip/roundtrip11.json",
                    "test/data/json_roundtrip/roundtrip12.json",
                    "test/data/json_roundtrip/roundtrip13.json",
                    "test/data/json_roundtrip/roundtrip14.json",
                    "test/data/json_roundtrip/roundtrip15.json",
                    "test/data/json_roundtrip/roundtrip16.json",
                    "test/data/json_roundtrip/roundtrip17.json",
                    "test/data/json_roundtrip/roundtrip18.json",
                    "test/data/json_roundtrip/roundtrip19.json",
                    "test/data/json_roundtrip/roundtrip20.json",
                    "test/data/json_roundtrip/roundtrip21.json",
                    "test/data/json_roundtrip/roundtrip22.json",
                    "test/data/json_roundtrip/roundtrip23.json",
                    "test/data/json_roundtrip/roundtrip24.json",
                    "test/data/json_roundtrip/roundtrip25.json",
                    "test/data/json_roundtrip/roundtrip26.json",
                    "test/data/json_roundtrip/roundtrip27.json",
                    "test/data/json_roundtrip/roundtrip28.json",
                    "test/data/json_roundtrip/roundtrip29.json",
                    "test/data/json_roundtrip/roundtrip30.json",
                    "test/data/json_roundtrip/roundtrip31.json",
                    "test/data/json_roundtrip/roundtrip32.json",
                    "test/data/json_testsuite/sample.json", // kills AppVeyor
                    "test/data/json_tests/pass1.json",
                    "test/data/json_tests/pass2.json",
                    "test/data/json_tests/pass3.json",
                    "test/data/regression/floats.json",
                    "test/data/regression/signed_ints.json",
                    "test/data/regression/unsigned_ints.json",
                    "test/data/regression/working_file.json",
                    "test/data/nst_json_testsuite/test_parsing/y_array_arraysWithSpaces.json",
                    "test/data/nst_json_testsuite/test_parsing/y_array_empty-string.json",
                    "test/data/nst_json_testsuite/test_parsing/y_array_empty.json",
                    "test/data/nst_json_testsuite/test_parsing/y_array_ending_with_newline.json",
                    "test/data/nst_json_testsuite/test_parsing/y_array_false.json",
                    "test/data/nst_json_testsuite/test_parsing/y_array_heterogeneous.json",
                    "test/data/nst_json_testsuite/test_parsing/y_array_null.json",
                    "test/data/nst_json_testsuite/test_parsing/y_array_with_1_and_newline.json",
                    "test/data/nst_json_testsuite/test_parsing/y_array_with_leading_space.json",
                    "test/data/nst_json_testsuite/test_parsing/y_array_with_several_null.json",
                    "test/data/nst_json_testsuite/test_parsing/y_array_with_trailing_space.json",
                    "test/data/nst_json_testsuite/test_parsing/y_number.json",
                    "test/data/nst_json_testsuite/test_parsing/y_number_0e+1.json",
                    "test/data/nst_json_testsuite/test_parsing/y_number_0e1.json",
                    "test/data/nst_json_testsuite/test_parsing/y_number_after_space.json",
                    "test/data/nst_json_testsuite/test_parsing/y_number_double_close_to_zero.json",
                    "test/data/nst_json_testsuite/test_parsing/y_number_double_huge_neg_exp.json",
                    "test/data/nst_json_testsuite/test_parsing/y_number_huge_exp.json",
                    "test/data/nst_json_testsuite/test_parsing/y_number_int_with_exp.json",
                    "test/data/nst_json_testsuite/test_parsing/y_number_minus_zero.json",
                    "test/data/nst_json_testsuite/test_parsing/y_number_negative_int.json",
                    "test/data/nst_json_testsuite/test_parsing/y_number_negative_one.json",
                    "test/data/nst_json_testsuite/test_parsing/y_number_negative_zero.json",
                    "test/data/nst_json_testsuite/test_parsing/y_number_real_capital_e.json",
                    "test/data/nst_json_testsuite/test_parsing/y_number_real_capital_e_neg_exp.json",
                    "test/data/nst_json_testsuite/test_parsing/y_number_real_capital_e_pos_exp.json",
                    "test/data/nst_json_testsuite/test_parsing/y_number_real_exponent.json",
                    "test/data/nst_json_testsuite/test_parsing/y_number_real_fraction_exponent.json",
                    "test/data/nst_json_testsuite/test_parsing/y_number_real_neg_exp.json",
                    "test/data/nst_json_testsuite/test_parsing/y_number_real_neg_overflow.json",
                    "test/data/nst_json_testsuite/test_parsing/y_number_real_pos_exponent.json",
                    "test/data/nst_json_testsuite/test_parsing/y_number_real_pos_overflow.json",
                    "test/data/nst_json_testsuite/test_parsing/y_number_real_underflow.json",
                    "test/data/nst_json_testsuite/test_parsing/y_number_simple_int.json",
                    "test/data/nst_json_testsuite/test_parsing/y_number_simple_real.json",
                    //"test/data/nst_json_testsuite/test_parsing/y_number_too_big_neg_int.json",
                    //"test/data/nst_json_testsuite/test_parsing/y_number_too_big_pos_int.json",
                    //"test/data/nst_json_testsuite/test_parsing/y_number_very_big_negative_int.json",
                    "test/data/nst_json_testsuite/test_parsing/y_object.json",
                    "test/data/nst_json_testsuite/test_parsing/y_object_basic.json",
                    "test/data/nst_json_testsuite/test_parsing/y_object_duplicated_key.json",
                    "test/data/nst_json_testsuite/test_parsing/y_object_duplicated_key_and_value.json",
                    "test/data/nst_json_testsuite/test_parsing/y_object_empty.json",
                    "test/data/nst_json_testsuite/test_parsing/y_object_empty_key.json",
                    "test/data/nst_json_testsuite/test_parsing/y_object_escaped_null_in_key.json",
                    "test/data/nst_json_testsuite/test_parsing/y_object_extreme_numbers.json",
                    "test/data/nst_json_testsuite/test_parsing/y_object_long_strings.json",
                    "test/data/nst_json_testsuite/test_parsing/y_object_simple.json",
                    "test/data/nst_json_testsuite/test_parsing/y_object_string_unicode.json",
                    "test/data/nst_json_testsuite/test_parsing/y_object_with_newlines.json",
                    "test/data/nst_json_testsuite/test_parsing/y_string_1_2_3_bytes_UTF-8_sequences.json",
                    "test/data/nst_json_testsuite/test_parsing/y_string_UTF-16_Surrogates_U+1D11E_MUSICAL_SYMBOL_G_CLEF.json",
                    "test/data/nst_json_testsuite/test_parsing/y_string_accepted_surrogate_pair.json",
                    "test/data/nst_json_testsuite/test_parsing/y_string_accepted_surrogate_pairs.json",
                    "test/data/nst_json_testsuite/test_parsing/y_string_allowed_escapes.json",
                    "test/data/nst_json_testsuite/test_parsing/y_string_backslash_and_u_escaped_zero.json",
                    "test/data/nst_json_testsuite/test_parsing/y_string_backslash_doublequotes.json",
                    "test/data/nst_json_testsuite/test_parsing/y_string_comments.json",
                    "test/data/nst_json_testsuite/test_parsing/y_string_double_escape_a.json",
                    "test/data/nst_json_testsuite/test_parsing/y_string_double_escape_n.json",
                    "test/data/nst_json_testsuite/test_parsing/y_string_escaped_control_character.json",
                    "test/data/nst_json_testsuite/test_parsing/y_string_escaped_noncharacter.json",
                    "test/data/nst_json_testsuite/test_parsing/y_string_in_array.json",
                    "test/data/nst_json_testsuite/test_parsing/y_string_in_array_with_leading_space.json",
                    "test/data/nst_json_testsuite/test_parsing/y_string_last_surrogates_1_and_2.json",
                    "test/data/nst_json_testsuite/test_parsing/y_string_newline_uescaped.json",
                    "test/data/nst_json_testsuite/test_parsing/y_string_nonCharacterInUTF-8_U+10FFFF.json",
                    "test/data/nst_json_testsuite/test_parsing/y_string_nonCharacterInUTF-8_U+1FFFF.json",
                    "test/data/nst_json_testsuite/test_parsing/y_string_nonCharacterInUTF-8_U+FFFF.json",
                    "test/data/nst_json_testsuite/test_parsing/y_string_null_escape.json",
                    "test/data/nst_json_testsuite/test_parsing/y_string_one-byte-utf-8.json",
                    "test/data/nst_json_testsuite/test_parsing/y_string_pi.json",
                    "test/data/nst_json_testsuite/test_parsing/y_string_simple_ascii.json",
                    "test/data/nst_json_testsuite/test_parsing/y_string_space.json",
                    "test/data/nst_json_testsuite/test_parsing/y_string_three-byte-utf-8.json",
                    "test/data/nst_json_testsuite/test_parsing/y_string_two-byte-utf-8.json",
                    "test/data/nst_json_testsuite/test_parsing/y_string_u+2028_line_sep.json",
                    "test/data/nst_json_testsuite/test_parsing/y_string_u+2029_par_sep.json",
                    "test/data/nst_json_testsuite/test_parsing/y_string_uEscape.json",
                    "test/data/nst_json_testsuite/test_parsing/y_string_unescaped_char_delete.json",
                    "test/data/nst_json_testsuite/test_parsing/y_string_unicode.json",
                    "test/data/nst_json_testsuite/test_parsing/y_string_unicodeEscapedBackslash.json",
                    "test/data/nst_json_testsuite/test_parsing/y_string_unicode_2.json",
                    "test/data/nst_json_testsuite/test_parsing/y_string_unicode_U+200B_ZERO_WIDTH_SPACE.json",
                    "test/data/nst_json_testsuite/test_parsing/y_string_unicode_U+2064_invisible_plus.json",
                    "test/data/nst_json_testsuite/test_parsing/y_string_unicode_escaped_double_quote.json",
                    // "test/data/nst_json_testsuite/test_parsing/y_string_utf16.json",
                    "test/data/nst_json_testsuite/test_parsing/y_string_utf8.json",
                    "test/data/nst_json_testsuite/test_parsing/y_string_with_del_character.json",
                    "test/data/nst_json_testsuite/test_parsing/y_structure_lonely_false.json",
                    "test/data/nst_json_testsuite/test_parsing/y_structure_lonely_int.json",
                    "test/data/nst_json_testsuite/test_parsing/y_structure_lonely_negative_real.json",
                    "test/data/nst_json_testsuite/test_parsing/y_structure_lonely_null.json",
                    "test/data/nst_json_testsuite/test_parsing/y_structure_lonely_string.json",
                    "test/data/nst_json_testsuite/test_parsing/y_structure_lonely_true.json",
                    "test/data/nst_json_testsuite/test_parsing/y_structure_string_empty.json",
                    "test/data/nst_json_testsuite/test_parsing/y_structure_trailing_newline.json",
                    "test/data/nst_json_testsuite/test_parsing/y_structure_true_in_array.json",
                    "test/data/nst_json_testsuite/test_parsing/y_structure_whitespace_array.json"
                })
        {
            CAPTURE(filename);

            // parse JSON file
            std::ifstream f_json(filename);
            json j1 = json::parse(f_json);

            // parse CBOR file
            std::ifstream f_cbor(filename + ".cbor", std::ios::binary);
            std::vector<uint8_t> packed(
                (std::istreambuf_iterator<char>(f_cbor)),
                std::istreambuf_iterator<char>());
            json j2;
            CHECK_NOTHROW(j2 = json::from_cbor(packed));

            // compare parsed JSON values
            CHECK(j1 == j2);
        }
    }
}

TEST_CASE("examples from RFC 7049 Appendix A")
{
    SECTION("numbers")
    {
        CHECK(json::to_cbor(json::parse("0")) == std::vector<uint8_t>({0x00}));
        CHECK(json::parse("0") == json::from_cbor(std::vector<uint8_t>({0x00})));

        CHECK(json::to_cbor(json::parse("1")) == std::vector<uint8_t>({0x01}));
        CHECK(json::parse("1") == json::from_cbor(std::vector<uint8_t>({0x01})));

        CHECK(json::to_cbor(json::parse("10")) == std::vector<uint8_t>({0x0a}));
        CHECK(json::parse("10") == json::from_cbor(std::vector<uint8_t>({0x0a})));

        CHECK(json::to_cbor(json::parse("23")) == std::vector<uint8_t>({0x17}));
        CHECK(json::parse("23") == json::from_cbor(std::vector<uint8_t>({0x17})));

        CHECK(json::to_cbor(json::parse("24")) == std::vector<uint8_t>({0x18, 0x18}));
        CHECK(json::parse("24") == json::from_cbor(std::vector<uint8_t>({0x18, 0x18})));

        CHECK(json::to_cbor(json::parse("25")) == std::vector<uint8_t>({0x18, 0x19}));
        CHECK(json::parse("25") == json::from_cbor(std::vector<uint8_t>({0x18, 0x19})));

        CHECK(json::to_cbor(json::parse("100")) == std::vector<uint8_t>({0x18, 0x64}));
        CHECK(json::parse("100") == json::from_cbor(std::vector<uint8_t>({0x18, 0x64})));

        CHECK(json::to_cbor(json::parse("1000")) == std::vector<uint8_t>({0x19, 0x03, 0xe8}));
        CHECK(json::parse("1000") == json::from_cbor(std::vector<uint8_t>({0x19, 0x03, 0xe8})));

        CHECK(json::to_cbor(json::parse("1000000")) == std::vector<uint8_t>({0x1a, 0x00, 0x0f, 0x42, 0x40}));
        CHECK(json::parse("1000000") == json::from_cbor(std::vector<uint8_t>({0x1a, 0x00, 0x0f, 0x42, 0x40})));

        CHECK(json::to_cbor(json::parse("1000000000000")) == std::vector<uint8_t>({0x1b, 0x00, 0x00, 0x00, 0xe8, 0xd4, 0xa5, 0x10, 0x00}));
        CHECK(json::parse("1000000000000") == json::from_cbor(std::vector<uint8_t>({0x1b, 0x00, 0x00, 0x00, 0xe8, 0xd4, 0xa5, 0x10, 0x00})));

        CHECK(json::to_cbor(json::parse("18446744073709551615")) == std::vector<uint8_t>({0x1b, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff}));
        CHECK(json::parse("18446744073709551615") == json::from_cbor(std::vector<uint8_t>({0x1b, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff})));

        // positive bignum is not supported
        //CHECK(json::to_cbor(json::parse("18446744073709551616")) == std::vector<uint8_t>({0xc2, 0x49, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}));
        //CHECK(json::parse("18446744073709551616") == json::from_cbor(std::vector<uint8_t>({0xc2, 0x49, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00})));

        //CHECK(json::to_cbor(json::parse("-18446744073709551616")) == std::vector<uint8_t>({0x3b, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff}));
        //CHECK(json::parse("-18446744073709551616") == json::from_cbor(std::vector<uint8_t>({0x3b, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff})));

        // negative bignum is not supported
        //CHECK(json::to_cbor(json::parse("-18446744073709551617")) == std::vector<uint8_t>({0xc3, 0x49, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}));
        //CHECK(json::parse("-18446744073709551617") == json::from_cbor(std::vector<uint8_t>({0xc3, 0x49, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00})));

        CHECK(json::to_cbor(json::parse("-1")) == std::vector<uint8_t>({0x20}));
        CHECK(json::parse("-1") == json::from_cbor(std::vector<uint8_t>({0x20})));

        CHECK(json::to_cbor(json::parse("-10")) == std::vector<uint8_t>({0x29}));
        CHECK(json::parse("-10") == json::from_cbor(std::vector<uint8_t>({0x29})));

        CHECK(json::to_cbor(json::parse("-100")) == std::vector<uint8_t>({0x38, 0x63}));
        CHECK(json::parse("-100") == json::from_cbor(std::vector<uint8_t>({0x38, 0x63})));

        CHECK(json::to_cbor(json::parse("-1000")) == std::vector<uint8_t>({0x39, 0x03, 0xe7}));
        CHECK(json::parse("-1000") == json::from_cbor(std::vector<uint8_t>({0x39, 0x03, 0xe7})));

        // half-precision float
        //CHECK(json::to_cbor(json::parse("0.0")) == std::vector<uint8_t>({0xf9, 0x00, 0x00}));
        CHECK(json::parse("0.0") == json::from_cbor(std::vector<uint8_t>({0xf9, 0x00, 0x00})));

        // half-precision float
        //CHECK(json::to_cbor(json::parse("-0.0")) == std::vector<uint8_t>({0xf9, 0x80, 0x00}));
        CHECK(json::parse("-0.0") == json::from_cbor(std::vector<uint8_t>({0xf9, 0x80, 0x00})));

        // half-precision float
        //CHECK(json::to_cbor(json::parse("1.0")) == std::vector<uint8_t>({0xf9, 0x3c, 0x00}));
        CHECK(json::parse("1.0") == json::from_cbor(std::vector<uint8_t>({0xf9, 0x3c, 0x00})));

        CHECK(json::to_cbor(json::parse("1.1")) == std::vector<uint8_t>({0xfb, 0x3f, 0xf1, 0x99, 0x99, 0x99, 0x99, 0x99, 0x9a}));
        CHECK(json::parse("1.1") == json::from_cbor(std::vector<uint8_t>({0xfb, 0x3f, 0xf1, 0x99, 0x99, 0x99, 0x99, 0x99, 0x9a})));

        // half-precision float
        //CHECK(json::to_cbor(json::parse("1.5")) == std::vector<uint8_t>({0xf9, 0x3e, 0x00}));
        CHECK(json::parse("1.5") == json::from_cbor(std::vector<uint8_t>({0xf9, 0x3e, 0x00})));

        // half-precision float
        //CHECK(json::to_cbor(json::parse("65504.0")) == std::vector<uint8_t>({0xf9, 0x7b, 0xff}));
        CHECK(json::parse("65504.0") == json::from_cbor(std::vector<uint8_t>({0xf9, 0x7b, 0xff})));

        //CHECK(json::to_cbor(json::parse("100000.0")) == std::vector<uint8_t>({0xfa, 0x47, 0xc3, 0x50, 0x00}));
        CHECK(json::parse("100000.0") == json::from_cbor(std::vector<uint8_t>({0xfa, 0x47, 0xc3, 0x50, 0x00})));

        //CHECK(json::to_cbor(json::parse("3.4028234663852886e+38")) == std::vector<uint8_t>({0xfa, 0x7f, 0x7f, 0xff, 0xff}));
        CHECK(json::parse("3.4028234663852886e+38") == json::from_cbor(std::vector<uint8_t>({0xfa, 0x7f, 0x7f, 0xff, 0xff})));

        CHECK(json::to_cbor(json::parse("1.0e+300")) == std::vector<uint8_t>({0xfb, 0x7e, 0x37, 0xe4, 0x3c, 0x88, 0x00, 0x75, 0x9c}));
        CHECK(json::parse("1.0e+300") == json::from_cbor(std::vector<uint8_t>({0xfb, 0x7e, 0x37, 0xe4, 0x3c, 0x88, 0x00, 0x75, 0x9c})));

        // half-precision float
        //CHECK(json::to_cbor(json::parse("5.960464477539063e-8")) == std::vector<uint8_t>({0xf9, 0x00, 0x01}));
        CHECK(json::parse("-4.0") == json::from_cbor(std::vector<uint8_t>({0xf9, 0xc4, 0x00})));

        // half-precision float
        //CHECK(json::to_cbor(json::parse("0.00006103515625")) == std::vector<uint8_t>({0xf9, 0x04, 0x00}));
        CHECK(json::parse("-4.0") == json::from_cbor(std::vector<uint8_t>({0xf9, 0xc4, 0x00})));

        // half-precision float
        //CHECK(json::to_cbor(json::parse("-4.0")) == std::vector<uint8_t>({0xf9, 0xc4, 0x00}));
        CHECK(json::parse("-4.0") == json::from_cbor(std::vector<uint8_t>({0xf9, 0xc4, 0x00})));

        CHECK(json::to_cbor(json::parse("-4.1")) == std::vector<uint8_t>({0xfb, 0xc0, 0x10, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66}));
        CHECK(json::parse("-4.1") == json::from_cbor(std::vector<uint8_t>({0xfb, 0xc0, 0x10, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66})));
    }

    SECTION("simple values")
    {
        CHECK(json::to_cbor(json::parse("false")) == std::vector<uint8_t>({0xf4}));
        CHECK(json::parse("false") == json::from_cbor(std::vector<uint8_t>({0xf4})));

        CHECK(json::to_cbor(json::parse("true")) == std::vector<uint8_t>({0xf5}));
        CHECK(json::parse("true") == json::from_cbor(std::vector<uint8_t>({0xf5})));

        CHECK(json::to_cbor(json::parse("true")) == std::vector<uint8_t>({0xf5}));
        CHECK(json::parse("true") == json::from_cbor(std::vector<uint8_t>({0xf5})));
    }

    SECTION("strings")
    {
        CHECK(json::to_cbor(json::parse("\"\"")) == std::vector<uint8_t>({0x60}));
        CHECK(json::parse("\"\"") == json::from_cbor(std::vector<uint8_t>({0x60})));

        CHECK(json::to_cbor(json::parse("\"a\"")) == std::vector<uint8_t>({0x61, 0x61}));
        CHECK(json::parse("\"a\"") == json::from_cbor(std::vector<uint8_t>({0x61, 0x61})));

        CHECK(json::to_cbor(json::parse("\"IETF\"")) == std::vector<uint8_t>({0x64, 0x49, 0x45, 0x54, 0x46}));
        CHECK(json::parse("\"IETF\"") == json::from_cbor(std::vector<uint8_t>({0x64, 0x49, 0x45, 0x54, 0x46})));

        CHECK(json::to_cbor(json::parse("\"\\u00fc\"")) == std::vector<uint8_t>({0x62, 0xc3, 0xbc}));
        CHECK(json::parse("\"\\u00fc\"") == json::from_cbor(std::vector<uint8_t>({0x62, 0xc3, 0xbc})));

        CHECK(json::to_cbor(json::parse("\"\\u6c34\"")) == std::vector<uint8_t>({0x63, 0xe6, 0xb0, 0xb4}));
        CHECK(json::parse("\"\\u6c34\"") == json::from_cbor(std::vector<uint8_t>({0x63, 0xe6, 0xb0, 0xb4})));

        CHECK(json::to_cbor(json::parse("\"\\ud800\\udd51\"")) == std::vector<uint8_t>({0x64, 0xf0, 0x90, 0x85, 0x91}));
        CHECK(json::parse("\"\\ud800\\udd51\"") == json::from_cbor(std::vector<uint8_t>({0x64, 0xf0, 0x90, 0x85, 0x91})));
    }

    SECTION("arrays")
    {
        CHECK(json::to_cbor(json::parse("[]")) == std::vector<uint8_t>({0x80}));
        CHECK(json::parse("[]") == json::from_cbor(std::vector<uint8_t>({0x80})));

        CHECK(json::to_cbor(json::parse("[1, 2, 3]")) == std::vector<uint8_t>({0x83, 0x01, 0x02, 0x03}));
        CHECK(json::parse("[1, 2, 3]") == json::from_cbor(std::vector<uint8_t>({0x83, 0x01, 0x02, 0x03})));

        CHECK(json::to_cbor(json::parse("[1, [2, 3], [4, 5]]")) == std::vector<uint8_t>({0x83, 0x01, 0x82, 0x02, 0x03, 0x82, 0x04, 0x05}));
        CHECK(json::parse("[1, [2, 3], [4, 5]]") == json::from_cbor(std::vector<uint8_t>({0x83, 0x01, 0x82, 0x02, 0x03, 0x82, 0x04, 0x05})));

        CHECK(json::to_cbor(json::parse("[1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25]")) == std::vector<uint8_t>({0x98, 0x19, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x18, 0x18, 0x19}));
        CHECK(json::parse("[1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25]") == json::from_cbor(std::vector<uint8_t>({0x98, 0x19, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x18, 0x18, 0x19})));
    }

    SECTION("objects")
    {
        CHECK(json::to_cbor(json::parse("{}")) == std::vector<uint8_t>({0xa0}));
        CHECK(json::parse("{}") == json::from_cbor(std::vector<uint8_t>({0xa0})));

        CHECK(json::to_cbor(json::parse("{\"a\": 1, \"b\": [2, 3]}")) == std::vector<uint8_t>({0xa2, 0x61, 0x61, 0x01, 0x61, 0x62, 0x82, 0x02, 0x03}));
        CHECK(json::parse("{\"a\": 1, \"b\": [2, 3]}") == json::from_cbor(std::vector<uint8_t>({0xa2, 0x61, 0x61, 0x01, 0x61, 0x62, 0x82, 0x02, 0x03})));

        CHECK(json::to_cbor(json::parse("[\"a\", {\"b\": \"c\"}]")) == std::vector<uint8_t>({0x82, 0x61, 0x61, 0xa1, 0x61, 0x62, 0x61, 0x63}));
        CHECK(json::parse("[\"a\", {\"b\": \"c\"}]") == json::from_cbor(std::vector<uint8_t>({0x82, 0x61, 0x61, 0xa1, 0x61, 0x62, 0x61, 0x63})));

        CHECK(json::to_cbor(json::parse("{\"a\": \"A\", \"b\": \"B\", \"c\": \"C\", \"d\": \"D\", \"e\": \"E\"}")) == std::vector<uint8_t>({0xa5, 0x61, 0x61, 0x61, 0x41, 0x61, 0x62, 0x61, 0x42, 0x61, 0x63, 0x61, 0x43, 0x61, 0x64, 0x61, 0x44, 0x61, 0x65, 0x61, 0x45}));
        CHECK(json::parse("{\"a\": \"A\", \"b\": \"B\", \"c\": \"C\", \"d\": \"D\", \"e\": \"E\"}") == json::from_cbor(std::vector<uint8_t>({0xa5, 0x61, 0x61, 0x61, 0x41, 0x61, 0x62, 0x61, 0x42, 0x61, 0x63, 0x61, 0x43, 0x61, 0x64, 0x61, 0x44, 0x61, 0x65, 0x61, 0x45})));
    }
}
