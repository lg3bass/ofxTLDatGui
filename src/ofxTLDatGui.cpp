/**
 * ofxTimeline
 * openFrameworks graphical timeline addon
 *
 * Copyright (c) 2011-2012 James George
 * Development Supported by YCAM InterLab http://interlab.ycam.jp/en/
 * http://jamesgeorge.org + http://flightphase.com
 * http://github.com/obviousjim + http://github.com/flightphase
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#include "ofxTLDatGui.h"
#include "ofxTimeline.h"

// setup the events to pass back
ofEvent <OscMessageEvent> OscMessageEvent::events;

//================================================================================
ofxTLDatGui::ofxTLDatGui(){
    
    clip = 0;
    
    //flag to accept gui events.
    guiAcceptEvents = true;
    
    for(int i=0;i<10;i++){
        clipParams c;
        c.playNoteOff = false;
        c.playAll = false;
        c.mirror = false;
        c.mirrorX = false;
        c.mirrorY = false;
        c.mirrorZ = false;
        c.OSCsetMatCap = 1;
        c.OSCsetTrack = 1;
        c.localSlices = 1;
        c.localCopies = 12;
        c.globalCopies = 1;
        c.mirrorDistance = 0.0;
        c.setGlobalRotX = 0.0;
        c.setGlobalRotY = 0.0;
        c.setGlobalRotZ = 0.0;
        c.setGlobalTransX = 0.0;
        c.setGlobalTransY = 0.0;
        c.setGlobalTransZ = 0.0;
        
        c.setLocalRotX = 0.0;
        c.setLocalRotY = 0.0;
        c.setLocalRotZ = 0.0;
        c.setLocalTransX = 0.0;
        c.setLocalTransY = 0.0;
        c.setLocalTransZ = 0.0;
        
        c.setObjRotX = 0.0;
        c.setObjRotY = 0.0;
        c.setObjRotZ = 0.0;
        
        c.localScale = 0.0;
        c.globalScale = 0.0;
        
        clips.push_back(c);
    }
    
    //setup all my params
    OSCsetMatCap.set("OSCsetMatCap",clips[clip].OSCsetMatCap,1,42);
    OSCsetTrack.set("OSCsetTrack",clips[clip].OSCsetTrack,1,25);
    localSlices.set("localSlices",clips[clip].localSlices,1,4);
    localCopies.set("localCopies",clips[clip].localCopies,1,12);
    globalCopies.set("globalCopies",clips[clip].globalCopies,1,12);
    mirrorDistance.set("mirrorDistance",clips[clip].mirrorDistance,-100.0,100.0);
    
    playNoteOff = clips[clip].playNoteOff;
    playAll = clips[clip].playAll;
    mirror = clips[clip].mirror;
    mirrorX = clips[clip].mirrorX;
    mirrorY = clips[clip].mirrorY;
    mirrorZ = clips[clip].mirrorZ;
    
    setGlobalRotX.set("setGlobalRotX",clips[clip].setGlobalRotX,-180,180);
    setGlobalRotY.set("setGlobalRotY",clips[clip].setGlobalRotY,-180,180);
    setGlobalRotZ.set("setGlobalRotZ",clips[clip].setGlobalRotZ,-180,180);
    
    setGlobalTransX.set("setGlobalTransX",clips[clip].setGlobalTransX,-100,100);
    setGlobalTransY.set("setGlobalTransY",clips[clip].setGlobalTransY,-100,100);
    setGlobalTransZ.set("setGlobalTransZ",clips[clip].setGlobalTransZ,-100,100);

    setLocalRotX.set("setLocalRotX",clips[clip].setLocalRotX,-180,180);
    setLocalRotY.set("setLocalRotY",clips[clip].setLocalRotY,-180,180);
    setLocalRotZ.set("setLocalRotZ",clips[clip].setLocalRotZ,-180,180);
    
    setLocalTransX.set("setLocalTransX",clips[clip].setLocalTransX,-100,100);
    setLocalTransY.set("setLocalTransY",clips[clip].setLocalTransY,-100,100);
    setLocalTransZ.set("setLocalTransZ",clips[clip].setLocalTransZ,-100,100);
    
    setObjRotX.set("setObjRotX",clips[clip].setObjRotX,-180,180);
    setObjRotY.set("setObjRotY",clips[clip].setObjRotY,-180,180);
    setObjRotZ.set("setObjRotZ",clips[clip].setObjRotZ,-180,180);
    
    localScale.set("localScale",clips[clip].localScale,0.1,10.0);
    globalScale.set("globalScale",clips[clip].globalScale,1.0,50.0);
    
    
    //create all the gui components.
    setupTrack();
}

ofxTLDatGui::~ofxTLDatGui(){

    trackGuiDelete();
}


//ofxDatGui setup elements
//--------------------------------------------------------------
void ofxTLDatGui::setupTrack(){
    
    //column 1
    playNoteOffToggle = new ofxDatGuiToggle("playNoteOff", playNoteOff);
    playNoteOffToggle->setWidth(tglW);
    playNoteOffToggle->onButtonEvent(this, &ofxTLDatGui::trackGuiButtonEvent);
    
    playAllToggle = new ofxDatGuiToggle("playAll", playAll);
    playAllToggle->setWidth(tglW);
    playAllToggle->onButtonEvent(this, &ofxTLDatGui::trackGuiButtonEvent);
    
    mirrorToggle = new ofxDatGuiToggle("mirror", mirror);
    mirrorToggle->setWidth(tglW);
    mirrorToggle->onButtonEvent(this, &ofxTLDatGui::trackGuiButtonEvent);
    
    mirrorXToggle = new ofxDatGuiToggle("mirrorX", mirrorX);
    mirrorXToggle->setWidth(tglW);
    mirrorXToggle->onButtonEvent(this, &ofxTLDatGui::trackGuiButtonEvent);
    
    mirrorYToggle = new ofxDatGuiToggle("mirrorY", mirrorY);
    mirrorYToggle->setWidth(tglW);
    mirrorYToggle->onButtonEvent(this, &ofxTLDatGui::trackGuiButtonEvent);
    
    mirrorZToggle = new ofxDatGuiToggle("mirrorZ", mirrorZ);
    mirrorZToggle->setWidth(tglW);
    mirrorZToggle->onButtonEvent(this, &ofxTLDatGui::trackGuiButtonEvent);
    
    //column 2
    OSCsetMatCapSlider = new ofxDatGuiSlider(OSCsetMatCap);
    OSCsetMatCapSlider->setLabelMargin(10.0);
    OSCsetMatCapSlider->setWidth(compW, 80.0);
    OSCsetMatCapSlider->onSliderEvent(this, &ofxTLDatGui::trackGuiSliderEvent);
    
    OSCsetTrackSlider = new ofxDatGuiSlider(OSCsetTrack);
    OSCsetTrackSlider->setLabelMargin(10.0);
    OSCsetTrackSlider->setWidth(compW, 80.0);
    OSCsetTrackSlider->onSliderEvent(this, &ofxTLDatGui::trackGuiSliderEvent);
    
    localSlicesSlider = new ofxDatGuiSlider(localSlices);
    localSlicesSlider->setLabelMargin(10.0);
    localSlicesSlider->setWidth(compW, 80.0);
    localSlicesSlider->onSliderEvent(this, &ofxTLDatGui::trackGuiSliderEvent);
    
    localCopiesSlider = new ofxDatGuiSlider(localCopies);
    localCopiesSlider->setLabelMargin(10.0);
    localCopiesSlider->setWidth(compW, 80.0);
    localCopiesSlider->onSliderEvent(this, &ofxTLDatGui::trackGuiSliderEvent);
    
    globalCopiesSlider = new ofxDatGuiSlider(globalCopies);
    globalCopiesSlider->setLabelMargin(10.0);
    globalCopiesSlider->setWidth(compW, 80.0);
    globalCopiesSlider->onSliderEvent(this, &ofxTLDatGui::trackGuiSliderEvent);
    
    mirrorDistanceSlider = new ofxDatGuiSlider(mirrorDistance);
    mirrorDistanceSlider->setLabelMargin(10.0);
    mirrorDistanceSlider->setWidth(compW, 80.0);
    mirrorDistanceSlider->onSliderEvent(this, &ofxTLDatGui::trackGuiSliderEvent);
    
    //column 3
    setGlobalRotXSlider = new ofxDatGuiSlider(setGlobalRotX);
    setGlobalRotXSlider->setLabelMargin(10.0);
    setGlobalRotXSlider->setWidth(compW, 80.0);
    setGlobalRotXSlider->onSliderEvent(this, &ofxTLDatGui::trackGuiSliderEvent);
    
    setGlobalRotYSlider = new ofxDatGuiSlider(setGlobalRotY);
    setGlobalRotYSlider->setLabelMargin(10.0);
    setGlobalRotYSlider->setWidth(compW, 80.0);
    setGlobalRotYSlider->onSliderEvent(this, &ofxTLDatGui::trackGuiSliderEvent);
    
    setGlobalRotZSlider = new ofxDatGuiSlider(setGlobalRotZ);
    setGlobalRotZSlider->setLabelMargin(10.0);
    setGlobalRotZSlider->setWidth(compW, 80.0);
    setGlobalRotZSlider->onSliderEvent(this, &ofxTLDatGui::trackGuiSliderEvent);
    
    setGlobalTransXSlider = new ofxDatGuiSlider(setGlobalTransX);
    setGlobalTransXSlider->setLabelMargin(10.0);
    setGlobalTransXSlider->setWidth(compW, 80.0);
    setGlobalTransXSlider->onSliderEvent(this, &ofxTLDatGui::trackGuiSliderEvent);
    
    setGlobalTransYSlider = new ofxDatGuiSlider(setGlobalTransY);
    setGlobalTransYSlider->setLabelMargin(10.0);
    setGlobalTransYSlider->setWidth(compW, 80.0);
    setGlobalTransYSlider->onSliderEvent(this, &ofxTLDatGui::trackGuiSliderEvent);
    
    setGlobalTransZSlider = new ofxDatGuiSlider(setGlobalTransZ);
    setGlobalTransZSlider->setLabelMargin(10.0);
    setGlobalTransZSlider->setWidth(compW, 80.0);
    setGlobalTransZSlider->onSliderEvent(this, &ofxTLDatGui::trackGuiSliderEvent);
    
    //column 4
    setLocalRotXSlider = new ofxDatGuiSlider(setLocalRotX);
    setLocalRotXSlider->setLabelMargin(10.0);
    setLocalRotXSlider->setWidth(compW, 80.0);
    setLocalRotXSlider->onSliderEvent(this, &ofxTLDatGui::trackGuiSliderEvent);
    
    setLocalRotYSlider = new ofxDatGuiSlider(setLocalRotY);
    setLocalRotYSlider->setLabelMargin(10.0);
    setLocalRotYSlider->setWidth(compW, 80.0);
    setLocalRotYSlider->onSliderEvent(this, &ofxTLDatGui::trackGuiSliderEvent);
    
    setLocalRotZSlider = new ofxDatGuiSlider(setLocalRotZ);
    setLocalRotZSlider->setLabelMargin(10.0);
    setLocalRotZSlider->setWidth(compW, 80.0);
    setLocalRotZSlider->onSliderEvent(this, &ofxTLDatGui::trackGuiSliderEvent);
    
    setLocalTransXSlider = new ofxDatGuiSlider(setLocalTransX);
    setLocalTransXSlider->setLabelMargin(10.0);
    setLocalTransXSlider->setWidth(compW, 80.0);
    setLocalTransXSlider->onSliderEvent(this, &ofxTLDatGui::trackGuiSliderEvent);
    
    setLocalTransYSlider = new ofxDatGuiSlider(setLocalTransY);
    setLocalTransYSlider->setLabelMargin(10.0);
    setLocalTransYSlider->setWidth(compW, 80.0);
    setLocalTransYSlider->onSliderEvent(this, &ofxTLDatGui::trackGuiSliderEvent);
    
    setLocalTransZSlider = new ofxDatGuiSlider(setLocalTransZ);
    setLocalTransZSlider->setLabelMargin(10.0);
    setLocalTransZSlider->setWidth(compW, 80.0);
    setLocalTransZSlider->onSliderEvent(this, &ofxTLDatGui::trackGuiSliderEvent);
    
    //column 5
    setObjRotXSlider = new ofxDatGuiSlider(setObjRotX);
    setObjRotXSlider->setLabelMargin(10.0);
    setObjRotXSlider->setWidth(compW, 80.0);
    setObjRotXSlider->onSliderEvent(this, &ofxTLDatGui::trackGuiSliderEvent);
    
    setObjRotYSlider = new ofxDatGuiSlider(setObjRotY);
    setObjRotYSlider->setLabelMargin(10.0);
    setObjRotYSlider->setWidth(compW, 80.0);
    setObjRotYSlider->onSliderEvent(this, &ofxTLDatGui::trackGuiSliderEvent);
    
    setObjRotZSlider = new ofxDatGuiSlider(setObjRotZ);
    setObjRotZSlider->setLabelMargin(10.0);
    setObjRotZSlider->setWidth(compW, 80.0);
    setObjRotZSlider->onSliderEvent(this, &ofxTLDatGui::trackGuiSliderEvent);
    
    localScaleSlider = new ofxDatGuiSlider(localScale);
    localScaleSlider->setLabelMargin(10.0);
    localScaleSlider->setWidth(compW, 80.0);
    localScaleSlider->onSliderEvent(this, &ofxTLDatGui::trackGuiSliderEvent);
    
    globalScaleSlider = new ofxDatGuiSlider(globalScale);
    globalScaleSlider->setLabelMargin(10.0);
    globalScaleSlider->setWidth(compW, 80.0);
    globalScaleSlider->onSliderEvent(this, &ofxTLDatGui::trackGuiSliderEvent);
}

//--------------------------------------------------------------
void ofxTLDatGui::setClipParams(int c){
    
    clip = c;
    
    playNoteOff = clips[clip].playNoteOff;
    playNoteOffToggle->setEnabled(clips[clip].playNoteOff);
    
    playAll = clips[clip].playAll;
    playAllToggle->setEnabled(clips[clip].playAll);
    
    mirror = clips[clip].mirror;
    mirrorToggle->setEnabled(clips[clip].mirror);
    
    mirrorX = clips[clip].mirrorX;
    mirrorXToggle->setEnabled(clips[clip].mirrorX);
    
    mirrorY = clips[clip].mirrorY;
    mirrorYToggle->setEnabled(clips[clip].mirrorY);
    
    mirrorZ = clips[clip].mirrorZ;
    mirrorZToggle->setEnabled(clips[clip].mirrorZ);
    
    OSCsetMatCap.set(clips[clip].OSCsetMatCap);
    OSCsetTrack.set(clips[clip].OSCsetTrack);
    localSlices.set(clips[clip].localSlices);
    localScale.set(clips[clip].localScale);
    localCopies.set(clips[clip].localCopies);
    globalCopies.set(clips[clip].globalCopies);
    mirrorDistance.set(clips[clip].mirrorDistance);
    setGlobalRotX.set(clips[clip].setGlobalRotX);
    setGlobalRotY.set(clips[clip].setGlobalRotY);
    setGlobalRotZ.set(clips[clip].setGlobalRotZ);
    
    setGlobalTransX.set(clips[clip].setGlobalTransX);
    setGlobalTransY.set(clips[clip].setGlobalTransY);
    setGlobalTransZ.set(clips[clip].setGlobalTransZ);
    
    setLocalRotX.set(clips[clip].setLocalRotX);
    setLocalRotY.set(clips[clip].setLocalRotY);
    setLocalRotZ.set(clips[clip].setLocalRotZ);
    
    setLocalTransX.set(clips[clip].setLocalTransX);
    setLocalTransY.set(clips[clip].setLocalTransY);
    setLocalTransZ.set(clips[clip].setLocalTransZ);
    
    setObjRotX.set(clips[clip].setObjRotX);
    setObjRotY.set(clips[clip].setObjRotY);
    setObjRotZ.set(clips[clip].setObjRotZ);
    
    localScale.set(clips[clip].localScale);
    globalScale.set(clips[clip].globalScale);
    
    
    ofLog() << "ofxTLDatGui::setClipParams(int c) - current clip: " << clip;
}

//--------------------------------------------------------------
void ofxTLDatGui::saveClipXML(int c){
    
}

//--------------------------------------------------------------
void ofxTLDatGui::loadClipXML(string filePath, int c){
    
    /*
    string savedClipSettingsPath = "";
    
    if(ofSplitString(getXMLFilePath(),"/").size() > 1){
        //we have set a project and loaded already.  The file path should be set on the timelines.
        savedClipSettingsPath = getXMLFilePath();
        
    } else {
        //if getXMLFilePath() only returns the fileaname
        //consider we are loading first time and construct filepath.
        savedClipSettingsPath = filePath + getXMLFilePath();
    }
    */
    
    string savedClipSettingsPath = filePath + "VMM.xml";
    ofxXmlSettings savedVMMSettings;

    if(ofFile(savedClipSettingsPath).exists()){
        //ofLogVerbose("LOAD") << "savedClipSettingsPath: " << savedClipSettingsPath << " EXISTS!!!!";

        if( savedVMMSettings.loadFile(savedClipSettingsPath) ){
            ofLogVerbose("LOAD") << savedClipSettingsPath;
            
            bool VMM_playNoteOff = savedVMMSettings.getValue("VMM:playNoteOff", 0);
            clips[c].playNoteOff = VMM_playNoteOff;
            
            bool VMM_playAll = savedVMMSettings.getValue("VMM:playAll", 0);
            clips[c].playAll = VMM_playAll;
            
            bool VMM_mirror = savedVMMSettings.getValue("VMM:mirror", 0);
            clips[c].mirror = VMM_mirror;
            
            bool VMM_mirrorX = savedVMMSettings.getValue("VMM:mirrorX", 0);
            clips[c].mirrorX = VMM_mirrorX;
            
            bool VMM_mirrorY = savedVMMSettings.getValue("VMM:mirrorY", 0);
            clips[c].mirrorY = VMM_mirrorY;
            
            bool VMM_mirrorZ = savedVMMSettings.getValue("VMM:mirrorZ", 0);
            clips[c].mirrorZ = VMM_mirrorZ;
            
            //update the params
            int VMM_OSCsetMatCap = savedVMMSettings.getValue("VMM:OSCsetMatCap", 0);
            clips[c].OSCsetMatCap = VMM_OSCsetMatCap;
            
            int VMM_OSCsetTrack = savedVMMSettings.getValue("VMM:OSCsetTrack", 0);
            clips[c].OSCsetTrack = VMM_OSCsetTrack;
            
            int VMM_localSlices = savedVMMSettings.getValue("VMM:localSlices", 0);
            clips[c].localSlices = VMM_localSlices;

            int VMM_localCopies = savedVMMSettings.getValue("VMM:localCopies", 0);
            clips[c].localCopies = VMM_localCopies;

            int VMM_globalCopies = savedVMMSettings.getValue("VMM:globalCopies", 0);
            clips[c].globalCopies = VMM_globalCopies;
            
            float VMM_mirrorDistance = savedVMMSettings.getValue("VMM:mirrorDistance", 0.0);
            clips[c].mirrorDistance = VMM_mirrorDistance;
            
            float VMM_setGlobalRotX = savedVMMSettings.getValue("VMM:setGlobalRotX", 0.0);
            clips[c].setGlobalRotX = VMM_setGlobalRotX;

            float VMM_setGlobalRotY = savedVMMSettings.getValue("VMM:setGlobalRotY", 0.0);
            clips[c].setGlobalRotY = VMM_setGlobalRotY;
        
            float VMM_setGlobalRotZ = savedVMMSettings.getValue("VMM:setGlobalRotZ", 0.0);
            clips[c].setGlobalRotZ = VMM_setGlobalRotZ;
            
            float VMM_setGlobalTransX = savedVMMSettings.getValue("VMM:setGlobalTransX", 0.0);
            clips[c].setGlobalTransX = VMM_setGlobalTransX;

            float VMM_setGlobalTransY = savedVMMSettings.getValue("VMM:setGlobalTransY", 0.0);
            clips[c].setGlobalTransY = VMM_setGlobalTransY;

            float VMM_setGlobalTransZ = savedVMMSettings.getValue("VMM:setGlobalTransZ", 0.0);
            clips[c].setGlobalTransZ = VMM_setGlobalTransZ;

            float VMM_setLocalRotX = savedVMMSettings.getValue("VMM:setLocalRotX", 0.0);
            clips[c].setLocalRotX = VMM_setLocalRotX;

            float VMM_setLocalRotY = savedVMMSettings.getValue("VMM:setLocalRotY", 0.0);
            clips[c].setLocalRotY = VMM_setLocalRotY;

            float VMM_setLocalRotZ = savedVMMSettings.getValue("VMM:setLocalRotZ", 0.0);
            clips[c].setLocalRotZ = VMM_setLocalRotZ;

            float VMM_setLocalTransX = savedVMMSettings.getValue("VMM:setLocalTransX", 0.0);
            clips[c].setLocalTransX = VMM_setLocalTransX;
            
            float VMM_setLocalTransY = savedVMMSettings.getValue("VMM:setLocalTransY", 0.0);
            clips[c].setLocalTransY = VMM_setLocalTransY;

            float VMM_setLocalTransZ = savedVMMSettings.getValue("VMM:setLocalTransZ", 0.0);
            clips[c].setLocalTransZ = VMM_setLocalTransZ;

            float VMM_setObjRotX = savedVMMSettings.getValue("VMM:setObjRotX", 0.0);
            clips[c].setObjRotX = VMM_setObjRotX;
            
            float VMM_setObjRotY = savedVMMSettings.getValue("VMM:setObjRotY", 0.0);
            clips[c].setObjRotY = VMM_setObjRotY;

            float VMM_setObjRotZ = savedVMMSettings.getValue("VMM:setObjRotZ", 0.0);
            clips[c].setObjRotZ = VMM_setObjRotZ;
            
            float VMM_localScale = savedVMMSettings.getValue("VMM:localScale", 0.0);
            clips[c].localScale = VMM_localScale;

            float VMM_globalScale = savedVMMSettings.getValue("VMM:globalScale", 0.0);
            clips[c].globalScale = VMM_globalScale;
            
            
            
            //DEBUG - output all the loaded params
            //coutTrackParams(c);
            
        }else{
            ofLogError("LOAD") <<  "ofxTLDatGui::load() - unable to load: " << savedClipSettingsPath ;
            return;
        }
    }
}


