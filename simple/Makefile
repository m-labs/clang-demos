#
# This was derived from the the lm32 qemu test code.
#


SIM = qemu-system-lm32
SIMFLAGS = -M lm32-evr -nographic -device lm32-sys -net none -kernel

CROSS=lm32-rtems4.11-
#CC      = $(CROSS)gcc
CC	= /Users/jpbonn/Documents/mico32/install2/bin/clang -march=mico32 -ccc-host-triple mico32-elf -ccc-gcc-name /opt/rtems-4.11/bin/lm32-rtems4.11-gcc
AS      = $(CROSS)as
AS      = $(CC) -x assembler
SIZE    = $(CROSS)size
LD      = $(CC)
OBJCOPY = $(CROSS)objcopy

CFLAGS+= -nostdinc -Wall -mbarrel-shift-enabled -mmultiply-enabled -mdivide-enabled -msign-extend-enabled -fno-builtin -fsigned-char -fsingle-precision-constant
LDFLAGS = -Tlinker.ld
NOSTDFLAGS = -nostdinc -nostdlib -nodefaultlibs

CRT        = crt.o
#TESTCASE	= main.tst

all: build

%.o: $(SRC_PATH)/tests/lm32/%.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: $(SRC_PATH)/tests/lm32/%.S
	$(AS) $(ASFLAGS) -c $< -o $@

%.tst: %.o macros.inc $(CRT)
	$(LD) $(LDFLAGS) $(NOSTDFLAGS) $(CRT) $< -o $@

build: $(CRT) $(TESTCASE)

check: $(CRT) $(SYS) $(TESTCASE)
		$(SIM) $(SIMFLAGS) $(TESTCASE)

clean:
	$(RM) -fr $(TESTCASE) $(CRT)
