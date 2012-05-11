#include "App.h"

#include "ofGraphics.h"
#include "ofAppRunner.h"

#include "Object.h"
#include "Bubble.h"

//--------------------------------------------------------------
App::App()
{
}
//--------------------------------------------------------------
void App::setup()
{
    ofBackground(0, 0, 0);
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);

    _wind = ofVec2f(0, -40);

    ofLoadImage(_pix, "img1.jpg");
}
//--------------------------------------------------------------
void App::update()
{
    float elapsed = ofGetLastFrameTime();

    //rotating wind
    _wind.rotate(110 * elapsed);
    Bubble::wind = _wind;

    //action!
    Object::updateAll(elapsed);
}
//--------------------------------------------------------------
void App::draw()
{
    //draw wind direction
    static const ofVec2f pos = ofVec2f(400, 400);
    ofSetColor(ofColor::red);
    ofLine(pos, pos + 45*_wind.getNormalized());

    //draw pretty things
    Object::drawAll();
}
//--------------------------------------------------------------
void App::keyPressed(int key)
{
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
    int w = _pix.getWidth();
    int h = _pix.getHeight();

    x -= w / 2;
    y -= h / 2;

#define BUBBLE_RADIUS 2, 4
#define BUBBLE_LIFETIME 4, 8
#define BUBBLE_VEL -20, 20
#define BUBBLE_ACC -1, 1
#define INCR_RANGE 3, 30
    for (int i = 0; i < w; i += ofRandom(INCR_RANGE))
        for (int j = 0; j < h; j += ofRandom(INCR_RANGE))
            if (_pix.getColor(i, j).getLightness() > 128)
                Object::add(new Bubble(ofVec2f(x + i, y + j), ofRandom(BUBBLE_RADIUS), 
                            ofRandom(BUBBLE_LIFETIME), ofColor::white, 
                            ofVec2f(ofRandom(BUBBLE_VEL), ofRandom(BUBBLE_VEL)), 
                            ofVec2f(ofRandom(BUBBLE_ACC), ofRandom(BUBBLE_ACC))));
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
