/***************************************************************************\
	Copyright (c) 2004-2007 threewater@up-tech.com, All rights reserved.
	by threewter	2004.4.26
\***************************************************************************/
	

/***************************************************************************\
    #说明: 文件命令函数定义
	----------------------------------  Bug  --------------------------------------

	----------------------------------  TODO list  --------------------------------------

	----------------------------------修正--------------------------------------

	2004-5-2	创建

\***************************************************************************/

int ls_callback(int argc, char *argv[]);
int ul_callback(int argc, char *argv[]);
int dl_callback(int argc, char *argv[]);
int cat_callback(int argc, char *argv[]);
int cd_callback(int argc, char *argv[]);
int mkdir_callback(int argc, char *argv[]);
int rm_callback(int argc, char *argv[]);
int mv_callback(int argc, char *argv[]);
int rmdir_callback(int argc, char *argv[]);

int FormatNandFlash(int argc, char *argv[]);

extern char currentpath[];

