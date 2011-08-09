/*
 * Milkymist SoC (Software)
 * Copyright (C) 2007, 2008, 2009, 2010, 2011 Sebastien Bourdeauducq
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <uart.h>
#include <irq.h>
#include <hw/sysctl.h>
#include <hw/gpio.h>
#include <hw/flash.h>

#include <hal/vga.h>
#include <hal/tmu.h>
#include <hal/brd.h>
#include <hal/usb.h>
#include <hal/ukb.h>

extern int main( int argc, const char* argv[] );

int rescue;

int init()
{
	CSR_GPIO_OUT = GPIO_LED1;
	rescue = !((unsigned int)main > FLASH_OFFSET_REGULAR_BIOS);

	irq_setmask(0);
	irq_enable(1);
	uart_init();
	vga_init(!(rescue || (CSR_GPIO_IN & GPIO_BTN2)));
	brd_init();
	tmu_init(); 
	usb_init();
	ukb_init();

        return main(0, (const char **) 0);
}
