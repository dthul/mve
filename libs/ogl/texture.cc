#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include "ogl/texture.h"

OGL_NAMESPACE_BEGIN

// as of 15.04.2014 not yet in GCC, took the version from http://gcc.gnu.org/bugzilla/show_bug.cgi?id=57350
inline void *align( std::size_t alignment, std::size_t size,
                    void *&ptr, std::size_t &space ) {
    std::uintptr_t pn = reinterpret_cast< std::uintptr_t >( ptr );
    std::uintptr_t aligned = ( pn + alignment - 1 ) & - alignment;
    std::size_t padding = aligned - pn;
    if ( space < size + padding ) return nullptr;
    space -= padding;
    return ptr = reinterpret_cast< void * >( aligned );
}

void
Texture::init(mve::ByteImage::ConstPtr image)
{
    GLint level = 0;
    GLint int_format = GL_RGBA;
    GLsizei w(image->width()), h(image->height()), c(image->channels());
    GLint border = 0;

    /* Set image properties. */
    GLint type = GL_UNSIGNED_BYTE;
    GLint format = GL_RGBA;
    std::size_t n = 4;
    switch (c)
    {
        case 1: format = GL_RED; n = 1; break;
        case 2: format = GL_RG; n = 2; break;
        case 3: format = GL_RGB; n = 3; break;
        case 4: format = GL_RGBA; n = 4; break;
        default:
            throw std::invalid_argument("Invalid amount of image channels");
    }

#if 0
    std::cout << "Level: " << level << ", internal format: " << int_format
        << ", size: " << w << "x" << h << ", format: " << format
        << std::endl;
#endif

    std::size_t a = this->alignment; // alignment in byte
    std::size_t s = 1; // It is a byte image
    std::size_t l = image->width();
    // see: http://www.talisman.org/opengl-1.1/Reference/glPixelStore.html
    std::size_t k = a * static_cast<std::size_t>(std::ceil(s * n * l / float(a))) / s;
    std::size_t bytes_in_row = image->width() * n;
    std::size_t needed_bytes = k * image->height();
    std::size_t space = needed_bytes + a - 1;
    void *texture_unaligned = std::malloc(space);
    this->texture_unaligned = std::shared_ptr<void>(texture_unaligned);
    void *texture_ptr = align(a, needed_bytes, texture_unaligned, space);
    for (std::size_t rowindex = 0; rowindex < static_cast<std::size_t>(image->height()); ++rowindex)
    {
        std::memcpy((uint8_t*)texture_ptr + (k * rowindex), image->get_data_pointer() + (bytes_in_row * rowindex), bytes_in_row);
    }
    this->level = level;
    this->int_format = int_format;
    this->w = w;
    this->h = h;
    this->border = border;
    this->format = format;
    this->type = type;
    this->data = static_cast<void*>(texture_ptr);
}

void
Texture::upload ()
{
    this->bind();
    glPixelStorei(GL_UNPACK_ALIGNMENT, this->alignment);
    glTexImage2D(GL_TEXTURE_2D, level, int_format, w, h,
        border, format, type, data);
    glGenerateMipmap(GL_TEXTURE_2D);
}

OGL_NAMESPACE_END
