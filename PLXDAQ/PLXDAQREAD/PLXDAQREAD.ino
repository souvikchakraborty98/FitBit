float readVolt;
int c;
void setup() {
 Serial.begin(38400);               //Fastest baudrate
 Serial.println("CLEARDATA");        //This string is defined as a 
                                      // commmand for the Excel VBA 
                                      // to clear all the rows and columns
 Serial.println("LABEL,Read Volt"); 
 c=2; 
                                      //LABEL command creates label for 
                                      // columns in the first row with bold font
}

void loop() {
  delay(100);
  Serial.println( (String) "CELL,GET,FROMSHEET,Furthersheet,C,"+c);
  readVolt = Serial.readStringUntil(10).toFloat();
  if(readVolt==0)
  {
  Serial.println("PAUSELOGGING");
  while(true)
  {}
  }
  else
  {
  Serial.print("DATA");
  Serial.print(",");
  Serial.println(readVolt);
  c++;
  }
  
  

}
