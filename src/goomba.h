#include "Villain.h"

class Goomba : public Villain {
public:

    Goomba(float px, float py, Texture texture);

    void render(Vector2 top_left, Vector2 size);

    void update(const Level& level);

private:
    
};