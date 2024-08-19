/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinders.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 08:53:37 by marianfurni       #+#    #+#             */
/*   Updated: 2024/08/19 11:31:10 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

void parse_cylinder(char *line, t_cylinder **cylinders)
{
    int i = 0; // Start at the beginning of the line

    // Skip leading whitespace
    while (line[i] && (line[i] == ' ' || line[i] == '\t'))
        i++;

    // Check for 'cy' identifier
    if (line[i] != 'c' || line[i + 1] != 'y') {
        error("Missing 'cy' identifier for cylinder", NULL);
    }
    i += 2; // Move past 'cy'

    // Skip whitespace
    while (line[i] && (line[i] == ' ' || line[i] == '\t'))
        i++;

    // Parse center
    t_cylinder *cylinder = malloc(sizeof(t_cylinder));
    if (!cylinder)
        error("Memory allocation failed", NULL);

    // Parse X coordinate of the center
    int start = i;
    while (line[i] && (ft_isdigit(line[i]) || line[i] == '.' || line[i] == '-' || line[i] == '+'))
        i++;
    if (start == i) {
        error("Invalid character in cylinder definition", NULL);
    }
    cylinder->center.x = ft_atof(&line[start]);

    if (line[i] == ',') i++;
    // Parse Y coordinate of the center
    start = i;
    while (line[i] && (ft_isdigit(line[i]) || line[i] == '.' || line[i] == '-' || line[i] == '+'))
        i++;
    if (start == i) {
        error("Invalid character in cylinder definition", NULL);
    }
    cylinder->center.y = ft_atof(&line[start]);

    if (line[i] == ',') i++;
    // Parse Z coordinate of the center
    start = i;
    while (line[i] && (ft_isdigit(line[i]) || line[i] == '.' || line[i] == '-' || line[i] == '+'))
        i++;
    if (start == i) {
        error("Invalid character in cylinder definition", NULL);
    }
    cylinder->center.z = ft_atof(&line[start]);

    // Skip whitespace
    while (line[i] && (line[i] == ' ' || line[i] == '\t'))
        i++;

    // Parse axis
    start = i;
    while (line[i] && (ft_isdigit(line[i]) || line[i] == '.' || line[i] == '-' || line[i] == '+'))
        i++;
    if (start == i) {
        error("Invalid character in cylinder definition", NULL);
    }
    cylinder->axis.x = ft_atof(&line[start]);

    if (line[i] == ',') i++;
    start = i;
    while (line[i] && (ft_isdigit(line[i]) || line[i] == '.' || line[i] == '-' || line[i] == '+'))
        i++;
    if (start == i) {
        error("Invalid character in cylinder definition", NULL);
    }
    cylinder->axis.y = ft_atof(&line[start]);

    if (line[i] == ',') i++;
    start = i;
    while (line[i] && (ft_isdigit(line[i]) || line[i] == '.' || line[i] == '-' || line[i] == '+'))
        i++;
    if (start == i) {
        error("Invalid character in cylinder definition", NULL);
    }
    cylinder->axis.z = ft_atof(&line[start]);

    // Skip whitespace
    while (line[i] && (line[i] == ' ' || line[i] == '\t'))
        i++;

    // Parse radius
    start = i;
    while (line[i] && (ft_isdigit(line[i]) || line[i] == '.' || line[i] == '-' || line[i] == '+'))
        i++;
    if (start == i) {
        error("Invalid character in cylinder definition", NULL);
    }
    cylinder->radius = ft_atof(&line[start]) / 2;
    if (cylinder->radius <= 0) {
        error("Cylinder radius must be positive", NULL);
    }

    // Skip whitespace
    while (line[i] && (line[i] == ' ' || line[i] == '\t'))
        i++;

    // Parse height
    start = i;
    while (line[i] && (ft_isdigit(line[i]) || line[i] == '.' || line[i] == '-' || line[i] == '+'))
        i++;
    if (start == i) {
        error("Invalid character in cylinder definition", NULL);
    }
    cylinder->height = ft_atof(&line[start]);
    if (cylinder->height <= 0) {
        error("Cylinder height must be positive", NULL);
    }

    // Skip whitespace
    while (line[i] && (line[i] == ' ' || line[i] == '\t'))
        i++;

    // Parse RGB values
    start = i;
    while (line[i] && ft_isdigit(line[i]))
        i++;
    if (start == i) {
        error("Invalid character in cylinder definition", NULL);
    }
    int r = ft_atoi(&line[start]);

    if (line[i] == ',') i++;
    start = i;
    while (line[i] && ft_isdigit(line[i]))
        i++;
    if (start == i) {
        error("Invalid character in cylinder definition", NULL);
    }
    int g = ft_atoi(&line[start]);

    if (line[i] == ',') i++;
    start = i;
    while (line[i] && ft_isdigit(line[i]))
        i++;
    if (start == i) {
        error("Invalid character in cylinder definition", NULL);
    }
    int b = ft_atoi(&line[start]);

    // Validate RGB values
    if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255) {
        free(cylinder);
        error("Cylinder color values out of range [0, 255]", NULL);
    }
    cylinder->color.r = r / 255.0;
    cylinder->color.g = g / 255.0;
    cylinder->color.b = b / 255.0;

    // Skip any trailing whitespace or newline characters
    while (line[i] && (line[i] == ' ' || line[i] == '\t' || line[i] == '\n'))
        i++;

    // Check if there are any unexpected characters after the expected values
    if (line[i] != '\0') {
        free(cylinder);
        error("Invalid character in cylinder definition", NULL);
    }

    // Add cylinder to the linked list of cylinders
    cylinder->next = *cylinders;
    *cylinders = cylinder;
}
