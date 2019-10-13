/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchanal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/06 21:35:37 by fchanal           #+#    #+#             */
/*   Updated: 2017/06/16 18:33:23 by fchanal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <stdbool.h>
# include <stddef.h>

# define C_NONE         "\033[0m"
# define C_BOLD         "\033[1m"
# define C_GREY         "\033[1;30m"
# define C_RED          "\033[1;31m"
# define C_GREEN        "\033[1;32m"
# define C_YELLOW       "\033[1;33m"
# define C_BLUE         "\033[1;34m"
# define C_MAGENTA      "\033[1;35m"
# define C_CYAN         "\033[1;36m"
# define C_DEL          "\033[H\033[2J"

# define BUFF_SIZE 40

# define FT_ASCII_SIZE	128

# define FT_DIGIT		"0123456789"
# define FT_HEX_DIGIT	"0123456789abcdef"
# define FT_HEXU_DIGIT	"0123456789ABCDEF"

typedef struct s_list	t_list;

struct			s_list
{
	void		*data;
	t_list		*next;
};

typedef struct s_clist	t_clist;

struct			s_clist
{
	t_list		*list;
	t_list		*parent_node;
	size_t		list_size;
};

typedef struct s_btree	t_btree;

struct			s_btree
{
	t_btree		*left;
	t_btree		*right;
	void		*item;
};

typedef struct s_file	t_file;

struct			s_file
{
	int		fd;
	char	*buffer;
};

t_btree			*ft_bt_new_node(void *item);
void			ft_bt_insert_node(t_btree **root, void *item, \
		int (*cmpf)(void *, void *));
void			ft_bt_apply_asc(t_btree *root, void (*applyf)(void *));
void			ft_bt_apply_asc_del(t_btree **root, void (*applyf)(void *), \
		void (*del)(void **));
void			ft_bt_apply_desc(t_btree *root, void (*applyf)(void *));
void			ft_bt_apply_desc_del(t_btree **root, void (*applyf)(void *), \
		void (*del)(void **));
size_t			ft_bt_tree_len(t_btree *root);
void			ft_bt_tree_del(t_btree **root, void (*del)(void **));
size_t			ft_strlen(const char *s);
size_t			ft_strnlen(const char *str, size_t n);
char			*ft_strdup(const char *s1);
char			*ft_strcpy(char *s1, const char *s2);
char			*ft_strcat(char *s1, const char *s2);
char			*ft_strncat(char *s1, const char *s2, size_t n);
char			*ft_strchr(const char *s, int c);
char			*ft_strchr_zero(const char *s, int c);
char			*ft_strrchr(const char *s, int c);
char			*ft_strstr(const char *s1, const char *s2);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_isalpha(int c);
int				ft_islower(int c);
int				ft_isupper(int c);
int				ft_isdigit(int c);
int				ft_isalnum(int c);
int				ft_isascii(int c);
int				ft_isprint(int c);
int				ft_isalnumstr(char *str);
int				ft_isdigitstr(char *str);
int				ft_isalphastr(char *str);
int				ft_isprintstr(char *str);
int				ft_toupper(int c);
int				ft_tolower(int c);
void			ft_strdel(char **as);
void			ft_strclr(char *s);
void			ft_striter(char *s, void (*f)(char*));
void			ft_striteri(char *s, void (*f)(unsigned int, char*));
char			*ft_strmap(char const *s, char (*f)(char));
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char			*ft_strsub(char const *s, unsigned int start, size_t len);
void			ft_putchar(char c);
void			ft_putstr(const char *s);
void			ft_putendl(const char *s);
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char const *s, int fd);
void			ft_putendl_fd(char const *s, int fd);
void			ft_putnbr(int n);
void			ft_putnbrendl(int n);
void			ft_putnbr_fd(int n, int fd);
void			*ft_memset(void *b, int c, size_t len);
void			ft_bzero(void *s, size_t n);
void			*ft_memcpy(void *s1, const void *s2, size_t n);
void			*ft_memccpy(void *s1, const void *s2, int c, size_t n);
void			*ft_memchr(const void *s, int c, size_t n);
void			*ft_memalloc(size_t size);
void			ft_memdel(void **ap);
char			*ft_strstr(const char *s1, const char *s2);
char			*ft_strncpy(char *s1, const char *s2, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
void			*ft_memmove(void *s1, const void *s2, size_t n);
size_t			ft_strlcat(char *s1, const char *s2, size_t size);
int				ft_strnequ(char const *s1, char const *s2, size_t n);
int				ft_strequ(char const *s1, char const *s2);
char			*ft_strnew(size_t size);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strtrim(char const *s);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strnstr(const char *s1, const char *s2, size_t n);
void			*ft_realloc(void *mem, size_t size);
int				ft_getmin(int a, int b);
int				ft_getmax(int a, int b);
uint32_t		ft_abs(int n);
double			ft_dabs(double n);
int				ft_power(int n, int power);
double			ft_pow(double n, int power);
int				ft_sqrt(unsigned int n);
unsigned int	ft_get_abs_len(int n, int base);
uint16_t		ft_dexp(double number);
uint64_t		ft_dmant(double number);
bool			ft_dtype(double number);
double			ft_get_dint_part(double number);
double			ft_modf(double n, double *p_integer_part);
void			ft_strrev(char **s);
char			*ft_strmerge(char *s1, const char *s2, size_t len);
int				ft_atoi(const char *s);
int64_t			ft_atol(const char *s);
double			ft_atod(const char *s);
char			*ft_itoa(int n);
char			**ft_strsplit(char const *s, char c);
t_list			*ft_create_elem(void *data);
t_list			*ft_list_at(t_list *begin_list, unsigned int nbr);
t_list			*ft_list_find(t_list *begin_list, void *data_ref, int (*cmp)());
void			ft_list_foreach(t_list *begin_list, void (*f)(void *));
void			ft_list_foreach_if(t_list *begin_list, void (*f)(void *),
									void *data_ref, int (*cmp)());
t_list			*ft_list_last(t_list *begin_list);
void			ft_list_merge(t_list **begin_list1, t_list *begin_list2);
void			ft_nodes_swap(t_list **begin_list, t_list *s1, t_list *s2);
void			ft_list_push_back(t_list **begin_list, void *data);
void			ft_list_push_front(t_list **begin_list, void *data);
t_list			*ft_list_push_params(int ac, char **av);
void			ft_list_remove_if(t_list **begin_list,
									void *data_ref, int (*cmp)());
void			ft_list_reverse(t_list **begin_list);
int				ft_list_size(t_list *begin_list);
void			ft_list_sort(t_list **begin_list, int (*cmp)());
void			ft_sorted_list_insert(t_list **begin_list,
									void *data, int (*cmp)());
void			ft_sorted_list_merge(t_list **begin_list1,
									t_list *begin_list2, int (*cmp)());
t_list			*ft_list_find_prev(t_list *list, t_list *wall);
void			ft_list_clear(t_list **begin_list);
void			ft_list_del(t_list **lst, void (*del)(void **));
void			ft_list_del_node(t_list **head, t_list **node,
														void (*del)(void **));
char			*ft_read_file(const char *path);
long long		ft_file_size(const char *path);
int				ft_get_next_line(const int fd, char **line);
t_list			*ft_clist_new(t_clist *clist, void *data);
t_list			*ft_clist_push_back(t_clist *clist, void *data);
t_list			*ft_clist_insert(t_clist *clist, t_list *current, void *data);
t_list			*ft_clist_find_prev(t_list *wall);
void			ft_clist_del_node(t_clist *clist, t_list **node,
														void (*del)(void**));
void			ft_clist_foreach(t_clist *clist, void (*f)(void *));
uint64_t		ft_get_nbr(const char **s);
int64_t			ft_get_snbr(const char **s);

#endif