//use this if you want the ofxDatGuiButton to behave like a toggle.
//--------------------------------------------------------------
void ofxTLDatGui::setButtonToggle(ofxDatGuiButton *_button, bool &val){
    
    val = !val;
    
    if(val){
        _button->setBackgroundColor(ofColor(255,0,0));
        cout << "drive on" << endl;
    } else {
        _button->setBackgroundColor(ofColor(0,0,0));
        cout << "drive off" << endl;
        
    }
}


//BUTTON EVENTS
//--------------------------------------------------------------
void ofxTLDatGui::trackGuiButtonEvent(ofxDatGuiButtonEvent e){
    
    //register all the boolean toggles.
    if(e.target->is("playNoteOff")){
        
        //ofxDatGuiButton (as toggle) - sample code
        //setButtonToggle(e.target, playNoteOff);
        //sendOSC("playNoteOff", playNoteOff);
        
        //ofxDatGuiToggle
        bool playNoteOffStatus = e.target->getEnabled();
        
        playNoteOff = clips[clip].playNoteOff = playNoteOffStatus;
        sendOSC("playNoteOff", playNoteOff);
        
    } else if (e.target->is("playAll")){
        
        bool playAllTglStatus = e.target->getEnabled();
        
        playAll = clips[clip].playAll = playAllTglStatus;
        sendOSC("playAll", playAll);
    } else if (e.target->is("mirror")){
        
        bool mirrorTglStatus = e.target->getEnabled();
        
        mirror = clips[clip].mirror = mirrorTglStatus;
        sendOSC("mirror", mirror);
        
    } else if (e.target->is("mirrorX")){
        
        bool mirrorXTglStatus = e.target->getEnabled();
        
        mirrorX = clips[clip].mirrorX = mirrorXTglStatus;
        sendOSC("mirrorX", mirrorX);
        
    } else if (e.target->is("mirrorY")){
        
        bool mirrorYTglStatus = e.target->getEnabled();
        
        mirrorY = clips[clip].mirrorY = mirrorYTglStatus;
        sendOSC("mirrorY", mirrorY);
        
    } else if (e.target->is("mirrorZ")){
        
        bool mirrorZTglStatus = e.target->getEnabled();
        
        mirrorZ = clips[clip].mirrorZ = mirrorZTglStatus;
        sendOSC("mirrorZ", mirrorZ);
        
    }    //...add more
    
}

