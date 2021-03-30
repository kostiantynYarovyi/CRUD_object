#include <string.h>
#include "curdport.h"


crud_status_t create_object(crud_attribute_t* attr_list, uint32_t attr_count, crud_object_id_t* object_id);

crud_status_t read_object(crud_object_id_t *object_id, crud_attribute_t* attr_list, uint32_t attr_count);

crud_status_t delete_object(crud_object_id_t *object_id);