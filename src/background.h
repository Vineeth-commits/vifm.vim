/* vifm
 * Copyright (C) 2001 Ken Steen.
 * Copyright (C) 2011 xaizek.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA
 */

#ifndef __BACKGROUND_H__
#define __BACKGROUND_H__

#ifdef _WIN32
#include <windef.h>
#endif

#include <sys/types.h>

#include <stdio.h>

typedef struct Jobs_List {
	pid_t pid;
	char *cmd;
	int skip_errors;
	int running;
	int exit_code;
	char *error;

	/* for backgrounded commands */
	int total;
	int done;

#ifndef _WIN32
	int fd;
#else
	HANDLE hprocess;
#endif
	struct Jobs_List *next;
} Jobs_List;

typedef struct Finished_Jobs {
	pid_t pid;
	int remove;
	int exit_code;
	struct Finished_Jobs *next;
} Finished_Jobs;

extern struct Jobs_List *jobs;
extern struct Finished_Jobs *fjobs;

int start_background_job(const char *cmd);
int background_and_wait_for_status(char *cmd);
int background_and_wait_for_errors(char *cmd);
int background_and_capture(char *cmd, FILE **out, FILE **err);
void add_finished_job(pid_t pid, int status);
void check_background_jobs(void);
void update_jobs_list(void);

void add_inner_bg_job(Jobs_List *job);
void inner_bg_next(void);
void remove_inner_bg_job(void);

#ifndef _WIN32
Jobs_List * add_background_job(pid_t pid, const char *cmd, int fd);
#else
Jobs_List * add_background_job(pid_t pid, const char *cmd, HANDLE hprocess);
#endif

#endif

/* vim: set tabstop=2 softtabstop=2 shiftwidth=2 noexpandtab cinoptions-=(0 : */
/* vim: set cinoptions+=t0 : */