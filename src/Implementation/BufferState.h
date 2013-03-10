#ifndef Magnum_Implementation_BufferState_h
#define Magnum_Implementation_BufferState_h
/*
    This file is part of Magnum.

    Copyright © 2010, 2011, 2012, 2013 Vladimír Vondruš <mosra@centrum.cz>

    Permission is hereby granted, free of charge, to any person obtaining a
    copy of this software and associated documentation files (the "Software"),
    to deal in the Software without restriction, including without limitation
    the rights to use, copy, modify, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included
    in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
    THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
    DEALINGS IN THE SOFTWARE.
*/

#include "Buffer.h"

namespace Magnum { namespace Implementation {

struct BufferState {
    #ifndef MAGNUM_TARGET_GLES
    static const std::size_t TargetCount = 13+1;
    #else
    #ifndef MAGNUM_TARGET_GLES2
    static const std::size_t TargetCount = 8+1;
    #else
    static const std::size_t TargetCount = 2+1;
    #endif
    #endif

    /* Target <-> index mapping */
    static std::size_t indexForTarget(Buffer::Target target);
    static const Buffer::Target targetForIndex[TargetCount-1];

    inline constexpr BufferState(): bindings() {}

    /* Currently bound buffer for all targets */
    GLuint bindings[TargetCount];
};

}}

#endif
