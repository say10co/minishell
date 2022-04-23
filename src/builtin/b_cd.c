

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

static void go_tohome()
{
    int status;

    status = chdir(ft_getenv("HOME"));
		if(status == -1)
			perror("cd faild !");
}
static void go_todir(char *dir)
{
	int status;

	status = chdir(dir);
	if (status == -1)
		printf("cd: no such file or directory: %s\n", dir);
}

static void go_tobasedhome(char *dir)
{
    char *holder;
    char *pwd;
    int status;

    holder = ft_getenv("HOME");
		pwd = ft_strreplace(dir, "~", holder);
		status = chdir(pwd);
		free(pwd);
		if(status == -1)
			printf("cd: no such file or directory: %s\n", dir);
}

static void go_replcpwd(char *target, char *replacement)
{
    char *pwd;
    char *holder;
    int status;

    pwd = ft_getenv("PWD");
		holder = ft_strreplace(pwd, target, replacement);
		if(!holder)
			printf("cd: string not in pwd: %s\n", target);
		else
		{
			status = chdir(holder);
		  if(status == -1)
        printf("cd: no such file or directory: %s\n", holder);
			else
      printf("%s\n", holder);
      free(holder);
    }
}

static void go_oldpwd()
{
    char *oldpwd;
    int status;

    oldpwd = ft_getenv("OLDPWD");
		printf("%s\n", oldpwd);
		status = chdir(oldpwd); 
		if(status == -1)
			perror("cd faild");
}

void cd(char **arg)
{
	int size;
	char path[4096];

	size = arg_size(arg);
	getcwd(path, 4096);
	if(size > 3)
		printf("cd: too many arguments\n");
	else if(size == 2 && arg[1][0] == '-' && ft_strlen(arg[1]) == 1)
    go_oldpwd();		
	else if((size == 2 && arg[1][0] == '~' && ft_strlen(arg[1]) == 1) || size == 1)
    go_tohome();
	else if(size == 3)
    go_replcpwd(arg[1], arg[2]);		
	else if(size == 2 && (arg[1][0] != '~'))
		go_todir(arg[1]);    
	else if(size == 2 && arg[1][0] == '~' && ft_strlen(arg[1]) > 1)
    go_tobasedhome(arg[1]);		
	else 
	{
		printf("Unsupported arguments !");
		return;
	}
	ft_updateenv("OLDPWD", path);
	getcwd(path, 4096);
	ft_updateenv("PWD", path);
}
