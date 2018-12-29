/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_printf.h                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: qcharpen <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/27 13:02:54 by qcharpen     #+#   ##    ##    #+#       */
/*   Updated: 2018/12/12 07:33:01 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdio.h>
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

# define MAX(a, b) ((a > b) ? a : b)
# define MIN(a, b) ((a > b) ? b : a)
# define ABS(a) (a > 0 ? a : -a)

enum					e_ftprintf_flags {HASH, ZERO, MINUS, PLUS, SPACE, MAJ_L};
enum					e_ftprintf_size {NONE, HH, H, L, LL, J, Z};

typedef struct			s_ftprintf
{
	char				*str;
	int					size;
	struct s_ftprintf	*next;
}						t_ftprintf;

typedef struct			s_ftprintf_flags
{
	int					flags[6];
	int					width;
	int					prec;
	int					size;
	char				conv;
}						t_ftprintf_flags;

typedef struct			s_ftprintf_handlers
{
	char				conv;
	t_ftprintf			*(*fct_handle)(t_ftprintf_flags*, va_list);
}						t_ftprintf_handlers;

void					ftprintf_lstaddend(t_ftprintf **alst, t_ftprintf *nxt);
void					ftprintf_lstdel(t_ftprintf **alst);
t_ftprintf				*ftprintf_lstnew(char *str, size_t len);
size_t					ftprintf_lstlen(t_ftprintf *list);
int						ftprintf_lstprint(void **fd, t_ftprintf *lst);
int						ftprintf_lstsprint(void **fd, t_ftprintf *lst);
int						ftprintf_lstfprint(void **fd, t_ftprintf *lst);

t_ftprintf_flags		*ftprintf_parse(char *arg);

int						ftprintf_is_conv(const char c);
int						ftprintf_is_size(const char c);
int						ftprintf_is_flag(const char c);
int						ftprintf_is_valid(const char c);

//A REPRENDRE ICI
char					*ft_strchr(const char *s, int c);
char					*ft_strdup(const char *src);
char					*ft_strcut(const char *s, size_t i);
size_t					ft_strlen(const char *s);
int						ft_strisdigit(char *str);
char					*ft_strsub(const char *s, unsigned int start, size_t len);
char					*ft_strjoin_len(const char *s1, const char *s2, int len);
char					*ft_strjoin_free_len(char *s1, char *s2, int len);
char					*ft_strnew(size_t size);

char					*ft_itoa(long long int n);
char					*ft_ftoa(long double n, int dec);
char					*ft_itoa_base_unsigned(uintmax_t n, int base, int maj);
int						ft_isdigit(int c);
int						ft_isinstr(char *str, char c);
char					*ft_strnjoin(char *s1, char *s2, int n);

void					ft_bzero(void *s, size_t n);
void					*ft_memalloc(size_t size);
void					*ft_tabset(size_t len);
void					ft_memdel(void **ap);


t_ftprintf					*handle(char **str, va_list args, int i);
t_ftprintf					*select_conv(t_ftprintf_flags *spec, va_list args);
t_ftprintf					*ftprintf_handle_percent(t_ftprintf_flags *spec, va_list args);
t_ftprintf					*ftprintf_handle_char(t_ftprintf_flags *spec, va_list args);
t_ftprintf					*ftprintf_handle_str(t_ftprintf_flags *spec, va_list args);
t_ftprintf					*ftprintf_handle_p(t_ftprintf_flags *spec, va_list args);
t_ftprintf					*ftprintf_handle_signed_int(t_ftprintf_flags *spec,
						va_list args);
t_ftprintf					*ftprintf_handle_unsigned_int(t_ftprintf_flags *spec,
						va_list args);
t_ftprintf					*ftprintf_handle_hex(t_ftprintf_flags *spec, va_list args);
t_ftprintf					*ftprintf_handle_oct(t_ftprintf_flags *spec, va_list args);
t_ftprintf					*ftprintf_handle_float(t_ftprintf_flags *spec, va_list args);
t_ftprintf					*zeroprec(t_ftprintf_flags *spec);
void					ft_printf_utils_norme(char **rst, int *i, char *tmp);


int						ft_printf(const char *format, ...);
int						ft_dprintf(int fd, const char *format, ...);
int						ft_sprintf(char **str, const char *format, ...);
int						ft_fprintf(char *str, const char *format, ...);
int						ft_inner_printf(int (*f)(void**, t_ftprintf*), void **fd,
						va_list args, const char *format);

#endif
