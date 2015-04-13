#include <SPI.h>
#include <Andee.h> // Don't forget the necessary libraries

// define inputs
AndeeHelper toggleButton;
AndeeHelper nameSetting;
AndeeHelper speedSetting;
AndeeHelper forwardButton;
AndeeHelper leftButton;
AndeeHelper fireButton;
AndeeHelper rightButton;
AndeeHelper reverseButton;

char cmdReply[64]; // String buffer
char newBluetoothName[] = "Remote"; // New device name
char commandString[100]; // String to store the new device name and device command into one
char user_name_in[32];
char project_name[40] = "Remote";
char project_name_default[40] = "Remote";

int state = 0;
int speed_in = 0;
int speed_default = 75;

void setup() {
  Andee.begin();
  Andee.clear();

  // We need to combine the new device name with the device command
  sprintf(commandString, "SET BT NAME %s", newBluetoothName);
  // Send command to change device name
  Andee.sendCommand(commandString, cmdReply);
  
  setInitialData(); // Define object types and their appearance
  
  // DO NOT USE -- causes disconnection -- power reset needed!
  //Andee.screenAlwaysOn(true);
}

// This is the function meant to define the types and the apperance of
// all the objects on your smartphone
void setInitialData() {  
  
  // Let's draw a toggle button
  toggleButton.setId(0); // Don't forget to assign a unique ID number
  toggleButton.setType(BUTTON_IN); // Defines object as a button
  toggleButton.setLocation(0,0,ONE_THIRD);
  toggleButton.setTitle("Turn On"); // Sets the initial words for button
  toggleButton.setColor(GREEN);
  // You can't use setData() and setUnit() for buttons.
  
  // Set Project name
  nameSetting.setId(1);
  nameSetting.setType(KEYBOARD_IN); // Sets object as a text input button
  nameSetting.setLocation(0,1,ONE_THIRD);
  nameSetting.setTitle( project_name_default );
  nameSetting.setKeyboardType(ALPHA_NUMERIC); 
  
  // Let's draw a speed control slider! ///////////////////////////////////////
  speedSetting.setId(2);  
  speedSetting.setType(SLIDER_IN); // Set object as a slider
  speedSetting.setLocation(0, 2, ONE_THIRD); // Sliders can only be full size
  speedSetting.setTitle("speed");
  speedSetting.setSliderMinMax(0, 100, 0);
  speedSetting.setSliderInitialValue( speed_default );
  speedSetting.setSliderNumIntervals(100);
  speedSetting.setSliderReportMode(ON_VALUE_CHANGE);
  
  forwardButton.setId(10); // Don't forget to assign a unique ID number
  forwardButton.setType(BUTTON_IN); // Defines object as a button
  forwardButton.setLocation(1,0,FULL);
  forwardButton.setTitle("Forward");
  forwardButton.requireAck(false); // You need this line to allow for multiple button presses
  // You can't use setData() and setUnit() for buttons.
  
  leftButton.setId(20); // Don't forget to assign a unique ID number
  leftButton.setType(BUTTON_IN); // Defines object as a button
  leftButton.setLocation(2,0,ONE_THIRD);
  leftButton.setTitle("Left");
  leftButton.requireAck(false); // You need this line to allow for multiple button presses
  // You can't use setData() and setUnit() for buttons.
  
  fireButton.setId(21); // Don't forget to assign a unique ID number
  fireButton.setType(BUTTON_IN); // Defines object as a button
  fireButton.setLocation(2,1,ONE_THIRD);
  fireButton.setTitle("Fire!");
  fireButton.setColor(RED);
  fireButton.requireAck(false); // You need this line to allow for multiple button presses
  // You can't use setData() and setUnit() for buttons.
  
  rightButton.setId(23); // Don't forget to assign a unique ID number
  rightButton.setType(BUTTON_IN); // Defines object as a button
  rightButton.setLocation(2,2,ONE_THIRD);
  rightButton.setTitle("Right");
  rightButton.requireAck(false); // You need this line to allow for multiple button presses
  // You can't use setData() and setUnit() for buttons.
  
  reverseButton.setId(30); // Don't forget to assign a unique ID number
  reverseButton.setType(BUTTON_IN); // Defines object as a button
  reverseButton.setLocation(3,0,FULL);
  reverseButton.setTitle("Reverse");
  reverseButton.requireAck(false); // You need this line to allow for multiple button presses
  // You can't use setData() and setUnit() for buttons.
}  

void loop() {
  
  speed_in = speedSetting.getSliderValue(INT); // Retrieve integer value
  speedSetting.update();
  
  if ( nameSetting.isPressed() ) {
    memset( user_name_in, 0x00, 32 ); // Empty the contents of the string before receiving user input
    nameSetting.ack(); // Acknowledge button press or else phone will be left waiting
    nameSetting.getKeyboardMessage( user_name_in ); // Display keyboard and store input into userInput
    sprintf( project_name, "%s", user_name_in );
    nameSetting.setTitle( project_name );   
    sprintf(commandString, "SET BT NAME %s", user_name_in );
    Andee.sendCommand( commandString, cmdReply );
  }
  nameSetting.update();
  
  // Do this as long as the forward button is pressed
  if( forwardButton.getButtonPressCount() > 0 ) {
    // Add your press and hold action here:
    // move the robot forward
  }
  forwardButton.update();
 
  // Do this as long as the left button is pressed
  if( leftButton.getButtonPressCount() > 0 ) {
    // Add your press and hold action here:
    // move the robot forward
  }
  leftButton.update();
 
  // Do this as long as the left button is pressed
  if( fireButton.getButtonPressCount() > 0 ) {
    // Add your press and hold action here:
    // move the robot forward
  }
  fireButton.update();
 
  // Do this as long as the right button is pressed
  if( rightButton.getButtonPressCount() > 0 ) {
    // Add your press and hold action here:
    // move the robot forward
  }
  rightButton.update();
 
  // Do this as long as the reverse button is pressed
  if( reverseButton.getButtonPressCount() > 0 ) {
    // Add your press and hold action here:
    // move the robot forward
  }
  reverseButton.update();

  // Here's how you code the button action
  if ( toggleButton.isPressed() ) {
    // Prevent user from accidentally pressing the button again
    // until Arduino has sent an acknowledgement 
    toggleButton.ack();
    if (state == 0) {
      toggleButton.setTitle("Turn off");
      state = 1; // Change state 
      toggleButton.setColor(RED);   
      // Add additional actions here to turn on something
    } else {
      toggleButton.setTitle("Turn on");
      state = 0; // Change state 
      toggleButton.setColor(GREEN); 
      // Add additional actions here to turn off something
    }  
  }
  toggleButton.update(); // Update your button to reflect the change in state
}

