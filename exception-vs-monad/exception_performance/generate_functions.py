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
#include <span>

#include <libhal-armcortex/dwt_counter.hpp>

constexpr size_t error_size = 128;

struct my_error_t
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

std::uint64_t start = 0;
std::uint64_t end = 0;
hal::steady_clock* my_clock = nullptr;

int main()
{
  using namespace hal::literals;
  static hal::cortex_m::dwt_counter counter(12.0_MHz);
  my_clock = &counter;

  volatile int return_code = 0;
  try {
    return_code = top_call();
  } catch ([[maybe_unused]] const my_error_t& p_error) {
    end = counter.uptime().ticks;
    return_code = end - start;
  } catch (...) {
    return_code = -1;
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
#if 0
  std::array<std::uint8_t, 1024> storage;
  std::span<std::uint8_t> storage_left(storage.data() + 256,
                                       storage.size() - 256);
  void* __wrap___cxa_allocate_exception(unsigned int p_size)
  {
    if (p_size > storage_left.size()) {
      return nullptr;
    }
    auto memory = storage_left.data();
    storage_left = storage_left.subspan(p_size);
    return memory;
  }
  void __wrap___cxa_free_exception(void*)
  {
  }
#endif
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

int fallible_function0();
volatile int side_effect = 0;
int return_error()
{
  fallible_function0();
  return side_effect;
}

// =============================================================================
// Add generated code below
// =============================================================================
"""

_DEPTH_FUNCTION_FORMAT = """
int fallible_function{next_depth}();
int fallible_function{depth}()
{{
  auto result = non_trivial_destructor({depth});
  result.trigger();
  auto result2 = non_trivial_destructor({depth} * 2);
  result2.trigger();
  side_effect = side_effect + 1;
  side_effect = side_effect + fallible_function{next_depth}();
  return side_effect;
}}
"""

_LAST_DEPTH_FUNCTION_FORMAT = """
int fallible_function{depth}()
{{
  // This will always be true so long as you have at least one addition to
  // side_effect, but due to it being volatile, it must be read
  side_effect = side_effect + 1;
  if (side_effect >= 1) {{
    start = my_clock->uptime().ticks;
    throw my_error_t{{ .data = {{ 0xAA, 0xBB, 0x33, 0x44 }} }};
  }}
  return side_effect;
}}
"""


def do_the_thing(max_depth: int):
    print(_FILE_HEADER)

    list_of_functions_and_groups = []

    for depth in range(max_depth):
        list_of_functions_and_groups.append(_DEPTH_FUNCTION_FORMAT.format(
            next_depth=depth + 1,
            depth=depth,
        ))

    list_of_functions_and_groups.append(_LAST_DEPTH_FUNCTION_FORMAT.format(
        depth=max_depth))

    print("".join(list_of_functions_and_groups))


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("-d", "--max_depth",
                        help="Max depth of functions", default=50, type=int)
    args = parser.parse_args()
    do_the_thing(max_depth=args.max_depth)
