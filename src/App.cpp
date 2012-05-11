#include "App.h"

#include "ofGraphics.h"
#include "ofAppRunner.h"

#include "Object.h"
#include "Bubble.h"

#define WIND_PERIOD 1
#define WIND_REFLECT_CONE 60
#define WIND_STRENGTH 25, 90

#define BUBBLE_COLOR_DELTA -1.2, 1.2
#define BUBBLE_RADIUS 1, 4.5
#define BUBBLE_LIFETIME 5, 8
#define BUBBLE_VEL -2, 2
#define BUBBLE_ACC -0.3, 0.3
#define BUBBLE_INCR_RANGE 3, 40

#define VID_SPEED 0.3
#define VID_SCALE 2

//--------------------------------------------------------------
App::App()
{
}
//--------------------------------------------------------------
App::~App()
{
    _vid.closeMovie();
}
//--------------------------------------------------------------
void App::setup()
{
    ofBackground(0, 0, 0);
    ofEnableBlendMode(OF_BLENDMODE_ADD);

    //initialize wind
    _windTarget = ofVec2f(0, -80);
    _windTimer = -1;

    //load video
    _vid.loadMovie("anim2.mp4");
    _vid.setSpeed(VID_SPEED);
}
//--------------------------------------------------------------
void App::update()
{
    float elapsed = ofGetLastFrameTime();

    //update wind
    _windTimer -= elapsed;
    if (_windTimer <= 0)
    {
        _windTarget.rotate(ofRandom(180 - WIND_REFLECT_CONE, 180 + WIND_REFLECT_CONE));
        _windTarget.normalize();
        _windTarget *= ofRandom(WIND_STRENGTH);

        _windTimer = WIND_PERIOD;
    }
    Bubble::wind = Bubble::wind + 2*(_windTarget - Bubble::wind)*elapsed;

    //update video
    _vid.update();

    //action!
    Object::updateAll(elapsed);
}
//--------------------------------------------------------------
void App::draw()
{
    //wind, wind target
    /*
    static const ofVec2f pos = ofVec2f(400, 400);
    ofSetColor(ofColor::blue);
    ofLine(pos, pos + _windTarget);
    ofSetColor(ofColor::red);
    ofLine(pos, pos + Bubble::wind);
    */

    //make particles from video
    const ofPixels &pix = _vid.getPixelsRef();
    int w = pix.getWidth();
    int h = pix.getHeight();
    ofColor color;
    for (int i = 0; i < w*VID_SCALE; i += ofRandom(BUBBLE_INCR_RANGE))
        for (int j = 0; j < h*VID_SCALE; j += ofRandom(BUBBLE_INCR_RANGE))
            if ((color = pix.getColor(i/VID_SCALE, j/VID_SCALE)).getLightness() > 128)
            {
                color.r += ofRandom(BUBBLE_COLOR_DELTA);
                color.g += ofRandom(BUBBLE_COLOR_DELTA);
                color.b += ofRandom(BUBBLE_COLOR_DELTA);

                Object::add(new Bubble(ofVec2f(100 + i, 100 + j), ofRandom(BUBBLE_RADIUS), 
                            ofRandom(BUBBLE_LIFETIME), color, 
                            ofVec2f(ofRandom(BUBBLE_VEL), ofRandom(BUBBLE_VEL)), 
                            ofVec2f(ofRandom(BUBBLE_ACC), ofRandom(BUBBLE_ACC))));
            }

    //draw pretty things!
    Object::drawAll();
}
//--------------------------------------------------------------
void App::keyPressed(int key)
{
    //restart video
    _vid.stop();
    _vid.play();
}
//--------------------------------------------------------------
void App::keyReleased(int key)
{
}
//--------------------------------------------------------------
void App::mouseMoved(int x, int y)
{
}
//--------------------------------------------------------------
void App::mouseDragged(int x, int y, int button)
{
}
//--------------------------------------------------------------
void App::mousePressed(int x, int y, int button)
{
}
//--------------------------------------------------------------
void App::mouseReleased(int x, int y, int button)
{
}
//--------------------------------------------------------------
void App::windowResized(int w, int h)
{
}
//--------------------------------------------------------------
