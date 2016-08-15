/*
    __ _____ _____ _____
 __|  |   __|     |   | |  JSON for Modern C++ (test suite)
|  |  |__   |  |  | | | |  version 2.0.2
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

#include <valarray>

TEST_CASE("deserialization")
{
    SECTION("stream")
    {
        std::stringstream ss;
        ss << "[\"foo\",1,2,3,false,{\"one\":1}]";
        json j = json::parse(ss);
        CHECK(j == json({"foo", 1, 2, 3, false, {{"one", 1}}}));
    }

    SECTION("string literal")
    {
        auto s = "[\"foo\",1,2,3,false,{\"one\":1}]";
        json j = json::parse(s);
        CHECK(j == json({"foo", 1, 2, 3, false, {{"one", 1}}}));
    }

    SECTION("string_t")
    {
        json::string_t s = "[\"foo\",1,2,3,false,{\"one\":1}]";
        json j = json::parse(s);
        CHECK(j == json({"foo", 1, 2, 3, false, {{"one", 1}}}));
    }

    SECTION("operator<<")
    {
        std::stringstream ss;
        ss << "[\"foo\",1,2,3,false,{\"one\":1}]";
        json j;
        j << ss;
        CHECK(j == json({"foo", 1, 2, 3, false, {{"one", 1}}}));
    }

    SECTION("operator>>")
    {
        std::stringstream ss;
        ss << "[\"foo\",1,2,3,false,{\"one\":1}]";
        json j;
        ss >> j;
        CHECK(j == json({"foo", 1, 2, 3, false, {{"one", 1}}}));
    }

    SECTION("user-defined string literal")
    {
        CHECK("[\"foo\",1,2,3,false,{\"one\":1}]"_json == json({"foo", 1, 2, 3, false, {{"one", 1}}}));
    }

    SECTION("contiguous containers")
    {
        SECTION("from std::vector")
        {
            std::vector<uint8_t> v = {'t', 'r', 'u', 'e', '\0'};
            CHECK(json::parse(std::begin(v), std::end(v)) == json(true));
        }

        SECTION("from std::array")
        {
            std::array<uint8_t, 5> v { {'t', 'r', 'u', 'e', '\0'} };
            CHECK(json::parse(std::begin(v), std::end(v)) == json(true));
        }

        SECTION("from array")
        {
            uint8_t v[] = {'t', 'r', 'u', 'e'};
            CHECK(json::parse(std::begin(v), std::end(v)) == json(true));
        }

        SECTION("from std::string")
        {
            std::string v = {'t', 'r', 'u', 'e'};
            CHECK(json::parse(std::begin(v), std::end(v)) == json(true));
        }

        SECTION("from std::initializer_list")
        {
            std::initializer_list<uint8_t> v = {'t', 'r', 'u', 'e', '\0'};
            CHECK(json::parse(std::begin(v), std::end(v)) == json(true));
        }

        SECTION("from std::valarray")
        {
            std::valarray<uint8_t> v = {'t', 'r', 'u', 'e', '\0'};
            CHECK(json::parse(std::begin(v), std::end(v)) == json(true));
        }
    }
}
