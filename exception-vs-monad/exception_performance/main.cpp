
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

  // ~non_trivial_destructor()
  // {
  //   enable_register = enable_register & ~(1 << (m_channel % 64));
  // }

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

int fallible_function1();
int fallible_function0()
{
  auto result = non_trivial_destructor(0);
  result.trigger();
  auto result2 = non_trivial_destructor(0 * 2);
  result2.trigger();
  side_effect = side_effect + 1;
  side_effect = side_effect + fallible_function1();
  return side_effect;
}

int fallible_function2();
int fallible_function1()
{
  auto result = non_trivial_destructor(1);
  result.trigger();
  auto result2 = non_trivial_destructor(1 * 2);
  result2.trigger();
  side_effect = side_effect + fallible_function2();
  return side_effect;
}

int fallible_function3();
int fallible_function2()
{
  auto result = non_trivial_destructor(2);
  result.trigger();
  auto result2 = non_trivial_destructor(2 * 2);
  result2.trigger();
  side_effect = side_effect + fallible_function3();
  return side_effect;
}

int fallible_function4();
int fallible_function3()
{
  auto result = non_trivial_destructor(3);
  result.trigger();
  auto result2 = non_trivial_destructor(3 * 2);
  result2.trigger();
  side_effect = side_effect + fallible_function4();
  return side_effect;
}

int fallible_function5();
int fallible_function4()
{
  auto result = non_trivial_destructor(4);
  result.trigger();
  auto result2 = non_trivial_destructor(4 * 2);
  result2.trigger();
  side_effect = side_effect + fallible_function5();
  return side_effect;
}

int fallible_function6();
int fallible_function5()
{
  auto result = non_trivial_destructor(5);
  result.trigger();
  auto result2 = non_trivial_destructor(5 * 2);
  result2.trigger();
  side_effect = side_effect + fallible_function6();
  return side_effect;
}

int fallible_function7();
int fallible_function6()
{
  auto result = non_trivial_destructor(6);
  result.trigger();
  auto result2 = non_trivial_destructor(6 * 2);
  result2.trigger();
  side_effect = side_effect + fallible_function7();
  return side_effect;
}

int fallible_function8();
int fallible_function7()
{
  auto result = non_trivial_destructor(7);
  result.trigger();
  auto result2 = non_trivial_destructor(7 * 2);
  result2.trigger();
  side_effect = side_effect + fallible_function8();
  return side_effect;
}

int fallible_function9();
int fallible_function8()
{
  auto result = non_trivial_destructor(8);
  result.trigger();
  auto result2 = non_trivial_destructor(8 * 2);
  result2.trigger();
  side_effect = side_effect + fallible_function9();
  return side_effect;
}

int fallible_function10();
int fallible_function9()
{
  auto result = non_trivial_destructor(9);
  result.trigger();
  auto result2 = non_trivial_destructor(9 * 2);
  result2.trigger();
  side_effect = side_effect + fallible_function10();
  return side_effect;
}

int fallible_function11();
int fallible_function10()
{
  auto result = non_trivial_destructor(10);
  result.trigger();
  auto result2 = non_trivial_destructor(10 * 2);
  result2.trigger();
  side_effect = side_effect + fallible_function11();
  return side_effect;
}

int fallible_function12();
int fallible_function11()
{
  auto result = non_trivial_destructor(11);
  result.trigger();
  auto result2 = non_trivial_destructor(11 * 2);
  result2.trigger();
  side_effect = side_effect + fallible_function12();
  return side_effect;
}

int fallible_function13();
int fallible_function12()
{
  auto result = non_trivial_destructor(12);
  result.trigger();
  auto result2 = non_trivial_destructor(12 * 2);
  result2.trigger();
  side_effect = side_effect + fallible_function13();
  return side_effect;
}

int fallible_function14();
int fallible_function13()
{
  auto result = non_trivial_destructor(13);
  result.trigger();
  auto result2 = non_trivial_destructor(13 * 2);
  result2.trigger();
  side_effect = side_effect + fallible_function14();
  return side_effect;
}

int fallible_function15();
int fallible_function14()
{
  auto result = non_trivial_destructor(14);
  result.trigger();
  auto result2 = non_trivial_destructor(14 * 2);
  result2.trigger();
  side_effect = side_effect + fallible_function15();
  return side_effect;
}

int fallible_function16();
int fallible_function15()
{
  auto result = non_trivial_destructor(15);
  result.trigger();
  auto result2 = non_trivial_destructor(15 * 2);
  result2.trigger();
  side_effect = side_effect + fallible_function16();
  return side_effect;
}

int fallible_function17();
int fallible_function16()
{
  auto result = non_trivial_destructor(16);
  result.trigger();
  auto result2 = non_trivial_destructor(16 * 2);
  result2.trigger();
  side_effect = side_effect + fallible_function17();
  return side_effect;
}

