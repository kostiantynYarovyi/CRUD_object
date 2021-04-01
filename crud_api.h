#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "curdattribute.h"



crud_status_t create_port_object(crud_attribute_t* attr_list, uint16_t object_type, crud_object_id_t* object_id, uint32_t attr_count);

crud_status_t create_switch_object(crud_attribute_t* attr_list,  uint16_t object_type, crud_object_id_t* object_id, uint32_t attr_count);

crud_status_t read_port_object(crud_object_id_t* object_id, crud_attribute_t* attr_list, uint32_t attr_count);

crud_status_t read_switch_object(crud_object_id_t* object_id, crud_attribute_t* attr_list, uint32_t attr_count);