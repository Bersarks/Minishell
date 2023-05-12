#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <fcntl.h>
# include <signal.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include "../utils/libft/inc/libft.h"
# include "../utils/gnl/inc/get_next_line.h"
# include "../utils/print_fd/inc/ft_printf.h"

# define BUILTIN 1
# define REDIRECT 2
# define T_FILE 3
# define COMMAND 4
# define PIPE 5
# define ERR STDERR_FILENO
# define OUT STDOUT_FILENO
# define IN STDIN_FILENO

// Local değişkenlerin tanımlanması
typedef struct s_local
{
	char			*key;
	char			*value;
	struct s_local	*next;
}					t_local;

// Çevresel değişkenleri tutan struct
typedef struct s_env
{
	char			*key;
	char			*value;
	int				flag;
	struct s_env	*next;
}					t_env;

typedef struct s_export
{
	char			*key;
	char			*value;
	struct s_export	*next;
}					t_export;

// Komutların tanımlanması
typedef struct s_l
{
	t_env		*env;
	t_local		*local;
	t_export	*export;
	int			exit_status;
	int			dup_fd[2];
	int			file_error_check;
	int			heredoc_count;
}				t_shell;

typedef struct s_token
{
	char			*value;
	int				type;
	int				quote_check;
	int				heredoc_check;
	struct s_token	*next;
}					t_token;

extern t_shell	*g_shell;

// Çevre değişkenlerinin ayrıştırması.
void		init_env(char **envp);

// Kullanıcı taraflı komutların ayrıştırılması.
void		begin_cmd(void);
char		**cmd_parser(char *usr_cmd, int index);

// Komutların geçmişe kaydedilmesi.
void		cmd_history(char *cmd);

// Terminal geçmişini yüklemek için.
void		load_history(char *path);

// Tırnak işaretlerinin denetlemesini.
int			quote_check(char *usr_cmd, int quote_count);

// Tırnak işaretlerini atlamak için.
char		*skip_quotes(char *str);

/**
 * @brief Verilen komut içerisinde ki "set" karakterlerini siler ve
 * geriye kalan harflerin adedini döner.
 * 
 * @param cmd Komut
 * @param set Çıkarılacak karakterler
 * @return Komut içerisinden "set" karakterlerini çıkarıp uzunluğunu döner.
 */
int			strtrim_len(char *cmd, char *set);

// Pipe ve Redirection işleçlerinin sayısını hesaplamak için.
int			pipe_redir_count(char *usr_cmd);

// Redirection işleçlerinin kelimede ki adedini hesaplamak için.
int			skip_inout(char **str, int len);

// Kelime uzunluğunu almak için --> Tırnaklı, redirection ve düz kelimeler için.
int			word_len(char *usr_cmd, int len);

// Tek kelimeyi almak için.
char		*only_word(char *input);

// Tırnak içerisinde ki kelimeleri almak için.
char		*quoted_words(char	*usr_cmd);

/**
 * @brief Parçalanmış olarak gelen komutların içerisindeki $ işleçlerini
 * işler.
 * 
 * @param split_cmds Parçalanmış komut dizisi
 */
void		tokenizer(char **split_cmds);

/**
 * @brief Komut içerisindeki $ ile başlayan tüm parçaların değerlerini
 * varsa çevresel
 * değişkenlerden
 * alır yoksa local değişkenlerden alır. Ekstra olarak $$ veya $? işleçlerini de
 * hesaplar.
 * 
 * @param cmd Parçalanmış komut
 * @param i Oluşturulan tokenin indexi (Varsayılan olarak 0)
 * @param idx Okunabilirlik için oluşturulmuş değişken (Varsayılan olarak 0)
 * @return Geriye, varsa $ ile başlayan parçaların değerlerini değiştirilmiş
 * şekilde döner.
 */
char		*get_dollar_val(char *cmd, int i, int idx);

// GET_DOLLAR_VAL de açılacak yerin uzunluğunu hesaplamak için.
int			dollar_len(char *split_cmds, int len);

/**
 * @brief Verilen stringin uzunluğunu hesaplar ve free eder.
 * Çünkü free_strlen'e gelen str genelde fonksiyon içerisinden malloc ile gelir.
 * 
 * @param str fonksiyon ile gelen string
 * @return int stringin uzunluğu
 */
int			free_strlen(char *str);

/**
 * @brief src stringini dst stringinin sonuna ekler ve src stringini free eder.
 * Çünkü free_strcat'e gelen src genelde fonksiyon içerisinden malloc ile gelir.
 * @param dst Hedef string
 * @param src Kaynak string
 * @return dst ve src'nin birleşmiş hali sonunda NULL olmadan geri döner.
 */
char		*free_strcat(char *dst, char *src);

char		*with_quotes(char *split_cmds);

char		*get_value(char *split_cmds, int i);

// Çevresel değişlenlerin içerisinde arama yapmak için.
char		*find_in_env(char *split_cmds);

// Local değişkenlerin içerisinde arama yapmak için.
char		*find_in_local(char *split_cmds);

// Başlangıç ve sonda ki tırnak işaretlerini atmak için.
void		remove_quotes(char **cmd);

// Parçalanmış komutları token listesine eklemek için.
void		add_token_lst(char **input, t_token **token_lst);

// Eklenen tokenlerin tipini belirlemek için.
void		define_types(t_token *token_lst);

