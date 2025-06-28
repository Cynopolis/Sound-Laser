#pragma once

#include <cstdint>

static constexpr uint32_t  SYSTEM_CLOCK{125'000'000};
static constexpr uint32_t  PWM_FREQUENCY{41'100};
static constexpr uint16_t CLOCK_DIVIDER{1}; // you can increase this value to get better PWM resolution.
static constexpr uint16_t TIMER_TOP_VALUE{SYSTEM_CLOCK / ((PWM_FREQUENCY + 1) * CLOCK_DIVIDER)};
