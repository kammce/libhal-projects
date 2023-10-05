
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


int fallible_function0_group0();
volatile int side_effect0 = 0;

int fallible_function0_group1();
volatile int side_effect1 = 0;

int fallible_function0_group2();
volatile int side_effect2 = 0;

int fallible_function0_group3();
volatile int side_effect3 = 0;

int fallible_function0_group4();
volatile int side_effect4 = 0;

int fallible_function0_group5();
volatile int side_effect5 = 0;

int fallible_function0_group6();
volatile int side_effect6 = 0;

int fallible_function0_group7();
volatile int side_effect7 = 0;

int fallible_function0_group8();
volatile int side_effect8 = 0;

int fallible_function0_group9();
volatile int side_effect9 = 0;

int return_error()
{
fallible_function0_group0();
fallible_function0_group1();
fallible_function0_group2();
fallible_function0_group3();
fallible_function0_group4();
fallible_function0_group5();
fallible_function0_group6();
fallible_function0_group7();
fallible_function0_group8();
fallible_function0_group9();
  return side_effect0+side_effect1+side_effect2+side_effect3+side_effect4+side_effect5+side_effect6+side_effect7+side_effect8+side_effect9;
}


int fallible_function1_group0();
int fallible_function0_group0()
{
  auto result = non_trivial_destructor(0 * 0);
  result.trigger();
  auto result2 = non_trivial_destructor(0 * 0 * 2);
  result2.trigger();
  side_effect0 = side_effect0 +
    fallible_function1_group0();
  return side_effect0;
}

int fallible_function2_group0();
int fallible_function1_group0()
{
  auto result = non_trivial_destructor(1 * 1);
  result.trigger();
  auto result2 = non_trivial_destructor(1 * 1 * 2);
  result2.trigger();
  side_effect0 = side_effect0 +
    fallible_function2_group0();
  return side_effect0;
}

int fallible_function3_group0();
int fallible_function2_group0()
{
  auto result = non_trivial_destructor(2 * 2);
  result.trigger();
  auto result2 = non_trivial_destructor(2 * 2 * 2);
  result2.trigger();
  side_effect0 = side_effect0 +
    fallible_function3_group0();
  return side_effect0;
}

int fallible_function4_group0();
int fallible_function3_group0()
{
  auto result = non_trivial_destructor(3 * 3);
  result.trigger();
  auto result2 = non_trivial_destructor(3 * 3 * 2);
  result2.trigger();
  side_effect0 = side_effect0 +
    fallible_function4_group0();
  return side_effect0;
}

int fallible_function5_group0();
int fallible_function4_group0()
{
  auto result = non_trivial_destructor(4 * 4);
  result.trigger();
  auto result2 = non_trivial_destructor(4 * 4 * 2);
  result2.trigger();
  side_effect0 = side_effect0 +
    fallible_function5_group0();
  return side_effect0;
}

int fallible_function6_group0();
int fallible_function5_group0()
{
  auto result = non_trivial_destructor(5 * 5);
  result.trigger();
  auto result2 = non_trivial_destructor(5 * 5 * 2);
  result2.trigger();
  side_effect0 = side_effect0 +
    fallible_function6_group0();
  return side_effect0;
}

int fallible_function7_group0();
int fallible_function6_group0()
{
  auto result = non_trivial_destructor(6 * 6);
  result.trigger();
  auto result2 = non_trivial_destructor(6 * 6 * 2);
  result2.trigger();
  side_effect0 = side_effect0 +
    fallible_function7_group0();
  return side_effect0;
}

int fallible_function8_group0();
int fallible_function7_group0()
{
  auto result = non_trivial_destructor(7 * 7);
  result.trigger();
  auto result2 = non_trivial_destructor(7 * 7 * 2);
  result2.trigger();
  side_effect0 = side_effect0 +
    fallible_function8_group0();
  return side_effect0;
}

int fallible_function9_group0();
int fallible_function8_group0()
{
  auto result = non_trivial_destructor(8 * 8);
  result.trigger();
  auto result2 = non_trivial_destructor(8 * 8 * 2);
  result2.trigger();
  side_effect0 = side_effect0 +
    fallible_function9_group0();
  return side_effect0;
}

int fallible_function10_group0();
int fallible_function9_group0()
{
  auto result = non_trivial_destructor(9 * 9);
  result.trigger();
  auto result2 = non_trivial_destructor(9 * 9 * 2);
  result2.trigger();
  side_effect0 = side_effect0 +
    fallible_function10_group0();
  return side_effect0;
}

int fallible_function11_group0();
int fallible_function10_group0()
{
  auto result = non_trivial_destructor(10 * 10);
  result.trigger();
  auto result2 = non_trivial_destructor(10 * 10 * 2);
  result2.trigger();
  side_effect0 = side_effect0 +
    fallible_function11_group0();
  return side_effect0;
}

int fallible_function12_group0();
int fallible_function11_group0()
{
  auto result = non_trivial_destructor(11 * 11);
  result.trigger();
  auto result2 = non_trivial_destructor(11 * 11 * 2);
  result2.trigger();
  side_effect0 = side_effect0 +
    fallible_function12_group0();
  return side_effect0;
}

int fallible_function13_group0();
int fallible_function12_group0()
{
  auto result = non_trivial_destructor(12 * 12);
  result.trigger();
  auto result2 = non_trivial_destructor(12 * 12 * 2);
  result2.trigger();
  side_effect0 = side_effect0 +
    fallible_function13_group0();
  return side_effect0;
}

int fallible_function14_group0();
int fallible_function13_group0()
{
  auto result = non_trivial_destructor(13 * 13);
  result.trigger();
  auto result2 = non_trivial_destructor(13 * 13 * 2);
  result2.trigger();
  side_effect0 = side_effect0 +
    fallible_function14_group0();
  return side_effect0;
}

int fallible_function15_group0();
int fallible_function14_group0()
{
  auto result = non_trivial_destructor(14 * 14);
  result.trigger();
  auto result2 = non_trivial_destructor(14 * 14 * 2);
  result2.trigger();
  side_effect0 = side_effect0 +
    fallible_function15_group0();
  return side_effect0;
}

int fallible_function15_group0()
{
  auto result = non_trivial_destructor(0 * 15);
  result.trigger();
  auto result2 = non_trivial_destructor(0 * 15);
  result2.trigger();
  return side_effect0 + 1;
}

int fallible_function1_group1();
int fallible_function0_group1()
{
  auto result = non_trivial_destructor(0 * 0);
  result.trigger();
  auto result2 = non_trivial_destructor(0 * 0 * 2);
  result2.trigger();
  side_effect1 = side_effect1 +
    fallible_function1_group1();
  return side_effect1;
}

