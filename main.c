
#include <assert.h>
#include "sdk_list.h"
#include "sdk_api.h"


crud_status_t create_object(crud_attribute_t* attr_list, uint32_t attr_count, crud_object_id_t* object_id);

crud_status_t read_object(crud_object_id_t *object_id, crud_attribute_t* attr_list, uint32_t attr_count);

crud_status_t update_object(crud_object_id_t *object_id, crud_attribute_t* attr_list, uint32_t attr_count);

crud_status_t delete_object(crud_object_id_t *object_id);

#define PORT // SWITCH
int main(void)
{
#ifdef PORT
    crud_attribute_t attr_list[10];
    crud_object_id_t port_oid[33] = {0};
    attr_list[0].id = CRUD_PORT_ATTR_STATE;
    attr_list[0].value.booldata = true;
    attr_list[1].id = CRUD_PORT_ATTR_SPEED;
    attr_list[1].value.u32 = 1000;
    attr_list[2].id = CRUD_PORT_ATTR_IPV4;
    attr_list[2].value.ip4 = 0x11223344;
    attr_list[3].id = CRUD_PORT_ATTR_MTU;
    attr_list[3].value.u32 = 100;
    // valid create
    for (int i = 0; i < 32; i++) { 
        assert(create_object(&attr_list, i % 4 + 1, &port_oid[i]) == CRUD_STATUS_SUCCESS);
        assert(((uint32_t) port_oid[i]) >> 16 == CRUD_OBJECT_TYPE_PORT);
        printf("Created port %02d, OID: %08X\n", i, port_oid[i]);
    }
    // invalid create 33
    port_oid[32] = 0;
    assert(create_object(&attr_list, 4, &port_oid[32]) != CRUD_STATUS_SUCCESS);
    assert(port_oid[32] == 0);
    // valid remove
    for (int i = 0; i < 32; i++) { 
        assert(delete_object(&port_oid[i]) == CRUD_STATUS_SUCCESS);
        printf("Removed port %02d, OID: %08X\n", i, port_oid[i]);
    }
    // invalid remove
    assert(delete_object(&port_oid[33]) != CRUD_STATUS_SUCCESS);
    // invalid create (out-of-range)
    //attr_list[1].id = CRUD_PORT_ATTR_SPEED;
    attr_list[1].value.u32 = 2000;
    port_oid[0] = 0;
    assert(create_object(&attr_list, 4, &port_oid[0]) != CRUD_STATUS_SUCCESS);
    assert(port_oid[0] == 0);
    //attr_list[2].id = CRUD_PORT_ATTR_IPV4;
    attr_list[2].value.ip4 = 0;
    assert(create_object(&attr_list, 4, &port_oid[0]) != CRUD_STATUS_SUCCESS);
    assert(port_oid[0] == 0);
    //attr_list[2].id = CRUD_PORT_ATTR_IPV4;
    attr_list[2].value.ip4 = 0xFFFFFFFF;
    assert(create_object(&attr_list, 4, &port_oid[0]) != CRUD_STATUS_SUCCESS);
    assert(port_oid[0] == 0);
    //attr_list[2].id = CRUD_PORT_ATTR_IPV4;
    attr_list[2].value.ip4 = 0xEF010101;
    assert(create_object(&attr_list, 4, &port_oid[0]) != CRUD_STATUS_SUCCESS);
    assert(port_oid[0] == 0);
    //attr_list[2].id = CRUD_PORT_ATTR_IPV4;
    attr_list[2].value.ip4 = 0xE0000000;
    assert(create_object(&attr_list, 4, &port_oid[0]) != CRUD_STATUS_SUCCESS);
    assert(port_oid[0] == 0);
    //attr_list[3].id = CRUD_PORT_ATTR_MTU;
    attr_list[3].value.u32 = 32;
    assert(create_object(&attr_list, 4, &port_oid[0]) != CRUD_STATUS_SUCCESS);
    assert(port_oid[0] == 0);
    //attr_list[3].id = CRUD_PORT_ATTR_MTU;
    attr_list[3].value.u32 = 2000;
    assert(create_object(&attr_list, 4, &port_oid[0]) != CRUD_STATUS_SUCCESS);
    assert(port_oid[0] == 0);
    // same attribute twice
    attr_list[0].id = CRUD_PORT_ATTR_STATE;
    attr_list[0].value.booldata = true;
    attr_list[1].id = CRUD_PORT_ATTR_SPEED;
    attr_list[1].value.u32 = 1000;
    attr_list[2].id = CRUD_PORT_ATTR_IPV4;
    attr_list[2].value.ip4 = 0x11223344;
    attr_list[3].id = CRUD_PORT_ATTR_IPV4;
    attr_list[3].value.ip4 = 0x11223344;
    assert(create_object(&attr_list, 4, &port_oid[0]) != CRUD_STATUS_SUCCESS);
    assert(port_oid[0] == 0);
    // no attr or NULLs
    assert(create_object(&attr_list, 0, &port_oid[0]) != CRUD_STATUS_SUCCESS);
    assert(port_oid[0] == 0);
    assert(create_object(NULL, 2, &port_oid[0]) != CRUD_STATUS_SUCCESS);
    assert(port_oid[0] == 0);
    assert(create_object(&attr_list, 3, NULL) != CRUD_STATUS_SUCCESS);
#else
    crud_attribute_t attr_list[10];
    crud_object_id_t switch_oid[2] = {0};
    attr_list[0].id = CRUD_SWITCH_ATTR_NAME;
    attr_list[0].value.chardata = "This is my switch";
    attr_list[1].id = CRUD_SWITCH_ATTR_HASH_SEED;
    attr_list[1].value.u32 = 1000;
    attr_list[2].id = CRUD_SWITCH_ATTR_SPLIT_MODE;
    attr_list[2].value.u32 = 0;
    attr_list[3].id = CRUD_SWITCH_ATTR_MAX_PORTS;
    attr_list[3].value.u32 = 1;
    // valid create
    assert(create_object(&attr_list, 4, &switch_oid[0]) == CRUD_STATUS_SUCCESS);
    assert(((uint32_t) switch_oid[0]) >> 16 == CRUD_OBJECT_TYPE_SWITCH);
    printf("Created switch %02d, OID: %08X\n", i, switch_oid[0]);
    // invalid create #2
    switch_oid[1] = 0;
    assert(create_object(&attr_list, 4, &switch_oid[1]) != CRUD_STATUS_SUCCESS);
    assert(switch_oid[1]) == 0);
    assert(delete_object(&switch_oid[0]) == CRUD_STATUS_SUCCESS);
    printf("Removed sw %02d, OID: %08X\n", i, switch_oid[0]);
    // partial create
    assert(create_object(&attr_list, 2, &switch_oid[0]) == CRUD_STATUS_SUCCESS);
    assert(((uint32_t) switch_oid[0]) >> 16 == CRUD_OBJECT_TYPE_SWITCH);
    printf("Created switch %02d, OID: %08X\n", i, switch_oid[0]);
    assert(delete_object(&switch_oid[0]) == CRUD_STATUS_SUCCESS);
    printf("Removed sw %02d, OID: %08X\n", i, switch_oid[0]);
    // invalid remove
    assert(delete_object(&switch_oid[1]) != CRUD_STATUS_SUCCESS);
    // invalid create (out-of-range)
    attr_list[2].id = CRUD_SWITCH_ATTR_SPLIT_MODE;
    attr_list[2].value.u32 = 4;
    assert(create_object(&attr_list, 4, &switch_oid[0]) != CRUD_STATUS_SUCCESS);
    assert(switch_oid[0]) == 0);

    attr_list[3].id = CRUD_SWITCH_ATTR_MAX_PORTS;
    attr_list[3].value.u32 = 0;
    assert(create_object(&attr_list, 4, &switch_oid[0]) != CRUD_STATUS_SUCCESS);
    assert(switch_oid[0]) == 0);
    attr_list[3].id = CRUD_SWITCH_ATTR_MAX_PORTS;
    attr_list[3].value.u32 = 100;
    assert(create_object(&attr_list, 4, &switch_oid[0]) != CRUD_STATUS_SUCCESS);
    assert(switch_oid[0]) == 0);
    // same attribute twice
    attr_list[0].id = CRUD_SWITCH_ATTR_NAME;
    attr_list[0].value.chardata = "This is my switch";
    attr_list[1].id = CRUD_SWITCH_ATTR_HASH_SEED;
    attr_list[1].value.u32 = 1000;
    attr_list[2].id = CRUD_SWITCH_ATTR_SPLIT_MODE;
    attr_list[2].value.u32 = 0;
    attr_list[3].id = CRUD_SWITCH_ATTR_SPLIT_MODE;
    attr_list[3].value.u32 = 1;
    assert(create_object(&attr_list, 4, &switch_oid[0]) != CRUD_STATUS_SUCCESS);
    assert(switch_oid[0]) == 0);
    // no attr or NULLs
    assert(create_object(&attr_list, 0, &switch_oid[0]) != CRUD_STATUS_SUCCESS);
    assert(switch_oid[0]) == 0);
    assert(create_object(NULL, 2, &switch_oid[0]) != CRUD_STATUS_SUCCESS);
    assert(switch_oid[0]) == 0);
    assert(create_object(&attr_list, 3, NULL) != CRUD_STATUS_SUCCESS);
#endif
    return 0;
}

/*
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

/**
    return 0;
}
*/