/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fracts.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/05 01:28:19 by nbouteme          #+#    #+#             */
/*   Updated: 2016/03/24 02:25:01 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTS_H
# define FRACTS_H

# include "gfx.h"
# include "mlx.h"
# include <complex.h>
# include "vmath.h"
# include <unistd.h>
# define COMPLEX float complex
# define B_SIZE 256
# undef assert

typedef struct	s_fracparams
{
	float		ix;
	float		iy;
}				t_fracparams;

typedef struct	s_mandel_param
{
	int				id;
	t_display		*d;
	t_fracparams	params;
}				t_mandel_param;

typedef void	(*t_dfrac)(struct s_display *, t_fracparams);

t_lsys			*parse_lsys(char **file);
void			mandel(t_display *d, t_fracparams params);
void			bato(t_display *d, t_fracparams params);
void			julia(t_display *d, t_fracparams params);
void			custom(t_display *d, t_fracparams params);
int				i_to_rgb(int x);
void			print_help(void);
int				contains(const char *rhs, char **args);
char			*readfile(int fd, int (*check)(char *));
int				check_input(char *s);
void			draw_fractal(t_display *d);
char			*parse_axiom(char **file);
void			assert(int b);

#endif
