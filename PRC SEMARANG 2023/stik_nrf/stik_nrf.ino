#include <PS2X_lib.h>
#include <RF24_config.h>
#include <RF24.h>
#include <nRF24L01.h>
#include <SPI.h>

RF24 radio(9, 10);  // CE, CSN
const byte address[10] = "ADDRESS1";

PS2X ps2x;

//right now, the library does NOT support hot-pluggable controllers, meaning
//you must always either restart your Arduino after you connect the controller,
//or call config_gamepad(pins) again after connecting the controller.

int error = 0;
byte type = 0;
byte vibrate = 0;

#define PIN_02_PS2X_ATT 5
#define PIN_03_PS2X_COM 6
#define PIN_04_PS2X_DTA 7
#define PIN_05_PS2X_CLK 8

int key_analog_up = 0;
int key_analog_down = 0;
int key_analog_left = 0;
int key_analog_right = 0;

struct {
  int lx;
  int ly;
  int rx;
  int ry;
} analog;


void setup() {
  Serial.begin(57600);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();


  error = ps2x.config_gamepad(PIN_05_PS2X_CLK, PIN_03_PS2X_COM, PIN_02_PS2X_ATT, PIN_04_PS2X_DTA, true, true);  //GamePad(clock, command, attention, data, Pressures?, Rumble?)




  if (error == 0) {
    Serial.println("Found Controller, configured successful");
    Serial.println("Try out all the buttons, X will vibrate the controller, faster as you press harder;");
    Serial.println("holding L1 or R1 will print out the analog stick values.");
    Serial.println("Go to www.billporter.info for updates and to report bugs.");
  }

  else if (error == 1)
    Serial.println("No controller found, check wiring, see readme.txt to enable debug. visit www.billporter.info for troubleshooting tips");

  else if (error == 2)
    Serial.println("Controller found but not accepting commands. see readme.txt to enable debug. Visit www.billporter.info for troubleshooting tips");

  else if (error == 3)
    Serial.println("Controller refusing to enter Pressures mode, may not support it. ");

  type = ps2x.readType();
  switch (type) {
    case 0:
      Serial.println("Unknown Controller type");
      break;
    case 1:
      Serial.println("DualShock Controller Found");
      break;
    case 2:
      Serial.println("GuitarHero Controller Found");
      break;
  }
}

void loop() {
  /* You must Read Gamepad to get new values
   Read GamePad and set vibration values
   ps2x.read_gamepad(small motor on/off, larger motor strenght from 0-255)
   if you don't enable the rumble, use ps2x.read_gamepad(); with no values
   
   you should call this at least once a second
   */
  // while(1){
  //   send("SELECT");
  //   delay(1000);
  // }
  if (error == 1)
    return;

  if (type == 2) {

    ps2x.read_gamepad();  //read controller

    if (ps2x.ButtonPressed(GREEN_FRET))
      Serial.println("Green Fret Pressed");
    if (ps2x.ButtonPressed(RED_FRET))
      Serial.println("Red Fret Pressed");
    if (ps2x.ButtonPressed(YELLOW_FRET))
      Serial.println("Yellow Fret Pressed");
    if (ps2x.ButtonPressed(BLUE_FRET))
      Serial.println("Blue Fret Pressed");
    if (ps2x.ButtonPressed(ORANGE_FRET))
      Serial.println("Orange Fret Pressed");


    if (ps2x.ButtonPressed(STAR_POWER))
      Serial.println("Star Power Command");

    if (ps2x.Button(UP_STRUM))  //will be TRUE as long as button is pressed
      Serial.println("Up Strum");
    if (ps2x.Button(DOWN_STRUM))
      Serial.println("DOWN Strum");


    if (ps2x.Button(PSB_START))  //will be TRUE as long as button is pressed
      send("START");
    if (ps2x.Button(PSB_SELECT))
      send("SELECT");


    if (ps2x.Button(ORANGE_FRET))  // print stick value IF TRUE
    {
      Serial.print("Wammy Bar Position:");
      Serial.println(ps2x.Analog(WHAMMY_BAR), DEC);
    }
  }

  else {  //DualShock Controller

    ps2x.read_gamepad(false, vibrate);  //read controller and set large motor to spin at 'vibrate' speed
    read_analog_stick();
    stop_button();
    if (ps2x.Button(PSB_START))  //will be TRUE as long as button is pressed
      send("START");
    if (ps2x.Button(PSB_SELECT))
      send("SELECT");


    if (ps2x.Button(PSB_PAD_UP)) {  //will be TRUE as long as button is pressed
      send("PU");
    }
    if (ps2x.Button(PSB_PAD_RIGHT)) {
      send("PR");
    }
    if (ps2x.Button(PSB_PAD_LEFT)) {
      send("PL");
    }
    if (ps2x.Button(PSB_PAD_DOWN)) {
      send("PD");
    }

    if (ps2x.Button(PSB_L3))
      send("L3");
    if (ps2x.Button(PSB_R3))
      send("R3");
    if (ps2x.Button(PSB_L2))
      send("L2");
    if (ps2x.Button(PSB_R2))
      send("R2");
    if (ps2x.Button(PSB_GREEN))
      send("A");


    // vibrate = ps2x.Analog(PSAB_BLUE);  //this will set the large motor vibrate speed based on
                                       //how hard you press the blue (X) button

    // if (ps2x.NewButtonState())  //will be TRUE if any button changes state (on to off, or off to on)
    // {
    // }

    // if (ps2x.ButtonReleased(1)) send("stop");
 
    if (ps2x.ButtonPressed(PSB_RED)) {  //will be TRUE if button was JUST pressed
      send("O");
    }

    if (ps2x.ButtonPressed(PSB_PINK)) {  //will be TRUE if button was JUST released
      send("D");
    }
    if (ps2x.NewButtonState(PSB_BLUE)) {  //will be TRUE if button was JUST pressed OR released
      // delay(500);
      send("X");
    }


   

    if (ps2x.Button(PSB_R1))  // print stick values if either is TRUE
    {
      send("R1");
    }

    if (ps2x.Button(PSB_L1))  // print stick values if either is TRUE
    {
      send("L1");
    }


    if (key_analog_up) {
      send("AU");
    }
    if (key_analog_right) {
      send("AR");
      delay(500);
    }
    if (key_analog_left) {
      send("AL");
      delay(500);
    }
    if (key_analog_down) {
      send("AD");
    }
  }


  delay(50);
}


