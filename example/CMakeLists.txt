option(BUILD_TEST_SDL "build the test with SDL" OFF)

if(BUILD_TEST_SDL)
add_subdirectory(sdl)
endif(BUILD_TEST_SDL)