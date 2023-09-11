#include <iostream>
#include <chrono>
#include "color.h"
#include "vec3.h"

int main() {
    // Image
    int image_width = 256;
    int image_height = 256;
    // Render
    // PPM standard: P3 means ASCII color values
    // Columns, then rows, then the max color value
    // Pixels are RGB triplets
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
    auto start = std::chrono::system_clock::now();
    for (int j = 0; j < image_height; ++j) {
        std::clog << "\rLines remaining: " << (image_height - j) << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            auto pixel_color = color(double(i)/(image_width - 1), double(j)/(image_height - 1), 0);
            write_color(std::cout, pixel_color);
        }
    }
    auto end = std::chrono::system_clock::now();
    std::clog << "\rFinished render in " <<
    std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms\n";
}