#include "corgi/image/raster_image.h"

#ifndef STB_IMAGE_IMPLEMENTATION
#    define STB_IMAGE_IMPLEMENTATION
#endif

#ifndef STB_IMAGE_WRITE_IMPLEMENTATION
#    define STB_IMAGE_WRITE_IMPLEMENTATION
#endif

#pragma warning(push, 0)
#include "corgi/image/stb_image.h"
#include "corgi/image/stb_image_write.h"
#pragma warning(pop)

#include <cmath>
#include <stdexcept>

namespace corgi::image
{

bool raster_image::almost_equal(const raster_image& img1,
                                const raster_image& img2,
                                int                 threshold)
{
    if(img1.width() != img2.width())
        return false;

    if(img1.height() != img2.height())
        return false;

    if(img1.bits_per_color_channel() != img2.bits_per_color_channel())
        return false;

    if(img1.color_channel_count() != img2.color_channel_count())
        return false;

    if(img1.format() != img2.format())
        return false;

    for(auto i = 0; i < img1.size(); i++)
    {
        auto c1 = img1.get_pixel(i).sum();
        auto c2 = img2.get_pixel(i).sum();

        if(std::abs(c2 - c1) > threshold)
            return false;
    }
    return true;
}

void raster_image::save(const std::string& file)
{
    stbi_write_png(file.c_str(), width_, height_, color_channel_count_,
                   data_.data(), 0);
}

color_format raster_image::format() const noexcept
{
    return format_;
}
raster_image::raster_image(int width, int height, color_format format)
    : width_(width)
    , height_(height)
    , format_(format)
{
    switch(format)
    {
        case color_format::rgba:
            bits_per_color_channel_ = 8;
            color_channel_count_    = 4;
            break;

        case color_format::rgb:
            bits_per_color_channel_ = 8;
            color_channel_count_    = 3;
            break;
    }
    init_data();
}

raster_image::raster_image(const std::string& path)
{
    // Images are horizontal on OpenGL otherwise
    stbi_set_flip_vertically_on_load(false);
    auto data = stbi_load(path.c_str(), &width_, &height_,
                          &color_channel_count_, STBI_rgb_alpha);

    if(color_channel_count_ == 3)
    {
        format_ = color_format::rgb;
    }
    else
        format_ = color_format::rgba;

    bits_per_color_channel_ = 8;

    data_ = std::vector<unsigned char>(
        data, data + (width_ * height_ * color_channel_count_));
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

int raster_image::bits_per_pixel() const
{
    return color_channel_count_ * bits_per_color_channel_;
}

int raster_image::bits_per_color_channel() const
{
    return bits_per_color_channel_;
}

int raster_image::color_channel_count() const
{
    return color_channel_count_;
}

color raster_image::get_pixel(std::size_t pos) const
{
    if(static_cast<int>(pos) >= width_ * height_)
        throw std::out_of_range("Argument pos is out of range");

    switch(format_)
    {
        case color_format::rgba:
            return color(data_[pos * 4], data_[pos * 4 + 1], data_[pos * 4 + 2],
                         data_[pos * 4 + 3]);
            break;
        case color_format::rgb:
            return color(data_[pos * 3], data_[pos * 3 + 1],
                         data_[pos * 3 + 2]);
            break;
    }

    throw std::logic_error("no format");
}

unsigned char* raster_image::data()
{
    return data_.data();
}

void raster_image::init_data()
{
    data_.resize(static_cast<int>(std::ceilf(
        static_cast<float>(bits_per_color_channel_) *
        static_cast<float>(color_channel_count_) * static_cast<float>(width_) *
        static_cast<float>(height_) / 8.0F)));
}

bool operator==(const raster_image& lhs, const raster_image& rhs)
{
    if(lhs.width() != rhs.width())
        return false;

    if(lhs.height() != rhs.height())
        return false;

    if(lhs.color_channel_count() != rhs.color_channel_count())
        return false;

    if(lhs.data_ != rhs.data_)
        return false;
    return true;
}
bool operator!=(const raster_image& img1, const raster_image& img2)
{
    return !(img1 == img2);
}

}    // namespace corgi::image
