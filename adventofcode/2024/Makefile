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

run: day-${day}
	"./build/day-${day}" "inputs/day-${day}.txt"
