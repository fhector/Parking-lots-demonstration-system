/***************************************************************************\
	Copyright (c) 2004-2007 threewater@up-tech.com, All rights reserved.
	by threewter	2004.4.26
\***************************************************************************/
	

/***************************************************************************\
    #说明: 控制台函数定义
	----------------------------------  Bug  --------------------------------------

	----------------------------------  TODO list  --------------------------------------

	----------------------------------修正--------------------------------------

	2004-5-2	创建

\***************************************************************************/

#ifndef __CONSOLE_H__
#define __CONSOLE_H__

typedef int (*cmd_func_t)(int, char *[]);

typedef struct {
	cmd_func_t func;
	char *pShellMenu;	//shell模式下显示的菜单字符串，如果为NULL,则不出现在系统菜单里
	char MenuAcc;		//shell模式下菜单快捷键 ，大小写不敏感
	char *pCommand;	//命令行模式下的命令，如果为NULL，则不出现在命令行中
	char *pHelp;			//命令行模式下的帮助
}cmd_function;


#define MAX_COMMANDLINE_LENGTH 256
#define MAX_ARGS (MAX_COMMANDLINE_LENGTH / 4)
#define MAX_COMMANDNAME_LENGTH 256/4
#define MAX_COMMANDTYPE_LENGTH 128

#define ENOERROR	0	/* no error at all */
#ifndef EINVAL
#define EINVAL		1	/* invalid argument */
#endif
#define ENOPARAMS	2	/* not enough parameters */
#define EMAGIC		3	/* magic value failed */
#define ECOMMAND	4	/* invalid command */
#define ENAN		5	/* not a number */
#define EALIGN		6	/* addres not aligned */
#define ERANGE		7	/* out of range */
#define ETIMEOUT	8	/* timeout exceeded */
#define ETOOSHORT	9	/* short CNCFILE */
#define ETOOLONG	10	/* long CNCFILE */
#define EAMBIGCMD	11	/* ambiguous command */
#define EFLASHERASE	12	/* can't erase flash block */
#define EFLASHPGM	13	/* flash program error */
#define ESERIAL		14	/* serial port error */

void Shell_input(void);
int Console_input(int argc, char *argv[]);
int GetCommand(char *command, int len);
int parse_command(char *cmdline);
void init_commands(void);
int get_num_command_matches(char *cmdline);
void parse_args(char *cmdline, int *argc, char **argv);

int echo_callback(int argc, char *argv[]);
int help_callback(int argc, char *argv[]);

#endif
