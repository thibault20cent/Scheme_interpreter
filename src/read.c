/**
 * @file read.c
 * @author François Cayre <cayre@yiking.(null)>
 * @date Fri Jun 15 18:31:05 2012
 * @brief Read routine for SFS.
 *
 * Read routine for SFS.
 */

#include <stdio.h>
#include <ctype.h>

#include <readline/readline.h>
#include <readline/history.h>

#include "read.h"


/*
 * @fn void insert_char(char subject[], const char insert[], int pos)
 *
 * @brief insert un caractère dans la chaine subject à la position pos
 */

void insert_char(char* subject, const char* insert, int pos)
{
    string buf = "";
    
    strncpy(buf, subject, pos);
    int len = strlen(buf);
    strcpy(buf+len, insert);
    len += strlen(insert);
    strcpy(buf+len, subject+pos);
    
    strcpy(subject, buf);
}

/*
 * @fn void sub_string(char subject[], int start)
 *
 * @brief extrait une sous chaine de la chaine subject depuis la position start jusqu'à la fin
 */

void sub_string(char* subject, int start)
{
    string buf="";
    
    int j=1;
    
    buf[0]=subject[start];
    
    while (subject[start+j] != '\0')
    {
        buf[j]=subject[start+j];
        j++;
    }
    
    strcpy(subject,buf);
}

/*
 * @fn void remove_backslash(char str[])
 *
 * @brief enlève tous les backslah se trouvant avant une guillemet dans la chaine de caratère str
 */

void remove_backslash(char* str)
{
    string buf="";
    int i=0;
    
    while( str[i] !='\0')
    {
        if (str[i] == '"')
        {
            if (str[i-1] == '\\')
            {
                strncpy(buf,str,i-1);
                sub_string(str,i);
                strcpy(str,strcat(buf,str));
            }
        }
        i++;
    }
}


/*
 * @fn char* first_usefull_char(char* line)
 *
 * @brief retourne un pointeur sur le premier caractere utile dans line
 * ou NULL si line ne contient que des espaces et des commentaires
 */

char* first_usefull_char(char* line) {

    int i=0;
    if (line == NULL) {
        return NULL;
    }
    i = 0;
    /* on saute les espaces */
    while(line[i] != '\0' && isspace(line[i])) {
        i++;
    }
    /* si fin de ligne => ligne inutile */
    if(line[i] == '\0') {
        return NULL;
    }
    /* si premier caractere non espace est ';' => ligne inutile */
    if(line[i] == ';') {
        return NULL;
    }
    return line + i; /* ligne utile */
}

/*
 * @fn char* first_usefull_char_v2(char* line)
 *
 * @brief enlève les espaces inutiles avant le premier caractère utile de line
 */

void first_usefull_char_v2(char* line) {
    
    int i=0;
    string buf="";
    
    if (line == NULL) {
        return;
    }
    i = 0;
    /* on saute les espaces */
    while(line[i] != '\0' && isspace(line[i]))
    {
        i++;
    }
    /* si fin de ligne => ligne inutile */
    if(line[i] == '\0') {
        return;
    }
    /* si premier caractere non espace est ';' => ligne inutile */
    if(line[i] == ';') {
        return;
    }
    /* copie */
    strcpy(buf, line+i);
    strcpy(line, buf);
}

char* first_usefull_char_v3(char* line, int* i) {
    
    if (line == NULL) {
        return NULL;
    }
    /* on saute les espaces */
    while(line[*i] != '\0' && isspace(line[*i])) {
        (*i)++;
    }
    /* si fin de ligne => ligne inutile */
    if(line[*i] == '\0') {
        return NULL;
    }
    /* si premier caractere non espace est ';' => ligne inutile */
    if(line[*i] == ';') {
        return NULL;
    }
    return line + (*i); /* ligne utile */
}

