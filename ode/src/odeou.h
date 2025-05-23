/*************************************************************************
*                                                                       *
* OU library interface file for Open Dynamics Engine,                   *
* Copyright (C) 2008-2025 Oleh Derevenko. All rights reserved.          *
* Email: odar@eleks.com (change all "a" to "e")                         *
*                                                                       *
* Open Dynamics Engine, Copyright (C) 2001,2002 Russell L. Smith.       *
* All rights reserved.  Email: russ@q12.org   Web: www.q12.org          *
*                                                                       *
*                                                                       *
* This library is free software; you can redistribute it and/or         *
* modify it under the terms of EITHER:                                  *
*   (1) The GNU Lesser General Public License as published by the Free  *
*       Software Foundation; either version 2.1 of the License, or (at  *
*       your option) any later version. The text of the GNU Lesser      *
*       General Public License is included with this library in the     *
*       file LICENSE.TXT.                                               *
*   (2) The BSD-style license that is included with this library in     *
*       the file LICENSE-BSD.TXT.                                       *
*                                                                       *
* This library is distributed in the hope that it will be useful,       *
* but WITHOUT ANY WARRANTY; without even the implied warranty of        *
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the files    *
* LICENSE.TXT and LICENSE-BSD.TXT for more details.                     *
*                                                                       *
*************************************************************************/

/*

ODE interface to OU library functions.

*/


#ifndef _ODE_ODEOU_H_
#define _ODE_ODEOU_H_


#if dOU_ENABLED

#include <ou/assert.h>
#include <ou/enumarrays.h>
#include <ou/macros.h>
#include <ou/templates.h>
#include <ou/typewrapper.h>
#include <ou/simpleflags.h>
#include <ou/customization.h>

#if dATOMICS_ENABLED
#include <ou/atomic.h>
#include <ou/atomicflags.h>
#endif

#if dTLS_ENABLED
#include <ou/threadlocalstorage.h>
#endif


using _OU_NAMESPACE::CEnumUnsortedElementArray;
using _OU_NAMESPACE::CEnumSortedElementArray;

#if dATOMICS_ENABLED
using _OU_NAMESPACE::atomicord32;
using _OU_NAMESPACE::atomicptr;
using _OU_NAMESPACE::InitializeAtomicAPI;
using _OU_NAMESPACE::FinalizeAtomicAPI;
using _OU_NAMESPACE::AtomicIncrement;
using _OU_NAMESPACE::AtomicDecrement;
using _OU_NAMESPACE::AtomicIncrementNoResult;
using _OU_NAMESPACE::AtomicDecrementNoResult;
using _OU_NAMESPACE::AtomicCompareExchange;
using _OU_NAMESPACE::AtomicExchange;
using _OU_NAMESPACE::AtomicExchangeAddNoResult;
using _OU_NAMESPACE::AtomicExchangeAdd;
using _OU_NAMESPACE::AtomicCompareExchangePointer;
using _OU_NAMESPACE::AtomicExchangePointer;
using _OU_NAMESPACE::AtomicReadReorderBarrier;
using _OU_NAMESPACE::AtomicStore;
using _OU_NAMESPACE::AtomicStorePointer;
#endif


class COdeOu
{
public:
    static bool DoOUCustomizations();
    static void UndoOUCustomizations();

#if dATOMICS_ENABLED
    static bool InitializeAtomics() { return InitializeAtomicAPI(); }
    static void FinalizeAtomics() { FinalizeAtomicAPI(); }
#endif
};


#endif 


#if !dOU_ENABLED || !dATOMICS_ENABLED

typedef unsigned int atomicord32;
typedef void *atomicptr;


#endif // dOU_ENABLED



#endif // _ODE_ODEOU_H_
