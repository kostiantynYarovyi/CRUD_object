
#include "sdk_list.h"

int main()
{

    crud_attribute_t attr_list[2];
    attr_list[0].id = 2;
    attr_list[1].id = 5;
    crud_attribute_t* attr_list_1 = attr_list[2];
    struct lobject* list = create_list_object();
    //add_node(list, 2, attr_list_1);
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