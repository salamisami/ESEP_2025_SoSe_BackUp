#include "HAL.h"

#include <iostream>
#include <stdint.h>
#include <sys/mman.h>
#include <hw/inout.h>
#include <sys/neutrino.h>

// register description:
// spruh73l.pdf page 4877
#define GPIO_SETDATAOUT 0x194
#define GPIO_CLEARDATAOUT 0x190

#define GPIO_0 0x44E07000  //page 180
#define GPIO_1 0x4804C000  //page 182
#define GPIO_2 0x481AC000  //page 183
#define GPIO_3 0x481AE000  //page 183

//GPIO_1
#define MOTOR_RIGHT_BIT     12
#define MOTOR_LEFT_BIT      13
#define MOTOR_SLOW_BIT      14
#define MOTOR_STOP_BIT      15
#define TRAFFIC_RED_BIT     16
#define TRAFFIC_YELLOW_BIT  17
#define TRAFFIC_GREEN_BIT   18
#define SORTING_BIT         19

//GPIO_2
#define LED_START_BIT       2
#define LED_RESET_BIT       3
#define LED_Q1_BIT          4
#define LED_Q2_BIT          5

#define SIZE   0x0FFF      //based on GPIO address range, see above

//===================== contructors & destructors =====================

HAL::HAL()
    :gpio_bank_0(mmap_device_io(SIZE, (uint64_t) (GPIO_0)))
    , gpio_bank_1(mmap_device_io(SIZE, (uint64_t) (GPIO_1)))
    , gpio_bank_2(mmap_device_io(SIZE, (uint64_t) (GPIO_2)))
    , gpio_bank_3(mmap_device_io(SIZE, (uint64_t) (GPIO_3))) {
    // request IO privileges (without this code, the code works too. What's the explanation?)
    ThreadCtl(_NTO_TCTL_IO, 0);
}

HAL::~HAL() {
    if(gpio_bank_0) {
        munmap_device_io(gpio_bank_0, SIZE);
    }
    if(gpio_bank_1) {
        munmap_device_io(gpio_bank_1, SIZE);
    }
    if(gpio_bank_2) {
        munmap_device_io(gpio_bank_2, SIZE);
    }
    if(gpio_bank_3) {
        munmap_device_io(gpio_bank_3, SIZE);
    }
}


//========================= private functions =========================

void HAL::set_data(uintptr_t gpio_bank, uint32_t bit) {
    uint32_t port = (1 << bit);
    out32((uintptr_t) (gpio_bank + GPIO_SETDATAOUT), port);
}

void HAL::clear_data(uintptr_t gpio_bank, uint32_t bit) {
    uint32_t port = (1 << bit);
    out32((uintptr_t) (gpio_bank + GPIO_CLEARDATAOUT), port);
}

//========================= public functions =========================

//GPIO_1

void HAL::motor_right_on() {
    set_data(gpio_bank_1, MOTOR_RIGHT_BIT);
}

void HAL::motor_right_off() {
    clear_data(gpio_bank_1, MOTOR_RIGHT_BIT);
}

void HAL::motor_left_on() {
    set_data(gpio_bank_1, MOTOR_LEFT_BIT);
}

void HAL::motor_left_off() {
    clear_data(gpio_bank_1, MOTOR_LEFT_BIT);
}

void HAL::motor_slow_on() {
    set_data(gpio_bank_1, MOTOR_SLOW_BIT);
}

void HAL::motor_slow_off() {
    clear_data(gpio_bank_1, MOTOR_SLOW_BIT);
}

void HAL::motor_stop_on() {
    set_data(gpio_bank_1, MOTOR_STOP_BIT);
}

void HAL::motor_stop_off() {
    clear_data(gpio_bank_1, MOTOR_STOP_BIT);
}

void HAL::traffic_red_on() {
    set_data(gpio_bank_1, TRAFFIC_RED_BIT);
}

void HAL::traffic_red_off() {
    clear_data(gpio_bank_1, TRAFFIC_RED_BIT);
}

void HAL::traffic_yellow_on() {
    set_data(gpio_bank_1, TRAFFIC_YELLOW_BIT);
}

void HAL::traffic_yellow_off() {
    clear_data(gpio_bank_1, TRAFFIC_YELLOW_BIT);
}

void HAL::traffic_green_on() {
    set_data(gpio_bank_1, TRAFFIC_GREEN_BIT);
}

void HAL::traffic_green_off() {
    clear_data(gpio_bank_1, TRAFFIC_GREEN_BIT);
}

void HAL::sorting_on() {
    set_data(gpio_bank_1, SORTING_BIT);
}

void HAL::sorting_off() {
    clear_data(gpio_bank_1, SORTING_BIT);
}

//GPIO_2

void HAL::led_start_on() {
    set_data(gpio_bank_2, LED_START_BIT);
}

void HAL::led_start_off() {
    clear_data(gpio_bank_2, LED_START_BIT);
}

void HAL::led_reset_on() {
    set_data(gpio_bank_2, LED_RESET_BIT);
}

void HAL::led_reset_off() {
    clear_data(gpio_bank_2, LED_RESET_BIT);
}

void HAL::led_q1_on() {
    set_data(gpio_bank_2, LED_Q1_BIT);
}

void HAL::led_q1_off() {
    clear_data(gpio_bank_2, LED_Q1_BIT);
}

void HAL::led_q2_on() {
    set_data(gpio_bank_2, LED_Q2_BIT);
}

void HAL::led_q2_off() {
    clear_data(gpio_bank_2, LED_Q2_BIT);
}