void read_analog_stick() {
  analog.ly = 128 - (ps2x.Analog(PSS_LY));
  analog.lx = 128 - (ps2x.Analog(PSS_LX));
  analog.ry = 128 - (ps2x.Analog(PSS_RY));
  analog.rx = 128 - (ps2x.Analog(PSS_RX));
  if (analog.ly > 50) key_analog_up = 1;
  else key_analog_up = 0;
  if (analog.ly < -50) key_analog_down = 1;
  else key_analog_down = 0;
  if (analog.lx > 50) key_analog_left = 1;
  else key_analog_left = 0;
  if (analog.lx < -50) key_analog_right = 1;
  else key_analog_right = 0;
}
void send(String kirim) {
  Serial.println(kirim);
  String myString = kirim;
  char charArray[myString.length() + 1];
  myString.toCharArray(charArray, myString.length() + 1);

  // Kirim data
  radio.write(&charArray, sizeof(charArray));
}
//////////////////////
void stop_button(){
    if (ps2x.ButtonReleased(PSB_L1)) {
   send("l1stop");

  }

  if (ps2x.ButtonReleased(PSB_L2)) {
   send("l2stop");

  }

  if (ps2x.ButtonReleased(PSB_R1)) {
   send("r1stop");

  }

  if (ps2x.ButtonReleased(PSB_R2)) {
   send("r2stop");

  }

  if (ps2x.ButtonReleased(PSB_GREEN)) {
   send("greenstop");

  }

  if (ps2x.ButtonReleased(PSB_RED)) {
   send("redstop");

  }

  if (ps2x.ButtonReleased(PSB_BLUE)) {
   send("bluestop");

  }

  if (ps2x.ButtonReleased(PSB_PINK)) {
   send("pinkstop");

  }

  if (ps2x.ButtonReleased(PSB_PAD_UP)) {
   send("pustop");

  }

  if (ps2x.ButtonReleased(PSB_PAD_RIGHT)) {
   send("prstop");

  }

  if (ps2x.ButtonReleased(PSB_PAD_DOWN)) {
   send("pdstop");

  }

  if (ps2x.ButtonReleased(PSB_PAD_LEFT)) {
   send("plstop");

  }

  // if (ps2x.ButtonReleased(13)) {
  //  send("13stop");

  // }

  // if (ps2x.ButtonReleased(14)) {
  //  send("14stop");

  // }

  // if (ps2x.ButtonReleased(15)) {
  //  send("15stop");

  // }

  // if (ps2x.ButtonReleased(16)) {
  //  send("16stop");

  // }
}