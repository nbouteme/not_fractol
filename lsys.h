/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lsys.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/31 23:20:18 by nbouteme          #+#    #+#             */
/*   Updated: 2016/02/01 03:34:40 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LSYS_H
# define LSYS_H

# include <libft/std.h>
# include "gfx.h"

typedef struct	s_sizecalc
{
	int			n;
	char		*expr;
	const char	*user;
}				t_sizecalc;

typedef struct	s_drawcall
{
	t_point		from;
	t_point		to;
}				t_drawcall;

typedef struct	s_lsys_res
{
	t_dlisthead	*draw_calls;
	int			a;
	int			b;
	int			c;
	int			d;
}				t_lsys_res;

typedef struct	s_lsys
{
	char		*axiom;
	char		*consts;
	float		angle;
	t_dlisthead	*rules;
	t_point		pos;
}				t_lsys;

typedef struct	s_lrule
{
	char		symbol;
	char		*expansion;
}				t_lrule;

t_lsys			*new_system();
void			set_constant(t_lsys *self, const char *constants);
void			set_axiom(t_lsys *self, const char *axiom);
void			set_angle(t_lsys *self, int angle);
void			add_rule(t_lsys *self, char symbol, const char *rule);
void			add_ruledir(t_lsys *self, t_lrule *r);
char			*get_command_string(t_lsys *self, int it);
t_dlisthead		*make_draw_list(t_lsys *self, char *r);
void			del_system(t_lsys *lsys);
int				find_rule(t_dlist *elem, char *d);
#endif
