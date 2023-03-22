#pragma once

#include <vector>

// Needed for the spaceship operator
#include <compare>

namespace corgi::image
{

/**
 * @brief Most common pixel format, just to make the whole thing easier to use
 */
enum class pixel_format
{
    rgba_32,
    rgb_24
};

/**
 * @brief   Represents an image composed of an array of pixels.
 *
 *		Pixels are color point that are represented in different
 *		format/channel.
 *
 *		Usual format being rgba : with 1 byte for each channel
 *
 *      The image starts on the top left corner :
 *
 *      (0,0)
 *      +------------->
 *      |
 *      |
 *      |
 *      |
 *      |
 *     \|/
 */
class raster_image
{
public:
    /**
     * @brief   Structure created by the pixel class to make it easier to access
     *          or manipulate pixel data when working on a rgba pixel encoded on
     *          32bits
     */
    struct rgba_32_pixel
    {
        unsigned char r, g, b, a;
    };

    /**
     * @brief   Structure created by the pixel class to make it easier to access
     *          or manipulate pixel data when working on a rgb pixel encoded on
     *          24 bits
     */
    struct rgb_24_pixel
    {
        unsigned char r, g, b;
    };

    /**
     * @brief   Checks whether 2 images are almost equals
     *
     *          The
     */
    static bool almost_equal(const raster_image& img1,
                             const raster_image& img2,
                             int                 threshold);

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
     * @brief   Constructs a new raster image with the given dimension and
     *          pixel_format. All pixel are set to 0
     */
    raster_image(int width, int height, pixel_format pixel_format);

    /**
     * @brief   Constructs a new raster image using the implied pixel format
     *          from @p pixel and fill it with copy of @p pixel
     */
    raster_image(int width, int height, rgb_24_pixel pixel);

    /**
     * @brief   Constructs a new raster image using the implied pixel format
     *          from @p pixel and fill it with a copy of @p pixel
     */
    raster_image(int width, int height, rgba_32_pixel pixel);

    /**
     * @brief   Gets how many pixels make the raster image
     */
    int size() const;

    /**
     * @brief   Returns the image's width
     */
    int width() const;

    rgba_32_pixel get_rgba_32_pixel(int index);
    rgb_24_pixel  get_rgb_24_pixel(int index);

    void set_pixel(rgba_32_pixel pixel, int index);
    void set_pixel(rgb_24_pixel pixel, int index);

    /**
     * @brief   Resize the image in width
     *
     *          @param new_width : Image's new width
     *          @param resize_mode sd
     */
    void width(int               new_width,
               width_resize_mode resize_mode = width_resize_mode::right);

    /**
     * @brief   Return's the image's on the y axis
     */
    int height() const;

    /**
     * @brief   Resize the the image on the x axis
     *
     * @param new_height    Image's new height
     * @param resize_mode   How the image is being resized
     */
    void height(int                new_height,
                height_resize_mode resize_mode = height_resize_mode::down);

    /**
     * @brief   Computes how many bits are used for 1 pixel.
     */
    short bits_per_pixel() const;

    /**
     * @brief   Gets how many bits are used per channel for the image
     */
    short bits_per_color_channel() const;

    /**
     * @brief   Gets how many color channel the image is made of
     */
    short color_channel_count() const;

    std::byte* data();

private:
    void init_data();

    /**
     * @brief   Image data
     */
    std::vector<std::byte> data_;

    int width_;
    /**
     * @brief   Image's height
     */
    int height_;

    /**
     * @brief   Channel count
     *
     *          1 = Greyscale
     *          2 = RG
     *          3 = RGB
     *          4 = RGBA
     */
    short color_channel_count_;

    /**
     * @brief   Channel size in bits
     *
     *          Images usually uses 8 bits per channel (1 byte)
     */
    short bits_per_color_channel_;

    friend bool operator==(const raster_image& img1, const raster_image& img2);
    friend bool operator!=(const raster_image& img1, const raster_image& img2);
};

bool operator==(const raster_image& img1, const raster_image& img2);
bool operator!=(const raster_image& img1, const raster_image& img2);
}    // namespace corgi::image