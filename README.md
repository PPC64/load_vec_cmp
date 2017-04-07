# load_vec_cmp

This project aims to compare performance between lvx and lxvd2x. Two scenarios are used to make this analysis: aligned array
and unaligned array.

In order to run the analysis locally, clone this repository and run:

``
make perf
``

To run on a dedicated cpu and have a more reliable result, use the following command:

``
taskset -ac 0 make perf
``

As an example, see the image below generated locally using the command above.

![Compare Results](https://raw.githubusercontent.com/igorsnunes/load_vec_cmp/master/doc/LoadVecCompare.png) 

As it can be seen, lxvd2x on a unaligned array is the worst scenario. 
