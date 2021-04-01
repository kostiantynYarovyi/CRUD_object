
#include "sdk_list.h"

struct lobject* list_port_object; 
struct lobject* list_switch_object;

struct lobject* create_list_port_object(){
    printf("create_list_port_object\n");
    list_port_object = (struct lobject*) malloc(sizeof(struct lobject));
    if(list_port_object){
        list_port_object->size = 0;
        list_port_object->head = 0;
        printf("create_list_port_object:  create object \n");
        return list_port_object;
    }
    printf("create_list_port_object: return 0 \n");
    return 0;
}

struct lobject* create_list_swirch_object(){
    printf("create_list_swirch_object\n");
    list_switch_object = (struct lobject*) malloc(sizeof(struct lobject));
    if(list_switch_object){
        list_switch_object->size = 0;
        list_switch_object->head = NULL;
        printf("create_list_swirch_object:  create object \n");
        return list_switch_object;
    }
    printf("create_list_swirch_object: return 0 \n");
    return 0;
}
 

struct lobject* get_list_port_object(){
    printf("get_list_port_object\n");
    return list_port_object;
}

struct lobject* get_list_switch_object(){
    printf("get_list_swirch_object\n");
    return list_switch_object;
}

uint32_t add_node(struct lobject* List, const uint16_t object_type, crud_attribute_t* listattribute){
    //printf("++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    printf("add_node\n");
    uint32_t object_id = 0;
    struct lnode* node = (struct lnode*)malloc(sizeof(struct lnode));

    if(node)
    {
        printf("add_node: IF NODE\n");
       
        node->next = NULL;
        node->count = 0;
        node->object_type = object_type;
        node->listattribute = listattribute;
        node->object_id = List->size;
        
        node->next = List->head;
		List->head = node;
        List->size++;
		
        //printf("add_node: List->head = NODE CHECK: %p \n", List->head);
        //printf("add_node: List->head = NODE CHECK: %p \n", List->head);
        object_id = (object_type << 16) | node->object_id;
        return object_id;
    }
    printf("add_node: fail !node\n");
    return 0;
}

struct lnode* get_node(struct lobject* List, const crud_object_id_t object_id){
    if(List){
       struct lnode* current =  List->head;

        uint16_t id = object_id &0xffff;
        while(current != NULL){   
            if(current->object_id == id)
                return current;
            current = current->next;
        }
        printf("get_node: fail List out of range\n");
        return 0;
    }
    printf("get_node: fail List is absetn\n");
    return 0;
}

crud_status_t delete_node(struct lobject* List, const crud_object_id_t object_id){
    if(List){
        struct lnode* current =  List->head;
        
        uint16_t id = object_id &0xffff;
        while(current->next != NULL){
            if(current->next->object_id == object_id)
            {
                struct lnode* buff = current->next;
                free(buff);
                current->next = current->next->next;
                break;
            }
            current = current->next;        
        }
        return 0;
    }
    printf("delete_node: fail List is absetn\n");
    return 6;
}