#include "crud_api.h"
#include "sdk_list.h"

bool get_crud_port_attr_state(union _sai_attribute_value_t state);

bool check_crud_port_attr_speed(union _sai_attribute_value_t speed);

bool check_crud_port_attr_ipv4(union _sai_attribute_value_t ipv4);

bool check_crud_port_attr_mtu(union _sai_attribute_value_t mtu);


crud_status_t create_port_object(crud_attribute_t* attr_list, uint16_t object_type, crud_object_id_t* object_id){
    //printf("-------------------------------------------\n");
    //printf("crud_api____create_port_object:\n");

    struct lobject* object_list = get_list_port_object();

    if (object_list == 0){
        object_list = create_list_port_object();
    }

    *object_id = add_node(object_list, object_type, attr_list);

    return 0;
    //printf("-------------------------------------------\n");
}

crud_status_t create_switch_object(crud_attribute_t* attr_list,  uint16_t object_type, crud_object_id_t* object_id){
    return 0;
}


crud_status_t read_port_object(crud_object_id_t* object_id, crud_attribute_t* attr_list, uint32_t attr_count){

    struct lnode*  node =  get_node(get_list_port_object(), *object_id);
    for (uint32_t i = 0; i < attr_count; ++i){
        switch (attr_list[i].id)
        {
        case CRUD_PORT_ATTR_STATE:
            attr_list[i].value.booldata = node->listattribute[i].value.booldata;
            break;

        case CRUD_PORT_ATTR_SPEED:
            if(check_crud_port_attr_speed(node->listattribute[i].value)){
                return CRUD_ATTRIBUTE_SPEED_INCORRECT;
            }
            attr_list[i].value.u32 = node->listattribute[i].value.u32;
            break;

        case CRUD_PORT_ATTR_IPV4:
            if (check_crud_port_attr_ipv4(node->listattribute[i].value)){
                return CRUD_ATTRIBUTE_SPEED_IPV4_MULTICAST;
            }
            attr_list[i].value.ip4 = node->listattribute[i].value.ip4;
            break;

        case CRUD_PORT_ATTR_MTU:
            if( check_crud_port_attr_mtu(node->listattribute[i].value)){
                return CRUD_ATTRIBUTE_SPEED_INCORRECT;
            }

            attr_list[i].value.u32 = node->listattribute[i].value.u32;
            break;
        }
    }
    return 0;
}

crud_status_t read_switch_object(crud_object_id_t* object_id, crud_attribute_t* attr_list, uint32_t attr_count){
    return 0;
}

bool get_crud_port_attr_state(union _sai_attribute_value_t state){
    return state.booldata;
}

bool check_crud_port_attr_speed(union _sai_attribute_value_t speed){
    return(     speed.u32 != 10  ||
                speed.u32 != 100 || 
                speed.u32 != 1000);
}

bool check_crud_port_attr_ipv4(union _sai_attribute_value_t ipv4){
    char firstbyte = (ipv4.ip4 >> 24) & 0xffff;
    return(firstbyte >= 224 && firstbyte <= 239);
}

bool check_crud_port_attr_mtu(union _sai_attribute_value_t mtu){
    return (    mtu.u32 >= 64 &&
                mtu.u32 <= 9000);
}