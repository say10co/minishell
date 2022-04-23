

#include "../../includes/includes.h"

// TODO:
// -> handle '--'
// -> handle '~-'
// -> handle '~[USER]'

static int arg_size(char **arg)
{
	int l;
	if(!arg)
		return (0);
	l = 0;
	while(arg[l])
		l++;
	return (l);
}

static void go_todir(char *dir)
{
	int status;

	status = chdir(dir);
	if (status == -1)
		printf("cd: no such file or directory: %s\n", dir);
}

void cd(char **arg)
{
	int size;
	char path[4096];
	int status;
	char *oldpwd;
	char *pwd;
	char *holder;

	size = arg_size(arg);
	getcwd(path, 4096);
	if(size > 3)
		printf("cd: too many arguments\n");
	else if(size == 2 && arg[1][0] == '-' && ft_strlen(arg[1]) == 1)
	{
		// print current directory !!!
		oldpwd = ft_getenv("OLDPWD");
		printf("%s\n", oldpwd);
		status = chdir(oldpwd); 
		if(status == -1)
			perror("cd faild");
	}
	else if((size == 2 && arg[1][0] == '~' && ft_strlen(arg[1]) == 1) || size == 1)
	{
		status = chdir(ft_getenv("HOME"));
		if(status == -1)
			perror("cd faild !");
	}
	else if(size == 3)
	{
		pwd = ft_getenv("PWD");
		holder = ft_strreplace(pwd, arg[1], arg[2]);
		if(!holder)
			printf("cd: string not in pwd: %s\n", arg[1]);
		else
		{
			printf("%s\n", holder);
			chdir(holder);
		}
	}
	else if(size == 2 && (arg[1][0] != '~'))
		go_todir(arg[1]);    
	else if(size == 2 && arg[1][0] == '~' && ft_strlen(arg[1]) > 1)
	{
		holder = ft_getenv("HOME");
		pwd = ft_strreplace(arg[1], "~", holder);
		status = chdir(pwd);
		free(pwd);
		if(status == -1)
			printf("cd: no such file or directory: %s\n", arg[1]);
	}
	else 
	{
		printf("Unsupported arguments !");
		return;
	}
	ft_updateenv("OLDPWD", path);
	getcwd(path, 4096);
	ft_updateenv("PWD", path);

}