/**
 * @fn uint  sfs_get_sexpr( char *input, FILE *fp )
 *
 * @brief extrait la prochaine S-Expression dans le flux fp et la stocke dans input
 * (meme si elle est repartie sur plusieurs lignes)
 * @param fp (FILE *) flux d'entree (ouvert en ecriture, mode texte)
 * @param input (char *) chaine allouee de taille BIGSTRING, dans laquelle la S-Expression sera stockée
 *
 * @return S_OK si une S-Expression apparemment valide a ete trouvee
 * @return S_KO si on n'a pas trouve de S-Expression valide
 * @return S_END si fin de fichier atteinte sans avoir lu de caractere utile.
 *
 * sfs_get_sexpr commence par lire une ligne dans fp,
 * puis compte le nombre de parentheses ouvrantes et fermantes sur la ligne.
 * Les parentheses dans des chaines et les caracteres Scheme #\( et #\)
 * ne sont pas comptes.
 *
 * Si le compte devient zéro et que 
 *        - la ligne est fini, la fonction retourne S_OK
 * 				- la ligne n'est pas fini la fonction retourne S_KO
 *
 * S'il y a plus de parentheses fermantes qu'ouvrantes,
 * la fonction retourne S_KO.
 * Les commentaires et espaces qui figurent a la fin de chaque ligne
 * sont remplacés par un espace.
 * Les espaces qui figurent a la fin de la S-Expression (y compris '\n')
 * sont supprimés.
 *
 * Attention : cette fonction refuse les S-Expression multiple sur une seule ligne. Ainsi :
 *    a b c
 *    (qqchose) (autrechose)
 *    (qqchose) 78
 * seront considereees comme des erreurs
 * et la fonction retournera S_KO
 *
 * @pre fp doit etre prealablement ouvert en lecture
 * @pre input doit etre prealablement alloue en memoire, de taille BIGSTRING
 */

typedef enum {
    NOTHING,        /* rien n'a ete trouve encore.. */
    STRING_ATOME,   /* la premiere trouvee dans la ligne semble etre un atome */
    BASIC_ATOME,    /* la premiere trouvee dans la ligne semble etre d'une chaine */
    S_EXPR_PARENTHESIS, /* la premiere trouvee dans la ligne semble etre une expression parenthesee */
    FINISHED        /* on a trouve une S-Expr bien formee */
} EXPRESSION_TYPE_T;

