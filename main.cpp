#include <iostream>
#include <chrono>
#include "color.h"
#include "vec3.h"
#include "ray.h"

bool contact_sphere(const Point3& center, double radius, const Ray& r) {
    // sphere equation: x^2 + y^2 + z^2 = r^2 (not including position)
    // definition of dot product: P (point) and C (center), (P-C) * (P-C) = r^2
    // test if our ray satisfies the sphere equation (makes contact with sphere)
    Vec3 oc = r.origin() - center;
    auto a = dot(r.direction(), r.direction());
    auto b = 2. * dot(oc, r.direction());
    auto c = dot(oc, oc) - radius*radius;
    auto quadratic = b*b - 4*a*c;
    return (quadratic >= 0);
}

// returns color for a given scene ray
Color ray_color(const Ray& r) {
    // render sample sphere at -1 z, in neutral position
    if (contact_sphere(Point3(0, 0, -1), 0.5, r))
        return Color(0, 1, 0);

    // lerp from white to blue (image will render other way)
    Vec3 unit_direction = unit_vector(r.direction());
    auto magnitude = 0.5 * (unit_direction.y() + 1.);
    // start value white (255, 255, 255), end value blue (75, 156, 211)
    return (1 - magnitude) * Color(1., 1., 1.) + magnitude * Color(0.297, 0.613, 0.828);
    // no relation to UNC i just like carolina blue
}

int main() {
    // image
    auto aspect_ratio = 16. / 9.;
    int image_width = 400;
    // calculate image height using defined aspect ratio and validate
    int image_height = static_cast<int>(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;
    // camera
    auto viewport_height = 2.;
    auto viewport_width = viewport_height * (static_cast<double>(image_width) / image_height);
    auto focal_length = 1.;
    // x goes right, y goes up, -z goes in viewing direction (right handed)
    auto camera_center = Point3(0, 0, 0);
    // define vectors for vertical and horizontal viewport edges
    // vertical render is top to bottom (down), so negative
    auto viewport_u = Vec3(viewport_width, 0, 0);
    auto viewport_v = Vec3(0, -viewport_height, 0);
    // define horizontal and vertical pixel delta vectors (dist between each pixel)
    auto pixel_delta_u = viewport_u / image_width;
    auto pixel_delta_v = viewport_v / image_height;
    // define location of top left pixel
    auto viewport_top_left = camera_center - Vec3(0, 0, focal_length)
                                           - (viewport_u / 2) - (viewport_v / 2);
    // square pixels make this easy
    auto pixel00_location = viewport_top_left + 0.5 * (pixel_delta_u + pixel_delta_v);
    // render
    // PPM standard: P3 means ASCII color values
    // columns, then rows, then the max color value
    // pixels are RGB triplets
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
    auto start = std::chrono::system_clock::now();
    for (int j = 0; j < image_height; ++j) {
        std::clog << "\rLines remaining: " << (image_height - j) << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            // trace rays
            auto pixel_center = pixel00_location + (i * pixel_delta_u) + (j * pixel_delta_v);
            auto ray_direction = pixel_center - camera_center;
            Ray r(pixel_center, ray_direction);
            Color pixel_color = ray_color(r);
            write_color(std::cout, pixel_color);
        }
    }
    auto end = std::chrono::system_clock::now();
    std::clog << "\rFinished render in " <<
    std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms\n";
}