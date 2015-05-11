
#diver
export OMPI_MCA_btl_sm_use_knem="0"
export OMPI_MCA_mpi_common_cuda_verbose="10" 
export OMPI_MCA_opal_cuda_verbose="10"  


#GPU DIRECT RDMA control
export OMPI_MCA_btl_openib_cuda_rdma_limit="100000000"
export OMPI_MCA_btl_openib_cuda_want_gdr_support="1" 
#export OMPI_MCA_btl_openib_if_include="mlx4_0" 




