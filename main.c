
#include "sdk_list.h"
#include "sdk_api.h"

crud_status_t create_object(crud_attribute_t* attr_list, uint32_t attr_count, crud_object_id_t* object_id);

crud_status_t read_object(crud_object_id_t *object_id, crud_attribute_t* attr_list, uint32_t attr_count);

crud_status_t delete_object(crud_object_id_t *object_id);

int main()
{
    crud_object_id_t object_id_1 = 0;
    crud_object_id_t object_id_2 = 0;
    crud_object_id_t object_id_3 = 0;
    crud_status_t buff;
    //printf("object: %u \n", object_id);
    printf("####################################################\n");
    uint32_t attr_count = 3;
    uint32_t test = 5;
    crud_attribute_t attr_list[attr_count];
    crud_attribute_t attr_list_2[attr_count];
    for (uint32_t i = 0; i < attr_count; ++i)
    {
        attr_list[i].id = i + test;
        attr_list_2[i].id = i + test;
    }
    attr_list[0].value.u32 = 1000;
    attr_list[1].value.ip4 = 0b10100000000000000000000000000000;
    attr_list[2].value.u32 = 64;
//####################################################
printf("####################################################\n");
    buff = create_object(attr_list, attr_count, &object_id_1);
    //printf("\n\n\n\n");
     printf("buff == : %u \n", buff);
printf("####################################################\n");
/*
    create_object(attr_list, attr_count, &object_id_2);
    //printf("\n\n\n\n");
    create_object(attr_list, attr_count, &object_id_3);

    printf("object_id_1: %u \n",  attr_list[0].value.u32);
    printf("object_id_2: %u \n",  attr_list[1].value.ip4);
    printf("object_id_3: %u \n",  attr_list[2].value.u32);

    printf("object_id_1: %u \n",  attr_list_2[0].value.u32);
    printf("object_id_2: %u \n",  attr_list_2[1].value.ip4);
    printf("object_id_3: %u \n",  attr_list_2[2].value.u32);

    //crud_attribute_t* attr_list_1 = attr_list[2];
    //struct lobject* list = create_list_object();
    printf("####################################################\n");
    buff = read_object(&object_id_2, attr_list_2, attr_count);
    printf("buff == : %u \n", buff);

    printf("####################################################\n");
    printf("object_id_1: %u \n",  attr_list_2[0].value.u32);
    printf("object_id_2: %u \n",  attr_list_2[1].value.ip4);
    printf("object_id_3: %u \n",  attr_list_2[2].value.u32);
    /*
    printf("object_id_1: %u \n", object_id_1);
    printf("object_id_2: %u \n", object_id_2);
    printf("object_id_3: %u \n", object_id_3);
    printf("\n\n\n\n");
    printf(" list port size: %u \n", get_list_size(get_list_port_object()));
    delete_object(&object_id_3);
    printf(" list port size: %u \n", get_list_size(get_list_port_object()));

    */
    //printf("get_list_port_object()_1: %u \n", get_list_port_object()->head->object_id);
    /*struct lnode* node =  get_node(get_list_port_object(),0);
   
    printf("get_node(get_list_port_object(),0): %u \n", node->object_id);
    node =  get_node(get_list_port_object(),1);
    
    printf("get_node(get_list_port_object(),0): %u \n", node->object_id);
    node =  get_node(get_list_port_object(),3);
    printf("get_node(get_list_port_object(),0): %u \n", node->object_id);
    */
    
    //add_node(list, 2, attr_list);
    //add_node(list, 2,attr_list[0]);


 /*   crud_attribute_t attr_list[2];
    attr_list[0].id = 2;
    attr_list[1].id = 5;

    uint32_t attr_count = 2;
    crud_object_id_t* object_id = 9;

    create_object( attr_list,  attr_count, object_id);
    //printf("main: object_id = %p\n", *object_id);

    */
    return 0;
}