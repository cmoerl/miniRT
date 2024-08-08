/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianfurnica <marianfurnica@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 23:38:31 by marianfurni       #+#    #+#             */
/*   Updated: 2024/08/08 16:17:00 by marianfurni      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

#include "../../inc/minirt.h"

void parse_camera(char *line, t_camera *camera)
{
    int i = 0; // Start at the beginning of the line

    // Skip leading whitespace
    while (line[i] && (line[i] == ' ' || line[i] == '\t'))
        i++;

    // Check for 'C' identifier
    if (line[i] != 'C')
    {
        error("Missing 'C' identifier for camera", NULL);
    }
    i++; // Move past 'C'

    // Skip whitespace
    while (line[i] && (line[i] == ' ' || line[i] == '\t'))
        i++;

    // Parse position
    int start = i;
    while (line[i] && (ft_isdigit(line[i]) || line[i] == '.' || line[i] == '-' || line[i] == '+'))
        i++;
    if (start == i)
    {
        error("Invalid character in camera position x value", NULL);
    }
    camera->center.x = ft_atof(&line[start]);

    if (line[i] == ',') i++;
    start = i;
    while (line[i] && (ft_isdigit(line[i]) || line[i] == '.' || line[i] == '-' || line[i] == '+'))
        i++;
    if (start == i)
    {
        error("Invalid character in camera position y value", NULL);
    }
    camera->center.y = ft_atof(&line[start]);

    if (line[i] == ',') i++;
    start = i;
    while (line[i] && (ft_isdigit(line[i]) || line[i] == '.' || line[i] == '-' || line[i] == '+'))
        i++;
    if (start == i)
    {
        error("Invalid character in camera position z value", NULL);
    }
    camera->center.z = ft_atof(&line[start]);

    // Skip whitespace
    while (line[i] && (line[i] == ' ' || line[i] == '\t'))
        i++;

    // Parse orientation
    start = i;
    while (line[i] && (ft_isdigit(line[i]) || line[i] == '.' || line[i] == '-' || line[i] == '+'))
        i++;
    if (start == i)
    {
        error("Invalid character in camera orientation x value", NULL);
    }
    camera->orientation.x = ft_atof(&line[start]);

    if (line[i] == ',') i++;
    start = i;
    while (line[i] && (ft_isdigit(line[i]) || line[i] == '.' || line[i] == '-' || line[i] == '+'))
        i++;
    if (start == i)
    {
        error("Invalid character in camera orientation y value", NULL);
    }
    camera->orientation.y = ft_atof(&line[start]);

    if (line[i] == ',') i++;
    start = i;
    while (line[i] && (ft_isdigit(line[i]) || line[i] == '.' || line[i] == '-' || line[i] == '+'))
        i++;
    if (start == i)
    {
        error("Invalid character in camera orientation z value", NULL);
    }
    camera->orientation.z = ft_atof(&line[start]);

    // Skip whitespace
    while (line[i] && (line[i] == ' ' || line[i] == '\t'))
        i++;

    // Parse field of view
    start = i;
    while (line[i] && (ft_isdigit(line[i]) || line[i] == '.' || line[i] == '-' || line[i] == '+'))
        i++;
    if (start == i)
    {
        error("Invalid character in camera field of view", NULL);
    }
    camera->fov = ft_atof(&line[start]);
    if (camera->fov < 0.0 || camera->fov > 180.0)
    {
        error("Camera FOV out of range [0.0, 180.0]", NULL);
    }

    // Skip any trailing whitespace or newline characters
    while (line[i] && (line[i] == ' ' || line[i] == '\t' || line[i] == '\n'))
        i++;

    // Check if there are any unexpected characters after the expected values
    if (line[i] != '\0')
    {
        error("Invalid character in camera definition", NULL);
    }

    // Print parsed values in a clear format
    printf("Parsed Camera:\n");
    printf("  Position: x=%f, y=%f, z=%f\n", camera->center.x, camera->center.y, camera->center.z);
    printf("  Orientation: x=%f, y=%f, z=%f\n", camera->orientation.x, camera->orientation.y, camera->orientation.z);
    printf("  FOV: %f\n", camera->fov);
}