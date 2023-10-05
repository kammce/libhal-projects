
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
#include <string_view>

constexpr size_t error_size = 128;
constexpr bool check_bounds_in_constructor = true;
constexpr bool check_bounds_in_class_function = true;
constexpr uint32_t depth_before_exception = 1000;

struct my_error_t
{
  std::array<std::uint8_t, error_size> data;
};

volatile std::uint64_t enable_register;
volatile std::uint64_t trigger_register;

// Extra type to demonstrate polymorphic errors with exceptions
class my_exception
{
public:
  virtual std::string_view what() = 0;
};

class my_runtime_exception
{
public:
  my_runtime_exception(std::string_view p_message)
    : m_message(p_message)
  {
  }

  std::string_view what()
  {
    return m_message;
  }

  std::string_view m_message;
};

class non_trivial_destructor
{
public:
  non_trivial_destructor(uint32_t p_channel)
    : m_channel(p_channel)
  {
    if constexpr (check_bounds_in_constructor) {
      if (p_channel >= depth_before_exception) {
        using namespace std::literals;
        // throw my_error_t{ .data = { 0x55, 0xAA, 0x33, 0x44 } };
        throw my_runtime_exception{ "p_channel is out of bounds"sv };
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
    enable_register = enable_register & ~(1 << m_channel);
  }

  void trigger()
  {
    if constexpr (check_bounds_in_class_function) {
      if (m_channel >= depth_before_exception) {
        throw my_error_t{ .data = { 0xAA, 0xBB, 0x33, 0x44 } };
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
  } catch (const my_error_t& p_error) {
    return p_error.data[0];
  } catch ([[maybe_unused]] const my_exception& p_exception) {
    return_code = 42;
  } catch (...) {
    return 15;
  }
  return return_code;
}

volatile int side_effect0 = 0;

int return_error()
{
  auto result = non_trivial_destructor(0);
  result.trigger();
  auto result2 = non_trivial_destructor(1000);
  result2.trigger();
  side_effect0 = side_effect0 + 1;
  return side_effect0;
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

[[noreturn]] void terminate() noexcept
{
  while (true) {
    continue;
  }
}

namespace __cxxabiv1 {
std::terminate_handler __terminate_handler = terminate;
}