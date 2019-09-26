
/*
  PanaTrap - MADV
  Debug Code for the turning the Xiaomi MiSphere (MADV) camera
  into a remotely controlled,
  PIR triggered, Camera Trap

*/

/* in order to trigger the MADV camera to change modes, in theory you should connect a relay to your arduino, and trigger that to connect the nodes of the MADV
  //But we are trying to use minimal hardware, and found that if you connect the node closest to the center of the camera to the ground, and then
  //Connect another digital pin  to the other node
  //Initially set the digital pin to HIGH, and then when you pull it LOW
  //it will trigger the camera

  - Long Press (5 seconds)
  - Camera ON/OFF
  - Medium Press (2 seconds)
  - Toggle Recording Mode (Video to Photo, or Photo to Video)
  - Short press (0.5-1 seconds)
  - Shutter Button (Take a photo, or start or stop a video)

*/

//Front PIR motion sensors
int fPIR = A4;
int fPIRval = -1;

//Back PIR motion sensors
int bPIR = A3;
int bPIRval = -1;

//camera trigger operants

int trigger = 12;
int gndtrigger = 9;


//LED for debugging display
int led = 13;


void setup() {
  //Serial for debugging PIRs
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);

  //Turning some of the pins on the camera into virtual Power sources and Grounds
  pinMode(A1, OUTPUT);
  digitalWrite(A1, LOW);

  pinMode(A2, OUTPUT);
  digitalWrite(A2, HIGH);

  pinMode(A5, OUTPUT);
  digitalWrite(A5, LOW);


  //Camera Trigger stuff
  pinMode(led, OUTPUT);
  pinMode(trigger, OUTPUT);
  pinMode(gndtrigger, OUTPUT);

  digitalWrite(led, HIGH);

  digitalWrite(trigger, HIGH);
  digitalWrite(gndtrigger, LOW); //**Andy note A

}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  fPIRval = analogRead(fPIR);
  bPIRval = analogRead(bPIR);
  // print out the value you read:
  Serial.print(fPIRval);
  Serial.print("    rear:  ");
  Serial.println(bPIRval);


  if (fPIRval > 600 || bPIRval > 600) {
    critterDetected();
  }
  delay(1);        // delay in between reads for stability
}

void critterDetected() {

  Serial.println("Critter detected");
  //Turn camera on
  onOffCamera();

  //Take a photo
  takePhoto();
  takePhoto();

  //TODO: Wait to see if other critters still around
  //before we shut off camera

  //TODO: the camera will toggle between photo and video each time it shuts off, add in a toggle here

  onOffCamera();

}

void onOffCamera() {
  Serial.println("cameraONOFF");

  //5 second turn on
  digitalWrite(led, LOW);
  digitalWrite(trigger, LOW);
  digitalWrite(gndtrigger, LOW);
  delay(5000);

  ///Chill
  digitalWrite(led, HIGH);
  digitalWrite(trigger, HIGH);
  digitalWrite(gndtrigger, LOW);
  delay(2000);
}

void takePhoto() {
  Serial.println("Take photo");

  //Take a photo
  digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
  digitalWrite(trigger, LOW);  // turn the LED on (HIGH is the voltage level)
  digitalWrite(gndtrigger, LOW);
  delay(1000);               // wait for a second

  ///Chill 4 secs
  digitalWrite(led, HIGH);
  digitalWrite(trigger, HIGH);
  digitalWrite(gndtrigger, LOW);
  delay(4000);

}

void togglePhotoVideo() {
  Serial.println("cameraTogglePhotoVideo");

  //2 second press
  digitalWrite(led, LOW);
  digitalWrite(trigger, LOW);
  digitalWrite(gndtrigger, LOW);
  delay(2000);

  ///Chill
  digitalWrite(led, HIGH);
  digitalWrite(trigger, HIGH);
  digitalWrite(gndtrigger, LOW);
  delay(2000);

}