//SLIDER EVENTS
//--------------------------------------------------------------
void ofxTLDatGui::trackGuiSliderEvent(ofxDatGuiSliderEvent e){

    /*
    if(e.target->getName() == "localCopies"){

        float angle = 360.0/e.target->getValue();
        setLocalRotZ.set(angle);

    }
    */
    
    if (e.target->getName() == "OSCsetMatCap"){
        
        clips[clip].OSCsetMatCap = e.target->getValue();
        OSCsetMatCap.set(clips[clip].OSCsetMatCap);
        
    } else if (e.target->getName() == "OSCsetTrack"){
        
        clips[clip].OSCsetTrack = e.target->getValue();
        OSCsetTrack.set(clips[clip].OSCsetTrack);
    
    } else if (e.target->getName() == "localSlices"){
        
        clips[clip].localSlices = e.target->getValue();
        localSlices.set(clips[clip].localSlices);
        
    } else if (e.target->getName() == "localCopies"){
        
        
        clips[clip].localCopies = e.target->getValue();
        localCopies.set(clips[clip].localCopies);
        
        
        float angle = 360.0/e.target->getValue();
        clips[clip].setLocalRotZ = angle;
        setLocalRotZ.set(angle);
        
    } else if (e.target->getName() == "globalCopies"){
        
        clips[clip].globalCopies = e.target->getValue();
        globalCopies.set(clips[clip].globalCopies);
        
    } else if (e.target->getName() == "mirrorDistance"){
        
        clips[clip].mirrorDistance = e.target->getValue();
        mirrorDistance.set(clips[clip].mirrorDistance);
        
    } else if (e.target->getName() == "setGlobalRotX"){
        
        clips[clip].setGlobalRotX = e.target->getValue();
        setGlobalRotX.set(clips[clip].setGlobalRotX);
        
    } else if (e.target->getName() == "setGlobalRotY"){
        
        clips[clip].setGlobalRotY = e.target->getValue();
        setGlobalRotY.set(clips[clip].setGlobalRotY);
        
    } else if (e.target->getName() == "setGlobalRotZ"){
        
        clips[clip].setGlobalRotZ = e.target->getValue();
        setGlobalRotZ.set(clips[clip].setGlobalRotZ);
        
    } else if (e.target->getName() == "setGlobalTransX"){
        
        clips[clip].setGlobalTransX = e.target->getValue();
        setGlobalTransX.set(clips[clip].setGlobalTransX);
        
    } else if (e.target->getName() == "setGlobalTransY"){
        
        clips[clip].setGlobalTransY = e.target->getValue();
        setGlobalTransY.set(clips[clip].setGlobalTransY);
        
    } else if (e.target->getName() == "setGlobalTransZ"){
        
        clips[clip].setGlobalTransZ = e.target->getValue();
        setGlobalTransZ.set(clips[clip].setGlobalTransZ);
        
    } else if (e.target->getName() == "setLocalRotX"){
        
        clips[clip].setLocalRotX = e.target->getValue();
        setLocalRotX.set(clips[clip].setLocalRotX);
        
    } else if (e.target->getName() == "setLocalRotY"){
        
        clips[clip].setLocalRotY = e.target->getValue();
        setLocalRotY.set(clips[clip].setLocalRotY);
        
    } else if (e.target->getName() == "setLocalRotZ"){
        
        clips[clip].setLocalRotZ = e.target->getValue();
        setLocalRotZ.set(clips[clip].setLocalRotZ);
        
    } else if (e.target->getName() == "setLocalTransX"){
        
        clips[clip].setLocalTransX = e.target->getValue();
        setLocalTransX.set(clips[clip].setLocalTransX);
        
    } else if (e.target->getName() == "setLocalTransY"){
        
        clips[clip].setLocalTransY = e.target->getValue();
        setLocalTransY.set(clips[clip].setLocalTransY);
        
    } else if (e.target->getName() == "setLocalTransZ"){
        
        clips[clip].setLocalTransZ = e.target->getValue();
        setLocalTransZ.set(clips[clip].setLocalTransZ);
        
    } else if (e.target->getName() == "setObjRotX"){
        
        clips[clip].setObjRotX = e.target->getValue();
        setObjRotX.set(clips[clip].setObjRotX);
        
    } else if (e.target->getName() == "setObjRotY"){
        
        clips[clip].setObjRotY = e.target->getValue();
        setObjRotY.set(clips[clip].setObjRotY);
        
    } else if (e.target->getName() == "setObjRotZ"){
        
        clips[clip].setObjRotZ = e.target->getValue();
        setObjRotZ.set(clips[clip].setObjRotZ);
        
    } else if (e.target->getName() == "localScale"){
        
        clips[clip].localScale = e.target->getValue();
        localScale.set(clips[clip].localScale);
        
    } else if (e.target->getName() == "globalScale"){
        
        clips[clip].globalScale = e.target->getValue();
        globalScale.set(clips[clip].globalScale);
        
    }

    
        
        
        
    sendOSC(e.target->getName(), e.target->getValue());
    
}

