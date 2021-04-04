#include "sdk_api.h"
#include "sdk_list.h"


struct lobject* get_list_switch_object(); 

struct lobject* get_list_port_object();

uint32_t get_list_size(struct lobject* List);

crud_status_t read_port_object(crud_object_id_t* object_id, crud_attribute_t* attr_list, uint32_t attr_count);

crud_status_t read_switch_object(crud_object_id_t* object_id, crud_attribute_t* attr_list, uint32_t attr_count);

crud_status_t delete_node(struct lobject* newList, const crud_object_id_t object_id);


crud_object_id_t check_type_attribute_list(crud_attribute_t* attr_list, uint32_t attr_count){
    bool chekTypeSwitchObject, chekTypePortObject, chekTypeInvalidObject  = false;
    //printf("sdk_api_check_type_object: \n");
    for (uint32_t i = 0; i < attr_count; ++i){
        switch (attr_list[i].id)
        {
        case CRUD_SWITCH_ATTR_NAME:
            //printf("sdk_api_check_type_attribute_list_0: set Switch type name\n");
            chekTypeSwitchObject = true;
            break;
        case CRUD_SWITCH_ATTR_HASH_SEED:
            //printf("sdk_api_check_type_attribute_list_1: set Switch type\n");
            chekTypeSwitchObject = true;
            break;
        case CRUD_SWITCH_ATTR_SPLIT_MODE:
            //printf("sdk_api_check_type_attribute_list_2: set Switch type\n");
            chekTypeSwitchObject = true;
            break;
        case CRUD_SWITCH_ATTR_MAX_PORTS:
            //printf("sdk_api_check_type_attribute_list_3: set Switch type\n");
            chekTypeSwitchObject = true;
            break;

        case CRUD_PORT_ATTR_STATE:
            //printf("sdk_api_check_type_attribute_list_4: set Port type bool\n");
            chekTypePortObject = true;
            break;
        case CRUD_PORT_ATTR_SPEED:
            //printf("sdk_api_check_type_attribute_list_5: set Port type Speed\n");
            chekTypePortObject = true;
            break;
        case CRUD_PORT_ATTR_IPV4:
            //printf("sdk_api_check_type_attribute_list_6: set Port type IP\n");
            chekTypePortObject = true;
            break;
        case CRUD_PORT_ATTR_MTU:
            //printf("sdk_api_check_type_attribute_list_7: set Port type MTU\n");
            chekTypePortObject = true;
            break;
        default:
            printf("sdk_api_check_type_attribute_list_8: CRUD_INVALID_PARAM\n");
            return 0;
        }
    }

    if(chekTypeSwitchObject && !chekTypePortObject)
        return 1;

    if(chekTypePortObject && !chekTypeSwitchObject)
        return 2;

    printf("check_type_attribute_list: CRUD_INVALID_PARAM\n");
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
    //printf("===========================================\n");
    printf("sdk_api___create_object: ");
    if(get_list_port_object() && (get_list_size(get_list_port_object()) >= 32)){
        printf("sdk_api___create_object: CRUD_PORT_LIST_IS_FULL \n");
        return CRUD_PORT_LIST_IS_FULL;
    }

    
    if(!object_id || !attr_list || attr_count < 0)
        return CRUD_INVALID_PARAM;

    if(attr_count == 0)
        return CRUD_ATTRIBUTE_LIST_IS_EMPTY;

    crud_object_id_t type_object = check_type_attribute_list(attr_list, attr_count);
    if(type_object == 0){
        printf("sdk_api___create_object: CRUD_INVALID_PARAM \n");
        return CRUD_INVALID_PARAM;
    }
    if(type_object == 1){    
        return create_switch_object(attr_list, type_object, object_id, attr_count);
        //printf("create_object:Type is SWITCH; start creating \n");
        //printf("===========================================\n");
    }
    if(type_object == 2){
        return create_port_object(attr_list, type_object, object_id, attr_count);
        printf("create_object:Type is PORT; start creating: object=  %u \n", *object_id);
        printf("===========================================\n");
    }
    
    return CRUD_STATUS_FAILURE;
}

crud_status_t read_object(crud_object_id_t *object_id, crud_attribute_t* attr_list, uint32_t attr_count){
    if(!object_id || !attr_list || attr_count < 0)
        return CRUD_INVALID_PARAM;

    if(attr_count == 0)
        return CRUD_ATTRIBUTE_LIST_IS_EMPTY;

    crud_object_id_t type_object = check_type_attribute_list(attr_list, attr_count);
    if(type_object == 0){
        printf("sdk_api_create_object: CRUD_INVALID_PARAM \n");
        return CRUD_INVALID_PARAM;
    }

    if(type_object == 1){    
        return read_switch_object(object_id, attr_list, attr_count);
    }

    if(type_object == 2){
        return read_port_object(object_id, attr_list, attr_count);
    }

    return CRUD_STATUS_FAILURE;
}

crud_status_t update_object(crud_object_id_t *object_id, crud_attribute_t* attr_list, uint32_t attr_count){
    
    if(!object_id || !attr_list|| attr_count < 0)
        return CRUD_INVALID_PARAM;

    if(attr_count == 0)
        return CRUD_ATTRIBUTE_LIST_IS_EMPTY;

    crud_object_id_t type_attribute_list =  check_type_attribute_list(attr_list, attr_count);

    crud_object_id_t type_object = ((*object_id >> 16) & 0xffff);

    if(type_object != type_attribute_list)
        return CRUD_ATTRIBUTE_PARAMETERS_LIST_DO_NOT_MATCH_WITH_TYPE_OBJECT;

    if(type_object == 0){
        printf("sdk_api_update_object: CRUD_INVALID_PARAM \n");
        return CRUD_INVALID_PARAM;
    }

    if(type_object == 1){    
        return update_switch_object(object_id, attr_list, attr_count);
    }

    if(type_object == 2){
        printf("sdk_api_update_object: update_port_object \n");
        return update_port_object(object_id, attr_list, attr_count);
    }

    return CRUD_STATUS_FAILURE;
}

crud_status_t delete_object(crud_object_id_t *object_id){
    if(!object_id)
        return CRUD_INVALID_PARAM;

    uint16_t type = (*object_id >> 16) & 0xffff;
    if(type == 1)
        return delete_node( get_list_switch_object(), *object_id);    

    if(type == 2)
        return delete_node(get_list_port_object(), *object_id);

    return CRUD_STATUS_FAILURE;
}