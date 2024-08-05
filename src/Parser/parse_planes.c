/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_planes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianfurnica <marianfurnica@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 08:47:53 by marianfurni       #+#    #+#             */
/*   Updated: 2024/08/05 09:22:36 by marianfurni      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

void parse_plane(char *line, t_plane **planes)
{
    int i = 2; // Start after 'pl'
    t_plane *plane = malloc(sizeof(t_plane));
    if (!plane)
        error("Memory allocation failed", NULL);

    // Skip whitespace
    while (line[i] && (line[i] == ' ' || line[i] == '\t'))
        i++;

    // Parse point
    plane->point.x = ft_atof(&line[i]);
    while (line[i] && (line[i] != ' ' && line[i] != '\t' && line[i] != ','))
        i++;
    if (line[i] == ',') i++;

    plane->point.y = ft_atof(&line[i]);
    while (line[i] && (line[i] != ' ' && line[i] != '\t' && line[i] != ','))
        i++;
    if (line[i] == ',') i++;

    plane->point.z = ft_atof(&line[i]);
    while (line[i] && (line[i] != ' ' && line[i] != '\t'))
        i++;

    // Skip whitespace
    while (line[i] && (line[i] == ' ' || line[i] == '\t'))
        i++;

    // Parse axis
    plane->axis.x = ft_atof(&line[i]);
    while (line[i] && (line[i] != ' ' && line[i] != '\t' && line[i] != ','))
        i++;
    if (line[i] == ',') i++;

    plane->axis.y = ft_atof(&line[i]);
    while (line[i] && (line[i] != ' ' && line[i] != '\t' && line[i] != ','))
        i++;
    if (line[i] == ',') i++;

    plane->axis.z = ft_atof(&line[i]);
    while (line[i] && (line[i] != ' ' && line[i] != '\t'))
        i++;

    // Skip whitespace
    while (line[i] && (line[i] == ' ' || line[i] == '\t'))
        i++;

    // Parse RGB values
    int r = ft_atoi(&line[i]);
    while (line[i] && line[i] != ',')
        i++;
    if (line[i] == ',') i++;

    int g = ft_atoi(&line[i]);
    while (line[i] && line[i] != ',')
        i++;
    if (line[i] == ',') i++;

    int b = ft_atoi(&line[i]);

    // Validate RGB values
    if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
    {
        free(plane);
        error("Plane color values out of range [0, 255]", NULL);
    }
    plane->color.r = r / 255.0;
    plane->color.g = g / 255.0;
    plane->color.b = b / 255.0;

    // Add plane to the linked list of planes
    plane->next = *planes;
    *planes = plane;
}