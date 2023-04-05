#pragma once

namespace corgi::image
{
enum class color_format
{
    rgba,
    rgb
};

class color
{
public:
    color(unsigned char red,
          unsigned char green,
          unsigned char blue,
          unsigned char alpha);

    color(unsigned char red, unsigned char green, unsigned char blue);

    unsigned char red() const noexcept;
    unsigned char green() const noexcept;
    unsigned char blue() const noexcept;

    /**
     * @brief Returns the alpha value
     * @throws std::logic_error Thrown if current color doesn't have an alpha
     * channel
     */
    unsigned char alpha() const noexcept;

    color_format format() const noexcept;

    void red(unsigned char val);
    void green(unsigned char val);
    void blue(unsigned char val);
    void alpha(unsigned char val);

    /**
     * @brief Computes the sum of every channel
     */
    int sum() const noexcept;

private:
    unsigned char red_;
    unsigned char green_;
    unsigned char blue_;
    unsigned char alpha_;

    color_format format_;
};
};    // namespace corgi::image