/*
    This file is part of Magnum.

    Copyright © 2010, 2011, 2012, 2013, 2014, 2015, 2016, 2017, 2018, 2019,
                2020, 2021, 2022 Vladimír Vondruš <mosra@centrum.cz>

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

#include "PixelFormat.h"

#include <string>
#include <Corrade/Containers/ArrayView.h>
#include <Corrade/Utility/Assert.h>
#include <Corrade/Utility/Debug.h>

#include "Magnum/Math/Vector3.h"

namespace Magnum {

UnsignedInt pixelFormatSize(const PixelFormat format) {
    CORRADE_ASSERT(!isPixelFormatImplementationSpecific(format),
        "pixelFormatSize(): can't determine size of an implementation-specific format" << reinterpret_cast<void*>(pixelFormatUnwrap(format)), {});

    #ifdef CORRADE_TARGET_GCC
    #pragma GCC diagnostic push
    #pragma GCC diagnostic error "-Wswitch"
    #endif
    switch(format) {
        case PixelFormat::R8Unorm:
        case PixelFormat::R8Snorm:
        case PixelFormat::R8Srgb:
        case PixelFormat::R8UI:
        case PixelFormat::R8I:
        case PixelFormat::Stencil8UI:
            return 1;
        case PixelFormat::RG8Unorm:
        case PixelFormat::RG8Snorm:
        case PixelFormat::RG8Srgb:
        case PixelFormat::RG8UI:
        case PixelFormat::RG8I:
        case PixelFormat::R16Unorm:
        case PixelFormat::R16Snorm:
        case PixelFormat::R16UI:
        case PixelFormat::R16I:
        case PixelFormat::R16F:
        case PixelFormat::Depth16Unorm:
            return 2;
        case PixelFormat::RGB8Unorm:
        case PixelFormat::RGB8Snorm:
        case PixelFormat::RGB8Srgb:
        case PixelFormat::RGB8UI:
        case PixelFormat::RGB8I:
            return 3;
        case PixelFormat::RGBA8Unorm:
        case PixelFormat::RGBA8Snorm:
        case PixelFormat::RGBA8Srgb:
        case PixelFormat::RGBA8UI:
        case PixelFormat::RGBA8I:
        case PixelFormat::RG16Unorm:
        case PixelFormat::RG16Snorm:
        case PixelFormat::RG16UI:
        case PixelFormat::RG16I:
        case PixelFormat::RG16F:
        case PixelFormat::R32UI:
        case PixelFormat::R32I:
        case PixelFormat::R32F:
        case PixelFormat::Depth24Unorm:
        case PixelFormat::Depth32F:
        case PixelFormat::Depth16UnormStencil8UI:
        case PixelFormat::Depth24UnormStencil8UI:
            return 4;
        case PixelFormat::RGB16Unorm:
        case PixelFormat::RGB16Snorm:
        case PixelFormat::RGB16UI:
        case PixelFormat::RGB16I:
        case PixelFormat::RGB16F:
            return 6;
        case PixelFormat::RGBA16Unorm:
        case PixelFormat::RGBA16Snorm:
        case PixelFormat::RGBA16UI:
        case PixelFormat::RGBA16I:
        case PixelFormat::RGBA16F:
        case PixelFormat::RG32UI:
        case PixelFormat::RG32I:
        case PixelFormat::RG32F:
        case PixelFormat::Depth32FStencil8UI:
            return 8;
        case PixelFormat::RGB32UI:
        case PixelFormat::RGB32I:
        case PixelFormat::RGB32F:
            return 12;
        case PixelFormat::RGBA32UI:
        case PixelFormat::RGBA32I:
        case PixelFormat::RGBA32F:
            return 16;
    }
    #ifdef CORRADE_TARGET_GCC
    #pragma GCC diagnostic pop
    #endif

    CORRADE_ASSERT_UNREACHABLE("pixelFormatSize(): invalid format" << format, {});
}

PixelFormat pixelFormatChannelFormat(const PixelFormat format) {
    CORRADE_ASSERT(!isPixelFormatImplementationSpecific(format),
        "pixelFormatChannelFormat(): can't determine channel format of an implementation-specific format" << reinterpret_cast<void*>(pixelFormatUnwrap(format)), {});

    #ifdef CORRADE_TARGET_GCC
    #pragma GCC diagnostic push
    #pragma GCC diagnostic error "-Wswitch"
    #endif
    switch(format) {
        case PixelFormat::R8Unorm:
        case PixelFormat::RG8Unorm:
        case PixelFormat::RGB8Unorm:
        case PixelFormat::RGBA8Unorm:
            return PixelFormat::R8Unorm;
        case PixelFormat::R8Snorm:
        case PixelFormat::RG8Snorm:
        case PixelFormat::RGB8Snorm:
        case PixelFormat::RGBA8Snorm:
            return PixelFormat::R8Snorm;
        case PixelFormat::R8Srgb:
        case PixelFormat::RG8Srgb:
        case PixelFormat::RGB8Srgb:
        case PixelFormat::RGBA8Srgb:
            return PixelFormat::R8Srgb;
        case PixelFormat::R8UI:
        case PixelFormat::RG8UI:
        case PixelFormat::RGB8UI:
        case PixelFormat::RGBA8UI:
            return PixelFormat::R8UI;
        case PixelFormat::R8I:
        case PixelFormat::RG8I:
        case PixelFormat::RGB8I:
        case PixelFormat::RGBA8I:
            return PixelFormat::R8I;
        case PixelFormat::R16Unorm:
        case PixelFormat::RG16Unorm:
        case PixelFormat::RGB16Unorm:
        case PixelFormat::RGBA16Unorm:
            return PixelFormat::R16Unorm;
        case PixelFormat::R16Snorm:
        case PixelFormat::RG16Snorm:
        case PixelFormat::RGB16Snorm:
        case PixelFormat::RGBA16Snorm:
            return PixelFormat::R16Snorm;
        case PixelFormat::R16UI:
        case PixelFormat::RG16UI:
        case PixelFormat::RGB16UI:
        case PixelFormat::RGBA16UI:
            return PixelFormat::R16UI;
        case PixelFormat::R16I:
        case PixelFormat::RG16I:
        case PixelFormat::RGB16I:
        case PixelFormat::RGBA16I:
            return PixelFormat::R16I;
        case PixelFormat::R32UI:
        case PixelFormat::RG32UI:
        case PixelFormat::RGB32UI:
        case PixelFormat::RGBA32UI:
            return PixelFormat::R32UI;
        case PixelFormat::R32I:
        case PixelFormat::RG32I:
        case PixelFormat::RGB32I:
        case PixelFormat::RGBA32I:
            return PixelFormat::R32I;
        case PixelFormat::R16F:
        case PixelFormat::RG16F:
        case PixelFormat::RGB16F:
        case PixelFormat::RGBA16F:
            return PixelFormat::R16F;
        case PixelFormat::R32F:
        case PixelFormat::RG32F:
        case PixelFormat::RGB32F:
        case PixelFormat::RGBA32F:
            return PixelFormat::R32F;

        case PixelFormat::Stencil8UI:
        case PixelFormat::Depth16Unorm:
        case PixelFormat::Depth24Unorm:
        case PixelFormat::Depth32F:
        case PixelFormat::Depth16UnormStencil8UI:
        case PixelFormat::Depth24UnormStencil8UI:
        case PixelFormat::Depth32FStencil8UI:
            CORRADE_ASSERT_UNREACHABLE("pixelFormatChannelFormat(): can't determine channel format of" << format, {});
    }
    #ifdef CORRADE_TARGET_GCC
    #pragma GCC diagnostic pop
    #endif

    CORRADE_ASSERT_UNREACHABLE("pixelFormatChannelFormat(): invalid format" << format, {});
}

UnsignedInt pixelFormatChannelCount(const PixelFormat format) {
    CORRADE_ASSERT(!isPixelFormatImplementationSpecific(format),
        "pixelFormatChannelCount(): can't determine channel count of an implementation-specific format" << reinterpret_cast<void*>(pixelFormatUnwrap(format)), {});

    #ifdef CORRADE_TARGET_GCC
    #pragma GCC diagnostic push
    #pragma GCC diagnostic error "-Wswitch"
    #endif
    switch(format) {
        case PixelFormat::R8Unorm:
        case PixelFormat::R8Snorm:
        case PixelFormat::R8Srgb:
        case PixelFormat::R8UI:
        case PixelFormat::R8I:
        case PixelFormat::R16Unorm:
        case PixelFormat::R16Snorm:
        case PixelFormat::R16UI:
        case PixelFormat::R16I:
        case PixelFormat::R32UI:
        case PixelFormat::R32I:
        case PixelFormat::R16F:
        case PixelFormat::R32F:
            return 1;
        case PixelFormat::RG8Unorm:
        case PixelFormat::RG8Snorm:
        case PixelFormat::RG8Srgb:
        case PixelFormat::RG8UI:
        case PixelFormat::RG8I:
        case PixelFormat::RG16Unorm:
        case PixelFormat::RG16Snorm:
        case PixelFormat::RG16UI:
        case PixelFormat::RG16I:
        case PixelFormat::RG32UI:
        case PixelFormat::RG32I:
        case PixelFormat::RG16F:
        case PixelFormat::RG32F:
            return 2;
        case PixelFormat::RGB8Unorm:
        case PixelFormat::RGB8Snorm:
        case PixelFormat::RGB8Srgb:
        case PixelFormat::RGB8UI:
        case PixelFormat::RGB8I:
        case PixelFormat::RGB16Unorm:
        case PixelFormat::RGB16Snorm:
        case PixelFormat::RGB16UI:
        case PixelFormat::RGB16I:
        case PixelFormat::RGB32UI:
        case PixelFormat::RGB32I:
        case PixelFormat::RGB16F:
        case PixelFormat::RGB32F:
            return 3;
        case PixelFormat::RGBA8Unorm:
        case PixelFormat::RGBA8Snorm:
        case PixelFormat::RGBA8Srgb:
        case PixelFormat::RGBA8UI:
        case PixelFormat::RGBA8I:
        case PixelFormat::RGBA16Unorm:
        case PixelFormat::RGBA16Snorm:
        case PixelFormat::RGBA16UI:
        case PixelFormat::RGBA16I:
        case PixelFormat::RGBA32UI:
        case PixelFormat::RGBA32I:
        case PixelFormat::RGBA16F:
        case PixelFormat::RGBA32F:
            return 4;
        case PixelFormat::Depth16Unorm:
        case PixelFormat::Depth24Unorm:
        case PixelFormat::Depth32F:
        case PixelFormat::Stencil8UI:
        case PixelFormat::Depth16UnormStencil8UI:
        case PixelFormat::Depth24UnormStencil8UI:
        case PixelFormat::Depth32FStencil8UI:
            CORRADE_ASSERT_UNREACHABLE("pixelFormatChannelCount(): can't determine channel count of" << format, {});
    }
    #ifdef CORRADE_TARGET_GCC
    #pragma GCC diagnostic pop
    #endif

    CORRADE_ASSERT_UNREACHABLE("pixelFormatChannelCount(): invalid format" << format, {});
}

bool isPixelFormatSrgb(const PixelFormat format) {
    CORRADE_ASSERT(!isPixelFormatImplementationSpecific(format),
        "isPixelFormatSrgb(): can't determine colorspace of an implementation-specific format" << reinterpret_cast<void*>(pixelFormatUnwrap(format)), {});

    #ifdef CORRADE_TARGET_GCC
    #pragma GCC diagnostic push
    #pragma GCC diagnostic error "-Wswitch"
    #endif
    switch(format) {
        case PixelFormat::R8Srgb:
        case PixelFormat::RG8Srgb:
        case PixelFormat::RGB8Srgb:
        case PixelFormat::RGBA8Srgb:
            return true;
        case PixelFormat::R8Unorm:
        case PixelFormat::RG8Unorm:
        case PixelFormat::RGB8Unorm:
        case PixelFormat::RGBA8Unorm:
        case PixelFormat::R8Snorm:
        case PixelFormat::RG8Snorm:
        case PixelFormat::RGB8Snorm:
        case PixelFormat::RGBA8Snorm:
        case PixelFormat::R8UI:
        case PixelFormat::RG8UI:
        case PixelFormat::RGB8UI:
        case PixelFormat::RGBA8UI:
        case PixelFormat::R8I:
        case PixelFormat::RG8I:
        case PixelFormat::RGB8I:
        case PixelFormat::RGBA8I:
        case PixelFormat::R16Unorm:
        case PixelFormat::RG16Unorm:
        case PixelFormat::RGB16Unorm:
        case PixelFormat::RGBA16Unorm:
        case PixelFormat::R16Snorm:
        case PixelFormat::RG16Snorm:
        case PixelFormat::RGB16Snorm:
        case PixelFormat::RGBA16Snorm:
        case PixelFormat::R16UI:
        case PixelFormat::RG16UI:
        case PixelFormat::RGB16UI:
        case PixelFormat::RGBA16UI:
        case PixelFormat::R16I:
        case PixelFormat::RG16I:
        case PixelFormat::RGB16I:
        case PixelFormat::RGBA16I:
        case PixelFormat::R32UI:
        case PixelFormat::RG32UI:
        case PixelFormat::RGB32UI:
        case PixelFormat::RGBA32UI:
        case PixelFormat::R32I:
        case PixelFormat::RG32I:
        case PixelFormat::RGB32I:
        case PixelFormat::RGBA32I:
        case PixelFormat::R16F:
        case PixelFormat::RG16F:
        case PixelFormat::RGB16F:
        case PixelFormat::RGBA16F:
        case PixelFormat::R32F:
        case PixelFormat::RG32F:
        case PixelFormat::RGB32F:
        case PixelFormat::RGBA32F:
        case PixelFormat::Depth16Unorm:
        case PixelFormat::Depth24Unorm:
        case PixelFormat::Depth32F:
        case PixelFormat::Stencil8UI:
        case PixelFormat::Depth16UnormStencil8UI:
        case PixelFormat::Depth24UnormStencil8UI:
        case PixelFormat::Depth32FStencil8UI:
            return false;
    }
    #ifdef CORRADE_TARGET_GCC
    #pragma GCC diagnostic pop
    #endif

    CORRADE_ASSERT_UNREACHABLE("isPixelFormatSrgb(): invalid format" << format, {});
}

bool isPixelFormatDepthOrStencil(const PixelFormat format) {
    CORRADE_ASSERT(!isPixelFormatImplementationSpecific(format),
        "isPixelFormatDepthOrStencil(): can't determine type of an implementation-specific format" << reinterpret_cast<void*>(pixelFormatUnwrap(format)), {});

    #ifdef CORRADE_TARGET_GCC
    #pragma GCC diagnostic push
    #pragma GCC diagnostic error "-Wswitch"
    #endif
    switch(format) {
        case PixelFormat::R8Unorm:
        case PixelFormat::RG8Unorm:
        case PixelFormat::RGB8Unorm:
        case PixelFormat::RGBA8Unorm:
        case PixelFormat::R8Snorm:
        case PixelFormat::RG8Snorm:
        case PixelFormat::RGB8Snorm:
        case PixelFormat::RGBA8Snorm:
        case PixelFormat::R8Srgb:
        case PixelFormat::RG8Srgb:
        case PixelFormat::RGB8Srgb:
        case PixelFormat::RGBA8Srgb:
        case PixelFormat::R8UI:
        case PixelFormat::RG8UI:
        case PixelFormat::RGB8UI:
        case PixelFormat::RGBA8UI:
        case PixelFormat::R8I:
        case PixelFormat::RG8I:
        case PixelFormat::RGB8I:
        case PixelFormat::RGBA8I:
        case PixelFormat::R16Unorm:
        case PixelFormat::RG16Unorm:
        case PixelFormat::RGB16Unorm:
        case PixelFormat::RGBA16Unorm:
        case PixelFormat::R16Snorm:
        case PixelFormat::RG16Snorm:
        case PixelFormat::RGB16Snorm:
        case PixelFormat::RGBA16Snorm:
        case PixelFormat::R16UI:
        case PixelFormat::RG16UI:
        case PixelFormat::RGB16UI:
        case PixelFormat::RGBA16UI:
        case PixelFormat::R16I:
        case PixelFormat::RG16I:
        case PixelFormat::RGB16I:
        case PixelFormat::RGBA16I:
        case PixelFormat::R32UI:
        case PixelFormat::RG32UI:
        case PixelFormat::RGB32UI:
        case PixelFormat::RGBA32UI:
        case PixelFormat::R32I:
        case PixelFormat::RG32I:
        case PixelFormat::RGB32I:
        case PixelFormat::RGBA32I:
        case PixelFormat::R16F:
        case PixelFormat::RG16F:
        case PixelFormat::RGB16F:
        case PixelFormat::RGBA16F:
        case PixelFormat::R32F:
        case PixelFormat::RG32F:
        case PixelFormat::RGB32F:
        case PixelFormat::RGBA32F:
            return false;
        case PixelFormat::Depth16Unorm:
        case PixelFormat::Depth24Unorm:
        case PixelFormat::Depth32F:
        case PixelFormat::Stencil8UI:
        case PixelFormat::Depth16UnormStencil8UI:
        case PixelFormat::Depth24UnormStencil8UI:
        case PixelFormat::Depth32FStencil8UI:
            return true;
    }
    #ifdef CORRADE_TARGET_GCC
    #pragma GCC diagnostic pop
    #endif

    CORRADE_ASSERT_UNREACHABLE("isPixelFormatDepthOrStencil(): invalid format" << format, {});
}

namespace {

#ifndef DOXYGEN_GENERATING_OUTPUT /* It gets *really* confused */
constexpr const char* PixelFormatNames[] {
    #define _c(format) #format,
    #include "Magnum/Implementation/pixelFormatMapping.hpp"
    #undef _c
};
#endif

}

