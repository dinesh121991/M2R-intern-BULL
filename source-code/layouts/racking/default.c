/** TODO: copyright notice */

#include "slurm/slurm.h"

#include "src/common/layouts_mgr.h"
#include "src/common/entity.h"
#include "src/common/log.h"

const char plugin_name[] = "Racking layouts plugin";
const char plugin_type[] = "layouts/racking";
const uint32_t plugin_version = 100;

/* if plugin_options is not NULL, automatically call config parser of the
 * layouts manager.
 */

/* specific options for racking layout */
s_p_options_t entity_options[] = {
	{"CoordsX", S_P_UINT32},
	{"CoordsY", S_P_UINT32},
	{"CoordsZ", S_P_UINT32},
	{NULL}
};
s_p_options_t options[] = {
	{"Entity", S_P_EXPLINE, NULL, NULL, entity_options},
	{NULL}
};

const layouts_keyspec_t keyspec[] = {
	{"CoordsX", L_T_UINT32},
	{"CoordsY", L_T_UINT32},
	{"CoordsZ", L_T_UINT32},
	{NULL}
};

/* types allowed in the entity's "type" field */
const char* etypes[] = {
	"Enclosure",
	"Chassis",
	"Rack",
	"Room",
	"Center",
	"Row",
	"Node",
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

/*
void layouts_p_load_entities(xhash_t *entities)
{
	debug3("Layouts: loading %s entities", plugin_type);
}

void layouts_p_build_layout(xhash_t *layouts, xhash_t *entities)
{
	debug3("Layouts: building %s layout", plugin_type);
}
typedef struct layout_options_st {
	s_p_options_t*	options;
	const char**	entities_types;
} layouts_options_t;


layout_options_t* layouts_p_get_options()
{
	static layout_options_t options = {
		racking_options,
		entities_types
	};
	return &options;
}
*/

