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
                 int bits_per_channel);

    /**
     * @brief   Returns the image's width
     */
    int width() const;

    /**
     * @brief   Resize the image in width
     *
     *          @param new_width : Image's new width
     */
    void width(int               new_width,
               width_resize_mode resize_mode = width_resize_mode::right);

    /**
     * @brief   Return's the image's on the y axis
     */
    int height() const;

    /**
     * @brief   Resize the the image on the x axis
     */
    void height(int new_height, height_resize_mode = height_resize_mode::down);

    /**
     * @brief   Computes how many bits are used for 1 pixel.
     */
    int bits_per_pixel() const;

    /**
     * @brief   Gets how many bits are used per channel for the image
     */
    int bits_per_color_channel() const;

    /**
     * @brief   Gets how many color channel the image is made of
     */
    int color_channel_count() const;

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
         * @brief Convertes the pixel in rgb 24 bitsPerPixel format
         */
        rgb_24_pixel as_rgb_24();

        int                color_channel_count;
        int                bits_per_pixel;
        std::vector<bool>* data;
    };

    // Well that's a solution, but I'd still

    class iterator
    {
    public:
        void  operator++();
        void  operator*();
        pixel operator->();

        friend bool operator==(iterator& it1, iterator& it2);
    };

    iterator begin();
    iterator end();

    /**
     * @brief   Image data
     */
    std::vector<bool> data_;

private:
    int width_;
    /**
     * @brief   Image's heigth
     */
    int height_;

    /**
     * @brief   Channel count
     *
     *          1 = Grayscale
     *          2 = RG
     *          3 = RGB
     *          4 = RGBA
     */
    int color_channel_count_;

    /**
     * @brief   Channel size in bits
     *
     *          Images usually uses 8 bits per channel (1 byte)
     */
    int bits_per_color_channel_;

    friend bool operator==(const raster_image& img1, const raster_image& img2);
    friend int  operator<=>(const raster_image& img1, const raster_image& img2);
};

bool operator==(const raster_image::iterator& it1, const raster_image& it2);

bool operator==(const raster_image& img1, const raster_image& img2);
int  operator<=>(const raster_image& img1, const raster_image& img2);
}    // namespace corgi::image