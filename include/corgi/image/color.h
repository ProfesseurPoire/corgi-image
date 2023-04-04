#pragma once

namespace corgi::image
{
class color
{
    enum class format
    {
        rgba,
        rgb
    };

public:
    color(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
    color(unsigned char r, unsigned char g, unsigned char b);

    unsigned char r() const noexcept;
    unsigned char g() const noexcept;
    unsigned char b() const noexcept;
    unsigned char a() const noexcept;

    void r(unsigned char val);
    void g(unsigned char val);
    void b(unsigned char val);
    void a(unsigned char val);

private:
    unsigned char red_;
    unsigned char green_;
    unsigned char blue_;
    unsigned char alpha_;

    // How can I know that I don't the alpha channel?
    int color_channel_count_ = 3;
};
};    // namespace corgi::image