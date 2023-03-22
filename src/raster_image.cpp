#include "corgi/image/raster_image.h"

namespace corgi::image
{

bool raster_image::almost_equal(const raster_image& img1,
                                const raster_image& img2,
                                int                 threshold)
{
    for(auto it1 = img1.cbegin(); it1 != img1.cend(); it1++)
    {
    }
    return true;
}

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

raster_image::raster_image(int   width,
                           int   height,
                           int   color_channel_count,
                           int   bits_per_channel,
                           pixel pix)
    : width_(width)
    , height_(height)
    , color_channel_count_(color_channel_count)
    , bits_per_color_channel_(bits_per_channel)
{
    data_.resize(bits_per_color_channel_ * color_channel_count_ * width_ *
                 height_);

    for(auto& p : *this)
    {
        p = pix;
    }
}

int raster_image::width() const
{
    return width_;
}

void raster_image::width(int new_width, width_resize_mode resize_mode) {}

int raster_image::height() const
{
    return height_;
}

void raster_image::height(int new_height, height_resize_mode) {}

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

raster_image::iterator raster_image::begin()
{
    return raster_image::iterator();
}

raster_image::iterator raster_image::end()
{
    return raster_image::iterator();
}

raster_image::iterator raster_image::cbegin() const
{
    return raster_image::iterator();
}

raster_image::iterator raster_image::cend() const
{
    return raster_image::iterator();
}

void* raster_image::data()
{
    return &data_[0];
}

bool operator==(const raster_image::iterator& it1,
                const raster_image::iterator& it2)
{
    return true;
}

std::partial_ordering operator<=>(const raster_image::iterator& it1,
                                  const raster_image::iterator& it2)
{
    if(it1.raster_image_ != it2.raster_image_)
        return std::partial_ordering::unordered;

    if(it1.current_pixel_index_ == it2.current_pixel_index_)
        return std::partial_ordering::equivalent;

    if(it1.current_pixel_index_ > it2.current_pixel_index_)
        return std::partial_ordering::greater;

    return std::partial_ordering::less;
}

}    // namespace corgi::image