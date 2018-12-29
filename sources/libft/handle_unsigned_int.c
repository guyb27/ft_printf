/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   handle_int.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: qcharpen <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/22 08:26:31 by qcharpen     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/17 22:36:19 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

t_ftprintf				*zeroprec(t_ftprintf_flags *spec)
{
	char	*rst;
	int		len;
	int		i;

	len = MAX(spec->width, ((ft_isinstr("dDi", spec->conv) &&
			(spec->flags[SPACE] || spec->flags[PLUS])) ||
			(ft_isinstr("oO", spec->conv) && spec->flags[HASH])));
	rst = ft_memalloc(sizeof(*rst) * (len + 1));
	i = 0;
	if (spec->flags[MINUS] &&
			((ft_isinstr("dDi", spec->conv) && spec->flags[PLUS]) ||
			(ft_isinstr("oO", spec->conv && spec->flags[HASH]))))
		rst[i++] = (ft_isinstr("dDi", spec->conv) ? '+' : '0');
	while (i < len - (ft_isinstr("dDoOi", spec->conv) && ((spec->flags[PLUS])
				|| spec->flags[HASH])) && !spec->flags[MINUS])
		rst[i++] = ' ';
	if (i == len - 1)
		rst[i++] = (ft_isinstr("dDi", spec->conv) ? '+' : '0');
	rst[i] = '\0';
	return (ftprintf_lstnew(rst, len));
}

static int			is_space(t_ftprintf_flags *spec, char *tmp, intmax_t len, int i)
{
	if (!spec->flags[ZERO])
		return (i < len - (MAX((int)ft_strlen(tmp),
						spec->prec) + 2 * spec->flags[HASH]));
	else
	{
		if (spec->prec == -1)
			return (0);
		else
		{
			if (spec->prec < spec->width)
				return (i < spec->width - MAX(spec->prec, ft_strlen(tmp))
						- 2 * spec->flags[HASH]);
			else
				return (0);
		}
	}
}

static int			is_zero(t_ftprintf_flags *spec, char *tmp, intmax_t len, int *i)
{
	if (spec->flags[MINUS] && ft_strlen(tmp) < len)
	{
		if (spec->prec > -1)
			return (i[0] < spec->prec - ft_strlen(tmp));
		else
			return (i[0] < spec->flags[HASH]);
	}
	else
		return (i[0] < len - (ft_strlen(tmp) - i[1]));
}

static uintmax_t	get_arg(t_ftprintf_flags *spec, va_list args)
{
	uintmax_t	arg;

	arg = va_arg(args, uintmax_t);
	if (spec->conv == 'U')
		arg = (unsigned long)arg;
	else if (spec->size == HH)
		arg = (unsigned char)arg;
	else if (spec->size == H)
		arg = (unsigned short)arg;
	else if (spec->size == L)
		arg = (unsigned long)arg;
	else if (spec->size == LL)
		arg = (unsigned long long)arg;
	else if (spec->size == J)
		arg = (uintmax_t)arg;
	else if (spec->size == Z)
		arg = (size_t)arg;
	else
		arg = (unsigned int)arg;
	return (arg);
}

t_ftprintf				*ftprintf_handle_unsigned_int(t_ftprintf_flags *spec, va_list args)
{
	char		*rst;
	char		*tmp;
	uintmax_t	arg;
	int			len;
	int			i[2];

	arg = get_arg(spec, args);
	if (spec->prec == 0 && arg == 0)
		return (zeroprec(spec));
	tmp = ft_itoa_base_unsigned((uintmax_t)arg, 10, 0);
	len = MAX((int)ft_strlen(tmp), (MAX(spec->width, spec->prec)));
	rst = ft_memalloc(sizeof(*rst) * (len + 1));
	i[0] = 0;
	i[1] = 0;
	while (is_space(spec, tmp, len, i[0]) && !spec->flags[MINUS])
		rst[(i[0])++] = ' ';
	while (is_zero(spec, tmp, len, i))
		rst[i[0]++] = '0';
	while (tmp[i[1]])
		rst[i[0]++] = tmp[i[1]++];
	while (i[0] < len && spec->flags[MINUS])
		rst[i[0]++] = ' ';
	rst[i[0]] = '\0';
	free(tmp);
	return (ftprintf_lstnew(rst, len));
}
