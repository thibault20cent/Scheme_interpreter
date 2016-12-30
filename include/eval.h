/**
 * @file eval.h
 * @author François Cayre <cayre@yiking.(null)>
 * @date Fri Jun 22 20:10:38 2012
 * @brief Evaluation stuff for SFS.
 *
 * Evaluation stuff for SFS.
 */

#ifndef _EVAL_H_
#define _EVAL_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "environnement.h"
#include "object.h"
#include "primitive.h"
    
object sfs_define( object , object );
object sfs_quote( object );
object sfs_set( object , object );
object sfs_if( object , object );
object sfs_and( object , object );
object sfs_or( object , object );
object sfs_begin( object , object );
object sfs_lambda( object , object );
object eval_compound( object, object env );
object sfs_let( object , object );
    
    
object eval_primitive( object , object  );
object eval_symbol( object , object );
object eval_pair( object , object );
object sfs_eval( object , object);
int    is_true( object , object);


#ifdef __cplusplus
}
#endif

#endif /* _EVAL_H_ */
