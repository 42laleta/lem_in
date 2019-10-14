/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmerge.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchanal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/10 17:30:18 by fchanal           #+#    #+#             */
/*   Updated: 2017/01/04 21:20:33 by fchanal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "2libft.h"

char	*ft_strmerge(char *s1, const char *s2, size_t len)
{
	char		*fresh;
	const char	*init;
	const char	*init2;

	if (!(fresh = (char*)malloc(sizeof(*fresh) * len + 1)))
		return (NULL);
	init = fresh;
	if (s1)
	{
		init2 = s1;
		while (len && (*fresh = *s1))
		{
			++fresh;
			++s1;
			--len;
		}
		free((char*)init2);
	}
	while (len && (*fresh++ = *s2++))
		--len;
	if (!len)
		*fresh = '\0';
	return ((char*)init);
}
