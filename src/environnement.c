/**
 * @file environnement.c
 * @author François Cayre <cayre@yiking.(null)>
 * @date Fri Jun 22 20:11:30 2012
 * @brief Environnement functions for SFS.
 *
 * Environnement functions for SFS.
 */

#include "environnement.h"


/*
 * @fn object create_env()
 *
 * @brief fonction de création d'une liste d'environnement
 */

object create_list_env()
{
    return nil;
}

/*
 * @fn object create_env()
 *
 * @brief fonction de création d'un environnement
 */

object create_env()
{
    return nil;
}

/*
 * @fn object create_binding(object symbol, object value)
 *
 * @brief crée la paire (symbole valeur)
 */

object create_binding(object symbol, object value)
{
    if (symbol->type != SFS_SYMBOL)
    {
        WARNING_MSG("binding requires symbol");
        return NULL;
    }
    else
    {
        return make_pair(symbol, make_pair(value, nil));
    }
}

/*
 * @fn void add_binding_to_env(object binding, object* env)
 *
 * @brief ajoute une paire (ou carrement un environnement) à l'environnement (respectivement à la liste d'environnement) donné en paramètre
 */

void add_binding_to_list_env(object binding, object* list_env)
{
    object current_env=car(*list_env);
    object env_temp = cons(binding, current_env);
    remove_env(list_env);
    add_env(env_temp,list_env);
    return;
}

/*
 * @fn void add_env(object env, object* list_env)
 *
 * @brief ajoute un environnement à une liste d'environnement
 */

void add_env(object env, object* list_env)
{
    object list_env_temp = cons(env, *list_env);
    *list_env = list_env_temp;
    return;
}

/*
 * @fn void remove_env(object* list_env)
 *
 * @brief supprimme l'environnement courant (i.e. le plus récent, ou le plus "à gauche") de la liste d'environnement
 */

void remove_env(object* list_env)
{
    if ((*list_env)->type == SFS_NIL)
    {
        WARNING_MSG("No environment left !");
        return;
    }
    else
    {
        object list_env_temp = cdr(*list_env);
        *list_env = list_env_temp;
        return;
    }
}

/*
 * @fn object search_env(object symbol,object env)
 *
 * @brief retourne la paire (symbole valeur) trouvé dans l'environnement correspondant au symbole donné en paramètre. Retourne NULL si le symbole n'est pas présent.
 */

object search_env(object symbol, object env)
{
    if (env->type != SFS_NIL)
    {
        if (strcmp(symbol->this.symbol,car(car(env))->this.symbol) == 0)
        {
            return car(env);
        }
        else
        {
            return search_env(symbol,cdr(env));
        }
    }
    else
    {
        return NULL;
    }
}

/*
 * @fn object search_list_env(object symbol, object env)
 *
 * @brief Retourne la paire (symbole valeur) trouvé dans la liste d'environnement correspondant au symbole donné en paramètre. La paire retournée sera celle de l'environnement de plus haut niveau (principe de masquage. Retourne NULL si le symbole n'est pas présent.
 */


object search_list_env(object symbol, object list_env)
{
    if (list_env->type != SFS_NIL)
    {
        if (search_env(symbol, car(list_env)) != NULL)
        {
            return search_env(symbol, car(list_env));
        }
        else
        {
            return search_list_env(symbol,cdr(list_env));
        }
    }
    else
    {
        return NULL;
    }
}




