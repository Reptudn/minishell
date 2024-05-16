/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_garbage_collector.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:11:49 by jkauker           #+#    #+#             */
/*   Updated: 2024/05/16 11:55:42 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "./libft.h"

#define GARBAGE_COL_SIZE 50
#define GARBAGE_ERROR_EXPAND -2
#define GARBAGE_ERROR_CREATE -1
#define GARBAGE_SUCCESS 0

static int	*garbage_col_count(void)
{
	static int	count = 0;

	return (&count);
}

static int	*garbage_col_size(void)
{
	static int	count = GARBAGE_COL_SIZE;

	return (&count);
}

static void	***garbage_col_get(void)
{
	static void	**garbage = NULL;

	return (&garbage);
}

static int	ft_garbage_col_create(void)
{
	void	***garbage;

	garbage = garbage_col_get();
	if (*garbage)
		return (1);
	*garbage_col_count() = 0;
	*garbage = malloc(sizeof(void *) * GARBAGE_COL_SIZE);
	if (!*(garbage))
		return (0);
	return (1);
}

// returns 0 on success and otherwise the number of elements that were able to be added
// returns -1 when the garbage collector has not been created
// retuen -2 when the garbage collector is full and could not be realloced
static int	ft_garbage_col_add(void *ptr)
{
	void	***garbage;
	void	**new_garbage;
	int		*count;

	garbage = garbage_col_get();
	if (!*garbage && !ft_garbage_col_create())
		return (GARBAGE_ERROR_CREATE);
	count = garbage_col_count();
	if (*count >= *garbage_col_size())
	{
		new_garbage = malloc(sizeof(void *) * (*garbage_col_size() * 2));
		if (!new_garbage)
			return (GARBAGE_ERROR_EXPAND);
		ft_memcpy(new_garbage, *garbage, sizeof(void *)
			* (*garbage_col_count()));
		free(*garbage);
		*garbage = new_garbage;
		*garbage_col_size() *= 2;
	}
	(*garbage)[(*count)++] = ptr;
	return (GARBAGE_SUCCESS);
}

static void	ft_garbage_col_clear(void)
{
	void	***garbage;
	int		*count;
	int		i;

	garbage = garbage_col_get();
	if (!*garbage)
		return ;
	count = garbage_col_count();
	i = 0;
	while (i < *count)
	{
		free((*garbage)[i]);
		(*garbage)[i] = NULL; 
		i++;
	}
	free(*garbage);
	*garbage = NULL;
	*count = 0;
}

void	*ft_malloc(size_t size)
{
	void	*ptr;
	int		err;

	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	err = ft_garbage_col_add(ptr);
	if (err == GARBAGE_ERROR_EXPAND)
	{
		ft_garbage_col_clear();
		free(ptr);
		return (NULL);
	}
	else if (err == GARBAGE_ERROR_CREATE)
	{
		free(ptr);
		return (NULL);
	}
	return (ptr);
}

void	ft_free_all(void)
{
	ft_garbage_col_clear();
}

void	ft_free(void *ptr)
{
	void	***garbage;
	int		i;
	int		j;

	i = -1;
	if (ptr == NULL)
		return ;
	garbage = garbage_col_get();
	while (++i < *garbage_col_count())
	{
		if ((*garbage)[i] == ptr)
		{
			j = i - 1;
			while (++j < *garbage_col_count() - 1)
				(*garbage)[j] = (*garbage)[j + 1];
			(*garbage_col_count())--;
			free(ptr);
			break ;
		}
	}
}
