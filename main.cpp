// Noah Bliss - 21.12.05
// Let's try to not kill ourselves, eh?

//Logic:
//Evaluate if a circuit 1 is grounded. 
//If not, use a momentary button in circuit 2 to control circuit 3 as latching button via a relay.
//If circuit 1 becomes grounded, unconditionally force circuit 3 open. 


//define pins
int pin_odrelay = 7; 
int pin_odreq = 6;
int pin_firstgear = 5;

//define states
//bool odreq = false;
int val_odreq = HIGH;
int val_firstgear = LOW;

bool odactive = false;
bool odreq = false;
bool infirst = true;
bool lasttickreq = false;

//enable overdrive function
bool od_enable() { 
  digitalWrite(pin_odrelay, HIGH); // Enable Overdrive
  digitalWrite(LED_BUILTIN, HIGH); // Turn on internal1 LED
  return true;
}

//disable overdrive function
bool od_disable() {
  digitalWrite(pin_odrelay, LOW); // Disable Overdrive
  digitalWrite(LED_BUILTIN, LOW); // Turn off internal1 LED
  return false;
}

//toggle overdrive function
void od_toggle() {
  if(odactive == false) {
    odactive = od_enable();
  } else {
    odactive = od_disable();
  }
  delay(1000);
}

bool query_first() {
  int val_firstgear = digitalRead(pin_firstgear); 
  if(val_firstgear == LOW) {
    return true;
  } else {
    return false;
  }
}

bool query_odreq() {
  int val_odreq = digitalRead(pin_odreq);
  if(val_odreq == LOW) {
    return true;
  } else {
    return false;
  }
}

//General setup and pin function definition
void setup() {
  pinMode(LED_BUILTIN, OUTPUT); //Internal LED
  pinMode(pin_odrelay, OUTPUT);
  pinMode(pin_odreq, INPUT_PULLUP);
  pinMode(pin_firstgear, INPUT_PULLUP);
}

//Main loop
void loop() {
  infirst = query_first();
  if(infirst == false) { //if NOT in first...
    odreq = query_odreq();
    if(odreq == true) { // if button is pressed...
      if(lasttickreq == false) { //if button wasn't pressed last time we read it...
        od_toggle(); //toggle overdrive
        lasttickreq = true; //set last request to true
      }
    } else {
      lasttickreq = false;
    }
  } else if(odactive == true) { //if IN first...
    odactive = od_disable();
    lasttickreq = false;
  }
}
