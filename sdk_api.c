#include "sdk_api.h"



crud_object_id_t check_type_object(crud_attribute_t* attr_list, uint32_t attr_count){
    bool chekTypeSwitchObject, chekTypePortObject, chekTypeInvalidObject  = false;
    printf("check_type_object: \n");
    for (uint32_t i = 0; i < attr_count; ++i){
        switch (attr_list[i].id)
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
        default:
            printf("check_type_object: CRUD_INVALID_PARAM\n");
            return 0;
        }
    }

    if(chekTypeSwitchObject && !chekTypePortObject)
        return 1;

    if(chekTypePortObject && !chekTypeSwitchObject)
        return 2;

    printf("check_type_object: CRUD_INVALID_PARAM\n");
    return 0;
}


crud_object_id_t check_invalid_type_object(crud_attribute_t* attr_list, uint32_t attr_count){
    for (uint32_t i = 0; i < attr_count; ++i) {
        if(attr_list[i].id < 0 ||attr_list[i].id > 7 )
            return 0;
    }
    return 1;
}

crud_status_t create_object(crud_attribute_t* attr_list, uint32_t attr_count, crud_object_id_t* object_id){
    //printf("create_object:\n");
    /*if(check_invalid_type_object(attr_list, attr_count) == 0){
        printf("create_object: CRUD_OBJECT_TYPE_INVALID \n");
        return 3;
    }*/
        

    crud_object_id_t type_object = check_type_object(attr_list, attr_count);
    if(type_object == 0){
        printf("create_object: CRUD_INVALID_PARAM \n");
        return 3;
    }
    if(type_object == 1){
        printf("create_object:Type is SWITCH; start creating \n");
        //create_switch_object(attr_list[i], object_id);
    }
    if(type_object == 2){

        printf("create_object:Type is PORT; start creating \n");
        //create_port_object(attr_list,type_object ,object_id);
    }
    return 0;
}