/**
 * @file list.h
 * @author Thibault Vincent
 * @date Thur Oct 13 14:01:30 2016
 * @brief List functions for SFS
 *
 * List functions for SFS.
 */

#ifndef _LIST_H_
#define _LIST_H_

#ifdef __cplusplus
extern "C" {
#endif
    
#include "object.h"
    
object car( object );
object cdr( object );
object cdar( object );
object cadr( object );
object caar( object );
object cddr( object );
object cadar( object );
object cdddr( object );
object caddr( object );
object caadr( object );
object caaar( object );
object cddar( object );
object cdaar( object );
object cadddr( object );
object caaadr( object );
object cons( object, object );
    
#ifdef __cplusplus
}
#endif

#endif /* _LIST_H_ */