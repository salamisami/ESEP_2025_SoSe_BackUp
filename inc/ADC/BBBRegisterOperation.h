/*
 * BBBRegisterOperation.h
 *
 *  Created on: 08.05.2025
 *      Author: robin
 */

#ifndef BBBREGISTEROPERATION_H_
#define BBBREGISTEROPERATION_H_

#include <hw/inout.h>
#include <stdint.h>

inline void setBitsInReg(uintptr_t addr, uint32_t mask) {
    out32(addr, in32(addr) | mask);
}

inline void clearBitsInReg(uintptr_t addr, uint32_t mask) {
    out32(addr, in32(addr) & ~mask);
}



#endif /* BBBREGISTEROPERATION_H_ */
