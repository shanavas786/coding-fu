# CFLAGS ?= -g

all: day-01 day-02 day-03

day-01: day-01.c libs/utils.c
	cc $(CFLAGS) -o build/day-01 day-01.c libs/utils.c

day-02: day-02.c
	cc $(CFLAGS) -o build/day-02 day-02.c

day-03: day-03.c
	cc $(CFLAGS) -o build/day-03 day-03.c libs/utils.c

run: all
	"./build/day-${day}" "inputs/day-${day}.txt"
