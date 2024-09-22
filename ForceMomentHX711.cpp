
#include "ForceMomentHX711.h"


 void thrust_calculate(void)
  {
  thrust = abs(loadcell_force[0]);    // [gr]
  }

  // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

  void torque_calculate(void)
  {
  torque = (abs(loadcell_force[1])) * TORQUE_FACTOR * GRAVITY/1000.0;  // N.m
  }

  // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  void loadcells_read(void)
  {
  if(LOADCELL_1.update())                                //if conversion is ready; read out 24 bit data and add to dataset
  loadcell_force[0] = LOADCELL_1.getData();              //returns data from the moving average dataset 
  if(LOADCELL_2.update())
  loadcell_force[1] = LOADCELL_2.getData();
  }

  // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

  void loadcells_calibrate(void)
  {
    delay(2000);
    LOADCELL_1.tareNoDelay();
    LOADCELL_2.tareNoDelay();
  }

  // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

  void init_loadcells(void)
  {
    LOADCELL_1.begin();   //set pinMode, HX711 gain and power up the HX711
    LOADCELL_2.begin();
    
    LOADCELL_1.start(TARE_TIME, TARE_FLAG);   //start HX711, do tare if selected
    LOADCELL_2.start(TARE_TIME, TARE_FLAG);

    LOADCELL_1.setCalFactor(LOADCELL_THRUST_SCALE);
    LOADCELL_2.setCalFactor(LOADCELL_TORQUE_SCALE);
    
    LOADCELL_1.setSamplesInUse(LOADCELL_SAMPLE_USE);      //overide number of samples in use for smoothing data output.
    LOADCELL_2.setSamplesInUse(LOADCELL_SAMPLE_USE);

    loadcells_calibrate(); // zero offset

  }