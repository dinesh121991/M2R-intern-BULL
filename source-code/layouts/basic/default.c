/** TODO: copyright notice */

#include "slurm/slurm.h"

#include "src/common/layouts_mgr.h"
#include "src/common/log.h"

const char plugin_name[] = "Null layouts plugin (used for testing purposes)";
const char plugin_type[] = "layouts/none";
const uint32_t plugin_version = 100;

int init(void)
{
	debug3("layouts_none: init.");
	return SLURM_SUCCESS;
}

int fini(void)
{
	debug3("layouts_none: fini.");
	return SLURM_SUCCESS;
}

void layouts_p_load_entities(xhash_t *entities)
{
}

void layouts_p_build_layout(xhash_t *layouts, xhash_t *entities)
{
}

