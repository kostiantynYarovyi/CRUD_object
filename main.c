
#include "sdk_list.h"
#include "sdk_api.h"

int main()
{

    crud_object_id_t* object_id = 0;
    uint32_t attr_count = 10;
    crud_attribute_t attr_list[2];
    for (uint32_t i = 0; i < attr_count; ++i)
    {
        attr_list[i].id = i;
        attr_list[i].value.u32 = i;
    }
//####################################################
    create_object(attr_list, attr_count, object_id);
    //crud_attribute_t* attr_list_1 = attr_list[2];
    //struct lobject* list = create_list_object();
    printf("object: %d \n", attr_count);
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