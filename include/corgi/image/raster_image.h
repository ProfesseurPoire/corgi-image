#pragma once

#include <bitset>
#include <vector>

// Needed for the spaceship operator apparently, maybe not lighted up because
// vector probably has it too
#include <compare>

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
    struct rgba_32_pixel
    {
        unsigned char r, g, b, a;
    };

    struct rgb_24_pixel
    {
        unsigned char r, g, b;
    };
    // would be nice to have the usual pixels though but I'm not really sure how
    // to handle that
    class pixel
    {
        /**
         * @brief Converts the pixel in rgba 32 bitsPerPixel format
         */
        rgba_32_pixel as_rgba_32();

        /**
         * @brief Converts the pixel in rgb 24 bitsPerPixel format
         */
        rgb_24_pixel as_rgb_24();

        int                color_channel_count_ {0};
        int                bits_per_pixel_ {0};
        std::vector<bool>* data_ {};
    };

    /**
     *@brief    Checks whether 2 images are almost equals
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
     * @brief   Creates a new raster image with all pixel channel set to 0
     */
    raster_image(int width,
                 int height,
                 int color_channel_count,
                 int bits_per_color_channel);

    /**
     * @brief   Creates a raster image where every pixels equals @p pix
     */
    raster_image(int   width,
                 int   height,
                 int   color_channel_count,
                 int   bits_per_channel,
                 pixel pix);

    /**
     * @brief   Returns the image's width
     */
    int width() const;

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

    // Well that's a solution, but I'd still

    class iterator
    {
    public:
        iterator& operator++();
        pixel&    operator*();
        iterator& operator+();
        pixel*    operator->();

        friend bool operator==(const iterator& it1, const iterator& it2);
        friend std::partial_ordering operator<=>(const iterator& it1,
                                                 const iterator& it2);

        raster_image* raster_image_ {nullptr};
        int           current_pixel_index_ {0};
    };

    iterator begin();
    iterator end();

    iterator cbegin() const;
    iterator cend() const;

    void* data();

private:
    /**
     * @brief   Image data
     */
    std::vector<bool> data_;

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
    friend int  operator<=>(const raster_image& img1, const raster_image& img2);
};

bool operator==(const raster_image::iterator& it1,
                const raster_image::iterator& it2);

std::partial_ordering operator<=>(const raster_image::iterator& it1,
                                  const raster_image::iterator& it2);

bool operator==(const raster_image& img1, const raster_image& img2);
int  operator<=>(const raster_image& img1, const raster_image& img2);
}    // namespace corgi::image