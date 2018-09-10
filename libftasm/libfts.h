#ifndef LIBFTS_H
# define LIBFTS_H

#include <stdio.h>
#include <string.h>
#include <unistd.h>

int		ft_isalnum(char c);
void	ft_bzero(void *str, int c);
int		ft_isalpha(char c);
int		ft_isascii(char c);
int		ft_isdigit(char c);
int		ft_isprint(char c);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memset(void *b, int c, size_t len);
void	ft_puts(char *str);
char	*ft_strcat(char *str1, char *str2);
char	*ft_strdup(const char *s1);
int		ft_strlen(char *str);
int		ft_tolower(int c);
int		ft_toupper(int c);
void	ft_cat(int fd);

#endif
