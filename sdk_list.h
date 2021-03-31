#if !defined (__SDKLIST_H_)
#define __SDKLIST_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "curdattribute.h"


struct lnode {
    struct lnode *next;
    crud_attribute_t listattribute;
    uint16_t object_id;
    uint16_t object_type;
    uint32_t count;
};  


struct lobject {
    struct lnode *head;
    int size;
};




struct lobject* create_list_object(); //+

struct lobject* get_list_object(); //+

uint32_t add_node(struct lobject* newList, const uint16_t object_type, crud_attribute_t listattribute); //+

//struct lnode* new_node(const uint16_t object_type, crud_attribute_t listattribute);

struct lnode* get_node(const crud_object_id_t object_id);

crud_status_t delete_node(const crud_object_id_t object_id);

#endif