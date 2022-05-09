#ifndef EXPLODE_H_
#define EXPLODE_H_

#include <stdlib.h>

/**
 * @brief count number of line of the future array
 * 
 * @param {char const *} str - string to be explode 
 * @param {char} separator - char which will split the string 
 * @return {int} number of line founded 
 */
int nb_line(char const *str, char separator);

/**
 * @brief malloc my future array
 * 
 * @param {char const *} str - string to be explode 
 * @param {char separator} - char which will split the string 
 * @return {char **} - array malloc 
 */
char **malloc_array(char const *str, char separator);

/**
 * @brief clean the string full of separators
 * 
 * @param {char const *} str - original string 
 * @param {char} separator - separator 
 * @return {char *} the clean string 
 */
char *clean_string(char const *str, char separator);

/**
 * @brief explode / split / str_to_word_tab, call it what you wnt
 * 
 * @param {char const *} str - string to be exploded 
 * @param {char} separator - char which will split the string 
 * @return {char **} - array of the string split 
 */
char **explode(char const *str, char separator);

#endif /* !EXPLODE_H_ */
