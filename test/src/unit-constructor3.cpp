/*
    __ _____ _____ _____
 __|  |   __|     |   | |  JSON for Modern C++ (test suite)
|  |  |__   |  |  | | | |  version 2.0.5
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

#include <string>
#include <memory>
#include "catch.hpp"

#include "json.hpp"
using nlohmann::json;

namespace udt
{
struct empty_type {};
struct pod_type {
  int a;
  char b;
  short c;
};

inline bool operator==(pod_type const& lhs, pod_type const& rhs) noexcept
{
  return std::tie(lhs.a, lhs.b, lhs.c) == std::tie(rhs.a, rhs.b, rhs.c);
}

struct bit_more_complex_type {
  pod_type a;
  pod_type b;
  std::string c;
};

inline bool operator==(bit_more_complex_type const &lhs,
                       bit_more_complex_type const &rhs) noexcept {
  return std::tie(lhs.a, lhs.b, lhs.c) == std::tie(rhs.a, rhs.b, rhs.c);
}

// best optional implementation ever
template <typename T>
class optional_type
{
public:
  optional_type() = default;
  explicit optional_type(T val) : _val(std::make_shared<T>(std::move(val))) {}
  explicit operator bool() const noexcept { return _val != nullptr; }

  T const &operator*() const { return *_val; }

private:
  std::shared_ptr<T> _val;
};

template <typename T>
inline bool operator==(optional_type<T> const& lhs, optional_type<T> const& rhs)
{
  if (!lhs && !rhs)
    return true;
  if (!lhs || !rhs)
    return false;
  return *lhs == *rhs;
}
}

namespace nlohmann
{
template <>
struct json_traits<udt::empty_type>
{
  using type = udt::empty_type;

  static json to_json(type)
  {
    return json::object();
  }
  
  static type from_json(json const& j)
  {
    assert(j.is_object() and j.empty());
    return {};
  }
};

template <>
struct json_traits<udt::pod_type>
{  
  using type = udt::pod_type;

  static json to_json(type const& t)
  {
    return {{"a", t.a}, {"b", t.b}, {"c", t.c}};
  }
  
  static type from_json(json const& j)
  {
    assert(j.is_object());
    return {j["a"].get<int>(), j["b"].get<char>(), j["c"].get<short>()};
  }
};

template <>
struct json_traits<udt::bit_more_complex_type>
{
  using type = udt::bit_more_complex_type;

  static json to_json(type const& t)
  {
    return json{{"a", json{t.a}}, {"b", json{t.b}}, {"c", t.c}};
  }

  static type from_json(json const& j)
  {
    return {j["a"].get<udt::pod_type>(), j["b"].get<udt::pod_type>(),
            j["c"].get<std::string>()};
  }
};

template <typename T>
struct json_traits<udt::optional_type<T>>
{
  using type = udt::optional_type<T>;

  static json to_json(type const& t)
  {
    if (t)
      return json(*t);
    return {};
  }

  static type from_json(json const& j)
  {
    if (j.is_null())
      return {};
    return type{j.get<T>()};
  }
};
}


TEST_CASE("constructors for user-defined types", "[udt]")
{
  SECTION("empty type")
  {
    udt::empty_type const e;
    auto const j = json{e};
    auto k = json::object();
    CHECK(j == k);
  }

  SECTION("pod type")
  {
    auto const e = udt::pod_type{42, 42, 42};
    auto j = json{e};
    auto k = json{{"a", 42}, {"b", 42}, {"c", 42}};
    CHECK(j == k);
  }

  SECTION("bit more complex type")
  {
    auto const e =
        udt::bit_more_complex_type{{42, 42, 42}, {41, 41, 41}, "forty"};

    auto j = json{e};
    auto k = json{{"a", {{"a", 42}, {"b", 42}, {"c", 42}}},
                  {"b", {{"a", 41}, {"b", 41}, {"c", 41}}},
                  {"c", "forty"}};
    CHECK(j == k);
  }

  SECTION("vector of udt")
  {
    std::vector<udt::bit_more_complex_type> v;
    auto const e =
        udt::bit_more_complex_type{{42, 42, 42}, {41, 41, 41}, "forty"};

    v.emplace_back(e);
    v.emplace_back(e);
    v.emplace_back(e);

    json j = v;
    auto k = json{{"a", {{"a", 42}, {"b", 42}, {"c", 42}}},
                  {"b", {{"a", 41}, {"b", 41}, {"c", 41}}},
                  {"c", "forty"}};
    auto l = json{k, k, k};
    CHECK(j == l);
  }

  SECTION("optional type") {
    SECTION("regular case") {
      udt::optional_type<int> u{3};
      CHECK(json{u} == json(3));
    }

    SECTION("nullopt case") {
      udt::optional_type<float> v;
      CHECK(json{v} == json{});
    }

    SECTION("optional of json convertible type")
    {
      auto const e =
          udt::bit_more_complex_type{{42, 42, 42}, {41, 41, 41}, "forty"};
      udt::optional_type<udt::bit_more_complex_type> o{e};
      auto k = json{{"a", {{"a", 42}, {"b", 42}, {"c", 42}}},
                    {"b", {{"a", 41}, {"b", 41}, {"c", 41}}},
                    {"c", "forty"}};
      CHECK(json{o} == k);
    }

    SECTION("optional of vector of json convertible type")
    {
      std::vector<udt::bit_more_complex_type> v;
      auto const e =
          udt::bit_more_complex_type{{42, 42, 42}, {41, 41, 41}, "forty"};
      v.emplace_back(e);
      v.emplace_back(e);
      v.emplace_back(e);
      udt::optional_type<std::vector<udt::bit_more_complex_type>> o{v};
      auto k = json{{"a", {{"a", 42}, {"b", 42}, {"c", 42}}},
                    {"b", {{"a", 41}, {"b", 41}, {"c", 41}}},
                    {"c", "forty"}};
      auto l = json{k, k, k};
      CHECK(json{o} == l);
    }
  }
}

TEST_CASE("get<> for user-defined types", "[udt]")
{
  SECTION("pod type")
  {
    auto const e = udt::pod_type{42, 42, 42};
    auto const j = json{{"a", 42}, {"b", 42}, {"c", 42}};

    auto const obj = j.get<udt::pod_type>();
    CHECK(e == obj);
  }

  SECTION("bit more complex type")
  {
    auto const e =
        udt::bit_more_complex_type{{42, 42, 42}, {41, 41, 41}, "forty"};
    auto const j = json{{"a", {{"a", 42}, {"b", 42}, {"c", 42}}},
                        {"b", {{"a", 41}, {"b", 41}, {"c", 41}}},
                        {"c", "forty"}};

    auto const obj = j.get<udt::bit_more_complex_type>();
    CHECK(e == obj);
  }

  SECTION("vector of udt")
  {
    auto const e =
        udt::bit_more_complex_type{{42, 42, 42}, {41, 41, 41}, "forty"};
    std::vector<udt::bit_more_complex_type> v{e, e, e};
    auto const j = json(v);

    auto const obj = j.get<decltype(v)>();
    CHECK(v == obj);
  }

  SECTION("optional")
  {
    SECTION("from null")
    {
      udt::optional_type<int> o;
      json j;
      CHECK(j.get<decltype(o)>() == o);
    }

    SECTION("from value")
    {
      json j{{"a", 42}, {"b", 42}, {"c", 42}};
      auto v = j.get<udt::optional_type<udt::pod_type>>();
      auto expected = udt::pod_type{42,42,42};
      REQUIRE(v);
      CHECK(*v == expected);
    }
  }
}
