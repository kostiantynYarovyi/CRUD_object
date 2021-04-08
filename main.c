

#define PORT // SWITCH
#if defined(SWITCH)
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "crud_api/crud.h"

#define create_object   create_switch_object
#define read_object     read_switch_object
#define update_object   update_switch_object
#define delete_object   delete_switch_object
#elif defined (PORT)
#include <assert.h>
#include "sdk_list.h"
#include "sdk_api.h"

crud_status_t create_object(crud_attribute_t* attr_list, uint32_t attr_count, crud_object_id_t *object_id);
crud_status_t read_object(crud_object_id_t *object_id, crud_attribute_t* attr_list, uint32_t attr_count);
crud_status_t update_object(crud_object_id_t *object_id, crud_attribute_t* attr_list, uint32_t attr_count);
crud_status_t delete_object(crud_object_id_t *object_id);

#endif

int main(void)
{
#ifdef PORT
    crud_attribute_t attr_list[10];
    crud_object_id_t port_oid[33] = {0};
    uint32_t test;
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
        assert(create_object(attr_list, i % 4 + 1, &port_oid[i]) == CRUD_STATUS_SUCCESS);
        assert(((uint32_t) port_oid[i]) >> 16 == CRUD_OBJECT_TYPE_PORT);
//        printf("Created port %02d, OID: %08X\n", i, port_oid[i]);
    }

    // invalid create 33
    port_oid[32] = 0;
    assert(create_object(attr_list, 4, &port_oid[32]) != CRUD_STATUS_SUCCESS);
    assert(port_oid[32] == 0);

    // valid remove
    for (int i = 0; i < 32; i++) {
        assert(delete_object(&port_oid[i]) == CRUD_STATUS_SUCCESS);
//        printf("Removed port %02d, OID: %08X\n", i, port_oid[i]);
    }

    // invalid remove
    assert(delete_object(&port_oid[31]) != CRUD_STATUS_SUCCESS);
    assert(delete_object(&port_oid[32]) != CRUD_STATUS_SUCCESS);
    assert(delete_object(NULL) != CRUD_STATUS_SUCCESS);

    // invalid create (out-of-range)
    //attr_list[1].id = CRUD_PORT_ATTR_SPEED;
    attr_list[1].value.u32 = 2000;
    port_oid[0] = 0;
    assert(create_object(attr_list, 4, &port_oid[0]) != CRUD_STATUS_SUCCESS);
    assert(port_oid[0] == 0);

    //attr_list[2].id = CRUD_PORT_ATTR_IPV4;
    attr_list[2].value.ip4 = 0;
    assert(create_object(attr_list, 4, &port_oid[0]) != CRUD_STATUS_SUCCESS);
    assert(port_oid[0] == 0);

    //attr_list[2].id = CRUD_PORT_ATTR_IPV4;
    attr_list[2].value.ip4 = 0xFFFFFFFF;
    assert(create_object(attr_list, 4, &port_oid[0]) != CRUD_STATUS_SUCCESS);
    assert(port_oid[0] == 0);

    //attr_list[2].id = CRUD_PORT_ATTR_IPV4;
    attr_list[2].value.ip4 = 0xEF010101;
    assert(create_object(attr_list, 4, &port_oid[0]) != CRUD_STATUS_SUCCESS);
    assert(port_oid[0] == 0);

    //attr_list[2].id = CRUD_PORT_ATTR_IPV4;
    attr_list[2].value.ip4 = 0xE0000000;
    assert(create_object(attr_list, 4, &port_oid[0]) != CRUD_STATUS_SUCCESS);
    assert(port_oid[0] == 0);

    //attr_list[3].id = CRUD_PORT_ATTR_MTU;
    attr_list[3].value.u32 = 32;
    assert(create_object(attr_list, 4, &port_oid[0]) != CRUD_STATUS_SUCCESS);
    assert(port_oid[0] == 0);

    //attr_list[3].id = CRUD_PORT_ATTR_MTU;
    attr_list[3].value.u32 = 2000;
    assert(create_object(attr_list, 4, &port_oid[0]) != CRUD_STATUS_SUCCESS);
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
    assert(create_object(attr_list, 4, &port_oid[0]) != CRUD_STATUS_SUCCESS);
    assert(port_oid[0] == 0);

    // no attr or NULLs
    assert(create_object(attr_list, 0, &port_oid[0]) != CRUD_STATUS_SUCCESS);
    assert(port_oid[0] == 0);

    assert(create_object(NULL, 2, &port_oid[0]) != CRUD_STATUS_SUCCESS);
    assert(port_oid[0] == 0);

    assert(create_object(attr_list, 3, NULL) != CRUD_STATUS_SUCCESS);

    
    // READ-UPDATE
    attr_list[0].id = CRUD_PORT_ATTR_STATE;
    attr_list[0].value.booldata = true;
    attr_list[1].id = CRUD_PORT_ATTR_SPEED;
    attr_list[1].value.u32 = 1000;
    attr_list[2].id = CRUD_PORT_ATTR_IPV4;
    attr_list[2].value.ip4 = 0x11223344;
    attr_list[3].id = CRUD_PORT_ATTR_MTU;
    attr_list[3].value.u32 = 100;
    


    assert(create_object(attr_list, 4, &port_oid[0]) == CRUD_STATUS_SUCCESS);

    
    attr_list[0].value.booldata = false;
    attr_list[1].value.u32 = 100;
    attr_list[2].value.ip4 = 0x55667788;
    attr_list[3].value.u32 = 200;

   (create_object(attr_list, 4, &port_oid[1]) == CRUD_STATUS_SUCCESS);
 
    //READ
    attr_list[0].value.booldata = false;
    attr_list[1].value.u32 = 0;
    attr_list[2].value.ip4 = 0;
    attr_list[3].value.u32 = 0;
   // printf("u32 %u \n", attr_list[3].value.u32);
    //printf("####################read_object#######################\n");
    //printf("\n");
    test = read_object(&port_oid[0], attr_list, 4);
    /*
    printf("\n");
    printf("###########################################\n");
    printf("==========%u = ===========\n", test);

    printf("booldata %u \n", attr_list[0].value.booldata);
    printf("u32 %u \n", attr_list[1].value.u32);
    printf("ip4 %u \n", attr_list[2].value.ip4);
    printf("u32 %u \n", attr_list[3].value.u32);
    */
    assert(attr_list[0].value.booldata == true);
    assert(attr_list[1].value.u32 == 1000);
    assert(attr_list[2].value.ip4 == 0x11223344);
    assert(attr_list[3].value.u32 == 100);



    for(int i =0; i < 4;i ++){
        printf("val %u", attr_list[i].value.booldata);
    }

    read_object(&port_oid[1], attr_list, 4);
    assert(attr_list[0].value.booldata == false);
    assert(attr_list[1].value.u32 == 100);
    assert(attr_list[2].value.ip4 == 0x55667788);
    assert(attr_list[3].value.u32 == 200);

    // UPDATE
    attr_list[0].id = CRUD_PORT_ATTR_STATE;
    attr_list[0].value.booldata = false;
    attr_list[1].id = CRUD_PORT_ATTR_SPEED;
    attr_list[1].value.u32 = 100;
    attr_list[2].id = CRUD_PORT_ATTR_IPV4;
    attr_list[2].value.ip4 = 0x55667788;
    printf("##################### update_object    ######################\n");
    printf("\n");
    assert(update_object(&port_oid[0], attr_list, 3) == CRUD_STATUS_SUCCESS);
    
    attr_list[0].value.booldata = true;
    attr_list[1].value.u32 = 0;
    attr_list[2].value.ip4 = 0;
    attr_list[3].value.u32 = 0;
    
    printf("##################### create_object__1 ######################\n");
    printf("\n");
    read_object(&port_oid[0], attr_list, 4);
                printf("get_node: booldata %u \n",  attr_list[0].value.booldata);
                printf("get_node: u32 %u \n",  attr_list[1].value.u32);
                printf("get_node: ip4 %u \n",  attr_list[2].value.ip4);
                printf("get_node: u32 %u \n",  attr_list[3].value.u32);
    printf("\n");
    printf("#####################create_object######################\n");
    assert(attr_list[0].value.booldata == false);
    assert(attr_list[1].value.u32 == 100);
    assert(attr_list[2].value.ip4 == 0x55667788);
    assert(attr_list[3].value.u32 == 100);

    attr_list[0].id = CRUD_PORT_ATTR_SPEED;
    attr_list[0].value.u32 = 1000;
    attr_list[1].id = CRUD_PORT_ATTR_STATE;
    attr_list[1].value.booldata = true;
    attr_list[2].id = CRUD_PORT_ATTR_IPV4;
    attr_list[2].value.ip4 = 0x11223344;
    attr_list[3].id = CRUD_PORT_ATTR_MTU;
    attr_list[3].value.u32 = 120;
    assert(update_object(&port_oid[1], attr_list + 0, 1) == CRUD_STATUS_SUCCESS);
    assert(update_object(&port_oid[1], attr_list + 1, 1) == CRUD_STATUS_SUCCESS);
    assert(update_object(&port_oid[1], attr_list + 2, 1) == CRUD_STATUS_SUCCESS);
    assert(update_object(&port_oid[1], attr_list + 3, 1) != CRUD_STATUS_SUCCESS); // speed when port is enabled
    assert(update_object(&port_oid[1], attr_list + 3, 1) != CRUD_STATUS_SUCCESS); // MTU cannot be updated

    attr_list[0].id = CRUD_PORT_ATTR_STATE;
    attr_list[0].value.booldata = false;
    assert(read_object(&port_oid[1], attr_list, 1) == CRUD_STATUS_SUCCESS);
    assert(attr_list[0].value.booldata == true);

    attr_list[0].id = CRUD_PORT_ATTR_SPEED;
    attr_list[0].value.u32 = 0;
        
    printf("##################### create_object__2 ######################\n");
    printf("\n");
    assert(read_object(&port_oid[1], attr_list, 1) == CRUD_STATUS_SUCCESS);
                printf("get_node: booldata %u \n",  attr_list[0].value.booldata);
                printf("get_node: u32 %u \n",  attr_list[1].value.u32);
                printf("get_node: ip4 %u \n",  attr_list[2].value.ip4);
                printf("get_node: u32 %u \n",  attr_list[3].value.u32);
    printf("\n");
    printf("#####################create_object######################\n");
    assert(attr_list[0].value.u32 == 1000);

    attr_list[0].id = CRUD_PORT_ATTR_IPV4;
    attr_list[0].value.u32 = 0;
    assert(read_object(&port_oid[1], attr_list, 1) == CRUD_STATUS_SUCCESS);
    assert(attr_list[0].value.ip4 == 0x11223344);

    attr_list[0].id = CRUD_PORT_ATTR_MTU;
    attr_list[0].value.u32 = 0;
    assert(read_object(&port_oid[1], attr_list, 1) == CRUD_STATUS_SUCCESS);
    assert(attr_list[0].value.u32 == 100);

    // make sure first wasn't changed
    attr_list[0].id = CRUD_PORT_ATTR_STATE;
    attr_list[0].value.booldata = true;
    attr_list[1].id = CRUD_PORT_ATTR_SPEED;
    attr_list[1].value.u32 = 0;
    attr_list[2].id = CRUD_PORT_ATTR_IPV4;
    attr_list[2].value.ip4 = 0;
    attr_list[3].id = CRUD_PORT_ATTR_MTU;
    attr_list[3].value.u32 = 0;
    assert(read_object(&port_oid[0], attr_list, 4) == CRUD_STATUS_SUCCESS);
    assert(attr_list[0].value.booldata == false);
    assert(attr_list[1].value.u32 == 100);
    assert(attr_list[2].value.ip4 == 0x55667788);
    assert(attr_list[3].value.u32 == 100);

