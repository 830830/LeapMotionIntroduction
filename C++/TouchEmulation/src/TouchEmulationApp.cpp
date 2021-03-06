#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"

#include "Leap.h"
#include "LeapMath.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class TouchEmulationApp : public AppNative {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();

private:
    static const int windowWidth = 800;
    static const int windowHeight = 800;
    Leap::Controller leap;
};
void TouchEmulationApp::setup()
{
    this->setWindowSize(windowWidth, windowHeight);
    this->setFrameRate(120);
    gl::enableAlphaBlending();
}

void TouchEmulationApp::mouseDown( MouseEvent event )
{
}

void TouchEmulationApp::update()
{
}

void TouchEmulationApp::draw()
{
    gl::clear( Color( .97, .93, .79 ) );
    Leap::PointableList pointables = leap.frame().pointables();
    Leap::InteractionBox iBox = leap.frame().interactionBox();

    for( int p = 0; p < pointables.count(); p++ )
    {
        Leap::Pointable pointable = pointables[p];
        Leap::Vector normalizedPosition = iBox.normalizePoint(pointable.stabilizedTipPosition());
        float x = normalizedPosition.x * windowWidth;
        float y = windowHeight - normalizedPosition.y * windowHeight;

        auto distance = pointable.touchDistance();
        auto zone = pointable.touchZone();

        {
            std::stringstream ss;
            ss << "distance : " << distance << ", zone : " << zone << std::endl;
            ::OutputDebugStringA( ss.str().c_str() );
        }

        if(pointable.touchDistance() > 0 && pointable.touchZone() != Leap::Pointable::Zone::ZONE_NONE)
        {
            gl::color(0, 1, 0, 1 - pointable.touchDistance());
        }
        else if(pointable.touchDistance() <= 0)
        {
            gl::color(1, 0, 0, -pointable.touchDistance());
        }
        else
        {
            gl::color(0, 0, 1, .05);
        }

        gl::drawSolidCircle(Vec2f(x,y), 40);
    }
}

CINDER_APP_NATIVE( TouchEmulationApp, RendererGl )
