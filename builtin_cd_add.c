#include "minishell.h"

void	cd_also_path(t_data *data, char **cmd, t_env *env_list)
{
	char	*home;

	home = our_get_env(env_list, "HOME");
	if (!home)
		ft_error(data, ERR_CD_HOME, STDERR_FILENO, CD_HOME);//TODO
	if (!cmd[1])
		data->new_path = home;
	else if (!is_token_path(cmd[1]))
		data->new_path = cmd[1];
}
