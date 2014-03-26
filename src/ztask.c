/*  =========================================================================
    ztask - framework to run various tasks in parallel

    Generated codec implementation for ztask
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
    ztask - framework to run various tasks in parallel
@discuss
@end
*/

#include "../include/ztask_classes.h"

//  Structure of our class

struct _ztask_t {
    int debug;      // debug
};

//  --------------------------------------------------------------------------
//  Create a new ztask

ztask_t *
ztask_new ()
{
    ztask_t *self = (ztask_t *) zmalloc (sizeof (ztask_t));
    self->debug = 0;
    return self;
}


//  --------------------------------------------------------------------------
//  Destroy the ztask

void
ztask_destroy (ztask_t **self_p)
{
    assert (self_p);
    if (*self_p) {
        ztask_t *self = *self_p;
        //  Free object itself
        free (self);
        *self_p = NULL;
    }
}

//  --------------------------------------------------------------------------
//  Print contents of message to stdout

void
ztask_dump (ztask_t *self)
{
    assert (self);
    printf ("debug=%d", self->debug);
}

//  --------------------------------------------------------------------------
//  Selftest

int
ztask_test (bool verbose)
{
    printf (" * ztask: ");

    //  @selftest
    //  Simple create/destroy test
    ztask_t *self = ztask_new ();
    assert (self);
    ztask_destroy (&self);

    printf ("OK\n");
    return 0;
}







