# ofxTLDatGui
ofxTLDatGui is an addon for ofxTimeline to add a pseudo-track ofxDatGui channel full of widgets meant send params to my application [VMM](https://github.com/lg3bass/VMM).  This addon is a customization of the ofxTLButtons addon by [https://github.com/hvfrancesco/ofxTLButtons](https://github.com/hvfrancesco/ofxTLButtons).ofxTLDatGui uses ofxDatGui instead of ofxUI.  

### Installing the addon
Add in addons.make after ofxTimeline and its dependencies add:

`ofxTLDatGui
ofxDatGui`

-- or -- 

Use the Project Generator to add ofxTLDatGui

### Setup
In you header file add (usually next to #include "ofxTimeline.h"):

	include "ofxTLDatGui.h"

And the in your cpp file you can add buttons track with something like this:

	ofxTLDatGui* datGuiTrack = new ofxTLDatGui();
    datGuiTrack->setXMLFileName("datguitrack.xml");
    timeline.addTrack("datGuiTrack", datGuiTrack);
      
To send events, I created an event in the ofxTLDatGui/src/ofxTLDatGui.h

	//CREATES A PREPACKAGED OSC MSG EVENT.
	//ofxTLDatGui/src/ofxTLDatGui.h
	class OscMessageEvent : public ofEventArgs{
	public:
	    ofxOscMessage m;
	    string message;
	    int value;
    
  
    void composeOscMsg(int track, string msg, float val){
        message = "/" + msg;
        value = (int)floor(val);
        
        //compose an osc message
        m.clear();
        m.setAddress(message);
        m.addIntArg(track);
        m.addIntArg(value);
    }
    
    void composeIntOscMsg(int track, string msg, int val){
        message = "/" + msg;

        m.clear();
        m.setAddress(message);
        m.addIntArg(track);
        m.addIntArg(val);
    }
    
    void composeFloatOscMsg(int track, string msg, float val){
        message = "/" + msg;
        m.clear();
        m.setAddress(message);
        m.addIntArg(track);
        m.addFloatArg(val);
    }
    
    static ofEvent <OscMessageEvent> events;
	};	 
	
	 
And then in the ofxTLDatGui.cpp file add the instance of the event.

	 //CREATE AND SEND AN OSC MESSAGE
	 //ofxTLDatGui/src/ofxTLDatGui.cpp
	 
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
	
	


Another importan note:
If you want to disable the mouse events on ofxDatGui components the update() functions accepts a boolean param.  Setting to false disables mouse events.  This is needed if you have multiple timelines/tabs.

    playNoteOffToggle->setPosition(bounds.getX(), bounds.getY());
    playNoteOffToggle->setVisible(bounds.getBottom()-bounds.getTop() < playNoteOffToggle->getHeight() ? false : true);
    playNoteOffToggle->update(guiAcceptEvents);





* TODO:
* - much of this code is for another project. Will need to slim it all down.
* - Test on PC.  I don't have any of this working on a PC. sorry
* - Fix the save/load code. Currently save is being handled elsewhere.  
* - ofxDatGui themes and fonts.  I have include my DatGui setup. You will need to setup your own fonts.
