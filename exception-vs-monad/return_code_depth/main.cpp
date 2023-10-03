
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

tl::expected<int, error_t> fallible_function0_group0();
volatile int side_effect0 = 0;

tl::expected<int, error_t> fallible_function0_group1();
volatile int side_effect1 = 0;

tl::expected<int, error_t> fallible_function0_group2();
volatile int side_effect2 = 0;

tl::expected<int, error_t> fallible_function0_group3();
volatile int side_effect3 = 0;

tl::expected<int, error_t> fallible_function0_group4();
volatile int side_effect4 = 0;

tl::expected<int, error_t> fallible_function0_group5();
volatile int side_effect5 = 0;

tl::expected<int, error_t> fallible_function0_group6();
volatile int side_effect6 = 0;

tl::expected<int, error_t> fallible_function0_group7();
volatile int side_effect7 = 0;

tl::expected<int, error_t> fallible_function0_group8();
volatile int side_effect8 = 0;

tl::expected<int, error_t> fallible_function0_group9();
volatile int side_effect9 = 0;

tl::expected<int, error_t> return_error()
{

  if (auto result = fallible_function0_group0(); !result) {
    return tl::unexpected(result.error());
  }

  if (auto result = fallible_function0_group1(); !result) {
    return tl::unexpected(result.error());
  }

  if (auto result = fallible_function0_group2(); !result) {
    return tl::unexpected(result.error());
  }

  if (auto result = fallible_function0_group3(); !result) {
    return tl::unexpected(result.error());
  }

  if (auto result = fallible_function0_group4(); !result) {
    return tl::unexpected(result.error());
  }

  if (auto result = fallible_function0_group5(); !result) {
    return tl::unexpected(result.error());
  }

  if (auto result = fallible_function0_group6(); !result) {
    return tl::unexpected(result.error());
  }

  if (auto result = fallible_function0_group7(); !result) {
    return tl::unexpected(result.error());
  }

  if (auto result = fallible_function0_group8(); !result) {
    return tl::unexpected(result.error());
  }

  if (auto result = fallible_function0_group9(); !result) {
    return tl::unexpected(result.error());
  }
  return side_effect0 + side_effect1 + side_effect2 + side_effect3 +
         side_effect4 + side_effect5 + side_effect6 + side_effect7 +
         side_effect8 + side_effect9;
}

tl::expected<int, error_t> fallible_function1_group0();

tl::expected<int, error_t> fallible_function0_group0()
{
  auto result_a = non_trivial_destructor::initialize(0);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(0);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function1_group0(); result) {
    side_effect0 = side_effect0 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect0;
}

tl::expected<int, error_t> fallible_function2_group0();

tl::expected<int, error_t> fallible_function1_group0()
{
  auto result_a = non_trivial_destructor::initialize(0);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(0);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function2_group0(); result) {
    side_effect0 = side_effect0 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect0;
}

tl::expected<int, error_t> fallible_function3_group0();

tl::expected<int, error_t> fallible_function2_group0()
{
  auto result_a = non_trivial_destructor::initialize(0);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(0);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function3_group0(); result) {
    side_effect0 = side_effect0 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect0;
}

tl::expected<int, error_t> fallible_function4_group0();

tl::expected<int, error_t> fallible_function3_group0()
{
  auto result_a = non_trivial_destructor::initialize(0);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(0);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function4_group0(); result) {
    side_effect0 = side_effect0 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect0;
}

tl::expected<int, error_t> fallible_function5_group0();

tl::expected<int, error_t> fallible_function4_group0()
{
  auto result_a = non_trivial_destructor::initialize(0);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(0);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function5_group0(); result) {
    side_effect0 = side_effect0 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect0;
}

tl::expected<int, error_t> fallible_function6_group0();

tl::expected<int, error_t> fallible_function5_group0()
{
  auto result_a = non_trivial_destructor::initialize(0);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(0);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function6_group0(); result) {
    side_effect0 = side_effect0 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect0;
}

tl::expected<int, error_t> fallible_function7_group0();

tl::expected<int, error_t> fallible_function6_group0()
{
  auto result_a = non_trivial_destructor::initialize(0);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(0);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function7_group0(); result) {
    side_effect0 = side_effect0 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect0;
}

tl::expected<int, error_t> fallible_function8_group0();

tl::expected<int, error_t> fallible_function7_group0()
{
  auto result_a = non_trivial_destructor::initialize(0);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(0);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function8_group0(); result) {
    side_effect0 = side_effect0 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect0;
}

tl::expected<int, error_t> fallible_function9_group0();

tl::expected<int, error_t> fallible_function8_group0()
{
  auto result_a = non_trivial_destructor::initialize(0);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(0);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function9_group0(); result) {
    side_effect0 = side_effect0 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect0;
}

tl::expected<int, error_t> fallible_function10_group0();

tl::expected<int, error_t> fallible_function9_group0()
{
  auto result_a = non_trivial_destructor::initialize(0);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(0);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function10_group0(); result) {
    side_effect0 = side_effect0 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect0;
}

tl::expected<int, error_t> fallible_function11_group0();

tl::expected<int, error_t> fallible_function10_group0()
{
  auto result_a = non_trivial_destructor::initialize(0);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(0);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function11_group0(); result) {
    side_effect0 = side_effect0 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect0;
}

tl::expected<int, error_t> fallible_function12_group0();

tl::expected<int, error_t> fallible_function11_group0()
{
  auto result_a = non_trivial_destructor::initialize(0);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(0);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function12_group0(); result) {
    side_effect0 = side_effect0 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect0;
}

tl::expected<int, error_t> fallible_function13_group0();

