#include <array>
#include <cstdio>

#include <libhal-armcortex/dwt_counter.hpp>
#include <libhal-armcortex/startup.hpp>
#include <libhal-armcortex/system_control.hpp>
#include <libhal-lpc40xx/input_pin.hpp>
#include <libhal-lpc40xx/system_controller.hpp>
#include <libhal-lpc40xx/uart.hpp>
#include <libhal-util/serial.hpp>
#include <libhal-util/steady_clock.hpp>

int
main()
{
  using namespace hal::literals;

  // Initializing the data section initializes global and static variables and
  // is required for the standard C library to run.
  hal::cortex_m::initialize_data_section();
  hal::cortex_m::system_control::initialize_floating_point_unit();

  auto& clock = hal::lpc40xx::clock::get();
  const auto cpu_frequency = clock.get_frequency(hal::lpc40xx::peripheral::cpu);
  hal::cortex_m::dwt_counter steady_clock(cpu_frequency);

  auto& uart0 = hal::lpc40xx::uart::get<0>(hal::serial::settings{
                                             .baud_rate = 38400.0f,
                                           })
                  .value();

  // 15
  // 23
  // 22
  // 20
  // 19
  // 26
  // 25
  // 24
  // 28
  // 9
  // 10
  //

  while (true) {
    using namespace std::literals;

    hal::print<512>(
      uart0,
      "G0  = P_1[15] = [%d] \n"
      "G1  = P_1[23] = [%d] \n"
      "G2  = P_1[22] = [%d] \n"
      "G3  = P_1[20] = [%d] \n"
      "G4  = P_1[19] = [%d] \n"
      "G5  = P_1[26] = [%d] \n"
      "G6  = P_1[25] = [%d] \n"
      "G7  = P_1[24] = [%d] \n"
      "G8  = P_1[28] = [%d] \n"
      "G9  = P_1[9]  = [%d] \n"
      "G10 = P_1[10] = [%d] \n"
      "=======================\n\n",
      hal::lpc40xx::input_pin::get<1, 15>().value().level().value(),
      hal::lpc40xx::input_pin::get<1, 23>().value().level().value(),
      hal::lpc40xx::input_pin::get<1, 22>().value().level().value(),
      hal::lpc40xx::input_pin::get<1, 20>().value().level().value(),
      hal::lpc40xx::input_pin::get<1, 19>().value().level().value(),
      hal::lpc40xx::input_pin::get<1, 26>().value().level().value(),
      hal::lpc40xx::input_pin::get<1, 25>().value().level().value(),
      hal::lpc40xx::input_pin::get<1, 24>().value().level().value(),
      hal::lpc40xx::input_pin::get<1, 28>().value().level().value(),
      hal::lpc40xx::input_pin::get<1, 9>().value().level().value(),
      hal::lpc40xx::input_pin::get<1, 10>().value().level().value());

    (void)hal::delay(steady_clock, 500ms);
  }

  return -1;
}

// When libhal.tweaks.hpp includes:
//
// #define BOOST_LEAF_EMBEDDED
// #define BOOST_LEAF_NO_THREADS
//
// Then Boost.LEAF needs this function to be defined
namespace boost {
void
throw_exception([[maybe_unused]] std::exception const& p_error)
{
  std::abort();
}
} // namespace boost
