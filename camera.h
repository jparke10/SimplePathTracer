#ifndef CAMERA_H
#define CAMERA_H

#include <iostream>
#include <chrono>
#include "include.h"
#include "color.h"
#include "hittable.h"

class Camera {
    private:
        int image_height;
        Point3 center;
        Point3 pixel00_loc;
        Vec3 pixel_delta_u;
        Vec3 pixel_delta_v;
        void initialize() {
            // calculate image height using defined aspect ratio and validate
            image_height = static_cast<int>(image_width / aspect_ratio);
            image_height = (image_height < 1) ? 1 : image_height;
            // x goes right, y goes up, -z goes in viewing direction (right handed)
            center = Point3(0, 0, 0);
            // define viewport dimensions
            auto focal_length = 1.;
            auto viewport_height = 2.;
            auto viewport_width = viewport_height * (static_cast<double>(image_width)/image_height);
            // define vectors for vertical and horizontal viewport edges
            // vertical render is top to bottom (down), so negative
            auto viewport_u = Vec3(viewport_width, 0, 0);
            auto viewport_v = Vec3(0, -viewport_height, 0);
            // define horizontal and vertical pixel delta vectors (dist between each pixel)
            pixel_delta_u = viewport_u / image_width;
            pixel_delta_v = viewport_v / image_height;
            // define location of top left pixel
            auto viewport_upper_left = center - Vec3(0, 0, focal_length) - viewport_u / 2 -
                                       viewport_v / 2;
            // square pixels make this easy
            pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
        }
        // returns color for a given scene ray
        Color ray_color(const Ray& r, const Hittable& world) {
            // render sample sphere at -1 z, in neutral position
            HitRecord rec;
            if (world.hit(r, Interval(0, infinity), rec)) {
                return 0.5 * (rec.normal + Color(1, 1, 1));
            }
            // lerp from white to blue (image will render other way)
            Vec3 unit_direction = unit_vector(r.direction());
            auto magnitude = 0.5 * (unit_direction.y() + 1.);
            // start value white (255, 255, 255), end value blue (75, 156, 211)
            return (1 - magnitude) * Color(1., 1., 1.) + magnitude * Color(0.297, 0.613, 0.828);
            // no relation to UNC i just like carolina blue
        }
    public:
        double aspect_ratio = 1.;
        int image_width = 100;
        void render(const Hittable& world) {
            initialize();
            // PPM standard: P3 means ASCII color values
            // columns, then rows, then the max color value
            // pixels are RGB triplets
            std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
            auto start = std::chrono::system_clock::now();
            for (int j = 0; j < image_height; ++j) {
                std::clog << "\rLines remaining: " << (image_height - j) << ' ' << std::flush;
                for (int i = 0; i < image_width; ++i) {
                    // trace rays
                    auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
                    auto ray_direction = pixel_center - center;
                    Ray r(center, ray_direction);
                    Color pixel_color = ray_color(r, world);
                    write_color(std::cout, pixel_color);
                }
            }
            auto end = std::chrono::system_clock::now();
            std::clog << "\rFinished render in " <<
            std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms\n";
        }
};

#endif