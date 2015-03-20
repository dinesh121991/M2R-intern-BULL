/** TODO: copyright notice */

#include "slurm/slurm.h"

#include "src/common/layouts_mgr.h"
#include "src/common/entity.h"
#include "src/common/log.h"

const char plugin_name[] = "Energy layout";
const char plugin_type[] = "layouts/energy";
const uint32_t plugin_version = 100;

/* specific options for energy layout */
s_p_options_t entity_options[] = {
	{"ConsoMIN", S_P_UINT32},
	{"ConsoMED", S_P_UINT32},
	{"ConsoMAX", S_P_UINT32},
	{NULL}
};
s_p_options_t options[] = {
	{"Entity", S_P_EXPLINE, NULL, NULL, entity_options},
	{NULL}
};

const layouts_keyspec_t keyspec[] = {
	{"ConsoMIN", L_T_UINT32},
	{"ConsoMED", L_T_UINT32},
	{"ConsoMAX", L_T_UINT32},
	{NULL}
};

/* types allowed in the entity's "type" field */
const char* etypes[] = {
	"Center",
	"Room",
	"Row",
	"RackDoor",
	"Rack",
	"Chassis",
	"Switch",
	"Node",
	"Socket",
	"Core",
	"Motherboard",
	"HardDisk",
	"NetworkCard",
	"Memory",
	NULL
};

const layouts_plugin_spec_t plugin_spec = {
	options,
	keyspec,
	LAYOUT_STRUCT_TREE,
	etypes,
	true /* if this evalued to true, keys inside plugin_keyspec present in
	      * plugin_options having corresponding types, are automatically
	      * handled by the layouts manager.
	      */
};

/* manager is lock then this function is called */
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

int init(void)
{
	return SLURM_SUCCESS;
}

int fini(void)
{
	return SLURM_SUCCESS;
}

