/**
 * @file primitive.c
 * @author Thibault Vincent
 * @date Mer 26 oct 2016 12:11:03
 * @brief Primitive for SFS
 *
 * Primitive for SFS.
 */

#include "primitive.h"

/*
 * @fn void init_primitive()
 *
 * @brief Charge les primitives dans l'environnement 0 (top-level). Elle est appelée dans init_interpreteur() au début de repl.c
 */

void init_primitive()
{
    /*prédicats*/
    object null = create_binding( make_symbol("null?") , make_primitive(is_null));
    add_binding_to_list_env(null, &LIST_ENV);
    object integer = create_binding( make_symbol("integer?") , make_primitive(is_integer));
    add_binding_to_list_env(integer, &LIST_ENV);
    object boolean = create_binding( make_symbol("boolean?") , make_primitive(is_boolean));
    add_binding_to_list_env(boolean, &LIST_ENV);
    object symbol = create_binding( make_symbol("symbol?") , make_primitive(is_symbol));
    add_binding_to_list_env(symbol, &LIST_ENV);
    object pair = create_binding( make_symbol("pair?") , make_primitive(is_pair));
    add_binding_to_list_env(pair, &LIST_ENV);
    object character = create_binding( make_symbol("char?") , make_primitive(is_char));
    add_binding_to_list_env(character, &LIST_ENV);
    object floatt = create_binding( make_symbol("float?") , make_primitive(is_float));
    add_binding_to_list_env(floatt, &LIST_ENV);
    object stringg = create_binding( make_symbol("string?") , make_primitive(is_string));
    add_binding_to_list_env(stringg, &LIST_ENV);
    object proc = create_binding( make_symbol("procedure?") , make_primitive(is_procedure));
    add_binding_to_list_env(proc, &LIST_ENV);
    
    /*conversion de type*/
    object char_int = create_binding( make_symbol("char->integer") , make_primitive(char_to_int));
    add_binding_to_list_env(char_int, &LIST_ENV);
    object int_char = create_binding( make_symbol("integer->char") , make_primitive(int_to_char));
    add_binding_to_list_env(int_char, &LIST_ENV);
    object symb_string = create_binding( make_symbol("symbol->string") , make_primitive(symb_to_string));
    add_binding_to_list_env(symb_string, &LIST_ENV);
    object string_symb = create_binding( make_symbol("string->symbol") , make_primitive(string_to_symb));
    add_binding_to_list_env(string_symb, &LIST_ENV);
    object string_numb = create_binding( make_symbol("string->number") , make_primitive(string_to_number));
    add_binding_to_list_env(string_numb, &LIST_ENV);
    object numb_string = create_binding( make_symbol("number->string") , make_primitive(number_to_string));
    add_binding_to_list_env(numb_string, &LIST_ENV);
    
    /*arithmétique*/
    object add = create_binding( make_symbol("+") , make_primitive(addition));
    add_binding_to_list_env(add, &LIST_ENV);
    object sous = create_binding( make_symbol("-") , make_primitive(soustraction));
    add_binding_to_list_env(sous, &LIST_ENV);
    object multi = create_binding( make_symbol("*") , make_primitive(multiplication));
    add_binding_to_list_env(multi, &LIST_ENV);
    object sup = create_binding( make_symbol(">") , make_primitive(superieur));
    add_binding_to_list_env(sup, &LIST_ENV);
    object inf = create_binding( make_symbol("<") , make_primitive(inferieur));
    add_binding_to_list_env(inf, &LIST_ENV);
    object egal = create_binding( make_symbol("=") , make_primitive(egalite));
    add_binding_to_list_env(egal, &LIST_ENV);
    object quo = create_binding( make_symbol("quotient") , make_primitive(quotient));
    add_binding_to_list_env(quo, &LIST_ENV);
    object rest = create_binding( make_symbol("remainder") , make_primitive(reste));
    add_binding_to_list_env(rest, &LIST_ENV);
    object div = create_binding( make_symbol("/") , make_primitive(division));
    add_binding_to_list_env(div, &LIST_ENV);
    
    /*manipulation de listes*/
    object o_car = create_binding( make_symbol("car") , make_primitive(p_car));
    add_binding_to_list_env(o_car, &LIST_ENV);
    object o_cdr = create_binding( make_symbol("cdr") , make_primitive(p_cdr));
    add_binding_to_list_env(o_cdr, &LIST_ENV);
    object o_cons = create_binding( make_symbol("cons") , make_primitive(p_cons));
    add_binding_to_list_env(o_cons, &LIST_ENV);
    object setcar = create_binding( make_symbol("set-car!") , make_primitive(set_car));
    add_binding_to_list_env(setcar, &LIST_ENV);
    object setcdr = create_binding( make_symbol("set-cdr!") , make_primitive(set_cdr));
    add_binding_to_list_env(setcdr, &LIST_ENV);
    object o_list = create_binding( make_symbol("list") , make_primitive(p_list));
    add_binding_to_list_env(o_list, &LIST_ENV);
}

