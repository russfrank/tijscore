/**
 * Appcelerator Titanium License
 * This source code and all modifications done by Appcelerator
 * are licensed under the Apache Public License (version 2) and
 * are Copyright (c) 2009-2012 by Appcelerator, Inc.
 */

/*
 *  Copyright (C) 2004, 2008, 2009 Apple Inc. All rights reserved.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Library General Public
 *  License as published by the Free Software Foundation; either
 *  version 2 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Library General Public License for more details.
 *
 *  You should have received a copy of the GNU Library General Public License
 *  along with this library; see the file COPYING.LIB.  If not, write to
 *  the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 *  Boston, MA 02110-1301, USA.
 *
 */


#ifndef Protect_h
#define Protect_h

#include "Heap.h"
#include "TiValue.h"

namespace TI {

    inline void gcProtect(TiCell* val) 
    {
        Heap::heap(val)->protect(val);
    }

    inline void gcUnprotect(TiCell* val)
    {
        Heap::heap(val)->unprotect(val);
    }

    inline void gcProtectNullTolerant(TiCell* val) 
    {
        if (val) 
            gcProtect(val);
    }

    inline void gcUnprotectNullTolerant(TiCell* val) 
    {
        if (val) 
            gcUnprotect(val);
    }
    
    inline void gcProtect(TiValue value)
    {
        if (value && value.isCell())
            gcProtect(value.asCell());
    }

    inline void gcUnprotect(TiValue value)
    {
        if (value && value.isCell())
            gcUnprotect(value.asCell());
    }

} // namespace TI

#endif // Protect_h
