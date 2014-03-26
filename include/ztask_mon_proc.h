/*  =========================================================================
    ztask_mon_proc - process monitoring for ztask

    Generated codec header for ztask_mon_proc
    -------------------------------------------------------------------------
    Copyright (c) 2014 UEF SAV -- http://www.saske.sk
    Copyright other contributors as noted in the AUTHORS file.

    This file is part of ztask, an open-source framework for running various
    tasks in parallel

    This is free software; you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License as published by the
    Free Software Foundation; either version 3 of the License, or (at your
    option) any later version.

    This software is distributed in the hope that it will be useful, but
    WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTA-
    BILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General
    Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program. If not, see http://www.gnu.org/licenses/.
    =========================================================================
*/

#ifndef __ZTASK_MON_PROC_H_INCLUDED__
#define __ZTASK_MON_PROC_H_INCLUDED__

#include <glibtop/mem.h>
#include <glibtop/cpu.h>

#ifdef __cplusplus
extern "C" {
#endif

//  Opaque class structure
typedef struct _ztask_mon_proc_t ztask_mon_proc_t;

//  @interface
//  Create a new ztask_mon_proc
ztask_mon_proc_t *
    ztask_mon_proc_new (pid_t pid);

//  Destroy the ztask_mon_proc
CZMQ_EXPORT void
    ztask_mon_proc_destroy (ztask_mon_proc_t **self_p);

//  Updates monitoring information
CZMQ_EXPORT void
ztask_mon_proc_update(ztask_mon_proc_t *self, glibtop_cpu *cpu, glibtop_mem *memory, ztask_mon_proc_t *sys);

//  Returns our pid
CZMQ_EXPORT pid_t
    ztask_mon_proc_pid(ztask_mon_proc_t *self);

//  Returns CPU used last
CZMQ_EXPORT guint64
    ztask_mon_proc_cpu_used_last(ztask_mon_proc_t *self);

//  Sets CPU used last
CZMQ_EXPORT void
    ztask_mon_proc_set_cpu_used_last(ztask_mon_proc_t *self, guint64 cpu_used_last);

//  Returns CPU total last
CZMQ_EXPORT guint64
    ztask_mon_proc_cpu_total_last(ztask_mon_proc_t *self);

//  Sets CPU total last
CZMQ_EXPORT void
    ztask_mon_proc_set_cpu_total_last(ztask_mon_proc_t *self, guint64 cpu_total_last);

//  Returns CPU usage
CZMQ_EXPORT float
    ztask_mon_proc_cpu(ztask_mon_proc_t *self);

//  Returns RSS mem
CZMQ_EXPORT float
    ztask_mon_proc_mem_rss(ztask_mon_proc_t *self);

//  Print contents of message to stdout
CZMQ_EXPORT void
    ztask_mon_proc_dump (ztask_mon_proc_t *self);

//  Self test of this class
CZMQ_EXPORT int
    ztask_mon_proc_test (bool verbose);
//  @end

#ifdef __cplusplus
}
#endif

#endif
