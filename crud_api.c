#include "crud_api.h"
#include "sdk_list.h"

crud_status_t create_port_object(crud_attribute_t* attr_list, uint16_t object_type, crud_object_id_t* object_id){
    printf("-------------------------------------------\n");
    printf("create_port_object:\n");


    struct lobject* object_list = get_list_port_object();
    //printf("create_port_object: get_list_port_object() %p \n", get_list_port_object());
    //printf("create_port_object: object_list %p \n", object_list);
    if (object_list == 0){
        object_list = create_list_port_object();
        //printf("create_port_object: create_list_port_object() %p \n", create_list_port_object());
        //printf("create_port_object: create_list_port_object()  object_list %p \n", object_list);
    }

   //list_port_object
    *object_id = add_node(object_list, object_type, attr_list);
    printf("create_port_object: |||||||||||||||||| after add newList->head: %p \n", get_list_port_object()->head);
    //printf("create_port_object: object_list->head = node: %p \n", object_list->head);
    //printf("create_port_object: object_list size = node: %d \n", object_list->size);
    //printf("create_port_object: *object_id = %u\n", *object_id);
    return 0;
    printf("-------------------------------------------\n");
}

crud_status_t create_switch_object(crud_attribute_t* attr_list,  uint16_t object_type, crud_object_id_t* object_id){
    return 0;
}