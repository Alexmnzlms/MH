#!/bin/bash

make -B


bin/clustering_exe 1 3 AM_10-1.0

gprof bin/clustering_exe gmon.out > profiler/profilingAM1010.txt

bin/clustering_exe 1 3 AM_10-0.1

gprof bin/clustering_exe gmon.out > profiler/profilingAM1001.txt
