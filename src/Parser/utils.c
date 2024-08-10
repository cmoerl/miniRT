/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianfurnica <marianfurnica@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 17:19:53 by marianfurni       #+#    #+#             */
/*   Updated: 2024/08/10 17:20:32 by marianfurni      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"


void skip_whitespace(char *line, int *i) {
    while (line[*i] && (line[*i] == ' ' || line[*i] == '\t')) {
        (*i)++;
    }
}

float parse_float(char *line, int *i) {
    int start = *i;
    while (line[*i] && (ft_isdigit(line[*i]) || line[*i] == '.' || line[*i] == '-' || line[*i] == '+')) {
        (*i)++;
    }
    if (start == *i) {
        error("Invalid character in input", NULL);
    }
    return ft_atof(&line[start]);
}

int parse_color_component(char *line, int *i) {
    int start = *i;
    while (line[*i] && ft_isdigit(line[*i])) {
        (*i)++;
    }
    if (start == *i) {
        error("Invalid character in input", NULL);
    }
    return ft_atoi(&line[start]);
}