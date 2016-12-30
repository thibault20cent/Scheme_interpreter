
/**
 * @file object.h
 * @author François Cayre <cayre@yiking.(null)>
 * @date Fri Jun 15 17:49:46 2012
 * @brief Object definition for SFS.
 *
 * Object definition for SFS.
 */

#ifndef _OBJECT_H_
#define _OBJECT_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "number.h"

typedef struct object_t {

    uint type;

    union {

        num              number;
        int              integer;
        int              boolean_value;
        char             character;
        string           string;
        string           symbol;
        struct object_t *(*primitive)(struct object_t *, struct object_t *);
        
        struct {
            struct object_t *car;
            struct object_t *cdr; } pair;

        struct object_t *special;
        
        struct {
            struct object_t *parms;
            struct object_t *body;
            struct object_t *envt; } compound;

    } this;

} *object;
    
typedef object (*Primitive)(object, object);


object make_object( uint type );
object make_nil( void );
object make_boolean( int val );
object make_character( char caractere);
object make_string( string chaine );
object make_symbol( string chaine );
object make_integer( int val );
object make_float( double val );
object make_pair( object car, object cdr );
object make_primitive( Primitive p );
object make_compound( object parms, object body, object envt );
    
#define SFS_INTEGER      0x00
#define SFS_CHARACTER    0x01
#define SFS_STRING       0x02
#define SFS_PAIR         0x03
#define SFS_NIL          0x04
#define SFS_BOOLEAN      0x05
#define SFS_SYMBOL       0x06
#define SFS_FLOAT        0x07
#define SFS_COMPLEX      0x08
#define SFS_PRIMITIVE    0x09
#define SFS_COMPOUND     0x10

extern object nil;
extern object sfs_true;
extern object sfs_false;
    

#ifdef __cplusplus
}
#endif

#endif /* _OBJECT_H_ */
