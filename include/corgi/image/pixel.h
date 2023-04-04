#pragma once

#include <corgi/image/raster_image.h>

namespace corgi::image
{
class pixel
{
public:
    pixel(raster_image& image, std::size_t pos);

    /**
     * @brief Returns the pixel's position
     */
    size_t pos() const noexcept;

    /**
     * @brief Returns the image the pixel is a part of
     */
    const raster_image& raster_image() const;

    int bits_per_pixel() const;

    int color_channel_count() const;

    /**
     * @brief Converts, if possible, the pixel to an int
     *
     * @throws std::logic_error Thrown if the pixel cannot be converted to an
     * int
     */
    int as_int() const;

    /**
     * @brief Read the bit value at @p pos
     */
    bool read_bit(std::size_t pos);

private:
    image::raster_image& image_;
    std::size_t          pos_ {0};
};
}    // namespace corgi::image