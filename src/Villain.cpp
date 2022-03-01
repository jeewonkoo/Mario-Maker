
#include "Villain.h"
#include <raymath.h>
#include <raylib.h>
#include <algorithm>

Villain::Villain(){}
Villain::Villain(float px, float py, Texture texture) : position({ px, py }), velocity({ 0.05,0 }), tex(texture), initialPosition({ px,py }) {}






