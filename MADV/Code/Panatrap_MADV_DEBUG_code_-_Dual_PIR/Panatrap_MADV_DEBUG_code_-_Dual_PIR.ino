
/*
PanaTrap - MADV
Debug Code for the turning the Xiaomi MiSphere (MADV) camera
into a remotely controlled, 
PIR triggered, Camera Trap

*/

//Front PIR motion sensors
int fPIR=A4;
int fPIRval=-1;

//Back PIR motion sensors
int bPIR=A3;
int bPIRval=-1;

///camera trigger operants
int led = 13;
int trigger=12;
int gndtrigger = 9;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);

  pinMode(A1,OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A5,OUTPUT);

digitalWrite(A1,LOW);

digitalWrite(A2,HIGH);

digitalWrite(A5,LOW);

//Camera Trigger stuff
  pinMode(led, OUTPUT);
    pinMode(trigger, OUTPUT);
        pinMode(gndtrigger, OUTPUT);

  digitalWrite(led, HIGH); 
  digitalWrite(trigger, HIGH); 
   digitalWrite(trigger, LOW); 

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
  

  if(fPIRval>600||bPIRval>600){
critterDetected();
  }
  delay(1);        // delay in between reads for stability
}

void critterDetected(){

  Serial.println("Critter detected");
//Turn camera on
onOffCamera();

//Take a photo
takePhoto();
takePhoto();

//TODO: Wait to see if other critters still around 
//before we shut off camera

onOffCamera();



}

void onOffCamera(){
    Serial.println("cameraONOFF");

    //5 second turn on
  digitalWrite(led, LOW);   
    digitalWrite(trigger,LOW);  
digitalWrite(gndtrigger,LOW);
  delay(5000);              

///Chill
   digitalWrite(led, HIGH);   
    digitalWrite(trigger, HIGH);   
  digitalWrite(gndtrigger,LOW);
  delay(2000);             
}

void takePhoto(){
    Serial.println("Take photo");

//Take a photo
    digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
    digitalWrite(trigger,LOW);   // turn the LED on (HIGH is the voltage level)
digitalWrite(gndtrigger,LOW);
  delay(1000);               // wait for a second

  ///Chill 4 secs
   digitalWrite(led, HIGH);   
    digitalWrite(trigger, HIGH);
  digitalWrite(gndtrigger,LOW);
  delay(4000);               

}
