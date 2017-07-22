#pragma once
#include <istream>
#include <ostream>
#include <vector>

#define BUFFER_LENGTH 2048
#define GET_BIT(byte, i) ((byte) & (1 << (i)))
#define SET_BIT(byte, i) ((byte) |= (1 << (i)))
#define CLS_BIT(byte, i) ((byte) &= (~(1 << (i))))
