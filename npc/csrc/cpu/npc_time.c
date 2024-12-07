#include <time.h>
#include <npc_common.h>

static uint64_t bool_time; 
static uint64_t get_time_internal() {
    struct timespec now;
    clock_gettime(CLOCK_MONOTONIC_COARSE, &now);
    uint64_t us = now.tv_sec * 1000000 + now.tv_nsec / 1000;

    return us;
}

uint64_t get_time() {
  if (bool_time == 0) bool_time = get_time_internal();
  uint64_t now = get_time_internal();
  return now - bool_time;
}

