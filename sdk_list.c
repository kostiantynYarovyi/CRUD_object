
#include "sdk_list.h"

struct lobject* list_port_object; 
struct lobject* list_switch_object;

struct lobject* create_list_port_object(){
    list_port_object = (struct lobject*) malloc(sizeof(struct lobject));
    if(list_port_object){
        list_port_object->size = 0;
        list_port_object->head = 0;
        list_port_object->count_id = 0;
        printf("sdk_list___create_list_port_object:  create object \n");
        return list_port_object;
    }
    printf("sdk_list___create_list_port_object: return 0 \n");
    return 0;
}

struct lobject* create_list_swirch_object(){
    list_switch_object = (struct lobject*) malloc(sizeof(struct lobject));
    if(list_switch_object){
        list_switch_object->size = 0;
        list_switch_object->head = 0;
        list_switch_object->count_id = 0;
        printf("sdk_list___create_list_swirch_object:  create object \n");
        return list_switch_object;
    }
    printf("sdk_list___create_list_swirch_object: return 0 \n");
    return 0;
}
 

struct lobject* get_list_port_object(){
    //printf("sdk_list___get_list_port_object\n");
    return list_port_object;
}

struct lobject* get_list_switch_object(){
    //printf("sdk_list___get_list_swirch_object\n");
    return list_switch_object;
}

uint32_t add_node(struct lobject* List, const uint16_t object_type, crud_attribute_t* listattribute, uint32_t attr_count){
    //printf("++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    printf("sdk_list___add_node\n");
    uint32_t object_id = 0;
    struct lnode* node = (struct lnode*)malloc(sizeof(struct lnode));

    if(node){
       
        node->next = NULL;
        node->countAttr = attr_count;
        node->object_type = object_type;
        node->listattribute = listattribute;
        node->object_id = List->size;
        
        node->next = List->head;
		List->head = node;
        List->size++;
        List->count_id++;
		
        object_id = (object_type << 16) | node->object_id;
        return object_id;
    }
    printf("sdk_list___add_node: fail !node\n");
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
        printf("sdk_list___get_node: fail List out of range\n");
        return 0;
    }
    printf("sdk_list___get_node: fail List is absetn\n");
    return 0;
}

crud_status_t delete_node(struct lobject* List, const crud_object_id_t object_id){
    if(List){
        struct lnode* node;
        struct lnode* prev;

        printf("sdk_list___delete_node: object_id =  %d \n", object_id);

        for (node = List->head; (node != 0 && node->object_id != object_id); node = node->next){
		    prev = node;
	    }

        if (node == 0){
		    return CRUD_NODE_IS_ABSENT;
	    }
        
        if (prev){
            if (node == List->head) {
                List->head = node->next;
            } 
            else {
                prev->next = node->next;
            }
            free(node);
            List->size--;
            return 0;
        }
        return CRUD_STATUS_FAILURE;
    }
    printf("sdk_list___delete_node: fail List is absetn\n");
    return CRUD_LIST_IS_ABSENT;
}

uint32_t get_list_size(struct lobject* List){
    return List->size;
}

bool get_attr_node(struct lnode* node, const  uint32_t id, uint32_t* get_id){
    for(uint32_t i = 0; i < node->countAttr; i++){
        //printf("get_attr_node: node->listattribute[i].id = %u \n", node->listattribute[i].id);
        //printf("get_attr_node: id = %u \n", id);
        if(node->listattribute[i].id == id){
            *get_id = i;
            return true;
        }
    }
    return false;
}