#ifndef DOXYGEN_GENERATING_OUTPUT
Debug& operator<<(Debug& debug, const PixelFormat value) {
    const bool packed = debug.immediateFlags() >= Debug::Flag::Packed;

    if(!packed)
        debug << "PixelFormat" << Debug::nospace;

    if(isPixelFormatImplementationSpecific(value)) {
        return debug << (packed ? "ImplementationSpecific(" : "::ImplementationSpecific(") << Debug::nospace << reinterpret_cast<void*>(pixelFormatUnwrap(value)) << Debug::nospace << ")";
    }

    if(UnsignedInt(value) - 1 < Containers::arraySize(PixelFormatNames)) {
        return debug << (packed ? "" : "::") << Debug::nospace << PixelFormatNames[UnsignedInt(value) - 1];
    }

    return debug << (packed ? "" : "(") << Debug::nospace << reinterpret_cast<void*>(UnsignedInt(value)) << Debug::nospace << (packed ? "" : ")");
}
#endif

namespace {

#ifndef DOXYGEN_GENERATING_OUTPUT /* It gets *really* confused */
constexpr const char* CompressedPixelFormatNames[] {
    #define _c(format, width, height, depth, size) #format,
    #include "Magnum/Implementation/compressedPixelFormatMapping.hpp"
    #undef _c
};

constexpr UnsignedShort CompressedBlockData[] {
    /* Assuming w/h/d/s is never larger than 16 (and never zero), each number
       has 1 subtracted and packed into four bits, 16 bits in total. The size
       is supplied in bits, so first divide by eight and then subtract 1. For
       the currently ~100 supported formats that makes this table to be about
       256 bytes.*/
    #define _c(format, width, height, depth, size) \
        ((width - 1) << 12) | \
        ((height - 1) << 8) | \
        ((depth - 1) << 4) | \
        ((size >> 3) - 1),
    #include "Magnum/Implementation/compressedPixelFormatMapping.hpp"
    #undef _c
};
#endif

}