#else

    crud_attribute_t attr_list[10];
    crud_attribute_t attr_list2[10];
    crud_object_id_t switch_oid[4] = {0};

    attr_list[0].id = CRUD_SWITCH_ATTR_NAME;
    memcpy(attr_list[0].value.chardata,"This is my switch", 18);
    attr_list[1].id = CRUD_SWITCH_ATTR_HASH_SEED;
    attr_list[1].value.u32 = 1000;
    attr_list[2].id = CRUD_SWITCH_ATTR_SPLIT_MODE;
    attr_list[2].value.u32 = 0;
    attr_list[3].id = CRUD_SWITCH_ATTR_MAX_PORTS;
    attr_list[3].value.u32 = 1;

    // valid create
    for (int i = 0; i < 3; i++) {
        assert(create_object(attr_list, i + 2, &switch_oid[i]) == CRUD_STATUS_SUCCESS);
        assert(((uint32_t) switch_oid[i]) >> 16 == CRUD_OBJECT_TYPE_SWITCH);
        printf("Created switch %02d, OID: %08X\n", i, switch_oid[i]);
    }

    // invalid create #4
    switch_oid[3] = 0;
    assert(create_object(attr_list, 4, &switch_oid[3]) != CRUD_STATUS_SUCCESS);
    assert(switch_oid[3] == 0);

    for (int i = 0; i < 3; i++) {
        assert(delete_object(&switch_oid[i]) == CRUD_STATUS_SUCCESS);
        printf("Removed sw %02d, OID: %08X\n", i, switch_oid[i]);
    }

    // invalid remove
    assert(delete_object(&switch_oid[1]) != CRUD_STATUS_SUCCESS);
    assert(delete_object(&switch_oid[3]) != CRUD_STATUS_SUCCESS);
    assert(delete_object(NULL) != CRUD_STATUS_SUCCESS);

    // invalid create (out-of-range)
    attr_list[2].id = CRUD_SWITCH_ATTR_SPLIT_MODE;
    attr_list[2].value.u32 = 4;
    assert(create_object(attr_list, 4, &switch_oid[0]) != CRUD_STATUS_SUCCESS);
    assert(switch_oid[0] == 0);


    attr_list[3].id = CRUD_SWITCH_ATTR_MAX_PORTS;
    attr_list[3].value.u32 = 0;
    assert(create_object(attr_list, 4, &switch_oid[0]) != CRUD_STATUS_SUCCESS);
    assert(switch_oid[0] == 0);

    attr_list[3].id = CRUD_SWITCH_ATTR_MAX_PORTS;
    attr_list[3].value.u32 = 100;
    assert(create_object(attr_list, 4, &switch_oid[0]) != CRUD_STATUS_SUCCESS);
    assert(switch_oid[0] == 0);

    // same attribute twice
    attr_list[0].id = CRUD_SWITCH_ATTR_NAME;
    memcpy(attr_list[0].value.chardata, "This is my switch", 18);
    attr_list[1].id = CRUD_SWITCH_ATTR_HASH_SEED;
    attr_list[1].value.u32 = 1000;
    attr_list[2].id = CRUD_SWITCH_ATTR_SPLIT_MODE;
    attr_list[2].value.u32 = 0;
    attr_list[3].id = CRUD_SWITCH_ATTR_SPLIT_MODE;
    attr_list[3].value.u32 = 1;
    assert(create_object(attr_list, 4, &switch_oid[0]) != CRUD_STATUS_SUCCESS);
    assert(switch_oid[0] == 0);

    // no attr or NULLs
    assert(create_object(attr_list, 0, &switch_oid[0]) != CRUD_STATUS_SUCCESS);
    assert(switch_oid[0] == 0);

    assert(create_object(NULL, 2, &switch_oid[0]) != CRUD_STATUS_SUCCESS);
    assert(switch_oid[0] == 0);

    assert(create_object(attr_list, 3, NULL) != CRUD_STATUS_SUCCESS);

    // READ/UPDATE
    attr_list[0].id = CRUD_SWITCH_ATTR_NAME;
    memcpy(attr_list[0].value.chardata,"This is my switch", 18);
    attr_list[1].id = CRUD_SWITCH_ATTR_HASH_SEED;
    attr_list[1].value.u32 = 1000;
    attr_list[2].id = CRUD_SWITCH_ATTR_SPLIT_MODE;
    attr_list[2].value.u32 = 1;
    attr_list[3].id = CRUD_SWITCH_ATTR_MAX_PORTS;
    attr_list[3].value.u32 = 1;

    assert(create_object(attr_list, 4, &switch_oid[0]) == CRUD_STATUS_SUCCESS);

    attr_list[4].id = CRUD_SWITCH_ATTR_NAME;
    memcpy(attr_list[4].value.chardata,"This is his switch", 19);
    attr_list[5].id = CRUD_SWITCH_ATTR_HASH_SEED;
    attr_list[5].value.u32 = 999;
    attr_list[6].id = CRUD_SWITCH_ATTR_SPLIT_MODE;
    attr_list[6].value.u32 = 2;
    attr_list[7].id = CRUD_SWITCH_ATTR_MAX_PORTS;
    attr_list[7].value.u32 = 32;
    assert(create_object(attr_list + 4, 4, &switch_oid[1]) == CRUD_STATUS_SUCCESS);

    attr_list2[0].id = CRUD_SWITCH_ATTR_NAME;
    attr_list2[0].value.chardata[0] = 0;
    attr_list2[1].id = CRUD_SWITCH_ATTR_HASH_SEED;
    attr_list2[1].value.u32 = 0;
    attr_list2[2].id = CRUD_SWITCH_ATTR_SPLIT_MODE;
    attr_list2[2].value.u32 = 0;
    attr_list2[3].id = CRUD_SWITCH_ATTR_MAX_PORTS;
    attr_list2[3].value.u32 = 0;

    assert(read_object(&switch_oid[0], attr_list2, 4) == CRUD_STATUS_SUCCESS);
    assert(!strcmp(attr_list2[0].value.chardata, "This is my switch"));
    assert(attr_list2[1].value.u32 == 1000);
    assert(attr_list2[2].value.u32 == 1);
    assert(attr_list2[3].value.u32 == 1);

    attr_list2[4].id = CRUD_SWITCH_ATTR_NAME;
    attr_list2[4].value.chardata[0] = 0;
    attr_list2[5].id = CRUD_SWITCH_ATTR_HASH_SEED;
    attr_list2[5].value.u32 = 0;
    attr_list2[6].id = CRUD_SWITCH_ATTR_SPLIT_MODE;
    attr_list2[6].value.u32 = 0;
    attr_list2[7].id = CRUD_SWITCH_ATTR_MAX_PORTS;
    attr_list2[7].value.u32 = 0;
    assert(read_object(&switch_oid[1], attr_list2+4, 1) == CRUD_STATUS_SUCCESS);
    assert(!strcmp(attr_list2[4].value.chardata, "This is his switch"));
    assert(read_object(&switch_oid[1], attr_list2+5, 1) == CRUD_STATUS_SUCCESS);
    printf("%d", attr_list2[5].value.u32);
    assert(attr_list2[5].value.u32 == 999);
    assert(read_object(&switch_oid[1], attr_list2+6, 1) == CRUD_STATUS_SUCCESS);
    assert(attr_list2[6].value.u32 == 2);
    assert(read_object(&switch_oid[1], attr_list2+7, 1) == CRUD_STATUS_SUCCESS);
    assert(attr_list2[7].value.u32 == 32);

    // valid udate
    assert(update_object(&switch_oid[0], attr_list+4, 2) == CRUD_STATUS_SUCCESS);
    assert(read_object(&switch_oid[0], attr_list2, 4) == CRUD_STATUS_SUCCESS);
    assert(!strcmp(attr_list2[0].value.chardata, "This is his switch"));
    assert(attr_list2[1].value.u32 == 999);
    assert(attr_list2[2].value.u32 == 1);
    assert(attr_list2[3].value.u32 == 1);

    assert(update_object(&switch_oid[1], attr_list, 2) == CRUD_STATUS_SUCCESS);
    assert(read_object(&switch_oid[1], attr_list2, 4) == CRUD_STATUS_SUCCESS);
    assert(!strcmp(attr_list2[0].value.chardata, "This is my switch"));
    assert(attr_list2[1].value.u32 == 1000);
    assert(attr_list2[2].value.u32 == 2);
    assert(attr_list2[3].value.u32 == 32);
    // check nothing changed for [0]
    assert(read_object(&switch_oid[0], attr_list2, 4) == CRUD_STATUS_SUCCESS);
    assert(!strcmp(attr_list2[0].value.chardata, "This is his switch"));
    assert(attr_list2[1].value.u32 == 999);
    assert(attr_list2[2].value.u32 == 1);
    assert(attr_list2[3].value.u32 == 1);

    assert(update_object(&switch_oid[0], attr_list, 3) != CRUD_STATUS_SUCCESS);
    assert(update_object(&switch_oid[0], attr_list+3, 1) != CRUD_STATUS_SUCCESS);
    assert(update_object(&switch_oid[1], attr_list, 3) != CRUD_STATUS_SUCCESS);
    assert(update_object(&switch_oid[1], attr_list+3, 1) != CRUD_STATUS_SUCCESS);

    assert(read_object(NULL, attr_list2, 4) != CRUD_STATUS_SUCCESS);
    assert(read_object(&switch_oid[0], NULL, 4) != CRUD_STATUS_SUCCESS);
    assert(read_object(&switch_oid[0], attr_list2, 0) != CRUD_STATUS_SUCCESS);
    assert(update_object(NULL, attr_list, 3) != CRUD_STATUS_SUCCESS);
    assert(update_object(&switch_oid[1], NULL, 1) != CRUD_STATUS_SUCCESS);


#endif
    return 0;
}