/* PREDICATS */

object is_null(object o,object env)
{
    while (o->type != SFS_NIL)
    {
        object eval_car = sfs_eval(car(o),env);
        if (eval_car == NULL)/*évite une seg fault si jamais l'évaluation génère une erreur*/
            return NULL;
        
        if (eval_car->type == SFS_NIL)
        {
            o = cdr(o);
        }
        else
        {
            return sfs_false;
        }
    }
    return sfs_true;
}

object is_integer(object o,object env)
{
    while (o->type != SFS_NIL)
    {
        object eval_car = sfs_eval(car(o),env);
        if (eval_car == NULL)/*évite une seg fault si jamais l'évaluation génère une erreur*/
            return NULL;
        
        if (eval_car->type == SFS_INTEGER)
        {
            o = cdr(o);
        }
        else
        {
            return sfs_false;
        }
    }
    return sfs_true;
}

object is_boolean(object o,object env)
{
    while (o->type != SFS_NIL)
    {
        object eval_car = sfs_eval(car(o),env);
        if (eval_car == NULL)/*évite une seg fault si jamais l'évaluation génère une erreur*/
            return NULL;
        
        if (eval_car->type == SFS_BOOLEAN)
        {
            o = cdr(o);
        }
        else
        {
            return sfs_false;
        }
    }
    return sfs_true;
}

object is_symbol(object o, object env)
{
    while (o->type != SFS_NIL)
    {
        object eval_car = sfs_eval(car(o),env);
        if (eval_car == NULL)/*évite une seg fault si jamais l'évaluation génère une erreur*/
            return NULL;
        
        if (eval_car->type == SFS_SYMBOL)
        {
            o = cdr(o);
        }
        else
        {
            return sfs_false;
        }
    }
    return sfs_true;
}

object is_char(object o, object env)
{
    while (o->type != SFS_NIL)
    {
        object eval_car = sfs_eval(car(o),env);
        if (eval_car == NULL)/*évite une seg fault si jamais l'évaluation génère une erreur*/
            return NULL;
        
        if (eval_car->type == SFS_CHARACTER)
        {
            o = cdr(o);
        }
        else
        {
            return sfs_false;
        }
    }
    return sfs_true;
}

object is_string(object o, object env)
{
    while (o->type != SFS_NIL)
    {
        object eval_car = sfs_eval(car(o),env);
        if (eval_car == NULL)/*évite une seg fault si jamais l'évaluation génère une erreur*/
            return NULL;
        
        if (eval_car->type == SFS_STRING)
        {
            o = cdr(o);
        }
        else
        {
            return sfs_false;
        }
    }
    return sfs_true;
}

object is_pair(object o, object env)
{
    while (o->type != SFS_NIL)
    {
        object eval_car = sfs_eval(car(o),env);
        if (eval_car == NULL)/*évite une seg fault si jamais l'évaluation génère une erreur*/
            return NULL;
        
        if (eval_car->type == SFS_PAIR)
        {
            o = cdr(o);
        }
        else
        {
            return sfs_false;
        }
    }
    return sfs_true;
}

object is_float(object o, object env)
{
    while (o->type != SFS_NIL)
    {
        object eval_car = sfs_eval(car(o),env);
        if (eval_car == NULL)/*évite une seg fault si jamais l'évaluation génère une erreur*/
            return NULL;
    
        if (eval_car->type == SFS_FLOAT)
        {
            o = cdr(o);
        }
        else
        {
            return sfs_false;
        }
    }
    return sfs_true;
}