//--------------------------------------------------------------
void ofxTLDatGui::sendOSC(string name, float value) {
    
    //create an event
    static OscMessageEvent vmmOscEvent;

    //logic to package the event.
    if (name == "setGlobalRotX" || name == "setGlobalRotY" || name == "setGlobalRotZ") {
        vmmOscEvent.composeFloatOscMsg(track+1, name, value);
    } else if (name == "setGlobalTransX" || name == "setGlobalTransY" || name == "setGlobalTransZ") {
        vmmOscEvent.composeFloatOscMsg(track+1, name, value);
    } else if (name == "setLocalRotX" || name == "setLocalRotY" || name == "setLocalRotZ") {
        vmmOscEvent.composeFloatOscMsg(track+1, name, value);
    } else if (name == "setLocalTransX" || name == "setLocalTransY" || name == "setLocalTransZ") {
        vmmOscEvent.composeFloatOscMsg(track+1, name, value);
    } else if (name == "setObjRotX" || name == "setObjRotY" || name == "setObjRotZ") {
        vmmOscEvent.composeFloatOscMsg(track+1, name, value);
    } else if (name == "localScale" || name == "globalScale") {
        vmmOscEvent.composeFloatOscMsg(track+1, name, value);
    } else {
        vmmOscEvent.composeIntOscMsg(track+1, name, int(value));
    }
    
    //notify event
    ofNotifyEvent(OscMessageEvent::events, vmmOscEvent);
}

//enable and disable are always automatically called
//in setup. Must call superclass's method as well as doing your own
//enabling and disabling
//--------------------------------------------------------------
void ofxTLDatGui::enable(){

    ofxTLTrack::enable();
    
    guiAcceptEvents = true;
    
	//other enabling
    OSCsetMatCapSlider->setEnabled(true);
    OSCsetTrackSlider->setEnabled(true);
    localSlicesSlider->setEnabled(true);
    localCopiesSlider->setEnabled(true);
    globalCopiesSlider->setEnabled(true);
    mirrorDistanceSlider->setEnabled(true);
    
    //not sure if this is needed
    setGlobalRotXSlider->setEnabled(true);
    setGlobalRotYSlider->setEnabled(true);
    setGlobalRotZSlider->setEnabled(true);
    setGlobalTransXSlider->setEnabled(true);
    setGlobalTransYSlider->setEnabled(true);
    setGlobalTransZSlider->setEnabled(true);
    
    //not sure if this is needed
    setLocalRotXSlider->setEnabled(true);
    setLocalRotYSlider->setEnabled(true);
    setLocalRotZSlider->setEnabled(true);
    setLocalTransXSlider->setEnabled(true);
    setLocalTransYSlider->setEnabled(true);
    setLocalTransZSlider->setEnabled(true);
    
    setObjRotXSlider->setEnabled(true);
    setObjRotYSlider->setEnabled(true);
    setObjRotZSlider->setEnabled(true);
    localScaleSlider->setEnabled(true);
    globalScaleSlider->setEnabled(true);
}

