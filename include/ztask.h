/*  =========================================================================
    ztask - framework to run various tasks in parallel

    Generated codec header for ztask
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

#ifndef __ZTASK_H_INCLUDED__
#define __ZTASK_H_INCLUDED__

#define ZTASK_VERSION_MAJOR 0
#define ZTASK_VERSION_MINOR 0
#define ZTASK_VERSION_PATCH 0

#define ZTASK_MAKE_VERSION(major, minor, patch) \
    ((major) * 10000 + (minor) * 100 + (patch))
#define ZTASK_VERSION \
    ZTASK_MAKE_VERSION(ZTASK_VERSION_MAJOR, ZTASK_VERSION_MINOR, ZTASK_VERSION_PATCH)

#include <czmq.h>
#if CZMQ_VERSION < 20100
#   error "Zyre needs CZMQ/2.1.0 or later"
#endif

#ifdef __cplusplus
extern "C" {
#endif

//  Opaque class structure
typedef struct _ztask_t ztask_t;

//  @interface
//  Create a new ztask
CZMQ_EXPORT ztask_t *
    ztask_new ();

//  Destroy the ztask
CZMQ_EXPORT void
    ztask_destroy (ztask_t **self_p);

//  Print contents of message to stdout
CZMQ_EXPORT void
    ztask_dump (ztask_t *self);

//  Self test of this class
CZMQ_EXPORT int
    ztask_test (bool verbose);
//  @end

#ifdef __cplusplus
}
#endif

#endif
