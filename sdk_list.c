
#include "sdk_list.h"

struct lobject* newList;

struct lobject* create_list_object(){
    newList = (struct lobject*) malloc(sizeof(struct lobject));
    if(newList){
        newList->size = 0;
        newList->head = NULL;
        return newList;
    }
    return 0;
}
 

struct lobject* get_list_object(){
    return newList;
}



uint32_t add_node(struct lobject* newList, const uint16_t object_type, crud_attribute_t* listattribute){
    uint32_t object_id = 0;
    uint16_t id = 0;
    struct lnode* node = (struct lnode*)malloc(sizeof(struct lnode));

    if(node)
    {
        struct lnode* current = newList->head;

        while (current->next != NULL)
        {
            current = current->next;
            id++;
        }
        
        node->next = NULL;
        node->count = 0;
        node->object_type = object_type;
        node->listattribute = *listattribute;
        node->object_id = id;
        newList->size++;

        current->next = node;
        object_id = (object_type << 16) | id;
        printf("add_node: node add and create\n");
    }else
        printf("add_node: fail !node\n");

    return object_id;
}

struct lnode* get_node(struct lobject* newList, const crud_object_id_t object_id){
    if(newList){
       struct lnode* current =  newList->head;

        uint16_t id = object_id &0xffff;
        while(current->next != NULL){   
            if(current->object_id == object_id)
                break;
            current = current->next;
        }
        return current;
    }
    printf("get_node: fail List is absetn\n");
    return 0;
}

crud_status_t delete_node(struct lobject* newList, const crud_object_id_t object_id){
    if(newList){
        struct lnode* current =  newList->head;
        
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
    printf("get_node: fail List is absetn\n");
    return 6;
}