tl::expected<int, error_t> fallible_function12_group0()
{
  auto result_a = non_trivial_destructor::initialize(0);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(0);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function13_group0(); result) {
    side_effect0 = side_effect0 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect0;
}

tl::expected<int, error_t> fallible_function14_group0();

tl::expected<int, error_t> fallible_function13_group0()
{
  auto result_a = non_trivial_destructor::initialize(0);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(0);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function14_group0(); result) {
    side_effect0 = side_effect0 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect0;
}

tl::expected<int, error_t> fallible_function15_group0();

tl::expected<int, error_t> fallible_function14_group0()
{
  auto result_a = non_trivial_destructor::initialize(0);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(0);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function15_group0(); result) {
    side_effect0 = side_effect0 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect0;
}

tl::expected<int, error_t> fallible_function15_group0()
{
  if (auto result = non_trivial_destructor::initialize(15); result) {
    auto result_internal = result.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect0 + 1;
}

tl::expected<int, error_t> fallible_function1_group1();

tl::expected<int, error_t> fallible_function0_group1()
{
  auto result_a = non_trivial_destructor::initialize(1);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(1);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function1_group1(); result) {
    side_effect1 = side_effect1 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect1;
}

tl::expected<int, error_t> fallible_function2_group1();

tl::expected<int, error_t> fallible_function1_group1()
{
  auto result_a = non_trivial_destructor::initialize(1);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(1);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function2_group1(); result) {
    side_effect1 = side_effect1 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect1;
}

tl::expected<int, error_t> fallible_function3_group1();

tl::expected<int, error_t> fallible_function2_group1()
{
  auto result_a = non_trivial_destructor::initialize(1);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(1);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function3_group1(); result) {
    side_effect1 = side_effect1 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect1;
}

tl::expected<int, error_t> fallible_function4_group1();

tl::expected<int, error_t> fallible_function3_group1()
{
  auto result_a = non_trivial_destructor::initialize(1);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(1);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function4_group1(); result) {
    side_effect1 = side_effect1 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect1;
}

tl::expected<int, error_t> fallible_function5_group1();

tl::expected<int, error_t> fallible_function4_group1()
{
  auto result_a = non_trivial_destructor::initialize(1);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(1);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function5_group1(); result) {
    side_effect1 = side_effect1 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect1;
}

tl::expected<int, error_t> fallible_function6_group1();

tl::expected<int, error_t> fallible_function5_group1()
{
  auto result_a = non_trivial_destructor::initialize(1);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(1);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function6_group1(); result) {
    side_effect1 = side_effect1 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect1;
}

tl::expected<int, error_t> fallible_function7_group1();

tl::expected<int, error_t> fallible_function6_group1()
{
  auto result_a = non_trivial_destructor::initialize(1);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(1);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function7_group1(); result) {
    side_effect1 = side_effect1 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect1;
}

tl::expected<int, error_t> fallible_function8_group1();

tl::expected<int, error_t> fallible_function7_group1()
{
  auto result_a = non_trivial_destructor::initialize(1);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(1);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function8_group1(); result) {
    side_effect1 = side_effect1 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect1;
}

tl::expected<int, error_t> fallible_function9_group1();

tl::expected<int, error_t> fallible_function8_group1()
{
  auto result_a = non_trivial_destructor::initialize(1);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(1);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function9_group1(); result) {
    side_effect1 = side_effect1 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect1;
}

tl::expected<int, error_t> fallible_function10_group1();

tl::expected<int, error_t> fallible_function9_group1()
{
  auto result_a = non_trivial_destructor::initialize(1);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(1);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function10_group1(); result) {
    side_effect1 = side_effect1 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect1;
}

tl::expected<int, error_t> fallible_function11_group1();

tl::expected<int, error_t> fallible_function10_group1()
{
  auto result_a = non_trivial_destructor::initialize(1);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(1);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function11_group1(); result) {
    side_effect1 = side_effect1 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect1;
}

tl::expected<int, error_t> fallible_function12_group1();

tl::expected<int, error_t> fallible_function11_group1()
{
  auto result_a = non_trivial_destructor::initialize(1);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(1);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function12_group1(); result) {
    side_effect1 = side_effect1 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect1;
}

tl::expected<int, error_t> fallible_function13_group1();

tl::expected<int, error_t> fallible_function12_group1()
{
  auto result_a = non_trivial_destructor::initialize(1);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(1);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function13_group1(); result) {
    side_effect1 = side_effect1 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect1;
}

tl::expected<int, error_t> fallible_function14_group1();

tl::expected<int, error_t> fallible_function13_group1()
{
  auto result_a = non_trivial_destructor::initialize(1);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(1);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function14_group1(); result) {
    side_effect1 = side_effect1 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect1;
}

tl::expected<int, error_t> fallible_function15_group1();

tl::expected<int, error_t> fallible_function14_group1()
{
  auto result_a = non_trivial_destructor::initialize(1);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(1);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function15_group1(); result) {
    side_effect1 = side_effect1 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect1;
}

tl::expected<int, error_t> fallible_function15_group1()
{
  if (auto result = non_trivial_destructor::initialize(15); result) {
    auto result_internal = result.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect1 + 1;
}

tl::expected<int, error_t> fallible_function1_group2();

tl::expected<int, error_t> fallible_function0_group2()
{
  auto result_a = non_trivial_destructor::initialize(2);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(2);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function1_group2(); result) {
    side_effect2 = side_effect2 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect2;
}

tl::expected<int, error_t> fallible_function2_group2();

tl::expected<int, error_t> fallible_function1_group2()
{
  auto result_a = non_trivial_destructor::initialize(2);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(2);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function2_group2(); result) {
    side_effect2 = side_effect2 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect2;
}

tl::expected<int, error_t> fallible_function3_group2();

tl::expected<int, error_t> fallible_function2_group2()
{
  auto result_a = non_trivial_destructor::initialize(2);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(2);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function3_group2(); result) {
    side_effect2 = side_effect2 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect2;
}

tl::expected<int, error_t> fallible_function4_group2();

tl::expected<int, error_t> fallible_function3_group2()
{
  auto result_a = non_trivial_destructor::initialize(2);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(2);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function4_group2(); result) {
    side_effect2 = side_effect2 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect2;
}

tl::expected<int, error_t> fallible_function5_group2();

tl::expected<int, error_t> fallible_function4_group2()
{
  auto result_a = non_trivial_destructor::initialize(2);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(2);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function5_group2(); result) {
    side_effect2 = side_effect2 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect2;
}

tl::expected<int, error_t> fallible_function6_group2();

tl::expected<int, error_t> fallible_function5_group2()
{
  auto result_a = non_trivial_destructor::initialize(2);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(2);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function6_group2(); result) {
    side_effect2 = side_effect2 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect2;
}

tl::expected<int, error_t> fallible_function7_group2();

tl::expected<int, error_t> fallible_function6_group2()
{
  auto result_a = non_trivial_destructor::initialize(2);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(2);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function7_group2(); result) {
    side_effect2 = side_effect2 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect2;
}

tl::expected<int, error_t> fallible_function8_group2();

tl::expected<int, error_t> fallible_function7_group2()
{
  auto result_a = non_trivial_destructor::initialize(2);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(2);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function8_group2(); result) {
    side_effect2 = side_effect2 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect2;
}

tl::expected<int, error_t> fallible_function9_group2();

tl::expected<int, error_t> fallible_function8_group2()
{
  auto result_a = non_trivial_destructor::initialize(2);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(2);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function9_group2(); result) {
    side_effect2 = side_effect2 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect2;
}

tl::expected<int, error_t> fallible_function10_group2();

tl::expected<int, error_t> fallible_function9_group2()
{
  auto result_a = non_trivial_destructor::initialize(2);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(2);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function10_group2(); result) {
    side_effect2 = side_effect2 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect2;
}

tl::expected<int, error_t> fallible_function11_group2();

tl::expected<int, error_t> fallible_function10_group2()
{
  auto result_a = non_trivial_destructor::initialize(2);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(2);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function11_group2(); result) {
    side_effect2 = side_effect2 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect2;
}

tl::expected<int, error_t> fallible_function12_group2();

tl::expected<int, error_t> fallible_function11_group2()
{
  auto result_a = non_trivial_destructor::initialize(2);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(2);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function12_group2(); result) {
    side_effect2 = side_effect2 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect2;
}

tl::expected<int, error_t> fallible_function13_group2();

tl::expected<int, error_t> fallible_function12_group2()
{
  auto result_a = non_trivial_destructor::initialize(2);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(2);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function13_group2(); result) {
    side_effect2 = side_effect2 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect2;
}

tl::expected<int, error_t> fallible_function14_group2();

tl::expected<int, error_t> fallible_function13_group2()
{
  auto result_a = non_trivial_destructor::initialize(2);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(2);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function14_group2(); result) {
    side_effect2 = side_effect2 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect2;
}

tl::expected<int, error_t> fallible_function15_group2();

tl::expected<int, error_t> fallible_function14_group2()
{
  auto result_a = non_trivial_destructor::initialize(2);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(2);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function15_group2(); result) {
    side_effect2 = side_effect2 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect2;
}

tl::expected<int, error_t> fallible_function15_group2()
{
  if (auto result = non_trivial_destructor::initialize(15); result) {
    auto result_internal = result.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect2 + 1;
}

tl::expected<int, error_t> fallible_function1_group3();

tl::expected<int, error_t> fallible_function0_group3()
{
  auto result_a = non_trivial_destructor::initialize(3);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(3);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function1_group3(); result) {
    side_effect3 = side_effect3 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect3;
}

tl::expected<int, error_t> fallible_function2_group3();

tl::expected<int, error_t> fallible_function1_group3()
{
  auto result_a = non_trivial_destructor::initialize(3);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(3);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function2_group3(); result) {
    side_effect3 = side_effect3 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect3;
}

tl::expected<int, error_t> fallible_function3_group3();

tl::expected<int, error_t> fallible_function2_group3()
{
  auto result_a = non_trivial_destructor::initialize(3);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(3);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function3_group3(); result) {
    side_effect3 = side_effect3 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect3;
}

tl::expected<int, error_t> fallible_function4_group3();

tl::expected<int, error_t> fallible_function3_group3()
{
  auto result_a = non_trivial_destructor::initialize(3);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(3);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function4_group3(); result) {
    side_effect3 = side_effect3 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect3;
}

tl::expected<int, error_t> fallible_function5_group3();

tl::expected<int, error_t> fallible_function4_group3()
{
  auto result_a = non_trivial_destructor::initialize(3);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(3);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function5_group3(); result) {
    side_effect3 = side_effect3 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect3;
}

tl::expected<int, error_t> fallible_function6_group3();

tl::expected<int, error_t> fallible_function5_group3()
{
  auto result_a = non_trivial_destructor::initialize(3);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(3);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function6_group3(); result) {
    side_effect3 = side_effect3 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect3;
}

tl::expected<int, error_t> fallible_function7_group3();

tl::expected<int, error_t> fallible_function6_group3()
{
  auto result_a = non_trivial_destructor::initialize(3);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(3);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function7_group3(); result) {
    side_effect3 = side_effect3 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect3;
}

tl::expected<int, error_t> fallible_function8_group3();

tl::expected<int, error_t> fallible_function7_group3()
{
  auto result_a = non_trivial_destructor::initialize(3);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(3);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function8_group3(); result) {
    side_effect3 = side_effect3 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect3;
}

tl::expected<int, error_t> fallible_function9_group3();

tl::expected<int, error_t> fallible_function8_group3()
{
  auto result_a = non_trivial_destructor::initialize(3);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(3);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function9_group3(); result) {
    side_effect3 = side_effect3 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect3;
}

tl::expected<int, error_t> fallible_function10_group3();

tl::expected<int, error_t> fallible_function9_group3()
{
  auto result_a = non_trivial_destructor::initialize(3);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(3);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function10_group3(); result) {
    side_effect3 = side_effect3 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect3;
}

tl::expected<int, error_t> fallible_function11_group3();

tl::expected<int, error_t> fallible_function10_group3()
{
  auto result_a = non_trivial_destructor::initialize(3);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(3);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function11_group3(); result) {
    side_effect3 = side_effect3 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect3;
}

tl::expected<int, error_t> fallible_function12_group3();

tl::expected<int, error_t> fallible_function11_group3()
{
  auto result_a = non_trivial_destructor::initialize(3);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(3);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function12_group3(); result) {
    side_effect3 = side_effect3 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect3;
}

tl::expected<int, error_t> fallible_function13_group3();

tl::expected<int, error_t> fallible_function12_group3()
{
  auto result_a = non_trivial_destructor::initialize(3);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(3);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function13_group3(); result) {
    side_effect3 = side_effect3 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect3;
}

tl::expected<int, error_t> fallible_function14_group3();

tl::expected<int, error_t> fallible_function13_group3()
{
  auto result_a = non_trivial_destructor::initialize(3);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(3);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function14_group3(); result) {
    side_effect3 = side_effect3 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect3;
}

tl::expected<int, error_t> fallible_function15_group3();

tl::expected<int, error_t> fallible_function14_group3()
{
  auto result_a = non_trivial_destructor::initialize(3);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(3);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function15_group3(); result) {
    side_effect3 = side_effect3 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect3;
}

tl::expected<int, error_t> fallible_function15_group3()
{
  if (auto result = non_trivial_destructor::initialize(15); result) {
    auto result_internal = result.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect3 + 1;
}

tl::expected<int, error_t> fallible_function1_group4();

tl::expected<int, error_t> fallible_function0_group4()
{
  auto result_a = non_trivial_destructor::initialize(4);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(4);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function1_group4(); result) {
    side_effect4 = side_effect4 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect4;
}

tl::expected<int, error_t> fallible_function2_group4();

tl::expected<int, error_t> fallible_function1_group4()
{
  auto result_a = non_trivial_destructor::initialize(4);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(4);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function2_group4(); result) {
    side_effect4 = side_effect4 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect4;
}

tl::expected<int, error_t> fallible_function3_group4();

tl::expected<int, error_t> fallible_function2_group4()
{
  auto result_a = non_trivial_destructor::initialize(4);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(4);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function3_group4(); result) {
    side_effect4 = side_effect4 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect4;
}

tl::expected<int, error_t> fallible_function4_group4();

tl::expected<int, error_t> fallible_function3_group4()
{
  auto result_a = non_trivial_destructor::initialize(4);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(4);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function4_group4(); result) {
    side_effect4 = side_effect4 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect4;
}

tl::expected<int, error_t> fallible_function5_group4();

tl::expected<int, error_t> fallible_function4_group4()
{
  auto result_a = non_trivial_destructor::initialize(4);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(4);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function5_group4(); result) {
    side_effect4 = side_effect4 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect4;
}

tl::expected<int, error_t> fallible_function6_group4();

tl::expected<int, error_t> fallible_function5_group4()
{
  auto result_a = non_trivial_destructor::initialize(4);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(4);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function6_group4(); result) {
    side_effect4 = side_effect4 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect4;
}

tl::expected<int, error_t> fallible_function7_group4();

tl::expected<int, error_t> fallible_function6_group4()
{
  auto result_a = non_trivial_destructor::initialize(4);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(4);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function7_group4(); result) {
    side_effect4 = side_effect4 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect4;
}

tl::expected<int, error_t> fallible_function8_group4();

tl::expected<int, error_t> fallible_function7_group4()
{
  auto result_a = non_trivial_destructor::initialize(4);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(4);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function8_group4(); result) {
    side_effect4 = side_effect4 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect4;
}

tl::expected<int, error_t> fallible_function9_group4();

tl::expected<int, error_t> fallible_function8_group4()
{
  auto result_a = non_trivial_destructor::initialize(4);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(4);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function9_group4(); result) {
    side_effect4 = side_effect4 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect4;
}

tl::expected<int, error_t> fallible_function10_group4();

tl::expected<int, error_t> fallible_function9_group4()
{
  auto result_a = non_trivial_destructor::initialize(4);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(4);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function10_group4(); result) {
    side_effect4 = side_effect4 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect4;
}

tl::expected<int, error_t> fallible_function11_group4();

tl::expected<int, error_t> fallible_function10_group4()
{
  auto result_a = non_trivial_destructor::initialize(4);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(4);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function11_group4(); result) {
    side_effect4 = side_effect4 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect4;
}

tl::expected<int, error_t> fallible_function12_group4();

tl::expected<int, error_t> fallible_function11_group4()
{
  auto result_a = non_trivial_destructor::initialize(4);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(4);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function12_group4(); result) {
    side_effect4 = side_effect4 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect4;
}

tl::expected<int, error_t> fallible_function13_group4();

tl::expected<int, error_t> fallible_function12_group4()
{
  auto result_a = non_trivial_destructor::initialize(4);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(4);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function13_group4(); result) {
    side_effect4 = side_effect4 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect4;
}

tl::expected<int, error_t> fallible_function14_group4();

tl::expected<int, error_t> fallible_function13_group4()
{
  auto result_a = non_trivial_destructor::initialize(4);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(4);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function14_group4(); result) {
    side_effect4 = side_effect4 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect4;
}

tl::expected<int, error_t> fallible_function15_group4();

tl::expected<int, error_t> fallible_function14_group4()
{
  auto result_a = non_trivial_destructor::initialize(4);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(4);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function15_group4(); result) {
    side_effect4 = side_effect4 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect4;
}

tl::expected<int, error_t> fallible_function15_group4()
{
  if (auto result = non_trivial_destructor::initialize(15); result) {
    auto result_internal = result.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect4 + 1;
}

tl::expected<int, error_t> fallible_function1_group5();

tl::expected<int, error_t> fallible_function0_group5()
{
  auto result_a = non_trivial_destructor::initialize(5);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(5);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function1_group5(); result) {
    side_effect5 = side_effect5 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect5;
}

tl::expected<int, error_t> fallible_function2_group5();

tl::expected<int, error_t> fallible_function1_group5()
{
  auto result_a = non_trivial_destructor::initialize(5);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(5);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function2_group5(); result) {
    side_effect5 = side_effect5 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect5;
}

tl::expected<int, error_t> fallible_function3_group5();

tl::expected<int, error_t> fallible_function2_group5()
{
  auto result_a = non_trivial_destructor::initialize(5);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(5);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function3_group5(); result) {
    side_effect5 = side_effect5 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect5;
}

tl::expected<int, error_t> fallible_function4_group5();

tl::expected<int, error_t> fallible_function3_group5()
{
  auto result_a = non_trivial_destructor::initialize(5);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(5);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function4_group5(); result) {
    side_effect5 = side_effect5 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect5;
}

tl::expected<int, error_t> fallible_function5_group5();

tl::expected<int, error_t> fallible_function4_group5()
{
  auto result_a = non_trivial_destructor::initialize(5);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(5);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function5_group5(); result) {
    side_effect5 = side_effect5 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect5;
}

tl::expected<int, error_t> fallible_function6_group5();

tl::expected<int, error_t> fallible_function5_group5()
{
  auto result_a = non_trivial_destructor::initialize(5);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(5);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function6_group5(); result) {
    side_effect5 = side_effect5 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect5;
}

tl::expected<int, error_t> fallible_function7_group5();

tl::expected<int, error_t> fallible_function6_group5()
{
  auto result_a = non_trivial_destructor::initialize(5);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(5);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function7_group5(); result) {
    side_effect5 = side_effect5 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect5;
}

tl::expected<int, error_t> fallible_function8_group5();

tl::expected<int, error_t> fallible_function7_group5()
{
  auto result_a = non_trivial_destructor::initialize(5);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(5);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function8_group5(); result) {
    side_effect5 = side_effect5 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect5;
}

tl::expected<int, error_t> fallible_function9_group5();

tl::expected<int, error_t> fallible_function8_group5()
{
  auto result_a = non_trivial_destructor::initialize(5);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(5);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function9_group5(); result) {
    side_effect5 = side_effect5 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect5;
}

tl::expected<int, error_t> fallible_function10_group5();

tl::expected<int, error_t> fallible_function9_group5()
{
  auto result_a = non_trivial_destructor::initialize(5);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(5);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function10_group5(); result) {
    side_effect5 = side_effect5 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect5;
}

tl::expected<int, error_t> fallible_function11_group5();

tl::expected<int, error_t> fallible_function10_group5()
{
  auto result_a = non_trivial_destructor::initialize(5);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(5);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function11_group5(); result) {
    side_effect5 = side_effect5 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect5;
}

tl::expected<int, error_t> fallible_function12_group5();

tl::expected<int, error_t> fallible_function11_group5()
{
  auto result_a = non_trivial_destructor::initialize(5);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(5);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function12_group5(); result) {
    side_effect5 = side_effect5 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect5;
}

tl::expected<int, error_t> fallible_function13_group5();

tl::expected<int, error_t> fallible_function12_group5()
{
  auto result_a = non_trivial_destructor::initialize(5);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(5);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function13_group5(); result) {
    side_effect5 = side_effect5 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect5;
}

tl::expected<int, error_t> fallible_function14_group5();

tl::expected<int, error_t> fallible_function13_group5()
{
  auto result_a = non_trivial_destructor::initialize(5);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(5);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function14_group5(); result) {
    side_effect5 = side_effect5 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect5;
}

tl::expected<int, error_t> fallible_function15_group5();

tl::expected<int, error_t> fallible_function14_group5()
{
  auto result_a = non_trivial_destructor::initialize(5);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(5);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function15_group5(); result) {
    side_effect5 = side_effect5 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect5;
}

tl::expected<int, error_t> fallible_function15_group5()
{
  if (auto result = non_trivial_destructor::initialize(15); result) {
    auto result_internal = result.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect5 + 1;
}

tl::expected<int, error_t> fallible_function1_group6();

tl::expected<int, error_t> fallible_function0_group6()
{
  auto result_a = non_trivial_destructor::initialize(6);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(6);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function1_group6(); result) {
    side_effect6 = side_effect6 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect6;
}

tl::expected<int, error_t> fallible_function2_group6();

tl::expected<int, error_t> fallible_function1_group6()
{
  auto result_a = non_trivial_destructor::initialize(6);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(6);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function2_group6(); result) {
    side_effect6 = side_effect6 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect6;
}

tl::expected<int, error_t> fallible_function3_group6();

tl::expected<int, error_t> fallible_function2_group6()
{
  auto result_a = non_trivial_destructor::initialize(6);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(6);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function3_group6(); result) {
    side_effect6 = side_effect6 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect6;
}

tl::expected<int, error_t> fallible_function4_group6();

tl::expected<int, error_t> fallible_function3_group6()
{
  auto result_a = non_trivial_destructor::initialize(6);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(6);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function4_group6(); result) {
    side_effect6 = side_effect6 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect6;
}

tl::expected<int, error_t> fallible_function5_group6();

tl::expected<int, error_t> fallible_function4_group6()
{
  auto result_a = non_trivial_destructor::initialize(6);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(6);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function5_group6(); result) {
    side_effect6 = side_effect6 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect6;
}

tl::expected<int, error_t> fallible_function6_group6();

tl::expected<int, error_t> fallible_function5_group6()
{
  auto result_a = non_trivial_destructor::initialize(6);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(6);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function6_group6(); result) {
    side_effect6 = side_effect6 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect6;
}

tl::expected<int, error_t> fallible_function7_group6();

tl::expected<int, error_t> fallible_function6_group6()
{
  auto result_a = non_trivial_destructor::initialize(6);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(6);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function7_group6(); result) {
    side_effect6 = side_effect6 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect6;
}

tl::expected<int, error_t> fallible_function8_group6();

tl::expected<int, error_t> fallible_function7_group6()
{
  auto result_a = non_trivial_destructor::initialize(6);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(6);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function8_group6(); result) {
    side_effect6 = side_effect6 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect6;
}

tl::expected<int, error_t> fallible_function9_group6();

tl::expected<int, error_t> fallible_function8_group6()
{
  auto result_a = non_trivial_destructor::initialize(6);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(6);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function9_group6(); result) {
    side_effect6 = side_effect6 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect6;
}

tl::expected<int, error_t> fallible_function10_group6();

tl::expected<int, error_t> fallible_function9_group6()
{
  auto result_a = non_trivial_destructor::initialize(6);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(6);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function10_group6(); result) {
    side_effect6 = side_effect6 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect6;
}

tl::expected<int, error_t> fallible_function11_group6();

tl::expected<int, error_t> fallible_function10_group6()
{
  auto result_a = non_trivial_destructor::initialize(6);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(6);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function11_group6(); result) {
    side_effect6 = side_effect6 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect6;
}

tl::expected<int, error_t> fallible_function12_group6();

tl::expected<int, error_t> fallible_function11_group6()
{
  auto result_a = non_trivial_destructor::initialize(6);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(6);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function12_group6(); result) {
    side_effect6 = side_effect6 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect6;
}

tl::expected<int, error_t> fallible_function13_group6();

tl::expected<int, error_t> fallible_function12_group6()
{
  auto result_a = non_trivial_destructor::initialize(6);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(6);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function13_group6(); result) {
    side_effect6 = side_effect6 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect6;
}

tl::expected<int, error_t> fallible_function14_group6();

tl::expected<int, error_t> fallible_function13_group6()
{
  auto result_a = non_trivial_destructor::initialize(6);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(6);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function14_group6(); result) {
    side_effect6 = side_effect6 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect6;
}

tl::expected<int, error_t> fallible_function15_group6();

tl::expected<int, error_t> fallible_function14_group6()
{
  auto result_a = non_trivial_destructor::initialize(6);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(6);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function15_group6(); result) {
    side_effect6 = side_effect6 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect6;
}

tl::expected<int, error_t> fallible_function15_group6()
{
  if (auto result = non_trivial_destructor::initialize(15); result) {
    auto result_internal = result.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect6 + 1;
}

tl::expected<int, error_t> fallible_function1_group7();

tl::expected<int, error_t> fallible_function0_group7()
{
  auto result_a = non_trivial_destructor::initialize(7);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(7);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function1_group7(); result) {
    side_effect7 = side_effect7 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect7;
}

tl::expected<int, error_t> fallible_function2_group7();

tl::expected<int, error_t> fallible_function1_group7()
{
  auto result_a = non_trivial_destructor::initialize(7);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(7);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function2_group7(); result) {
    side_effect7 = side_effect7 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect7;
}

tl::expected<int, error_t> fallible_function3_group7();

tl::expected<int, error_t> fallible_function2_group7()
{
  auto result_a = non_trivial_destructor::initialize(7);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(7);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function3_group7(); result) {
    side_effect7 = side_effect7 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect7;
}

tl::expected<int, error_t> fallible_function4_group7();

tl::expected<int, error_t> fallible_function3_group7()
{
  auto result_a = non_trivial_destructor::initialize(7);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(7);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function4_group7(); result) {
    side_effect7 = side_effect7 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect7;
}

tl::expected<int, error_t> fallible_function5_group7();

tl::expected<int, error_t> fallible_function4_group7()
{
  auto result_a = non_trivial_destructor::initialize(7);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(7);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function5_group7(); result) {
    side_effect7 = side_effect7 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect7;
}

tl::expected<int, error_t> fallible_function6_group7();

tl::expected<int, error_t> fallible_function5_group7()
{
  auto result_a = non_trivial_destructor::initialize(7);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(7);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function6_group7(); result) {
    side_effect7 = side_effect7 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect7;
}

tl::expected<int, error_t> fallible_function7_group7();

tl::expected<int, error_t> fallible_function6_group7()
{
  auto result_a = non_trivial_destructor::initialize(7);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(7);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function7_group7(); result) {
    side_effect7 = side_effect7 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect7;
}

tl::expected<int, error_t> fallible_function8_group7();

tl::expected<int, error_t> fallible_function7_group7()
{
  auto result_a = non_trivial_destructor::initialize(7);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(7);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function8_group7(); result) {
    side_effect7 = side_effect7 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect7;
}

tl::expected<int, error_t> fallible_function9_group7();

tl::expected<int, error_t> fallible_function8_group7()
{
  auto result_a = non_trivial_destructor::initialize(7);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(7);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function9_group7(); result) {
    side_effect7 = side_effect7 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect7;
}

tl::expected<int, error_t> fallible_function10_group7();

tl::expected<int, error_t> fallible_function9_group7()
{
  auto result_a = non_trivial_destructor::initialize(7);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(7);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function10_group7(); result) {
    side_effect7 = side_effect7 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect7;
}

tl::expected<int, error_t> fallible_function11_group7();

tl::expected<int, error_t> fallible_function10_group7()
{
  auto result_a = non_trivial_destructor::initialize(7);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(7);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function11_group7(); result) {
    side_effect7 = side_effect7 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect7;
}

tl::expected<int, error_t> fallible_function12_group7();

tl::expected<int, error_t> fallible_function11_group7()
{
  auto result_a = non_trivial_destructor::initialize(7);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(7);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function12_group7(); result) {
    side_effect7 = side_effect7 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect7;
}

tl::expected<int, error_t> fallible_function13_group7();

tl::expected<int, error_t> fallible_function12_group7()
{
  auto result_a = non_trivial_destructor::initialize(7);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(7);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function13_group7(); result) {
    side_effect7 = side_effect7 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect7;
}

tl::expected<int, error_t> fallible_function14_group7();

tl::expected<int, error_t> fallible_function13_group7()
{
  auto result_a = non_trivial_destructor::initialize(7);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(7);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function14_group7(); result) {
    side_effect7 = side_effect7 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect7;
}

tl::expected<int, error_t> fallible_function15_group7();

tl::expected<int, error_t> fallible_function14_group7()
{
  auto result_a = non_trivial_destructor::initialize(7);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(7);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function15_group7(); result) {
    side_effect7 = side_effect7 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect7;
}

tl::expected<int, error_t> fallible_function15_group7()
{
  if (auto result = non_trivial_destructor::initialize(15); result) {
    auto result_internal = result.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect7 + 1;
}

tl::expected<int, error_t> fallible_function1_group8();

tl::expected<int, error_t> fallible_function0_group8()
{
  auto result_a = non_trivial_destructor::initialize(8);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(8);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function1_group8(); result) {
    side_effect8 = side_effect8 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect8;
}

tl::expected<int, error_t> fallible_function2_group8();

tl::expected<int, error_t> fallible_function1_group8()
{
  auto result_a = non_trivial_destructor::initialize(8);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(8);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function2_group8(); result) {
    side_effect8 = side_effect8 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect8;
}

tl::expected<int, error_t> fallible_function3_group8();

tl::expected<int, error_t> fallible_function2_group8()
{
  auto result_a = non_trivial_destructor::initialize(8);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(8);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function3_group8(); result) {
    side_effect8 = side_effect8 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect8;
}

tl::expected<int, error_t> fallible_function4_group8();

tl::expected<int, error_t> fallible_function3_group8()
{
  auto result_a = non_trivial_destructor::initialize(8);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(8);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function4_group8(); result) {
    side_effect8 = side_effect8 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect8;
}

tl::expected<int, error_t> fallible_function5_group8();

tl::expected<int, error_t> fallible_function4_group8()
{
  auto result_a = non_trivial_destructor::initialize(8);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(8);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function5_group8(); result) {
    side_effect8 = side_effect8 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect8;
}

tl::expected<int, error_t> fallible_function6_group8();

tl::expected<int, error_t> fallible_function5_group8()
{
  auto result_a = non_trivial_destructor::initialize(8);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(8);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function6_group8(); result) {
    side_effect8 = side_effect8 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect8;
}

tl::expected<int, error_t> fallible_function7_group8();

tl::expected<int, error_t> fallible_function6_group8()
{
  auto result_a = non_trivial_destructor::initialize(8);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(8);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function7_group8(); result) {
    side_effect8 = side_effect8 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect8;
}

tl::expected<int, error_t> fallible_function8_group8();

tl::expected<int, error_t> fallible_function7_group8()
{
  auto result_a = non_trivial_destructor::initialize(8);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(8);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function8_group8(); result) {
    side_effect8 = side_effect8 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect8;
}

tl::expected<int, error_t> fallible_function9_group8();

tl::expected<int, error_t> fallible_function8_group8()
{
  auto result_a = non_trivial_destructor::initialize(8);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(8);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function9_group8(); result) {
    side_effect8 = side_effect8 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect8;
}

tl::expected<int, error_t> fallible_function10_group8();

tl::expected<int, error_t> fallible_function9_group8()
{
  auto result_a = non_trivial_destructor::initialize(8);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(8);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function10_group8(); result) {
    side_effect8 = side_effect8 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect8;
}

tl::expected<int, error_t> fallible_function11_group8();

tl::expected<int, error_t> fallible_function10_group8()
{
  auto result_a = non_trivial_destructor::initialize(8);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(8);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function11_group8(); result) {
    side_effect8 = side_effect8 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect8;
}

tl::expected<int, error_t> fallible_function12_group8();

tl::expected<int, error_t> fallible_function11_group8()
{
  auto result_a = non_trivial_destructor::initialize(8);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(8);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function12_group8(); result) {
    side_effect8 = side_effect8 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect8;
}

tl::expected<int, error_t> fallible_function13_group8();

tl::expected<int, error_t> fallible_function12_group8()
{
  auto result_a = non_trivial_destructor::initialize(8);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(8);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function13_group8(); result) {
    side_effect8 = side_effect8 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect8;
}

tl::expected<int, error_t> fallible_function14_group8();

tl::expected<int, error_t> fallible_function13_group8()
{
  auto result_a = non_trivial_destructor::initialize(8);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(8);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function14_group8(); result) {
    side_effect8 = side_effect8 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect8;
}

tl::expected<int, error_t> fallible_function15_group8();

tl::expected<int, error_t> fallible_function14_group8()
{
  auto result_a = non_trivial_destructor::initialize(8);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(8);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function15_group8(); result) {
    side_effect8 = side_effect8 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect8;
}

tl::expected<int, error_t> fallible_function15_group8()
{
  if (auto result = non_trivial_destructor::initialize(15); result) {
    auto result_internal = result.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect8 + 1;
}

tl::expected<int, error_t> fallible_function1_group9();

tl::expected<int, error_t> fallible_function0_group9()
{
  auto result_a = non_trivial_destructor::initialize(9);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(9);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function1_group9(); result) {
    side_effect9 = side_effect9 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect9;
}

tl::expected<int, error_t> fallible_function2_group9();

tl::expected<int, error_t> fallible_function1_group9()
{
  auto result_a = non_trivial_destructor::initialize(9);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(9);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function2_group9(); result) {
    side_effect9 = side_effect9 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect9;
}

tl::expected<int, error_t> fallible_function3_group9();

tl::expected<int, error_t> fallible_function2_group9()
{
  auto result_a = non_trivial_destructor::initialize(9);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(9);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function3_group9(); result) {
    side_effect9 = side_effect9 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect9;
}

tl::expected<int, error_t> fallible_function4_group9();

tl::expected<int, error_t> fallible_function3_group9()
{
  auto result_a = non_trivial_destructor::initialize(9);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(9);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function4_group9(); result) {
    side_effect9 = side_effect9 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect9;
}

tl::expected<int, error_t> fallible_function5_group9();

tl::expected<int, error_t> fallible_function4_group9()
{
  auto result_a = non_trivial_destructor::initialize(9);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(9);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function5_group9(); result) {
    side_effect9 = side_effect9 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect9;
}

tl::expected<int, error_t> fallible_function6_group9();

tl::expected<int, error_t> fallible_function5_group9()
{
  auto result_a = non_trivial_destructor::initialize(9);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(9);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function6_group9(); result) {
    side_effect9 = side_effect9 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect9;
}

tl::expected<int, error_t> fallible_function7_group9();

tl::expected<int, error_t> fallible_function6_group9()
{
  auto result_a = non_trivial_destructor::initialize(9);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(9);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function7_group9(); result) {
    side_effect9 = side_effect9 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect9;
}

tl::expected<int, error_t> fallible_function8_group9();

tl::expected<int, error_t> fallible_function7_group9()
{
  auto result_a = non_trivial_destructor::initialize(9);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(9);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function8_group9(); result) {
    side_effect9 = side_effect9 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect9;
}

tl::expected<int, error_t> fallible_function9_group9();

tl::expected<int, error_t> fallible_function8_group9()
{
  auto result_a = non_trivial_destructor::initialize(9);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(9);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function9_group9(); result) {
    side_effect9 = side_effect9 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect9;
}

tl::expected<int, error_t> fallible_function10_group9();

tl::expected<int, error_t> fallible_function9_group9()
{
  auto result_a = non_trivial_destructor::initialize(9);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(9);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function10_group9(); result) {
    side_effect9 = side_effect9 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect9;
}

tl::expected<int, error_t> fallible_function11_group9();

tl::expected<int, error_t> fallible_function10_group9()
{
  auto result_a = non_trivial_destructor::initialize(9);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(9);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function11_group9(); result) {
    side_effect9 = side_effect9 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect9;
}

tl::expected<int, error_t> fallible_function12_group9();

tl::expected<int, error_t> fallible_function11_group9()
{
  auto result_a = non_trivial_destructor::initialize(9);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(9);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function12_group9(); result) {
    side_effect9 = side_effect9 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect9;
}

tl::expected<int, error_t> fallible_function13_group9();

tl::expected<int, error_t> fallible_function12_group9()
{
  auto result_a = non_trivial_destructor::initialize(9);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(9);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function13_group9(); result) {
    side_effect9 = side_effect9 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect9;
}

tl::expected<int, error_t> fallible_function14_group9();

tl::expected<int, error_t> fallible_function13_group9()
{
  auto result_a = non_trivial_destructor::initialize(9);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(9);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function14_group9(); result) {
    side_effect9 = side_effect9 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect9;
}

tl::expected<int, error_t> fallible_function15_group9();

tl::expected<int, error_t> fallible_function14_group9()
{
  auto result_a = non_trivial_destructor::initialize(9);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(9);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function15_group9(); result) {
    side_effect9 = side_effect9 + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect9;
}

tl::expected<int, error_t> fallible_function15_group9()
{
  if (auto result = non_trivial_destructor::initialize(15); result) {
    auto result_internal = result.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect9 + 1;
}
