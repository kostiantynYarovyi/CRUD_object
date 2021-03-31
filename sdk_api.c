#include "sdk_api.h"
#include "crud_api.h"


crud_object_id_t check_type_object(crud_attribute_t attr_list){
    bool chekTypeSwitchObject, chekTypePortObject = false;
        printf("check_type_object: \n");
        switch (attr_list.id)
        {
        case CRUD_SWITCH_ATTR_NAME:
            printf("check_type_object_0: set Switch type name\n");
            chekTypeSwitchObject = true;
            break;
        case CRUD_SWITCH_ATTR_HASH_SEED:
            printf("check_type_object_1: set Switch type\n");
            chekTypeSwitchObject = true;
            break;
        case CRUD_SWITCH_ATTR_SPLIT_MODE:
            printf("check_type_object_2: set Switch type\n");
            chekTypeSwitchObject = true;
            break;
        case CRUD_SWITCH_ATTR_MAX_PORTS:
            printf("check_type_object_3: set Switch type\n");
            chekTypeSwitchObject = true;
            break;

        case CRUD_PORT_ATTR_STATE:
            printf("check_type_object_4: set Port type bool\n");
            chekTypePortObject = true;
            break;
        case CRUD_PORT_ATTR_SPEED:
            printf("check_type_object_5: set Port type\n");
            chekTypePortObject = true;
            break;
        case CRUD_PORT_ATTR_IPV4:
            printf("check_type_object_6: set Port type\n");
            chekTypePortObject = true;
            break;
        case CRUD_PORT_ATTR_MTU:
            printf("check_type_object_7: set Port type\n");
            chekTypePortObject = true;
            break;
        }

    if(chekTypeSwitchObject && !chekTypePortObject)
        return 1;

    if(chekTypePortObject && !chekTypeSwitchObject)
        return 2;

    printf("check_type_object: CRUD_INVALID_PARAM\n");
    return 0;
}



crud_status_t create_object(crud_attribute_t* attr_list, uint32_t attr_count, crud_object_id_t* object_id){
    printf("create_object:\n");
    for (uint32_t i = 0; i < attr_count; ++i) {
        crud_object_id_t type_object = check_type_object(attr_list[i]);
        if(type_object == 0){
            printf("create_object: CRUD_OBJECT_TYPE_INVALID \n");
        }
        if(type_object == 1){
            printf("create_object:Type is SWITCH \n");
            create_switch_object(attr_list[i], object_id);
        }
        if(type_object == 2){

            printf("create_object:Type is PORT \n");
            create_port_object(attr_list[i], object_id);
        }
    }
    return 0;
}