int fallible_function18();
int fallible_function17()
{
  auto result = non_trivial_destructor(17);
  result.trigger();
  auto result2 = non_trivial_destructor(17 * 2);
  result2.trigger();
  side_effect = side_effect + fallible_function18();
  return side_effect;
}

int fallible_function19();
int fallible_function18()
{
  auto result = non_trivial_destructor(18);
  result.trigger();
  auto result2 = non_trivial_destructor(18 * 2);
  result2.trigger();
  side_effect = side_effect + fallible_function19();
  return side_effect;
}

int fallible_function20();
int fallible_function19()
{
  auto result = non_trivial_destructor(19);
  result.trigger();
  auto result2 = non_trivial_destructor(19 * 2);
  result2.trigger();
  side_effect = side_effect + fallible_function20();
  return side_effect;
}

int fallible_function21();
int fallible_function20()
{
  auto result = non_trivial_destructor(20);
  result.trigger();
  auto result2 = non_trivial_destructor(20 * 2);
  result2.trigger();
  side_effect = side_effect + fallible_function21();
  return side_effect;
}

int fallible_function22();
int fallible_function21()
{
  auto result = non_trivial_destructor(21);
  result.trigger();
  auto result2 = non_trivial_destructor(21 * 2);
  result2.trigger();
  side_effect = side_effect + fallible_function22();
  return side_effect;
}

int fallible_function23();
int fallible_function22()
{
  auto result = non_trivial_destructor(22);
  result.trigger();
  auto result2 = non_trivial_destructor(22 * 2);
  result2.trigger();
  side_effect = side_effect + fallible_function23();
  return side_effect;
}

int fallible_function24();
int fallible_function23()
{
  auto result = non_trivial_destructor(23);
  result.trigger();
  auto result2 = non_trivial_destructor(23 * 2);
  result2.trigger();
  side_effect = side_effect + fallible_function24();
  return side_effect;
}

int fallible_function25();
int fallible_function24()
{
  auto result = non_trivial_destructor(24);
  result.trigger();
  auto result2 = non_trivial_destructor(24 * 2);
  result2.trigger();
  side_effect = side_effect + fallible_function25();
  return side_effect;
}

int fallible_function26();
int fallible_function25()
{
  auto result = non_trivial_destructor(25);
  result.trigger();
  auto result2 = non_trivial_destructor(25 * 2);
  result2.trigger();
  side_effect = side_effect + fallible_function26();
  return side_effect;
}

int fallible_function27();
int fallible_function26()
{
  auto result = non_trivial_destructor(26);
  result.trigger();
  auto result2 = non_trivial_destructor(26 * 2);
  result2.trigger();
  side_effect = side_effect + fallible_function27();
  return side_effect;
}

int fallible_function28();
int fallible_function27()
{
  auto result = non_trivial_destructor(27);
  result.trigger();
  auto result2 = non_trivial_destructor(27 * 2);
  result2.trigger();
  side_effect = side_effect + fallible_function28();
  return side_effect;
}

int fallible_function29();
int fallible_function28()
{
  auto result = non_trivial_destructor(28);
  result.trigger();
  auto result2 = non_trivial_destructor(28 * 2);
  result2.trigger();
  side_effect = side_effect + fallible_function29();
  return side_effect;
}

int fallible_function30();
int fallible_function29()
{
  auto result = non_trivial_destructor(29);
  result.trigger();
  auto result2 = non_trivial_destructor(29 * 2);
  result2.trigger();
  side_effect = side_effect + fallible_function30();
  return side_effect;
}

int fallible_function31();
int fallible_function30()
{
  auto result = non_trivial_destructor(30);
  result.trigger();
  auto result2 = non_trivial_destructor(30 * 2);
  result2.trigger();
  side_effect = side_effect + fallible_function31();
  return side_effect;
}

int fallible_function32();
int fallible_function31()
{
  auto result = non_trivial_destructor(31);
  result.trigger();
  auto result2 = non_trivial_destructor(31 * 2);
  result2.trigger();
  side_effect = side_effect + fallible_function32();
  return side_effect;
}

int fallible_function33();
int fallible_function32()
{
  auto result = non_trivial_destructor(32);
  result.trigger();
  auto result2 = non_trivial_destructor(32 * 2);
  result2.trigger();
  side_effect = side_effect + fallible_function33();
  return side_effect;
}

int fallible_function34();
int fallible_function33()
{
  auto result = non_trivial_destructor(33);
  result.trigger();
  auto result2 = non_trivial_destructor(33 * 2);
  result2.trigger();
  side_effect = side_effect + fallible_function34();
  return side_effect;
}

