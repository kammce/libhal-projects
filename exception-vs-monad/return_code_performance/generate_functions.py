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

#include <libhal-armcortex/dwt_counter.hpp>

constexpr size_t error_size = 4;

struct my_error_t
{
  std::array<std::uint8_t, error_size> data;
};

volatile std::uint64_t enable_register;
volatile std::uint64_t trigger_register;

class non_trivial_destructor
{
public:
  static tl::expected<non_trivial_destructor, my_error_t> initialize(
    uint8_t p_channel)
  {
    enable_register = enable_register | (1 << p_channel);
    return non_trivial_destructor{ p_channel };
  }

  non_trivial_destructor(non_trivial_destructor&) = delete;
  non_trivial_destructor& operator=(non_trivial_destructor&) = delete;
  non_trivial_destructor(non_trivial_destructor&&) noexcept = default;
  non_trivial_destructor& operator=(non_trivial_destructor&&) noexcept =
    default;

  tl::expected<void, my_error_t> trigger()
  {
    trigger_register = trigger_register | (1 << (m_channel % 64));
    return {};
  }

#if defined(NON_TRIVIAL_DTOR)
  ~non_trivial_destructor()
  {
    enable_register = enable_register & ~(1 << (m_channel % 64));
  }
#endif

private:
  non_trivial_destructor(uint8_t p_channel)
    : m_channel(p_channel)
  {
  }

  uint8_t m_channel = 0;
};

tl::expected<int, my_error_t> return_error();
tl::expected<int, my_error_t> top_call()
{
  auto result = return_error();
  if (!result) {
    return tl::unexpected(result.error());
  }
  return result.value();
}

std::uint64_t start = 0;
std::uint64_t end = 0;
hal::steady_clock* my_clock = nullptr;

int main()
{
  using namespace hal::literals;
  volatile int return_code = 0;

  static hal::cortex_m::dwt_counter counter(12.0_MHz);
  my_clock = &counter;

  auto result = top_call();
  end = counter.uptime().ticks;
  if (!result) {
    return_code = end - start;
  }
  return return_code;
}

tl::expected<int, my_error_t> fallible_function0();
volatile int side_effect = 0;
tl::expected<int, my_error_t> return_error()
{
  if (auto result = fallible_function0(); !result) {
    return tl::unexpected(result.error());
  }
  return side_effect;
}

// =============================================================================
// Add generated code below
// =============================================================================
"""

_DEPTH_FUNCTION_FORMAT = """
tl::expected<int, my_error_t>
fallible_function{next_depth}();

tl::expected<int, my_error_t>
fallible_function{depth}()
{{
  auto result_a = non_trivial_destructor::initialize({depth});

  if (result_a) {{
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {{
      return tl::unexpected(result_internal.error());
    }}
  }} else {{
    return tl::unexpected(result_a.error());
  }}

  auto result_b = non_trivial_destructor::initialize({depth});

  if (result_b) {{
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {{
      return tl::unexpected(result_internal.error());
    }}
  }} else {{
    return tl::unexpected(result_b.error());
  }}

  if(auto result = fallible_function{next_depth}(); result) {{
    side_effect = side_effect + result.value();
  }} else {{
    return tl::unexpected(result.error());
  }}

  return side_effect;
}}
"""

_LAST_DEPTH_FUNCTION_FORMAT = """
tl::expected<int, my_error_t>
fallible_function{depth}()
{{
  side_effect = side_effect + 1;
  if (side_effect >= 1) {{
    start = my_clock->uptime().ticks;
    return tl::unexpected(my_error_t{{ .data = {{ 0x55, 0xAA, 0x33, 0x44 }} }});
  }}
  return side_effect + 1;
}}
"""

final_source_code: str = ""


def do_the_thing(max_depth: int, non_trivial_dtor: bool):
    global final_source_code

    if (non_trivial_dtor):
        final_source_code = final_source_code + "#define NON_TRIVIAL_DTOR 1"

    final_source_code = final_source_code + _FILE_HEADER

    list_of_functions_and_groups = []
    for depth in range(max_depth):
        list_of_functions_and_groups.append(_DEPTH_FUNCTION_FORMAT.format(
            next_depth=depth + 1,
            depth=depth,
        ))
    list_of_functions_and_groups.append(_LAST_DEPTH_FUNCTION_FORMAT.format(
        depth=max_depth))

    final_source_code = final_source_code + \
        "".join(list_of_functions_and_groups)

    print(final_source_code)


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("-d", "--max_depth",
                        help="Max depth of functions", default=10, type=int)
    parser.add_argument("-t", "--non_trivial_destructor",
                        help="Use non_trivial destructor", default=True, type=bool)
    args = parser.parse_args()
    do_the_thing(max_depth=args.max_depth,
                 non_trivial_dtor=args.non_trivial_destructor)
