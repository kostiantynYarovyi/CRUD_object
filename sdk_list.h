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
    uint32_t countAttr;
};  


struct lobject {
    struct lnode *head;
    uint32_t size;
    uint32_t count_id;
    int state;
};




struct lobject* create_list_swirch_object(); 

struct lobject* create_list_port_object();

struct lobject* get_list_switch_object(); 

struct lobject* get_list_port_object();

uint32_t get_list_size(struct lobject* List);


uint32_t add_node(struct lobject* newList, const uint16_t object_type, crud_attribute_t* listattribute, uint32_t attr_count);

struct lnode* get_node(struct lobject* List, const crud_object_id_t object_id);

bool get_attr_node(struct lnode* node, const  uint32_t id, uint32_t* get_id);

crud_status_t delete_node(struct lobject* List, const crud_object_id_t object_id);

void add_new_attr(struct lnode* node,  crud_attribute_t attr);

#endif
