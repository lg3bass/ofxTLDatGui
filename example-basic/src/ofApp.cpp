#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetFrameRate(30);
    ofSetVerticalSync(true);
    
    //on mac lets you use COMMAND+C and COMMAND+V actions
    ofxTimeline::removeCocoaMenusFromGlut("Example Basic");
    
    timeline.setup();
    timeline.setLoopType(OF_LOOP_NORMAL);
    timeline.setDurationInSeconds(30);
    timeline.setShowBPMGrid(true);
    timeline.toggleSnapToBPM();
    timeline.setBPM(120.0);
    
    //create a ofxDatGui track
    ofxTLDatGui* datGuiTrack = new ofxTLDatGui();
    datGuiTrack->setXMLFileName("datguitrack.xml");
    datGuiTrack->track = 1;
    datGuiTrack->page = 1;
    timeline.addTrack("datGuiTrack", datGuiTrack);
    
    
    //ofxOSC
    receiver_timeline.setup(rPORT);
    sender.setup(HOST, sPORT);
    
    
    ofAddListener(OscMessageEvent::events, this, &ofApp::OscSendEvent);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    timeline.draw();
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

//--------------------------------------------------------------
void ofApp::OscSendEvent(OscMessageEvent &e){
    //message originating from ofxTLDatGui
    string value = (e.m.getArgType(1)==OFXOSC_TYPE_FLOAT) ? ofToString(e.m.getArgAsFloat(1)) : ofToString(e.m.getArgAsInt(1));
    
    ofLog() << e.m.getAddress() << " "
            << ofToString(e.m.getArgAsInt(0)) << " "    //_track  -- preformated base 1
            << value;                                   //_value
    
    //send out the OSC
    sender.sendMessage(e.m);
    
}
