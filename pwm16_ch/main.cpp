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
#include <libhal/pwm.hpp>

class pca9685
{
public:
  class pwm_channel : public hal::pwm
  {
  private:
    pwm_channel(pca9685* p_pca9685, hal::byte p_channel)
      : m_pca9685(p_pca9685)
      , m_channel(p_channel)
    {
    }

    hal::status driver_frequency(hal::hertz p_frequency) override
    {
      return m_pca9685->set_channel_frequency(p_frequency, m_channel);
    }

    hal::status driver_duty_cycle(float p_duty_cycle) override
    {
      return m_pca9685->set_channel_duty_cycle(p_duty_cycle, m_channel);
    }

    pca9685* m_pca9685;
    hal::byte m_channel;

    friend class pca9685;
  };

  enum class output_enable_state
  {
    /// Set all pins to LOW voltage when output enable is asserted.
    set_low = 0b00,
    /// Set all the pins to HIGH voltage when output enable is asserted.
    /// When the pins are set to be open_collector, meaning the device was
    /// configured for `totem_pole_output = false`, then the output is high-Z.
    set_high = 0b10,
    /// Set all pins to HIGH-Z output
    set_high_z = 0b11,
  };

  struct settings
  {
    bool use_external_clock = false;
    bool invert_outputs = false;
    bool output_changes_on_i2c_acknowledge = false;
    bool totem_pole_output = true;
  };

  template<size_t Channel>
  static hal::result<pwm_channel> create()
  {
    static constexpr size_t max_channel_count = 16;
    static_assert(Channel <= max_channel_count,
                  "The PCA9685 only has 16 channels!");
    return
  }

  template<hal::byte Channel>
  hal::result<pwm_channel> get_pwm_channel()
  {
    static constexpr size_t max_channel_count = 16;
    static_assert(Channel <= max_channel_count,
                  "The PCA9685 only has 16 channels!");

    return pwm_channel(this, Channel);
  }

  hal::status configure() {}
  hal::status restart() {}

private:
  pca9685() {}

  hal::status set_channel_frequency(hal::hertz p_frequency,
                                    hal::byte p_channel);
  hal::status set_channel_duty_cycle(float p_duty_cycle, hal::byte p_channel);
};

hal::status
pca9685::set_channel_frequency([[maybe_unused]] hal::hertz p_frequency,
                               [[maybe_unused]] hal::byte p_channel)
{
  return hal::success();
}

hal::status
pca9685::set_channel_duty_cycle([[maybe_unused]] float p_duty_cycle,
                                [[maybe_unused]] hal::byte p_channel)
{
  return hal::success();
}

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

  while (true) {
    using namespace std::literals;
    (void)hal::delay(steady_clock, 500ms);
  }

  return -1;
}
