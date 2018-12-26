//
// Created by erik on 22.12.18.
//

#ifndef GAMEPRO_TRANSFORM_H
#define GAMEPRO_TRANSFORM_H


class Transform {
public:
    Transform();
    ~Transform();

private:;
    float x = 0, y = 0;

    float xScale = 1, yScale = 1;
    float rotation = 0;
};


#endif //GAMEPRO_TRANSFORM_H
