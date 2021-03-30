
#include <stdlib.h>
#include "curdport.h"

struct port{
    crud_attribute_t *listattribute[32];
    crud_object_id_t object_id;
    uint32_t count;
}port;



uint32_t size_listattribute() {
    uint32_t i = 0;
    for (uint32_t j = 0; j < 32; ++j) {
        if (port.listattribute[j] == NULL)
            ++i;
    }
    return i;
}

uint32_t get_listattribute(crud_object_id_t* object_id) {
    uint32_t i = 0;
    for (uint32_t j = 0; j < 32; ++j) {
        if (port.listattribute[j] == NULL)
            ++i;
    }
    return i;
}

uint32_t set_listattribute(crud_object_id_t* object_id) {
    uint32_t i = 0;
    for (uint32_t j = 0; j < 32; ++j) {
        if (port.listattribute[j] == NULL)
            ++i;
    }
    return i;
}

crud_status_t add_listattribute(crud_attribute_t* buff, crud_object_id_t* object_id) {
    bool isHaveEmptyElement = false;
    for (uint32_t j = 0; j < 32; ++j) {
        if (port.listattribute[j] == NULL)
        {
            isHaveEmptyElement = true;

        }
    }
    if(isHaveEmptyElement)
        return 0;
    else
        return 5;
}

void clear_listattribute() {
    for (uint32_t j = 0; j < 32; ++j) 
        port.listattribute[j] = NULL;
}


crud_status_t create_object(crud_attribute_t* attr_list, uint32_t attr_count, crud_object_id_t* object_id)
{
    if (attr_count <= 0 || NULL == object_id || NULL == attr_list)
        return 3;

    bool chekTypePortObject = false;
    bool chekTypeSwitchObject = false;

    crud_attribute_t buff;
    for (uint32_t i = 0; i < attr_count; ++i) {
        switch (attr_list->id)
        {
        case CRUD_PORT_ATTR_STATE:
            buff.value.booldata = attr_list->value.booldata;
            chekTypePortObject = true;
            break;
        case CRUD_PORT_ATTR_SPEED:
            strcpy(buff.value.chardata, attr_list->value.chardata);
            chekTypePortObject = true;
            break;
        case CRUD_PORT_ATTR_IPV4:
            buff.value.ip4 = attr_list->value.ip4;
            chekTypePortObject = true;
            break;
        case CRUD_PORT_ATTR_MTU:
            buff.value.u32 = attr_list->value.u32;
            chekTypePortObject = true;
            break;

        case CRUD_SWITCH_ATTR_NAME:
            buff.value.booldata = attr_list->value.booldata;
            chekTypeSwitchObject = true;
            break;
        case CRUD_SWITCH_ATTR_HASH_SEED:
            strcpy(buff.value.chardata, attr_list->value.chardata);
            chekTypeSwitchObject = true;
            break;
        case CRUD_SWITCH_ATTR_SPLIT_MODE:
            buff.value.ip4 = attr_list->value.ip4;
            chekTypeSwitchObject = true;
            break;
        case CRUD_SWITCH_ATTR_MAX_PORTS:
            buff.value.u32 = attr_list->value.u32;
            chekTypeSwitchObject = true;
            break;
        }
    }
    if(chekTypeSwitchObject && chekTypePortObject)
        return 3;
    
    uint16_t first, second = 0;

    if(chekTypeSwitchObject)
    {
        second = 1;
    }

    if(chekTypePortObject)
    {
        second = 2;
    }
    
    object_id = (first << 16) | second;

    return 0;
}

