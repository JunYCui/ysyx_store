#include <am.h>
#include <stdint.h>
#include <riscv/riscv.h>

#define DEVICE_BASE 0xa0000000
#define RTC_ADDR  (DEVICE_BASE + 0x0000048)

static uint64_t read_time() {
  uint32_t hi = inl(RTC_ADDR+4);
  uint32_t lo = inl(RTC_ADDR);
  uint64_t time = ((uint64_t)hi << 32) + lo;
  return time;
}
static uint64_t time =0;

void __am_timer_init() {
  time = 0;
}

void __am_timer_uptime(AM_TIMER_UPTIME_T *uptime) {
  uptime->us = read_time() - time;
}

void __am_timer_rtc(AM_TIMER_RTC_T *rtc) {
  rtc->second = 0;
  rtc->minute = 0;
  rtc->hour   = 0;
  rtc->day    = 0;
  rtc->month  = 0;
  rtc->year   = 1900;
}
