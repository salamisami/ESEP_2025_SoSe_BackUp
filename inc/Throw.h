#ifndef THROW_H
#define THROW_H
#pragma once

#include <stdexcept>
#include <string>

#define THROW(msg) throw std::runtime_error(std::string(__FUNCTION__) + ": " + msg)


#endif
