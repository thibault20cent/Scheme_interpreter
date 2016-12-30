/**
 * @file eval.c
 * @author François Cayre <cayre@yiking.(null)>
 * @date Fri Jun 22 20:11:30 2012
 * @brief Evaluation stuff for SFS.
 *
 * Evaluation stuff for SFS.
 */

#include "eval.h"
#include "print.h"

/*
 * @fn int istrue(object input, object env)
 *
 * @brief renvoie TRUE si l'évaluation de l'expression scheme en paramètre est vraie et FALSE sinon
 */
int istrue(object input, object env)
{
    return (sfs_eval(input,env)->type != SFS_BOOLEAN || sfs_eval(input,env)->this.boolean_value == TRUE);
}

/*
 * @fn int is_reserved(string word)
 *
 * @brief renvoie TRUE si le mot est un mot réservé du scheme (forme), FALSE sinon
 */

int is_reserved(string word)
{
    if (strcmp(word,"define")==0)
        return TRUE;
    if (strcmp(word,"set!")==0)
        return TRUE;
    if (strcmp(word,"if")==0)
        return TRUE;
    if (strcmp(word,"and")==0)
        return TRUE;
    if (strcmp(word,"or")==0)
        return TRUE;
    if (strcmp(word,"lambda")==0)
        return TRUE;
    if (strcmp(word,"add_env")==0)
        return TRUE;
    if (strcmp(word,"show_list")==0)
        return TRUE;
    if (strcmp(word,"rm_env")==0)
        return TRUE;
    else
        return FALSE;
}

/*
 * @fn object sfs_quote(object input)
 *
 * @brief forme quote
 */


object sfs_quote(object input)
{
    return cadr(input);
}

/*
 * @fn object sfs_define(object input, object env)
 *
 * @brief forme define
 */

object sfs_define(object input, object env)
{
    /* erreur si trop ou pas assez d'arguments */
    if (cdr(input)->type==SFS_NIL || cddr(input)->type==SFS_NIL || cdddr(input) != nil)
    {
        WARNING_MSG("define takes 2 arguments");
        return NULL;
    }
    /*On récupère symbole et valeur de (define symb val)*/
    object symb  = cadr(input);
    object value = caddr(input);
    
    if (symb->type != SFS_PAIR)/*define d'une valeur ou d'un lambda calcul*/
    {
        if (value == NULL)/*évite une seg fault si jamais l'évaluation génère une erreur*/
            return NULL;
        
        if (is_reserved(symb->this.symbol))
        {
            WARNING_MSG("Symbol used is reserved to scheme");
            return NULL;
        }
        
        if (search_env(symb, car(env)) != NULL)
        {
            WARNING_MSG("Variable already defined in environment. Use set! or add a new environment with add_env");
            return NULL;
        }
        
        else
        {
            
            /*On crée la paire et on l'ajoute à l'environnement*/
            object binding = create_binding(symb, value);
            add_binding_to_list_env(binding, &LIST_ENV);
            
            if (binding == NULL)
                return NULL;
            else
                return symb;
        }
    }
    
    else /*define d'un lambda calcul sans passer par la forme lambda*/
    {
        object name = car(symb);
        object parms = cdr(symb);
        object body = value;
        
        /*on transforme en lambda*/
        object lambda_list = cons(make_symbol("lambda"),cons(parms,cons(body,nil)));
        object result = cons(make_symbol("define"), cons(name, cons(lambda_list,nil)));
        
        return sfs_eval(result, env);
    }
}



/*
 * @fn object sfs_set(object input, object env)
 *
 * @brief forme set!
 */

object sfs_set(object input, object env)
{
    /* erreur si trop ou pas assez d'arguments */
    if (cdr(input)->type==SFS_NIL || cddr(input)->type==SFS_NIL || cdddr(input) != nil)
    {
        WARNING_MSG("set! takes 2 arguments");
        return NULL;
    }
    
    else
    {
        /*On récupère symbole et valeur de (set! symb val)*/
        object symb  = cadr(input);
        object new_value = sfs_eval(caddr(input),env);
        object existing_binding = search_list_env(symb, env);
        
        if (new_value == NULL)/*évite une seg fault si jamais l'évaluation génère une erreur*/
            return NULL;
        
        if (existing_binding == NULL)
        {
            /*Si la variable n'a jamais été défini on retourne nil*/
            WARNING_MSG("Undefined variable");
            return NULL;
        }
        else
        {
            /*sauvegarde de l'ancienne valeur avant modification*/
            object old_value = make_object(cadr(existing_binding)->type);
            memcpy(old_value,cadr(existing_binding),sizeof(*old_value));
            /*modification de la valeur*/
            memcpy(cadr(existing_binding),new_value,sizeof(*new_value));
            /*on retourne l'ancienne valeur*/
            return old_value;
        }
    }
}

