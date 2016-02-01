/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lsys_access.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/31 23:55:19 by nbouteme          #+#    #+#             */
/*   Updated: 2016/02/01 03:36:24 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lsys.h"
#include <stdlib.h>

void	set_constant(t_lsys *self, const char *constants)
{
	self->consts = ft_strdup(constants);
}

void	set_axiom(t_lsys *self, const char *axiom)
{
	self->axiom = ft_strdup(axiom);
}

int		find_rule(t_dlist *elem, char *d)
{
	t_lrule *r;

	r = elem->content;
	return (r->symbol == *d);
}

void	add_rule(t_lsys *self, char symbol, const char *rule)
{
	t_lrule *r;

	r = malloc(sizeof(*r));
	*r = (t_lrule) { symbol, ft_strdup(rule) };
	add_ruledir(self, r);
}

void	add_ruledir(t_lsys *self, t_lrule *r)
{
	if (!ftext_lstfind(self->rules, (void*)&find_rule, &r->symbol))
		ftext_lstpush_back(self->rules, ftext_lstnewelemown(r, sizeof(*r)));
}