int fallible_function2_group1();
int fallible_function1_group1()
{
  auto result = non_trivial_destructor(1 * 1);
  result.trigger();
  auto result2 = non_trivial_destructor(1 * 1 * 2);
  result2.trigger();
  side_effect1 = side_effect1 +
    fallible_function2_group1();
  return side_effect1;
}

int fallible_function3_group1();
int fallible_function2_group1()
{
  auto result = non_trivial_destructor(2 * 2);
  result.trigger();
  auto result2 = non_trivial_destructor(2 * 2 * 2);
  result2.trigger();
  side_effect1 = side_effect1 +
    fallible_function3_group1();
  return side_effect1;
}

int fallible_function4_group1();
int fallible_function3_group1()
{
  auto result = non_trivial_destructor(3 * 3);
  result.trigger();
  auto result2 = non_trivial_destructor(3 * 3 * 2);
  result2.trigger();
  side_effect1 = side_effect1 +
    fallible_function4_group1();
  return side_effect1;
}

int fallible_function5_group1();
int fallible_function4_group1()
{
  auto result = non_trivial_destructor(4 * 4);
  result.trigger();
  auto result2 = non_trivial_destructor(4 * 4 * 2);
  result2.trigger();
  side_effect1 = side_effect1 +
    fallible_function5_group1();
  return side_effect1;
}

int fallible_function6_group1();
int fallible_function5_group1()
{
  auto result = non_trivial_destructor(5 * 5);
  result.trigger();
  auto result2 = non_trivial_destructor(5 * 5 * 2);
  result2.trigger();
  side_effect1 = side_effect1 +
    fallible_function6_group1();
  return side_effect1;
}

int fallible_function7_group1();
int fallible_function6_group1()
{
  auto result = non_trivial_destructor(6 * 6);
  result.trigger();
  auto result2 = non_trivial_destructor(6 * 6 * 2);
  result2.trigger();
  side_effect1 = side_effect1 +
    fallible_function7_group1();
  return side_effect1;
}

int fallible_function8_group1();
int fallible_function7_group1()
{
  auto result = non_trivial_destructor(7 * 7);
  result.trigger();
  auto result2 = non_trivial_destructor(7 * 7 * 2);
  result2.trigger();
  side_effect1 = side_effect1 +
    fallible_function8_group1();
  return side_effect1;
}

int fallible_function9_group1();
int fallible_function8_group1()
{
  auto result = non_trivial_destructor(8 * 8);
  result.trigger();
  auto result2 = non_trivial_destructor(8 * 8 * 2);
  result2.trigger();
  side_effect1 = side_effect1 +
    fallible_function9_group1();
  return side_effect1;
}

int fallible_function10_group1();
int fallible_function9_group1()
{
  auto result = non_trivial_destructor(9 * 9);
  result.trigger();
  auto result2 = non_trivial_destructor(9 * 9 * 2);
  result2.trigger();
  side_effect1 = side_effect1 +
    fallible_function10_group1();
  return side_effect1;
}

int fallible_function11_group1();
int fallible_function10_group1()
{
  auto result = non_trivial_destructor(10 * 10);
  result.trigger();
  auto result2 = non_trivial_destructor(10 * 10 * 2);
  result2.trigger();
  side_effect1 = side_effect1 +
    fallible_function11_group1();
  return side_effect1;
}

int fallible_function12_group1();
int fallible_function11_group1()
{
  auto result = non_trivial_destructor(11 * 11);
  result.trigger();
  auto result2 = non_trivial_destructor(11 * 11 * 2);
  result2.trigger();
  side_effect1 = side_effect1 +
    fallible_function12_group1();
  return side_effect1;
}

int fallible_function13_group1();
int fallible_function12_group1()
{
  auto result = non_trivial_destructor(12 * 12);
  result.trigger();
  auto result2 = non_trivial_destructor(12 * 12 * 2);
  result2.trigger();
  side_effect1 = side_effect1 +
    fallible_function13_group1();
  return side_effect1;
}

int fallible_function14_group1();
int fallible_function13_group1()
{
  auto result = non_trivial_destructor(13 * 13);
  result.trigger();
  auto result2 = non_trivial_destructor(13 * 13 * 2);
  result2.trigger();
  side_effect1 = side_effect1 +
    fallible_function14_group1();
  return side_effect1;
}

int fallible_function15_group1();
int fallible_function14_group1()
{
  auto result = non_trivial_destructor(14 * 14);
  result.trigger();
  auto result2 = non_trivial_destructor(14 * 14 * 2);
  result2.trigger();
  side_effect1 = side_effect1 +
    fallible_function15_group1();
  return side_effect1;
}

int fallible_function15_group1()
{
  auto result = non_trivial_destructor(1 * 15);
  result.trigger();
  auto result2 = non_trivial_destructor(1 * 15);
  result2.trigger();
  return side_effect1 + 1;
}

int fallible_function1_group2();
int fallible_function0_group2()
{
  auto result = non_trivial_destructor(0 * 0);
  result.trigger();
  auto result2 = non_trivial_destructor(0 * 0 * 2);
  result2.trigger();
  side_effect2 = side_effect2 +
    fallible_function1_group2();
  return side_effect2;
}

int fallible_function2_group2();
int fallible_function1_group2()
{
  auto result = non_trivial_destructor(1 * 1);
  result.trigger();
  auto result2 = non_trivial_destructor(1 * 1 * 2);
  result2.trigger();
  side_effect2 = side_effect2 +
    fallible_function2_group2();
  return side_effect2;
}

int fallible_function3_group2();
int fallible_function2_group2()
{
  auto result = non_trivial_destructor(2 * 2);
  result.trigger();
  auto result2 = non_trivial_destructor(2 * 2 * 2);
  result2.trigger();
  side_effect2 = side_effect2 +
    fallible_function3_group2();
  return side_effect2;
}

int fallible_function4_group2();
int fallible_function3_group2()
{
  auto result = non_trivial_destructor(3 * 3);
  result.trigger();
  auto result2 = non_trivial_destructor(3 * 3 * 2);
  result2.trigger();
  side_effect2 = side_effect2 +
    fallible_function4_group2();
  return side_effect2;
}

int fallible_function5_group2();
int fallible_function4_group2()
{
  auto result = non_trivial_destructor(4 * 4);
  result.trigger();
  auto result2 = non_trivial_destructor(4 * 4 * 2);
  result2.trigger();
  side_effect2 = side_effect2 +
    fallible_function5_group2();
  return side_effect2;
}

