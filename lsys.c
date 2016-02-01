/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lsys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/31 23:52:55 by nbouteme          #+#    #+#             */
/*   Updated: 2016/01/31 23:55:47 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lsys.h"
#include <stdlib.h>
#include <math.h>

int		expanded_size(t_lsys *self, char *expr)
{
	int		n;
	t_dlist	*tmp;
	t_lrule	*r;

	n = 0;
	while (*expr)
	{
		if ((tmp = ftext_lstfind(self->rules, (void*)find_rule, expr)))
		{
			r = tmp->content;
			n += ft_strlen(r->expansion);
		}
		else
			++n;
		++expr;
	}
	return (n);
}

char	*expand_into(t_lsys *self, char *input, char *out)
{
	int		n;
	t_dlist	*tmp;
	t_lrule	*r;

	n = 0;
	while (*input)
	{
		if ((tmp = ftext_lstfind(self->rules, (void*)find_rule, input)))
		{
			r = tmp->content;
			ft_memcpy(out + n, r->expansion, ft_strlen(r->expansion) + 1);
			n += ft_strlen(r->expansion);
		}
		else
		{
			out[n] = *input;
			++n;
		}
		++input;
	}
	return (out);
}

char	*get_command_string(t_lsys *self, int it)
{
	char	*result;
	char	*tmp;
	int		i;
	int		nsize;

	i = 1;
	result = ft_strdup(self->axiom);
	while (i++ < it)
	{
		nsize = expanded_size(self, result);
		tmp = result;
		result = expand_into(self, result, malloc(nsize + 1));
		free(tmp);
	}
	return (result);
}