object is_procedure(object o, object env)
{
    while (o->type != SFS_NIL)
    {
        object eval_car = sfs_eval(car(o),env);
        if (eval_car == NULL)/*évite une seg fault si jamais l'évaluation génère une erreur*/
            return NULL;
        
        if (eval_car->type == SFS_PRIMITIVE || eval_car->type == SFS_COMPOUND)
        {
            o = cdr(o);
        }
        else
        {
            return sfs_false;
        }
    }
    return sfs_true;
}

/* CONVERSION DE TYPE */

object char_to_int(object o, object env)
{
    object eval_car = sfs_eval(car(o),env);
    if (eval_car == NULL)/*évite une seg fault si jamais l'évaluation génère une erreur*/
        return NULL;
    
    if (eval_car->type == SFS_CHARACTER && cdr(o)->type == SFS_NIL)
    {
        return make_integer((int)eval_car->this.character);
    }
    else
    {
        WARNING_MSG("conversion needs one char in argument");
        return NULL;
    }
}

object int_to_char(object o, object env)
{
    object eval_car = sfs_eval(car(o),env);
    if (eval_car == NULL)/*évite une seg fault si jamais l'évaluation génère une erreur*/
        return NULL;
    
    if (eval_car->type == SFS_INTEGER && cdr(o)->type == SFS_NIL)
    {
        return make_character((char)eval_car->this.integer);
    }
    else
    {
        WARNING_MSG("conversion needs one int in argument");
        return NULL;
    }
}

object symb_to_string(object o, object env)
{
    object eval_car = sfs_eval(car(o),env);
    if (eval_car == NULL)/*évite une seg fault si jamais l'évaluation génère une erreur*/
        return NULL;
    
    if (eval_car->type == SFS_SYMBOL && cdr(o)->type == SFS_NIL)
    {
        return make_string(eval_car->this.symbol);
    }
    else
    {
        WARNING_MSG("conversion needs one symbol in argument");
        return NULL;
    }
}

object string_to_symb(object o, object env)
{
    object eval_car = sfs_eval(car(o),env);
    if (eval_car == NULL)/*évite une seg fault si jamais l'évaluation génère une erreur*/
        return NULL;
    
    if (eval_car->type == SFS_STRING && cdr(o)->type == SFS_NIL)
    {
        return make_symbol(eval_car->this.string);
    }
    else
    {
        WARNING_MSG("conversion needs one string in argument");
        return NULL;
    }
}

object number_to_string(object o, object env)
{
    object eval_car = sfs_eval(car(o),env);
    if (eval_car == NULL)/*évite une seg fault si jamais l'évaluation génère une erreur*/
        return NULL;
    
    if (eval_car->type == SFS_INTEGER && cdr(o)->type == SFS_NIL)
    {
        string str="";
        
        if (sprintf(str, "%d", eval_car->this.integer)<0)
        {
            WARNING_MSG("conversion failed");
            return NULL;
        }
        else
        {
            return make_string(str);
        }
    }
    else if (eval_car->type == SFS_FLOAT && cdr(o)->type == SFS_NIL)
    {
        string str="";
        
        if (sprintf(str, "%lf", eval_car->this.number.this.real)<0)
        {
            WARNING_MSG("conversion failed");
            return NULL;
        }
        else
        {
            return make_string(str);
        }
    }
    else
    {
        WARNING_MSG("conversion needs one number in argument");
        return NULL;
    }
}

object string_to_number(object o, object env) /*probleme*/
{
    object eval_car = sfs_eval(car(o),env);
    if (eval_car == NULL)/*évite une seg fault si jamais l'évaluation génère une erreur*/
        return NULL;
    
    if (eval_car->type == SFS_STRING && cdr(o)->type == SFS_NIL)
    {
        int conv = strtol(eval_car->this.string,NULL,10);
        
        if (conv != 0) /*attention si "0" ou "0000"*/
        {
            return make_float(conv);
        }
        else
        {
            WARNING_MSG("the string given doesn't contain number");
            return NULL;
        }
    }
    else
    {
        WARNING_MSG("conversion needs one string in argument");
        return NULL;
    }
}

/* ARITHMETIQUE */

object addition (object o, object env)
{
    double res = 0;
    int is_a_float = FALSE;
    
