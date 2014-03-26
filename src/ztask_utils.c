/*  =========================================================================
    ztask_utils - utils for ztask

    Generated codec implementation for ztask_utils
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
    ztask_utils - utils for ztask
@discuss
@end
*/

#include "../include/ztask_classes.h"
#include "../include/ztask_utils.h"

//  --------------------------------------------------------------------------
//  Return human string

char *
ztask_utils_human_str (float number)
{
    static char str[8];
    const char *units[] = { "B", "kB", "MB", "GB", "TB", "PB", "EB", "ZB", "YB" };
    int unitIndex = 0;
    while (number >= 1024.0) {
        number /= 1024.0;
        unitIndex++;
    }
    sprintf (str, "%4.3f %s", number, units[unitIndex]);
    return str;
}

//  --------------------------------------------------------------------------
//  Selftest

int
ztask_utils_test (bool verbose)
{
    printf (" * ztask_utils: ");
    if (verbose) {
        printf ("\n");
        printf ("  %s\n", ztask_utils_human_str (1024.0));
        printf ("  %s\n", ztask_utils_human_str (1024.0 * 1024.0));
        printf ("  %s\n", ztask_utils_human_str (1024.0 * 1024.0 * 1024.0));
        printf ("  %s\n", ztask_utils_human_str (1024.0 * 1024.0 * 1024.0 * 1024.0));
        printf ("  %s\n", ztask_utils_human_str (1024.0 * 1024.0 * 1024.0 * 1024.0 * 1024.0));
        printf ("  %s\n", ztask_utils_human_str (1024.0 * 1024.0 * 1024.0 * 1024.0 * 1024.0 * 1024.0));
        printf ("  %s\n", ztask_utils_human_str (123 * 1024.0 * 1024.0 * 1024.0));
        printf (" * ztask_utils: ");
    }
    printf ("OK\n");
    return 0;
}
