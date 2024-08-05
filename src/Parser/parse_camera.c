/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianfurnica <marianfurnica@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 23:38:31 by marianfurni       #+#    #+#             */
/*   Updated: 2024/08/04 23:39:51 by marianfurni      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

void parse_camera(char *line, t_camera *camera)
{
    int i = 1; // Start after 'C'

    // Skip whitespace
    while (line[i] && (line[i] == ' ' || line[i] == '\t'))
        i++;

    // Parse position
    camera->center.x = ft_atof(&line[i]);
    while (line[i] && (line[i] != ' ' && line[i] != '\t' && line[i] != ','))
        i++;
    if (line[i] == ',') i++;

    camera->center.y = ft_atof(&line[i]);
    while (line[i] && (line[i] != ' ' && line[i] != '\t' && line[i] != ','))
        i++;
    if (line[i] == ',') i++;

    camera->center.z = ft_atof(&line[i]);
    while (line[i] && (line[i] != ' ' && line[i] != '\t'))
        i++;

    // Skip whitespace
    while (line[i] && (line[i] == ' ' || line[i] == '\t'))
        i++;

    // Parse orientation
    camera->orientation.x = ft_atof(&line[i]);
    while (line[i] && (line[i] != ' ' && line[i] != '\t' && line[i] != ','))
        i++;
    if (line[i] == ',') i++;

    camera->orientation.y = ft_atof(&line[i]);
    while (line[i] && (line[i] != ' ' && line[i] != '\t' && line[i] != ','))
        i++;
    if (line[i] == ',') i++;

    camera->orientation.z = ft_atof(&line[i]);
    while (line[i] && (line[i] != ' ' && line[i] != '\t'))
        i++;

    // Skip whitespace
    while (line[i] && (line[i] == ' ' || line[i] == '\t'))
        i++;

    // Parse field of view
    camera->fov = ft_atof(&line[i]);
    if (camera->fov < 0.0 || camera->fov > 180.0)
    {
        error("Camera FOV out of range [0.0, 180.0]", NULL);
    }
}