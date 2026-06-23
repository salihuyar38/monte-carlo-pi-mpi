Build

Compile the serial version:

gcc montecarlo_serial.c -o montecarlo_serial -lm

Compile the MPI version:

mpicc montecarlo_mpi.c -o montecarlo_mpi -lm
Run

Serial execution:

./montecarlo_serial 100000000

MPI execution:

mpirun -np 4 ./montecarlo_mpi 100000000
Automated Benchmarking

Run all benchmarks:

chmod +x run_benchmarks.sh
./run_benchmarks.sh

The benchmark executes:

Serial version
MPI with 1 process
MPI with 2 processes
MPI with 4 processes
MPI with 8 processes

Results are written to:

results.csv

Analysis

Generate speedup and efficiency metrics:

python3 analyze_results.py

Generated files:

results_analyzed.csv
runtime.png
speedup.png
efficiency.png

Benchmark Results

The benchmark was executed using 100,000,000 random points.

Version	Processes	Runtime (s)	Speedup	Efficiency
Serial	1	1.382	1.00	1.00
MPI	1	    1.373   1.01	1.01
MPI	2	    0.849	1.63	0.81
MPI	4	    0.381   3.63	0.91
MPI	8	    0.295	4.69	0.59

Observations
The MPI implementation achieves approximately 4.69× speedup with 8 processes.
The best efficiency was observed with 4 processes (90.7%).
Runtime decreases significantly as additional processes participate in the computation.
Efficiency decreases at higher process counts due to communication and synchronization overhead.
Monte Carlo simulation scales well because the workload is largely independent and requires very little communication.

Performance Plots

After running the analysis script, the following plots are generated:

Runtime
![Runtime](results/runtime.png)
Speedup
![Speedup](results/speedup.png)
Efficiency
![Efficiency](results/efficiency.png)