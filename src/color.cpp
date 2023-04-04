#include <corgi/image/color.h>

namespace corgi::image
{

unsigned char color::r() const noexcept
{
    return red_;
}

unsigned char color::g() const noexcept
{
    return green_;
}

unsigned char color::b() const noexcept
{
    return blue_;
}

unsigned char color::a() const noexcept
{
    return alpha_;
}

void color::r(unsigned char val)
{
    red_ = val;
}

void color::g(unsigned char val)
{
    green_ = val;
}

void color::b(unsigned char val)
{
    blue_ = val;
}

void color::a(unsigned char val)
{
    alpha_ = val;
}

}    // namespace corgi::image