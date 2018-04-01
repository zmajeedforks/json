/*
    __ _____ _____ _____
 __|  |   __|     |   | |  JSON for Modern C++ (test suite)
|  |  |__   |  |  | | | |  version 3.1.2
|_____|_____|_____|_|___|  https://github.com/nlohmann/json

Licensed under the MIT License <http://opensource.org/licenses/MIT>.
Copyright (c) 2013-2018 Niels Lohmann <http://nlohmann.me>.

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

#include <nlohmann/json.hpp>

using nlohmann::json;


TEST_CASE("wide strings")
{
    SECTION("std::wstring")
    {
        std::wstring w = L"[12.2,\"Ⴥaäö💤🧢\"]";
        json j = json::parse(w);
        CHECK(j.dump() == "[12.2,\"Ⴥaäö💤🧢\"]");
    }

    SECTION("std::u16string")
    {
        std::u16string w = u"[12.2,\"Ⴥaäö💤🧢\"]";
        json j = json::parse(w);
        CHECK(j.dump() == "[12.2,\"Ⴥaäö💤🧢\"]");
    }

    SECTION("std::u32string")
    {
        std::u32string w = U"[12.2,\"Ⴥaäö💤🧢\"]";
        json j = json::parse(w);
        CHECK(j.dump() == "[12.2,\"Ⴥaäö💤🧢\"]");
    }
}