uint  sfs_get_sexpr( char *input, FILE *fp ) {
    int       parlevel = 0;
    uint      in_string = FALSE;
    uint      s = 0;
    char      k[BIGSTRING];
    char      *ret = NULL;
    char      *chunk = NULL;
    uint      i = 0;
    string    sfs_prompt;
    
    EXPRESSION_TYPE_T typeOfExpressionFound = NOTHING;
    
    parlevel = 0;
    memset( input, '\0', BIGSTRING );
    
    do {
        ret = NULL;
        chunk = NULL;
        
        /* si en mode interactif*/
        if ( stdin == fp ) {
            uint nspaces = 2*parlevel;
            
            init_string( sfs_prompt );
            
            /* le prompt indique le niveau de parenthese
             et decale la prochaine entrée en fonction
             de ce niveau (un peu à la python)*/
            sprintf( sfs_prompt, "\033[35m SFS:%u > \033[0m", parlevel );
            
            for ( i= 0; i< nspaces; i++ ) {
                sfs_prompt[strlen(sfs_prompt)] = ' ';
            }
            
            /* si sur plusieurs lignes, le \n équivaut à un espace*/
            if (nspaces>0) {
                input[strlen(input)+1] = '\0';
                input[strlen(input)] = ' ';
            }
            
            /*saisie de la prochaine ligne à ajouter dans l'input*/
            chunk = readline( sfs_prompt );
        }
        /*si en mode fichier*/
        else {
            chunk=k;
            memset( chunk, '\0', BIGSTRING );
            ret = fgets( chunk, BIGSTRING, fp );
            
            if ( NULL == ret ) {
                /* fin de fichier...*/
                if ( parlevel != 0 ) {
                    WARNING_MSG( "Parse error: missing ')'" );
                    return S_KO;
                }
                return S_END;
            }
            
            if (strlen(chunk) == BIGSTRING-1
                && chunk[BIGSTRING-1] != '\n'
                && !feof(fp)) {
                WARNING_MSG( "Too long line for this interpreter!" );
                return S_KO;
            }
        }
        
        /* si la ligne est inutile
        	=> on va directement à la prochaine iteration */
        if (first_usefull_char(chunk) == NULL) {
            continue;
        }
        
        
        s = strlen( chunk );
        
        if ( s > 0 ) {
            if (strlen(input) + s > BIGSTRING-1 ) {
                WARNING_MSG( "Too long a S-expression for this interpreter!" );
                return S_KO;
            }
            
            for ( i = 0; i< strlen(chunk); i++ ) {
                /* si la fin de la ligne chunk est inutile,
                 on ajoute un espace dans input et on sort de la boucle*/
                if ( in_string == FALSE && first_usefull_char(chunk + i) == NULL ) {
                    chunk[i]='\0';
                    input[strlen(input)] = ' ';
                    break;
                }
                
                
                switch(chunk[i]) {
                    case '(':
                        if (in_string == FALSE
                            && ! ( i>1 && chunk[i-1] == '\\' && chunk[i-2] == '#' ) ) {
                            parlevel++;
                            typeOfExpressionFound = S_EXPR_PARENTHESIS;
                        }
                        break;
                    case ')':
                        if ( in_string == FALSE
                            && ! ( i>1 && chunk[i-1] == '\\' && chunk[i-2] == '#' ) ) {
                            parlevel--;
                            if (parlevel == 0 ) {
                                typeOfExpressionFound = FINISHED;
                            }
                            if ( parlevel < 0 ) {
                                WARNING_MSG( "Parse error : cannot start with ')'" );
                                return S_KO;
                            }
                        }
                        break;
                    case '"':
                        if ( i<2 || chunk[i-1] != '\\' ) {
                            if ( in_string == FALSE ) {
                                if(typeOfExpressionFound == BASIC_ATOME) {
                                    WARNING_MSG("Parse error: invalid string after atom : '%s'", chunk+i);
                                    return S_KO;
                                }
                                in_string = TRUE;
                                if(typeOfExpressionFound != S_EXPR_PARENTHESIS) {
                                    typeOfExpressionFound = STRING_ATOME;
                                }
                            }
                            else {
                                in_string = FALSE;
                                if(typeOfExpressionFound == STRING_ATOME) {
                                    typeOfExpressionFound = FINISHED;
                                }
                            }
                        }
                        break;
                    default:
                        if(in_string == FALSE) {
                            if(isspace(chunk[i])) {
                                if(typeOfExpressionFound == BASIC_ATOME) {
                                    typeOfExpressionFound = FINISHED;
                                }
                            } else if(typeOfExpressionFound != S_EXPR_PARENTHESIS) {
                                typeOfExpressionFound = BASIC_ATOME;
                            }
                        }
                        break;
                }
                
                
                if(typeOfExpressionFound == FINISHED) {
                    char *first_useful = first_usefull_char(chunk + i + 1);
                    if( first_useful != NULL) {
                        if(*first_useful == ')' ) {
                            WARNING_MSG( "Parse error: too many closing parenthesis')'" );
                        }
                        else {
                            WARNING_MSG("Parse error: invalid trailing chars after S-Expr : '%s'", chunk+i);
                        }
                        return S_KO;
                    }
                }
                
                /* recopie char par char*/
                input[strlen(input)] = chunk[i];
            }
            if(in_string == TRUE) {
                WARNING_MSG( "Parse error: non terminated string on line %s", chunk );
                return S_KO;
            }
        }
        
        
        if ( parlevel > 0 && fp != stdin ) {
            if ( feof( fp ) ) {
                WARNING_MSG( "Parse error: missing ')'" );
                return S_KO;
            }
            
            if (input[strlen(input)-1] == '\n') input[strlen(input)-1] = ' ';
        }
    } while ( parlevel > 0 );
    
    /* Suppression des espaces restant a la fin de l'expression, notamment le dernier '\n' */
    while (isspace(input[strlen(input)-1])) input[strlen(input)-1] = '\0';
    
    if(stdin == fp) {
        add_history( input );
    }
    return S_OK;
}


