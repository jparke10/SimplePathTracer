#include <iostream>
#include <chrono>

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
            auto r = double(i) / (image_width - 1);
            auto g = double(j) / (image_height - 1);
            auto b = 0;

            int ir = static_cast<int>(255.999 * r);
            int ig = static_cast<int>(255.999 * g);
            int ib = static_cast<int>(255.999 * b);

            std::cout << ir << ' ' << ig << ' ' << ib << '\n';
        }
    }
    auto end = std::chrono::system_clock::now();
    std::clog << "\rFinished render in " <<
    std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms\n";
}