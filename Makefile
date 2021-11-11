FLAGS = -mmcu=attiny13a -DF_CPU=4800000UL -Os -std=c99

all: blink.hex

%.hex: %.elf
	avr-objcopy -O ihex $< $@

clean:
	rm -f *.elf *.hex

%.elf: %.c hsv_rgb.c
	avr-gcc $(FLAGS) $^ -o $@
	avr-size -C --mcu=attiny13a $@
