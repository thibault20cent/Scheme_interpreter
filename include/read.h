
/**
 * @file read.h
 * @author François Cayre <cayre@yiking.(null)>
 * @date Fri Jun 15 18:30:11 2012
 * @brief Read routine for SFS.
 *
 * Read routine for SFS.
 */

#ifndef _READ_H_
#define _READ_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>

#include "list.h"

enum {S_OK, S_KO, S_END};

void  insert_char(char subject[], const char insert[], int pos);
void  sub_string(char subject[], int start);
void  remove_backslash(char str[]);
char* first_usefull_char_v3(char* line, int* i);
void  first_usefull_char_v2(char* line);

uint   sfs_get_sexpr( string input, FILE *fp );

object sfs_read( char *input, uint *here );
object sfs_read_atom( char *input, uint *here );
object sfs_read_pair( char *stream, uint *i );

object read_bool_char(char* input, uint* here);
object read_number(char* input, uint* here);
object read_number(char* input, uint* here);
object read_string(char* input, uint* here);
object read_symbol(char* input, uint* here);



#ifdef __cplusplus
}
#endif

#endif /* _READ_H_ */
