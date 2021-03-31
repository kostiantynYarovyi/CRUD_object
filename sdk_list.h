#if !defined (__SDKLIST_H_)
#define __SDKLIST_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "curdattribute.h"


struct lnode {
    struct lnode *next;
    crud_attribute_t* listattribute;
    uint16_t object_id;
    uint16_t object_type;
    uint32_t count;
};  


struct lobject {
    struct lnode *head;
    int size;
}*list_port_object, *list_switch_object;




struct lobject* create_list_swirch_object(); 

struct lobject* create_list_port_object();

struct lobject* get_list_swirch_object(); 

struct lobject* get_list_port_object();


uint32_t add_node(struct lobject* newList, const uint16_t object_type, crud_attribute_t* listattribute);

struct lnode* get_node(struct lobject* newList, const crud_object_id_t object_id);

crud_status_t delete_node(struct lobject* newList, const crud_object_id_t object_id);

#endif