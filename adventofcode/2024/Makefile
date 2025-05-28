# CFLAGS ?= -g

all: day-01 day-02 day-03

day-01: day-01.c libs/utils.c
	cc $(CFLAGS) -o build/day-01 day-01.c libs/utils.c

day-02: day-02.c
	cc $(CFLAGS) -o build/day-02 day-02.c

day-03: day-03.c
	cc $(CFLAGS) -o build/day-03 day-03.c libs/utils.c

day-04: day-04.c
	cc $(CFLAGS) -o build/day-04 day-04.c libs/utils.c

day-04-2: day-04-2.c
	cc $(CFLAGS) -o build/day-04-2 day-04-2.c libs/utils.c

day-05: day-05.c
	cc $(CFLAGS) -o build/day-05 day-05.c libs/utils.c

day-06: day-06.c
	cc $(CFLAGS) -o build/day-06 day-06.c libs/utils.c

day-07: day-07.c
	cc $(CFLAGS) -o build/day-07 day-07.c libs/utils.c

day-08: day-08.c
	cc $(CFLAGS) -o build/day-08 day-08.c libs/utils.c

day-09: day-09.c
	cc $(CFLAGS) -o build/day-09 day-09.c libs/utils.c

day-10: day-10.c
	cc $(CFLAGS) -o build/day-10 day-10.c libs/utils.c

day-11: day-11.c
	cc $(CFLAGS) -o build/day-11 day-11.c libs/utils.c

day-11-2: day-11-2.c
	cc $(CFLAGS) -o build/day-11-2 day-11-2.c libs/utils.c

day-12: day-12.c
	cc $(CFLAGS) -o build/day-12 day-12.c libs/utils.c

run: day-${day}
	"./build/day-${day}" "inputs/day-${day}.txt"
