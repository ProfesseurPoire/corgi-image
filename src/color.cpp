#include <corgi/image/color.h>

namespace corgi::image
{

color::color(unsigned char red,
             unsigned char green,
             unsigned char blue,
             unsigned char alpha)
    : red_(red)
    , green_(green)
    , blue_(blue)
    , alpha_(alpha)
    , format_(color_format::rgba)
{
}

color::color(unsigned char red, unsigned char green, unsigned char blue)
    : red_(red)
    , green_(green)
    , blue_(blue)
    , format_(color_format::rgb)
{
}

unsigned char color::red() const noexcept
{
    return red_;
}

unsigned char color::green() const noexcept
{
    return green_;
}

unsigned char color::blue() const noexcept
{
    return blue_;
}

unsigned char color::alpha() const noexcept
{
    return alpha_;
}

void color::red(unsigned char val)
{
    red_ = val;
}

void color::green(unsigned char val)
{
    green_ = val;
}

void color::blue(unsigned char val)
{
    blue_ = val;
}

void color::alpha(unsigned char val)
{
    alpha_ = val;
}

color_format color::format() const noexcept
{
    return format_;
}

int color::sum() const noexcept
{
    int sum {0};
    sum += red_;
    sum += green_;
    sum += blue_;
    if(format_ == color_format::rgba)
        sum += alpha_;
    return sum;
}

}    // namespace corgi::image