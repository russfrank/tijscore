/**
 * Appcelerator Titanium License
 * This source code and all modifications done by Appcelerator
 * are licensed under the Apache Public License (version 2) and
 * are Copyright (c) 2009 by Appcelerator, Inc.
 */

/*
 * Copyright (C) 2008, 2009 Apple Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1.  Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 * 2.  Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 * 3.  Neither the name of Apple Computer, Inc. ("Apple") nor the names of
 *     its contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE AND ITS CONTRIBUTORS "AS IS" AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL APPLE OR ITS CONTRIBUTORS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef TiPropertyNameIterator_h
#define TiPropertyNameIterator_h

#include "TiObject.h"
#include "TiString.h"
#include "Operations.h"
#include "PropertyNameArray.h"

namespace TI {

    class Identifier;
    class TiObject;

    class TiPropertyNameIterator : public TiCell {
        friend class JIT;

    public:
        static TiPropertyNameIterator* create(TiExcState*, TiObject*);
        
        static PassRefPtr<Structure> createStructure(TiValue prototype)
        {
            return Structure::create(prototype, TypeInfo(CompoundType, OverridesMarkChildren));
        }

        virtual bool isPropertyNameIterator() const { return true; }

        virtual void markChildren(MarkStack&);

        bool getOffset(size_t i, int& offset)
        {
            if (i >= m_numCacheableSlots)
                return false;
            offset = i;
            return true;
        }

        TiValue get(TiExcState*, TiObject*, size_t i);
        size_t size() { return m_jsStringsSize; }

        void setCachedStructure(Structure* structure) { m_cachedStructure = structure; }
        Structure* cachedStructure() { return m_cachedStructure; }

        void setCachedPrototypeChain(NonNullPassRefPtr<StructureChain> cachedPrototypeChain) { m_cachedPrototypeChain = cachedPrototypeChain; }
        StructureChain* cachedPrototypeChain() { return m_cachedPrototypeChain.get(); }

    private:
        TiPropertyNameIterator(TiExcState*, PropertyNameArrayData* propertyNameArrayData, size_t numCacheableSlot);

        Structure* m_cachedStructure;
        RefPtr<StructureChain> m_cachedPrototypeChain;
        uint32_t m_numCacheableSlots;
        uint32_t m_jsStringsSize;
        OwnArrayPtr<TiValue> m_jsStrings;
    };

inline TiPropertyNameIterator::TiPropertyNameIterator(TiExcState* exec, PropertyNameArrayData* propertyNameArrayData, size_t numCacheableSlots)
    : TiCell(exec->globalData().propertyNameIteratorStructure.get())
    , m_cachedStructure(0)
    , m_numCacheableSlots(numCacheableSlots)
    , m_jsStringsSize(propertyNameArrayData->propertyNameVector().size())
    , m_jsStrings(new TiValue[m_jsStringsSize])
{
    PropertyNameArrayData::PropertyNameVector& propertyNameVector = propertyNameArrayData->propertyNameVector();
    for (size_t i = 0; i < m_jsStringsSize; ++i)
        m_jsStrings[i] = jsOwnedString(exec, propertyNameVector[i].ustring());
}

inline void Structure::setEnumerationCache(TiPropertyNameIterator* enumerationCache)
{
    ASSERT(!isDictionary());
    m_enumerationCache = enumerationCache;
}

} // namespace TI

#endif // TiPropertyNameIterator_h
