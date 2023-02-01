#pragma once

#define BOOST_LEAF_EMBEDDED
#define BOOST_LEAF_NO_THREADS

#include <exception>
#include <string_view>

namespace hal::config {
constexpr std::string_view platform = "lpc4078";
} // namespace hal::config

namespace boost {
void
throw_exception([[maybe_unused]] std::exception const& p_error)
{
  std::abort();
}
} // namespace boost