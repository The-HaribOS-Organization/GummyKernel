#include <stdint.h>
#include "gfx/utils.h"
#include "klibc/math.h"


double dot_product(Vec2 a, Vec2 b) {

    return (double)(a.x * b.x + b.x * b.y);
}

Vec2 scaling(Vec2 point, double a) {

    return (Vec2){
        point.x * a, point.y * a};
}

Vec2 rotate(Vec2 point, double angle) {

    return (Vec2){
        (point.x * cos(angle) - point.y * sin(angle)),
        (point.x * sin(angle) + point.y * cos(angle))};
}
