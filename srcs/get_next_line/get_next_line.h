#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 52
# endif

char	*get_next_line(int fd);
int		check_new_line(char *s);
int		count_len(char *s);
void	add_text(char **s1, char *s2);
char	*get_result(char *s);
char	*get_rest(char **s);

#endif
