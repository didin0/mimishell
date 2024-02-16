/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabbadi <mabbadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 17:03:38 by mabbadi           #+#    #+#             */
/*   Updated: 2023/10/13 15:19:29 by mabbadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	j;
	size_t	i;
	size_t	srclen;
	size_t	dstlen;

	j = 0;
	srclen = ft_strlen(src);
	if (!dst)
		return (srclen);
	dstlen = ft_strlen(dst);
	i = dstlen;
	if (dstsize == 0)
		return (srclen);
	if (dstsize < dstlen)
		return (srclen + dstsize);
	while (src[j] && (dstlen + j) < dstsize)
		dst[i++] = src[j++];
	if ((dstlen + j) == dstsize && dstlen < dstsize)
		dst[--i] = '\0';
	else
		dst[i] = '\0';
	return (srclen + dstlen);
}
