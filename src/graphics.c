/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csturm <csturm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 12:25:37 by csturm            #+#    #+#             */
/*   Updated: 2024/07/03 12:30:22 by csturm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

void    decrease_resolution(t_scene *scene)
{
    scene->width /= 2;
    scene->height /= 2;
    scene->img = mlx_new_image(scene->mlx_ptr, scene->width, scene->height);
    scene->img->img_ptr = (int *)mlx_get_data_addr(scene->img, &scene->img->bits_per_pixel, &scene->img->line_length, &scene->img->endian);
    render_scene(*scene);
}

void    increase_resolution(t_scene *scene)
{
    scene->width *= 2;
    scene->height *= 2;
    scene->img = mlx_new_image(scene->mlx_ptr, scene->width, scene->height);
    scene->img->img_ptr = (int *)mlx_get_data_addr(scene->img, &scene->img->bits_per_pixel, &scene->img->line_length, &scene->img->endian);
    render_scene(*scene);
}
