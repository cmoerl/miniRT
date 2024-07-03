/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csturm <csturm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 17:03:05 by csturm            #+#    #+#             */
/*   Updated: 2024/07/03 10:36:10 by csturm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

/*
- take a t_scene struct
- iterate over the screen pixels
- get the ray for each pixel
- trace the ray and get the color
- put the color on the screen
- repeat until all pixels are colored
- show the image 
*/

void    put_pixel(int x, int y, t_color color, t_scene scene)
{
    int	position;

    // should be handled in initialisation:
    // if (scene.img == NULL)
    //     error("Image not initialised", &scene);
    // if (x < 0 || y < 0 || x >= scene.width || y >= scene.height)
    //     error("Pixel out of bounds", &scene);
	position = y * scene.img->line_length + x * (scene.img->bits_per_pixel / 8);
	*(unsigned int *)(scene.img->pxl + position) = (int)(color.r * 255) << 16 | (int)(color.g * 255) << 8 | (int)(color.b * 255);
}

void    render_scene(t_scene scene)
{
    int x;
    int y;
    t_ray ray;
    t_color color;

    x = 0;
    y = 0;
    // should be handled in initialisation:
    // if (scene.img == NULL)
    //     error("Image not initialised", &scene);
    // if (scene.width <= 0 || scene.height <= 0)
    //     error("Invalid resolution", &scene);
    while (y < scene.height)
    {
        while (x < scene.width)
        {
            ray = get_ray(scene, x, y);
            color = trace_ray(scene, ray);
            put_pixel(x, y, color, scene);
            x++;
        }
        y++;
    }
    mlx_put_image_to_window(scene.mlx_ptr, scene.win_ptr, scene.img->img_ptr, 0, 0);
}
