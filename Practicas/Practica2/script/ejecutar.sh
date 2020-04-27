#!/bin/bash

make -B

echo 'Ejecutando greedy...'
bin/clustering_exe 5 0 G > result/TotalP1_G_result &
echo 'Ejecutando BL...'
bin/clustering_exe 5 0 BL > result/TotalP1_BL_result &

wait
