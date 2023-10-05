#define NON_TRIVIAL_DTOR 1
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

tl::expected<int, my_error_t> fallible_function1();

tl::expected<int, my_error_t> fallible_function0()
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

  if (auto result = fallible_function1(); result) {
    side_effect = side_effect + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect;
}

tl::expected<int, my_error_t> fallible_function2();

tl::expected<int, my_error_t> fallible_function1()
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

  if (auto result = fallible_function2(); result) {
    side_effect = side_effect + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect;
}

tl::expected<int, my_error_t> fallible_function3();

tl::expected<int, my_error_t> fallible_function2()
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

  if (auto result = fallible_function3(); result) {
    side_effect = side_effect + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect;
}

tl::expected<int, my_error_t> fallible_function4();

tl::expected<int, my_error_t> fallible_function3()
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

  if (auto result = fallible_function4(); result) {
    side_effect = side_effect + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect;
}

tl::expected<int, my_error_t> fallible_function5();

tl::expected<int, my_error_t> fallible_function4()
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

  if (auto result = fallible_function5(); result) {
    side_effect = side_effect + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect;
}

tl::expected<int, my_error_t> fallible_function6();

tl::expected<int, my_error_t> fallible_function5()
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

  if (auto result = fallible_function6(); result) {
    side_effect = side_effect + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect;
}

tl::expected<int, my_error_t> fallible_function7();

tl::expected<int, my_error_t> fallible_function6()
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

  if (auto result = fallible_function7(); result) {
    side_effect = side_effect + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect;
}

tl::expected<int, my_error_t> fallible_function8();

tl::expected<int, my_error_t> fallible_function7()
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

  if (auto result = fallible_function8(); result) {
    side_effect = side_effect + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect;
}

tl::expected<int, my_error_t> fallible_function9();

tl::expected<int, my_error_t> fallible_function8()
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

  if (auto result = fallible_function9(); result) {
    side_effect = side_effect + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect;
}

tl::expected<int, my_error_t> fallible_function10();

tl::expected<int, my_error_t> fallible_function9()
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

  if (auto result = fallible_function10(); result) {
    side_effect = side_effect + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect;
}

tl::expected<int, my_error_t> fallible_function11();

tl::expected<int, my_error_t> fallible_function10()
{
  auto result_a = non_trivial_destructor::initialize(10);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(10);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function11(); result) {
    side_effect = side_effect + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect;
}

tl::expected<int, my_error_t> fallible_function12();

tl::expected<int, my_error_t> fallible_function11()
{
  auto result_a = non_trivial_destructor::initialize(11);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(11);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function12(); result) {
    side_effect = side_effect + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect;
}

tl::expected<int, my_error_t> fallible_function13();

tl::expected<int, my_error_t> fallible_function12()
{
  auto result_a = non_trivial_destructor::initialize(12);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(12);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function13(); result) {
    side_effect = side_effect + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect;
}

tl::expected<int, my_error_t> fallible_function14();

tl::expected<int, my_error_t> fallible_function13()
{
  auto result_a = non_trivial_destructor::initialize(13);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(13);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function14(); result) {
    side_effect = side_effect + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect;
}

tl::expected<int, my_error_t> fallible_function15();

tl::expected<int, my_error_t> fallible_function14()
{
  auto result_a = non_trivial_destructor::initialize(14);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(14);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function15(); result) {
    side_effect = side_effect + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect;
}

tl::expected<int, my_error_t> fallible_function16();

tl::expected<int, my_error_t> fallible_function15()
{
  auto result_a = non_trivial_destructor::initialize(15);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(15);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function16(); result) {
    side_effect = side_effect + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect;
}

tl::expected<int, my_error_t> fallible_function17();

tl::expected<int, my_error_t> fallible_function16()
{
  auto result_a = non_trivial_destructor::initialize(16);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(16);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function17(); result) {
    side_effect = side_effect + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect;
}

tl::expected<int, my_error_t> fallible_function18();

tl::expected<int, my_error_t> fallible_function17()
{
  auto result_a = non_trivial_destructor::initialize(17);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(17);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function18(); result) {
    side_effect = side_effect + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect;
}

tl::expected<int, my_error_t> fallible_function19();

