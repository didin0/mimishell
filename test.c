// #include "minishell.h"

// int	is_token(char c)
// {
// 	return (c == '|' || c == '<' || c == '>' || c == '\0');
// }

// void add_substr_to_list(char *buff, char *line, int i, int ibis)
// {
//     buff = ft_substr(line, ibis, i - ibis);
// 	printf("buff : %s\n", buff);
// 	free(buff);
// }

// int	main(void)
// {
// 	int		i;
// 	int		ibis;
// 	char	*buff;
// 	char	*line;

// 	i = 0;
// 	ibis = 0;
// 	line = "ls               -l            |      cat              -e";
// 	while (line && line[i])
// 	{
// 		if (is_token(line[i]))
// 		{
// 			if (ibis != i)
//                 add_substr_to_list(buff, line, i, ibis);
// 			buff = ft_substr(line, i, 1);
// 			printf("buff : %s\n", buff);
// 			free(buff);
// 			while (line[i + 1] == ' ')
// 				i++;
// 			ibis = i + 1;
// 		}
// 		else if (line[i] == ' ' || line[i + 1] == '\0')
// 		{
// 						while (line[i + 1] == ' ')
// 				i++;
// 			if (line[i + 1] == '\0')
// 			{
// 				i++;
// 				add_substr_to_list(buff, line, i, ibis);
// 				break ;
// 			}
// 			add_substr_to_list(buff, line, i, ibis);
// 			ibis = i + 1;
// 		}
// 		i++;
// 	}
// 	printf("line : %s\n", line);
// 	return (0);
// }
