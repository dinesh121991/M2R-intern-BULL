/** TODO: copyright notice */

#include "slurm/slurm.h"

#include "src/common/layouts_mgr.h"
#include "src/common/layout.h"
#include "src/common/entity.h"
#include "src/common/log.h"
/*#include "src/common/slurm_topology.h"
#include "src/common/xmalloc.h"


#if defined (__APPLE__)
int switch_levels __attribute__((weak_import));
struct switch_record *switch_record_table __attribute__((weak_import));
int switch_record_cnt __attribute__((weak_import));
#else
int switch_levels;
struct switch_record *switch_record_table;
int switch_record_cnt;
#endif*/

#define L_SELECTED_NODE_CNT "SelectedNodeCountInLevel-"
#define L_SELECTED_CPU_CNT "SelectedCpuCountInLevel-"
#define L_ALLOCATED_CPU_CNT "AllocatedCpuCountInLevel-"
#define L_NUM_CPU_CNT "NumCpuCountInLevel-"

#define L_NUM_NODE_CNT "NumNodeCountInLevel-"
#define L_NUM_SOCKET_CNT "NumSocketCountInLevel-"
#define L_NUM_CORE_CNT "NumCoreCountInLevel-"
#define L_ALLOCATED_NODE_CNT "NumNodeCountInLevel-"
#define L_ALLOCATED_SOCKET_CNT "NumSocketCountInLevel-"
#define L_ALLOCATED_CORE_CNT "NumCoreCountInLevel-"

int i;

const char plugin_name[] = "Consumable resources layout(CRL) partition plugin";
const char plugin_type[] = "layouts/cons_res_partition";
const uint32_t plugin_version = 100;

