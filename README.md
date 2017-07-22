# Memory Management in Linux Kernel

The tester files for part 1 and 2 can be found in the `/test` directory.

## Part 1

#### Compile & Run

1. `gcc test_memstats.c -o memstats`
2. `./memstats`

## Part 2

#### Compile & Run

1. `gcc test_algorithms.c -o algo`
2. `./algo`

#### Trigger counter-based clock page replacement algorithm

You can easily trigger on and off the algorithm by updating the `IS_COUNTER_BASED_CLOCK` variable defined in `vmscan.c`.

> NOTE: This would require you to recompile and reboot the kernel. You can do this by using either `compile.sh` or `full_compile.sh`