Vector3i compressedPixelFormatBlockSize(const CompressedPixelFormat format) {
    CORRADE_ASSERT(!(UnsignedInt(format) & (1 << 31)),
        "compressedPixelFormatBlockSize(): can't determine size of an implementation-specific format" << reinterpret_cast<void*>(compressedPixelFormatUnwrap(format)), {});

    CORRADE_ASSERT(UnsignedInt(format) - 1 < Containers::arraySize(CompressedBlockData),
        "compressedPixelFormatBlockSize(): invalid format" << format, {});
    const UnsignedInt data = CompressedBlockData[UnsignedInt(format) - 1];
    return {
        (Int(data >> 12) & 0xf) + 1,
        (Int(data >>  8) & 0xf) + 1,
        (Int(data >>  4) & 0xf) + 1,
    };
}

#ifdef MAGNUM_BUILD_DEPRECATED
Vector3i compressedBlockSize(const CompressedPixelFormat format) {
    return compressedPixelFormatBlockSize(format);
}
#endif

UnsignedInt compressedPixelFormatBlockDataSize(const CompressedPixelFormat format) {
    CORRADE_ASSERT(!(UnsignedInt(format) & (1 << 31)),
        "compressedPixelFormatBlockDataSize(): can't determine size of an implementation-specific format" << reinterpret_cast<void*>(compressedPixelFormatUnwrap(format)), {});

    CORRADE_ASSERT(UnsignedInt(format) - 1 < Containers::arraySize(CompressedBlockData),
        "compressedPixelFormatBlockDataSize(): invalid format" << format, {});
    return (CompressedBlockData[UnsignedInt(format) - 1] & 0xf) + 1;
}

