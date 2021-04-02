#if !defined (__CRUDATTRIBUTE_H_)
#define __CRUDATTRIBUTE_H_

#include <stdbool.h>

typedef  unsigned short int uint16_t;
typedef  unsigned int uint32_t;
typedef  unsigned char uint8_t;


typedef enum

{

    CRUD_STATUS_SUCCESS,

    CRUD_STATUS_FAILURE,

    CRUD_READ_ONLY,

    CRUD_INVALID_PARAM,

    CRUD_PORT_LIST_IS_FULL,

    CRUD_PORT_IS_USED,

    CRUD_LIST_IS_ABSENT,

    CRUD_CREATE_OBJ_FAILED,

    CRUD_NODE_IS_ABSENT,

    CRUD_ATTRIBUTE_LIST_IS_EMPTY,

    CRUD_ATTRIBUTE_SPEED_INCORRECT,

    CRUD_ATTRIBUTE_IPV4_MULTICAST,

    CRUD_ATTRIBUTE_MTU_INCORRECT,

    CRUD_ATTRIBUTE_MTU_ONLY_READ



    // add your own codes if needed 

} crud_status_t;



// 

typedef enum

{

    CRUD_OBJECT_TYPE_INVALID,

    CRUD_OBJECT_TYPE_SWITCH,

    CRUD_OBJECT_TYPE_PORT

} crud_object_type_t;



typedef enum

{

    // Switch attributes 

    CRUD_SWITCH_ATTR_NAME,       //+ chardata,        read-write 

    CRUD_SWITCH_ATTR_HASH_SEED,  //+ uint32 [0..max], read-write 

    CRUD_SWITCH_ATTR_SPLIT_MODE, // uint32 [0..3],   read-only   

    CRUD_SWITCH_ATTR_MAX_PORTS,  // uint32 [1..32],  read-only 


    
    // port attributes 

    CRUD_PORT_ATTR_STATE,        // bool, read-write 


    CRUD_PORT_ATTR_SPEED,        // uint32 [10, 100, 1000], read-write 

                                 // but write is allowed only if STATE 

                                 // is true 

    CRUD_PORT_ATTR_IPV4,         // ip4_t, read-write any non-multicast  

                                                              // and non-broadcast 

    CRUD_PORT_ATTR_MTU,          // uint32, [64..9K], read-only 

} crud_attr_id_t;



typedef uint32_t ip4_t;

typedef uint32_t crud_object_id_t;



typedef union _sai_attribute_value_t

{

    bool booldata;

    char chardata[32];

    uint8_t u8;

    uint32_t u32;

    ip4_t ip4;

} crud_attr_value_t;



typedef struct 

{

    crud_attr_id_t id;

    crud_attr_value_t value;

} crud_attribute_t;
// 
#endif