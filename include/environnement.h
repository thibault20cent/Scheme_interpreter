/**
 * @file environnement.h
 * @author François Cayre <cayre@yiking.(null)>
 * @date Fri Jun 22 20:11:30 2012
 * @brief Environnement functions for SFS.
 *
 * Environnement functions for SFS.
 */

#ifndef _ENV_H_
#define _ENV_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "object.h"
#include "list.h"
    
extern object LIST_ENV;
    
object create_list_env();
object create_env();
object create_binding( object , object );
void   add_binding_to_list_env( object , object* );
object search_env( object , object );
void   add_env(object env, object* list_env);
void   remove_env( object* list_env);
object search_list_env(object symbol, object list_env);

#ifdef __cplusplus
}
#endif

#endif /* _ENV_H_ */