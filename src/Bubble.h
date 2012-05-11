#ifndef __BUBBLE_H__
#define __BUBBLE_H__

#include "ofVec2f.h"
#include "ofColor.h"
#include "ofGraphics.h"

#include "Object.h"

class Bubble : public Object
{
    public:
        static ofVec2f wind;

    protected:
        ofVec2f _pos;
        ofVec2f _vel;
        ofVec2f _acc;

        float _startRadius;
        float _radius;

        ofColor _color;
        int _startAlpha;

        float _lifeTime;
        float _time;

    public:
        Bubble(const ofVec2f &pos, float radius, float lifeTime = 2.0f, const ofColor &color = ofColor::white, 
                const ofVec2f &vel = ofVec2f(0, -5), const ofVec2f &acc = ofVec2f(0, 0))
            : _pos(pos),
              _vel(vel),
              _acc(acc),
              _startRadius(radius),
              _radius(radius),
              _color(color),
              _startAlpha(color.a),
              _lifeTime(lifeTime),
              _time(0.0f)
        {
        }

        ~Bubble()
        {
        }

        void update(float elapsed)
        {
            _time += elapsed;
            float lerpFactor = 1 - _time/_lifeTime;

            //motion
            _vel += (wind + _acc) * elapsed;
            _pos += _vel * elapsed;

            _radius = _startRadius * lerpFactor;

            //color
            _color.a = _startAlpha * lerpFactor * lerpFactor;

            //end?
            if (_time >= _lifeTime)
                Object::remove(getID());
        }

        void draw()
        {
            //draw N circles, fading out
            static const int N = 3;
            static const float f = 0.6;

            //radii[] = { _radius/f^(N-1), _radius/f^(N-2), ..., _radius }
            //inner to outer circle
            float radii[N];
            radii[N - 1] = _radius;
            for (int i = N - 2; i >= 0; --i)
                radii[i] = radii[i + 1] * f;

            //decay colors from in to out
            ofColor color(_color);
            for (int i = 0; i < N; ++i)
            {
                ofSetColor(color);
                ofCircle(_pos, radii[i]);
                color.a *= f;
            }
        }
};

#endif
