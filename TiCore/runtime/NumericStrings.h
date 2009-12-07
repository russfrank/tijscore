/**
 * Appcelerator Titanium License
 * This source code and all modifications done by Appcelerator
 * are licensed under the Apache Public License (version 2) and
 * are Copyright (c) 2009 by Appcelerator, Inc.
 */

/*
 * Copyright (C) 2009 Apple Inc. All Rights Reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL APPLE INC. OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef NumericStrings_h
#define NumericStrings_h

#include "UString.h"
#include <wtf/HashFunctions.h>

namespace TI {

    class NumericStrings {
    public:
        UString add(double d)
        {
            CacheEntry<double>& entry = lookup(d);
            if (d == entry.key && !entry.value.isNull())
                return entry.value;
            entry.key = d;
            entry.value = UString::from(d);
            return entry.value;
        }

        UString add(int i)
        {
            CacheEntry<int>& entry = lookup(i);
            if (i == entry.key && !entry.value.isNull())
                return entry.value;
            entry.key = i;
            entry.value = UString::from(i);
            return entry.value;
        }

    private:
        static const size_t cacheSize = 64;

        template<typename T>
        struct CacheEntry {
            T key;
            UString value;
        };

        CacheEntry<double>& lookup(double d) { return doubleCache[WTI::FloatHash<double>::hash(d) & (cacheSize - 1)]; }
        CacheEntry<int>& lookup(int i) { return intCache[WTI::IntHash<int>::hash(i) & (cacheSize - 1)]; }

        CacheEntry<double> doubleCache[cacheSize];
        CacheEntry<int> intCache[cacheSize];
    };

} // namespace TI

#endif // NumericStrings_h
