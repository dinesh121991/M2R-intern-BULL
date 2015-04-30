/** TODO: copyright notice */

#include "slurm/slurm.h"

#include "src/common/layouts_mgr.h"
#include "src/common/entity.h"
#include "src/common/log.h"

const char plugin_name[] = "Power layouts plugin";
const char plugin_type[] = "layouts/power";
const uint32_t plugin_version = 100;

/* specific options for power tests layout */
s_p_options_t entity_options[] = {
	/* base keys */
        {"CurrentPower", S_P_UINT32},
        {"CurrentFreq", S_P_UINT32},
        {"IdleWatts", S_P_UINT32},
        {"MaxWatts", S_P_UINT32},
        {"Cpufreq1Watts", S_P_UINT32},
        {"Cpufreq2Watts", S_P_UINT32},
        {"Cpufreq3Watts", S_P_UINT32},
        {"Cpufreq4Watts", S_P_UINT32},
        {"Cpufreq5Watts", S_P_UINT32},
        {"Cpufreq6Watts", S_P_UINT32},
        {"Cpufreq7Watts", S_P_UINT32},
        {"Cpufreq8Watts", S_P_UINT32},
        {"Cpufreq1", S_P_UINT32},
        {"Cpufreq2", S_P_UINT32},
        {"Cpufreq3", S_P_UINT32},
        {"Cpufreq4", S_P_UINT32},
        {"Cpufreq5", S_P_UINT32},
        {"Cpufreq6", S_P_UINT32},
        {"Cpufreq7", S_P_UINT32},
        {"Cpufreq8", S_P_UINT32},
        {"PowerCapPriority", S_P_UINT32},
//        {"DownWatts",S_P_UINT32},
//        {"SaveWatts",S_P_UINT32},
        {"NumFreqChoices",S_P_UINT32},
	/* parents aggregated keys */
        {"CurrentSumPower", S_P_UINT32},
        {"IdleSumWatts", S_P_UINT32},
        {"MaxSumWatts", S_P_UINT32},
	{NULL}
};
s_p_options_t options[] = {
	{"Entity", S_P_EXPLINE, NULL, NULL, entity_options},
	{NULL}
};

const layouts_keyspec_t keyspec[] = {
	/* base keys */
        {"CurrentPower", L_T_UINT32},
        {"CurrentFreq", L_T_UINT32},
        {"IdleWatts", L_T_UINT32},
        {"MaxWatts", L_T_UINT32},
        {"Cpufreq1Watts", L_T_UINT32},
        {"Cpufreq2Watts", L_T_UINT32},
        {"Cpufreq3Watts", L_T_UINT32},
        {"Cpufreq4Watts", L_T_UINT32},
        {"Cpufreq5Watts", L_T_UINT32},
        {"Cpufreq6Watts", L_T_UINT32},
        {"Cpufreq7Watts", L_T_UINT32},
        {"Cpufreq8Watts", L_T_UINT32},
        {"Cpufreq1", L_T_UINT32},
        {"Cpufreq2", L_T_UINT32},
        {"Cpufreq3", L_T_UINT32},
        {"Cpufreq4", L_T_UINT32},
        {"Cpufreq5", L_T_UINT32},
        {"Cpufreq6", L_T_UINT32},
        {"Cpufreq7", L_T_UINT32},
        {"Cpufreq8", L_T_UINT32},
        {"PowerCapPriority", L_T_UINT32},
//        {"DownWatts",L_T_UINT32},
//        {"SaveWatts",L_T_UINT32},
        {"NumFreqChoices",L_T_UINT32},
        /* parents aggregated keys */
        {"CurrentSumPower", L_T_UINT32,
	KEYSPEC_UPDATE_CHILDREN_SUM, "CurrentPower"},
        {"IdleSumWatts", L_T_UINT32,
	KEYSPEC_UPDATE_CHILDREN_SUM, "IdleWatts"},
        {"MaxSumWatts", L_T_UINT32,
	KEYSPEC_UPDATE_CHILDREN_SUM, "MaxWatts"},
        {NULL}

};

/* types allowed in the entity's "type" field */
const char* etypes[] = {
	"Center",
	"Node",
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
	debug3("layouts/cons_res: receiving update callback for %d entities",
	       e_cnt);
	for (i=0; i < e_cnt; i++) {
		if (e_array[i] == NULL) {
			debug3("layouts/cons_res: skipping update of nullified"
			       "entity[%d]", i);
		} else {
			debug3("layouts/cons_res: updating entity[%d]=%s",
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

