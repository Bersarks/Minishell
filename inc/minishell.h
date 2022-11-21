#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/wait.h>
# include <dirent.h>
# include <sys/ioctl.h>
# include "../utils/libft/inc/libft.h"

typedef struct s_local
{
	char			*key;
	char			*value;
	struct s_local	*next;
}					t_local;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_l
{
	t_env		*env;
	t_local		*local;
	int			exit_status;
}				t_shell;

typedef struct s_t
{
	unsigned int	counter;
	unsigned int	counter2;
	int				begin_sign_d;
	int				end_sign_d;
	int				begin_echo;
	int				end_echo;
	char			*key;
	char			*return_val;
}					t_set;

typedef struct s_token
{
	char			*value;
	int				type; 
	struct s_token	*next;
}					t_token;

extern t_shell	*g_shell;

// Çevre değişkenlerini okuyup g_shell->env'e atar.
void	init_env(char **envp);

// Ekrana promptu basar ve kullanıcıdan komutu alır.
void	begin_cmds(void);

// Kullanıcıdan alınan komutu <|>"' ve boşluklara göre parçalar.
char 	**cmds_parser(char *input, int idx);


int		pipe_redir_count(char *str);

// tokenizer
int		get_dollar_len(char *str, int len, char *paid);
char	*get_value(char *str, int i);
char	*get_dollar_value(char *str, int idx);
char	*with_quotes(char *str);
char	*get_paid(char c);
char	**tokenizer(char **d_input);
char	*token_proccess(char *str);
char	*only_tilda_or_dollar(char *str);


// UTILS
char	*find_in_env(char *find);

// Açılan tırnakların doğru şekilde kapatılıp kapatılmadığını kontrol eder.
int		quote_check(char *input, int quote_check);

// Tırnak içindeki karakterleri atlayıp tırnak dışına çıkar.
char	*skip_quotes(char *str);

// HOME envini bulur.
char	*find_env_home(void);

// 2 boyutlu diziyi free eder.
void	free_2d_array(char **array);

// Çevre değişkenlerini ekrana basar.
char	*find_in_env(char *find);

char	*word_dup(char *input, int idx, char quote, int *start);
int		word_len(char *str, int i);

// UTILS


// UTILS_2
int		skip_inout(char **str, int len);
char	*quoted_words(char *input, int *idx);
char	*only_word(char *input, int *idx);
char	*find_in_local(char *find);

// Verilen adrese verilen karakteri yazar;
void	assignment_process(char **input, char **str, int idx);

// UTILS_2


#endif