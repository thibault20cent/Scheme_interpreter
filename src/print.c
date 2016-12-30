/**
 * @file print.c
 * @author François Cayre <cayre@yiking.(null)>
 * @date Fri Jun 22 20:12:17 2012
 * @brief Printing stuff for SFS.
 *
 * Printing stuff for SFS.
 */

#include "print.h"

#include <stdio.h>

/*
 * @fn void sfs_print_atom( object o )
 *
 * @brief fonction d'affichage d'un atome
 */

void sfs_print_atom( object o ) {

    switch( o->type ) {
            
        case SFS_STRING :
            
            printf( "\"%s\"", o->this.string);
            break;
            
        case SFS_BOOLEAN :
            
            if (o->this.boolean_value == TRUE)
                printf( "#t");
            if (o->this.boolean_value == FALSE)
                printf( "#f");
            break;
            
        case SFS_CHARACTER :
            
            if (o->this.character == '\n')
            {
                printf("#\\newline");
                break;
            }
            if (o->this.character == ' ')
            {
                printf("#\\space");
                break;
            }
            else
            {
                printf( "#\\%c", o->this.character);
                break;
            }
            
        case SFS_INTEGER :

            printf( "%d", o->this.integer);
            break;
        
        case SFS_FLOAT :
            
            printf( "%lf", o->this.number.this.real);
            break;
            
        case SFS_SYMBOL :
            
            printf( "%s", o->this.symbol );
            break;
            
        case SFS_NIL :
            
            printf("()" );
            break;
        
        case SFS_PRIMITIVE :
            printf("#<procedure>");
            break;
            
        case SFS_COMPOUND :
            printf("#<procedure>");
            break;
    }
    return;
}

/*
 * @fn void sfs_print_pair( object o )
 *
 * @brief fonction d'affichage d'une paire
 */

void sfs_print_pair( object o ) {
    
    if ( (o->this.pair.car->type == SFS_PAIR && o->this.pair.cdr->type == SFS_NIL) || (o->this.pair.cdr->type == SFS_PAIR && o->this.pair.car->type == SFS_PAIR) )
    {
        if (o->this.pair.cdr->type == SFS_PAIR && o->this.pair.car->type == SFS_PAIR )
        {
            printf("(");
            sfs_print(o->this.pair.car);
            printf(" ");
            sfs_print(o->this.pair.cdr);
        }
        else
        {
            printf("(");
            sfs_print(o->this.pair.car);
            printf(")");
        }
    }
    
    else
    {
        if 	(o->this.pair.cdr->type != SFS_PAIR)
        {
            sfs_print(o->this.pair.car);
            printf(")");
        }
        else
        {
            sfs_print(o->this.pair.car);
            printf(" ");
            sfs_print(o->this.pair.cdr);
        }
    }
    
    
    return;
}

/*
 * @fn void sfs_print( object o )
 *
 * @brief fonction principale d'affichage
 */

void sfs_print( object o ) {

    if ( SFS_PAIR == o->type )
    {
        sfs_print_pair( o );
    }
    else
    {
        sfs_print_atom( o );
    }
}

/*
 * @fn void sfs_print_first_bracket( object o )
 *
 * @brief point d'entréee de l'affichage dans la boucle REPL
 */

void sfs_print_first_bracket( object o )
{
    printf( "==> " );
    
    if ( SFS_PAIR == o->type )
    {
        printf("(");
    }
    
    sfs_print( o );
}






