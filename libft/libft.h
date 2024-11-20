/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrasamoe <lrasamoe@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 16:33:23 by yaretel-          #+#    #+#             */
/*   Updated: 2024/07/29 14:27:44 by lrasamoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

char	*verify_line(char **line_reserve);
int		browse_line(char **line_reserve);
char	*transfer_in_reserve(char **reserve, int fd);
char	*transfer_read_in_buffer(int fd);
char	*get_next_line(int fd);

int		ft_numbers(int n);
int		count_number(int n);
int		ft_print_nbr(int n);
int		ft_print_char(char c);
int		ft_print_hexa(unsigned int nbr, int lowupp);
int		ft_print_pointer(unsigned long long nbr);
int		ft_is_zero(void);
int		ft_print_str(char *s);
int		ft_numbers_uns(unsigned int n);
char	*ft_itoa_nbr_uns(unsigned int n);
int		ft_print_nbr_uns(unsigned int n);
int		ft_printf(const char *str, ...);
int		ft_format(char c, va_list print);

int		ft_atoi(const char *nptr);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
char	*ft_itoa(int n);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
void	*ft_memset(void *s, int c, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
char	*ft_strtrim(char const *s1, const char *set);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcat(char *d, const char *s, size_t dstsize);
char	*ft_strrchr(const char *s, int c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(char const *s, char c);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char	*ft_strchr(const char *s, int c);
char	*ft_strnstr(const char *big, const char *little, size_t len);
void	ft_striteri(char *s, void (*f)(unsigned	int, char*));
char	*ft_strdup(const char *s);
size_t	ft_strlen(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_toupper(int c);
int		ft_tolower(int c);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int n,	int fd);
void	ft_putendl_fd(char const *s, int fd);

#endif
