/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabbadi <mabbadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 15:21:55 by mabbadi           #+#    #+#             */
/*   Updated: 2023/04/14 17:12:53 by mabbadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*ptr;
	size_t	s1len;

	if (!s1)
		return (NULL);
	s1len = ft_strlen(s1);
	ptr = ft_calloc(s1len + 1, sizeof(char));
	if (ptr != NULL)
		ft_strlcpy(ptr, s1, s1len + 1);
	return (ptr);
}
