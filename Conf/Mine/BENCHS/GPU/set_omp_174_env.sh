
#diver
export OMPI_MCA_btl_sm_use_knem="0"
export OMPI_MCA_mpi_common_cuda_verbose="10" 
export OMPI_MCA_opal_cuda_verbose="10"  


#GPU DIRECT RDMA control
export OMPI_MCA_btl_openib_cuda_rdma_limit="100000000"
export OMPI_MCA_btl_openib_want_cuda_gdr="1"

export OMPI_MCA_hwloc_base_report_bindings="1"
export OMPI_MCA_rmaps_lama_bind="c"
export OMPI_MCA_btl_openib_verbose="100"
export OMPI_MCA_btl_openib_cpc_include="rdmacm"
