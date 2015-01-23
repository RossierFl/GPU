#! /bin/bash
n_secondes=10
( cbirt gl ./cuda_conv_dg16_db256.run >> cuda_conv_dg16_db256.csv ) &
sleep $n_secondes
#kill $!
read -p "Press any key..."

n_secondes=10
( cbirt gl ./cuda_conv_dg16_db512.run >> cuda_conv_dg16_db512.csv ) &
sleep $n_secondes
read -p "Press any key..."

n_secondes=10
( cbirt gl ./cuda_conv_dg32_db256.run >> cuda_conv_dg32_db256.csv ) &
sleep $n_secondes
read -p "Press any key..."

n_secondes=10
( cbirt gl ./cuda_conv_dg32_db512.run >> cuda_conv_dg32_db512.csv ) &
sleep $n_secondes
read -p "Press any key..."


n_secondes=10
( cbirt gl ./omp_conv_12threads.run >> omp_conv_12threads.csv) &
sleep $n_secondes
read -p "Press any key..."

n_secondes=10
( cbirt gl ./cuda_conv_dg16_db32.run >> cuda_conv_dg16_db32.csv ) &
sleep $n_secondes
read -p "Press any key..."

n_secondes=10
( cbirt gl ./cuda_conv_dg1_db1.run >> cuda_conv_dg1_db1.csv ) &
sleep $n_secondes
read -p "Press any key..."

n_secondes=10
( cbirt gl ./cuda_conv_dg32_db32.run >> cuda_conv_dg32_db32.csv ) &
sleep $n_secondes
read -p "Press any key..."

n_secondes=10
( cbirt gl ./cuda_conv_dg32_db32.run >>  omp_conv_12threads_intel.csv) &
sleep $n_secondes
read -p "Press any key..."

n_secondes=10
( cbirt gl ./omp_conv_1threads.run >>  omp_conv_1threads.csv) &
sleep $n_secondes
read -p "Press any key..."
