/* Simple demostration of the gpio access
 * @author: Franz Korf
 * @author: Thomas Lehmann
 * @date: 2022-03-18
 * @date: 2020-04-24
 */

#include <iostream>
#include <stdint.h>
#include <sys/mman.h>
#include <hw/inout.h>
#include <sys/neutrino.h>

int main() {
	std::cout << "Hello World!!!" << std::endl; // prints Hello World!!!

	// request IO privileges
	ThreadCtl( _NTO_TCTL_IO, 0);

	uintptr_t gpio_bank_1 = mmap_device_io(0x1000, (uint64_t) 0x4804C000);

	// register description:
	// spruh73l.pdf page 4877

	std::cout << "Switch traffic light on" << std::endl;
	out32((uintptr_t) (gpio_bank_1 + 0x194), 0x00010000); // set register

	usleep(1000 * 500);

	std::cout << "Switch traffic light off" << std::endl;
	out32((uintptr_t) (gpio_bank_1 + 0x190), 0x00010000); // clear register

	return 0;
}
