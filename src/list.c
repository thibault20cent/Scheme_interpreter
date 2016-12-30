/**
 * @file list.c
 * @author Thibault Vincent
 * @date Thur Oct 13 14:01:30 2016
 * @brief List functions for SFS
 *
 * List functions for SFS.
 */

#include "list.h"


object car(object pair)
{
    return pair->this.pair.car;
}

object cdr(object pair)
{
    return pair->this.pair.cdr;
}

object cons(object element, object list)
{
    return make_pair(element, list);
}

object cadr(object input)
{
    return car(cdr(input));
}

object cdar(object input)
{
    return cdr(car(input));
}

object cadar(object input)
{
    return car(cdr(car(input)));
}

object caar(object input)
{
    return car(car(input));
}

object cddr(object input)
{
    return cdr(cdr(input));
}

object cdddr(object input)
{
    return cdr(cdr(cdr(input)));
}

object caddr(object input)
{
    return car(cdr(cdr(input)));
}

object cadddr(object input)
{
    return car(cdr(cdr(cdr(input)))) ;
}

object caadr(object input)
{
    return car(car(cdr(input))) ;
}

object caaar(object input)
{
    return car(car(car(input))) ;
}

object cddar(object input)
{
    return cdr(cdr(car(input))) ;
}

object cdaar(object input)
{
    return cdr(car(car(input))) ;
}

object caaadr(object input)
{
    return car(car(car(cdr(input)))) ;
}