s_p_options_t entity_options[] = {
	/* base keys */
	{"BitmapPosition", S_P_UINT32},  // Bitmap position or Array Index correlation, This is used for conversion from Layout to Bitmap
//	{"Selected", S_P_BOOLEAN},
	{"AllocatedNodeCount",S_P_UINT32}, // Selected,Allocated separate list is possible
	{"AllocatedSocketCount",S_P_UINT32},
	{"AllocatedCoreCount",S_P_UINT32},
	
	/* Non-Aggregated keys and used for aggregation */
	{"nodecount",S_P_UINT32},  // It is for SUM from child , And it shoud be "1"
	{"socketcount",S_P_UINT32},  // It is for SUM from child , And it shoud be "1"
	{"corecount",S_P_UINT32},  // It is for SUM from child , And it shoud be "1"
	{"ThreadsPerCore",S_P_UINT32},  // RD_ONLY value never Change.In the core entity only

	/* Selected cores,sockets,nodes information */
	{"SelectedNodeCount",S_P_UINT32}, // Selected,Allocated separate list is possible
	{"SelectedSocketCount",S_P_UINT32},
	{"SelectedCoreCount",S_P_UINT32},

	
//	{"NodeState",S_P_LONG},   // In Node level only. If NodeState is drained change count to zero.
	
//	{"NumParts",S_P_UINT32},   // In root level only, If the LAYOUT_STRUCT_TREE is used partition will not be addable.
//	{"PartitionPriority",S_P_UINT32},   //If Graph struct_type in the Layout use Partition virtual entity
		
//  {"FreeMemory", S_P_UINT32}, // In node level only
	
//	{"ForWhatPurposePriority",S_P_UINT32}, // Fir What reason selected. if we have multiple Reason 
		
	/* After Allocation  */
	
//  {"AllocatedMemory", S_P_UINT32},
//	{"AllocatedJobID", S_P_UINT32},
//	{"JobIdList",S_P_ARRAY},

	/* Parents aggregated keys */
	
	{"NumSumNodes", S_P_UINT32},  // It is in Cluster
	{"NumSumCoresInCluster",S_P_UINT32},
	{"NumSumSocketsInCluster",S_P_UINT32},
	{"NumSumSockets",S_P_UINT32}, // It is in Node
	{"NumSumCoresInNode",S_P_UINT32},
	{"NumSumCores",S_P_UINT32}, //It is in Socket
//  {"NumSumThreadsInCluster",S_P_UINT32}  // If CR_THREAD LEVEL
	
	{"SelectedSumNodes", S_P_UINT32},  // It is in Cluster
	{"SelectedSumCoresInCluster",S_P_UINT32},
	{"SelectedSumSocketsInCluster",S_P_UINT32},
	{"SelectedSumSockets",S_P_UINT32}, // It is in Node
	{"SelectedSumCoresInNode",S_P_UINT32},
	{"SelectedSumCores",S_P_UINT32},	//It is in Socket
	
	{"AllocatedSumNodes", S_P_UINT32},  // It is in Cluster
	{"AllocatedSumCoresInCluster",S_P_UINT32},
	{"AllocatedSumSocketsInCluster",S_P_UINT32},
	{"AllocatedSumSockets",S_P_UINT32}, // It is in Node
	{"AllocatedSumCoresInNode",S_P_UINT32},
	{"AllocatedSumCores",S_P_UINT32}, //It is in Socket

	// topology based Node config
	{"SelectedNodeCount", S_P_UINT32},
	{"SelectedCpuCountInNode",S_P_UINT32},
		
	// topology based configuration
	
	{"NumSumNodesInLevel0", S_P_UINT32},  
	{"NumSumCoresInLevel0",S_P_UINT32},
	{"NumSumSocketsInLevel0",S_P_UINT32},
	{"NumSumCpusInLevel0",S_P_UINT32},
		
	{"SelectedSumNodesInLevel0", S_P_UINT32},  
	{"SelectedSumCoresInLevel0",S_P_UINT32},
	{"SelectedSumSocketsInLevel0",S_P_UINT32},
	{"SelectedSumCpusInLevel0",S_P_UINT32}, 	
	
	{"AllocatedSumNodesInLevel0", S_P_UINT32},  
	{"AllocatedSumCoresInLevel0",S_P_UINT32},
	{"AllocatedSumSocketsInLevel0",S_P_UINT32},
	{"AllocatedSumCpusInLevel0",S_P_UINT32},

	{"NumSumNodesInLevel1", S_P_UINT32},  
	{"NumSumCoresInLevel1",S_P_UINT32},
	{"NumSumSocketsInLevel1",S_P_UINT32},
	{"NumSumCpusInLevel1",S_P_UINT32},
	
	{"SelectedSumNodesInLevel1", S_P_UINT32},  
	{"SelectedSumCoresInLevel1",S_P_UINT32},
	{"SelectedSumSocketsInLevel1",S_P_UINT32},
	{"SelectedSumCpusInLevel1",S_P_UINT32}, 	
	
	{"AllocatedSumNodesInLevel1", S_P_UINT32},  
	{"AllocatedSumCoresInLevel1",S_P_UINT32},
	{"AllocatedSumSocketsInLevel1",S_P_UINT32},
	{"AllocatedSumCpusInLevel1",S_P_UINT32},

	{"NumSumNodesInLevel2", S_P_UINT32},  
	{"NumSumCoresInLevel2",S_P_UINT32},
	{"NumSumSocketsInLevel2",S_P_UINT32},
	{"NumSumCpusInLevel2",S_P_UINT32},
	
	{"SelectedSumNodesInLevel2", S_P_UINT32},  
	{"SelectedSumCoresInLevel2",S_P_UINT32},
	{"SelectedSumSocketsInLevel2",S_P_UINT32},
	{"SelectedSumCpusInLevel2",S_P_UINT32}, 	
	
	{"AllocatedSumNodesInLevel2", S_P_UINT32},  
	{"AllocatedSumCoresInLevel2",S_P_UINT32},
	{"AllocatedSumSocketsInLevel2",S_P_UINT32},
	{"AllocatedSumCpusInLevel2",S_P_UINT32},

	{"NumSumNodesInLevel3", S_P_UINT32},  
	{"NumSumCoresInLevel3",S_P_UINT32},
	{"NumSumSocketsInLevel3",S_P_UINT32},
	{"NumSumCpusInLevel3",S_P_UINT32},
	
	{"SelectedSumNodesInLevel3", S_P_UINT32},  
	{"SelectedSumCoresInLevel3",S_P_UINT32},
	{"SelectedSumSocketsInLevel3",S_P_UINT32},
	{"SelectedSumCpusInLevel3",S_P_UINT32}, 	
	
	{"AllocatedSumNodesInLevel3", S_P_UINT32},  
	{"AllocatedSumCoresInLevel3",S_P_UINT32},
	{"AllocatedSumSocketsInLevel3",S_P_UINT32},
	{"AllocatedSumCpusInLevel3",S_P_UINT32},
	//Leaf switches to process
	{"SwitchToProcessInLevel0",S_P_UINT32},
	{"SwitchToProcessInLevel1",S_P_UINT32},
	{"SwitchToProcessInLevel2",S_P_UINT32},
	{"SwitchToProcessInLevel3",S_P_UINT32},
	/*for( i=0; i<switch_levels; i++)
	{
		{selected_node_cnt[i][30],S_P_UINT32},
		{selected_cpu_cnt[i][30],S_P_UINT32},
		{num_node_cnt[i][30],S_P_UINT32},
		{num_cpu_cnt[i][30],S_P_UINT32},
		{num_core_cnt[i][30],S_P_UINT32},
		{num_socket_cnt[i][30],S_P_UINT32},
		{allocated_node_cnt[i][30],S_P_UINT32},
		{allocated_core_cnt[i][30],S_P_UINT32},
		{allocated_socket_cnt[i][30],S_P_UINT32},
		{allocated_cpu_cnt[i][30],S_P_UINT32},
	}*/

	{NULL}
        
};
s_p_options_t options[] = {
	{"Entity", S_P_EXPLINE, NULL, NULL, entity_options},
	{NULL}
};

