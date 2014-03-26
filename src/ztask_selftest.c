/*  =========================================================================
    ztask_selftest - framework to run various tasks in parallel

    -------------------------------------------------------------------------
    Copyright (c) 1991-2014 iMatix Corporation -- http://www.imatix.com
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
    ztask_selftest - Self test of framework to run various tasks in parallel
@discuss
@end
*/

#include "ztask_classes.h"

int main (int argc, char *argv [])
{
    bool verbose;
    if (argc == 2 && streq (argv [1], "-v"))
        verbose = true;
    else
        verbose = false;

    printf ("Running ztask self tests...\n");
    ztask_test (verbose);
    ztask_mon_test (verbose);
    ztask_mon_proc_test (verbose);
    ztask_utils_test (verbose);
    printf ("Tests passed OK\n");
    return 0;
}
