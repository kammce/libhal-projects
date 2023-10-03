# REGEX to find number of functions in disassembly
# ^[0-9a-f]+ <fallible_function[0-9]+_group[0-9]+\(\)>:

import argparse

_FILE_HEADER = """
// Copyright 2023 Google LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <array>
#include <cstdint>

#include <tl/expected.hpp>

constexpr size_t error_size = 128;
constexpr bool error_in_constructor = true;
constexpr bool error_in_class_function = true;
constexpr uint8_t depth_before_exception = 50;

struct error_t
{
  std::array<std::uint8_t, error_size> data;
};

volatile std::uint64_t enable_register;
volatile std::uint64_t trigger_register;

class non_trivial_destructor
{
public:
  static tl::expected<non_trivial_destructor, error_t> initialize(
    uint8_t p_channel)
  {
    if constexpr (error_in_constructor) {
      if (p_channel >= depth_before_exception) {
        return tl::unexpected(error_t{ .data = { 0x55, 0xAA, 0x33, 0x44 } });
      }
    }
    enable_register = enable_register | (1 << p_channel);
    return non_trivial_destructor{ p_channel };
  }

  non_trivial_destructor(non_trivial_destructor&) = delete;
  non_trivial_destructor& operator=(non_trivial_destructor&) = delete;
  non_trivial_destructor(non_trivial_destructor&&) noexcept = default;
  non_trivial_destructor& operator=(non_trivial_destructor&&) noexcept =
    default;

  tl::expected<void, error_t> trigger()
  {
    if constexpr (error_in_class_function) {
      if (m_channel >= depth_before_exception) {
        tl::unexpected(error_t{ .data = { 0xAA, 0xBB, 0x33, 0x44 } });
      }
    }
    trigger_register = trigger_register | (1 << (m_channel % 64));

    return {};
  }

  ~non_trivial_destructor()
  {
    enable_register = enable_register & ~(1 << (m_channel % 64));
  }

private:
  non_trivial_destructor(uint8_t p_channel)
    : m_channel(p_channel)
  {
  }

  uint8_t m_channel = 0;
};

tl::expected<int, error_t> return_error();
tl::expected<int, error_t> top_call()
{
  auto result = return_error();
  if (!result) {
    return tl::unexpected(result.error());
  }
  return result.value();
}

int main()
{
  auto result = top_call();
  if (!result) {
    return static_cast<int>(result.error().data[0]);
  }
  return result.value();
}

// =============================================================================
// Add generated code below
// =============================================================================
"""
_RETURN_ERROR_FORMAT = """
{forward_declarations}
tl::expected<int, error_t> return_error()
{{
{usages}
  return {sum};
}}
"""
_RETURN_FORWARD_ENTRY = """tl::expected<int, error_t>
fallible_function0_group{group}();
volatile int side_effect{group} = 0;
"""
_RETURN_ERROR_FORMAT_ENTRY = """
  if(auto result = fallible_function0_group{group}(); !result) {{
    return tl::unexpected(result.error());
  }}"""
_RETURN_SUM = """side_effect{group}"""

_DEPTH_FUNCTION_FORMAT = """
  tl::expected<int, error_t>
  fallible_function{next_depth}_group{group}();

  tl::expected<int, error_t>
  fallible_function{depth}_group{group}()
  {{
    auto result_a = non_trivial_destructor::initialize({group});

    if (result_a) {{
      auto result_internal = result_a.value().trigger();
      if (!result_internal) {{
        return tl::unexpected(result_internal.error());
      }}
    }} else {{
      return tl::unexpected(result_a.error());
    }}

    auto result_b = non_trivial_destructor::initialize({group});

    if (result_b) {{
      auto result_internal = result_b.value().trigger();
      if (!result_internal) {{
        return tl::unexpected(result_internal.error());
      }}
    }} else {{
      return tl::unexpected(result_b.error());
    }}

    if(auto result = fallible_function{next_depth}_group{group}(); result) {{
      side_effect{group} = side_effect{group} + result.value();
    }} else {{
      return tl::unexpected(result.error());
    }}

    return side_effect{group};
  }}
  """

_LAST_DEPTH_FUNCTION_FORMAT = """
  tl::expected<int, error_t>
  fallible_function{depth}_group{group}()
  {{
    if (auto result = non_trivial_destructor::initialize({depth}); result) {{
      auto result_internal = result.value().trigger();
      if (!result_internal) {{
        return tl::unexpected(result_internal.error());
      }}
    }} else {{
      return tl::unexpected(result.error());
    }}

    return side_effect{group} + 1;
  }}
  """


def do_the_thing(max_groups: int, max_depth: int):
    return_error_function_calls = []
    forwards = []
    sums = []
    for group in range(max_groups):
        forwards.append(_RETURN_FORWARD_ENTRY.format(group=group))
        return_error_function_calls.append(
            _RETURN_ERROR_FORMAT_ENTRY.format(group=group))
        sums.append(_RETURN_SUM.format(group=group))

    sums_string = "+".join(sums)
    forward_string = "\n".join(forwards)
    call_string = "\n".join(return_error_function_calls)
    full_return_error_str = _RETURN_ERROR_FORMAT.format(
        forward_declarations=forward_string,
        usages=call_string,
        sum=sums_string)

    print(_FILE_HEADER)
    print(full_return_error_str)

    list_of_functions_and_groups = []

    for group in range(max_groups):
        for depth in range(max_depth):
            list_of_functions_and_groups.append(_DEPTH_FUNCTION_FORMAT.format(
                next_group=group + 1,
                next_depth=depth + 1,
                group=group,
                depth=depth,
            ))
        list_of_functions_and_groups.append(_LAST_DEPTH_FUNCTION_FORMAT.format(
            depth=max_depth,
            group=group))

    print("".join(list_of_functions_and_groups))


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("-g", "--max_groups",
                        help="Number of groups", default=10, type=int)
    parser.add_argument("-d", "--max_depth",
                        help="Max depth of functions", default=50, type=int)
    args = parser.parse_args()
    do_the_thing(max_depth=args.max_depth, max_groups=args.max_groups)