const layouts_keyspec_t keyspec[] = {
	/* base keys */
   	{"BitmapPosition", L_T_UINT32},  // Bitmap position or Array Index correlation, This is used for conversion from Layout to Bitmap
	
	{"AllocatedNodeCount",L_T_UINT32,KEYSPEC_UPDATE_CHILDREN_MASK,"AllocatedSocketCount"}, // Selected,Allocated separate list is possible
	{"AllocatedSocketCount",L_T_UINT32,KEYSPEC_UPDATE_CHILDREN_MASK,"AllocatedCoreCount"},
	{"AllocatedCoreCount",L_T_UINT32},
//	{"AllocatedJobID", L_T_UINT32},
	
	/* Non-Aggregated keys and used for aggregation */
	{"nodecount",L_T_UINT32},  // It is for SUM from child , And it shoud be "1"
	{"socketcount",L_T_UINT32},  // It is for SUM from child , And it shoud be "1"
	{"corecount",L_T_UINT32},  // It is for SUM from child , And it shoud be "1"
	{"ThreadsPerCore",L_T_UINT32},  // RD_ONLY value never Change.In the core entity only
/* Selected cores,sockets,nodes information */
	{"SelectedNodeCount",L_T_UINT32}, // Selected,Allocated separate list is possible
	{"SelectedSocketCount",L_T_UINT32},
	{"SelectedCoreCount",L_T_UINT32},
	
//	{"NodeState",S_P_LONG},   // In Node level only. If NodeState is drained change count to zero.
	
//	{"NumParts",S_P_UINT32},   // In root level only, If the LAYOUT_STRUCT_TREE is used partition will not be addable.
//	{"PartitionPriority",S_P_UINT32},   //If Graph struct_type in the Layout use Partition virtual entity
		
//  {"FreeMemory", S_P_UINT32}, // In node level only
	
//	{"ForWhatPurposePriority",S_P_UINT32}, // Fir What reason selected. if we have multiple Reason 
		
	/* After Allocation  */
	
//  {"AllocatedMemory", S_P_UINT32},
//	{"AllocatedJobID", L_T_UINT32},
//	{"JobIdList",S_P_ARRAY},

	/* Parents aggregated keys */
	
	{"NumSumNodes", L_T_UINT32, KEYSPEC_UPDATE_CHILDREN_SUM, "nodecount"},  // It is in Cluster
	{"NumSumCoresInCluster",L_T_UINT32, KEYSPEC_UPDATE_CHILDREN_SUM, "NumSumCoresInNode"},
	{"NumSumSocketsInCluster",L_T_UINT32, KEYSPEC_UPDATE_CHILDREN_SUM, "NumSumSockets"},
	{"NumSumSockets",L_T_UINT32, KEYSPEC_UPDATE_CHILDREN_SUM, "socketcount"}, // It is in Node
	{"NumSumCoresInNode",L_T_UINT32, KEYSPEC_UPDATE_CHILDREN_SUM, "NumSumCores"},
	{"NumSumCores",L_T_UINT32, KEYSPEC_UPDATE_CHILDREN_SUM, "corecount"}, //It is in Socket
//  {"NumSumThreadsInCluster",S_P_UINT32}  // If CR_THREAD LEVEL

/*Free Nodes, Cores details inserted in the beginning aftewards value change update */
	{"SelectedSumNodes", L_T_UINT32, KEYSPEC_UPDATE_CHILDREN_SUM, "SelectedNodeCount"},  // It is in Cluster
	{"SelectedCoresInCluster",L_T_UINT32, KEYSPEC_UPDATE_CHILDREN_SUM, "SelectedSumCoresInNode"},
	{"SelectedSumSocketsInCluster",L_T_UINT32, KEYSPEC_UPDATE_CHILDREN_SUM, "SelectedSumSockets"},
	{"SelectedSumSockets",L_T_UINT32, KEYSPEC_UPDATE_CHILDREN_SUM, "SelectedSocketCount"}, // It is in Node
	{"SelectedSumCoresInNode",L_T_UINT32, KEYSPEC_UPDATE_CHILDREN_SUM, "SelectedSumCores"},
	{"SelectedSumCores",L_T_UINT32, KEYSPEC_UPDATE_CHILDREN_SUM, "SelectedCoreCount"},	//It is in Socket
	
	{"AllocatedSumNodes", L_T_UINT32, KEYSPEC_UPDATE_CHILDREN_SUM, "AllocatedNodeCount"},  // It is in Cluster
	{"AllocatedSumCoresInCluster",L_T_UINT32, KEYSPEC_UPDATE_CHILDREN_SUM, "AllocatedSumCoresInNode"},
	{"AllocatedSumSocketsInCluster",L_T_UINT32 ,KEYSPEC_UPDATE_CHILDREN_SUM ,"AllocatedSumSockets"},
	{"AllocatedSumSockets",L_T_UINT32, KEYSPEC_UPDATE_CHILDREN_SUM ,"AllocatedSocketCount"}, // It is in Node
	{"AllocatedSumCoresInNode",L_T_UINT32, KEYSPEC_UPDATE_CHILDREN_SUM, "AllocatedSumCores"},
	{"AllocatedSumCores",L_T_UINT32, KEYSPEC_UPDATE_CHILDREN_SUM, "AllocatedCoreCount"}, //It is in Socket

	// topology based Node config
	{"SelectedNodeCount", L_T_UINT32},
	{"SelectedCpuCountInNode",L_T_UINT32},
		
	// topology based configuration
	
	{"NumSumNodesInLevel0", L_T_UINT32, KEYSPEC_UPDATE_CHILDREN_SUM, "nodecount"},  
	{"NumSumCoresInLevel0",L_T_UINT32, KEYSPEC_UPDATE_CHILDREN_SUM, "NumSumCoresInNode"},
	{"NumSumSocketsInLevel0",L_T_UINT32, KEYSPEC_UPDATE_CHILDREN_SUM, "NumSumSockets"},
	//{"NumSumCpusInLevel0",L_T_UINT32, KEYSPEC_UPDATE_CHILDREN_SUM, "AllocatedNodeCount"},
	
	{"SelectedSumNodesInLevel0", L_T_UINT32, KEYSPEC_UPDATE_CHILDREN_SUM, "SelectedNodeCount"},  
	{"SelectedSumCoresInLevel0",L_T_UINT32, KEYSPEC_UPDATE_CHILDREN_SUM, "SelectedSumCoresInNode"},
	{"SelectedSumSocketsInLevel0",L_T_UINT32, KEYSPEC_UPDATE_CHILDREN_SUM, "SelectedSumSockets"},
	{"SelectedSumCpusInLevel0",L_T_UINT32, KEYSPEC_UPDATE_CHILDREN_SUM, "SelectedCpuCountInNode"}, 	
	
	{"AllocatedSumNodesInLevel0", L_T_UINT32, KEYSPEC_UPDATE_CHILDREN_SUM, "AllocatedNodeCount"},  
	{"AllocatedSumCoresInLevel0",L_T_UINT32, KEYSPEC_UPDATE_CHILDREN_SUM, "AllocatedSumCoresInNode"},
	{"AllocatedSumSocketsInLevel0",L_T_UINT32, KEYSPEC_UPDATE_CHILDREN_SUM, "AllocatedSumSockets"},
	//{"AllocatedSumCpusInLevel0",L_T_UINT32, KEYSPEC_UPDATE_CHILDREN_SUM, "AllocatedNodeCount"},

	{"NumSumNodesInLevel1", L_T_UINT32, KEYSPEC_UPDATE_CHILDREN_SUM, "NumSumNodesInLevel0"},  
	{"NumSumCoresInLevel1",L_T_UINT32, KEYSPEC_UPDATE_CHILDREN_SUM, "NumSumCoresInLevel0"},
	{"NumSumSocketsInLevel1",L_T_UINT32, KEYSPEC_UPDATE_CHILDREN_SUM, "NumSumSocketsInLevel0"},
	//{"NumSumCpusInLevel1",L_T_UINT32, KEYSPEC_UPDATE_CHILDREN_SUM, "NumSumCpusInLevel"},
	
	{"SelectedSumNodesInLevel1", L_T_UINT32, KEYSPEC_UPDATE_CHILDREN_SUM, "SelectedSumNodesInLevel0"},  
	{"SelectedSumCoresInLevel1",L_T_UINT32, KEYSPEC_UPDATE_CHILDREN_SUM, "SelectedSumCoresInLevel0"},
	{"SelectedSumSocketsInLevel1",L_T_UINT32, KEYSPEC_UPDATE_CHILDREN_SUM, "SelectedSumSocketsInLevel0"},
	{"SelectedSumCpusInLevel1",L_T_UINT32, KEYSPEC_UPDATE_CHILDREN_SUM, "SelectedSumCpusInLevel0"}, 	
	
	{"AllocatedSumNodesInLevel1", L_T_UINT32, KEYSPEC_UPDATE_CHILDREN_SUM, "AllocatedSumNodesInLevel0"},  
	{"AllocatedSumCoresInLevel1",L_T_UINT32, KEYSPEC_UPDATE_CHILDREN_SUM, "AllocatedSumCoresInLevel0"},
	{"AllocatedSumSocketsInLevel1",L_T_UINT32, KEYSPEC_UPDATE_CHILDREN_SUM, "AllocatedSumSocketsInLevel0"},
	//{"AllocatedSumCpusInLevel1",L_T_UINT32, KEYSPEC_UPDATE_CHILDREN_SUM, "AllocatedNodeCount"},

	{"NumSumNodesInLevel2", L_T_UINT32, KEYSPEC_UPDATE_CHILDREN_SUM, "NumSumNodesInLevel1"},  
	{"NumSumCoresInLevel2",L_T_UINT32, KEYSPEC_UPDATE_CHILDREN_SUM, "NumSumCoresInLevel1"},
	{"NumSumSocketsInLevel2",L_T_UINT32, KEYSPEC_UPDATE_CHILDREN_SUM, "NumSumSocketsInLevel1"},
	//{"NumSumCpusInLevel1",L_T_UINT32, KEYSPEC_UPDATE_CHILDREN_SUM, "NumSumCpusInLevel"},
	
	{"SelectedSumNodesInLevel2", L_T_UINT32, KEYSPEC_UPDATE_CHILDREN_SUM, "SelectedSumNodesInLevel1"},  
	{"SelectedSumCoresInLevel2",L_T_UINT32, KEYSPEC_UPDATE_CHILDREN_SUM, "SelectedSumCoresInLevel1"},
	{"SelectedSumSocketsInLevel2",L_T_UINT32, KEYSPEC_UPDATE_CHILDREN_SUM, "SelectedSumSocketsInLevel1"},
	{"SelectedSumCpusInLevel2",L_T_UINT32, KEYSPEC_UPDATE_CHILDREN_SUM, "SelectedSumCpusInLevel1"}, 	
	
	{"AllocatedSumNodesInLevel2", L_T_UINT32, KEYSPEC_UPDATE_CHILDREN_SUM, "AllocatedSumNodesInLevel1"},  
	{"AllocatedSumCoresInLevel2",L_T_UINT32, KEYSPEC_UPDATE_CHILDREN_SUM, "AllocatedSumCoresInLevel1"},
	{"AllocatedSumSocketsInLevel2",L_T_UINT32, KEYSPEC_UPDATE_CHILDREN_SUM, "AllocatedSumSocketsInLevel1"},
	//{"AllocatedSumCpusInLevel2",L_T_UINT32, KEYSPEC_UPDATE_CHILDREN_SUM, "AllocatedNodeCount"},

	{"NumSumNodesInLevel3", L_T_UINT32, KEYSPEC_UPDATE_CHILDREN_SUM, "NumSumNodesInLevel2"},  
	{"NumSumCoresInLevel3",L_T_UINT32, KEYSPEC_UPDATE_CHILDREN_SUM, "NumSumCoresInLevel2"},
	{"NumSumSocketsInLevel3",L_T_UINT32, KEYSPEC_UPDATE_CHILDREN_SUM, "NumSumSocketsInLevel2"},
	//{"NumSumCpusInLevel3",L_T_UINT32, KEYSPEC_UPDATE_CHILDREN_SUM, "NumSumCpusInLevel"},
	
	{"SelectedSumNodesInLevel3", L_T_UINT32, KEYSPEC_UPDATE_CHILDREN_SUM, "SelectedSumNodesInLevel2"},  
	{"SelectedSumCoresInLevel3",L_T_UINT32, KEYSPEC_UPDATE_CHILDREN_SUM, "SelectedSumCoresInLevel2"},
	{"SelectedSumSocketsInLevel3",L_T_UINT32, KEYSPEC_UPDATE_CHILDREN_SUM, "SelectedSumSocketsInLevel2"},
	{"SelectedSumCpusInLevel3",L_T_UINT32, KEYSPEC_UPDATE_CHILDREN_SUM, "SelectedSumCpusInLevel2"}, 	
	
	{"AllocatedSumNodesInLevel3", L_T_UINT32, KEYSPEC_UPDATE_CHILDREN_SUM, "AllocatedSumNodesInLevel2"},  
	{"AllocatedSumCoresInLevel3",L_T_UINT32, KEYSPEC_UPDATE_CHILDREN_SUM, "AllocatedSumCoresInLevel2"},
	{"AllocatedSumSocketsInLevel3",L_T_UINT32, KEYSPEC_UPDATE_CHILDREN_SUM, "AllocatedSumSocketsInLevel2"},
	//{"AllocatedSumCpusInLevel1",L_T_UINT32, KEYSPEC_UPDATE_CHILDREN_SUM, "AllocatedNodeCount"},

	//Leaf switches to process 
	{"SwitchToProcessInLevel0",L_T_UINT32},
	{"SwitchToProcessInLevel1",L_T_UINT32, KEYSPEC_UPDATE_CHILDREN_SUM,"SwitchToProcessInLevel0"},
	{"SwitchToProcessInLevel2",L_T_UINT32, KEYSPEC_UPDATE_CHILDREN_SUM,"SwitchToProcessInLevel1"},
	{"SwitchToProcessInLevel3",L_T_UINT32, KEYSPEC_UPDATE_CHILDREN_SUM,"SwitchToProcessInLevel2"},
	
/*	for( i=0; i<switch_levels; i++)
	{
		if( i == 0 )
		{
			{selected_node_cnt[i],L_T_UINT32},
			{selected_cpu_cnt[i],L_T_UINT32},
			{num_node_cnt[i],L_T_UINT32},
			{num_cpu_cnt[i],L_T_UINT32},
			{num_core_cnt[i],L_T_UINT32},
			{num_socket_cnt[i],L_T_UINT32},
			{allocated_node_cnt[i],L_T_UINT32},
			{allocated_core_cnt[i],L_T_UINT32},
			{allocated_socket_cnt[i],L_T_UINT32},
			{allocated_cpu_cnt[i],L_T_UINT32},
		}
		else
		{
			{selected_node_cnt[i],L_T_UINT32},
			{selected_cpu_cnt[i],L_T_UINT32},
			{num_node_cnt[i],L_T_UINT32},
			{num_cpu_cnt[i],L_T_UINT32},
			{num_core_cnt[i],L_T_UINT32},
			{num_socket_cnt[i],L_T_UINT32},
			{allocated_node_cnt[i],L_T_UINT32},
			{allocated_core_cnt[i],L_T_UINT32},
			{allocated_socket_cnt[i],L_T_UINT32},
			{allocated_cpu_cnt[i],L_T_UINT32},
		}
	}*/

	{NULL}
};