    while (o->type != SFS_NIL)
    {
        object eval_car = sfs_eval(car(o),env);
        if (eval_car == NULL)/*évite une seg fault si jamais l'évaluation génère une erreur*/
            return NULL;
        
        if (eval_car->type == SFS_INTEGER)
        {
            res += eval_car->this.integer;
            o = cdr(o);
        }
        else if (eval_car->type == SFS_FLOAT)
        {
            is_a_float = TRUE;
            res += eval_car->this.number.this.real;
            o = cdr(o);
        }
        else
        {
            o = cdr(o);
            WARNING_MSG("A non-number expression result was used in addition and was skipped");
        }
    }
    
    if (is_a_float == TRUE)
        return make_float(res);
    
    else
        return make_integer(res);
}

object soustraction(object o, object env)
{
    double res = 0;
    int is_a_float = FALSE;
    int first_number = TRUE;
    int one_argument = TRUE;
    
    /*On compte positivement le premier nombre*/
    while (first_number)
    {
        object eval_car = sfs_eval(car(o),env);
        if (eval_car == NULL)/*évite une seg fault si jamais l'évaluation génère une erreur*/
            return NULL;
        
        if (eval_car->type == SFS_INTEGER)
        {
            res += eval_car->this.integer;
            o = cdr(o);
            first_number = FALSE;
            
        }
        else if (eval_car->type == SFS_FLOAT)
        {
            is_a_float = TRUE;
            res += eval_car->this.number.this.real;
            o = cdr(o);
            first_number = FALSE;
        }
        else
        {
            o = cdr(o);
            WARNING_MSG("A non-number expression result was used in soustraction and was skipped");
            /*on continue la boucle while tant que l'on a pas un nombre*/
        }
    }
    
    /*ensuite meme principe que pour l'addition*/
    while (o->type != SFS_NIL)
    {
        one_argument = FALSE;
        
        object eval_car = sfs_eval(car(o),env);
        if (eval_car == NULL)/*évite une seg fault si jamais l'évaluation génère une erreur*/
            return NULL;
        
        if (eval_car->type == SFS_INTEGER)
        {
            res -= eval_car->this.integer;
            o = cdr(o);
        }
        else if (eval_car->type == SFS_FLOAT)
        {
            is_a_float = TRUE;
            res -= eval_car->this.number.this.real;
            o = cdr(o);
        }
        else
        {
            o = cdr(o);
            WARNING_MSG("A non-number expression result was used in soustraction and was skipped");
        }
    }
    if (one_argument)
    {
        res= -res;
    }
    if (is_a_float)
        return make_float(res);
    
    else
        return make_integer(res);

}

object multiplication(object o, object env)
{
    double res = 1;
    int is_a_float = FALSE;
    
    while (o->type != SFS_NIL)
    {
        object eval_car = sfs_eval(car(o),env);
        if (eval_car == NULL)/*évite une seg fault si jamais l'évaluation génère une erreur*/
            return NULL;
        
        if (eval_car->type == SFS_INTEGER)
        {
            res = res*eval_car->this.integer;
            o = cdr(o);
        }
        else if (eval_car->type == SFS_FLOAT)
        {
            is_a_float = TRUE;
            res = res*eval_car->this.number.this.real;
            o = cdr(o);
        }
        else
        {
            o = cdr(o);
            WARNING_MSG("A non-number expression result was used in product and was skipped");
        }
    }
    
    if (is_a_float == TRUE)
        return make_float(res);
    
    else
        return make_integer(res);
}

object quotient(object o, object env)
{
    /* erreur si trop ou pas assez d'arguments */
    if (cdr(o)->type==SFS_NIL || cddr(o)->type!=SFS_NIL || o->type == SFS_NIL)
    {
        WARNING_MSG("quotient takes 2 arguments");
        return NULL;
    }
    
    object eval_car = sfs_eval(car(o),env);
    if (eval_car == NULL)/*évite une seg fault si jamais l'évaluation génère une erreur*/
        return NULL;
    object eval_cadr = sfs_eval(cadr(o),env);
    if (eval_cadr == NULL)/*évite une seg fault si jamais l'évaluation génère une erreur*/
        return NULL;
    
    if (eval_car->type == SFS_INTEGER && eval_cadr->type == SFS_INTEGER)
    {
        if (eval_cadr->this.integer == 0)
        {
            WARNING_MSG("Division by 0. Sorry but you can't do that dude.");
            return NULL;
        }
        else
            return make_integer(eval_car->this.integer/eval_cadr->this.integer);
    }
    