void ofxTLDatGui::disable(){

    ofxTLTrack::disable();

    guiAcceptEvents = false;
    //cout << "Called from TimelinePanel - ofxTLDatGui::disable() - guiAcceptEvents " << guiAcceptEvents << endl;
    
	//other disabling
    OSCsetMatCapSlider->setEnabled(false);
    OSCsetTrackSlider->setEnabled(false);
    localSlicesSlider->setEnabled(false);
    localCopiesSlider->setEnabled(false);
    globalCopiesSlider->setEnabled(false);
    mirrorDistanceSlider->setEnabled(false);
    
    setGlobalRotXSlider->setEnabled(false);
    setGlobalRotYSlider->setEnabled(false);
    setGlobalRotZSlider->setEnabled(false);
    setGlobalTransXSlider->setEnabled(false);
    setGlobalTransYSlider->setEnabled(false);
    setGlobalTransZSlider->setEnabled(false);
    
    //not sure if this is needed
    setLocalRotXSlider->setEnabled(false);
    setLocalRotYSlider->setEnabled(false);
    setLocalRotZSlider->setEnabled(false);
    setLocalTransXSlider->setEnabled(false);
    setLocalTransYSlider->setEnabled(false);
    setLocalTransZSlider->setEnabled(false);
    
    setObjRotXSlider->setEnabled(false);
    setObjRotYSlider->setEnabled(false);
    setObjRotZSlider->setEnabled(false);
    localScaleSlider->setEnabled(false);
    globalScaleSlider->setEnabled(false);
}

//--------------------------------------------------------------
void ofxTLDatGui::trackGuiDelete(){
    
    //clear the clips vector
    clips.clear();
    
    delete OSCsetMatCapSlider;
    delete OSCsetTrackSlider;
    delete localSlicesSlider;
    delete localCopiesSlider;
    delete globalCopiesSlider;
    delete mirrorDistanceSlider;
    delete playNoteOffToggle;
    delete playAllToggle;
    delete mirrorToggle;
    delete mirrorXToggle;
    delete mirrorYToggle;
    delete mirrorZToggle;
    
    delete setGlobalRotXSlider;
    delete setGlobalRotYSlider;
    delete setGlobalRotZSlider;
    
    delete setGlobalTransXSlider;
    delete setGlobalTransYSlider;
    delete setGlobalTransZSlider;
    
    delete setLocalRotXSlider;
    delete setLocalRotYSlider;
    delete setLocalRotZSlider;
    
    delete setLocalTransXSlider;
    delete setLocalTransYSlider;
    delete setLocalTransZSlider;
    
    delete setObjRotXSlider;
    delete setObjRotYSlider;
    delete setObjRotZSlider;
    delete localScaleSlider;
    delete globalScaleSlider;
    
    
    //  REMOVE LISTENERS
    //ofRemoveListener(trackGui->newGUIEvent, this, &ofxTLDatGui::trackGuiEvent);
    //ofRemoveListener(, this, &ofxTLDatGui::trackGuiSliderEvent);
    //ofRemoveListener(OSCsetTrackSlider, this, &ofxTLDatGui::trackGuiSliderEvent);
}

//--------------------------------------------------------------
void ofxTLDatGui::coutTrackParams(int c){
    
    cout << "clip: " << clip << endl;
    cout << "clips[clip].playNoteOff; - " << ofToString(clips[c].playNoteOff) << endl;
    cout << "clips[clip].playAll; - " << ofToString(clips[c].playAll) << endl;
    cout << "clips[clip].mirror; - " << ofToString(clips[c].mirror) << endl;
    cout << "clips[clip].mirrorX; - " << ofToString(clips[c].mirrorX) << endl;
    cout << "clips[clip].mirrorY; - " << ofToString(clips[c].mirrorY) << endl;
    cout << "clips[clip].mirrorZ; - " << ofToString(clips[c].mirrorZ) << endl;
    cout << "clips[clip].OSCsetMatCap; - " << ofToString(clips[c].OSCsetMatCap) << endl;
    cout << "clips[clip].OSCsetTrack; - " << ofToString(clips[c].OSCsetTrack) << endl;
    cout << "clips[clip].localSlices; - " << ofToString(clips[c].localSlices) << endl;
    cout << "clips[clip].localScale; - " << ofToString(clips[c].localScale) << endl;
    cout << "clips[clip].localCopies; - " << ofToString(clips[c].localCopies) << endl;
    cout << "clips[clip].globalCopies; - " << ofToString(clips[c].globalCopies) << endl;
    cout << "clips[clip].mirrorDistance; - " << ofToString(clips[c].mirrorDistance) << endl;
    cout << "clips[clip].setGlobalRotX; - " << ofToString(clips[c].setGlobalRotX) << endl;
    cout << "clips[clip].setGlobalRotY; - " << ofToString(clips[c].setGlobalRotY) << endl;
    cout << "clips[clip].setGlobalRotZ; - " << ofToString(clips[c].setGlobalRotZ) << endl;
    cout << "clips[clip].setGlobalTransX; - " << ofToString(clips[c].setGlobalTransX) << endl;
    cout << "clips[clip].setGlobalTransY; - " << ofToString(clips[c].setGlobalTransY) << endl;
    cout << "clips[clip].setGlobalTransZ; - " << ofToString(clips[c].setGlobalTransZ) << endl;
    cout << "clips[clip].setLocalRotX; - " << ofToString(clips[c].setLocalRotX) << endl;
    cout << "clips[clip].setLocalRotY; - " << ofToString(clips[c].setLocalRotY) << endl;
    cout << "clips[clip].setLocalRotZ; - " << ofToString(clips[c].setLocalRotZ) << endl;
    cout << "clips[clip].setLocalTransX; - " << ofToString(clips[c].setLocalTransX) << endl;
    cout << "clips[clip].setLocalTransY; - " << ofToString(clips[c].setLocalTransY) << endl;
    cout << "clips[clip].setLocalTransZ; - " << ofToString(clips[c].setLocalTransZ) << endl;
    cout << "clips[clip].setObjRotX; - " << ofToString(clips[c].setObjRotX) << endl;
    cout << "clips[clip].setObjRotY; - " << ofToString(clips[c].setObjRotY) << endl;
    cout << "clips[clip].setObjRotZ; - " << ofToString(clips[c].setObjRotZ) << endl;
    cout << "clips[clip].localScale; - " << ofToString(clips[c].localScale) << endl;
    cout << "clips[clip].globalScale; - " << ofToString(clips[c].globalScale) << endl;
    
}



