/** TODO: copyright notice */

#include "slurm/slurm.h"

#include "src/common/layouts_mgr.h"
#include "src/common/layout.h"
#include "src/common/entity.h"
#include "src/common/log.h"

const char plugin_name[] = "Consumable resources layout(CRL) partition plugin";
const char plugin_type[] = "layouts/cons_res_partition";
const uint32_t plugin_version = 100;

/* specific options for power tests layout */
s_p_options_t entity_options[] = {
	/* base keys */
	{"BitmapPosition", S_P_UINT32},  // Bitmap position or Array Index correlation, This is used for conversion from Layout to Bitmap
	{"Selected", S_P_BOOLEAN},
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

	{NULL}
        
};
s_p_options_t options[] = {
	{"Entity", S_P_EXPLINE, NULL, NULL, entity_options},
	{NULL}
};

const layouts_keyspec_t keyspec[] = {
	/* base keys */
   	{"BitmapPosition", L_T_UINT32},  // Bitmap position or Array Index correlation, This is used for conversion from Layout to Bitmap
	{"Selected", L_T_BOOLEAN},
	{"AllocatedNodeCount",L_T_UINT32}, // Selected,Allocated separate list is possible
	{"AllocatedSocketCount",L_T_UINT32},
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
	{"AllocatedJobID", L_T_UINT32},
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

	{NULL}
};

/* types allowed in the entity's "type" field */
const char* etypes[] = {
	"Center",
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

