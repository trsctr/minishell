


define T_CMD            42
define T_WORD            43
define T_EMPTY_WORD    44
define T_PIPE            45
define T_RD_S_L        46
define T_RD_S_R        47
define T_RD_D_L        48
define T_RD_D_R        49


cat Makefile | wc -l


pipe() palautaa 2fd, 0 lukemiseen, 1 kirjoittamiseen

typedef struct s_exec{
	char			*cmd;		= cat
	char			**argv;		= [0]cat [1] Makefile (etsii WORD, jos useampi WORD niin monta [])
	int				read_fd;
	int				write_fd; 	= kirjotus fd jonka pipe palauttaa (luku saastetaan seuraavaa varten)
	struct s_exec	*next;
}				t_exec;


typedef struct s_exec{
	char			*cmd;		= wc
	char			**argv;		= [0]wc [1] -l
	int				read_fd;	= pipesta luku fd
	int				write_fd;
	struct s_exec	*next;
}				t_exec;





/* * * * * * */


cat Makefile >> file > jee | wc -l

// 1. cmd -> sana/sanat
// 2. sen jalkeen ignore kaikki mika ei ole pipe
// 3. 


typedef struct s_token {
	int				type;	CMD
	char			*str;	cat
	struct s_token	*next;
} t_token;





typedef struct s_token {
	int				type;
	char			*str;
	struct s_token	*next;
} t_token;

typedef struct s_token {
	int				type;
	char			*str;
	struct s_token	*next;
} t_token;

typedef struct s_token {
	int				type;
	char			*str;
	struct s_token	*next;
} t_token;

typedef struct s_token {
	int				type;
	char			*str;
	struct s_token	*next;
} t_token;

typedef struct s_token {
	int				type;
	char			*str;
	struct s_token	*next;
} t_token;

typedef struct s_token {
	int				type;
	char			*str;
	struct s_token	*next;
} t_token;




cat Makefile >> file > jee | wc -l


int fd[2];

pipe(fd);

// jos kasiteltava komento pipen vasemmalla, tallennettaan write FD

// fd[0] on read
// fd[1] on write

pipe() palautaa 2fd, 0 lukemiseen, 1 kirjoittamiseen

1. iteraatio (skipataaan RD ja perassa oleva WORD)

typedef struct s_exec{
	char			*cmd;		= cat
	char			**argv;		= [0]cat [1] Makefile (etsii WORD, jos useampi WORD niin monta [])
	int				read_fd;
	int				write_fd; 	= write FD
	struct s_exec	*next;
}				t_exec;

typedef struct s_exec{
	char			*cmd;		= wc
	char			**argv;		= [0]wc [1] -l
	int				read_fd;	= read fd
	int				write_fd;
	struct s_exec	*next;
}				t_exec;


cat Makefile >> file > jee | wc -l

void	funktio() // >>
{
int fd2;

fd2 = open(file, O_CREAT, O_WRONLY, O_APPEND)

close(exec->write_fd);
exec->write_fd = fd2;
}

// funktio tapahtuu uusiksi koska uusi RD
// naita funktioita pitaa olla 4 jokaiselle omalle RD:lle




// << 	HEREDOC

// < fd2 = open(jee, O_RDONLY)




2. iteraatio (etsitaan RD ja perassa oleva WORD)

typedef struct s_exec{
	char			*cmd;		= cat
	char			**argv;		= [0]cat [1] Makefile (etsii WORD, jos useampi WORD niin monta [])
	int				read_fd;
	int				write_fd;	= vanha write FD KORVATAAN uudella fd2 (muista sulkea vanha)
	struct s_exec	*next;
}				t_exec;

// koska loytyi uusi RD korvataan se vanha uudella

void	funktio() // >
{
int fd2;

fd2 = open(jee, O_CREAT, O_WRONLY, O_TRUNC)

close(exec->write_fd);
exec->write_fd = fd2;
}

typedef struct s_exec{
	char			*cmd;		= cat
	char			**argv;		= [0]cat [1] Makefile (etsii WORD, jos useampi WORD niin monta [])
	int				read_fd;
	int				write_fd;	= vanha write FD KORVATAAN uudella fd2 (muista sulkea vanha)
	struct s_exec	*next;
}				t_exec;

// koska nyt pipe -> liikutaan yksi node eteenpain

typedef struct s_exec{
	char			*cmd;		= wc
	char			**argv;		= [0]wc [1] -l
	int				read_fd;	= pipesta luku fd
	int				write_fd;
	struct s_exec	*next;
}				t_exec;

// koska ei RD niin valmis


/*EXECUTRer*/

while (linked listas on nodeja)
{
	if (write_fd)
		dup2(write_fd, 1);
	if (read_fd)
		dup2(read_fd, 0);
	execve(cmd, argv, get_env());
	seuraava node
}




>> sana >> sana CMD



1. Ensimmainen tyyppi oltava aina RD tai CMD

2.	-> RD	->	WORD
	-> CMD	->  WORD / PIPE / RD


RD -> sana (taman tai useamman tallaisen yhdistelman lisaksi pitaa loytya CMD ennen tai jalkeen)

CMD -> mita vaan paitsi CMD

PIPE -> mita vaan paitsi PIPE (huom PIPE hyvaksytaan vain jos ennen ollut CMD)

WORD -> oltava vahintan yksi RD (joka vaatii myos CMD) tai CMD (jos monta WORD niin
		niita ennen oltava yksi CMD tai RD)


