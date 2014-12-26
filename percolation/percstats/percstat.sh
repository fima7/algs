#!/bin/bash

OUTFILE=$1

echo "				Threshold 			Time" >  $OUTFILE
echo "UnionFind, T, size, mean, stddev, confidence interval, mean, stddev, confidence interval" >> $OUTFILE

for ((i=2; i <= 2048; i*=2 )) 
do
	echo "Percolation for $i"
	./percstat 200 100 >> $OUTFILE
done
