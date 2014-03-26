/*  =========================================================================
    ztask_mon_proc - process monitoring for ztask

    Generated codec implementation for ztask_mon_proc
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

/*
@header
    ztask_mon_proc - process monitoring for ztask
@discuss
@end
*/

#include <glibtop/proctime.h>
#include <glibtop/procmem.h>

#include "../include/ztask_classes.h"

//  Structure of our class

struct _ztask_mon_proc_t {
    pid_t pid;              // pid of process
    float cpu;              // cpu usage
    float mem_rss;          // mem_rss usage

    guint64 cpu_used_last;  // cpu used last
    guint64 cpu_total_last; // cpu total last
};

//  --------------------------------------------------------------------------
//  Create a new ztask_mon_proc

ztask_mon_proc_t *
ztask_mon_proc_new (pid_t pid)
{
    ztask_mon_proc_t *self = (ztask_mon_proc_t *) zmalloc (sizeof (ztask_mon_proc_t));
    self->pid = pid;
    self->cpu = 0.0;
    self->mem_rss = 0.0;

    self->cpu_used_last = 0;
    self->cpu_used_last = 0;

    return self;
}


//  --------------------------------------------------------------------------
//  Destroy the ztask_mon_proc

void
ztask_mon_proc_destroy (ztask_mon_proc_t **self_p)
{
    assert (self_p);
    if (*self_p) {
        ztask_mon_proc_t *self = *self_p;
        //  Free object itself
        free (self);
        *self_p = NULL;
    }
}

//  --------------------------------------------------------------------------
//  Updates monitoring information

void ztask_mon_proc_update (ztask_mon_proc_t *self, glibtop_cpu *cpu, glibtop_mem *memory, ztask_mon_proc_t *sys)
{
    assert (self);
    assert (cpu);
    assert (memory);
    
    float total, used, load;

    if (!self->pid) {

        // updating system monitoring info
        if (!ztask_mon_proc_cpu_total_last (self)) {
            used = 0;
            total = 0;
        } else {

            total = cpu->total - ztask_mon_proc_cpu_total_last (self);
            used = cpu->user + cpu->nice + cpu->sys - ztask_mon_proc_cpu_used_last (self);
        }
        //   load = used/total;
        load = 100 * used / MAX (total, 1.0f);
        load = MIN (load, 100.0f);

        self->cpu = load;
        self->mem_rss = (memory->used - memory->buffer - memory->cached);
    } else {
        // updating process monitoring info
        glibtop_proc_time proctime;

        glibtop_get_proc_time (&proctime, self->pid);
        if (!ztask_mon_proc_cpu_total_last (sys)) {
            used = 0;
            total = 0;
        } else {
            // updating system monitoring info
            total = cpu->total - ztask_mon_proc_cpu_total_last (sys);
            used = proctime.rtime - ztask_mon_proc_cpu_used_last (self);
        }

        //   load = used/total;
        load = 100 * used / MAX (total, 1.0f);
        load = MIN (load, 100.0f);

        ztask_mon_proc_set_cpu_total_last (self, cpu->total);
        ztask_mon_proc_set_cpu_used_last (self, proctime.rtime);

        glibtop_proc_mem mem;
        glibtop_get_proc_mem (&mem, self->pid);
        self->cpu = (float) load;
        self->mem_rss = (float) (mem.rss);
    }
}

//  --------------------------------------------------------------------------
//  Returns our pid

pid_t
ztask_mon_proc_pid (ztask_mon_proc_t *self)
{
    assert (self);
    return self->pid;
}

//  --------------------------------------------------------------------------
//  Returns CPU used last

guint64 ztask_mon_proc_cpu_used_last (ztask_mon_proc_t *self)
{
    assert (self);
    return self->cpu_used_last;
}

//  --------------------------------------------------------------------------
//  Sets CPU used last

void ztask_mon_proc_set_cpu_used_last (ztask_mon_proc_t *self, guint64 cpu_used_last)
{
    assert (self);
    self->cpu_used_last = cpu_used_last;
}

//  --------------------------------------------------------------------------
//  Returns CPU total last

guint64 ztask_mon_proc_cpu_total_last (ztask_mon_proc_t *self)
{
    assert (self);
    return self->cpu_total_last;
}

//  --------------------------------------------------------------------------
//  Sets CPU total last

void ztask_mon_proc_set_cpu_total_last (ztask_mon_proc_t *self, guint64 cpu_total_last)
{
    assert (self);
    self->cpu_total_last = cpu_total_last;
}

//  --------------------------------------------------------------------------
//  Returns CPU usage

float ztask_mon_proc_cpu (ztask_mon_proc_t *self)
{
    assert (self);
    return self->cpu;
}

//  --------------------------------------------------------------------------
//  Returns RSS mem

float ztask_mon_proc_mem_rss (ztask_mon_proc_t *self)
{
    assert (self);
    return self->mem_rss;
}


//  --------------------------------------------------------------------------
//  Print contents of message to stdout

void
ztask_mon_proc_dump (ztask_mon_proc_t *self)
{
    assert (self);
    float unit = 1024.0 * 1024.0;
    if (!self->pid)
        printf ("System: ");
    else
        printf ("  pid=%5d", self->pid);

    printf (" cpu=%3.2f mem_rss=%s\n", self->cpu,
            ztask_utils_human_str (self->mem_rss));
}

//  --------------------------------------------------------------------------
//  Selftest

int
ztask_mon_proc_test (bool verbose)
{
    printf (" * ztask_mon_proc: ");
    if (verbose) printf ("\n");

    //  @selftest
    //  Simple create/destroy test
    ztask_mon_proc_t *self = ztask_mon_proc_new (0);
    assert (self);

    // FIXME memory leak (report bug to glibtop)
    glibtop_init();

    glibtop_cpu cpu;
    glibtop_mem memory;

    for (int i = 0; i < 4; i++) {
        glibtop_get_cpu (&cpu);
        glibtop_get_mem (&memory);
        ztask_mon_proc_update (self, &cpu, &memory, 0);
        if (verbose) ztask_mon_proc_dump (self);
        zclock_sleep (500);
        /* setting current values for total and used cpu */
        ztask_mon_proc_set_cpu_total_last (self, cpu.total);
        ztask_mon_proc_set_cpu_used_last (self, cpu.user + cpu.nice + cpu.sys);
    }

    glibtop_close();

    ztask_mon_proc_destroy (&self);

    if (verbose) printf (" * ztask_mon_proc: ");
    printf ("OK\n");
    return 0;
}
