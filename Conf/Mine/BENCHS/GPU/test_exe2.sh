#!/bin/sh
export CUDA_VISIBLE_DEVICES=1
export OMPI_MCA_btl_openib_if_include="mlx4_1"
/home_nfs/georgioy/BENCHS/GPU/osu_bw H D