int fallible_function6_group2();
int fallible_function5_group2()
{
  auto result = non_trivial_destructor(5 * 5);
  result.trigger();
  auto result2 = non_trivial_destructor(5 * 5 * 2);
  result2.trigger();
  side_effect2 = side_effect2 +
    fallible_function6_group2();
  return side_effect2;
}

int fallible_function7_group2();
int fallible_function6_group2()
{
  auto result = non_trivial_destructor(6 * 6);
  result.trigger();
  auto result2 = non_trivial_destructor(6 * 6 * 2);
  result2.trigger();
  side_effect2 = side_effect2 +
    fallible_function7_group2();
  return side_effect2;
}

int fallible_function8_group2();
int fallible_function7_group2()
{
  auto result = non_trivial_destructor(7 * 7);
  result.trigger();
  auto result2 = non_trivial_destructor(7 * 7 * 2);
  result2.trigger();
  side_effect2 = side_effect2 +
    fallible_function8_group2();
  return side_effect2;
}

int fallible_function9_group2();
int fallible_function8_group2()
{
  auto result = non_trivial_destructor(8 * 8);
  result.trigger();
  auto result2 = non_trivial_destructor(8 * 8 * 2);
  result2.trigger();
  side_effect2 = side_effect2 +
    fallible_function9_group2();
  return side_effect2;
}

int fallible_function10_group2();
int fallible_function9_group2()
{
  auto result = non_trivial_destructor(9 * 9);
  result.trigger();
  auto result2 = non_trivial_destructor(9 * 9 * 2);
  result2.trigger();
  side_effect2 = side_effect2 +
    fallible_function10_group2();
  return side_effect2;
}

int fallible_function11_group2();
int fallible_function10_group2()
{
  auto result = non_trivial_destructor(10 * 10);
  result.trigger();
  auto result2 = non_trivial_destructor(10 * 10 * 2);
  result2.trigger();
  side_effect2 = side_effect2 +
    fallible_function11_group2();
  return side_effect2;
}

int fallible_function12_group2();
int fallible_function11_group2()
{
  auto result = non_trivial_destructor(11 * 11);
  result.trigger();
  auto result2 = non_trivial_destructor(11 * 11 * 2);
  result2.trigger();
  side_effect2 = side_effect2 +
    fallible_function12_group2();
  return side_effect2;
}

int fallible_function13_group2();
int fallible_function12_group2()
{
  auto result = non_trivial_destructor(12 * 12);
  result.trigger();
  auto result2 = non_trivial_destructor(12 * 12 * 2);
  result2.trigger();
  side_effect2 = side_effect2 +
    fallible_function13_group2();
  return side_effect2;
}

int fallible_function14_group2();
int fallible_function13_group2()
{
  auto result = non_trivial_destructor(13 * 13);
  result.trigger();
  auto result2 = non_trivial_destructor(13 * 13 * 2);
  result2.trigger();
  side_effect2 = side_effect2 +
    fallible_function14_group2();
  return side_effect2;
}

int fallible_function15_group2();
int fallible_function14_group2()
{
  auto result = non_trivial_destructor(14 * 14);
  result.trigger();
  auto result2 = non_trivial_destructor(14 * 14 * 2);
  result2.trigger();
  side_effect2 = side_effect2 +
    fallible_function15_group2();
  return side_effect2;
}

int fallible_function15_group2()
{
  auto result = non_trivial_destructor(2 * 15);
  result.trigger();
  auto result2 = non_trivial_destructor(2 * 15);
  result2.trigger();
  return side_effect2 + 1;
}

int fallible_function1_group3();
int fallible_function0_group3()
{
  auto result = non_trivial_destructor(0 * 0);
  result.trigger();
  auto result2 = non_trivial_destructor(0 * 0 * 2);
  result2.trigger();
  side_effect3 = side_effect3 +
    fallible_function1_group3();
  return side_effect3;
}

int fallible_function2_group3();
int fallible_function1_group3()
{
  auto result = non_trivial_destructor(1 * 1);
  result.trigger();
  auto result2 = non_trivial_destructor(1 * 1 * 2);
  result2.trigger();
  side_effect3 = side_effect3 +
    fallible_function2_group3();
  return side_effect3;
}

int fallible_function3_group3();
int fallible_function2_group3()
{
  auto result = non_trivial_destructor(2 * 2);
  result.trigger();
  auto result2 = non_trivial_destructor(2 * 2 * 2);
  result2.trigger();
  side_effect3 = side_effect3 +
    fallible_function3_group3();
  return side_effect3;
}

int fallible_function4_group3();
int fallible_function3_group3()
{
  auto result = non_trivial_destructor(3 * 3);
  result.trigger();
  auto result2 = non_trivial_destructor(3 * 3 * 2);
  result2.trigger();
  side_effect3 = side_effect3 +
    fallible_function4_group3();
  return side_effect3;
}

int fallible_function5_group3();
int fallible_function4_group3()
{
  auto result = non_trivial_destructor(4 * 4);
  result.trigger();
  auto result2 = non_trivial_destructor(4 * 4 * 2);
  result2.trigger();
  side_effect3 = side_effect3 +
    fallible_function5_group3();
  return side_effect3;
}

int fallible_function6_group3();
int fallible_function5_group3()
{
  auto result = non_trivial_destructor(5 * 5);
  result.trigger();
  auto result2 = non_trivial_destructor(5 * 5 * 2);
  result2.trigger();
  side_effect3 = side_effect3 +
    fallible_function6_group3();
  return side_effect3;
}

int fallible_function7_group3();
int fallible_function6_group3()
{
  auto result = non_trivial_destructor(6 * 6);
  result.trigger();
  auto result2 = non_trivial_destructor(6 * 6 * 2);
  result2.trigger();
  side_effect3 = side_effect3 +
    fallible_function7_group3();
  return side_effect3;
}

int fallible_function8_group3();
int fallible_function7_group3()
{
  auto result = non_trivial_destructor(7 * 7);
  result.trigger();
  auto result2 = non_trivial_destructor(7 * 7 * 2);
  result2.trigger();
  side_effect3 = side_effect3 +
    fallible_function8_group3();
  return side_effect3;
}

int fallible_function9_group3();
int fallible_function8_group3()
{
  auto result = non_trivial_destructor(8 * 8);
  result.trigger();
  auto result2 = non_trivial_destructor(8 * 8 * 2);
  result2.trigger();
  side_effect3 = side_effect3 +
    fallible_function9_group3();
  return side_effect3;
}

int fallible_function10_group3();
int fallible_function9_group3()
{
  auto result = non_trivial_destructor(9 * 9);
  result.trigger();
  auto result2 = non_trivial_destructor(9 * 9 * 2);
  result2.trigger();
  side_effect3 = side_effect3 +
    fallible_function10_group3();
  return side_effect3;
}

