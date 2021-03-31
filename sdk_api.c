#include "sdk_api.h"

crud_object_id_t check_type_object(crud_object_id_t* object_id){
    uint16_t type = (object_id << 16) & 0xffff;
    return type;
}

crud_status_t create_object(crud_attribute_t* attr_list, uint32_t attr_count, crud_object_id_t* object_id){
    if(check_type_object(object_id) == 0){
        printf("add_node: node add and create\n");
        return 3;
    }
    if(check_type_object(object_id) == 1){

        printf("create_object:Type is SWITCH \n");
    }
    if(check_type_object(object_id) == 2){

        printf("create_object:Type is PORT \n");
    }
    return 0;
}