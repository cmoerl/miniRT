/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 17:03:05 by csturm            #+#    #+#             */
/*   Updated: 2024/08/28 12:02:31 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

// putting the pixel on the screen
void	put_pixel(int x, int y, t_color color, t_scene scene)
{
	int	position;

	position = y * scene.img->line_length + x * (scene.img->bits_per_pixel / 8);
	*(unsigned int *)(scene.img->pxl + position)
		= (int)(color.r) << 16 | (int)(color.g) << 8 | (int)(color.b);
}

// initialising the ray
// interating over each pixel
// getting the ray for each pixel
// tracing the ray
// putting the color on the screen
// showing the image
void	render_scene(t_scene scene)
{
	t_ray	ray;
	t_color	color;
	int		x;
	int		y;

	x = 0;
	y = 0;
	ray = (t_ray){(t_vector){0, 0, 0}, (t_vector){0, 0, 0}};
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			ray = get_ray(scene, x, y);
			color = trace_ray(scene, ray);
			put_pixel(x, y, color, scene);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(scene.mlx_ptr,
		scene.win_ptr, scene.img->img_ptr, 0, 0);
}