int fallible_function11_group3();
int fallible_function10_group3()
{
  auto result = non_trivial_destructor(10 * 10);
  result.trigger();
  auto result2 = non_trivial_destructor(10 * 10 * 2);
  result2.trigger();
  side_effect3 = side_effect3 +
    fallible_function11_group3();
  return side_effect3;
}

int fallible_function12_group3();
int fallible_function11_group3()
{
  auto result = non_trivial_destructor(11 * 11);
  result.trigger();
  auto result2 = non_trivial_destructor(11 * 11 * 2);
  result2.trigger();
  side_effect3 = side_effect3 +
    fallible_function12_group3();
  return side_effect3;
}

int fallible_function13_group3();
int fallible_function12_group3()
{
  auto result = non_trivial_destructor(12 * 12);
  result.trigger();
  auto result2 = non_trivial_destructor(12 * 12 * 2);
  result2.trigger();
  side_effect3 = side_effect3 +
    fallible_function13_group3();
  return side_effect3;
}

int fallible_function14_group3();
int fallible_function13_group3()
{
  auto result = non_trivial_destructor(13 * 13);
  result.trigger();
  auto result2 = non_trivial_destructor(13 * 13 * 2);
  result2.trigger();
  side_effect3 = side_effect3 +
    fallible_function14_group3();
  return side_effect3;
}

int fallible_function15_group3();
int fallible_function14_group3()
{
  auto result = non_trivial_destructor(14 * 14);
  result.trigger();
  auto result2 = non_trivial_destructor(14 * 14 * 2);
  result2.trigger();
  side_effect3 = side_effect3 +
    fallible_function15_group3();
  return side_effect3;
}

int fallible_function15_group3()
{
  auto result = non_trivial_destructor(3 * 15);
  result.trigger();
  auto result2 = non_trivial_destructor(3 * 15);
  result2.trigger();
  return side_effect3 + 1;
}

int fallible_function1_group4();
int fallible_function0_group4()
{
  auto result = non_trivial_destructor(0 * 0);
  result.trigger();
  auto result2 = non_trivial_destructor(0 * 0 * 2);
  result2.trigger();
  side_effect4 = side_effect4 +
    fallible_function1_group4();
  return side_effect4;
}

int fallible_function2_group4();
int fallible_function1_group4()
{
  auto result = non_trivial_destructor(1 * 1);
  result.trigger();
  auto result2 = non_trivial_destructor(1 * 1 * 2);
  result2.trigger();
  side_effect4 = side_effect4 +
    fallible_function2_group4();
  return side_effect4;
}

int fallible_function3_group4();
int fallible_function2_group4()
{
  auto result = non_trivial_destructor(2 * 2);
  result.trigger();
  auto result2 = non_trivial_destructor(2 * 2 * 2);
  result2.trigger();
  side_effect4 = side_effect4 +
    fallible_function3_group4();
  return side_effect4;
}

int fallible_function4_group4();
int fallible_function3_group4()
{
  auto result = non_trivial_destructor(3 * 3);
  result.trigger();
  auto result2 = non_trivial_destructor(3 * 3 * 2);
  result2.trigger();
  side_effect4 = side_effect4 +
    fallible_function4_group4();
  return side_effect4;
}

int fallible_function5_group4();
int fallible_function4_group4()
{
  auto result = non_trivial_destructor(4 * 4);
  result.trigger();
  auto result2 = non_trivial_destructor(4 * 4 * 2);
  result2.trigger();
  side_effect4 = side_effect4 +
    fallible_function5_group4();
  return side_effect4;
}

int fallible_function6_group4();
int fallible_function5_group4()
{
  auto result = non_trivial_destructor(5 * 5);
  result.trigger();
  auto result2 = non_trivial_destructor(5 * 5 * 2);
  result2.trigger();
  side_effect4 = side_effect4 +
    fallible_function6_group4();
  return side_effect4;
}

int fallible_function7_group4();
int fallible_function6_group4()
{
  auto result = non_trivial_destructor(6 * 6);
  result.trigger();
  auto result2 = non_trivial_destructor(6 * 6 * 2);
  result2.trigger();
  side_effect4 = side_effect4 +
    fallible_function7_group4();
  return side_effect4;
}

int fallible_function8_group4();
int fallible_function7_group4()
{
  auto result = non_trivial_destructor(7 * 7);
  result.trigger();
  auto result2 = non_trivial_destructor(7 * 7 * 2);
  result2.trigger();
  side_effect4 = side_effect4 +
    fallible_function8_group4();
  return side_effect4;
}

int fallible_function9_group4();
int fallible_function8_group4()
{
  auto result = non_trivial_destructor(8 * 8);
  result.trigger();
  auto result2 = non_trivial_destructor(8 * 8 * 2);
  result2.trigger();
  side_effect4 = side_effect4 +
    fallible_function9_group4();
  return side_effect4;
}

int fallible_function10_group4();
int fallible_function9_group4()
{
  auto result = non_trivial_destructor(9 * 9);
  result.trigger();
  auto result2 = non_trivial_destructor(9 * 9 * 2);
  result2.trigger();
  side_effect4 = side_effect4 +
    fallible_function10_group4();
  return side_effect4;
}

int fallible_function11_group4();
int fallible_function10_group4()
{
  auto result = non_trivial_destructor(10 * 10);
  result.trigger();
  auto result2 = non_trivial_destructor(10 * 10 * 2);
  result2.trigger();
  side_effect4 = side_effect4 +
    fallible_function11_group4();
  return side_effect4;
}

int fallible_function12_group4();
int fallible_function11_group4()
{
  auto result = non_trivial_destructor(11 * 11);
  result.trigger();
  auto result2 = non_trivial_destructor(11 * 11 * 2);
  result2.trigger();
  side_effect4 = side_effect4 +
    fallible_function12_group4();
  return side_effect4;
}

int fallible_function13_group4();
int fallible_function12_group4()
{
  auto result = non_trivial_destructor(12 * 12);
  result.trigger();
  auto result2 = non_trivial_destructor(12 * 12 * 2);
  result2.trigger();
  side_effect4 = side_effect4 +
    fallible_function13_group4();
  return side_effect4;
}

int fallible_function14_group4();
int fallible_function13_group4()
{
  auto result = non_trivial_destructor(13 * 13);
  result.trigger();
  auto result2 = non_trivial_destructor(13 * 13 * 2);
  result2.trigger();
  side_effect4 = side_effect4 +
    fallible_function14_group4();
  return side_effect4;
}

