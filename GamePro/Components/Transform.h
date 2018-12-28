//
// Created by erik on 22.12.18.
//

#ifndef GAMEPRO_TRANSFORM_H
#define GAMEPRO_TRANSFORM_H


class Transform {
public:
    Transform();
    ~Transform();

    void increaseX(float value);
    void decreaseX(float value);
    void increaseY(float value);
    void decreaseY(float value);

    float getX() const;

    void setX(float x);

    float getY() const;

    void setY(float y);

    float getXScale() const;

    void setXScale(float xScale);

    float getYScale() const;

    void setYScale(float yScale);

    float getRotation() const;

    void setRotation(float rotation);

private:;
    float x = 0, y = 0;

    float xScale = 1.0, yScale = 1.0;
    float rotation = 0;
};


#endif //GAMEPRO_TRANSFORM_H
