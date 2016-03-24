

int b;

void setup() {
  Serial.begin(9600);

    pinMode(9, OUTPUT);
  b=0;
}

void loop() {
  // to view the data the serial monitor.
 
// Serial.write(analogRead(0));

//  analogWrite(9, b++);
//  delay(3);



 
Serial.println( analogRead(0));
//  
//  
//  // write one byte
//  //Serial.write(analogRead(0));
//
//  
// use a marker :
//  Serial.print(analogRead(0));

  Serial.print(analogRead(0));  
  Serial.print(":");
  


  
}