int fallible_function15_group4();
int fallible_function14_group4()
{
  auto result = non_trivial_destructor(14 * 14);
  result.trigger();
  auto result2 = non_trivial_destructor(14 * 14 * 2);
  result2.trigger();
  side_effect4 = side_effect4 +
    fallible_function15_group4();
  return side_effect4;
}

int fallible_function15_group4()
{
  auto result = non_trivial_destructor(4 * 15);
  result.trigger();
  auto result2 = non_trivial_destructor(4 * 15);
  result2.trigger();
  return side_effect4 + 1;
}

int fallible_function1_group5();
int fallible_function0_group5()
{
  auto result = non_trivial_destructor(0 * 0);
  result.trigger();
  auto result2 = non_trivial_destructor(0 * 0 * 2);
  result2.trigger();
  side_effect5 = side_effect5 +
    fallible_function1_group5();
  return side_effect5;
}

int fallible_function2_group5();
int fallible_function1_group5()
{
  auto result = non_trivial_destructor(1 * 1);
  result.trigger();
  auto result2 = non_trivial_destructor(1 * 1 * 2);
  result2.trigger();
  side_effect5 = side_effect5 +
    fallible_function2_group5();
  return side_effect5;
}

int fallible_function3_group5();
int fallible_function2_group5()
{
  auto result = non_trivial_destructor(2 * 2);
  result.trigger();
  auto result2 = non_trivial_destructor(2 * 2 * 2);
  result2.trigger();
  side_effect5 = side_effect5 +
    fallible_function3_group5();
  return side_effect5;
}

int fallible_function4_group5();
int fallible_function3_group5()
{
  auto result = non_trivial_destructor(3 * 3);
  result.trigger();
  auto result2 = non_trivial_destructor(3 * 3 * 2);
  result2.trigger();
  side_effect5 = side_effect5 +
    fallible_function4_group5();
  return side_effect5;
}

int fallible_function5_group5();
int fallible_function4_group5()
{
  auto result = non_trivial_destructor(4 * 4);
  result.trigger();
  auto result2 = non_trivial_destructor(4 * 4 * 2);
  result2.trigger();
  side_effect5 = side_effect5 +
    fallible_function5_group5();
  return side_effect5;
}

int fallible_function6_group5();
int fallible_function5_group5()
{
  auto result = non_trivial_destructor(5 * 5);
  result.trigger();
  auto result2 = non_trivial_destructor(5 * 5 * 2);
  result2.trigger();
  side_effect5 = side_effect5 +
    fallible_function6_group5();
  return side_effect5;
}

int fallible_function7_group5();
int fallible_function6_group5()
{
  auto result = non_trivial_destructor(6 * 6);
  result.trigger();
  auto result2 = non_trivial_destructor(6 * 6 * 2);
  result2.trigger();
  side_effect5 = side_effect5 +
    fallible_function7_group5();
  return side_effect5;
}

int fallible_function8_group5();
int fallible_function7_group5()
{
  auto result = non_trivial_destructor(7 * 7);
  result.trigger();
  auto result2 = non_trivial_destructor(7 * 7 * 2);
  result2.trigger();
  side_effect5 = side_effect5 +
    fallible_function8_group5();
  return side_effect5;
}

int fallible_function9_group5();
int fallible_function8_group5()
{
  auto result = non_trivial_destructor(8 * 8);
  result.trigger();
  auto result2 = non_trivial_destructor(8 * 8 * 2);
  result2.trigger();
  side_effect5 = side_effect5 +
    fallible_function9_group5();
  return side_effect5;
}

int fallible_function10_group5();
int fallible_function9_group5()
{
  auto result = non_trivial_destructor(9 * 9);
  result.trigger();
  auto result2 = non_trivial_destructor(9 * 9 * 2);
  result2.trigger();
  side_effect5 = side_effect5 +
    fallible_function10_group5();
  return side_effect5;
}

int fallible_function11_group5();
int fallible_function10_group5()
{
  auto result = non_trivial_destructor(10 * 10);
  result.trigger();
  auto result2 = non_trivial_destructor(10 * 10 * 2);
  result2.trigger();
  side_effect5 = side_effect5 +
    fallible_function11_group5();
  return side_effect5;
}

int fallible_function12_group5();
int fallible_function11_group5()
{
  auto result = non_trivial_destructor(11 * 11);
  result.trigger();
  auto result2 = non_trivial_destructor(11 * 11 * 2);
  result2.trigger();
  side_effect5 = side_effect5 +
    fallible_function12_group5();
  return side_effect5;
}

int fallible_function13_group5();
int fallible_function12_group5()
{
  auto result = non_trivial_destructor(12 * 12);
  result.trigger();
  auto result2 = non_trivial_destructor(12 * 12 * 2);
  result2.trigger();
  side_effect5 = side_effect5 +
    fallible_function13_group5();
  return side_effect5;
}

int fallible_function14_group5();
int fallible_function13_group5()
{
  auto result = non_trivial_destructor(13 * 13);
  result.trigger();
  auto result2 = non_trivial_destructor(13 * 13 * 2);
  result2.trigger();
  side_effect5 = side_effect5 +
    fallible_function14_group5();
  return side_effect5;
}

int fallible_function15_group5();
int fallible_function14_group5()
{
  auto result = non_trivial_destructor(14 * 14);
  result.trigger();
  auto result2 = non_trivial_destructor(14 * 14 * 2);
  result2.trigger();
  side_effect5 = side_effect5 +
    fallible_function15_group5();
  return side_effect5;
}

int fallible_function15_group5()
{
  auto result = non_trivial_destructor(5 * 15);
  result.trigger();
  auto result2 = non_trivial_destructor(5 * 15);
  result2.trigger();
  return side_effect5 + 1;
}

int fallible_function1_group6();
int fallible_function0_group6()
{
  auto result = non_trivial_destructor(0 * 0);
  result.trigger();
  auto result2 = non_trivial_destructor(0 * 0 * 2);
  result2.trigger();
  side_effect6 = side_effect6 +
    fallible_function1_group6();
  return side_effect6;
}

int fallible_function2_group6();
int fallible_function1_group6()
{
  auto result = non_trivial_destructor(1 * 1);
  result.trigger();
  auto result2 = non_trivial_destructor(1 * 1 * 2);
  result2.trigger();
  side_effect6 = side_effect6 +
    fallible_function2_group6();
  return side_effect6;
}

int fallible_function3_group6();
int fallible_function2_group6()
{
  auto result = non_trivial_destructor(2 * 2);
  result.trigger();
  auto result2 = non_trivial_destructor(2 * 2 * 2);
  result2.trigger();
  side_effect6 = side_effect6 +
    fallible_function3_group6();
  return side_effect6;
}