int			pipe_check(t_token *tmp);

// Builtin kontrolü yapmak için.
int			is_builtin(char *str);

// Operator kontrolü yapmak için. "| < > >> <<"
int			is_operator(char *str);

// Redirection işleçlerinin kontrolü yapmak için.
int			is_redirect(char *str);

// Pipe mı Redirection mu kontrolü yapmak için.
int			find_operator(char *str);

// TEST AŞAMASINDA
	// RUN_CMD.C
void		run_cmd(t_token *token_lst);
	// RUN_REDIRECT.C
void		redirect_proccess(t_token *token_lst, int *heredoc_count);

	// RUN_UTILS.C
int			is_command_or_argument(int type);
int			get_commands_length(t_token *current, t_token *command);
char		**before_pipe(t_token *token_lst, t_token *command);
int			redirect_file_check(t_token *token_list);
	// CHECK_EQUAL_VALUE.C
void		check_equal_value(char **split);
int			check_env(char **double_str);
	// PROCESS_COMMAND.C
void		execute_command(char **no_pipe);
	// EXECUTE_BUILTINS.C
void		execute_builtin(char **str);

	// RUN_BUILTIN.C
void		echo_option_n(char **str);
void		pwd_no_option(void);
void		env(char **argv);
void		export(char **str);
void		unset(char **str);

	// RUN_CD.C
/**
 * @brief Bash'te yer alan cd komutunun belirli kısımlarını taklit eder.
 * 
 * @param str cd komutunun parçalanmış hali. Örn: cd .. veya cd /home gibi.
 * str[0] = cd str[1] = .. veya str[1] = /home
 */
void		cd(char **str);

// TEST AŞAMASINDA

/**
 * @brief Dinamik olarak yer ayrılmış 2 bouyutlu diziyi free eder.
 * 
 * @param 2 bouyutlu diziyi alır.
 */
void		free_2d_array(char **array);

/**
 * @brief Çevresel değişkenlerin içerisine yeni bir değişken ekler.
 * 
 * @param key env içerisindeki görüntülenecek değişken adını alır 
 * @param value env içerisindeki görüntülenecek değişken değerini alır 
 */
void		add_env(char *key, char *value);

/**
 * @brief OLDPWD değişkenin env de olup olmadığını kontrol ettikten sonra
 * yoksa oluşturur, varsa günceller.
 * 
 * @param oldpwd Varsa OLDPWD değişkenini alır yoksa NULL alır.
 * @param new_pwd OLDPWD değişkeninin güncellenecek değerini alır.
 */
void		update_oldpwd(char *oldpwd, char *new_pwd);

/**
 * @brief Verilen key değerinin alfabetik olup olmadığını kontrol eder.
 * Ekstra olarak "_" işareti dahil edilmiştir.
 * 
 * @param key Alfabetik olup olmadığı kontrol edilecek kelimeyi alır.
 * @return Kelime alfabetik ise 1, değilse 0 döner.
 */
int			check_key(char *key);

/**
 * @brief Atama işlemi yapılırken "=" varsa "=" önceki kısmı str[0] içerisine
 * "=" sonrası kısmı str[1] içerisine atar.
 * 
 * @param str Ayrıştırılacak stringi alır.
 * @return str[0] ve str[1] içerisine ayrıştırılmış stringi döner.
 */
char		**my_split(char **str);

/**
 * @brief Unset komutu çalıştırıldığında çevresel değişkenlerin içerisinden
 * silinmesini sağlar.
 * 
 * @param del Silinecek değişkenin adını alır.
 * @param local Silinecek değişkenin local struct adresini alır
 * (Standart olarak: &g_shell->local)
 */
void		delete_from_local(char *del, t_local **local);

void		commands(char **str);

void		heredoc(char *delimiter, int fd);

void		readable_for_heredoc(char *file_name, t_token *token_lst);

/**
 * @brief STDERR'a hata mesajı yazdırır ve çıkış kodu'nu günceller.
 * 
 * @param message STDERR'a yazılacak mesajı alır.
 * @param exit_status Çıkış kodunu alır.
 * @param ... Hata mesajı içerisinde değişken kullanılacaksa kullanılır.
 */
void		error_message(char *message, int exit_status, ...);

/**
 * @brief Çevresel değişkenlerin içerisindeki değişkenlerin
 * içerisindeki here document operatörlerini kontrol eder.
 * 
 * @param token_lst Token listesi alır.
 * @return 1: here document operatörü varsa, 0: yoksa
 */
int			redirect_check(t_token *token_lst);

/**
 * @brief Çevresel değişkenlerin içerisindeki PATH değişkenini
 * alır ve dizi olarak döndürür.
 * Eğer PATH değişkeni yoksa NULL döndürür.
 * 
 * @return PATH değişkeni dizi olarak döndürülür.
*/
char		*get_path(void);

/**
 * @brief Kullanıcının girdiği komutların işlenmeye başladığı nokta.
 * 
 * @param *usr_cmd Kullanıcının prompta girdiği komut.
 * 
 */
void		cmd_operations(char *usr_cmd);

/**
 * @brief Girilen komutun en sonunda pipe varsa ve sonrası null ise
 * quota girer.
 * 
 * @return Yapılan işlem başarılı ise 1 döner.
 */
int			last_pipe_check(void);

#endif