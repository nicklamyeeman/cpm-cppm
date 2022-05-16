#include "open_read_file.h"

char *read_file(int fd, struct stat *st)
{
	char *result = malloc(st->st_size + 1);
	int	size = st->st_size;

    if (!result) {
        fprintf(stderr, "Error: %s\n", strerror(errno));
        return (NULL);
    }
	while (size >= 0)
		size = read(fd, result, size);
    result[st->st_size] = '\0';
    return (result);
}

char *open_read_file(char const *filepath)
{
	struct stat *st = NULL;
    char *result = NULL;
    int fd = open(filepath, O_RDONLY);

    if (fd == -1 || (st = malloc(sizeof(struct stat))) == NULL) {
		fprintf(stderr, "Error: %s\n", strerror(errno));
        return (NULL);
    }
    stat(filepath, st);
    result = read_file(fd, st);
	close(fd);
    free(st);
	return (result);
}
