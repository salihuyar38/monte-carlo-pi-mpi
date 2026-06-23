#!/bin/bash

POINTS=100000000
OUTPUT=results.csv

gcc montecarlo_serial.c -o montecarlo_serial -lm
mpicc montecarlo_mpi.c -o montecarlo_mpi -lm

echo "version,processes,points,pi,error,runtime,compute_time,reduce_time" > $OUTPUT

echo "Running serial version..."
./montecarlo_serial $POINTS >> $OUTPUT

for p in 1 2 4 8
do
    echo "Running MPI with $p processes..."
    mpirun -np $p ./montecarlo_mpi $POINTS | awk -F',' '{print "mpi," $1 "," $2 "," $3 "," $4 "," $5 "," $6 "," $7}' >> $OUTPUT
done

echo "Results written to $OUTPUT"