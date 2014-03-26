/*  =========================================================================
    ztask_mon - system monitoring for ztask

    Generated codec header for ztask_mon
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

#ifndef __ZTASK_MON_H_INCLUDED__
#define __ZTASK_MON_H_INCLUDED__

#ifdef __cplusplus
extern "C" {
#endif

//  Opaque class structure
typedef struct _ztask_mon_t ztask_mon_t;

//  @interface
//  Create a new ztask_mon
CZMQ_EXPORT ztask_mon_t *
    ztask_mon_new ();

//  Destroy the ztask_mon
CZMQ_EXPORT void
    ztask_mon_destroy (ztask_mon_t **self_p);

//  Print contents of message to stdout
CZMQ_EXPORT void
    ztask_mon_dump (ztask_mon_t *self);

//  Do we monitor process
CZMQ_EXPORT int
   ztask_mon_is_process(ztask_mon_t *self, pid_t pid);

//  Add process
CZMQ_EXPORT void
    ztask_mon_add_process(ztask_mon_t *self, pid_t pid);

//  Remove process
CZMQ_EXPORT void
    ztask_mon_remove_process(ztask_mon_t *self, pid_t pid);

//  Destroy all subprocesses
CZMQ_EXPORT void
    ztask_mon_processes_destroy(ztask_mon_t *self);

//   Update monitoring information
CZMQ_EXPORT void
    ztask_mon_update(ztask_mon_t *self);

//  Self test of this class
CZMQ_EXPORT int
    ztask_mon_test (bool verbose);
//  @end

#ifdef __cplusplus
}
#endif

#endif
