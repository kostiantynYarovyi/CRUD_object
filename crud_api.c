#include "crud_api.h"
#include "sdk_list.h"

bool get_crud_port_attr_state(crud_attribute_t* attr_list, uint32_t attr_count);

bool check_crud_port_attr_speed(union _sai_attribute_value_t speed);

bool check_crud_port_attr_ipv4(union _sai_attribute_value_t ipv4);

bool check_crud_port_attr_mtu(union _sai_attribute_value_t mtu);




crud_status_t create_port_object(crud_attribute_t* attr_list, uint16_t object_type, crud_object_id_t* object_id, uint32_t attr_count){
    //printf("-------------------------------------------\n");
    //printf("crud_api____create_port_object:\n");
    bool Is_CRUD_PORT_ATTR_STATE    = false;
    bool Is_CRUD_PORT_ATTR_SPEED    = false;
    bool Is_CRUD_PORT_ATTR_IPV4     = false;
    bool Is_CRUD_PORT_ATTR_MTU      = false;
     for (uint32_t i = 0; i < attr_count; ++i){
        switch (attr_list[i].id)
        {
        case CRUD_PORT_ATTR_STATE:
            //printf("crud_api____create_port_object_0:\n");
            if(Is_CRUD_PORT_ATTR_STATE)
            {
                // printf("crud_api____create_port_object_0: return CRUD_ATTRIBUTE_REPEAT;\n");
                 return CRUD_ATTRIBUTE_REPEAT;
            }
                       
            Is_CRUD_PORT_ATTR_STATE = true;
            
            break;

        case CRUD_PORT_ATTR_SPEED:
          //printf("crud_api____create_port_object_1:\n");
            if(Is_CRUD_PORT_ATTR_SPEED)
                 return CRUD_ATTRIBUTE_REPEAT;        
          
            Is_CRUD_PORT_ATTR_SPEED = true;
            if(check_crud_port_attr_speed(attr_list[i].value)){
            //    printf("crud_api____create_port_object_1: CRUD_ATTRIBUTE_SPEED_INCORRECT\n");
                return CRUD_ATTRIBUTE_SPEED_INCORRECT;
            }
            break;

        case CRUD_PORT_ATTR_IPV4:
         // printf("crud_api____create_port_object_2:\n");
            if(Is_CRUD_PORT_ATTR_IPV4)
                 return CRUD_ATTRIBUTE_REPEAT;
            Is_CRUD_PORT_ATTR_IPV4 = true;
          
            if (check_crud_port_attr_ipv4(attr_list[i].value)){
                //printf("crud_api____create_port_object: CRUD_ATTRIBUTE_IPV4_MULTICAST\n");
                return CRUD_ATTRIBUTE_IPV4_MULTICAST;
            }
            break;

        case CRUD_PORT_ATTR_MTU:
            //  printf("crud_api____create_port_object_3:\n");
            if(Is_CRUD_PORT_ATTR_MTU)
                 return CRUD_ATTRIBUTE_REPEAT;
            Is_CRUD_PORT_ATTR_MTU = true;

            if( check_crud_port_attr_mtu(attr_list[i].value)){
                //printf("crud_api____create_port_object: CRUD_ATTRIBUTE_MTU_INCORRECT\n");
                return CRUD_ATTRIBUTE_MTU_INCORRECT;
            }
            break;
        }
    }

   //printf("crud_api____create_port_object: ============\n");
    struct lobject* object_list = get_list_port_object();

    if (object_list == 0){
        object_list = create_list_port_object();
    }

    *object_id = add_node(object_list, object_type, attr_list, attr_count);

    return 0;
    //printf("-------------------------------------------\n");
}

crud_status_t create_switch_object(crud_attribute_t* attr_list,  uint16_t object_type, crud_object_id_t* object_id, uint32_t attr_count){
    return 1;
}


