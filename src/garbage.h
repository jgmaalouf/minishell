#ifndef GARBAGE_H
# define GARBAGE_H

/* malloc exit(EXIT_FAILURE) */

/* PROHIBITED */
#include <ctype.h>
#include <string.h>
/* PROHIBITED */


# define DELIMITERS "\"'$ =@(*)#:/"
# define WORDCHARS  ""    // '*?_-.[]~&;!#$%^(){}<>' WORDCHARS='~!#$%^&*(){}[]<>?.+;-'

# define ASCII_DELIMITERS "\t\n\v\f\r !\"#$%&'()*+,-./:;<=>?@[\\]^`{|}~"


#endif
