#ifndef _FSMON_H_
#define _FSMON_H_

#include <stdint.h>
#include "fsev.h"
#include "util.h"

#define eprintf(x,y...) fprintf(stderr,x,##y)

#define FM_DEV "/dev/fsevents"
//#define FM_BUFSIZE 131072
#define FM_BUFSIZE 2048
#define FM_DEBUG 0
#define IF_FM_DEBUG if (FM_DEBUG)

typedef struct {
	int pid;
	int ppid;
	const char *proc;
	const char *file;
	const char *newfile; // renamed/moved
	int uid;
	int gid;
	int type;
	int mode;
	uint32_t inode;
	uint64_t tstamp;
	int dev_major;
	int dev_minor;
} FileMonitorEvent;

typedef struct {
	const char *root;
	const char *proc;
	const char *link;
	int pid;
	int json;
	int stop;
	int child;
	int alarm;
	int fd;
	int fileonly;
	uint64_t count;
} FileMonitor;

typedef int (*FileMonitorCallback)(FileMonitor *fm, FileMonitorEvent *ev);

int fm_begin (FileMonitor *fm);
int fm_loop (FileMonitor *fm, FileMonitorCallback cb);
int fm_end (FileMonitor *fm);

#endif