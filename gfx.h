/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 18:36:55 by nbouteme          #+#    #+#             */
/*   Updated: 2016/01/13 18:41:21 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GFX_H
# define GFX_H

# include <libft/std.h>

# define SIGN(x) ((x > 0) ? 1 : ((x < 0)? -1 : 0))
# define ABS(x) ((x < 0)? -(x) : (x))

typedef struct s_display	t_display;

typedef struct				s_point
{
	int						w;
	int						h;
}							t_point;

typedef struct				s_graphics
{
	void					*int_img;
	int						*fb;
	t_display				*d;
	t_point					dim;
	unsigned				color;
}							t_graphics;

void						draw_point_bare(t_graphics *g, t_point pos);
void						draw_point(t_graphics *g, t_point pos);
t_graphics					*new_graphics(t_display *d);
unsigned					get_pixel(t_graphics *g, t_point pos);
void						present(t_graphics *g);
void						clear_graphics(t_graphics *g);

#endif