int fallible_function4_group6();
int fallible_function3_group6()
{
  auto result = non_trivial_destructor(3 * 3);
  result.trigger();
  auto result2 = non_trivial_destructor(3 * 3 * 2);
  result2.trigger();
  side_effect6 = side_effect6 +
    fallible_function4_group6();
  return side_effect6;
}

int fallible_function5_group6();
int fallible_function4_group6()
{
  auto result = non_trivial_destructor(4 * 4);
  result.trigger();
  auto result2 = non_trivial_destructor(4 * 4 * 2);
  result2.trigger();
  side_effect6 = side_effect6 +
    fallible_function5_group6();
  return side_effect6;
}

int fallible_function6_group6();
int fallible_function5_group6()
{
  auto result = non_trivial_destructor(5 * 5);
  result.trigger();
  auto result2 = non_trivial_destructor(5 * 5 * 2);
  result2.trigger();
  side_effect6 = side_effect6 +
    fallible_function6_group6();
  return side_effect6;
}

int fallible_function7_group6();
int fallible_function6_group6()
{
  auto result = non_trivial_destructor(6 * 6);
  result.trigger();
  auto result2 = non_trivial_destructor(6 * 6 * 2);
  result2.trigger();
  side_effect6 = side_effect6 +
    fallible_function7_group6();
  return side_effect6;
}

int fallible_function8_group6();
int fallible_function7_group6()
{
  auto result = non_trivial_destructor(7 * 7);
  result.trigger();
  auto result2 = non_trivial_destructor(7 * 7 * 2);
  result2.trigger();
  side_effect6 = side_effect6 +
    fallible_function8_group6();
  return side_effect6;
}

int fallible_function9_group6();
int fallible_function8_group6()
{
  auto result = non_trivial_destructor(8 * 8);
  result.trigger();
  auto result2 = non_trivial_destructor(8 * 8 * 2);
  result2.trigger();
  side_effect6 = side_effect6 +
    fallible_function9_group6();
  return side_effect6;
}

int fallible_function10_group6();
int fallible_function9_group6()
{
  auto result = non_trivial_destructor(9 * 9);
  result.trigger();
  auto result2 = non_trivial_destructor(9 * 9 * 2);
  result2.trigger();
  side_effect6 = side_effect6 +
    fallible_function10_group6();
  return side_effect6;
}

int fallible_function11_group6();
int fallible_function10_group6()
{
  auto result = non_trivial_destructor(10 * 10);
  result.trigger();
  auto result2 = non_trivial_destructor(10 * 10 * 2);
  result2.trigger();
  side_effect6 = side_effect6 +
    fallible_function11_group6();
  return side_effect6;
}

int fallible_function12_group6();
int fallible_function11_group6()
{
  auto result = non_trivial_destructor(11 * 11);
  result.trigger();
  auto result2 = non_trivial_destructor(11 * 11 * 2);
  result2.trigger();
  side_effect6 = side_effect6 +
    fallible_function12_group6();
  return side_effect6;
}

int fallible_function13_group6();
int fallible_function12_group6()
{
  auto result = non_trivial_destructor(12 * 12);
  result.trigger();
  auto result2 = non_trivial_destructor(12 * 12 * 2);
  result2.trigger();
  side_effect6 = side_effect6 +
    fallible_function13_group6();
  return side_effect6;
}

int fallible_function14_group6();
int fallible_function13_group6()
{
  auto result = non_trivial_destructor(13 * 13);
  result.trigger();
  auto result2 = non_trivial_destructor(13 * 13 * 2);
  result2.trigger();
  side_effect6 = side_effect6 +
    fallible_function14_group6();
  return side_effect6;
}

int fallible_function15_group6();
int fallible_function14_group6()
{
  auto result = non_trivial_destructor(14 * 14);
  result.trigger();
  auto result2 = non_trivial_destructor(14 * 14 * 2);
  result2.trigger();
  side_effect6 = side_effect6 +
    fallible_function15_group6();
  return side_effect6;
}

int fallible_function15_group6()
{
  auto result = non_trivial_destructor(6 * 15);
  result.trigger();
  auto result2 = non_trivial_destructor(6 * 15);
  result2.trigger();
  return side_effect6 + 1;
}

int fallible_function1_group7();
int fallible_function0_group7()
{
  auto result = non_trivial_destructor(0 * 0);
  result.trigger();
  auto result2 = non_trivial_destructor(0 * 0 * 2);
  result2.trigger();
  side_effect7 = side_effect7 +
    fallible_function1_group7();
  return side_effect7;
}

int fallible_function2_group7();
int fallible_function1_group7()
{
  auto result = non_trivial_destructor(1 * 1);
  result.trigger();
  auto result2 = non_trivial_destructor(1 * 1 * 2);
  result2.trigger();
  side_effect7 = side_effect7 +
    fallible_function2_group7();
  return side_effect7;
}

int fallible_function3_group7();
int fallible_function2_group7()
{
  auto result = non_trivial_destructor(2 * 2);
  result.trigger();
  auto result2 = non_trivial_destructor(2 * 2 * 2);
  result2.trigger();
  side_effect7 = side_effect7 +
    fallible_function3_group7();
  return side_effect7;
}

int fallible_function4_group7();
int fallible_function3_group7()
{
  auto result = non_trivial_destructor(3 * 3);
  result.trigger();
  auto result2 = non_trivial_destructor(3 * 3 * 2);
  result2.trigger();
  side_effect7 = side_effect7 +
    fallible_function4_group7();
  return side_effect7;
}

int fallible_function5_group7();
int fallible_function4_group7()
{
  auto result = non_trivial_destructor(4 * 4);
  result.trigger();
  auto result2 = non_trivial_destructor(4 * 4 * 2);
  result2.trigger();
  side_effect7 = side_effect7 +
    fallible_function5_group7();
  return side_effect7;
}

int fallible_function6_group7();
int fallible_function5_group7()
{
  auto result = non_trivial_destructor(5 * 5);
  result.trigger();
  auto result2 = non_trivial_destructor(5 * 5 * 2);
  result2.trigger();
  side_effect7 = side_effect7 +
    fallible_function6_group7();
  return side_effect7;
}

int fallible_function7_group7();
int fallible_function6_group7()
{
  auto result = non_trivial_destructor(6 * 6);
  result.trigger();
  auto result2 = non_trivial_destructor(6 * 6 * 2);
  result2.trigger();
  side_effect7 = side_effect7 +
    fallible_function7_group7();
  return side_effect7;
}

