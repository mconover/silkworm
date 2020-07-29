/*
   Copyright 2020 The Silkworm Authors

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#include "encode.hpp"

#include <boost/algorithm/hex.hpp>
#include <catch2/catch.hpp>
#include <iterator>
#include <silkworm/common/util.hpp>
#include <sstream>
#include <string>

namespace {

template <typename T>
std::string encoded(T x) {
  std::ostringstream s;
  silkworm::rlp::encode(s, x);
  return s.str();
}

}  // namespace

namespace silkworm {

TEST_CASE("RLP encoding") {
  using boost::algorithm::hex;

  SECTION("strings") {
    CHECK(hex(encoded(ByteView{})) == "80");
    CHECK(hex(encoded(from_hex("7B"))) == "7B");
    CHECK(hex(encoded(from_hex("80"))) == "8180");
    CHECK(hex(encoded(from_hex("ABBA"))) == "82ABBA");
  }

  SECTION("uint64") {
    CHECK(hex(encoded(0)) == "80");
    CHECK(hex(encoded(1)) == "01");
    CHECK(hex(encoded(0x7F)) == "7F");
    CHECK(hex(encoded(0x80)) == "8180");
    CHECK(hex(encoded(0x400)) == "820400");
    CHECK(hex(encoded(0xFFCCB5)) == "83FFCCB5");
    CHECK(hex(encoded(0xFFCCB5DD)) == "84FFCCB5DD");
    CHECK(hex(encoded(0xFFCCB5DDFF)) == "85FFCCB5DDFF");
    CHECK(hex(encoded(0xFFCCB5DDFFEE)) == "86FFCCB5DDFFEE");
    CHECK(hex(encoded(0xFFCCB5DDFFEE14)) == "87FFCCB5DDFFEE14");
    CHECK(hex(encoded(0xFFCCB5DDFFEE1483)) == "88FFCCB5DDFFEE1483");
  }

  SECTION("uint256") {
    CHECK(hex(encoded(intx::uint256{})) == "80");
    CHECK(hex(encoded(intx::uint256{1})) == "01");
    CHECK(hex(encoded(intx::uint256{0x7F})) == "7F");
    CHECK(hex(encoded(intx::uint256{0x80})) == "8180");
    CHECK(hex(encoded(intx::uint256{0x400})) == "820400");
    CHECK(hex(encoded(intx::uint256{0xFFCCB5})) == "83FFCCB5");
    CHECK(hex(encoded(intx::uint256{0xFFCCB5DD})) == "84FFCCB5DD");
    CHECK(hex(encoded(intx::uint256{0xFFCCB5DDFF})) == "85FFCCB5DDFF");
    CHECK(hex(encoded(intx::uint256{0xFFCCB5DDFFEE})) == "86FFCCB5DDFFEE");
    CHECK(hex(encoded(intx::uint256{0xFFCCB5DDFFEE14})) == "87FFCCB5DDFFEE14");
    CHECK(hex(encoded(intx::uint256{0xFFCCB5DDFFEE1483})) == "88FFCCB5DDFFEE1483");

    CHECK(hex(encoded(intx::from_string<intx::uint256>("0x10203E405060708090A0B0C0D0E0F2"))) ==
          "8F10203E405060708090A0B0C0D0E0F2");

    CHECK(hex(encoded(intx::from_string<intx::uint256>(
              "0x0100020003000400050006000700080009000A0B4B000C000D000E01"))) ==
          "9C0100020003000400050006000700080009000A0B4B000C000D000E01");
  }

  SECTION("vectors") {
    CHECK(hex(encoded(std::vector<uint64_t>{})) == "C0");
    CHECK(hex(encoded(std::vector<uint64_t>{0xFFCCB5, 0xFFC0B5})) == "C883FFCCB583FFC0B5");
  }
}
}  // namespace silkworm