/*  =========================================================================
    ztask_utils - utils for ztask

    Generated codec header for ztask_utils
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

#ifndef __ZTASK_UTILS_H_INCLUDED__
#define __ZTASK_UTILS_H_INCLUDED__

#ifdef __cplusplus
extern "C" {
#endif


//  Return human string
CZMQ_EXPORT char*
    ztask_utils_human_str (float number);

//  Self test of this class
CZMQ_EXPORT int
    ztask_utils_test (bool verbose);
//  @end

#ifdef __cplusplus
}
#endif

#endif
