#include "corgi/image/raster_image.h"

namespace corgi::image
{

raster_image::raster_image(const int width,
                           const int height,
                           const int color_channel_count,
                           const int bits_per_color_channel)
    : width_(width)
    , height_(height)
    , bits_per_color_channel_(bits_per_color_channel)
    , color_channel_count_(color_channel_count)
{
    data_.resize(bits_per_color_channel * color_channel_count_ * width_ *
                 height_);
}

int raster_image::width() const
{
    return width_;
}

int raster_image::height() const
{
    return height_;
}

int raster_image::bits_per_pixel() const
{
    return color_channel_count * bits_per_color_channel_;
}

}    // namespace corgi::image