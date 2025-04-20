CC=clang
OPTLEVEL=-O3 -funroll-loops -ffast-math -march=native  
CFLAGS=-O3 -g  -Wall
VERSION ?= NONE

OBJS_COMMON=kernel.o rdtsc.o

all: check calibrate measure

check: $(OBJS_COMMON) driver_check.o
	$(CC) -lm -o $@ $^

calibrate: $(OBJS_COMMON) driver_calib.o
	$(CC) -lm -o $@ $^

measure: $(OBJS_COMMON) driver.o
	$(CC) -lm -o $@ $^

driver_check.o: driver_check.c
	$(CC) $(CFLAGS) -D$(VERSION) -D CHECK -c $< -o $@

driver_calib.o: driver_calib.c
	$(CC) $(CFLAGS) -D$(VERSION) -D CALIB -c $< -o $@

driver.o: driver.c
	$(CC) $(CFLAGS) -D$(VERSION) -c $< -o $@

kernel.o: kernel.c
	$(CC) $(CFLAGS) -D$(VERSION) -c $< -o $@

rdtsc.o: rdtsc.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o check calibrate measure

.PHONY: all clean check calibrate measure
