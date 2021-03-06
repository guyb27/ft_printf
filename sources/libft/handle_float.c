/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   handle_float.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: qcharpen <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/28 12:27:47 by qcharpen     #+#   ##    ##    #+#       */
/*   Updated: 2018/12/15 01:33:15 by qcharpen    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

static int				mallsize(t_ftprintf_flags *spec, long double i)
{
	int		rst;

	rst = 1;
	if (i < 0 || spec->flags[PLUS] || spec->flags[SPACE])
		rst++;
	while (i <= -10 || i >= 10)
	{
		i /= 10;
		rst++;
	}
	if (spec->prec > 0)
		rst += spec->prec + 1;
	rst = MAX(rst, spec->width);
	return (rst);
}

static int				is_space(t_ftprintf_flags *spec, char *tmp, intmax_t len, int i)
{
	if (spec->flags[MINUS])
		return (0);
	return (!spec->flags[ZERO] && i < len - ft_strlen(tmp));
}

static int				is_zero(t_ftprintf_flags *spec, char *tmp, intmax_t len, int i)
{
	if (spec->flags[MINUS])
		return (0);
	return (i < len - ft_strlen(tmp));
}

static long double		get_arg(t_ftprintf_flags *spec, va_list args)
{
	long double	arg;

	if (spec->flags[MAJ_L])
		arg = va_arg(args, long double);
	else
		arg = va_arg(args, double);
	if (spec->prec == -1)
		spec->prec = 6;
	return (arg);
}

t_ftprintf					*ftprintf_handle_float(t_ftprintf_flags *spec, va_list args)
{
	char		*rst;
	char		*tmp;
	long double	arg;
	int			len;
	int			*i;

	arg = get_arg(spec, args);
	tmp = ft_ftoa(arg, spec->prec);
	len = mallsize(spec, arg);
	rst = ft_memalloc(sizeof(*rst) * (len + 1));
	i = ft_tabset(2);
	while (is_space(spec, tmp, len, i[0]))
		rst[(i[0])++] = ' ';
	if (tmp[i[1]] == '-' || spec->flags[PLUS])
		rst[i[0]++] = (tmp[i[1]] == '-' ? tmp[i[1]++] : '+');
	while (is_zero(spec, tmp, len, i[0]))
		rst[i[0]++] = '0';
	while (tmp[i[1]])
		rst[i[0]++] = tmp[i[1]++];
	while (i[0] < len && spec->flags[MINUS])
		rst[i[0]++] = ' ';
	rst[i[0]] = '\0';
	free(tmp);
	return (ftprintf_lstnew(rst, len));
}