/*
 * @fn object sfs_read_atom( char *input, uint *here )
 *
 * @brief crée et retourne un atome scheme à partir de la chaine de caractère input. Renvoie une erreur si l'atome n'est pas valide en scheme. Cette fonction lira uniquement l'atome commencant à la position here de la chaine input et terminera sa lecture lorsqu'un espace, une parenthèse fermante ou une fin de chaine ( \0 ) est rencontré. Le cas d'apparition de ces caractères dans une chaine ou un symbole est géré conformément à la grammaire du scheme ( norme R5RS ).
 */


object sfs_read_atom( char *input, uint *here )
{
    switch(input[*here])
    
    {
        case '#':
            
            return read_bool_char(input, here);
        
        case '+':
        case '-':
            
            if ( isdigit(input[(*here)+1]) )
            {
                return read_number(input, here);
            }
            else
            {
                return read_symbol(input, here);
            }
            
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':

            return read_number(input, here);

            
        case '"':
            
            return read_string(input, here);
            
        default:
            
            return read_symbol(input, here);
    }
}

/* BOOLEAN AND CHAR */

object read_bool_char(char* input, uint* here )
{
    object atom = NULL;
    (*here)++;

    /* BOOLEAN */

    if (input[*here]=='f' || input[*here]=='t')
    {
        if (input[(*here)+1]=='\0' || isspace(input[(*here)+1]) || input[(*here)+1]==')' || input[(*here)+1]=='(')
        {
            if (input[*here]=='f')
            {
                atom = sfs_false;
                (*here)++;
                return atom;
            }
                
            if (input[*here]=='t')
            {
                atom = sfs_true;                
                (*here)++;
                return atom;
            }
        }
        else
        {
            WARNING_MSG("Atome syntax error: invalid # atom");
            return NULL;
        }
    }


    /* CHAR */

    if (input[*here]=='\\')
    {
        (*here)++;
        if (input[(*here)+1]=='\0' || isspace(input[(*here)+1]) || input[(*here)+1]==')' || input[(*here)+1]=='(')
        {
            atom = make_character(input[*here]);
            (*here)++;
            return atom;
        }
        if (input[*here]=='s' && input[(*here)+1]=='p' && input[(*here)+2]=='a' && input[(*here)+3]=='c' && input[(*here)+4]=='e')
        {
            atom = make_character(' ');
            (*here)+=5;
            return atom;
        }
        if(input[*here]=='n' && input[(*here)+1]=='e' && input[(*here)+2]=='w' && input[(*here)+3]=='l' && input[(*here)+4]=='i' && input[(*here)+5]=='n' && input[(*here)+6]=='e')
        {
            atom = make_character('\n');
            (*here)+=7;
            return atom;
        }
        else
        {
            WARNING_MSG("Atome syntax error: invalid # atom ");
            return NULL;
        }
    }

    else
    {
        WARNING_MSG("Atome syntax error: invalid # atom ");
        return NULL;
    }
}


/* NUMBER*/

object read_number(char* input, uint* here)
{         
    object atom = NULL;
    {
        int i=1;
        string str="";
        str[0]=input[*here];
        
        
        while (input[(*here)+i] != '\0' && !isspace(input[(*here)+i]) && input[(*here)+i]!=')' && input[(*here)+i]!='(' && input[(*here)+i]!='"')
        {

            /* INTEGER*/
            if (isdigit(input[(*here)+i])) 
            {
                str[i]=input[(*here)+i];
                i++;
            }

            else
            {

                /* FLOAT*/
                if (input[(*here)+i] == '.') 
                {
                    str[i]=input[(*here)+i];
                    i++;
                    while (input[(*here)+i] != '\0' && !isspace(input[(*here)+i]) && input[(*here)+i]!=')' && input[(*here)+i]!='(')
                    {
                        if (isdigit(input[(*here)+i]))
                        {
                            str[i]=input[(*here)+i];
                            i++;
                        }
                        else
                        {
                            WARNING_MSG("Atom syntax error: invalid float atom");
                            atom = NULL;
                            (*here)+=i;
                            return atom;
                        }
                    }
                    atom = make_float(strtod(str,NULL));
                    (*here)+=i;
                    return atom;
                }
                else
                {
                    WARNING_MSG("Atom syntax error: invalid int atom");
                    (*here)+=i;
                    return NULL;
                }
            }
        }
        atom = make_integer(strtol(str,NULL,10));
        (*here)+=i;
        return atom;
    }
}