    else
    {
        WARNING_MSG("quotient needs integer arguments. See / for float division");
        return NULL;
    }
}

object reste(object o, object env)
{
    /* erreur si trop ou pas assez d'arguments */
    if (cdr(o)->type==SFS_NIL || cddr(o)->type!=SFS_NIL || o->type == SFS_NIL)
    {
        WARNING_MSG("remainder takes 2 arguments");
        return NULL;
    }
    
    object eval_car = sfs_eval(car(o),env);
    if (eval_car == NULL)/*évite une seg fault si jamais l'évaluation génère une erreur*/
        return NULL;
    object eval_cadr = sfs_eval(cadr(o),env);
    if (eval_cadr == NULL)/*évite une seg fault si jamais l'évaluation génère une erreur*/
        return NULL;
    
    if (eval_car->type == SFS_INTEGER && eval_cadr->type == SFS_INTEGER)
    {
        if (eval_cadr->this.integer == 0)
        {
            WARNING_MSG("Division by 0. Sorry but you can't do that dude.");
            return NULL;
        }
        else
            return make_integer(eval_car->this.integer % eval_cadr->this.integer);
    }
    
    else
    {
        WARNING_MSG("remainder needs integer arguments. See / for float division");
        return NULL;
    }
}

object division(object o, object env) /*pareil que la sousctraction*/
{
    double res = 1;
    int first_number = TRUE;
    int one_argument = TRUE;
    
    /*On met le premier nombre dans le résultat*/
    while (first_number)
    {
        object eval_car = sfs_eval(car(o),env);
        if (eval_car == NULL)/*évite une seg fault si jamais l'évaluation génère une erreur*/
            return NULL;
        
        if (eval_car->type == SFS_INTEGER)
        {
            res = (double)eval_car->this.integer;
            o = cdr(o);
            first_number = FALSE;
            
        }
        else if (eval_car->type == SFS_FLOAT)
        {
            res = eval_car->this.number.this.real;
            o = cdr(o);
            first_number = FALSE;
        }
        else
        {
            o = cdr(o);
            WARNING_MSG("A non-number expression result was used in soustraction and was skipped");
            /*on continue la boucle while tant que l'on a pas un nombre*/
        }
    }
    
    /*on divise par les arguments restants*/
    while (o->type != SFS_NIL)
    {
        one_argument = FALSE;
        object eval_car = sfs_eval(car(o),env);
        if (eval_car == NULL)/*évite une seg fault si jamais l'évaluation génère une erreur*/
            return NULL;
        
        if (eval_car->type == SFS_INTEGER)
        {
            res = res/((double)eval_car->this.integer);
            o = cdr(o);
        }
        else if (eval_car->type == SFS_FLOAT)
        {
            res = res/eval_car->this.number.this.real;
            o = cdr(o);
        }
        else
        {
            o = cdr(o);
            WARNING_MSG("A non-number expression result was used in soustraction and was skipped");
        }
    }
    if (one_argument)
    {
        res= 1/res;
    }
    return make_float(res);
}


object inferieur(object o, object env)
{
    /* erreur si trop ou pas assez d'arguments */
    if (cdr(o)->type==SFS_NIL || cddr(o)->type!=SFS_NIL || o->type == SFS_NIL)
    {
        WARNING_MSG("inf takes 2 arguments");
        return NULL;
    }
    
    object eval_car = sfs_eval(car(o),env);
    if (eval_car == NULL)/*évite une seg fault si jamais l'évaluation génère une erreur*/
        return NULL;
    object eval_cadr = sfs_eval(cadr(o),env);
    if (eval_cadr == NULL)/*évite une seg fault si jamais l'évaluation génère une erreur*/
        return NULL;
    
    if (eval_car->type == SFS_INTEGER && eval_cadr->type == SFS_INTEGER)
    {
        if (eval_car->this.integer < eval_cadr->this.integer) return make_boolean(TRUE);
        else return make_boolean (FALSE);
    }
    
    else if (eval_car->type == SFS_INTEGER && eval_cadr->type == SFS_FLOAT)
    {
        if (eval_car->this.integer < eval_cadr->this.number.this.real) return make_boolean(TRUE);
        else return make_boolean (FALSE);
    }
    
