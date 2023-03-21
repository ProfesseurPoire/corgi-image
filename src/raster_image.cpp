#include "corgi/image/raster_image.h"

namespace corgi::image
{

raster_image::raster_image(const int width,
                           const int height,
                           const int color_channel_count,
                           const int bits_per_channel)
    : width_(width)
    , height(height)
    , bits_per_channel(bits_per_channel)
    , color_channel_count(color_channel_count)
{
    data_.resize(bits_per_channel * color_channel_count * width * height);
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
    return color_channel_count * bits_per_channel;
}

}    // namespace corgi::image