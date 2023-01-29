#include <libhal-armcortex/dwt_counter.hpp>
#include <libhal-armcortex/startup.hpp>
#include <libhal-armcortex/system_control.hpp>
#include <libhal-lpc40xx/can.hpp>
#include <libhal-lpc40xx/system_controller.hpp>
#include <libhal-lpc40xx/uart.hpp>
#include <libhal-rmd/drc.hpp>
#include <libhal-util/serial.hpp>
#include <libhal-util/steady_clock.hpp>

#include <cinttypes>

[[nodiscard]] hal::status
print_feedback_and_delay(hal::rmd::drc& p_drc,
                         hal::serial& p_serial,
                         hal::steady_clock& p_steady_clock,
                         hal::time_duration p_duration) noexcept
{
  std::array<char, 256> buffer;
  HAL_CHECK(hal::delay(p_steady_clock, p_duration / 2));
  p_drc.feedback_request(hal::rmd::drc::read::status_1_and_error_flags);
  p_drc.feedback_request(hal::rmd::drc::read::status_2);
  HAL_CHECK(hal::delay(p_steady_clock, p_duration / 2));
  int count =
    std::snprintf(buffer.data(),
                  buffer.size(),
                  "raw_current = %" PRId16 "\n"
                  "raw_voltage = %" PRId16 "\n"
                  "raw_motor_temperature = %" PRId16 "\n"
                  "raw_speed = %" PRId16 "\n"
                  "over_temperature_protection_tripped = %d\n"
                  "over_voltage_protection_tripped = %d\n"
                  "encoder = %" PRId16 "\n\n",
                  p_drc.feedback().raw_current,
                  p_drc.feedback().raw_volts,
                  p_drc.feedback().raw_motor_temperature,
                  p_drc.feedback().raw_speed,
                  p_drc.feedback().over_temperature_protection_tripped,
                  p_drc.feedback().over_voltage_protection_tripped,
                  p_drc.feedback().encoder);

  HAL_CHECK((hal::write(
    p_serial, hal::as_bytes(buffer).subspan(0, static_cast<size_t>(count)))));

  return hal::success();
}

int
main()
{
  using namespace hal::literals;
  using namespace std::literals;

  // Initializing the data section initializes global and static variables and
  // is required for the standard C library to run.
  hal::cortex_m::initialize_data_section();
  hal::cortex_m::system_control::initialize_floating_point_unit();

  // Set the MCU to the maximum clock speed
  (void)hal::lpc40xx::clock::maximum(12.0_MHz);

  // Create a hardware counter
  auto& clock = hal::lpc40xx::clock::get();
  auto cpu_frequency = clock.get_frequency(hal::lpc40xx::peripheral::cpu);
  static hal::cortex_m::dwt_counter steady_clock(cpu_frequency);

  // Get and initialize UART0 for UART based terminal logging
  auto& terminal = hal::lpc40xx::uart::get<0, 64>(hal::serial::settings{
                                                    .baud_rate = 38400,
                                                  })
                     .value();

  (void)hal::write(terminal, "Starting 6 motor RMD Demo!\n");

  hal::can::settings can_settings{ .baud_rate = 1.0_MHz };
  auto can = hal::lpc40xx::can::get<2>().value();
  (void)can.configure(can_settings);

  auto router = hal::can_router::create(can).value();
  auto drc1 = hal::rmd::drc::create(router, 6.0f, 0x141).value();
  auto drc2 = hal::rmd::drc::create(router, 6.0f, 0x142).value();
  auto drc3 = hal::rmd::drc::create(router, 6.0f, 0x143).value();
  auto drc4 = hal::rmd::drc::create(router, 6.0f, 0x144).value();
  auto drc5 = hal::rmd::drc::create(router, 6.0f, 0x145).value();
  auto drc6 = hal::rmd::drc::create(router, 6.0f, 0x146).value();

  while (true) {
    drc1.velocity_control(6.0_rpm);
    // drc2.velocity_control(50.0_rpm);
    drc3.velocity_control(6.0_rpm);
    // drc4.velocity_control(50.0_rpm);
    drc5.velocity_control(6.0_rpm);
    // drc6.velocity_control(50.0_rpm);

    (void)hal::delay(steady_clock, 5s);

    drc1.velocity_control(-6.0_rpm);
    // drc2.velocity_control(-50.0_rpm);
    drc3.velocity_control(-6.0_rpm);
    // drc4.velocity_control(-50.0_rpm);
    drc5.velocity_control(-6.0_rpm);
    // drc6.velocity_control(-50.0_rpm);

    (void)hal::delay(steady_clock, 5s);
  }
  return 0;
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
