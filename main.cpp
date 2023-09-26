#include "include.h"
#include "camera.h"
#include "hittable_list.h"
#include "sphere.h"

int main() {
    HittableList world;
    world.add(make_shared<Sphere>(Point3(0, 0, -1), 0.5));
    world.add(make_shared<Sphere>(Point3(0, -100.5, -1), 100));
    Camera cam;
    cam.aspect_ratio = 16. / 9.;
    cam.image_width = 400;
    cam.render(world);
}