#pragma once

#include <corgi/image/color.h>

#include <iostream>
#include <string>
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
     * @brief Checks whether 2 images are almost equals
     * The function inspect every pixel. If the "value"(sum of components) of
     * a pixel from img1 is greater than the value of img2 + threshold, then
     * the test fails
     *
     *
     * @param img1 First image being compared
     * @param img2 Second image being compared
     * @param threshold Max difference between a pixel of img1 and img2
     * authorized
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
    raster_image(int          width,
                 int          height,
                 color_format pixel_format = color_format::rgba);

    /**
     * @brief Constructs a new raster image from @p data
     *
     * Very volatile function.
     */
    raster_image(int                        width,
                 int                        height,
                 color_format               format,
                 std::vector<unsigned char> data);

    /**
     * @brief Constructs a new image by loading the file located at @p path
     *
     * This will be very limited at the start
     *
     * @param path The path to the file that contains the image
     */
    explicit raster_image(const std::string& path);

    /**
     * @brief   Gets how many pixels make the raster image
     */
    int size() const;

    /**
     * @brief   Returns the image's width
     */
    int width() const;

    /**
     * @brief Get the pixel color at @p pos
     *
     * @throws std::out_of_range Thrown if @p pos is out of the image's range
     */
    color get_pixel(std::size_t pos) const;

    /**
     * @brief Sets the pixel at @p index
     */
    void set_pixel(color color, int pos);

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
     * @brief Saves the current image to the given file
     */
    void save(const std::string& file);

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
    int bits_per_pixel() const;

    /**
     * @brief   Gets how many bits are used per channel for the image
     */
    int bits_per_color_channel() const;

    /**
     * @brief   Gets how many color channel the image is made of
     */
    int color_channel_count() const;

    /**
     * @brief Gets the image's color/pixel format
     */
    color_format format() const noexcept;

    unsigned char*       data();
    friend std::ostream& operator<<(std::ostream& os, const raster_image& img);

private:
    void init_data();

    /**
     * @brief   Image data
     */
    std::vector<unsigned char> data_;

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
    int color_channel_count_;

    /**
     * @brief   Channel size in bits
     *
     *          Images usually uses 8 bits per channel (1 byte)
     */
    int bits_per_color_channel_;

    color_format format_;

    friend bool operator==(const raster_image& lhs, const raster_image& rhs);
    friend bool operator!=(const raster_image& lhs, const raster_image& rhs);
};

bool operator==(const raster_image& lhs, const raster_image& rhs);
bool operator!=(const raster_image& lhs, const raster_image& rhs);

inline std::ostream& operator<<(std::ostream& os, const raster_image& img)
{
    os << img.width() << std::endl;
    return os;
}
}    // namespace corgi::image
