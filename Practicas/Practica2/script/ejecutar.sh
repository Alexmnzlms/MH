#!/bin/bash

make -B

# echo 'Ejecutando greedy...'
# bin/clustering_exe 5 0 G > result/Total_G_result &
# echo 'Ejecutando BL...'
# bin/clustering_exe 5 0 BL > result/Total_BL_result &
#
# wait
# echo 'Terminado bloque, se procede al siguiente'
#
# echo 'Ejecutando AGG_UN...'
# bin/clustering_exe 5 0 AGG_UN > result/Total_AGG_UN_result &
# echo 'Ejecutando AGG_SF...'
# bin/clustering_exe 5 0 AGG_SF > result/Total_AGG_SF_result &
# echo 'Ejecutando AGE_UN...'
# bin/clustering_exe 5 0 AGE_UN > result/Total_AGE_UN_result &
# echo 'Ejecutando AGE_SF...'
# bin/clustering_exe 5 0 AGE_SF > result/Total_AGE_SF_result &
#
# wait
# echo 'Terminado bloque, se procede al siguiente'
#
# echo 'Ejecutando AM 1.0...'
# bin/clustering_exe 5 0 AM_10-1.0 > result/Total_AM10_result &
# echo 'Ejecutando AM 0.1...'
# bin/clustering_exe 5 0 AM_10-0.1 > result/Total_AM01_result &
# echo 'Ejecutando AM 0.1 mejor...'
# bin/clustering_exe 5 0 AM_10-0.1mej > result/Total_AM01MEJ_result &
#
# wait
#
# echo 'Graficando geneticos...'
# bin/clustering_exe 0 3 AGG_UN > graph/AGG_UN_Ecoli_graph &
# bin/clustering_exe 0 3 AGG_SF > graph/AGG_SF_Ecoli_graph &
# bin/clustering_exe 0 3 AGE_UN > graph/AGE_UN_Ecoli_graph &
# bin/clustering_exe 0 3 AGE_SF > graph/AGE_SF_Ecoli_graph &
#
# wait
#
# echo 'Graficando memeticos...'
# bin/clustering_exe 0 3 AM_10-1.0 > graph/AM_10-10_Ecoli_graph &
# bin/clustering_exe 0 3 AM_10-0.1 > graph/AM_10-01_Ecoli_graph &
# bin/clustering_exe 0 3 AM_10-0.1mej > graph/AM_10-01mej_Ecoli_graph &
#
# wait
#
# poweroff


echo 'Ejecutando AGG_SF...'
bin/clustering_exe 5 0 AGG_SF > result/Total_0_AGG_SF_result &
echo 'Ejecutando AGE_SF...'
bin/clustering_exe 5 0 AGE_SF > result/Total_0_AGE_SF_result &
bin/clustering_exe 0 3 AGG_UN > graph/AGG_UN_0_Ecoli_graph &
bin/clustering_exe 0 3 AGG_SF > graph/AGG_SF_0_Ecoli_graph &

wait

sed -i 's/int n = 0/int n = 1/g' include/cc.h
echo 'Ejecutando AGG_SF...'
bin/clustering_exe 5 0 AGG_SF > result/Total_1_AGG_SF_result &
echo 'Ejecutando AGE_SF...'
bin/clustering_exe 5 0 AGE_SF > result/Total_1_AGE_SF_result &
bin/clustering_exe 0 3 AGG_UN > graph/AGG_UN_1_Ecoli_graph &
bin/clustering_exe 0 3 AGG_SF > graph/AGG_SF_1_Ecoli_graph &

wait

sed -i 's/int n = 1/int n = 0/g' include/cc.h
