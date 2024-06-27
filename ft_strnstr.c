/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabbadi <mabbadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 17:56:32 by mabbadi           #+#    #+#             */
/*   Updated: 2024/04/22 16:19:27 by mabbadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	needle_len;

	needle_len = ft_strlen(needle);
	if (!haystack)
		return (NULL);
	if (*needle == '\0')
		return ((char *)haystack);
	while (*haystack != '\0' && len >= needle_len)
	{
		if (*haystack == *needle && !adv_strncmp(haystack, needle))
			return ((char *)haystack);
		haystack++;
	}
	return (NULL);
}
