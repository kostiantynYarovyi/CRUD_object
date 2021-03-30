

#include "curdadapter.h"


struct object{
    crud_attribute_t istattribute;
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
    int size;
}*ListPort;


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



void create_adapter(){
    static struct llist *ListSwitch;
    //static struct llist *ListPort;

    ListSwitch = new_list();
    ListPort = new_list();
}




crud_status_t create_object(crud_attribute_t* attr_list, uint32_t attr_count, crud_object_id_t* object_id)
{
    printf("create_object: open\n");
    if (attr_count <= 0 || NULL == object_id || NULL == attr_list)
    {
        printf("create_object_1: attr_count = %d\n", attr_count);
        printf("create_object_1: object_id = %p\n", object_id);
        printf("create_object_1: attr_list = %p\n", attr_list);
        printf("create_object_1: CRUD_INVALID_PARAM\n");
        return 3;
    }
        

    bool chekTypePortObject = false;
    bool chekTypeSwitchObject = false;

    struct object* buff;
    for (uint32_t i = 0; i < attr_count; ++i) {
        
        switch (attr_list[i].id)
        {
        case CRUD_PORT_ATTR_STATE:
            buff->istattribute.value.booldata = attr_list[i].value.booldata;
            printf("create_object_chekTypePortObject_0: set Port type bool\n");
            chekTypePortObject = true;
            break;
        case CRUD_PORT_ATTR_SPEED:
            if((attr_list[i].value.u32 == 10) || (attr_list[i].value.u32 == 100) || (attr_list[i].value.u32 == 1000)){
                printf("create_object_chekTypePortObject_1: set Port type\n");
                buff->istattribute.value.u32 = attr_list[i].value.u32;
            }
            chekTypePortObject = true;
            break;
        case CRUD_PORT_ATTR_IPV4:
            if(true)
            {
                printf("create_object_chekTypePortObject_2: set Port type\n");
                buff->istattribute.value.ip4 = attr_list[i].value.ip4;
            }
            chekTypePortObject = true;
            break;
        case CRUD_PORT_ATTR_MTU:
            if((attr_list[i].value.u32 > 64) && (attr_list[i].value.u32 < 9000)){
                printf("create_object_chekTypePortObject_3: set Port type\n");
                buff->istattribute.value.u32 = attr_list[i].value.u32;
            }
            chekTypePortObject = true;
            break;

        case CRUD_SWITCH_ATTR_NAME:
            printf("create_object_chekTypeSwitchObject_4: set Switch type name\n");
            strcpy(buff->istattribute.value.chardata, attr_list[i].value.chardata);
            chekTypeSwitchObject = true;
            break;
        case CRUD_SWITCH_ATTR_HASH_SEED:
            printf("create_object_chekTypeSwitchObject_5: set Switch type\n");
            buff->istattribute.value.u32 = attr_list[i].value.u32;
            chekTypeSwitchObject = true;
            break;
        case CRUD_SWITCH_ATTR_SPLIT_MODE:
            printf("create_object_chekTypeSwitchObject_6: set Switch type\n");
            //buff.value.ip4 = attr_list->value.ip4;
            chekTypeSwitchObject = true;
            break;
        case CRUD_SWITCH_ATTR_MAX_PORTS:
            printf("create_object_chekTypeSwitchObject_7: set Switch type\n");
            //buff.value.u32 = attr_list->value.u32;
            chekTypeSwitchObject = true;
            break;
        }
    }

    if(chekTypeSwitchObject && chekTypePortObject)
    {
        printf("create_object _2: CRUD_INVALID_PARAM\n");
        return 3;
    }
        
    
    uint16_t first, second = 0;

    if(chekTypeSwitchObject)
    {
        //l_insert(ListSwitch, buff);
        printf("create_object: set Swith type\n");
        second = 1;
    }

    if(chekTypePortObject)
    {
        l_insert(ListPort, buff);
        printf("create_object: set Port type\n");
        second = 2;
    }
    
    *object_id = (first << 16) | second;
    buff->count = 0;
    buff->object_id = object_id;
    //printf("create_object: object_id = %p\n", *object_id);
    
    return 0;
}

crud_status_t read_object(crud_object_id_t *object_id, crud_attribute_t* attr_list, uint32_t attr_count){
    printf("create_object: open\n");
    if (attr_count <= 0 || NULL == object_id || NULL == attr_list)
    {
        printf("create_object_1: attr_count = %d\n", attr_count);
        printf("create_object_1: object_id = %p\n", object_id);
        printf("create_object_1: attr_list = %p\n", attr_list);
        printf("create_object_1: CRUD_INVALID_PARAM\n");
        return 3;
    }

    for (uint32_t i = 0; i < attr_count; ++i) {
        
        
    }

    return 0;
}



crud_status_t delete_object(crud_object_id_t *object_id)
{

    uint16_t first_int;
    first_int = *(object_id) & 0xffff;

    if(false)
        return 5;

    l_delete(ListPort, (void *) first_int);

    return 0;
}
