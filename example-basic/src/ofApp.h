#pragma once

#include "ofMain.h"
#include "ofxTimeline.h"
#include "ofxTLDatGui.h"

#define HOST "localhost"
#define rPORT 7006 //recieve port
#define sPORT 7005 //send port

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    #pragma mark - ofxTimeline
        ofxTimeline timeline;
		
    
    #pragma mark - ofxOsc
        ofxOscReceiver receiver_timeline;
        ofxOscSender sender;

        //send out the OSC
        void OscSendEvent(OscMessageEvent &e);
    
};
