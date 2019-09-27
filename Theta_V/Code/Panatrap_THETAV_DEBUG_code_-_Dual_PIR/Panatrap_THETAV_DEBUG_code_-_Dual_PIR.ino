/*
  PanaTrap - Theta V
  Debug Code for the turning the Ricoh Theta V camera
  into a remotely controlled,
  PIR triggered, Camera Trap

  Using the Teensy 3.2

  This camera is unfortunately blocked in lots of parts of its API from being able to just control with digital signals
    so we control it two ways

    Wake up: Sending a Fake Keyboard Command

    Take Photo:
    Trigger a servo to physically press the button
    Note: if the button is held down WHILE the camera is waking up, it will NOT take a photo, thus there is some timing trickiness here

    Note: make sure to set the Teensy on Serial+Keyboard+Mouse+Joystick

    Note: we are using the Teensy 3.2 because it can send virtual HID signals, and it is the only one I had that was 5V tolerant (which i only had 5V PIRs)
*/

#include <Servo.h>
Servo myservo;
// create servo object to control a servo
// twelve servo objects can be created on most boards

int offpos = 160;
int onpos = 180;


//Front PIR motion sensors
int fPIR = A5;
int fPIRval = -1;
int fPIRpower = 22;
int fPIRgnd = 20;

//Back PIR motion sensors
int bPIR = A2;
int bPIRval = -1;
int bPIRpower = 19;
int bPIRgnd = 17;

//LED for debugging display
int led = 13;

int detectionThreshold = 600; // Our PIRs are actually just binary, but setting up infrastructure in case other sensors are used
void setup() {
  //Serial for debugging PIRs
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  digitalWrite(led, HIGH);

  //Configure the mouse (im not sure we actually have to do this
  Mouse.screenSize(1920, 1080);  // configure screen size


  //Setup Servo and put it into waiting position
  myservo.attach(23);
  myservo.write(offpos);
  delay(1000); // You have to wait before detaching the servo for it to actually move into position
  myservo.detach();



}


void loop() {

  fPIRval = analogRead(fPIR);
  bPIRval = analogRead(bPIR);
  // print out the value you read
  Serial.print("   Front PIR:  ");
  Serial.print( fPIRval);
  Serial.print("    rear:  ");
  Serial.println(bPIRval);
  Serial.println( analogRead(A3));


  //For the debug code we are just gonna run a simple routine, Field code should have timeouts, and all kinds of other stuff
  if (fPIRval > 600 || bPIRval > 600) {
    critterDetected();
  }

  delay(1);        // delay in between reads for stability
}

//For our Debug code, we are going to just Turn the camera on, and take two photos, or
//conveniently, if we are in Video mode, we will start and stop a video

void critterDetected() {
  Serial.println("Critter detected");
  //Turn camera on
  onOffCamera();

  //Take a photo
  takePhoto();
  takePhoto();

  //TODO: Wait to see if other critters still around
  //before we shut off camera

  //The theta cannot turn off, just turns on
  //It is set to go to sleep after 3 mins, so we just leave it on in case we catch another critter
  //onOffCamera();

}

void onOffCamera() {
  Serial.println("cameraONOFF");
  digitalWrite(led, LOW);

  //Wake the Camera with a Pulse
  Mouse.set_buttons(1, 0, 0);
  myservo.attach(23);
  myservo.write(offpos); // This keeps the camera from just swinging to a random position
  //Wake the Camera with a Pulse

  delay(50); // Wait for a quick click
  Mouse.set_buttons(0, 0, 0);


  //Let camera wake up
  delay(900);

  ///Chill
  digitalWrite(led, HIGH);
}



void takePhoto() {
  Serial.println("Take photo");
    myservo.attach(23);
   myservo.write(onpos);
delay (1200);//hold for like 1.2 seconds

  //Take a photo
  digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW

//Set back to resting mode
    myservo.write(offpos);
   delay(200); //Need a delay or else it detaches before it finish moving
    myservo. detach();


  ///Chill 4 secs // Camera needs 4 seconds to process between photos
  delay(4000);
 digitalWrite(led, HIGH);
}

void togglePhotoVideo() {
  Serial.println("cameraTogglePhotoVideo");

  //2 second press
  digitalWrite(led, LOW);

  delay(2000);

  ///Chill
  digitalWrite(led, HIGH);

  delay(2000);

}