/*
 * @fn object sfs_if(object input, object env)
 *
 * @brief forme if
 */

object sfs_if(object input, object env)
{
    /* erreur si trop ou pas assez d'arguments */
    if (cdr(input)->type==SFS_NIL || cddr(input)->type==SFS_NIL || cdddr(input)->type==SFS_NIL || cdr(cdddr(input))->type != SFS_NIL)
    {
        WARNING_MSG("if takes 3 arguments");
        return NULL;
    }

    else
    {
        /* si l'évaluation du prédicat est vraie, on retourne l'évaluation de la conséquence. En scheme tout est vrai sauf #f */
        if (sfs_eval(cadr(input),env) == NULL)/*évite une seg fault si jamais l'évaluation génère une erreur*/
            return NULL;
        
        if (istrue(cadr(input), env))
        {
            return sfs_eval(caddr(input),env);
        }
        
        /* sinon on retourne l'évaluation de l'alternative */
        else
        {
            return sfs_eval(cadddr(input),env);
        }
    }
}

/*
 * @fn object sfs_and(object input, object env)
 *
 * @brief forme and
 */

object sfs_and(object input, object env)
{
    if (sfs_eval(cadr(input),env) == NULL)/*évite une seg fault si jamais l'évaluation génère une erreur*/
        return NULL;
    
    if (cdr(input)->type ==SFS_NIL)
    {
        return sfs_true;
    }
    else if (istrue(cadr(input), env))
    {
        return sfs_and(cdr(input), env);
    }
    
    else
    {
        return sfs_false;
    }
}

/*
 * @fn object sfs_or(object input, object env)
 *
 * @brief forme or (c'est l'inverse de and)
 */


object sfs_or(object input, object env)
{
    if (sfs_eval(cadr(input),env) == NULL)/*évite une seg fault si jamais l'évaluation génère une erreur*/
        return NULL;
    
    if (cdr(input)->type == SFS_NIL)
    {
        return sfs_false;
    }
    else if (!istrue(cadr(input), env))
    {
        return sfs_or(cdr(input), env);
    }
    else
    {
        return sfs_true;
    }
}

/*
 * @fn object sfs_begin(object input, object env)
 *
 * @brief forme begin
 */

object sfs_begin(object input, object env)
{
    input = cdr(input);
    object eval_car = NULL;

    while (input->type != SFS_NIL)
    {
        eval_car = sfs_eval(car(input),env);
        if (eval_car == NULL) /*évite une seg fault si jamais l'évaluation génère une erreur*/
            return NULL;
        input = cdr(input);
    }
    
    return eval_car;
}

/*
 * @fn object sfs_lambda(object input, object env)
 *
 * @brief forme lambda
 */

object sfs_lambda(object input, object env)
{
    /* erreur si trop ou pas assez d'arguments */
    if (cdr(input)->type == SFS_NIL || cddr(input)->type == SFS_NIL || cdddr(input) != nil)
    {
        WARNING_MSG("lambda takes 2 arguments");
        return NULL;
    }
    /*On récupère parametre et corps de (lambda parms body)*/
    object parms  = cadr(input);
    object body = caddr(input);
    
    return make_compound(parms, body, env);
}

/*
 * @fn object sfs_let(object input, object env)
 *
 * @brief forme let
 */

object sfs_let(object input, object env)
{
    object list_parms_value =cadr(input);
    object parms = nil;
    object value = nil;
    object body = caddr(input);

    while (list_parms_value->type != SFS_NIL)
    {
        parms = cons(caar(list_parms_value),parms);
        value = cons(cadar(list_parms_value),value);
        list_parms_value =cdr(list_parms_value);
    }

    object lambda_list = cons(make_symbol("lambda"),cons(parms,cons(body,nil)));
    
    return sfs_eval(cons(lambda_list,value), env);
}

/*
 * @fn object eval_primitive(object input, object env)
 *
 * @brief fonction d'évaluation d'une primitive
 */

object eval_primitive(object input, object env)
{
    object binding = search_list_env(car(input),env);
    
    if (binding == NULL)
    {
        WARNING_MSG("Unknown primitive");
        return NULL;
    }
    
