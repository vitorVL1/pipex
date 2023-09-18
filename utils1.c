/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima <vlima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 11:01:24 by vlima             #+#    #+#             */
/*   Updated: 2023/06/28 15:40:31 by vlima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	error(char *str)
{
	perror(str);
	exit(1);
}

void	free_all(char **duo_pointer)
{
	int	i;

	i = 0;
	while (duo_pointer[i])
	{
		free(duo_pointer[i]);
		i++;
	}
	free(duo_pointer);
}

char	*ft_strcat(char *dest, const char *src)
{
	char	*ptr;

	ptr = dest;

	while (*ptr)
		ptr++;

	while (*src)
	{
		*ptr = *src;
		ptr++;
		src++;
	}

	*ptr = '\0';

	return (dest);
}
