/**
 * @file object.c
 * @author François Cayre <cayre@yiking.(null)>
 * @date Fri Jun 15 18:02:57 2012
 * @brief Object definitions for SFS.
 *
 * Object definitions for SFS.
 */


#include "object.h"
#include "mem.h"


object make_object( uint type )
{

    object t = sfs_malloc( sizeof( *t ) );
    
    if (t == NULL) /*Si l'allocation a échoué*/
    {
        ERROR_MSG("malloc problem when creating object"); /*On arrête immédiatement le programme*/
    }
    
    t->type = type;

    return t;
}


object make_nil( void )
{

    object t = make_object( SFS_NIL );

    t->this.special = t;
    
    return t;
}


object make_boolean( int val )
{
    
    object t = make_object(SFS_BOOLEAN);
    
    if (val == TRUE)
        t->this.boolean_value = TRUE;
    if (val == FALSE)
        t->this.boolean_value = FALSE;
    return t;
}


object make_integer( int val )
{
    object t = make_object(SFS_INTEGER);
    
    t->this.integer = val;
    
    return t;
}

object make_float( double val )
{
    object t = make_object(SFS_FLOAT);
    
    t->this.number.this.real = val;
    
    return t;
}

object make_complex( double real, double imaginary )
{
    object t = make_object(SFS_COMPLEX);
    
    t->this.number.this.real = real;
    t->this.number.this.imaginary = imaginary;
    
    return t;
}

object make_character( char caractere )
{
    
    object t = make_object(SFS_CHARACTER);
    
    t->this.character = caractere;
    
    return t;
}

object make_string( string chaine )
{
    
    object t = make_object(SFS_STRING);
    
    strcpy(t->this.string, chaine);
    
    return t;
}

object make_symbol( string chaine )
{
    
    object t = make_object(SFS_SYMBOL);
    
    strcpy(t->this.symbol, chaine);
    
    return t;
}

object make_pair(object car, object cdr)
{
    
    object t = make_object(SFS_PAIR);
    
    t->this.pair.car=car;
    t->this.pair.cdr=cdr;
    
    return t;
}

object make_primitive( Primitive p )
{
    object t = make_object(SFS_PRIMITIVE);
    
    t->this.primitive = p;
    
    return t;
}


object make_compound( object parms, object body, object envt )
{
    object t = make_object(SFS_COMPOUND);
    
    t->this.compound.parms = parms;
    t->this.compound.body = body;
    t->this.compound.envt = envt;
    
    return t;
}
