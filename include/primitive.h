/**
 * @file primitive.h
 * @author Thibault Vincent
 * @date Mer 26 oct 2016 12:11:03
 * @brief Primitive for SFS
 *
 * Primitive for SFS.
 */

#ifndef _PRIMITIVE_H_
#define _PRIMITIVE_H_

#ifdef __cplusplus
extern "C" {
#endif
    
#include "object.h"
#include "list.h"
#include "environnement.h"
#include "eval.h"
    
#include <stdio.h>
#include <ctype.h>
    
object addition( object, object );
object soustraction( object, object );
object multiplication( object, object );
object inferieur( object, object );
object superieur( object, object );
object egalite( object, object );
object quotient( object, object );
object reste( object, object );
object division( object, object );
    
object is_null( object, object );
object is_char( object, object );
object is_pair( object, object );
object is_float( object, object );
object is_symbol( object, object );
object is_string( object, object );
object is_integer( object, object );
object is_boolean( object, object );
object is_procedure( object, object );

object char_to_int( object, object );
object int_to_char( object, object );
object symb_to_string( object, object );
object string_to_symb( object, object );
object number_to_string( object, object );
object string_to_number( object, object );
    
object p_car( object, object );
object p_cdr( object, object );
object p_cons( object, object );
object set_car( object, object );
object set_cdr( object, object );
object p_list( object, object );
    
void init_primitive();

#ifdef __cplusplus
}
#endif

#endif /* _PRIMITIVE_H_ */
