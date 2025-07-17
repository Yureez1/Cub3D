/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 15:17:45 by leaugust          #+#    #+#             */
/*   Updated: 2025/07/17 12:09:10 by jbanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d_bonus.h"

int	handle_pre_map_line(char *line, int *started)
{
	char	*trimmed;

	trimmed = ft_strtrim(line, " \t\n");
	if (!trimmed)
		return (1);
	if (trimmed[0] == '\0')
		return (free(trimmed), 0);
	if (!ft_strncmp(trimmed, "NO ", 3) || !ft_strncmp(trimmed, "SO ", 3)
		|| !ft_strncmp(trimmed, "WE ", 3) || !ft_strncmp(trimmed, "EA ", 3)
		|| !ft_strncmp(trimmed, "F ", 2) || !ft_strncmp(trimmed, "C ", 2))
		return (free(trimmed), 0);
	if (trimmed[0] == '1' || trimmed[0] == '0' || trimmed[0] == ' '
		|| trimmed[0] == 'N' || trimmed[0] == 'S' || trimmed[0] == 'E'
		|| trimmed[0] == 'W')
	{
		*started = 1;
		return (free(trimmed), 0);
	}
	free(trimmed);
	return (1);
}

int	handle_map_line(char *line, char **temp_map, int *height, int *max_width)
{
	if (line[0] == '\n' || line[0] == '\0')
		return (1);
	if (process_map_line(line, temp_map, height, max_width))
		return (1);
	return (0);
}
