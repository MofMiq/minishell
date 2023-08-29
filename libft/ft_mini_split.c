/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mini_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 17:13:22 by marirodr          #+#    #+#             */
/*   Updated: 2023/08/29 15:32:47 by marirodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Like ft_split but only with one equal.*/

/*int i;     count 's'
int count; coutn 'words'
int w;     'word' yes(1) or no (0)*/

int	mini_count_word(char const *s, char c)
{
	int	i;
	int	count;
	int	w;
	int	equal;

	i = 0;
	count = 0;
	w = 0;
	equal = 0;
	while (s[i])
	{
		if (s[i] != c && w == 0 && (equal == 0 || equal == 1))
		{
			w = 1;
			count = count + 1;
		}
		else if (s[i] == c)
		{
			w = 0;
			equal++;
		}
		i++;
	}
	return (count);
}

	/*int len; // lenght of 'words'
	int j;   // count of s*/

static int	mini_count_len(char *s, int *i, char c)
{
	int	len;
	int	j;

	len = 0;
	while (s[*i] == c && s[*i])
		*i = *i + 1;
	j = *i;
	while (s[j] && (s[j] != c))
	{
		j++;
		len++;
	}
	return (len);
}

	/*int wordsize; //size of  'word'
	int k;        //count for 'word' (count of **)
	int q;        //count to 'write' 'words' (count of *)
	char *word;   // where 'words' are gonna be allocated*/

static int	mini_w_word(char *s, char **p, int *i, char c)
{
	int		wordsize;
	int		k;
	int		q;
	char	*word;

	wordsize = mini_count_len(s, i, c);
	q = 0;
	while (wordsize != 0)
	{
		word = (char *)ft_calloc(sizeof(char), (wordsize + 1));
		if (!word)
			return (1);
		k = 0;
		while (k < wordsize)
		{
			word[k++] = s[*i];
			*i = *i + 1;
		}
		word[k] = '\0';
		p[q] = word;
		q++;
		wordsize = ft_strlen(&s[*i]);
	}
	p[q] = NULL;
	return (0);
}
	//int i;      //nº od 'words'
	//char **str; //where substr is gonna be allocated.
	//int j;      //count for an error
	//int error;  //if there's an error, free memory

char	**ft_mini_split(char const *s, char c)
{
	int		i;
	char	**str;
	int		j;
	int		error;

	if (!s)
		return (NULL);
	i = mini_count_word(s, c);
	str = (char **)ft_calloc(sizeof(char *), i + 1);
	if (!str)
		return (NULL);
	j = 0;
	error = mini_w_word((char *)s, str, &j, c);
	if (error)
	{
		j = 0;
		while (str[j])
		{
			free(str[j]);
			j++;
		}
		free(str);
		return (NULL);
	}
	return (str);
}

/*void	ft_leaks(void)
{
	system("leaks -q a.out");
}

int	main(void)
{
	atexit(ft_leaks);
	int		i;
	char	*str1;
	char	*str2;
	char	**split1;
	char	**split2;

	i = 0;
	str1 = "PAGER=less";
	str2 = "LS_COLORS=di=1;36:ln=35:so=32:pi=33:ex=31:bd=34;46:cd=34";
	split1 = ft_mini_split(str1, '=');
	split2 = ft_mini_split(str2, '=');
	while (split1[i])
	{
		printf("split1: %s\n", split1[i]);
		i++;
	}
	i = 0;
	while (split2[i])
	{
		printf("split2: %s\n", split2[i]);
		i++;
	}
	ft_free_double_pointer(split1);
	ft_free_double_pointer(split2);
}*/
