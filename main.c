
#include "sdk_list.h"
#include "sdk_api.h"

crud_status_t create_object(crud_attribute_t* attr_list, uint32_t attr_count, crud_object_id_t* object_id);

crud_status_t read_object(crud_object_id_t *object_id, crud_attribute_t* attr_list, uint32_t attr_count);

crud_status_t update_object(crud_object_id_t *object_id, crud_attribute_t* attr_list, uint32_t attr_count);

crud_status_t delete_object(crud_object_id_t *object_id);

int main()
{
    crud_object_id_t object_id_1 = 0;
    crud_object_id_t object_id_2 = 0;
    crud_object_id_t object_id_3 = 0;
    crud_status_t buff;
    //printf("object: %u \n", object_id);
    printf("####################################################\n");
    uint32_t attr_count = 4;
    uint32_t test = 4;
    crud_attribute_t attr_list[attr_count];
    crud_attribute_t attr_list_2[3];
    crud_attribute_t attr_list_3[attr_count];

    attr_list_2[0].id = 4;
    attr_list_2[1].id = 5;
    attr_list_2[2].id = 6;

    for (uint32_t i = 0; i < attr_count; ++i)
    {
        attr_list[i].id = i + test;
        attr_list_3[i].id = i + test;
    }
    attr_list[0].value.u32 = true;
    attr_list[1].value.u32 = 1000;
    attr_list[2].value.ip4 = 0b10100000000000000000000000000000;
    attr_list[3].value.u32 = 64;

    attr_list_2[0].value.u32 = true;
    attr_list_2[1].value.u32 = 10;
    attr_list_2[2].value.ip4 = 0b10100100000000000000000000000000;
    //attr_list_2[3].value.u32 = 6575;

    attr_list_3[0].value.u32 = 0;
    attr_list_3[1].value.u32 = 0;
    attr_list_3[2].value.ip4 = 0;
    attr_list_3[3].value.u32 = 0;
    int* ptr;

printf("####################################################\n");
printf("###---------------create_object-----------------####\n");
printf("####################################################\n");
buff =  create_object(attr_list, attr_count, &object_id_1);
        create_object(attr_list, attr_count, &object_id_2);
        create_object(attr_list, attr_count, &object_id_3);
    printf("create_object: Status == : %u \n", buff);
    printf("\n\n");
    printf("object_id_1: State =  %u \n",  attr_list[0].value.booldata);
    printf("object_id_1: SPEED =  %u \n",  attr_list[1].value.u32);
    printf("object_id_1: IPv4  =  %u \n",  attr_list[2].value.ip4);
    printf("object_id_1: Mtu   =  %u \n",  attr_list[3].value.u32);

    printf("object_id_1: id    =  %u \n",  ( object_id_1        & 0xffff));
    printf("object_id_1: type  =  %u \n",  ((object_id_1 >> 16) & 0xffff));
printf("\n\n\n\n");


printf("####################################################\n");
printf("###---------------update_object-----------------####\n");
printf("####################################################\n");
    printf("object_id_1: id    =  %u \n",  ( object_id_1        & 0xffff));
    printf("object_id_1: type  =  %u \n",  ((object_id_1 >> 16) & 0xffff));
buff = update_object(&object_id_1, attr_list_2, 3);
    
    printf("create_object: Status == : %u \n", buff);
    printf("\n\n");
printf("\n\n\n\n");


printf("####################################################\n");
printf("###----------------read_object------------------####\n");
printf("####################################################\n");
printf("-------------attr_list_3 before read----------------\n");
    printf("attr_list_3: State =  %u \n",  attr_list_3[0].value.booldata);
    printf("attr_list_3: SPEED =  %u \n",  attr_list_3[1].value.u32);
    printf("attr_list_3: IPv4  =  %u \n",  attr_list_3[2].value.ip4);
    printf("attr_list_3: Mtu   =  %u \n",  attr_list_3[3].value.u32);
printf("----------------------------------------------------\n");
printf("\n\n");
buff = read_object(&object_id_1, attr_list_3, attr_count);
    printf("\n\n"); 
    printf("read_object: Status == : %u \n", buff);
    printf("object_id_1: attr_list_3 State =  %u \n",  attr_list_3[0].value.booldata);
    printf("object_id_1: attr_list_3 SPEED =  %u \n",  attr_list_3[1].value.u32);
    printf("object_id_1: attr_list_3 IPv4  =  %u \n",  attr_list_3[2].value.ip4);
    printf("object_id_1: attr_list_3 Mtu   =  %u \n",  attr_list_3[3].value.u32);

    printf("object_id_1: id    =  %u \n",  ( object_id_1        & 0xffff));
    printf("object_id_1: type  =  %u \n",  ((object_id_1 >> 16) & 0xffff));
printf("\n\n\n\n");


printf("####################################################\n");
printf("###---------------delete_object-----------------####\n");
printf("####################################################\n");
buff = delete_object(&object_id_1);
printf("delete_object: Status == : %u \n", buff);
buff = read_object(&object_id_1, attr_list_3, attr_count);
printf("read_object: Status == : %u \n", buff);
printf("####################################################\n");
printf("\n\n\n\n");

/**/
    return 0;
}