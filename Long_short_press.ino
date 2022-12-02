#define button 7

unsigned long debounce_delay = 150;
unsigned long last_press;
bool inputstate;                     // says if you started an input(1) or not (0)
bool long_press = 0;

void setup() {
  pinMode(button, INPUT);
}

void loop() {
  if (digitalRead(button) && !inputstate && !long_press) { // check if you pressed the button at least once if you are not in a wainting state(inputstate==1) or in a longpress
    inputstate = true;                                     // start waiting for debounce delay to run off
    last_press = millis();                                 // so it takes curent time
  }
  if (!digitalRead(button) && long_press) {              // if it is a long press you check thath you are still pressing otherwise
    long_press = false;                                  // is not a long press anymore
    inputstate = false;                                  // reset the input to start over again
  }
  if (millis() - last_press >= debounce_delay && inputstate && digitalRead(button)) {    // check if you are still pressing after the debounce delay
    long_press = true;          // it's a long press                                     // inputstate has to be high which means that you are waiting for an input
    
    doLongPressStuff();
    
  } else if (millis() - last_press >= debounce_delay && !long_press && inputstate && !digitalRead(button)) {  // if the button isnt still pressed it is a short press
    long_press = false;   // not  long press                                                                  // since if the longpress is ended or it has never started
    inputstate = false;   // to wait for a long/short press again after this iteration                        // it should be false, this is  a condition.
                                                                                                              //inputstate has to be true because you are still waiting for some sort of inpu
    doShortPressStuff();                                                                                      // since you are debouncing and the press is short, after the debounce delay 
                                                                                                              //the button pin should be low (released)
    
  }
}
