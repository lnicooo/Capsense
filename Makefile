CC = avr-gcc
LD = avr-objcopy
DU = avrdude
TARGET = main
UART = uart/uart

MU=atmega328p
CPU_CK=16000000
PORT = /dev/ttyUSB0
BAUD = 115200


all:
	$(CC) -Os -DF_CPU=$(CPU_CK)UL -mmcu=$(MU) -c -o $(TARGET).o $(TARGET).c
	$(CC) -Os -DF_CPU=$(CPU_CK)UL -mmcu=$(MU) -c -o $(UART).o $(UART).c
	$(CC) -mmcu=$(MU) $(TARGET).o $(UART).o -o $(TARGET)
	$(LD) -O ihex -R .eeprom $(TARGET) $(TARGET).hex

flash:
	$(DU) -F -V -c arduino -p ATMEGA328P -P $(PORT) -b $(BAUD) -U flash:w:$(TARGET).hex
