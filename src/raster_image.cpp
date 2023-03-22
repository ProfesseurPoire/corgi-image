#include "corgi/image/raster_image.h"

#include <cmath>

namespace corgi::image
{

bool raster_image::almost_equal(const raster_image& img1,
                                const raster_image& img2,
                                int                 threshold)
{
    for(auto it1 = img1.cbegin(); it1 != img1.cend(); ++it1)
    {

        for(auto it2 = img2.cbegin(); it2 != img2.cend(); ++it2)
        {
            if(threshold == 1)
            {
                return false;
            }
        }
    }
    return true;
}

raster_image::raster_image(const int   width,
                           const int   height,
                           const short color_channel_count,
                           const short bits_per_color_channel)
    : width_(width)
    , height_(height)
    , bits_per_color_channel_(bits_per_color_channel)
    , color_channel_count_(color_channel_count)
{
    data_.resize(static_cast<int>(
        std::ceilf(bits_per_color_channel * color_channel_count_ * width_ *
                   height_ / 8.0F)));
}

raster_image::pixel& raster_image::pixel::operator=(raster_image::pixel& other)
{
    data_ = other.data_;
}

raster_image::raster_image(const int   width,
                           const int   height,
                           const short color_channel_count,
                           const short bits_per_channel,
                           pixel       pix)
    : width_(width)
    , height_(height)
    , color_channel_count_(color_channel_count)
    , bits_per_color_channel_(bits_per_channel)
{
    data_.resize(bits_per_color_channel_ * color_channel_count_ * width_ *
                 height_);

    for(auto p : *this)
    {
        p = pix;
    }
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

}    // namespace corgi::image