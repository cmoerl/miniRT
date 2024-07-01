/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csturm <csturm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 17:03:05 by csturm            #+#    #+#             */
/*   Updated: 2024/07/01 09:59:16 by csturm           ###   ########.fr       */
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

void    put_pixel(int x, int y, t_color color)
{
    // set the color of the pixel at the given coordinates
    // use the mlx_pixel_put function
}

void    render_scene(t_scene scene)
{
    int x;
    int y;
    t_vector ray;
    t_color color;

    x = 0;
    y = 0;
    while (y < scene.height)
    {
        while (x < scene.width)
        {
            ray = get_ray(scene, x, y);
            color = trace_ray(scene, ray);
            put_pixel(x, y, color);
            x++;
        }
        y++;
    }
    mlx_put_image_to_window(scene.mlx_ptr, scene.win_ptr, scene.img->img_ptr, 0, 0);
}