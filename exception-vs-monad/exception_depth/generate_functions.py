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
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <exception>

constexpr size_t error_size = 128;
constexpr bool check_bounds_in_constructor = true;
constexpr bool check_bounds_in_class_function = true;
constexpr uint32_t depth_before_exception = 1000;

struct error_t
{
  std::array<std::uint8_t, error_size> data;
};

volatile std::uint64_t enable_register;
volatile std::uint64_t trigger_register;

class non_trivial_destructor
{
public:
  non_trivial_destructor(uint32_t p_channel)
    : m_channel(p_channel)
  {
    if constexpr (check_bounds_in_constructor) {
      if (p_channel >= depth_before_exception) {
        throw error_t{ .data = { 0x55, 0xAA, 0x33, 0x44 } };
      }
    }
    enable_register = enable_register | (1 << (p_channel % 64));
  }

  non_trivial_destructor(non_trivial_destructor&) = delete;
  non_trivial_destructor& operator=(non_trivial_destructor&) = delete;
  non_trivial_destructor(non_trivial_destructor&&) noexcept = default;
  non_trivial_destructor& operator=(non_trivial_destructor&&) noexcept =
    default;

  ~non_trivial_destructor()
  {
    enable_register = enable_register & ~(1 << (m_channel % 64));
  }

  void trigger()
  {
    if constexpr (check_bounds_in_class_function) {
      if (m_channel >= depth_before_exception) {
        throw error_t{ .data = { 0xAA, 0xBB, 0x33, 0x44 } };
      }
    }
    trigger_register = trigger_register | (1 << (m_channel % 64));
  }

private:
  uint32_t m_channel = 0;
};

int return_error();
int top_call()
{
  return return_error();
}

int main()
{
  volatile int return_code = 0;
  try {
    return_code = top_call();
  } catch (const error_t& p_error) {
    return p_error.data[0];
  } catch (...) {
    return 15;
  }
  return return_code;
}

extern "C"
{
  void _exit([[maybe_unused]] int rc)
  {
    while (true) {
      continue;
    }
  }

  int kill(int, int)
  {
    return -1;
  }

  struct _reent* _impure_ptr = nullptr;

  int getpid()
  {
    return 1;
  }
}

[[noreturn]] void my_terminate() noexcept
{
  while (true) {
    continue;
  }
}

namespace __cxxabiv1 {
std::terminate_handler __terminate_handler = my_terminate;
}

// =============================================================================
// Add generated code below
// =============================================================================
"""

_RETURN_ERROR_FORMAT = """
{forward_declarations}
int return_error()
{{
{usages}
  return {sum};
}}
"""
_RETURN_FORWARD_ENTRY = """int fallible_function0_group{group}();
volatile int side_effect{group} = 0;
"""
_RETURN_SUM = """side_effect{group}"""
_RETURN_ERROR_FORMAT_ENTRY = """fallible_function0_group{group}();"""

_DEPTH_FUNCTION_FORMAT = """
int fallible_function{next_depth}_group{group}();
int fallible_function{depth}_group{group}()
{{
  auto result = non_trivial_destructor({depth} * {depth});
  result.trigger();
  auto result2 = non_trivial_destructor({depth} * {depth} * 2);
  result2.trigger();
  side_effect{group} = side_effect{group} +
    fallible_function{next_depth}_group{group}();
  return side_effect{group};
}}
"""

_LAST_DEPTH_FUNCTION_FORMAT = """
int fallible_function{depth}_group{group}()
{{
  auto result = non_trivial_destructor({group} * {depth});
  result.trigger();
  auto result2 = non_trivial_destructor({group} * {depth});
  result2.trigger();
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