//update is called every frame.
//if your track triggers events it's good to do it here
//if timeline is set to thread this is called on the back thread so
//be careful if loading images in here
//--------------------------------------------------------------
void ofxTLDatGui::update(){
    
    //    //get the bounds of the track.  used to show or hide the GUI.
    //    cout << "gui height: " << gui->getHeight() <<
    //    " track minY: " << bounds.getMinY() <<
    //    " track maxY: " << bounds.getMaxY() <<
    //    " getBottom - getTop = " << bounds.getBottom()-bounds.getTop() <<
    //    endl;
    
    
    //column 2
    playNoteOffToggle->setPosition(bounds.getX(), bounds.getY());
    playNoteOffToggle->setVisible(bounds.getBottom()-bounds.getTop() < playNoteOffToggle->getHeight() ? false : true);
    playNoteOffToggle->update(guiAcceptEvents);
    
    playAllToggle->setPosition(bounds.getX(), bounds.getY()+(compH*1));
    playAllToggle->setVisible(bounds.getBottom()-bounds.getTop() < (playAllToggle->getHeight()+(compH*1)) ? false : true);
    playAllToggle->update(guiAcceptEvents);
    
    mirrorToggle->setPosition(bounds.getX(), bounds.getY()+(compH*2));
    mirrorToggle->setVisible(bounds.getBottom()-bounds.getTop() < (mirrorToggle->getHeight()+(compH*2)) ? false : true);
    mirrorToggle->update(guiAcceptEvents);
    
    mirrorXToggle->setPosition(bounds.getX(), bounds.getY()+(compH*3));
    mirrorXToggle->setVisible(bounds.getBottom()-bounds.getTop() < (mirrorXToggle->getHeight()+(compH*3)) ? false : true);
    mirrorXToggle->update(guiAcceptEvents);
    
    mirrorYToggle->setPosition(bounds.getX(), bounds.getY()+(compH*4));
    mirrorYToggle->setVisible(bounds.getBottom()-bounds.getTop() < (mirrorYToggle->getHeight()+(compH*4)) ? false : true);
    mirrorYToggle->update(guiAcceptEvents);
    
    mirrorZToggle->setPosition(bounds.getX(), bounds.getY()+(compH*5));
    mirrorZToggle->setVisible(bounds.getBottom()-bounds.getTop() < (mirrorZToggle->getHeight()+(compH*5)) ? false : true);
    mirrorZToggle->update(guiAcceptEvents);
    
    
    //FINAL PLACEMENT CODE
    //column 1
    OSCsetMatCapSlider->setPosition(bounds.getX()+tglW, bounds.getY());
    OSCsetMatCapSlider->setVisible(bounds.getBottom()-bounds.getTop() < OSCsetMatCapSlider->getHeight() ? false : true);
    OSCsetMatCapSlider->update(guiAcceptEvents);
    
    OSCsetTrackSlider->setPosition(bounds.getX()+tglW, bounds.getY()+compH);
    OSCsetTrackSlider->setVisible(bounds.getBottom()-bounds.getTop() < (OSCsetTrackSlider->getHeight()+compH) ? false : true);
    OSCsetTrackSlider->update(guiAcceptEvents);
    
    localSlicesSlider->setPosition(bounds.getX()+tglW, bounds.getY()+(compH*2));
    localSlicesSlider->setVisible(bounds.getBottom()-bounds.getTop() < (localSlicesSlider->getHeight()+(compH*2)) ? false : true);
    localSlicesSlider->update(guiAcceptEvents);
    
    localCopiesSlider->setPosition(bounds.getX()+tglW, bounds.getY()+(compH*3));
    localCopiesSlider->setVisible(bounds.getBottom()-bounds.getTop() < (localCopiesSlider->getHeight()+(compH*3)) ? false : true);
    localCopiesSlider->update(guiAcceptEvents);
    
    globalCopiesSlider->setPosition(bounds.getX()+tglW, bounds.getY()+(compH*4));
    globalCopiesSlider->setVisible(bounds.getBottom()-bounds.getTop() < (globalCopiesSlider->getHeight()+(compH*4)) ? false : true);
    globalCopiesSlider->update(guiAcceptEvents);
    
    mirrorDistanceSlider->setPosition(bounds.getX()+tglW, bounds.getY()+(compH*5));
    mirrorDistanceSlider->setVisible(bounds.getBottom()-bounds.getTop() < (mirrorDistanceSlider->getHeight()+(compH*5)) ? false : true);
    mirrorDistanceSlider->update(guiAcceptEvents);
    

    //column 3
    setGlobalRotXSlider->setPosition(bounds.getX()+tglW+(compW*1), bounds.getY());
    setGlobalRotXSlider->setVisible(bounds.getBottom()-bounds.getTop() < setGlobalRotXSlider->getHeight() ? false : true);
    setGlobalRotXSlider->update(guiAcceptEvents);
    
    setGlobalRotYSlider->setPosition(bounds.getX()+tglW+(compW*1), bounds.getY()+(compH*1));
    setGlobalRotYSlider->setVisible(bounds.getBottom()-bounds.getTop() < setGlobalRotYSlider->getHeight()+(compH*1) ? false : true);
    setGlobalRotYSlider->update(guiAcceptEvents);
    
    setGlobalRotZSlider->setPosition(bounds.getX()+tglW+(compW*1), bounds.getY()+(compH*2));
    setGlobalRotZSlider->setVisible(bounds.getBottom()-bounds.getTop() < setGlobalRotZSlider->getHeight()+(compH*2) ? false : true);
    setGlobalRotZSlider->update(guiAcceptEvents);
    
    setGlobalTransXSlider->setPosition(bounds.getX()+tglW+(compW*1), bounds.getY()+(compH*3));
    setGlobalTransXSlider->setVisible(bounds.getBottom()-bounds.getTop() < setGlobalTransXSlider->getHeight()+(compH*3) ? false : true);
    setGlobalTransXSlider->update(guiAcceptEvents);
    
    setGlobalTransYSlider->setPosition(bounds.getX()+tglW+(compW*1), bounds.getY()+(compH*4));
    setGlobalTransYSlider->setVisible(bounds.getBottom()-bounds.getTop() < setGlobalTransYSlider->getHeight()+(compH*4) ? false : true);
    setGlobalTransYSlider->update(guiAcceptEvents);
    
    setGlobalTransZSlider->setPosition(bounds.getX()+tglW+(compW*1), bounds.getY()+(compH*5));
    setGlobalTransZSlider->setVisible(bounds.getBottom()-bounds.getTop() < setGlobalTransZSlider->getHeight()+(compH*5) ? false : true);
    setGlobalTransZSlider->update(guiAcceptEvents);
 
    
    //column 4
    setLocalRotXSlider->setPosition(bounds.getX()+tglW+(compW*2), bounds.getY());
    setLocalRotXSlider->setVisible(bounds.getBottom()-bounds.getTop() < setLocalRotXSlider->getHeight() ? false : true);
    setLocalRotXSlider->update(guiAcceptEvents);
    
    setLocalRotYSlider->setPosition(bounds.getX()+tglW+(compW*2), bounds.getY()+(compH*1));
    setLocalRotYSlider->setVisible(bounds.getBottom()-bounds.getTop() < setLocalRotYSlider->getHeight()+(compH*1) ? false : true);
    setLocalRotYSlider->update(guiAcceptEvents);
    
    setLocalRotZSlider->setPosition(bounds.getX()+tglW+(compW*2), bounds.getY()+(compH*2));
    setLocalRotZSlider->setVisible(bounds.getBottom()-bounds.getTop() < setLocalRotZSlider->getHeight()+(compH*2) ? false : true);
    setLocalRotZSlider->update(guiAcceptEvents);
    
    setLocalTransXSlider->setPosition(bounds.getX()+tglW+(compW*2), bounds.getY()+(compH*3));
    setLocalTransXSlider->setVisible(bounds.getBottom()-bounds.getTop() < setLocalTransXSlider->getHeight()+(compH*3) ? false : true);
    setLocalTransXSlider->update(guiAcceptEvents);
    
    setLocalTransYSlider->setPosition(bounds.getX()+tglW+(compW*2), bounds.getY()+(compH*4));
    setLocalTransYSlider->setVisible(bounds.getBottom()-bounds.getTop() < setLocalTransYSlider->getHeight()+(compH*4) ? false : true);
    setLocalTransYSlider->update(guiAcceptEvents);
    
    setLocalTransZSlider->setPosition(bounds.getX()+tglW+(compW*2), bounds.getY()+(compH*5));
    setLocalTransZSlider->setVisible(bounds.getBottom()-bounds.getTop() < setLocalTransZSlider->getHeight()+(compH*5) ? false : true);
    setLocalTransZSlider->update(guiAcceptEvents);
    
    //column 5
    setObjRotXSlider->setPosition(bounds.getX()+tglW+(compW*3), bounds.getY());
    setObjRotXSlider->setVisible(bounds.getBottom()-bounds.getTop() < setObjRotXSlider->getHeight() ? false : true);
    setObjRotXSlider->update(guiAcceptEvents);
    
    setObjRotYSlider->setPosition(bounds.getX()+tglW+(compW*3), bounds.getY()+(compH*1));
    setObjRotYSlider->setVisible(bounds.getBottom()-bounds.getTop() < setObjRotYSlider->getHeight()+(compH*1) ? false : true);
    setObjRotYSlider->update(guiAcceptEvents);
    
    setObjRotZSlider->setPosition(bounds.getX()+tglW+(compW*3), bounds.getY()+(compH*2));
    setObjRotZSlider->setVisible(bounds.getBottom()-bounds.getTop() < setObjRotZSlider->getHeight()+(compH*2) ? false : true);
    setObjRotZSlider->update(guiAcceptEvents);
    
    localScaleSlider->setPosition(bounds.getX()+tglW+(compW*3), bounds.getY()+(compH*3));
    localScaleSlider->setVisible(bounds.getBottom()-bounds.getTop() < localScaleSlider->getHeight()+(compH*3) ? false : true);
    localScaleSlider->update(guiAcceptEvents);
    
    globalScaleSlider->setPosition(bounds.getX()+tglW+(compW*3), bounds.getY()+(compH*4));
    globalScaleSlider->setVisible(bounds.getBottom()-bounds.getTop() < globalScaleSlider->getHeight()+(compH*4) ? false : true);
    globalScaleSlider->update(guiAcceptEvents);
    
}

