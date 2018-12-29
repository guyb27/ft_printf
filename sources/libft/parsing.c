/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   specialize.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: qcharpen <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/27 15:09:16 by qcharpen     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/17 14:39:41 by qcharpen    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

static int				ftprintf_mini_atoi(char **arg)
{
	int		rst;

	rst = 0;
	while (ft_isdigit(**arg))
	{
		rst *= 10;
		rst += **arg - '0';
		(*arg)++;
	}
	(*arg)--;
	return (rst);
}

static void				ftprintf_def_flags(char c, t_ftprintf_flags *spec)
{
	if (c == '#')
		spec->flags[HASH] = 1;
	else if (c == '0')
		spec->flags[ZERO] = 1;
	else if (c == '-')
		spec->flags[MINUS] = 1;
	else if (c == '+')
		spec->flags[PLUS] = 1;
	else if (c == ' ')
		spec->flags[SPACE] = 1;
	else if (c == 'L')
		spec->flags[MAJ_L] = 1;
}

static void				ftprintf_set_t_flags(t_ftprintf_flags *spec)
{
	spec->flags[0] = 0;
	spec->flags[1] = 0;
	spec->flags[2] = 0;
	spec->flags[3] = 0;
	spec->flags[4] = 0;
	spec->flags[5] = 0;
	spec->width = -1;
	spec->prec = -1;
	spec->size = 0;
	spec->conv = '0';
}

static void				ftprintf_def_size(char **arg, t_ftprintf_flags *spec)
{
	if (**arg == 'h' && spec->size <= HH)
	{
		spec->size = H;
		if (*(*arg + 1) == 'h')
		{
			(*arg)++;
			spec->size = HH;
		}
	}
	else if (**arg == 'l' && spec->size <= LL)
	{
		spec->size = L;
		if (*(*arg + 1) == 'l')
		{
			(*arg)++;
			spec->size = LL;
		}
	}
	else if (**arg == 'j' && spec->size <= J)
		spec->size = J;
	else if (**arg == 'z')
		spec->size = Z;
}

t_ftprintf_flags		*ftprintf_parse(char *arg)
{
	t_ftprintf_flags		*spec;

	if ((spec = (t_ftprintf_flags*)ft_memalloc(sizeof(*spec))) == NULL)
		return (NULL);
	ftprintf_set_t_flags(spec);
	while (!ftprintf_is_conv(*arg) && (*arg))
	{
		if (ftprintf_is_flag(*arg))
			ftprintf_def_flags(*arg, spec);
		else if (ft_isdigit(*arg))
			spec->width = ftprintf_mini_atoi(&arg);
		else if (*arg == '.')
		{
			arg++;
			spec->prec = 0;
			spec->prec = ftprintf_mini_atoi(&arg);
		}
		else if (ftprintf_is_size(*arg))
			ftprintf_def_size(&arg, spec);
		arg++;
	}
	if (!(*arg))
		return (NULL);
	spec->conv = *arg;
	return (spec);
}