tl::expected<int, my_error_t> fallible_function18()
{
  auto result_a = non_trivial_destructor::initialize(18);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(18);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function19(); result) {
    side_effect = side_effect + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect;
}

tl::expected<int, my_error_t> fallible_function20();

tl::expected<int, my_error_t> fallible_function19()
{
  auto result_a = non_trivial_destructor::initialize(19);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(19);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function20(); result) {
    side_effect = side_effect + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect;
}

tl::expected<int, my_error_t> fallible_function21();

tl::expected<int, my_error_t> fallible_function20()
{
  auto result_a = non_trivial_destructor::initialize(20);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(20);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function21(); result) {
    side_effect = side_effect + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect;
}

tl::expected<int, my_error_t> fallible_function22();

tl::expected<int, my_error_t> fallible_function21()
{
  auto result_a = non_trivial_destructor::initialize(21);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(21);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function22(); result) {
    side_effect = side_effect + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect;
}

tl::expected<int, my_error_t> fallible_function23();

tl::expected<int, my_error_t> fallible_function22()
{
  auto result_a = non_trivial_destructor::initialize(22);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(22);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function23(); result) {
    side_effect = side_effect + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect;
}

tl::expected<int, my_error_t> fallible_function24();

tl::expected<int, my_error_t> fallible_function23()
{
  auto result_a = non_trivial_destructor::initialize(23);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(23);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function24(); result) {
    side_effect = side_effect + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect;
}

tl::expected<int, my_error_t> fallible_function25();

tl::expected<int, my_error_t> fallible_function24()
{
  auto result_a = non_trivial_destructor::initialize(24);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(24);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function25(); result) {
    side_effect = side_effect + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect;
}

tl::expected<int, my_error_t> fallible_function26();

tl::expected<int, my_error_t> fallible_function25()
{
  auto result_a = non_trivial_destructor::initialize(25);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(25);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function26(); result) {
    side_effect = side_effect + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect;
}

tl::expected<int, my_error_t> fallible_function27();

tl::expected<int, my_error_t> fallible_function26()
{
  auto result_a = non_trivial_destructor::initialize(26);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(26);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function27(); result) {
    side_effect = side_effect + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect;
}

tl::expected<int, my_error_t> fallible_function28();

tl::expected<int, my_error_t> fallible_function27()
{
  auto result_a = non_trivial_destructor::initialize(27);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(27);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function28(); result) {
    side_effect = side_effect + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect;
}

tl::expected<int, my_error_t> fallible_function29();

tl::expected<int, my_error_t> fallible_function28()
{
  auto result_a = non_trivial_destructor::initialize(28);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(28);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function29(); result) {
    side_effect = side_effect + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect;
}

tl::expected<int, my_error_t> fallible_function30();

tl::expected<int, my_error_t> fallible_function29()
{
  auto result_a = non_trivial_destructor::initialize(29);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(29);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function30(); result) {
    side_effect = side_effect + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect;
}

tl::expected<int, my_error_t> fallible_function31();

tl::expected<int, my_error_t> fallible_function30()
{
  auto result_a = non_trivial_destructor::initialize(30);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(30);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function31(); result) {
    side_effect = side_effect + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect;
}

tl::expected<int, my_error_t> fallible_function32();

tl::expected<int, my_error_t> fallible_function31()
{
  auto result_a = non_trivial_destructor::initialize(31);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(31);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function32(); result) {
    side_effect = side_effect + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect;
}

tl::expected<int, my_error_t> fallible_function33();

tl::expected<int, my_error_t> fallible_function32()
{
  auto result_a = non_trivial_destructor::initialize(32);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(32);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function33(); result) {
    side_effect = side_effect + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect;
}

tl::expected<int, my_error_t> fallible_function34();

tl::expected<int, my_error_t> fallible_function33()
{
  auto result_a = non_trivial_destructor::initialize(33);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(33);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function34(); result) {
    side_effect = side_effect + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect;
}

tl::expected<int, my_error_t> fallible_function35();

tl::expected<int, my_error_t> fallible_function34()
{
  auto result_a = non_trivial_destructor::initialize(34);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(34);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function35(); result) {
    side_effect = side_effect + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect;
}

tl::expected<int, my_error_t> fallible_function36();

