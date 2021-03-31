#include "crud_api.h"

crud_status_t create_port_object(crud_attribute_t attr_list, uint16_t object_type, crud_object_id_t* object_id){
    printf("create_port_object:\n");


    struct lobject* object_list = get_list_port_object();
    if (object_list == 0)
    {
        object_list = create_list();
    }
    uint32_t id = add_node(object_list, object_type, attr_list);
    return id;
}

crud_status_t create_switch_object(crud_attribute_t attr_list,  uint16_t object_type, crud_object_id_t* object_id){
    return 0;
}