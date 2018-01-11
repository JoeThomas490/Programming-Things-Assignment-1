/**

 */


import processing.serial.*;

Serial myPort;  // Create object from Serial class
int val;        // Data received from the serial port
boolean canTurnLeft;
boolean canTurnRight;

void setup() 
{
  size(1024, 765);
  String portName = "COM8";
  
  myPort = new Serial(this, portName, 9600);
}

void draw() 
{
  background(255);
  
//---------UP SQUARE-------------------
  if(mouseOverUp() == true)
  {
    fill(0);
    myPort.write('W');
  }
  else
  {
    fill(204);
  }
  //Draw top square
  rect(400, 100, 250, 100);         // Draw a square
//-----------END UP SQUARE------------------ 
//-----------DOWN SQUARE------------------ 
  if(mouseOverDown() == true)
  {
    fill(0);
    myPort.write('S');
  }
  else
  {
    fill(204);
  }  
  //Draw bottom square
  rect(400, 600, 250, 100);
//-----------END DOWN SQUARE------------------   
//-----------LEFT SQUARE------------------ 
  if(mouseOverLeft() == true)
  {
    fill(0);
    if(canTurnLeft == true)
    {
      myPort.write('A');
      canTurnLeft = false;
    }
  }
  else
  {
    fill(204);
    canTurnLeft = true;
  } 
  //Draw left square
  rect(250, 300, 100, 250);
//-----------END LEFTSQUARE------------------ 
//-----------RIGHT SQUARE------------------ 
  if(mouseOverRight() == true)
  {
    fill(0);
    if(canTurnRight == true)
    {
      myPort.write('D');
      canTurnRight = false;
    }
  }
  else
  {
    fill(204);
    canTurnRight = true;
  }  
  //Draw right square
  rect(750, 300, 100, 250);
//-----------END RIGHT SQUARE------------------ 


//-----------STOP SQUARE----------------------

  if(mouseOverStop() == true)
  {
    fill(3000);
    myPort.write('E');
  }
  else
  {
    fill(100);
  }
  rect(450,350, 150,150);
//----------END STOP SQUARE----------------

//-----------Horn SQUARE----------------------

  if(mouseOverStop() == true)
  {
    fill(3000);
    myPort.write('Q');
  }
  else
  {
    fill(100);
  }
  rect(450,350, 150,150);
//----------END Horn SQUARE----------------
}

boolean mouseOverRect() { // Test if mouse is over square
  return ((mouseX >= 50) && (mouseX <= 150) && (mouseY >= 50) && (mouseY <= 150));
}

boolean mouseOverUp()
{
   return ((mouseX >= 400) && (mouseX <= 650) && (mouseY >= 100) && (mouseY <= 200));
}

boolean mouseOverDown()
{
   return ((mouseX >= 400) && (mouseX <= 650) && (mouseY >= 600) && (mouseY <= 700));
}

boolean mouseOverLeft()
{
   return ((mouseX >= 250) && (mouseX <= 350) && (mouseY >= 300) && (mouseY <= 550));
}

boolean mouseOverRight()
{
   return ((mouseX >= 750) && (mouseX <= 850) && (mouseY >= 300) && (mouseY <= 550));
}

boolean mouseOverStop()
{
   return ((mouseX >= 450) && (mouseX <= 600) && (mouseY >= 350) && (mouseY <= 500));
} 