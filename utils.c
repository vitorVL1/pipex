/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima <vlima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 14:15:58 by vlima             #+#    #+#             */
/*   Updated: 2023/04/14 11:02:06 by vlima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	word_count(const char *str, char c)
{
	int	words;
	int	separator;

	words = 0;
	separator = 0;
	while (*str)
	{
		if (*str != c && separator == 0)
		{
			separator = 1;
			words++;
		}
		else if (*str == c)
			separator = 0;
		str++;
	}
	return (words);
}

static char	*word_dup(const char *s, int start, int end)
{
	char	*word;
	size_t	i;

	i = 0;
	word = malloc((end - start + 1) * sizeof(char));
	while (start < end)
		word[i++] = s[start++];
	word[i] = '\0';
	return (word);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	j;
	int		index;
	char	**split;

	index = -1;
	i = 0;
	j = 0;
	split = malloc((word_count(s, c) + 1) * sizeof(char *));
	if (!split || !s)
		return (0);
	while (i <= ft_strlen(s))
	{
		if (s[i] != c && index < 0)
			index = i;
		else if ((s[i] == c || i == ft_strlen(s)) && index >= 0)
		{
			split[j++] = word_dup(s, index, i);
			index = -1;
		}
		i++;
	}
	split[j] = 0;
	return (split);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*str;

	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	j = 0;
	i = 0;
	if (!str)
		return (NULL);
	while (s1[i] != '\0')
	{
		str[j] = s1[i];
		i++;
		j++;
	}
	i = 0;
	while (s2[i] != '\0')
	{
		str[j] = s2[i];
		i++;
		j++;
	}
	str[j] = '\0';
	return (str);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*str;

	i = 0;
	if (!s)
		return (NULL);
	if (start > ft_strlen(s) || len == 0)
	{
		str = malloc(1);
		*str = '\0';
		return (str);
	}
	if (ft_strlen(s) - start >= len)
		str = (char *)malloc(sizeof(char) * (len + 1));
	else
		str = (char *)malloc(sizeof(char) * (ft_strlen(s) - start + 1));
	if (!str)
		return (0);
	while (s[start] && i < len && start < ft_strlen(s))
	{
		str[i] = s[start++];
		i++;
	}
	str[i] = '\0';
	return (str);
}
