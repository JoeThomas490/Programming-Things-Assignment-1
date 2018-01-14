
import processing.serial.*;
import g4p_controls.*;

Serial myPort;  // Create object from Serial class
boolean canTurnLeft;
boolean canTurnRight;

String potVal;

enum ZUMO_STATES
{
  INIT,
  USER,
  CORRIDOR,
  ROOM,
  RETURN
}

ZUMO_STATES state;

void setup() 
{
    createGUI();
  
  SwitchState(ZUMO_STATES.INIT);
  
  size(1024, 768);
 
  String portName = "COM8";
  
  myPort = new Serial(this, portName, 9600);
 
}

void keyPressed() 
{
  myPort.write(key);
}

void serialEvent(Serial xbee) 
{
  potVal = xbee.readStringUntil('/'); 
  
  if(potVal != null)
  { 
    if(potVal.charAt(0) == '@')
    {
       String[] split = split(potVal, ':');
       if(split.length > 1)
       {
         print('\n');
          print(split[2]);
          if(split[1].equals("DATA"))
          { 
              if(split[2].equals("INIT"))
              {
                SwitchState(ZUMO_STATES.INIT);
              }
              else if(split[2].equals("CORRIDOR"))
              {
                SwitchState(ZUMO_STATES.CORRIDOR);
              }
              else if(split[2].equals("USER"))
              {
                SwitchState(ZUMO_STATES.USER);
              }
          }
        }
      }
      else
      {
        //txtAreaConsole.appendText(potVal);
      }
  }
}

void SwitchState(ZUMO_STATES newState)
{
  switch(newState)
  {
    case INIT:
      ToggleMovementControls(false);
      ToggleStateChangeControls(false);
      btnStopForRoom.setVisible(false);
    break;
    
    case CORRIDOR:
      ToggleMovementControls(false);
      ToggleStateChangeControls(false);
      btnStopForRoom.setVisible(true);
    break;
    
    case USER:
      ToggleMovementControls(true);
      ToggleStateChangeControls(true);
      btnStopForRoom.setVisible(false);
    break;
  }
  
  state = newState;
  
  createGUI();
  
}

void ToggleMovementControls(boolean toggle)
{
    btnForward.setVisible(toggle);
    btnLeft.setVisible(toggle);
    btnRight.setVisible(toggle);
    btnDown.setVisible(toggle);
    
    btnRight90.setVisible(toggle);
    btnLeft90.setVisible(toggle);
}

void ToggleStateChangeControls(boolean toggle)
{
    btnCorridorChange.setVisible(toggle);
    btnRoomChange.setVisible(toggle);
    
    btnRightChange.setVisible(toggle);
    btnLeftChange.setVisible(toggle);
    btnStraightChange.setVisible(toggle);
}


void draw() 
{
}