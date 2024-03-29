/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmney <hmney@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 18:26:33 by hmney             #+#    #+#             */
/*   Updated: 2019/11/04 22:42:46 by hmney            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include "get_next_line.h"

# include <stdint.h>

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

typedef struct		s_queue
{
	t_list			*front;
	t_list			*rear;
	int				counter;
}					t_queue;

void				*ft_memset(void *b, int c, size_t len);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
size_t				ft_strlen(const char *str);
char				*ft_strdup(const char *src);
char				*ft_strcpy(char *dest, const char *src);
char				*ft_strncpy(char *dest, const char *src, size_t n);
char				*ft_strcat(char *dest, const char *src);
char				*ft_strncat(char *dest, const char *src, size_t n);
size_t				ft_strlcat(char *dest, const char *src, size_t maxlen);
char				*ft_strchr(const char *str, int c);
char				*ft_strrchr(const char *str, int c);
char				*ft_strstr(const char *string, const char *substring);
char				*ft_strnstr(const char	*string, const char *substring,
		size_t len);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *str1, const char *str2, size_t n);
intmax_t			ft_atol(const char *str);
int					ft_atoi(const char *str);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isspace(int c);
int					ft_isprint(int c);
int					ft_isnumber(char *str);
int					ft_tolower(int c);
int					ft_toupper(int c);
void				*ft_memalloc(size_t size);
void				ft_memdel(void **ap);
char				*ft_strnew(size_t size);
void				ft_strdel(char **as);
void				ft_strclr(char *s);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s);
char				**ft_strsplit(char const *s, char c);
char				*ft_itoa(int n);
void				ft_putchar(char c);
void				ft_putstr(char const *s);
void				ft_putendl(char const *s);
void				ft_putnbr(int n);
void				ft_putbits(const char *bits, size_t size);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr_fd(int n, int fd);
void				ft_putbits_fd(const char *bits, size_t size, int fd);
t_list				*ft_lstnew(void const *content, size_t content_size);
void				ft_lstdelone(t_list **alst, void (*del)(void*, size_t));
void				ft_lstdel(t_list **alst, void (*del)(void*, size_t));
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
int					ft_list_add_back(t_list **begin_list, void const *content,
		size_t content_size);
size_t				ft_lstlength(t_list *begin_list);
void				ft_lstclear(t_list **begin_list);
t_list				*ft_list_find(t_list *begin_list, void const *content,
		int (*cmp)());
void				ft_lstrev(t_list **head);
int					ft_isupper(int c);
int					ft_islower(int c);
int					ft_ispunct(int c);
int					ft_isgraph(int c);
int					ft_isblank(int c);
int					get_next_line(const int fd, char **line);
int					ft_length_number(intmax_t number);
int					ft_tablen(char **tab);
void				free_tab(char ***tab);
int					ft_search_characters(char *str, char search);
intmax_t			ft_hash_string(char *str);
int					empty_queue(t_queue *queue);
t_list				*dequeue(t_queue *queue);
int					enqueue(t_queue *queue, void *content, size_t content_size);
void				free_queue(t_queue *queue);
void				ft_delete_content(void *content, size_t content_size);
void				ft_delete_node(void *content, size_t content_size);
int					ft_ceil(float score);
int16_t				ft_swap_int16(int16_t value);
int32_t				ft_swap_int32(int32_t value);
#endif