tl::expected<int, my_error_t> fallible_function35()
{
  auto result_a = non_trivial_destructor::initialize(35);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(35);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function36(); result) {
    side_effect = side_effect + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect;
}

tl::expected<int, my_error_t> fallible_function37();

tl::expected<int, my_error_t> fallible_function36()
{
  auto result_a = non_trivial_destructor::initialize(36);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(36);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function37(); result) {
    side_effect = side_effect + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect;
}

tl::expected<int, my_error_t> fallible_function38();

tl::expected<int, my_error_t> fallible_function37()
{
  auto result_a = non_trivial_destructor::initialize(37);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(37);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function38(); result) {
    side_effect = side_effect + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect;
}

tl::expected<int, my_error_t> fallible_function39();

tl::expected<int, my_error_t> fallible_function38()
{
  auto result_a = non_trivial_destructor::initialize(38);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(38);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function39(); result) {
    side_effect = side_effect + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect;
}

tl::expected<int, my_error_t> fallible_function40();

tl::expected<int, my_error_t> fallible_function39()
{
  auto result_a = non_trivial_destructor::initialize(39);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(39);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function40(); result) {
    side_effect = side_effect + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect;
}

tl::expected<int, my_error_t> fallible_function41();

tl::expected<int, my_error_t> fallible_function40()
{
  auto result_a = non_trivial_destructor::initialize(40);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(40);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function41(); result) {
    side_effect = side_effect + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect;
}

tl::expected<int, my_error_t> fallible_function42();

tl::expected<int, my_error_t> fallible_function41()
{
  auto result_a = non_trivial_destructor::initialize(41);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(41);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function42(); result) {
    side_effect = side_effect + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect;
}

tl::expected<int, my_error_t> fallible_function43();

tl::expected<int, my_error_t> fallible_function42()
{
  auto result_a = non_trivial_destructor::initialize(42);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(42);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function43(); result) {
    side_effect = side_effect + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect;
}

tl::expected<int, my_error_t> fallible_function44();

tl::expected<int, my_error_t> fallible_function43()
{
  auto result_a = non_trivial_destructor::initialize(43);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(43);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function44(); result) {
    side_effect = side_effect + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect;
}

tl::expected<int, my_error_t> fallible_function45();

tl::expected<int, my_error_t> fallible_function44()
{
  auto result_a = non_trivial_destructor::initialize(44);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(44);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function45(); result) {
    side_effect = side_effect + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect;
}

tl::expected<int, my_error_t> fallible_function46();

tl::expected<int, my_error_t> fallible_function45()
{
  auto result_a = non_trivial_destructor::initialize(45);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(45);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function46(); result) {
    side_effect = side_effect + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect;
}

tl::expected<int, my_error_t> fallible_function47();

tl::expected<int, my_error_t> fallible_function46()
{
  auto result_a = non_trivial_destructor::initialize(46);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(46);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function47(); result) {
    side_effect = side_effect + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect;
}

tl::expected<int, my_error_t> fallible_function48();

tl::expected<int, my_error_t> fallible_function47()
{
  auto result_a = non_trivial_destructor::initialize(47);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(47);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function48(); result) {
    side_effect = side_effect + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect;
}

tl::expected<int, my_error_t> fallible_function49();

tl::expected<int, my_error_t> fallible_function48()
{
  auto result_a = non_trivial_destructor::initialize(48);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(48);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function49(); result) {
    side_effect = side_effect + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect;
}

tl::expected<int, my_error_t> fallible_function50();

tl::expected<int, my_error_t> fallible_function49()
{
  auto result_a = non_trivial_destructor::initialize(49);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(49);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function50(); result) {
    side_effect = side_effect + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect;
}

tl::expected<int, my_error_t> fallible_function51();

tl::expected<int, my_error_t> fallible_function50()
{
  auto result_a = non_trivial_destructor::initialize(50);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(50);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function51(); result) {
    side_effect = side_effect + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect;
}

tl::expected<int, my_error_t> fallible_function52();

tl::expected<int, my_error_t> fallible_function51()
{
  auto result_a = non_trivial_destructor::initialize(51);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(51);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function52(); result) {
    side_effect = side_effect + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect;
}

tl::expected<int, my_error_t> fallible_function53();

