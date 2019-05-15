#include <stdint.h>
#include <stdio.h>
#include "benchmark.h"

#ifdef __cplusplus
  #include "lua.hpp"
#else
  #include "lua.h"
  #include "lualib.h"
  #include "lauxlib.h"
#endif

#ifdef __MACH__
  #include <mach/mach.h>
  #include <mach/clock.h>
#else
  #include <time.h>
  #include <sys/time.h>
#endif

#ifdef __cplusplus
extern "C"{
#endif

uint64_t rdtsc(){
    unsigned int lo,hi;
    __asm__ __volatile__ ("rdtsc" : "=a" (lo), "=d" (hi));
    return ((uint64_t)hi << 32) | lo;
}

NANO nano_return_t nano_timespec(struct timespec *now)
{
#ifdef __MACH__
    clock_serv_t clock_service;
    mach_timespec_t mach_time;

    if (host_get_clock_service(mach_host_self(), CALENDAR_CLOCK, &clock_service) != 0) {
        return NANO_FAILURE;
    }

    if (clock_get_time(clock_service, &mach_time) != 0) {
        return NANO_FAILURE;
    }

    if (mach_port_deallocate(mach_task_self(), clock_service) != 0) {
        return NANO_FAILURE;
    }

    now->tv_sec = mach_time.tv_sec;
    now->tv_nsec = mach_time.tv_nsec;
#else
    if (clock_gettime(CLOCK_REALTIME, now) != 0) {
        return NANO_FAILURE;
    }
#endif

    return NANO_SUCCESS;
}

static int lua_rdtsc(lua_State *L) {
    lua_pushnumber(L, (double) rdtsc());
    return 1;
}

static int lua_nano_second(lua_State *L) {
    struct timespec now;
    if (NANO_UNEXPECTED(nano_timespec(&now))) {
        lua_pushnumber(L, 0);
    } else {
        lua_pushnumber(L, (double) now.tv_nsec);
    }
    return 1;
}

static const struct luaL_Reg benchmark [] = {
    {"rdtsc", lua_rdtsc},
    {"ns", lua_nano_second},
    {NULL, NULL}
};

int luaopen_benchmark (lua_State *L) {
    luaL_newlib(L, benchmark);
    return 1;
}

#ifdef __cplusplus
}
#endif

