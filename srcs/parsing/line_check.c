/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leaugust <leaugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 15:17:45 by leaugust          #+#    #+#             */
/*   Updated: 2025/07/16 15:48:46 by leaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	handle_pre_map_line(char *line, int *started)
{
	if (line[0] == ' ' || line[0] == '1')
		*started = 1;
	else
		return (free(line), 1);
	return (0);
}

int	handle_map_line(char *line, char **temp_map, int *height, int *max_width)
{
	if (is_line_empty(line))
		return (free(line), 1);
	if (process_map_line(line, temp_map, height, max_width))
		return (free(line), 1);
	return (0);
}