tl::expected<int, my_error_t> fallible_function52()
{
  auto result_a = non_trivial_destructor::initialize(52);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(52);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function53(); result) {
    side_effect = side_effect + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect;
}

tl::expected<int, my_error_t> fallible_function54();

tl::expected<int, my_error_t> fallible_function53()
{
  auto result_a = non_trivial_destructor::initialize(53);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(53);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function54(); result) {
    side_effect = side_effect + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect;
}

tl::expected<int, my_error_t> fallible_function55();

tl::expected<int, my_error_t> fallible_function54()
{
  auto result_a = non_trivial_destructor::initialize(54);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(54);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function55(); result) {
    side_effect = side_effect + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect;
}

tl::expected<int, my_error_t> fallible_function56();

tl::expected<int, my_error_t> fallible_function55()
{
  auto result_a = non_trivial_destructor::initialize(55);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(55);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function56(); result) {
    side_effect = side_effect + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect;
}

tl::expected<int, my_error_t> fallible_function57();

tl::expected<int, my_error_t> fallible_function56()
{
  auto result_a = non_trivial_destructor::initialize(56);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(56);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function57(); result) {
    side_effect = side_effect + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect;
}

tl::expected<int, my_error_t> fallible_function58();

tl::expected<int, my_error_t> fallible_function57()
{
  auto result_a = non_trivial_destructor::initialize(57);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(57);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function58(); result) {
    side_effect = side_effect + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect;
}

tl::expected<int, my_error_t> fallible_function59();

tl::expected<int, my_error_t> fallible_function58()
{
  auto result_a = non_trivial_destructor::initialize(58);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(58);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function59(); result) {
    side_effect = side_effect + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect;
}

tl::expected<int, my_error_t> fallible_function60();

tl::expected<int, my_error_t> fallible_function59()
{
  auto result_a = non_trivial_destructor::initialize(59);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(59);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function60(); result) {
    side_effect = side_effect + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect;
}

tl::expected<int, my_error_t> fallible_function61();

tl::expected<int, my_error_t> fallible_function60()
{
  auto result_a = non_trivial_destructor::initialize(60);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(60);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function61(); result) {
    side_effect = side_effect + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect;
}

tl::expected<int, my_error_t> fallible_function62();

tl::expected<int, my_error_t> fallible_function61()
{
  auto result_a = non_trivial_destructor::initialize(61);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(61);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function62(); result) {
    side_effect = side_effect + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect;
}

tl::expected<int, my_error_t> fallible_function63();

tl::expected<int, my_error_t> fallible_function62()
{
  auto result_a = non_trivial_destructor::initialize(62);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(62);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function63(); result) {
    side_effect = side_effect + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect;
}

tl::expected<int, my_error_t> fallible_function64();

tl::expected<int, my_error_t> fallible_function63()
{
  auto result_a = non_trivial_destructor::initialize(63);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(63);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function64(); result) {
    side_effect = side_effect + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect;
}

tl::expected<int, my_error_t> fallible_function65();

tl::expected<int, my_error_t> fallible_function64()
{
  auto result_a = non_trivial_destructor::initialize(64);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(64);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function65(); result) {
    side_effect = side_effect + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect;
}

tl::expected<int, my_error_t> fallible_function66();

tl::expected<int, my_error_t> fallible_function65()
{
  auto result_a = non_trivial_destructor::initialize(65);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(65);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function66(); result) {
    side_effect = side_effect + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect;
}

tl::expected<int, my_error_t> fallible_function67();

tl::expected<int, my_error_t> fallible_function66()
{
  auto result_a = non_trivial_destructor::initialize(66);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(66);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function67(); result) {
    side_effect = side_effect + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect;
}

tl::expected<int, my_error_t> fallible_function68();

tl::expected<int, my_error_t> fallible_function67()
{
  auto result_a = non_trivial_destructor::initialize(67);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(67);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function68(); result) {
    side_effect = side_effect + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect;
}

tl::expected<int, my_error_t> fallible_function69();

tl::expected<int, my_error_t> fallible_function68()
{
  auto result_a = non_trivial_destructor::initialize(68);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(68);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function69(); result) {
    side_effect = side_effect + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect;
}

tl::expected<int, my_error_t> fallible_function70();

