#!/bin/bash

make -B

# bin/clustering_exe -1 3 AM_10-1.0 > graph/AM_10-10_Ecoli_graph &
# bin/clustering_exe -1 3 AM_10-0.1 > graph/AM_10-01_Ecoli_graph &
# bin/clustering_exe -1 3 AM_10-0.1mej > graph/AM_10-01mej_Ecoli_graph &

bin/clustering_exe -1 3 AGG_UN > graph/AGG_UN_Ecoli_graph &
bin/clustering_exe -1 3 AGG_SF > graph/AGG_SF_Ecoli_graph &
bin/clustering_exe -1 3 AGE_UN > graph/AGE_UN_Ecoli_graph &
bin/clustering_exe -1 3 AGE_SF > graph/AGE_SF_Ecoli_graph &
bin/clustering_exe -1 3 BL > graph/BL_Ecoli_graph &

wait