//draw your track contents. use ofRectangle bounds to know where to draw
//and the Track functions screenXToMillis() or millisToScreenX() to respect zoom
//--------------------------------------------------------------
void ofxTLDatGui::draw(){
    
    OSCsetMatCapSlider->draw();
    OSCsetTrackSlider->draw();
    localSlicesSlider->draw();
    localCopiesSlider->draw();
    globalCopiesSlider->draw();
    mirrorDistanceSlider->draw();
    
    playNoteOffToggle->draw();
    playAllToggle->draw();
    mirrorToggle->draw();
    mirrorXToggle->draw();
    mirrorYToggle->draw();
    mirrorZToggle->draw();
    
    setGlobalRotXSlider->draw();
    setGlobalRotYSlider->draw();
    setGlobalRotZSlider->draw();
    setGlobalTransXSlider->draw();
    setGlobalTransYSlider->draw();
    setGlobalTransZSlider->draw();
    
    setLocalRotXSlider->draw();
    setLocalRotYSlider->draw();
    setLocalRotZSlider->draw();
    setLocalTransXSlider->draw();
    setLocalTransYSlider->draw();
    setLocalTransZSlider->draw();
    
    setObjRotXSlider->draw();
    setObjRotYSlider->draw();
    setObjRotZSlider->draw();
    localScaleSlider->draw();
    globalScaleSlider->draw();
    
	//this is just a simple example (not working for me)
	/* SAMPLE CODE
	ofPushStyle();
	ofFill();
	if(isHovering()){
		//ofSetColor(timeline->getColors().backgroundColor);
        ofSetColor(ofColor::indianRed);
        ofRectangle(bounds);

	}

	ofNoFill();
	ofSetColor(timeline->getColors().keyColor);
	for(int i = 0; i < clickPoints.size(); i++){
		float screenX = millisToScreenX(clickPoints[i].time);
		if(screenX > bounds.x && screenX < bounds.x+bounds.width){
			float screenY = ofMap(clickPoints[i].value, 0.0, 1.0, bounds.getMinY(), bounds.getMaxY());
            ofDrawCircle(screenX, screenY, 4);
		}
	}
    ofPopStyle();
    */
}

//caled by the timeline, don't need to register events
//--------------------------------------------------------------
bool ofxTLDatGui::mousePressed(ofMouseEventArgs& args, long millis){
	
    /* SAMPLE CODE
	createNewPoint = isActive();
	clickPoint = ofVec2f(args.x,args.y);
	return createNewPoint; //signals that the click made a selection
	*/
}

//--------------------------------------------------------------
void ofxTLDatGui::mouseMoved(ofMouseEventArgs& args, long millis){

}

//--------------------------------------------------------------
void ofxTLDatGui::mouseDragged(ofMouseEventArgs& args, long millis){

}

//--------------------------------------------------------------
void ofxTLDatGui::mouseReleased(ofMouseEventArgs& args, long millis){

	/* SAMPLE CODE
	//need to create clicks on mouse up if the mouse hasn't moved in order to work
	//well with the click-drag rectangle thing
	if(createNewPoint && clickPoint.distance(ofVec2f(args.x, args.y)) < 4){
		ClickPoint newpoint;
		newpoint.value = ofMap(args.y, bounds.getMinY(), bounds.getMaxY(), 0, 1.0);
		newpoint.time = millis;
		clickPoints.push_back(newpoint);
		//call this on mouseup or keypressed after a click
		//will trigger save and needed for undo
		timeline->flagTrackModified(this);
	}
	*/
}

//keys pressed events, and nuding from arrow keys with normalized nudge amount 0 - 1.0
//--------------------------------------------------------------
void ofxTLDatGui::keyPressed(ofKeyEventArgs& args){

}
void ofxTLDatGui::nudgeBy(ofVec2f nudgePercent){

}

//if your track has some selectable elements you can interface with snapping
//and selection/unselection here
//--------------------------------------------------------------
void ofxTLDatGui::getSnappingPoints(set<unsigned long>& points){

}
void ofxTLDatGui::regionSelected(ofLongRange timeRange, ofRange valueRange){

}
void ofxTLDatGui::unselectAll(){

}
void ofxTLDatGui::selectAll(){

}

//return a unique name for your track
string ofxTLDatGui::getTrackType(){
	return "Buttons";
}

//for copy+paste you can optionaly implement ways
//of creating XML strings that represent your selected tracks
string ofxTLDatGui::copyRequest(){
	return "";
}

string ofxTLDatGui::cutRequest(){
	return "";
}

//will return the same type of strings you provide in copy and paste
//but may contain foreign data from other tracks so be careful
void ofxTLDatGui::pasteSent(string pasteboard){

}

//for undo and redo you can implement a way of
//reperesnt your whole track as XML
string ofxTLDatGui::getXMLRepresentation(){
	return "";
}

void ofxTLDatGui::loadFromXMLRepresentation(string rep){

}

//serialize your track.
//use ofxTLTrack's string xmlFileName
//--------------------------------------------------------------
void ofxTLDatGui::save(){
    cout << "ofxTLDatGui::save()" << endl;
    
    //string xmlRep = getXMLStringForKeyframes(keyframes);
    ofxXmlSettings savedButtonsTrack;
    
    //write all the VMM settings.
    savedButtonsTrack.addTag("VMM");
    savedButtonsTrack.pushTag("VMM");
    
    savedButtonsTrack.addValue("playNoteOff", playNoteOff);
    savedButtonsTrack.addValue("playAll", playAll);
    savedButtonsTrack.addValue("mirror", mirror);
    savedButtonsTrack.addValue("mirrorX", mirrorX);
    savedButtonsTrack.addValue("mirrorY", mirrorY);
    savedButtonsTrack.addValue("mirrorZ", mirrorZ);
    
    savedButtonsTrack.addValue(OSCsetMatCap.getName(), OSCsetMatCap.get());
    savedButtonsTrack.addValue(OSCsetTrack.getName(), OSCsetTrack.get());
    savedButtonsTrack.addValue(localSlices.getName(), localSlices.get());
    savedButtonsTrack.addValue(localCopies.getName(), localCopies.get());
    savedButtonsTrack.addValue(globalCopies.getName(), globalCopies.get());
    savedButtonsTrack.addValue(mirrorDistance.getName(), mirrorDistance.get());
    
    savedButtonsTrack.addValue(setGlobalRotX.getName(), setGlobalRotX.get());
    savedButtonsTrack.addValue(setGlobalRotY.getName(), setGlobalRotY.get());
    savedButtonsTrack.addValue(setGlobalRotZ.getName(), setGlobalRotZ.get());
    savedButtonsTrack.addValue(setGlobalTransX.getName(), setGlobalTransX.get());
    savedButtonsTrack.addValue(setGlobalTransY.getName(), setGlobalTransY.get());
    savedButtonsTrack.addValue(setGlobalTransZ.getName(), setGlobalTransZ.get());
    
    savedButtonsTrack.addValue(setLocalRotX.getName(), setLocalRotX.get());
    savedButtonsTrack.addValue(setLocalRotY.getName(), setLocalRotY.get());
    savedButtonsTrack.addValue(setLocalRotZ.getName(), setLocalRotZ.get());
    savedButtonsTrack.addValue(setLocalTransX.getName(), setLocalTransX.get());
    savedButtonsTrack.addValue(setLocalTransY.getName(), setLocalTransY.get());
    savedButtonsTrack.addValue(setLocalTransZ.getName(), setLocalTransZ.get());

    savedButtonsTrack.addValue(setObjRotX.getName(), setObjRotX.get());
    savedButtonsTrack.addValue(setObjRotY.getName(), setObjRotY.get());
    savedButtonsTrack.addValue(setObjRotZ.getName(), setObjRotZ.get());
    savedButtonsTrack.addValue(localScale.getName(), localScale.get());
    savedButtonsTrack.addValue(globalScale.getName(), globalScale.get());
    
    
    savedButtonsTrack.popTag();
    
    //cout where and what to save.
    string outstring;
    savedButtonsTrack.copyXmlToString(outstring);
    cout << outstring << endl;
    cout << "XMLFilePath: " << getXMLFilePath() << endl;
    cout << "XMLFileName: " << getXMLFileName() << endl;
    
    savedButtonsTrack.saveFile(xmlFileName);
    
}