/* STRING */

object read_string(char* input, uint* here)
{
    object atom = NULL;
    string str = "";
    int i=1;
    
    while ( input[*here+i] != '"' )
        {
            
            if (input[*here+i] == '\\' && input[*here+i+1] == '"')
            {
                str[i-1]='\\';
                str[i]='"';
                i+=2;
                continue;
            }
            str[i-1]=input[*here+i];
            i++;
            
        }
    atom = make_string(str);
    (*here)+=i+1;
    return atom;
}


/* SYMBOL */

object read_symbol(char* input, uint* here)
{
    object atom = NULL;
    int i=1;
    string str = "";
    str[0]=input[*here];
    while (input[(*here)+i] != '\0'&& !isspace(input[(*here)+i]) && input[(*here)+i]!=')'&& input[(*here)+i]!='"'&& input[(*here)+i]!='(')
    {
        str[i]=input[(*here)+i];
        i++;
    }
    atom = make_symbol(str);
    (*here)+=i;
    return atom;               
}

/*
 * @fn object sfs_read_pair( char *stream, uint *i )
 *
 * @brief crée et retourne un objet de type pair. Cette fonction et sfs_read sont mutuellement récursive. Ces 2 fonctions créent l'arbre syntaxique d'une expression en scheme ( s-expression )
 */

object sfs_read_pair( char *stream, uint *i )
{
    
        object o_pair = make_object(SFS_PAIR);
    
        first_usefull_char_v2(stream);
    
        o_pair->this.pair.car = sfs_read(stream, i);
    
        /*insertion parenthese*/
        insert_char(stream, "(", (*i));
        /*découpage de la chaine*/
        sub_string(stream, *i);
        /*réinitialisation du compteur suite au découpage de la chaine*/
        (*i)=0;
    
        o_pair->this.pair.cdr = sfs_read(stream, i);
    
    return o_pair;
}

/*
 * @fn object sfs_read( char *input, uint *here )
 *
 * @brief crée et retourne un objet de type pair. Cette fonction et sfs_read_pair sont mutuellement récursive. Ces 2 fonctions créent l'arbre syntaxique d'une expression en scheme ( s-expression )
 */

object sfs_read( char *input, uint *here )
{
    first_usefull_char_v2(input);
    int* i = malloc ( sizeof(*i));
    *i=0;
    
    if ( input[*here] == '(' )
    {
        
        if ( first_usefull_char_v3(input+1, i)[0] == ')' )
        {
            *here += 2+(*i);
            return nil;
        }
        else
        {
            (*here)++;
            sub_string(input, *here);
            /*réinitialisation du compteur suite au découpage de la chaine*/
            (*here)=0;
            
            return sfs_read_pair( input, here );
        }
        
    }
    
    /* Raccourci de la forme quote*/
    if (input[*here]=='\'')
    {
        (*here)++;
        
        /* Si espace */
        if (input[(*here)]=='\0'||isspace(input[(*here)]) )
        {
            /* C'est un symbole */
            first_usefull_char_v2(input);
            return sfs_read_atom( input, here );
        }
        else
        {
            /* Sinon c'est le raccourci de la forme quote */
            object o2 = make_object(SFS_PAIR);
            o2->this.pair.car = sfs_read(input, here);
            o2->this.pair.cdr = nil;
            object o1 = make_pair(make_symbol("quote"),o2);
            return o1;
        }
    }
    else
    {
        first_usefull_char_v2(input);
        return sfs_read_atom( input, here );
    }
}





