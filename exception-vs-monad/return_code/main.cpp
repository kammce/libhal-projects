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

// Switches
constexpr size_t error_size = 4;
constexpr bool error_in_constructor = false;
constexpr bool error_in_class_function = false;
constexpr bool depth_before_exception = 50;

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
  non_trivial_destructor(non_trivial_destructor&&) = default;
  non_trivial_destructor& operator=(non_trivial_destructor&&) = default;

  tl::expected<void, error_t> trigger()
  {
    if constexpr (error_in_class_function) {
      if (m_channel >= depth_before_exception) {
        tl::unexpected(error_t{ .data = { 0xAA, 0xBB, 0x33, 0x44 } });
      }
    }
    trigger_register = trigger_register | (1 << m_channel);
    return {};
  }

  ~non_trivial_destructor()
  {
    enable_register = enable_register & ~(1 << m_channel);
  }

private:
  non_trivial_destructor(uint8_t p_channel)
    : m_channel(p_channel)
  {
  }

  uint8_t m_channel = 0;
};

tl::expected<void, error_t> return_error();
tl::expected<void, error_t> top_call()
{
  auto result = return_error();
  if (!result) {
    return tl::unexpected(result.error());
  }
  return {};
}

int main()
{
  auto result = top_call();
  if (!result) {
    return static_cast<int>(result.error().data[0]);
  }
  return 0;
}

tl::expected<void, error_t> return_error()
{
  auto result = non_trivial_destructor::initialize(50);

  if (result) {
    auto result2 = result.value().trigger();
    if (!result2) {
      return tl::unexpected(result2.error());
    }
  } else {
    return tl::unexpected(result.error());
  }

  return {};
}