#ifndef DOXYGEN_GENERATING_OUTPUT
Debug& operator<<(Debug& debug, const CompressedPixelFormat value) {
    const bool packed = debug.immediateFlags() >= Debug::Flag::Packed;

    if(!packed)
        debug << "CompressedPixelFormat" << Debug::nospace;

    if(isCompressedPixelFormatImplementationSpecific(value)) {
        return debug << (packed ? "ImplementationSpecific(" : "::ImplementationSpecific(") << Debug::nospace << reinterpret_cast<void*>(compressedPixelFormatUnwrap(value)) << Debug::nospace << ")";
    }

    if(UnsignedInt(value) - 1 < Containers::arraySize(CompressedPixelFormatNames)) {
        return debug << (packed ? "" : "::") << Debug::nospace << CompressedPixelFormatNames[UnsignedInt(value) - 1];
    }

    return debug << (packed ? "" : "(") << Debug::nospace << reinterpret_cast<void*>(UnsignedInt(value)) << Debug::nospace << (packed ? "" : ")");
}
#endif

}

namespace Corrade { namespace Utility {

std::string ConfigurationValue<Magnum::PixelFormat>::toString(Magnum::PixelFormat value, ConfigurationValueFlags) {
    if(Magnum::UnsignedInt(value) - 1 < Containers::arraySize(Magnum::PixelFormatNames))
        return Magnum::PixelFormatNames[Magnum::UnsignedInt(value) - 1];

    return {};
}

Magnum::PixelFormat ConfigurationValue<Magnum::PixelFormat>::fromString(const std::string& stringValue, ConfigurationValueFlags) {
    /** @todo This is extremely slow with >100 values. Do a binary search on a
        sorted index list instead (extracted into a common utility) */
    for(std::size_t i = 0; i != Containers::arraySize(Magnum::PixelFormatNames); ++i)
        if(stringValue == Magnum::PixelFormatNames[i]) return Magnum::PixelFormat(i + 1);

    return {};
}

std::string ConfigurationValue<Magnum::CompressedPixelFormat>::toString(Magnum::CompressedPixelFormat value, ConfigurationValueFlags) {
    if(Magnum::UnsignedInt(value) - 1 < Containers::arraySize(Magnum::CompressedPixelFormatNames))
        return Magnum::CompressedPixelFormatNames[Magnum::UnsignedInt(value) - 1];

    return {};
}

Magnum::CompressedPixelFormat ConfigurationValue<Magnum::CompressedPixelFormat>::fromString(const std::string& stringValue, ConfigurationValueFlags) {
    /** @todo This is extremely slow with >100 values. Do a binary search on a
        sorted index list instead (extracted into a common utility) */
    for(std::size_t i = 0; i != Containers::arraySize(Magnum::CompressedPixelFormatNames); ++i)
        if(stringValue == Magnum::CompressedPixelFormatNames[i]) return Magnum::CompressedPixelFormat(i + 1);

    return {};
}

}}
