#include "corgi/image/raster_image.h"

#include <cmath>

namespace corgi::image
{

bool raster_image::almost_equal(const raster_image& img1,
                                const raster_image& img2,
                                int)
{

    if(img1.width() != img2.width())
        return false;

    if(img1.height() != img2.height())
        return false;

    if(img1.bits_per_color_channel() != img2.bits_per_color_channel())
        return false;

    if(img1.color_channel_count() != img2.color_channel_count())
        return false;

    for(int i = 0; i < img1.size(); i++)
    {
        // Ok now the hardest part because I don't really know how to test 2
        // pixels
        // And to be honest I'm considering having only rgb 32 and rgba 32
        // images instead of trying to work with everything, 1 bits image are
        // pretty rare but well.
    }

    return true;
}

raster_image::raster_image(int width, int height, pixel_format pixel_format)
    : width_(width)
    , height_(height)
{
    switch(pixel_format)
    {
        case pixel_format::rgba_32:
            bits_per_color_channel_ = 8;
            color_channel_count_    = 4;
            break;

        case pixel_format::rgb_24:
            bits_per_color_channel_ = 8;
            color_channel_count_    = 3;
            break;
    }
    init_data();
}

int raster_image::size() const
{
    return width_ * height_;
}

int raster_image::width() const
{
    return width_;
}

void raster_image::width(int, width_resize_mode) {}

int raster_image::height() const
{
    return height_;
}

void raster_image::height(int, height_resize_mode) {}

short raster_image::bits_per_pixel() const
{
    return color_channel_count_ * bits_per_color_channel_;
}

short raster_image::bits_per_color_channel() const
{
    return bits_per_color_channel_;
}

short raster_image::color_channel_count() const
{
    return color_channel_count_;
}

std::byte* raster_image::data()
{
    return data_.data();
}

void raster_image::init_data()
{
    data_.resize(static_cast<int>(
        std::ceilf(bits_per_color_channel_ * color_channel_count_ * width_ *
                   height_ / 8.0F)));
}

}    // namespace corgi::image