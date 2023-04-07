#include <corgi/image/raster_image.h>
#include <corgi/test/test.h>

#include <filesystem>

using namespace corgi::test;

int main(int argc, char** argv)
{
    corgi::test::add_test(
        "corgi-image", "save_and_load",
        []() -> void
        {
            auto image = corgi::image::raster_image("./resources/corgi.png");

            std::filesystem::remove("./resouces/corgi2.png");
            image.save("./resources/corgi2.png");

            auto image2 = corgi::image::raster_image("./resources/corgi2.png");

            check_equals(image, image2);
        });

    corgi::test::add_test(
        "corgi-image", "almost_equals",
        []() -> void
        {
            std::cout << "load image 1" << std::endl;

            std::cout << " Exist :"
                      << std::filesystem::exists("./resources/corgi.png")
                      << std::endl;

            auto img = corgi::image::raster_image("./resources/corgi.png");

            std::cout << "load image2" << std::endl;
            auto img2 =
                corgi::image::raster_image("./resources/corgi-edited.png");

            std::cout << "check equals" << std::endl;
            check_equals(
                corgi::image::raster_image::almost_equal(img, img2, 117), true);
        });

    corgi::test::run_all();
}