    else if (eval_car->type == SFS_FLOAT && eval_cadr->type == SFS_INTEGER)
    {
        if (eval_car->this.number.this.real < eval_cadr->this.integer) return make_boolean(TRUE);
        else return make_boolean (FALSE);
    }
    
    else if(eval_car->type == SFS_FLOAT && eval_cadr->type == SFS_FLOAT)
    {
        if (eval_car->this.number.this.real < eval_cadr->this.number.this.real) return make_boolean(TRUE);
        else return make_boolean (FALSE);
    }
    
    else
    {
        WARNING_MSG("Comparaison needs number arguments");
        return NULL;
    }
}

object superieur(object o, object env)
{
    /* erreur si trop ou pas assez d'arguments */
    if (cdr(o)->type==SFS_NIL || cddr(o)->type!=SFS_NIL)
    {
        WARNING_MSG("sup takes 2 arguments");
        return NULL;
    }
    
    object eval_car = sfs_eval(car(o),env);
    if (eval_car == NULL)/*évite une seg fault si jamais l'évaluation génère une erreur*/
        return NULL;
    object eval_cadr = sfs_eval(cadr(o),env);
    if (eval_cadr == NULL)/*évite une seg fault si jamais l'évaluation génère une erreur*/
        return NULL;
    
    if (eval_car->type == SFS_INTEGER && eval_cadr->type == SFS_INTEGER)
    {
        if (eval_car->this.integer > eval_cadr->this.integer) return make_boolean(TRUE);
        else return make_boolean (FALSE);
    }
    
    else if (eval_car->type == SFS_INTEGER && eval_cadr->type == SFS_FLOAT)
    {
        if (eval_car->this.integer > eval_cadr->this.number.this.real) return make_boolean(TRUE);
        else return make_boolean (FALSE);
    }
    
    else if (eval_car->type == SFS_FLOAT && eval_cadr->type == SFS_INTEGER)
    {
        if (eval_car->this.number.this.real > eval_cadr->this.integer) return make_boolean(TRUE);
        else return make_boolean (FALSE);
    }
    
    else if(eval_car->type == SFS_FLOAT && eval_cadr->type == SFS_FLOAT)
    {
        if (eval_car->this.number.this.real > eval_cadr->this.number.this.real) return make_boolean(TRUE);
        else return make_boolean (FALSE);
    }
    
    else
    {
        WARNING_MSG("Comparaison needs number arguments");
        return NULL;
    }
}

object egalite(object o, object env)
{
    /* erreur si trop ou pas assez d'arguments */
    if (cdr(o)->type==SFS_NIL || cddr(o)->type!=SFS_NIL)
    {
        WARNING_MSG("egalite takes 2 arguments");
        return NULL;
    }
    
    object eval_car = sfs_eval(car(o),env);
    if (eval_car == NULL)/*évite une seg fault si jamais l'évaluation génère une erreur*/
        return NULL;
    object eval_cadr = sfs_eval(cadr(o),env);
    if (eval_cadr == NULL)/*évite une seg fault si jamais l'évaluation génère une erreur*/
        return NULL;
    
    if (eval_car->type == SFS_INTEGER && eval_cadr->type == SFS_INTEGER)
    {
        if (eval_car->this.integer == eval_cadr->this.integer) return make_boolean(TRUE);
        else return make_boolean (FALSE);
    }
    
    else if (eval_car->type == SFS_INTEGER && eval_cadr->type == SFS_FLOAT)
    {
        if (eval_car->this.integer == eval_cadr->this.number.this.real) return make_boolean(TRUE);
        else return make_boolean (FALSE);
    }
    
    else if (eval_car->type == SFS_FLOAT && eval_cadr->type == SFS_INTEGER)
    {
        if (eval_car->this.number.this.real == eval_cadr->this.integer) return make_boolean(TRUE);
        else return make_boolean (FALSE);
    }
    
    else if(eval_car->type == SFS_FLOAT && eval_cadr->type == SFS_FLOAT)
    {
        if (eval_car->this.number.this.real == eval_cadr->this.number.this.real)
            return make_boolean(TRUE);
        else
            return make_boolean (FALSE);
    }
    
    else 
    {
        WARNING_MSG("Comparaison needs number arguments");
        return NULL;
    }
}
/* MANIPULATION DE LISTES */

