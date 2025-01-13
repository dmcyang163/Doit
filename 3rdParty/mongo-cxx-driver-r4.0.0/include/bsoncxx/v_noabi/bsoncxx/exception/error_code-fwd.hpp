// Copyright 2009-present MongoDB, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#pragma once

#include <cstdint>
#include <system_error>

namespace bsoncxx {
namespace v_noabi {

enum class error_code : std::int32_t;

}  // namespace v_noabi
}  // namespace bsoncxx

namespace bsoncxx {

using ::bsoncxx::v_noabi::error_code;

}  // namespace bsoncxx

namespace std {

template <>
struct is_error_code_enum<bsoncxx::v_noabi::error_code>;

}  // namespace std

///
/// @file
/// Declares @ref bsoncxx::v_noabi::error_code.
///

#if defined(BSONCXX_PRIVATE_DOXYGEN_PREPROCESSOR)

namespace bsoncxx {

/// @ref bsoncxx::v_noabi::error_code
class error_code {};

}  // namespace bsoncxx

#endif  // defined(BSONCXX_PRIVATE_DOXYGEN_PREPROCESSOR)
