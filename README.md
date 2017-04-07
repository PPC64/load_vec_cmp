# load_vec_cmp

This project aims to compare performance between lvx and lxvd2x. Two scenarios are used to make this analysis: aligned memory
and unaligned memory.

In order to run the analysis locally, clone this repository and run:

``
make perf
``

To run on a dedicated cpu and have a more reliable result, use the following command:

``
taskset -ac 0 make perf
``
