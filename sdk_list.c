
#include "sdk_list.h"

struct lobject* list_port_object; 
struct lobject* list_switch_object;


struct lobject* create_list_port_object(){
    list_port_object = (struct lobject*) malloc(sizeof(struct lobject));
    if(list_port_object){
        list_port_object->size = 0;
        list_port_object->head = 0;
        list_port_object->count_id = 0;
        //printf("sdk_list___create_list_port_object:  create object \n");
        return list_port_object;
    }
    //printf("sdk_list___create_list_port_object: return 0 \n");
    return 0;
}

struct lobject* create_list_swirch_object(){
    list_switch_object = (struct lobject*) malloc(sizeof(struct lobject));
    if(list_switch_object){
        list_switch_object->size = 0;
        list_switch_object->head = 0;
        list_switch_object->count_id = 0;
        //printf("sdk_list___create_list_swirch_object:  create object \n");
        return list_switch_object;
    }
    //printf("sdk_list___create_list_swirch_object: return 0 \n");
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

crud_status_t add_node(struct lobject* List, const uint16_t object_type, crud_attribute_t* listattribute, uint32_t attr_count, uint32_t* object_id){
    //printf("++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    //printf("sdk_list___add_node\n");
    struct lnode* node = (struct lnode*)malloc(sizeof(struct lnode));

    if(node){

        node->listattribute = (crud_attribute_t*)malloc(sizeof(crud_attribute_t)*attr_count);

        if(node->listattribute)
        { 
            //printf("add_node: sizeof(listattribute) %lu \n",  sizeof(crud_attribute_t));
            node->next = NULL;
            node->countAttr = attr_count;
            node->object_type = object_type;
            for(uint32_t i = 0; i < attr_count; ++i){
                node->listattribute[i].id = listattribute[i].id;
                node->listattribute[i].value = listattribute[i].value;
            }
            
            node->object_id = List->size;
            
            node->next = List->head;
            
            List->head = node;
            List->size++;
            List->count_id++;

            *object_id = (object_type << 16) | node->object_id;
           /* printf("\n\nadd_node:  node->object_id %u \n",   node->object_id);
            printf("add_node: object_id %u \n\n\n",   *object_id);

            printf("add_node: booldata %u \n",  node->listattribute[0].value.booldata);
            printf("add_node: u32 %u \n",  node->listattribute[1].value.u32);
            printf("add_node: ip4 %u \n",  node->listattribute[2].value.ip4);
            printf("add_node: u32 %u \n",  node->listattribute[3].value.u32);
            
            printf("\n add_node |||||||||||||||||: id  %p \n\n", node->listattribute);
            */
        // printf("++++++++++++++++++++++++++++++++++++++++++++++++++\n");
            return 0;
        }   
    }
    //printf("sdk_list___add_node: fail !node\n");
    //printf("++++++++++++++++++return 0+++++++++++++++++++++++\n");
    return CRUD_CREATE_OBJ_FAILED;
}

struct lnode* get_node(struct lobject* List, const crud_object_id_t object_id){
    if(List){
       struct lnode* current =  List->head;
       // printf("\nget_node |||||||||||||||||: List->head  %p \n\n", List->head->next->listattribute);
        
        uint16_t id = object_id &0xffff;
       
        while(current != NULL){   
        //    printf("current != NULL current->object_id = %u\n", current->object_id);
            if(current->object_id == id)
            {


               
                /*printf("\nget_node |||||||||||||||||: current->listattribute  %p \n\n", current->listattribute);
                printf("\nget_node |||||||||||||||||: List->head->listattribute  %p \n\n", List->head->listattribute);
                printf("get_node: object_id %u \n",  object_id);

                printf("get_node: booldata %u \n",  current->listattribute[0].value.booldata);
                printf("get_node: u32 %u \n",  current->listattribute[1].value.u32);
                printf("get_node: ip4 %u \n",  current->listattribute[2].value.ip4);
                printf("get_node: u32 %u \n",  current->listattribute[3].value.u32);
                */
                return current;
            }
            //printf(" current->next\n");    
            current = current->next;
        }
        //printf("sdk_list___get_node: fail List out of range\n");
        return 0;
    }
    //printf("sdk_list___get_node: fail List is absetn\n");
    return 0;
}

crud_status_t delete_node(struct lobject* List, const crud_object_id_t object_id){
    if(List){
        struct lnode* node;
        struct lnode* prev;

        //printf("sdk_list___delete_node: object_id =  %u \n", (object_id & 0xffff));

        for (node = List->head; (node != 0 && node->object_id != (object_id & 0xffff)); node = node->next){
            //printf("sdk_list___delete_node: node->object_id =  %u \n", node->object_id);
		    prev = node;
	    }

        if (node == 0){
            //printf("sdk_list___delete_node:return CRUD_NODE_IS_ABSENT  \n");
		    return CRUD_NODE_IS_ABSENT;
	    }
        
        if (prev){
            if (node == List->head) {
                List->head = node->next;
            } 
            else {
                prev->next = node->next;
            }
            free(node->listattribute);
            free(node);
            List->size--;
           // printf("sdk_list___delete_node:return CRUD_STATUS_SUCCESS  \n");
            return CRUD_STATUS_SUCCESS;
        }
       // printf("sdk_list___delete_node:return CRUD_STATUS_FAILURE  \n");
        return CRUD_STATUS_FAILURE;
    }
   // printf("sdk_list___delete_node: fail List is absetn\n");
    return CRUD_LIST_IS_ABSENT;
}

uint32_t get_list_size(struct lobject* List){
    return List->size;
}

bool get_attr_node(struct lnode* node, const  uint32_t id, uint32_t* get_id){
    for(uint32_t i = 0; i < node->countAttr; i++){
        if(node->listattribute[i].id == id){
            *get_id = i;
            return true;
        }
    }
    return false;
}

void add_new_attr(struct lnode* node,  crud_attribute_t attr){
   // printf("add_new_attr\n");
    node->listattribute[node->countAttr].id = attr.id;
    node->listattribute[node->countAttr].value = attr.value;
}