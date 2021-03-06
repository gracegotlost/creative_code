// =============================================================================
//
// Copyright (c) 2010-2013 Christopher Baker <http://christopherbaker.net>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
// =============================================================================


#include "ofApp.h"


//------------------------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(30);
    //ofSetLogLevel(OF_LOG_VERBOSE);
    
    // A simplified interface when using the ofxExampleTwitterClient class.
    // Twitter-specific configuration details can be taken care of the 
    // ofxOAuth base class.
    client.setup("Ja78nwGLoScRoVlPZh8Y6PGqq","imHbjy5J12KkiWhIlpyI4pYprYd34vYKGqQT7wGa8TyVdim7Lk");
    
    // Once authenticated, press the spacebar to try a test call.
}

//------------------------------------------------------------------------------
void ofApp::update(){

    //cout << ofGetElapsedTimeMillis() << endl;
    
    if(ofGetElapsedTimeMillis()%5000 < 20){
        
        if(client.isAuthorized()){
            
            // Get number of followers
            std::string s = client.exampleMethod();
            
            // Parse, Check, and Post new status
            response.parse(s);
            currentNumber = response["ids"].size();
            if (currentNumber - lastNumber != 0) {
                std::string s2 = client.getScreenName();
                showName.parse(s2);
                std::string name = showName["users"][0]["name"].asString(); //results are ordered with the most recent following first
                cout << "name: " << name << endl;
                
                // If a person follows me
                if (currentNumber - lastNumber > 0) {
                    client.exampleUpdateStatusMethod("I'm so excited @" + name + " followed me today! Hope you enjoy everyday with my sweet posts:)");
                }
                
                // If a person unfollows me
                if (currentNumber - lastNumber < 0) {
                    client.exampleUpdateStatusMethod("Who just left me");
                }
            }
            
            // Post new status & image
            //std::string s = client.exampleUpdateStatusWithPhotoMethod("Hi from OF!", "buses.jpg");
            
            lastNumber = currentNumber;
            
            // Print in console
            ofLogNotice("Current Number ") << currentNumber;
            
        }
        
        else{
            ofLogWarning("Bad Response ") << "Not authorized yet.";
        }
    }
}

//------------------------------------------------------------------------------
void ofApp::draw(){
    
    if(client.isAuthorized()) {
        
        ofBackground(0,255,0);
    }
    
    else {
        
        ofBackground(255,0,0);
    }
    
}

//------------------------------------------------------------------------------
void ofApp::keyPressed(int key){
    
}