int fallible_function8_group7();
int fallible_function7_group7()
{
  auto result = non_trivial_destructor(7 * 7);
  result.trigger();
  auto result2 = non_trivial_destructor(7 * 7 * 2);
  result2.trigger();
  side_effect7 = side_effect7 +
    fallible_function8_group7();
  return side_effect7;
}

int fallible_function9_group7();
int fallible_function8_group7()
{
  auto result = non_trivial_destructor(8 * 8);
  result.trigger();
  auto result2 = non_trivial_destructor(8 * 8 * 2);
  result2.trigger();
  side_effect7 = side_effect7 +
    fallible_function9_group7();
  return side_effect7;
}

int fallible_function10_group7();
int fallible_function9_group7()
{
  auto result = non_trivial_destructor(9 * 9);
  result.trigger();
  auto result2 = non_trivial_destructor(9 * 9 * 2);
  result2.trigger();
  side_effect7 = side_effect7 +
    fallible_function10_group7();
  return side_effect7;
}

int fallible_function11_group7();
int fallible_function10_group7()
{
  auto result = non_trivial_destructor(10 * 10);
  result.trigger();
  auto result2 = non_trivial_destructor(10 * 10 * 2);
  result2.trigger();
  side_effect7 = side_effect7 +
    fallible_function11_group7();
  return side_effect7;
}

int fallible_function12_group7();
int fallible_function11_group7()
{
  auto result = non_trivial_destructor(11 * 11);
  result.trigger();
  auto result2 = non_trivial_destructor(11 * 11 * 2);
  result2.trigger();
  side_effect7 = side_effect7 +
    fallible_function12_group7();
  return side_effect7;
}

int fallible_function13_group7();
int fallible_function12_group7()
{
  auto result = non_trivial_destructor(12 * 12);
  result.trigger();
  auto result2 = non_trivial_destructor(12 * 12 * 2);
  result2.trigger();
  side_effect7 = side_effect7 +
    fallible_function13_group7();
  return side_effect7;
}

int fallible_function14_group7();
int fallible_function13_group7()
{
  auto result = non_trivial_destructor(13 * 13);
  result.trigger();
  auto result2 = non_trivial_destructor(13 * 13 * 2);
  result2.trigger();
  side_effect7 = side_effect7 +
    fallible_function14_group7();
  return side_effect7;
}

int fallible_function15_group7();
int fallible_function14_group7()
{
  auto result = non_trivial_destructor(14 * 14);
  result.trigger();
  auto result2 = non_trivial_destructor(14 * 14 * 2);
  result2.trigger();
  side_effect7 = side_effect7 +
    fallible_function15_group7();
  return side_effect7;
}

int fallible_function15_group7()
{
  auto result = non_trivial_destructor(7 * 15);
  result.trigger();
  auto result2 = non_trivial_destructor(7 * 15);
  result2.trigger();
  return side_effect7 + 1;
}

int fallible_function1_group8();
int fallible_function0_group8()
{
  auto result = non_trivial_destructor(0 * 0);
  result.trigger();
  auto result2 = non_trivial_destructor(0 * 0 * 2);
  result2.trigger();
  side_effect8 = side_effect8 +
    fallible_function1_group8();
  return side_effect8;
}

int fallible_function2_group8();
int fallible_function1_group8()
{
  auto result = non_trivial_destructor(1 * 1);
  result.trigger();
  auto result2 = non_trivial_destructor(1 * 1 * 2);
  result2.trigger();
  side_effect8 = side_effect8 +
    fallible_function2_group8();
  return side_effect8;
}

int fallible_function3_group8();
int fallible_function2_group8()
{
  auto result = non_trivial_destructor(2 * 2);
  result.trigger();
  auto result2 = non_trivial_destructor(2 * 2 * 2);
  result2.trigger();
  side_effect8 = side_effect8 +
    fallible_function3_group8();
  return side_effect8;
}

int fallible_function4_group8();
int fallible_function3_group8()
{
  auto result = non_trivial_destructor(3 * 3);
  result.trigger();
  auto result2 = non_trivial_destructor(3 * 3 * 2);
  result2.trigger();
  side_effect8 = side_effect8 +
    fallible_function4_group8();
  return side_effect8;
}

int fallible_function5_group8();
int fallible_function4_group8()
{
  auto result = non_trivial_destructor(4 * 4);
  result.trigger();
  auto result2 = non_trivial_destructor(4 * 4 * 2);
  result2.trigger();
  side_effect8 = side_effect8 +
    fallible_function5_group8();
  return side_effect8;
}

int fallible_function6_group8();
int fallible_function5_group8()
{
  auto result = non_trivial_destructor(5 * 5);
  result.trigger();
  auto result2 = non_trivial_destructor(5 * 5 * 2);
  result2.trigger();
  side_effect8 = side_effect8 +
    fallible_function6_group8();
  return side_effect8;
}

int fallible_function7_group8();
int fallible_function6_group8()
{
  auto result = non_trivial_destructor(6 * 6);
  result.trigger();
  auto result2 = non_trivial_destructor(6 * 6 * 2);
  result2.trigger();
  side_effect8 = side_effect8 +
    fallible_function7_group8();
  return side_effect8;
}

int fallible_function8_group8();
int fallible_function7_group8()
{
  auto result = non_trivial_destructor(7 * 7);
  result.trigger();
  auto result2 = non_trivial_destructor(7 * 7 * 2);
  result2.trigger();
  side_effect8 = side_effect8 +
    fallible_function8_group8();
  return side_effect8;
}

int fallible_function9_group8();
int fallible_function8_group8()
{
  auto result = non_trivial_destructor(8 * 8);
  result.trigger();
  auto result2 = non_trivial_destructor(8 * 8 * 2);
  result2.trigger();
  side_effect8 = side_effect8 +
    fallible_function9_group8();
  return side_effect8;
}

int fallible_function10_group8();
int fallible_function9_group8()
{
  auto result = non_trivial_destructor(9 * 9);
  result.trigger();
  auto result2 = non_trivial_destructor(9 * 9 * 2);
  result2.trigger();
  side_effect8 = side_effect8 +
    fallible_function10_group8();
  return side_effect8;
}

int fallible_function11_group8();
int fallible_function10_group8()
{
  auto result = non_trivial_destructor(10 * 10);
  result.trigger();
  auto result2 = non_trivial_destructor(10 * 10 * 2);
  result2.trigger();
  side_effect8 = side_effect8 +
    fallible_function11_group8();
  return side_effect8;
}

