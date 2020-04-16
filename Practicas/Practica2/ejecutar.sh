#!/bin/bash

make -B

bin/clustering_exe 1 0 G > result/G_result &
bin/clustering_exe 1 0 BL > result/BL_result &

wait

bin/clustering_exe 1 0 AGG_UN > result/AGG_UN_result &
bin/clustering_exe 1 0 AGG_SF > result/AGG_SF_result &
bin/clustering_exe 1 0 AGE_UN > result/AGE_UN_result &
bin/clustering_exe 1 0 AGE_SF > result/AGE_SF_result &

wait

bin/clustering_exe 1 0 AM_10-1.0 > result/AM_10-10_result &
bin/clustering_exe 1 0 AM_10-0.1 > result/AM_10-01_result &
bin/clustering_exe 1 0 AM_10-0.1mej > result/AM_10-01mej_result &

wait