//--------------------------------------------------------------
void ofxTLDatGui::load(){
    
    //ofLog() << "ofxTLDatGui::load() - DO NOTHING! - path: " << getXMLFilePath();
    
    //string savedClipSettingsPath = getXMLFilePath();
    
    /*
    
    string savedClipSettingsPath = getXMLFilePath();
    ofxXmlSettings savedVMMSettings;
    
    //TODO - if Loading
    
    
    if( savedVMMSettings.loadFile(savedClipSettingsPath) ){
        ofLogVerbose("LOAD") << "ofxTLDatGui::load() - Loading VMM.xml " << savedClipSettingsPath;
        
        //send clear.
        //sendOSC("clear", 1.0);
        
        bool VMM_playNoteOff = savedVMMSettings.getValue("VMM:playNoteOff", 0);
        //sendOSC("playNoteOff", VMM_playNoteOff);
        playNoteOff = VMM_playNoteOff;
        playNoteOffToggle->setEnabled(playNoteOff);
        
        bool VMM_playAll = savedVMMSettings.getValue("VMM:playAll", 0);
        //sendOSC("playAll", VMM_playAll);
        playAll = VMM_playAll;
        playAllToggle->setEnabled(playAll);
        
        bool VMM_mirror = savedVMMSettings.getValue("VMM:mirror", 0);
        //sendOSC("mirror", VMM_mirror);
        mirror = VMM_mirror;
        mirrorToggle->setEnabled(mirror);
        
        bool VMM_mirrorX = savedVMMSettings.getValue("VMM:mirrorX", 0);
        //sendOSC("mirrorX", VMM_mirrorX);
        mirrorX = VMM_mirrorX;
        mirrorXToggle->setEnabled(mirrorX);
        
        bool VMM_mirrorY = savedVMMSettings.getValue("VMM:mirrorY", 0);
        //sendOSC("mirrorY", VMM_mirrorY);
        mirrorY = VMM_mirrorY;
        mirrorYToggle->setEnabled(mirrorY);
        
        bool VMM_mirrorZ = savedVMMSettings.getValue("VMM:mirrorZ", 0);
        //sendOSC("mirrorZ", VMM_mirrorZ);
        mirrorZ = VMM_mirrorZ;
        mirrorZToggle->setEnabled(mirrorZ);
        
        
        //update the params
        int VMM_OSCsetMatCap = savedVMMSettings.getValue("VMM:OSCsetMatCap", 0);
        //sendOSC("OSCsetMatCap", VMM_OSCsetMatCap);
        OSCsetMatCap.set(VMM_OSCsetMatCap);
        
        int VMM_OSCsetTrack = savedVMMSettings.getValue("VMM:OSCsetTrack", 0);
        ////sendOSC("OSCsetTrack", VMM_OSCsetTrack);
        OSCsetTrack.set(VMM_OSCsetTrack);
        
        int VMM_localSlices = savedVMMSettings.getValue("VMM:localSlices", 0);
        //sendOSC("localSlices", VMM_localSlices);
        localSlices.set(VMM_localSlices);
        
        int VMM_localCopies = savedVMMSettings.getValue("VMM:localCopies", 0);
        //sendOSC("localCopies", VMM_localCopies);
        localCopies.set(VMM_localCopies);
        
        int VMM_globalCopies = savedVMMSettings.getValue("VMM:globalCopies", 0);
        //sendOSC("globalCopies", VMM_globalCopies);
        globalCopies.set(VMM_globalCopies);
        
        int VMM_mirrorDistance = savedVMMSettings.getValue("VMM:mirrorDistance", 0);
        //sendOSC("mirrorDistance", VMM_mirrorDistance);
        mirrorDistance.set(VMM_mirrorDistance);
        
        int VMM_setGlobalRotX = savedVMMSettings.getValue("VMM:setGlobalRotX", 0);
        //sendOSC("setGlobalRotX", VMM_setGlobalRotX);
        setGlobalRotX.set(VMM_setGlobalRotX);
        
        int VMM_setGlobalRotY = savedVMMSettings.getValue("VMM:setGlobalRotY", 0);
        //sendOSC("setGlobalRotY", VMM_setGlobalRotY);
        setGlobalRotY.set(VMM_setGlobalRotY);
        
        int VMM_setGlobalRotZ = savedVMMSettings.getValue("VMM:setGlobalRotZ", 0);
        //sendOSC("setGlobalRotZ", VMM_setGlobalRotZ);
        setGlobalRotZ.set(VMM_setGlobalRotZ);
        
        int VMM_setGlobalTransX = savedVMMSettings.getValue("VMM:setGlobalTransX", 0);
        //sendOSC("setGlobalTransX", VMM_setGlobalTransX);
        setGlobalTransX.set(VMM_setGlobalTransX);
        
        int VMM_setGlobalTransY = savedVMMSettings.getValue("VMM:setGlobalTransY", 0);
        //sendOSC("setGlobalTransY", VMM_setGlobalTransY);
        setGlobalTransY.set(VMM_setGlobalTransY);
        
        int VMM_setGlobalTransZ = savedVMMSettings.getValue("VMM:setGlobalTransZ", 0);
        //sendOSC("setGlobalTransZ", VMM_setGlobalTransZ);
        setGlobalTransZ.set(VMM_setGlobalTransZ);
        
        int VMM_setLocalRotX = savedVMMSettings.getValue("VMM:setLocalRotX", 0);
        //sendOSC("setLocalRotX", VMM_setLocalRotX);
        setLocalRotX.set(VMM_setLocalRotX);
        
        int VMM_setLocalRotY = savedVMMSettings.getValue("VMM:setLocalRotY", 0);
        //sendOSC("setLocalRotY", VMM_setLocalRotY);
        setLocalRotY.set(VMM_setLocalRotY);
        
        int VMM_setLocalRotZ = savedVMMSettings.getValue("VMM:setLocalRotZ", 0);
        //sendOSC("setLocalRotZ", VMM_setLocalRotZ);
        setLocalRotZ.set(VMM_setLocalRotZ);
        
        int VMM_setLocalTransX = savedVMMSettings.getValue("VMM:setLocalTransX", 0);
        //sendOSC("setLocalTransX", VMM_setLocalTransX);
        setLocalTransX.set(VMM_setLocalTransX);
        
        int VMM_setLocalTransY = savedVMMSettings.getValue("VMM:setLocalTransY", 0);
        //sendOSC("setLocalTransY", VMM_setLocalTransY);
        setLocalTransY.set(VMM_setLocalTransY);
        
        int VMM_setLocalTransZ = savedVMMSettings.getValue("VMM:setLocalTransZ", 0);
        //sendOSC("setLocalTransZ", VMM_setLocalTransZ);
        setLocalTransZ.set(VMM_setLocalTransZ);
        
        int VMM_setObjRotX = savedVMMSettings.getValue("VMM:setObjRotX", 0);
        //sendOSC("setObjRotX", VMM_setObjRotX);
        setObjRotX.set(VMM_setObjRotX);
        
        int VMM_setObjRotY = savedVMMSettings.getValue("VMM:setObjRotY", 0);
        //sendOSC("setObjRotY", VMM_setObjRotY);
        setObjRotY.set(VMM_setObjRotY);
        
        int VMM_setObjRotZ = savedVMMSettings.getValue("VMM:setObjRotZ", 0);
        //sendOSC("setObjRotZ", VMM_setObjRotZ);
        setObjRotZ.set(VMM_setObjRotZ);
        
        int VMM_localScale = savedVMMSettings.getValue("VMM:localScale", 0);
        //sendOSC("localScale", VMM_localScale);
        localScale.set(VMM_localScale);
        
        int VMM_globalScale = savedVMMSettings.getValue("VMM:globalScale", 0);
        //sendOSC("globalScale", VMM_globalScale);
        globalScale.set(VMM_globalScale);
        
    }else{
        ofLogError("LOAD") <<  "ofxTLDatGui::load() - unable to load: " << savedClipSettingsPath ;
        return;
    }
    
    */
}

void ofxTLDatGui::clear(){

}
