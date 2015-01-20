/***************************************************************************\
	Copyright (c) 2004-2007 threewater@up-tech.com, All rights reserved.
	by threewter	2005.3.9
\***************************************************************************/
/***************************************************************************\
    #说明: bon part
	----------------------------------  Bug  --------------------------------------

	----------------------------------  TODO list  --------------------------------------

	----------------------------------修正--------------------------------------
	2005-3-10	创建

\***************************************************************************/

#define MAX_PART				9
#define PARTITION_OFFSET		(~0)

#define BON_YAFFS_PART		1

typedef struct {
    unsigned long offset;
    unsigned long size;
    unsigned long flag;
    unsigned short *bad_blocks;
} partition_t;

typedef struct {
	int num_part;
	partition_t parts[MAX_PART];
} bon_part_info;

extern bon_part_info bon_part;
int read_bon_partition(void);


