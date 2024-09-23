# ForceMomentHX711 Library

This library is designed for propeller electric motor thrust and torque measurement stand.  

## Specifications

- One loadcell is used for thrust measurement and one loadcell is used for torque measurement.   
- Each loadcell connect to a HX711 24 bit ADC.   
- This library use <HX711_ADC.h> library for HX711.   

-------------------------------------------------------------

## <HX711_ADC.h> Library Guideline

Repository for <HX711_ADC.h> library: https://github.com/olkal/HX711_ADC

**Important:**  
The HX711 sample rate can be set to **10SPS** or **80SPS** (samples per second) by pulling pin 15 high (80SPS) or low (10SPS), ref HX711 data sheet.
On fabricated HX711 modules there is usually a solder jumper on the PCB for pin 15 high/low. The rate setting can be checked by measuring the voltage on pin 15.
ADC noise is worst on the 80SPS rate. Unless very quick settling time is required, 10SPS should be the best sample rate for most applications.   

For read data by interrupts it should write code same as below:  

```cpp

attachInterrupt(digitalPinToInterrupt(HX711_dout), dataReadyISR, FALLING);

//interrupt routine:
void dataReadyISR() {
  if (LoadCell.update()) {
    newDataReady = 1;
    float i = LoadCell.getData();
  }
}
```

### HX711_ADC library method description

To use this library, open the Library Manager in the Arduino IDE and install it from there.  
**Some methods for Version: 1.2.12:**      

```cpp
HX711_ADC(uint8_t dout, uint8_t sck);              //constructor
void setGain(uint8_t gain = 128);                  //value must be 32, 64 or 128*
void begin();                                      //set pinMode, HX711 gain and power up the HX711
void begin(uint8_t gain);                          //set pinMode, HX711 selected gain and power up the HX711
void start(unsigned long t);                       //start HX711 and do tare 
void start(unsigned long t, bool dotare);          //start HX711, do tare if selected
int startMultiple(unsigned long t);                //start and do tare, multiple HX711 simultaniously
int startMultiple(unsigned long t, bool dotare);   //start and do tare if selected, multiple HX711 simultaniously
void tare();                                       //zero the scale, wait for tare to finnish (blocking)
void tareNoDelay();                                //zero the scale, initiate the tare operation to run in the background (non-blocking)
bool getTareStatus();                              //returns 'true' if tareNoDelay() operation is complete
void setCalFactor(float cal);                      //set new calibration factor, raw data is divided by this value to convert to readable data
float getCalFactor();                              //returns the current calibration factor
float getData();                                   //returns data from the moving average dataset 
int getReadIndex();                                //for testing and debugging
float getConversionTime();                         //for testing and debugging
float getSPS();                                    //for testing and debugging
bool getTareTimeoutFlag();                         //for testing and debugging
void disableTareTimeout();                         //for testing and debugging
long getSettlingTime();                            //for testing and debugging
void powerDown();                                  //power down the HX711
void powerUp();                                    //power up the HX711
long getTareOffset();                              //get the tare offset (raw data value output without the scale "calFactor")
void setTareOffset(long newoffset);                //set new tare offset (raw data value input without the scale "calFactor")
uint8_t update();                                  //if conversion is ready; read out 24 bit data and add to dataset
void setSamplesInUse(int samples);                 //overide number of samples in use for Moving average filter.
int getSamplesInUse();                             //returns current number of samples in use
void resetSamplesIndex();                          //resets index for dataset
bool refreshDataSet();                             //Fill the whole dataset up with new conversions, i.e. after a reset/restart (this function is blocking once started)
bool getDataSetStatus();                           //returns 'true' when the whole dataset has been filled up with conversions, i.e. after a reset/restart
float getNewCalibration(float known_mass);         //returns and sets a new calibration value (calFactor) based on a known mass input
bool getSignalTimeoutFlag();                       //returns 'true' if it takes longer time then 'SIGNAL_TIMEOUT' for the dout pin to go low after a new conversion is started
```

