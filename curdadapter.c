
#include <stdlib.h>
#include "curdport.h"

crud_attribute_t *listattribute[32];

uint32_t listattributeSize() {
    uint32_t i = 0;
    for (uint32_t j = 0; j < 32; ++j) {
        if (listattribute[j] == NULL)
            ++i;
    }
    return i;
}



crud_status_t create_object(crud_attribute_t* attr_list, uint32_t attr_count, crud_object_id_t* object_id)
{
    if (attr_count <= 0 || NULL == object_id || NULL == attr_list)
        return 3;

    crud_attribute_t buff;
    for (uint32_t i = 0; i < attr_count; ++i) {
        switch (attr_list->id)
        {
        case CRUD_PORT_ATTR_STATE:
            buff.value.booldata = attr_list->value.booldata;
            break;
        case CRUD_PORT_ATTR_SPEED:
            strcpy(buff.value.chardata, attr_list->value.chardata);
            break;
        case CRUD_PORT_ATTR_IPV4:
            buff.value.ip4 = attr_list->value.ip4;
            break;
        case CRUD_PORT_ATTR_MTU:
            buff.value.u32 = attr_list->value.u32;
            break;
        }
    }


    return 0;
}