tl::expected<int, my_error_t> fallible_function69()
{
  auto result_a = non_trivial_destructor::initialize(69);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(69);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function70(); result) {
    side_effect = side_effect + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect;
}

tl::expected<int, my_error_t> fallible_function71();

tl::expected<int, my_error_t> fallible_function70()
{
  auto result_a = non_trivial_destructor::initialize(70);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(70);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function71(); result) {
    side_effect = side_effect + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect;
}

tl::expected<int, my_error_t> fallible_function72();

tl::expected<int, my_error_t> fallible_function71()
{
  auto result_a = non_trivial_destructor::initialize(71);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(71);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function72(); result) {
    side_effect = side_effect + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect;
}

tl::expected<int, my_error_t> fallible_function73();

tl::expected<int, my_error_t> fallible_function72()
{
  auto result_a = non_trivial_destructor::initialize(72);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(72);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function73(); result) {
    side_effect = side_effect + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect;
}

tl::expected<int, my_error_t> fallible_function74();

tl::expected<int, my_error_t> fallible_function73()
{
  auto result_a = non_trivial_destructor::initialize(73);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(73);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function74(); result) {
    side_effect = side_effect + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect;
}

tl::expected<int, my_error_t> fallible_function75();

tl::expected<int, my_error_t> fallible_function74()
{
  auto result_a = non_trivial_destructor::initialize(74);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(74);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function75(); result) {
    side_effect = side_effect + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect;
}

tl::expected<int, my_error_t> fallible_function76();

tl::expected<int, my_error_t> fallible_function75()
{
  auto result_a = non_trivial_destructor::initialize(75);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(75);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function76(); result) {
    side_effect = side_effect + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect;
}

tl::expected<int, my_error_t> fallible_function77();

tl::expected<int, my_error_t> fallible_function76()
{
  auto result_a = non_trivial_destructor::initialize(76);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(76);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function77(); result) {
    side_effect = side_effect + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect;
}

tl::expected<int, my_error_t> fallible_function78();

tl::expected<int, my_error_t> fallible_function77()
{
  auto result_a = non_trivial_destructor::initialize(77);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(77);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function78(); result) {
    side_effect = side_effect + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect;
}

tl::expected<int, my_error_t> fallible_function79();

tl::expected<int, my_error_t> fallible_function78()
{
  auto result_a = non_trivial_destructor::initialize(78);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(78);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function79(); result) {
    side_effect = side_effect + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect;
}

tl::expected<int, my_error_t> fallible_function80();

tl::expected<int, my_error_t> fallible_function79()
{
  auto result_a = non_trivial_destructor::initialize(79);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(79);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function80(); result) {
    side_effect = side_effect + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect;
}

tl::expected<int, my_error_t> fallible_function81();

tl::expected<int, my_error_t> fallible_function80()
{
  auto result_a = non_trivial_destructor::initialize(80);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(80);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function81(); result) {
    side_effect = side_effect + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect;
}

tl::expected<int, my_error_t> fallible_function82();

tl::expected<int, my_error_t> fallible_function81()
{
  auto result_a = non_trivial_destructor::initialize(81);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(81);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function82(); result) {
    side_effect = side_effect + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect;
}

tl::expected<int, my_error_t> fallible_function83();

tl::expected<int, my_error_t> fallible_function82()
{
  auto result_a = non_trivial_destructor::initialize(82);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(82);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function83(); result) {
    side_effect = side_effect + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect;
}

tl::expected<int, my_error_t> fallible_function84();

tl::expected<int, my_error_t> fallible_function83()
{
  auto result_a = non_trivial_destructor::initialize(83);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(83);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function84(); result) {
    side_effect = side_effect + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect;
}

tl::expected<int, my_error_t> fallible_function85();

tl::expected<int, my_error_t> fallible_function84()
{
  auto result_a = non_trivial_destructor::initialize(84);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(84);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function85(); result) {
    side_effect = side_effect + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect;
}

tl::expected<int, my_error_t> fallible_function86();

tl::expected<int, my_error_t> fallible_function85()
{
  auto result_a = non_trivial_destructor::initialize(85);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(85);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function86(); result) {
    side_effect = side_effect + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect;
}

tl::expected<int, my_error_t> fallible_function87();

