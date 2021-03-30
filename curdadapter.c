

#include "curdadapter.h"


struct object{
    crud_attribute_t *listattribute[32];
    crud_object_id_t object_id;
    uint32_t count;
};

//####################################################################################3
struct lnode {
  struct lnode *next;
  void *item;
};  /* <---- note the semicolon */

/* The definition of what a llist (linked list) is.  */
struct llist {
    struct lnode *head;
    //struct object object;
    int size;
};


/* Functions that operate on llists */

/* -----------------------------------------------------------------
 * struct llist * new_list(void)
 * 
 * A function that is basically a list constructor.
 * Returns a pointer to a llist structure.
 * ----------------------------------------------------------------- */
struct llist* new_list() {   
  struct llist *lst;
  /* our first use of malloc().  Allocates enough space for a 
     llist structure, casts the void pointer returned by malloc() to 
     the correct type (struct llist pointer) and stores that pointer in lst.*/
  lst = (struct llist *) malloc(sizeof(struct llist));

  /* malloc returns 0 on error */
  if (lst == NULL) {
    fprintf(stderr, "new_list() : malloc error");
    return NULL;
  }

  /* initialize the list size and the list head */
  lst->head = 0;
  lst->size = 0;
  return lst;
}

/* -----------------------------------------------------------------
 * struct new_node * new_node(void *item)
 *
 * Function that works like a constructor for lnodes.
 * Takes a void pointer and returns a pointer to a struct lnode.
 * ----------------------------------------------------------------- */
struct lnode* new_node(void *item) {
  struct lnode *node;
  node = (struct lnode *) malloc (sizeof (struct lnode));
  if (node == NULL) {
    fprintf(stderr, "new_node() : malloc error");
    return NULL;
  }
  node->item = item;
  node->next = 0;
  return node;
}  


/* -----------------------------------------------------------------
 * int l_insert(struct llist *ls, void *item)
 *
 * Insert function for a list.  Takes a pointer 'ls' to the list on 
 * which we want to insert 'item'.
 * Returns 0 on error, 1 otherwise.
 * ----------------------------------------------------------------- */
int l_insert(struct llist *ls, void *item) {
  struct lnode *node;
  /* get a new node */
  node = new_node(item);
  if (node == NULL) return 0;
  
  /* insert the node at the head of the list */
  node->next = ls->head;
  ls->head = node;  
  (ls->size)++;
  return 1;
}

/* -----------------------------------------------------------------
 * int l_delete(struct llist *ls, void *item) {
 *
 * Searches list 'ls' for 'item' and removes it from the list.
 * Returns 1 if found or 0 otherwise.
 * ----------------------------------------------------------------- */
int l_delete(struct llist *ls, void *item) {
  struct lnode *node;
  struct lnode *prev;
  
  /* iterate through the list looking for 'item'. */
  for (node = ls->head; node != NULL && node->item != item; node = node->next) {
    prev = node;
  }
  if (node == NULL) {
    printf("Item not found\n");
    return 0; /* 'item' not found */
  }

  /* Do bookkeeping on the list */
  if (node == ls->head) {
    ls->head = node->next;
  } else {
    prev->next = node->next;
  }

  (ls->size)--;
  

  free(node);
  return 1;
}


//####################################################################################3







crud_status_t create_object(crud_attribute_t* attr_list, uint32_t attr_count, crud_object_id_t* object_id)
{
    if (attr_count <= 0 || NULL == object_id || NULL == attr_list)
        return 3;

    bool chekTypePortObject = false;
    bool chekTypeSwitchObject = false;

   
    
    for (uint32_t i = 0; i < attr_count; ++i) {
        switch (attr_list->id)
        {
        case CRUD_PORT_ATTR_STATE:
            //buff.listattribute[freeElement]->value.booldata = attr_list->value.booldata;
            chekTypePortObject = true;
            break;
        case CRUD_PORT_ATTR_SPEED:
            //
            chekTypePortObject = true;
            break;
        case CRUD_PORT_ATTR_IPV4:
            //buff.value.ip4 = attr_list->value.ip4;
            chekTypePortObject = true;
            break;
        case CRUD_PORT_ATTR_MTU:
            //buff.value.u32 = attr_list->value.u32;
            chekTypePortObject = true;
            break;

        case CRUD_SWITCH_ATTR_NAME:
            //strcpy(buff.value.chardata, attr_list->value.chardata);
            chekTypeSwitchObject = true;
            break;
        case CRUD_SWITCH_ATTR_HASH_SEED:
            //strcpy(buff.value.chardata, attr_list->value.chardata);
            chekTypeSwitchObject = true;
            break;
        case CRUD_SWITCH_ATTR_SPLIT_MODE:
            //buff.value.ip4 = attr_list->value.ip4;
            chekTypeSwitchObject = true;
            break;
        case CRUD_SWITCH_ATTR_MAX_PORTS:
            //buff.value.u32 = attr_list->value.u32;
            chekTypeSwitchObject = true;
            break;
        }
    }
    if(chekTypeSwitchObject && chekTypePortObject)
        return 3;
    
    uint16_t first, second = 0;

    if(chekTypeSwitchObject)
    {
        second = 1;
    }

    if(chekTypePortObject)
    {
        second = 2;
    }
    
    object_id = (first << 16) | second;
    
    return 0;
}