/* types allowed in the entity's "type" field */
const char* etypes[] = {
	"Center",
	"Switch",
//	"Partition", //If Graph struct_type in the Layout use Partition virtual entity
	"Node",
	"Socket",
	"Core",
	NULL
};

const layouts_plugin_spec_t plugin_spec = {
	options,
	keyspec,
	LAYOUT_STRUCT_TREE,
	etypes,
	true, /* if this evalued to true, keys inside plugin_keyspec present in
	       * plugin_options having corresponding types, are automatically
	       * handled by the layouts manager.
	       */
	true  /* if this evalued to true, keys updates trigger an automatic
	       * update of their entities neighborhoods based on their
	       * KEYSPEC_UPDATE_* set flags
	       */
};

/* manager is lock when this function is called */
/* disable this callback by setting it to NULL, warn: not every callback can
 * be desactivated this way */
int layouts_p_conf_done(
		xhash_t* entities, layout_t* layout, s_p_hashtbl_t* tbl)
{
	return 1;
}


/* disable this callback by setting it to NULL, warn: not every callback can
 * be desactivated this way */
void layouts_p_entity_parsing(
		entity_t* e, s_p_hashtbl_t* etbl, layout_t* layout)
{
}

/* manager is lock then this function is called */
/* disable this callback by setting it to NULL, warn: not every callback can
 * be desactivated this way */
int layouts_p_update_done(layout_t* layout, entity_t** e_array, int e_cnt)
{
	int i;
	debug3("layouts/cons_res_partition: receiving update callback for %d entities",
	       e_cnt);
	for (i=0; i < e_cnt; i++) {
		if (e_array[i] == NULL) {
			debug3("layouts/cons_res_partition: skipping update of nullified"
			       "entity[%d]", i);
		} else {
			debug3("layouts/cons_res_partition: updating entity[%d]=%s",
			       i, e_array[i]->name);
		}
	}
	return 1;
}

int init(void)
{
	return SLURM_SUCCESS;
}

int fini(void)
{
	return SLURM_SUCCESS;
}

