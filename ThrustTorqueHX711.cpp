
#include "ThrustTorqueHX711.h"

ThrustTorqueHX711::ThrustTorqueHX711()
{
  parameters.THRUST_DOUT_PIN = -1;
  parameters.THRUST_SCK_PIN = -1;
  parameters.TORQUE_DOUT_PIN = -1;
  parameters.TORQUE_SCK_PIN = -1;
  parameters.TORQUE_ARM = 0.15;
  parameters.TORQUE_SCALE = 1;
  parameters.THRUST_SCALE = 1;
  parameters.GRAVITY = 9.81;
  parameters.SAMPLE_USE = 3;
  parameters.TARE_FLAG = false;
  parameters.TARE_TIME = 3000;
  
  value.thrust = 0;
  value.torque = 0;
  value.torqueForce = 0;

  thrustLoadcell = nullptr;
  torqueLoadcell = nullptr;

  _thrustDefinedFlag = false;
  _torqueDefinedFlag = false;
}

ThrustTorqueHX711::~ThrustTorqueHX711()
{
  
}

bool ThrustTorqueHX711::setThrustHX711Pins(int8_t dout_pin, int8_t sck_pin)
{
  if( (dout_pin < 0) || (sck_pin < 0) )
  {
    errorMessage = "Error ThrustTorqueHX711: Dout and Sck pins for thrust loadcell is not correct value.";
    return false;
  }

  parameters.THRUST_DOUT_PIN = dout_pin;
  parameters.THRUST_SCK_PIN = sck_pin;

  return true;
}

bool ThrustTorqueHX711::setTorqueHX711Pins(int8_t dout_pin, int8_t sck_pin)
{
  if( (dout_pin < 0) || (sck_pin < 0) )
  {
    errorMessage = "Error ThrustTorqueHX711: Dout and Sck pins for torque loadcell is not correct value.";
    return false;
  }

  parameters.TORQUE_DOUT_PIN = dout_pin;
  parameters.TORQUE_SCK_PIN = sck_pin;
  
  return true;
}

bool ThrustTorqueHX711::init(void)
{
  if(!_checkParameters())
  {
    return false;
  }

  if( (parameters.THRUST_DOUT_PIN >= 0) || (parameters.THRUST_SCK_PIN >= 0) )
  {
    thrustLoadcell = new HX711_ADC(parameters.THRUST_DOUT_PIN, parameters.THRUST_SCK_PIN);
    thrustLoadcell->setCalFactor(parameters.THRUST_SCALE);
    thrustLoadcell->setSamplesInUse(parameters.SAMPLE_USE);      //overide number of samples in use for smoothing data output.
    thrustLoadcell->begin();   //set pinMode, HX711 gain and power up the HX711
    thrustLoadcell->start(parameters.TARE_TIME, parameters.TARE_FLAG);   //start HX711, do tare if selected
    _thrustDefinedFlag = true;

  }

  if( (parameters.TORQUE_DOUT_PIN >= 0) || (parameters.TORQUE_SCK_PIN >= 0) )
  {
    torqueLoadcell = new HX711_ADC(parameters.TORQUE_DOUT_PIN, parameters.TORQUE_SCK_PIN);
    torqueLoadcell->setCalFactor(parameters.TORQUE_SCALE);
    torqueLoadcell->setSamplesInUse(parameters.SAMPLE_USE);
    torqueLoadcell->begin();
    torqueLoadcell->start(parameters.TARE_TIME, parameters.TARE_FLAG);
    _torqueDefinedFlag = true;
  }

  delay(1000);

  if(_thrustDefinedFlag)
  {
    thrustLoadcell->tareNoDelay();      // zero offset
  }
  
  if(_torqueDefinedFlag)
  {
    torqueLoadcell->tareNoDelay();      // zero offset
  }
  
  return true;
}

bool ThrustTorqueHX711::_checkParameters(void)
{
  bool state = (parameters.THRUST_SCALE > 0) && (parameters.TORQUE_SCALE > 0) && (parameters.TORQUE_ARM >= 0) && (parameters.GRAVITY >= 0);

  if(state == false)
  {
    errorMessage = "Error ThrustTorqueHX711: one or some parameters is not correct value.";
    return false;
  }

  return true;
}

void ThrustTorqueHX711::update(void)
{
  //if conversion is ready; read out 24 bit data and add to dataset
  if(thrustLoadcell->update())     
  {
    value.thrust = thrustLoadcell->getData();              //returns data from the moving average dataset 
  }  

  if(torqueLoadcell->update())
  {
    value.torqueForce = torqueLoadcell->getData();
    value.torque = value.torqueForce * (parameters.GRAVITY / 1000.0) * parameters.TORQUE_ARM;
  }
}

void ThrustTorqueHX711::calibrate(void)
{
  delay(2000);
  thrustLoadcell->tareNoDelay();
  torqueLoadcell->tareNoDelay();
}
