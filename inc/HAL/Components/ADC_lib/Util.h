#ifndef UTIL_H
#define UTIL_H

// for Error
#include <cstdio>

// for wait
#include <thread>
#include <chrono>


#define DBG_ERROR(err) std::perror(err);

#define _BV(x) (1<<(x))

#endif
