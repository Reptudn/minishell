#include "../../lib/libft/libft.h"
#include "../../include/minishell.h"

void	copy(char **result, int start, int i, int signs)
{
	if (signs == 2)
	{

	}
	else if (signs == 1)
	{

	}
	else
	{

	}
}

char **ft_split_shell(const char *str)
{
	char **result = malloc((ft_strlen(str) + 1) * sizeof(char *));
	int i = 0;
	int start = 0;
	char *temp;

	//solange string ncoh nicht am end
	while(str[i] != 0)
	{
		//solange wir auf kein Shell_Operator stossen einfach weiter
		if (str[i] != '>' && str[i] != '<' && str[i] != '|' && str[i] != '&')
		{
			i++;
			continue;
		}
		//wir sind auf ein Shell_Operator gestossen, 
		else
		{
			temp[0] = str[i];
			temp[1] = str[i + 1];
			temp[2] = '\0';
			if (ft_strncmp(temp, ">>", 2) == 0 || ft_strncmp(temp, "<<", 2) == 0 || ft_strncmp(temp, "||", 2) == 0 || ft_strncmp (temp, "&&", 2) == 0)
			{
				copy(result, start, i, 2);
				start += i + 2;
			}
			else if (ft_strncmp(temp, ">", 1) == 0 || ft_strncmp(temp, "<", 1) == 0)
			{
				copy(result, start, i, 1);
				start += i + 1;
			}
		}
	}
	return (result);
}


int main() {
	char **result;
	char *str = "echo \"hel<lo\" || wc || ls || ls -la";
	int i = 0;

	result = ft_split_shell(str);
	while (result[i] != NULL) {
		printf("%s\n", result[i]);
		free(result[i]);
		i++;
	}
	free(result);

	return 0;
}