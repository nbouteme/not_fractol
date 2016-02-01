/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 18:41:44 by nbouteme          #+#    #+#             */
/*   Updated: 2016/02/01 02:52:55 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_H
# define MLX_H

# include "gfx.h"
# include "lsys.h"

typedef struct s_graphics	t_graphics;
typedef struct	s_display t_display;

typedef void (*t_drawfun) (t_display *);

typedef void (*t_inputfun) (t_display *);

typedef struct	s_display
{
	void		*conn;
	void		*win;
	t_point		dim;
	t_graphics	*g;
	t_drawfun	paint;
	t_inputfun	input;
	t_lsys		*system;
}				t_display;

void			*mlx_init();
void			*mlx_new_image(void *mlx_ptr, int width, int height);
int				mlx_loop (void *mlx_ptr);
int				mlx_do_sync(void *mlx_ptr);
int				mlx_do_key_autorepeaton(void *mlx_ptr);
int				mlx_do_key_autorepeatoff(void *mlx_ptr);
int				mlx_clear_window(void *mlx_ptr, void *win_ptr);
int				mlx_destroy_image(void *mlx_ptr, void *img_ptr);
int				mlx_destroy_window(void *mlx_ptr, void *win_ptr);
int				mlx_key_hook (void *win_ptr, int (*funct_ptr)(), void *param);
int				mlx_loop_hook (void *mlx_ptr, int (*funct_ptr)(), void *param);
int				mlx_mouse_hook (void *win_ptr, int (*funct_ptr)(), void *param);
unsigned int	mlx_get_color_value(void *mlx_ptr, int color);
int				mlx_hook(void *win_ptr, int x_event, int x_mask,
						int (*funct)(), void *param);
void			*mlx_new_window(void *mlx_ptr, int size_x, int size_y,
								char *title);
int				mlx_pixel_put(void *mlx_ptr, void *win_ptr, int x, int y,
							int color);
char			*mlx_get_data_addr(void *img_ptr, int *bits_per_pixel,
								int *size_line, int *endian);
int				mlx_put_image_to_window(void *mlx_ptr, void *win_ptr,
										void *img_ptr, int x, int y);
int				mlx_expose_hook (void *win_ptr, int (*funct_ptr)(),
								void *param);
int				mlx_string_put(void *mlx_ptr, void *win_ptr, int x, int y,
							int color, char *string);
void			*mlx_xpm_to_image(void *mlx_ptr, char **xpm_data, int *width,
								int *height);
void			*mlx_xpm_file_to_image(void *mlx_ptr, char *filename,
									int *width, int *height);
int				mlx_hook(void *win, int x_event, int x_mask,
						int (*funct)(), void *param);
int				mlx_do_sync(void *xvar);

int				disp_key_released(int key);
int				disp_key_pressed(int key);

t_display		*new_display();
void			run_display(t_display *d);
int				disp_handle_key(t_display *d);
int				is_key_pressed(int key);
void			set_key_handlers(t_display *d);
int				disp_expose(t_display *d);
int				disp_mouse_moved(int x, int y);
t_point			get_mouse_pos();

#endif
