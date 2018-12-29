/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   handle_int.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: qcharpen <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/22 08:26:31 by qcharpen     #+#   ##    ##    #+#       */
/*   Updated: 2018/12/12 07:17:56 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

static int			mallsize(t_ftprintf_flags *spec, intmax_t i)
{
	int		rst;

	rst = 1;
	if (i < 0 || spec->flags[PLUS] || spec->flags[SPACE])
	{
		if (spec->prec > -1)
			spec->prec++;
		rst++;
	}
	while (i <= -10 || i >= 10)
	{
		i /= 10;
		rst++;
	}
	rst = MAX(rst, MAX(spec->width, spec->prec));
	return (rst);
}

static int			is_space(t_ftprintf_flags *spec, char *tmp, intmax_t len, int i)
{
	if (spec->flags[MINUS] && !(spec->flags[SPACE] && i == 0))
		return (0);
	if (spec->flags[SPACE] && (tmp[0] == '-' || spec->flags[PLUS]))
		spec->flags[SPACE] = 0;
	if (spec->flags[SPACE] && i == 0 && tmp[0] != '-')
		return (1);
	if (!spec->flags[ZERO])
		return (i < len - (MAX((int)(ft_strlen(tmp) + spec->flags[PLUS]),
						spec->prec - spec->flags[SPACE])));
	else
	{
		if (spec->prec == -1)
			return (0);
		else
		{
			if (spec->prec < spec->width)
				return (i < spec->width - MAX(spec->prec, ft_strlen(tmp))
						+ spec->flags[SPACE]);
			else
				return (0);
		}
	}
}

static int			is_zero(t_ftprintf_flags *spec, char *tmp, intmax_t len, int *i)
{
	if (spec->flags[MINUS] && ft_strlen(tmp) < spec->prec)
	{
		if (spec->prec > -1)
			return (i[0] - (tmp[0] == '-') < spec->prec - ft_strlen(tmp));
		else
			return (0);
	}
	else
		return (i[0] < len - (ft_strlen(tmp) - i[1]));
}

static intmax_t		get_arg(t_ftprintf_flags *spec, va_list args)
{
	intmax_t	arg;

	arg = va_arg(args, intmax_t);
	if (spec->conv == 'D')
		arg = (long int)arg;
	else if (spec->size == HH)
		arg = (char)arg;
	else if (spec->size == H)
		arg = (short int)arg;
	else if (spec->size == L)
		arg = (long int)arg;
	else if (spec->size == LL)
		arg = (long long int)arg;
	else if (spec->size == J)
		arg = (intmax_t)arg;
	else if (spec->size == Z)
		arg = (size_t)arg;
	else
		arg = (int)arg;
	return (arg);
}

t_ftprintf				*ftprintf_handle_signed_int(t_ftprintf_flags *spec, va_list args)
{
	char		*rst;
	char		*tmp;
	intmax_t	arg;
	int			len;
	int			*i;

	arg = get_arg(spec, args);
	if (spec->prec == 0 && arg == 0)
		return (zeroprec(spec));
	tmp = ft_itoa(arg);
	len = mallsize(spec, arg);
	rst = ft_memalloc(sizeof(*rst) * (len + 1));
	i = ft_tabset(2);
	while (is_space(spec, tmp, len, i[0]))
		rst[(i[0])++] = ' ';
	if (tmp[i[1]] == '-' || spec->flags[PLUS])
		rst[i[0]++] = (tmp[i[1]] == '-' ? tmp[i[1]++] : '+');
	while (is_zero(spec, tmp, len, i))
		rst[i[0]++] = '0';
	while (tmp[i[1]])
		rst[i[0]++] = tmp[i[1]++];
	while (i[0] < len && spec->flags[MINUS])
		rst[i[0]++] = ' ';
	ft_printf_utils_norme(&rst, i, tmp);
	return (ftprintf_lstnew(rst, len));
}
