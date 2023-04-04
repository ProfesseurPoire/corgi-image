#include <corgi/image/pixel.h>

namespace corgi::image
{
pixel::pixel(image::raster_image* image, std::size_t pos)
    : image_(image)
    , pos_(pos)
{
}

int pixel::bits_per_pixel() const
{
    return image_.bits_per_pixel();
}

int pixel::color_channel_count() const
{
    return image_.color_channel_count();
}

bool pixel::read_bit(std::size_t pos)
{
    return image_.data_.test(pos_ + pos);
}
}    // namespace corgi::image