    object o_prim = sfs_eval(cadr(binding),env);
    if (o_prim == NULL )
    {
        return NULL;
    }
    
    if (o_prim->type == SFS_COMPOUND )
    {
        return eval_compound(input, env);
    }
    else
    {
        return o_prim->this.primitive(cdr(input), env);
    }
}

/*
 * @fn object eval_symbol(object input, object env)
 *
 * @brief fonction d'évaluation d'un symbole
 */

object eval_symbol(object input, object env)
{
    /*commandes de gestion des environnements*/
    
    if (strcmp(input->this.symbol, "show_env") == 0)
        return env;
    
    if (strcmp(input->this.symbol, "show_list") == 0)
        return LIST_ENV;
    
    else if (strcmp(input->this.symbol, "add_env") == 0)
    {
        add_env(create_env(), &env);
        return env;
    }
    else if (strcmp(input->this.symbol, "rm_env") == 0)
    {
        remove_env(&env);
        return env;
    }
    
    else
    {
        object binding = search_list_env(input,env);
        if (binding == NULL)
        {
            WARNING_MSG("Unbound variable");
            return NULL;
        }
        else
        {
            /*on renvoie la valeur associée à la variable*/
            return sfs_eval(cadr(binding),env);
        }
    }
}

/*
 * @fn object eval_compound(object input, object env)
 *
 * @brief fonction d'évaluation d'une forme lambda
 */

object eval_compound(object input, object env)
{
    if (sfs_eval(car(input), env)->type == SFS_COMPOUND)
    {
    
        object t = sfs_eval(car(input), env);
        if (t == NULL)/*évite une seg fault si jamais l'évaluation génère une erreur*/
            return NULL;
        
        object parms = t->this.compound.parms;
        object body = t->this.compound.body;
        object exec_env = t->this.compound.envt;

        add_env(create_env(), &exec_env);
        
        while (parms->type != SFS_NIL)/*tant qu'on a des parametres*/
        {
            if (cadr(input)->type == SFS_NIL)/*pas assez d'arguments*/
            {
                WARNING_MSG("not enough arguments");
                return NULL;
            }
            
            object b = create_binding(car(parms), sfs_eval(cadr(input), env));
            add_binding_to_list_env(b, &exec_env);
            parms = cdr(parms);
            input = cdr(input);
        }
        
        if (cadr(input)->type != SFS_NIL)/*trop d'arguments*/
        {
            WARNING_MSG("too much arguments");
            return NULL;
        }
    
        return sfs_eval(body, exec_env);
    }
    else
    {
        WARNING_MSG("syntax error");
        return NULL;
    }
}

/*
 * @fn object eval_pair(object input, object env)
 *
 * @brief fonction d'évaluation d'une paire
 */

object eval_pair(object input, object env)
{
    if (strcmp(car(input)->this.symbol, "quote") == 0)
        return sfs_quote(input);
    
    else if (strcmp(car(input)->this.symbol, "define") == 0)
        return sfs_define(input, env);
    
    else if (strcmp(car(input)->this.symbol, "set!") == 0)
        return sfs_set(input, env);
    
    else if (strcmp(car(input)->this.symbol, "if") == 0)
        return sfs_if(input, env);
    
    else if (strcmp(car(input)->this.symbol, "and") == 0)
        return sfs_and(input, env);
    
    else if (strcmp(car(input)->this.symbol, "or") == 0)
        return sfs_or(input, env);
    
    else if (strcmp(car(input)->this.symbol, "begin") == 0)
        return sfs_begin(input, env);
    
    else if (strcmp(car(input)->this.symbol, "lambda") == 0)
        return sfs_lambda(input, env);
    
    else if (strcmp(car(input)->this.symbol, "let") == 0)
        return sfs_let(input, env);
    
    else if (car(input)->type == SFS_SYMBOL)
        return eval_primitive(input, env);
    
    else if (car(input)->type == SFS_PAIR)
        return eval_compound(input, env);
    else
    {
        WARNING_MSG("missing form or primitive. Try quoting");
        return NULL;
    }
}

/*
 * @fn object sfs_eval( object input, object env)
 *
 * @brief fonction d'évaluation d'une s-expression
 */

object sfs_eval( object input, object env)
{
    switch(input->type)
    {
        case SFS_PAIR:
            return eval_pair(input, env);
            
        case SFS_SYMBOL:
            return eval_symbol(input, env);
        
        case SFS_BOOLEAN:
            return input;
            
        default:
            return input;
            
    }
}

