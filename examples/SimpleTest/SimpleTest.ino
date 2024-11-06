
#include <ThrustTorqueHX711.h>

// ######################################################################
// Define pins:

#define THRUST_HX711_DOUT                  33           //mcu > HX711 dout pin
#define THRUST_HX711_SCK                   35           //mcu > HX711 sck pin

#define TORQUE_HX711_DOUT                  27           //mcu > HX711 dout pin
#define TORQUE_HX711_SCK                   29           //mcu > HX711 sck pin

// ###################################################################
// Define global variables and objects:

ThrustTorqueHX711 thrustTorqueUnit;

// ####################################################################
// Setup:

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  
  thrustTorqueUnit.setThrustHX711Pins(THRUST_HX711_DOUT, THRUST_HX711_SCK);
  thrustTorqueUnit.setTorqueHX711Pins(TORQUE_HX711_DOUT, TORQUE_HX711_SCK);

  thrustTorqueUnit.parameters.THRUST_SCALE = 433.553 * 10 / 3 ;
  thrustTorqueUnit.parameters.TORQUE_SCALE = 433.553;

  if(!thrustTorqueUnit.init())
  {
    Serial.println(thrustTorqueUnit.errorMessage);
  }
}

// ###############################################################
// Loop:

void loop() {
  // put your main code here, to run repeatedly:
  thrustTorqueUnit.update();

  Serial.print(thrustTorqueUnit.value.thrust);Serial.print(", ");
  Serial.println(thrustTorqueUnit.value.torqueForce);
  
  delay(100);
}

// ##########################################################


