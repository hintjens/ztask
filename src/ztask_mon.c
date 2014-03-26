/*  =========================================================================
    ztask_mon - system monitoring for ztask

    Generated codec implementation for ztask_mon
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
    ztask_mon - system monitoring for ztask
@discuss
@end
*/

#include "../include/ztask_classes.h"

//  Structure of our class

struct _ztask_mon_t {
    glibtop_cpu cpu;              // current cpu
    glibtop_mem memory;           // current memory
    ztask_mon_proc_t *sys;        // system proc
    zlist_t *proceses;            // list of processes

};

//  --------------------------------------------------------------------------
//  Create a new ztask_mon

ztask_mon_t *
ztask_mon_new ()
{
    ztask_mon_t *self = (ztask_mon_t *) zmalloc (sizeof (ztask_mon_t));
    self->sys = ztask_mon_proc_new (0);
    self->proceses = zlist_new();

    glibtop_init();

    return self;
}


//  --------------------------------------------------------------------------
//  Destroy the ztask_mon

void
ztask_mon_destroy (ztask_mon_t **self_p)
{
    assert (self_p);
    if (*self_p) {
        ztask_mon_t *self = *self_p;

        ztask_mon_processes_destroy (self);
        zlist_destroy (&self->proceses);

        ztask_mon_proc_destroy (&self->sys);
        glibtop_close();

        //  Free object itself
        free (self);
        *self_p = NULL;
    }
}

//  --------------------------------------------------------------------------
//  Print contents of message to stdout

void
ztask_mon_dump (ztask_mon_t *self)
{
    assert (self);
    ztask_mon_proc_dump (self->sys);
    ztask_mon_proc_t *p = (ztask_mon_proc_t *) zlist_first (self->proceses);
    while (p) {
        ztask_mon_proc_dump (p);
        p = (ztask_mon_proc_t *) zlist_next (self->proceses);
    }
}

//  --------------------------------------------------------------------------
//  Destroy all subprocesses

void
ztask_mon_processes_destroy (ztask_mon_t *self)
{
    assert (self);
    ztask_mon_proc_t *p;
    while ( (p = (ztask_mon_proc_t *) zlist_pop (self->proceses))) {
        ztask_mon_proc_destroy (&p);
    }
}

//  --------------------------------------------------------------------------
//  Update all subprocesses

void
ztask_mon_update (ztask_mon_t *self)
{
    assert (self);
    glibtop_get_cpu (&self->cpu);
    glibtop_get_mem (&self->memory);

    /* update system monitoring */
    ztask_mon_proc_update (self->sys, &self->cpu, &self->memory, 0);

    /* update processes monitoring */
    ztask_mon_proc_t *p = (ztask_mon_proc_t *) zlist_first (self->proceses);
    while (p) {
        ztask_mon_proc_update (p, &self->cpu, &self->memory, self->sys);
        p = (ztask_mon_proc_t *) zlist_next (self->proceses);
    }

    /* setting current values for total and used cpu */
    ztask_mon_proc_set_cpu_total_last (self->sys, self->cpu.total);
    ztask_mon_proc_set_cpu_used_last (self->sys, self->cpu.user + self->cpu.nice + self->cpu.sys);
}

//  --------------------------------------------------------------------------
//  Is process monitred

int
ztask_mon_is_process (ztask_mon_t *self, pid_t pid)
{
    assert (self);
    ztask_mon_proc_t *p = (ztask_mon_proc_t *) zlist_first (self->proceses);
    while (p) {
        if (ztask_mon_proc_pid (p) == pid)
            return 1;
        p = (ztask_mon_proc_t *) zlist_next (self->proceses);
    }
    return 0;
}

//  --------------------------------------------------------------------------
//  Add process

void
ztask_mon_add_process (ztask_mon_t *self, pid_t pid)
{
    assert (self);
    // TODO think of it
    if (ztask_mon_proc_pid (self->sys) == pid) return;

    ztask_mon_proc_t *p = ztask_mon_proc_new (pid);
    zlist_append (self->proceses, p);
}

//  --------------------------------------------------------------------------
//  Remove Process

void
ztask_mon_remove_process (ztask_mon_t *self, pid_t pid)
{
    assert (self);
    if (ztask_mon_proc_pid (self->sys) != pid) return;

    ztask_mon_proc_t *p = (ztask_mon_proc_t *) zlist_first (self->proceses);
    while (p) {
        if (ztask_mon_proc_pid (p) == pid) {
            zlist_remove (self->proceses, p);
            return;
        }
        p = (ztask_mon_proc_t *) zlist_next (self->proceses);
    }
}
//  --------------------------------------------------------------------------
//  Selftest

int
ztask_mon_test (bool verbose)
{
    printf (" * ztask_mon: ");
    if (verbose) printf ("\n");
    //  @selftest
    //  Simple create/destroy test
    ztask_mon_t *self = ztask_mon_new (0);
    assert (self);

    ztask_mon_add_process (self, getpid());

    for (int i = 0; i < 4; i++) {
        ztask_mon_update (self);
        if (verbose) ztask_mon_dump (self);
        zclock_sleep (500);
    }

    ztask_mon_destroy (&self);
    if (verbose) printf (" * ztask_mon: ");
    printf ("OK\n");
    return 0;
}


