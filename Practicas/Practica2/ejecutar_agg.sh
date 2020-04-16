#!/bin/bash

make -B

bin/clustering_exe 5 0 AGG_UN > result/AGG_UN_result &
bin/clustering_exe 5 0 AGG_SF > result/AGG_SF_result &
#bin/clustering_exe 5 3 AGE_UN > result/AGE_UN_result &
#bin/clustering_exe 5 3 AGE_SF > result/AGE_SF_result &

wait
