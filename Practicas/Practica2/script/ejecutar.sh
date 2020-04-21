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
echo 'Ejecutando AGG_SF...'
bin/clustering_exe 5 0 AGG_SF > result/Total_AGG_SF_result &
# echo 'Ejecutando AGE_UN...'
# bin/clustering_exe 5 0 AGE_UN > result/Total_AGE_UN_result &
echo 'Ejecutando AGE_SF...'
bin/clustering_exe 5 0 AGE_SF > result/Total_AGE_SF_result &
#
wait
# echo 'Terminado bloque, se procede al siguiente'
#
# echo 'Ejecutando AM 1.0'
# bin/clustering_exe 5 0 AM_10-1.0 > result/Total_AM10_result &
# echo 'Ejecutando AM 0.1'
# bin/clustering_exe 5 0 AM_10-0.1 > result/Total_AM01_result &
# echo 'Ejecutando AM 0.1 mejor'
# bin/clustering_exe 5 0 AM_10-0.1mej > result/Total_AM01MEJ_result &
#
# wait
#
# poweroff
