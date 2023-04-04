#include "corgi/image/raster_image.h"

#include <corgi/binary/binary.h>

#include <cmath>

namespace corgi::image
{

color::color(int                           channel_count,
             int                           bits_per_channel,
             corgi::binary::dynamic_bitset bs)
{
    if(channel_count * bits_per_channel != bs.size())
        throw std::invalid_argument(
            "dynamic_bitset size doesn't match channel_count and "
            "bits_per_channel arguments");
    data_ = std::move(bs);
}

rgba32_color::rgba32_color(unsigned char r,
                           unsigned char g,
                           unsigned char b,
                           unsigned char a)
    : color_(4, 8)
{
}

unsigned char rgba32_color::r() const
{
    return color_.data_.data()[0];
}

unsigned char rgba32_color::g() const
{
    return color_.data_.data()[1];
}

unsigned char rgba32_color::b() const
{
    return color_.data_.data()[2];
}

unsigned char rgba32_color::a() const
{
    return color_.data_.data()[3];
}

void rgba32_color::r(unsigned char val)
{
    color_.data_.data()[0] = val;
}

void rgba32_color::g(unsigned char val)
{
    color_.data_.data()[1] = val;
}
void rgba32_color::b(unsigned char val)
{
    color_.data_.data()[2] = val;
}

void rgba32_color::a(unsigned char val)
{
    color_.data_.data()[3] = val;
}

color::color(int channel_count, int bits_per_channel)
    : channel_count_(channel_count)
    , bits_per_channel_(bits_per_channel)
{
    data_ = corgi::binary::dynamic_bitset(channel_count_ * bits_per_channel_);
}

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

    auto d1 = img1.data_;
    auto d2 = img2.data_;

    auto bpp = img1.bits_per_pixel();

    for(int i = 0; i < img1.size(); i++)
    {
        const auto p1 = binary::bits_to_llong(
            bpp * i, bpp, reinterpret_cast<unsigned char*>(d1.data()),
            static_cast<int>(std::ceilf(img1.size() * bpp / 8)));

        const auto p2 = binary::bits_to_llong(
            bpp * i, bpp, reinterpret_cast<unsigned char*>(d2.data()),
            static_cast<int>(std::ceilf(img2.size() * bpp / 8)));

        if(std::abs(p2 - p1) > threshold)
            return false;
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
