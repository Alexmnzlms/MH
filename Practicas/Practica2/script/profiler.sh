#!/bin/bash

make -B


bin/clustering_exe 1 3 AGG_UN

gprof bin/clustering_exe gmon.out > profiler/profilingAGG_UN.txt

bin/clustering_exe 1 3 AGG_SF

gprof bin/clustering_exe gmon.out > profiler/profilingAGG_SF.txt
