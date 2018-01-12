

/**

 */


import processing.serial.*;
import g4p_controls.*;

Serial myPort;  // Create object from Serial class
boolean canTurnLeft;
boolean canTurnRight;

String potVal;

void setup() 
{
  size(1024, 768);

  String portName = "COM8";
  
  myPort = new Serial(this, portName, 9600);
  
  createGUI();
  customGUI();
}

public void customGUI()
{
  
}

void keyPressed() {
  if(key == 'w')
  {
    myPort.write('w');
  }
  else if(key == 's')
  {
    myPort.write('s');
  }
  else if(key == 'a')
  {
    myPort.write('a');
  }
  else if(key == 'd')
  {
    myPort.write('d');
  }  
}



void serialEvent(Serial xbee) {
  // See Tom Igoe's serial examples for more info
  potVal = xbee.readStringUntil('\0'); // read incoming data until line feed
  if (potVal != null) {
    txtAreaConsole.appendText(potVal);
  }
}

void draw() 
{
}