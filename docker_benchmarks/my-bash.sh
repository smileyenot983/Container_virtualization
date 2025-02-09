#!/bin/bash
set -e

echo "Benchmark..."

#echo "__________________CPU___________________"
#sysbench cpu --cpu-max-prime=20000 run
#echo "_____________Memory___________________"
#sysbench memory run
#echo "_____________FILEIO__________________"
#sysbench fileio --num-threads=16 --file-total-size=20G --file-test-mode=rndrw prepare
#sysbench fileio --num-threads=16 --file-total-size=20G --file-test-mode=rndrw run
#sysbench fileio --num-threads=16 --file-total-size=20G --file-test-mode=rndrw cleanup
echo "________________Threads_____________________"
sysbench threads --num-threads=64 --thread-yields=100 --thread-locks=2 run
