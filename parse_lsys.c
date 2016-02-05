/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_lsys.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/05 01:31:04 by nbouteme          #+#    #+#             */
/*   Updated: 2016/02/05 02:12:06 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fracts.h"

static int	is_symbol(char c)
{
	return (ft_isupper(c) || c == '-' || c == '+');
}

t_lrule		*parse_rule(char **file)
{
	t_lrule *r;

	r = malloc(sizeof(*r));
	if (!is_symbol(*file[0]))
		assert(0);
	if (1[*file] != '=')
		assert(0);
	r->symbol = *file[0];
	*file += 2;
	r->expansion = parse_axiom(file);
	*file -= 2;
	return (r);
}

char		*parse_axiom(char **file)
{
	char *s;

	s = *file;
	while (*s)
		if (!is_symbol(*s))
			assert(0);
		else
			++s;
	return (ft_strdup(*file));
}

float		parse_angle(char **file)
{
	char *s;

	s = *file;
	while (*s)
		if (!ft_isdigit(*s))
			assert(0);
		else
			++s;
	return ((float)ft_atoi(*file) * (M_PI / 180.0));
}

/*
** file	   := Axiome <sep> Angle <Sep> Regle [Regles...]
** Axiome  := Symbole [Symboles...]
** Angle   := Entier en degres
** Regle   := Symbole = Symbole [Symboles...]
** Symbole := x -> (is_upper(x) || x == '-' || x == '+') == true
** sep	   := '\n'
*/

t_lsys		*parse_lsys(char **file)
{
	t_lsys *ret;

	ret = new_system();
	ret->axiom = parse_axiom(file++);
	ret->angle = parse_angle(file++);
	add_ruledir(ret, parse_rule(file++));
	while (*file)
		add_ruledir(ret, parse_rule(file++));
	return (ret);
}