crud_status_t read_port_object(crud_object_id_t* object_id, crud_attribute_t* attr_list, uint32_t attr_count){
  //  printf("crud_api____read_port_object:\n");
    struct lnode*  node =  get_node(get_list_port_object(), *object_id);
    uint32_t attr_id = -1;

    for (uint32_t i = 0; i < attr_count; ++i){
        switch (attr_list[i].id)
        {
        case CRUD_PORT_ATTR_STATE:
            //printf("crud_api____read_port_object_0:\n");
            if(get_attr_node(node, attr_list[i].id, &attr_id) == true) 
                attr_list[i].value.booldata = node->listattribute[attr_id].value.booldata;
            break;

        case CRUD_PORT_ATTR_SPEED:
            //printf("crud_api____read_port_object_1:\n");
            if(get_attr_node(node, attr_list[i].id, &attr_id) == true){
                if(check_crud_port_attr_speed(node->listattribute[attr_id].value)){
                    //printf("crud_api____read_port_object_1: CRUD_ATTRIBUTE_SPEED_INCORRECT\n");
                    return CRUD_ATTRIBUTE_SPEED_INCORRECT;
                }

                attr_list[i].value.u32 = node->listattribute[attr_id].value.u32;
            }
            break;

        case CRUD_PORT_ATTR_IPV4:
            //printf("crud_api____read_port_object_2:\n");
            if(get_attr_node(node, attr_list[i].id, &attr_id) == true){
                if (check_crud_port_attr_ipv4(node->listattribute[attr_id].value)){
                    //printf("crud_api____read_port_object: CRUD_ATTRIBUTE_IPV4_MULTICAST\n");
                    return CRUD_ATTRIBUTE_IPV4_MULTICAST;
                }

                attr_list[i].value.ip4 = node->listattribute[attr_id].value.ip4;
            }

            break;

        case CRUD_PORT_ATTR_MTU:
            //printf("crud_api____read_port_object_3:\n");
            if(get_attr_node(node, attr_list[i].id, &attr_id) == true){
                if( check_crud_port_attr_mtu(node->listattribute[attr_id].value)){
                    //printf("crud_api____read_port_object: CRUD_ATTRIBUTE_MTU_INCORRECT\n");
                    return CRUD_ATTRIBUTE_MTU_INCORRECT;
                }

                attr_list[i].value.u32 = node->listattribute[attr_id].value.u32;
            }
            break;
        }
    }
    return 0;
}

crud_status_t read_switch_object(crud_object_id_t* object_id, crud_attribute_t* attr_list, uint32_t attr_count){
    return 1;
}

crud_status_t update_port_object(crud_object_id_t* object_id, crud_attribute_t* attr_list, uint32_t attr_count){
    struct lnode*  node =  get_node(get_list_port_object(), *object_id);
    uint32_t attr_id = -1;

    for (uint32_t i = 0; i < attr_count; ++i){
        switch (attr_list[i].id)
        {
        case CRUD_PORT_ATTR_STATE:
        //    printf("crud_api____update_port_object_0:\n");

            if(get_attr_node(node, attr_list[i].id, &attr_id) == true)
                node->listattribute[attr_id].value.booldata = attr_list[i].value.booldata;
            break;

        case CRUD_PORT_ATTR_SPEED:
            if(get_attr_node(node, attr_list[i].id, &attr_id) == true){
                if( check_crud_port_attr_speed(attr_list[i].value) ||
                    ((get_list_port_object()->state != -1 && !((bool)get_list_port_object()->state)) ||
                    (get_list_port_object()->state == -1 && get_crud_port_attr_state(attr_list, attr_count)))){
                //    printf("crud_api____update_port_object_1: CRUD_ATTRIBUTE_SPEED_INCORRECT\n");
                    return CRUD_ATTRIBUTE_SPEED_INCORRECT;
                }
            
                node->listattribute[attr_id].value.u32 = attr_list[i].value.u32;
            }
            break;

        case CRUD_PORT_ATTR_IPV4:

            if(get_attr_node(node, attr_list[i].id, &attr_id) == true) {
                if (check_crud_port_attr_ipv4(attr_list[i].value)){
                    //printf("crud_api____update_port_object: CRUD_ATTRIBUTE_IPV4_MULTICAST\n");
                    return CRUD_ATTRIBUTE_IPV4_MULTICAST;
                }
                node->listattribute[attr_id].value.ip4 = attr_list[i].value.ip4;
            }
                
            break;

        case CRUD_PORT_ATTR_MTU:
        //    printf("crud_api____update_object: CRUD_ATTRIBUTE_MTU_ONLY_READ\n");
            return CRUD_ATTRIBUTE_MTU_ONLY_READ;
            break;
        }
    }
    return 0;
}

crud_status_t update_switch_object(crud_object_id_t* object_id, crud_attribute_t* attr_list, uint32_t attr_count){
    return 1;
}

bool get_crud_port_attr_state(crud_attribute_t* attr_list, uint32_t attr_count){
    for(uint32_t i = 0; i < attr_count; i++){
        if(attr_list[i].id == CRUD_PORT_ATTR_STATE)
            return attr_list[i].value.booldata;
    }
    return false;
}

bool check_crud_port_attr_speed(union _sai_attribute_value_t speed){
    //printf("crud_api____check_crud_port_attr_speed: speed = %u \n", speed.u32);
    return(     speed.u32 != 10  &&
                speed.u32 != 100 && 
                speed.u32 != 1000);
}

bool check_crud_port_attr_ipv4(union _sai_attribute_value_t ipv4){
    uint16_t firstbyte = (ipv4.ip4 >> 24) & 0xffff;
    return(firstbyte >= 224 && firstbyte <= 239);
}

bool check_crud_port_attr_mtu(union _sai_attribute_value_t mtu){
   // printf("crud_api____check_crud_port_attr_speed: mtu = %u \n", mtu.u32);
    return (    mtu.u32 < 64 ||
                mtu.u32 > 9000);
}
