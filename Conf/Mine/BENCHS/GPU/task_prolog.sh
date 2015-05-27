#!/bin/sh


echo $SLURM_TASK_PID > /tmp/test
cat /cgroup/cpuset/slurm/uid_0/job_261/step_0/cpus >> /tmp/test
export CUDA_VISIBLE_DEVICES=1
export OMPI_MCA_btl_openib_if_include="mlx4_1"
export >> /tmp/test
###/home_nfs/georgioy/BENCHS/GPU/osu_bw H D

