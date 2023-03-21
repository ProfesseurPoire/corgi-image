#pragma once

#include <bitset>
#include <vector>

namespace corgi::image
{
/**
 * @brief   Represents an image composed of an array of pixels.
 *
 *		Pixels are color point that are represented in different
 *		format/channel.
 *
 *		Usual format being rgba : with 1 byte for each channel
 *
 *
 */
class raster_image
{

public:
    /**
     * @brief   Creates a new raster image with all pixel channel set to 0
     */
    raster_image(int width,
                 int height,
                 int color_channel_count,
                 int bits_per_channel);

    /**
     * @brief   Returns the image's width
     */
    int width() const;

    enum class width_resize_mode
    {
        stretch,    // The image is stretched to fill the new width
        left,       // New pixels are added to the left side of the image
        right,      // New pixels are added to the right side of the image
        center      // New pixels are equally added to the left and right of the
                    // image
    };

    enum class height_resize_mode
    {
        stretch,    // The image is stretched to fill the new height
        up,         // New pixels are added to the top side of the image
        down,       // New pixels are added to the down side of the image
        center    // New pixels are added to the top and down side of the image
    };

    /**
     * @brief   Resize the image, trying to keep the existing pixels in place
     *
     *          @param
     */
    void width(int new_width, bool stretch = false);

    /**
     * @brief   Image's height
     */
    int height() const;

    int width_;

    /**
     * @brief   Image's heigth
     */
    int height_;

    /**
     * @brief   Computes how many bits are used for 1 pixel.
     */
    int bits_per_pixel() const;

    /**
     * @brief   Data image
     */
    std::vector<bool> data_;

    /**
     * @brief   Channel size in bits
     *
     *          Images usually uses 8 bits per channel (1 byte)
     */
    int bits_per_channel_;

    /**
     * @brief   Channel count
     *
     *          1 = Grayscale
     *          2 = RG
     *          3 = RGB
     *          4 = RGBA
     */
    int color_channel_count;
};
}    // namespace corgi::image