object p_car(object o, object env)
{
    /* erreur si trop ou pas assez d'arguments */
    if (cdr(o)->type!=SFS_NIL || o->type == SFS_NIL)
    {
        WARNING_MSG("car takes 1 argument");
        return NULL;
    }
    
    object eval_car = sfs_eval(car(o),env);
    if (eval_car == NULL)/*évite une seg fault si jamais l'évaluation génère une erreur*/
        return NULL;
    
    if (car(o)->type == SFS_PAIR)
    {
        return car(eval_car);
    }
    else
    {
        WARNING_MSG("primitive car takes a pair in argument");
        return NULL;
    }
}

object p_cdr(object o, object env)
{
    /* erreur si trop ou pas assez d'arguments */
    if (cdr(o)->type!=SFS_NIL || o->type == SFS_NIL)
    {
        WARNING_MSG("cdr takes 1 argument");
        return NULL;
    }
    
    object eval_car = sfs_eval(car(o),env);
    if (eval_car == NULL)/*évite une seg fault si jamais l'évaluation génère une erreur*/
        return NULL;
    
    if (o->type == SFS_PAIR)
    {
        return cdr(eval_car);
    }
    else
    {
        WARNING_MSG("primitive cdr takes a pair in argument");
        return NULL;
    }
}

object p_cons(object o, object env)
{
    /* erreur si trop ou pas assez d'arguments */
    if (cdr(o)->type==SFS_NIL || cddr(o)->type!=SFS_NIL || o->type == SFS_NIL)
    {
        WARNING_MSG("cons takes 2 arguments");
        return NULL;
    }
    
    object eval_car = sfs_eval(car(o),env);
    if (eval_car == NULL)/*évite une seg fault si jamais l'évaluation génère une erreur*/
        return NULL;
    object eval_cadr = sfs_eval(cadr(o),env);
    if (eval_cadr == NULL)/*évite une seg fault si jamais l'évaluation génère une erreur*/
        return NULL;
    
    return cons(eval_car,eval_cadr);
}

object p_list(object o, object env)
{
    object eval_car = sfs_eval(car(o),env);
    if (eval_car == NULL)/*évite une seg fault si jamais l'évaluation génère une erreur*/
        return NULL;
    
    if (cdr(o)->type == SFS_NIL)
    {
        return o;
    }
    else
    {
        return cons(eval_car,p_list(cdr(o), env));
    }
}

object set_car(object o, object env)
{
    /* erreur si trop ou pas assez d'arguments */
    if (cdr(o)->type==SFS_NIL || cddr(o)->type!=SFS_NIL || o->type == SFS_NIL)
    {
        WARNING_MSG("set-car! takes 2 arguments");
        return NULL;
    }
    object eval_car = sfs_eval(car(o),env);
    if (eval_car == NULL)/*évite une seg fault si jamais l'évaluation génère une erreur*/
        return NULL;
    object eval_cadr = sfs_eval(cadr(o),env);/*nouveau car*/
    if (eval_cadr == NULL)/*évite une seg fault si jamais l'évaluation génère une erreur*/
        return NULL;
    
    if (eval_car->type == SFS_PAIR)
    {
        eval_car->this.pair.car = eval_cadr;
        return eval_car;
    }
    else
    {
        WARNING_MSG("set-car! takes a pair in first argument");
        return NULL;
    }
}

object set_cdr(object o, object env)
{
    /* erreur si trop ou pas assez d'arguments */
    if (cdr(o)->type==SFS_NIL || cddr(o)->type!=SFS_NIL || o->type == SFS_NIL)
    {
        WARNING_MSG("set-cdr! takes 2 arguments");
        return NULL;
    }
    object eval_car = sfs_eval(car(o),env);
    if (eval_car == NULL)/*évite une seg fault si jamais l'évaluation génère une erreur*/
        return NULL;
    object eval_cadr = sfs_eval(cadr(o),env);/*nouveau cdr*/
    if (eval_cadr == NULL)/*évite une seg fault si jamais l'évaluation génère une erreur*/
        return NULL;
    
    if (eval_car->type == SFS_PAIR)
    {
        eval_car->this.pair.cdr = cons(eval_cadr,nil);
        return eval_car;
    }
    else
    {
        WARNING_MSG("set-cdr! takes a pair in first argument");
        return NULL;
    }
}


