#ifndef OPEN_READ_FILE_H_
#define OPEN_READ_FILE_H_

#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

/**
 * @brief read a file a return his content
 * 
 * @param {int} fd - file descriptor opened before 
 * @param {struct stat *} st - file stats struct
 * @return {char *} - return file content as string 
 */
char *read_file(int fd, struct stat *st);

/**
 * @brief open file and return the read content
 * 
 * @param {char const *} filepath - path of the file to open 
 * @return {char *} - file content as a string 
 */
char *open_read_file(char const *filepath);

#endif /* !OPEN_READ_FILE_H_ */
