/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cyllinders.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianfurnica <marianfurnica@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 08:53:37 by marianfurni       #+#    #+#             */
/*   Updated: 2024/08/05 09:04:04 by marianfurni      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

void parse_cylinder(char *line, t_cylinder **cylinders)
{
    int i = 2; // Start after 'cy'
    t_cylinder *cylinder = malloc(sizeof(t_cylinder));
    if (!cylinder)
        error("Memory allocation failed", NULL);

    // Skip whitespace
    while (line[i] && (line[i] == ' ' || line[i] == '\t'))
        i++;

    // Parse center
    cylinder->center.x = ft_atof(&line[i]);
    while (line[i] && (line[i] != ' ' && line[i] != '\t' && line[i] != ','))
        i++;
    if (line[i] == ',') i++;

    cylinder->center.y = ft_atof(&line[i]);
    while (line[i] && (line[i] != ' ' && line[i] != '\t' && line[i] != ','))
        i++;
    if (line[i] == ',') i++;

    cylinder->center.z = ft_atof(&line[i]);
    while (line[i] && (line[i] != ' ' && line[i] != '\t'))
        i++;

    // Skip whitespace
    while (line[i] && (line[i] == ' ' || line[i] == '\t'))
        i++;

    // Parse axis
    cylinder->axis.x = ft_atof(&line[i]);
    while (line[i] && (line[i] != ' ' && line[i] != '\t' && line[i] != ','))
        i++;
    if (line[i] == ',') i++;

    cylinder->axis.y = ft_atof(&line[i]);
    while (line[i] && (line[i] != ' ' && line[i] != '\t' && line[i] != ','))
        i++;
    if (line[i] == ',') i++;

    cylinder->axis.z = ft_atof(&line[i]);
    while (line[i] && (line[i] != ' ' && line[i] != '\t'))
        i++;

    // Skip whitespace
    while (line[i] && (line[i] == ' ' || line[i] == '\t'))
        i++;

    // Parse radius
    cylinder->radius = ft_atof(&line[i]) / 2;
    while (line[i] && (line[i] != ' ' && line[i] != '\t'))
        i++;

    // Skip whitespace
    while (line[i] && (line[i] == ' ' || line[i] == '\t'))
        i++;

    // Parse height
    cylinder->height = ft_atof(&line[i]);
    while (line[i] && (line[i] != ' ' && line[i] != '\t'))
        i++;

    // Skip whitespace
    while (line[i] && (line[i] == ' ' || line[i] == '\t'))
        i++;

    // Parse RGB values
    int r = ft_atoi(&line[i]);
    while (line[i] && line[i] != ',')
        i++;
    if (line[i] == ',')
        i++;

    int g = ft_atoi(&line[i]);
    while (line[i] && line[i] != ',')
        i++;
    if (line[i] == ',')
        i++;

    int b = ft_atoi(&line[i]);

    // Validate RGB values
    if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
    {
        free(cylinder);
        error("Cylinder color values out of range [0, 255]", NULL);
    }
    cylinder->color.r = r / 255.0;
    cylinder->color.g = g / 255.0;
    cylinder->color.b = b / 255.0;

    // Add cylinder to the linked list of cylinders
    cylinder->next = *cylinders;
    *cylinders = cylinder;
}