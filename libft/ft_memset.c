/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabbadi <mabbadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 13:23:31 by mabbadi           #+#    #+#             */
/*   Updated: 2023/04/14 17:09:48 by mabbadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *dest, int c, size_t count)
{
	int		i;

	if (!dest)
		return (NULL);
	i = 0;
	while (count != 0)
	{
		*((unsigned char *)dest + i) = c;
		i++;
		count --;
	}
	return (dest);
}