int fallible_function12_group8();
int fallible_function11_group8()
{
  auto result = non_trivial_destructor(11 * 11);
  result.trigger();
  auto result2 = non_trivial_destructor(11 * 11 * 2);
  result2.trigger();
  side_effect8 = side_effect8 +
    fallible_function12_group8();
  return side_effect8;
}

int fallible_function13_group8();
int fallible_function12_group8()
{
  auto result = non_trivial_destructor(12 * 12);
  result.trigger();
  auto result2 = non_trivial_destructor(12 * 12 * 2);
  result2.trigger();
  side_effect8 = side_effect8 +
    fallible_function13_group8();
  return side_effect8;
}

int fallible_function14_group8();
int fallible_function13_group8()
{
  auto result = non_trivial_destructor(13 * 13);
  result.trigger();
  auto result2 = non_trivial_destructor(13 * 13 * 2);
  result2.trigger();
  side_effect8 = side_effect8 +
    fallible_function14_group8();
  return side_effect8;
}

int fallible_function15_group8();
int fallible_function14_group8()
{
  auto result = non_trivial_destructor(14 * 14);
  result.trigger();
  auto result2 = non_trivial_destructor(14 * 14 * 2);
  result2.trigger();
  side_effect8 = side_effect8 +
    fallible_function15_group8();
  return side_effect8;
}

int fallible_function15_group8()
{
  auto result = non_trivial_destructor(8 * 15);
  result.trigger();
  auto result2 = non_trivial_destructor(8 * 15);
  result2.trigger();
  return side_effect8 + 1;
}

int fallible_function1_group9();
int fallible_function0_group9()
{
  auto result = non_trivial_destructor(0 * 0);
  result.trigger();
  auto result2 = non_trivial_destructor(0 * 0 * 2);
  result2.trigger();
  side_effect9 = side_effect9 +
    fallible_function1_group9();
  return side_effect9;
}

int fallible_function2_group9();
int fallible_function1_group9()
{
  auto result = non_trivial_destructor(1 * 1);
  result.trigger();
  auto result2 = non_trivial_destructor(1 * 1 * 2);
  result2.trigger();
  side_effect9 = side_effect9 +
    fallible_function2_group9();
  return side_effect9;
}

int fallible_function3_group9();
int fallible_function2_group9()
{
  auto result = non_trivial_destructor(2 * 2);
  result.trigger();
  auto result2 = non_trivial_destructor(2 * 2 * 2);
  result2.trigger();
  side_effect9 = side_effect9 +
    fallible_function3_group9();
  return side_effect9;
}

int fallible_function4_group9();
int fallible_function3_group9()
{
  auto result = non_trivial_destructor(3 * 3);
  result.trigger();
  auto result2 = non_trivial_destructor(3 * 3 * 2);
  result2.trigger();
  side_effect9 = side_effect9 +
    fallible_function4_group9();
  return side_effect9;
}

int fallible_function5_group9();
int fallible_function4_group9()
{
  auto result = non_trivial_destructor(4 * 4);
  result.trigger();
  auto result2 = non_trivial_destructor(4 * 4 * 2);
  result2.trigger();
  side_effect9 = side_effect9 +
    fallible_function5_group9();
  return side_effect9;
}

int fallible_function6_group9();
int fallible_function5_group9()
{
  auto result = non_trivial_destructor(5 * 5);
  result.trigger();
  auto result2 = non_trivial_destructor(5 * 5 * 2);
  result2.trigger();
  side_effect9 = side_effect9 +
    fallible_function6_group9();
  return side_effect9;
}

int fallible_function7_group9();
int fallible_function6_group9()
{
  auto result = non_trivial_destructor(6 * 6);
  result.trigger();
  auto result2 = non_trivial_destructor(6 * 6 * 2);
  result2.trigger();
  side_effect9 = side_effect9 +
    fallible_function7_group9();
  return side_effect9;
}

int fallible_function8_group9();
int fallible_function7_group9()
{
  auto result = non_trivial_destructor(7 * 7);
  result.trigger();
  auto result2 = non_trivial_destructor(7 * 7 * 2);
  result2.trigger();
  side_effect9 = side_effect9 +
    fallible_function8_group9();
  return side_effect9;
}

int fallible_function9_group9();
int fallible_function8_group9()
{
  auto result = non_trivial_destructor(8 * 8);
  result.trigger();
  auto result2 = non_trivial_destructor(8 * 8 * 2);
  result2.trigger();
  side_effect9 = side_effect9 +
    fallible_function9_group9();
  return side_effect9;
}

int fallible_function10_group9();
int fallible_function9_group9()
{
  auto result = non_trivial_destructor(9 * 9);
  result.trigger();
  auto result2 = non_trivial_destructor(9 * 9 * 2);
  result2.trigger();
  side_effect9 = side_effect9 +
    fallible_function10_group9();
  return side_effect9;
}

int fallible_function11_group9();
int fallible_function10_group9()
{
  auto result = non_trivial_destructor(10 * 10);
  result.trigger();
  auto result2 = non_trivial_destructor(10 * 10 * 2);
  result2.trigger();
  side_effect9 = side_effect9 +
    fallible_function11_group9();
  return side_effect9;
}

int fallible_function12_group9();
int fallible_function11_group9()
{
  auto result = non_trivial_destructor(11 * 11);
  result.trigger();
  auto result2 = non_trivial_destructor(11 * 11 * 2);
  result2.trigger();
  side_effect9 = side_effect9 +
    fallible_function12_group9();
  return side_effect9;
}

int fallible_function13_group9();
int fallible_function12_group9()
{
  auto result = non_trivial_destructor(12 * 12);
  result.trigger();
  auto result2 = non_trivial_destructor(12 * 12 * 2);
  result2.trigger();
  side_effect9 = side_effect9 +
    fallible_function13_group9();
  return side_effect9;
}

int fallible_function14_group9();
int fallible_function13_group9()
{
  auto result = non_trivial_destructor(13 * 13);
  result.trigger();
  auto result2 = non_trivial_destructor(13 * 13 * 2);
  result2.trigger();
  side_effect9 = side_effect9 +
    fallible_function14_group9();
  return side_effect9;
}

int fallible_function15_group9();
int fallible_function14_group9()
{
  auto result = non_trivial_destructor(14 * 14);
  result.trigger();
  auto result2 = non_trivial_destructor(14 * 14 * 2);
  result2.trigger();
  side_effect9 = side_effect9 +
    fallible_function15_group9();
  return side_effect9;
}

int fallible_function15_group9()
{
  auto result = non_trivial_destructor(9 * 15);
  result.trigger();
  auto result2 = non_trivial_destructor(9 * 15);
  result2.trigger();
  return side_effect9 + 1;
}

