/*************************************************************************
 *                                                                       *
 * Open Dynamics Engine, Copyright (C) 2001-2003 Russell L. Smith.       *
 * All rights reserved.  Email: russ@q12.org   Web: www.q12.org          *
 *                                                                       *
 * Threading base wrapper class header file.                             *
 * Copyright (C) 2011-2025 Oleh Derevenko. All rights reserved.          *
 * e-mail: odar@eleks.com (change all "a" to "e")                        *
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
 * A default threading instance holder class definition
 * Copyright (c) 2017-2025 Oleh Derevenko, odar@eleks.com (change all "a" to "e")
 */


#ifndef _ODE__PRIVATE_DEFAULT_THREADING_H_
#define _ODE__PRIVATE_DEFAULT_THREADING_H_


#include <ode/threading.h>


class DefaultThreadingHolder
{
public:
    static bool initializeDefaultThreading();
    static void finalizeDefaultThreading();

    static dThreadingImplementationID getDefaultThreadingImpl() { return m_defaultThreadingImpl; }
    static const dThreadingFunctionsInfo *getDefaultThreadingFunctions() { return m_defaultThreadingFunctions; }

private:
    static dThreadingImplementationID       m_defaultThreadingImpl;
    static const dThreadingFunctionsInfo    *m_defaultThreadingFunctions;
};


#endif // #ifndef _ODE__PRIVATE_DEFAULT_THREADING_H_