int fallible_function35();
int fallible_function34()
{
  auto result = non_trivial_destructor(34);
  result.trigger();
  auto result2 = non_trivial_destructor(34 * 2);
  result2.trigger();
  side_effect = side_effect + fallible_function35();
  return side_effect;
}

int fallible_function36();
int fallible_function35()
{
  auto result = non_trivial_destructor(35);
  result.trigger();
  auto result2 = non_trivial_destructor(35 * 2);
  result2.trigger();
  side_effect = side_effect + fallible_function36();
  return side_effect;
}

int fallible_function37();
int fallible_function36()
{
  auto result = non_trivial_destructor(36);
  result.trigger();
  auto result2 = non_trivial_destructor(36 * 2);
  result2.trigger();
  side_effect = side_effect + fallible_function37();
  return side_effect;
}

int fallible_function38();
int fallible_function37()
{
  auto result = non_trivial_destructor(37);
  result.trigger();
  auto result2 = non_trivial_destructor(37 * 2);
  result2.trigger();
  side_effect = side_effect + fallible_function38();
  return side_effect;
}

int fallible_function39();
int fallible_function38()
{
  auto result = non_trivial_destructor(38);
  result.trigger();
  auto result2 = non_trivial_destructor(38 * 2);
  result2.trigger();
  side_effect = side_effect + fallible_function39();
  return side_effect;
}

int fallible_function40();
int fallible_function39()
{
  auto result = non_trivial_destructor(39);
  result.trigger();
  auto result2 = non_trivial_destructor(39 * 2);
  result2.trigger();
  side_effect = side_effect + fallible_function40();
  return side_effect;
}

int fallible_function41();
int fallible_function40()
{
  auto result = non_trivial_destructor(40);
  result.trigger();
  auto result2 = non_trivial_destructor(40 * 2);
  result2.trigger();
  side_effect = side_effect + fallible_function41();
  return side_effect;
}

int fallible_function42();
int fallible_function41()
{
  auto result = non_trivial_destructor(41);
  result.trigger();
  auto result2 = non_trivial_destructor(41 * 2);
  result2.trigger();
  side_effect = side_effect + fallible_function42();
  return side_effect;
}

int fallible_function43();
int fallible_function42()
{
  auto result = non_trivial_destructor(42);
  result.trigger();
  auto result2 = non_trivial_destructor(42 * 2);
  result2.trigger();
  side_effect = side_effect + fallible_function43();
  return side_effect;
}

int fallible_function44();
int fallible_function43()
{
  auto result = non_trivial_destructor(43);
  result.trigger();
  auto result2 = non_trivial_destructor(43 * 2);
  result2.trigger();
  side_effect = side_effect + fallible_function44();
  return side_effect;
}

int fallible_function45();
int fallible_function44()
{
  auto result = non_trivial_destructor(44);
  result.trigger();
  auto result2 = non_trivial_destructor(44 * 2);
  result2.trigger();
  side_effect = side_effect + fallible_function45();
  return side_effect;
}

int fallible_function46();
int fallible_function45()
{
  auto result = non_trivial_destructor(45);
  result.trigger();
  auto result2 = non_trivial_destructor(45 * 2);
  result2.trigger();
  side_effect = side_effect + fallible_function46();
  return side_effect;
}

int fallible_function47();
int fallible_function46()
{
  auto result = non_trivial_destructor(46);
  result.trigger();
  auto result2 = non_trivial_destructor(46 * 2);
  result2.trigger();
  side_effect = side_effect + fallible_function47();
  return side_effect;
}

int fallible_function48();
int fallible_function47()
{
  auto result = non_trivial_destructor(47);
  result.trigger();
  auto result2 = non_trivial_destructor(47 * 2);
  result2.trigger();
  side_effect = side_effect + fallible_function48();
  return side_effect;
}

int fallible_function49();
int fallible_function48()
{
  auto result = non_trivial_destructor(48);
  result.trigger();
  auto result2 = non_trivial_destructor(48 * 2);
  result2.trigger();
  side_effect = side_effect + fallible_function49();
  return side_effect;
}

int fallible_function50();
int fallible_function49()
{
  auto result = non_trivial_destructor(49);
  result.trigger();
  auto result2 = non_trivial_destructor(49 * 2);
  result2.trigger();
  side_effect = side_effect + fallible_function50();
  return side_effect;
}

int fallible_function50()
{
  // This will always be true so long as you have at least one addition to
  // side_effect, but due to it being volatile, it must be read
  side_effect = side_effect + 1;
  if (side_effect >= 1) {
    start = my_clock->uptime().ticks;
    throw my_error_t{ .data = { 0xAA, 0xBB, 0x33, 0x44 } };
  }
  return side_effect;
}
