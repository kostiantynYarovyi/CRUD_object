#include "sdk_api.h"

crud_object_id_t check_type_object(crud_attribute_t* attr_list, uint32_t attr_count){
    bool chekTypeSwitchObject, chekTypePortObject = false;
    for (uint32_t i = 0; i < attr_count; ++i) {
        
        switch (attr_list[i].id)
        {
        case CRUD_PORT_ATTR_STATE:
            printf("check_type_object_0: set Port type bool\n");
            chekTypePortObject = true;
            break;
        case CRUD_PORT_ATTR_SPEED:
            printf("check_type_object_1: set Port type\n");
            chekTypePortObject = true;
            break;
        case CRUD_PORT_ATTR_IPV4:
            printf("check_type_object_2: set Port type\n");
            chekTypePortObject = true;
            break;
        case CRUD_PORT_ATTR_MTU:
            printf("check_type_object_3: set Port type\n");
            chekTypePortObject = true;
            break;

        case CRUD_SWITCH_ATTR_NAME:
            printf("check_type_object_4: set Switch type name\n");
            chekTypeSwitchObject = true;
            break;
        case CRUD_SWITCH_ATTR_HASH_SEED:
            printf("check_type_object_5: set Switch type\n");
            chekTypeSwitchObject = true;
            break;
        case CRUD_SWITCH_ATTR_SPLIT_MODE:
            printf("check_type_object_6: set Switch type\n");
            chekTypeSwitchObject = true;
            break;
        case CRUD_SWITCH_ATTR_MAX_PORTS:
            printf("check_type_object_7: set Switch type\n");
            chekTypeSwitchObject = true;
            break;
        }
    }

    if(chekTypeSwitchObject && !chekTypePortObject)
        return 1;

    if(chekTypePortObject && !chekTypeSwitchObject)
        return 2;

    printf("check_type_object: CRUD_INVALID_PARAM\n");
    return 0;
}



crud_status_t create_object(crud_attribute_t* attr_list, uint32_t attr_count, crud_object_id_t* object_id){
    if(check_type_object(attr_list, attr_count) == 0){
        printf("add_node: node add and create\n");
        return 3;
    }
    if(check_type_object(attr_list, attr_count) == 1){
        printf("create_object:Type is SWITCH \n");
        return 0;
    }
    if(check_type_object(attr_list, attr_count) == 2){

        printf("create_object:Type is PORT \n");
        return 0;
    }
    return 7;
}