tl::expected<int, my_error_t> fallible_function86()
{
  auto result_a = non_trivial_destructor::initialize(86);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(86);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function87(); result) {
    side_effect = side_effect + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect;
}

tl::expected<int, my_error_t> fallible_function88();

tl::expected<int, my_error_t> fallible_function87()
{
  auto result_a = non_trivial_destructor::initialize(87);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(87);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function88(); result) {
    side_effect = side_effect + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect;
}

tl::expected<int, my_error_t> fallible_function89();

tl::expected<int, my_error_t> fallible_function88()
{
  auto result_a = non_trivial_destructor::initialize(88);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(88);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function89(); result) {
    side_effect = side_effect + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect;
}

tl::expected<int, my_error_t> fallible_function90();

tl::expected<int, my_error_t> fallible_function89()
{
  auto result_a = non_trivial_destructor::initialize(89);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(89);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function90(); result) {
    side_effect = side_effect + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect;
}

tl::expected<int, my_error_t> fallible_function91();

tl::expected<int, my_error_t> fallible_function90()
{
  auto result_a = non_trivial_destructor::initialize(90);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(90);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function91(); result) {
    side_effect = side_effect + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect;
}

tl::expected<int, my_error_t> fallible_function92();

tl::expected<int, my_error_t> fallible_function91()
{
  auto result_a = non_trivial_destructor::initialize(91);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(91);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function92(); result) {
    side_effect = side_effect + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect;
}

tl::expected<int, my_error_t> fallible_function93();

tl::expected<int, my_error_t> fallible_function92()
{
  auto result_a = non_trivial_destructor::initialize(92);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(92);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function93(); result) {
    side_effect = side_effect + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect;
}

tl::expected<int, my_error_t> fallible_function94();

tl::expected<int, my_error_t> fallible_function93()
{
  auto result_a = non_trivial_destructor::initialize(93);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(93);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function94(); result) {
    side_effect = side_effect + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect;
}

tl::expected<int, my_error_t> fallible_function95();

tl::expected<int, my_error_t> fallible_function94()
{
  auto result_a = non_trivial_destructor::initialize(94);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(94);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function95(); result) {
    side_effect = side_effect + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect;
}

tl::expected<int, my_error_t> fallible_function96();

tl::expected<int, my_error_t> fallible_function95()
{
  auto result_a = non_trivial_destructor::initialize(95);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(95);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function96(); result) {
    side_effect = side_effect + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect;
}

tl::expected<int, my_error_t> fallible_function97();

tl::expected<int, my_error_t> fallible_function96()
{
  auto result_a = non_trivial_destructor::initialize(96);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(96);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function97(); result) {
    side_effect = side_effect + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect;
}

tl::expected<int, my_error_t> fallible_function98();

tl::expected<int, my_error_t> fallible_function97()
{
  auto result_a = non_trivial_destructor::initialize(97);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(97);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function98(); result) {
    side_effect = side_effect + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect;
}

tl::expected<int, my_error_t> fallible_function99();

tl::expected<int, my_error_t> fallible_function98()
{
  auto result_a = non_trivial_destructor::initialize(98);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(98);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function99(); result) {
    side_effect = side_effect + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect;
}

tl::expected<int, my_error_t> fallible_function100();

tl::expected<int, my_error_t> fallible_function99()
{
  auto result_a = non_trivial_destructor::initialize(99);

  if (result_a) {
    auto result_internal = result_a.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_a.error());
  }

  auto result_b = non_trivial_destructor::initialize(99);

  if (result_b) {
    auto result_internal = result_b.value().trigger();
    if (!result_internal) {
      return tl::unexpected(result_internal.error());
    }
  } else {
    return tl::unexpected(result_b.error());
  }

  if (auto result = fallible_function100(); result) {
    side_effect = side_effect + result.value();
  } else {
    return tl::unexpected(result.error());
  }

  return side_effect;
}

tl::expected<int, my_error_t> fallible_function100()
{
  side_effect = side_effect + 1;
  if (side_effect >= 1) {
    start = my_clock->uptime().ticks;
    return tl::unexpected(my_error_t{ .data = { 0x55, 0xAA, 0x33, 0x44 } });
  }
  return side_effect + 1;
}
