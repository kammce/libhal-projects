#include <array>
#include <cstdio>

#include <libhal-armcortex/dwt_counter.hpp>
#include <libhal-armcortex/startup.hpp>
#include <libhal-armcortex/system_control.hpp>
#include <libhal-lpc40xx/i2c.hpp>
#include <libhal-lpc40xx/system_controller.hpp>
#include <libhal-lpc40xx/uart.hpp>
#include <libhal-util/i2c.hpp>
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

  // Set the MCU to the maximum clock speed
  (void)hal::lpc40xx::clock::maximum(10.0_MHz);

  auto& clock = hal::lpc40xx::clock::get();
  const auto cpu_frequency = clock.get_frequency(hal::lpc40xx::peripheral::cpu);
  hal::cortex_m::dwt_counter steady_clock(cpu_frequency);

  auto& uart0 = hal::lpc40xx::uart::get<0>(hal::serial::settings{
                                             .baud_rate = 38400.0f,
                                           })
                  .value();

  auto& i2c2 = hal::lpc40xx::i2c::get<2>().value();

  static constexpr hal::byte address = 0x31;
  static constexpr hal::byte id_register = 0xC0;
  static constexpr hal::byte expected_sensor_id = 0x14;
  static constexpr hal::byte one_burst_register = 0xC4;
  static constexpr hal::byte automatic_bit_register = 0xC5;
  static constexpr hal::byte most_significant_register = 0xC1;

  static constexpr std::array<hal::byte, 2> one_burst_payload{
    one_burst_register, 0x04
  };
  static constexpr std::array<hal::byte, 2> automatic_payload{
    automatic_bit_register, 0x01
  };
  static constexpr std::array<hal::byte, 1> msb_payload{
    most_significant_register
  };
  static constexpr std::array<hal::byte, 1> get_id_register{ id_register };
  std::array<hal::byte, 1> temperature_id{};

  hal::print(uart0, "Starting si7060 demo!\n");

  (void)hal::write_then_read(
    i2c2, address, get_id_register, temperature_id, hal::never_timeout());

  if (temperature_id[0] != expected_sensor_id) {
    hal::print<128>(uart0,
                    "Invalid temperature ID 0x%02X :: expected = 0x%02X\n",
                    temperature_id[0],
                    expected_sensor_id);
  }

  while (true) {
    using namespace std::literals;

    std::array<hal::byte, 1> temperature_msb;
    std::array<hal::byte, 1> temperature_lsb;

    // The register will enable the device to collect data once
    // and automatically sets the stop bit to 0 (2nd bit).
    (void)(hal::write(i2c2, address, one_burst_payload, hal::never_timeout()));

    // Enable I2C automatic address increment on read (must be done every time)
    (void)(hal::write(i2c2, address, automatic_payload, hal::never_timeout()));

    // These need to be in separate transactions
    (void)(hal::write_then_read(
      i2c2, address, msb_payload, temperature_msb, hal::never_timeout()));
    (void)(hal::read(i2c2, address, temperature_lsb, hal::never_timeout()));

    temperature_msb[0] = temperature_msb[0] & ~(1 << 7);

    int32_t temperature_data = (temperature_msb[0] << 8) | temperature_lsb[0];

    float acquired_temperature =
      static_cast<float>(temperature_data - 0b11'1111'1111'1111);
    auto temperature = (acquired_temperature / 160.0f) + 55.0f;

    hal::print<128>(uart0, "temperature = %f\n", temperature);
    (void)hal::delay(steady_clock, 1s);
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
