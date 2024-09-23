#ifndef THRUST_TORQUE_HX711_H
#define THRUST_TORQUE_HX711_H

#include <HX711_ADC.h>                    // For the HX711 24-bit ADC for weight scales. https://github.com/olkal/HX711_ADC


class ThrustTorqueHX711
{
  public:

    // Last error accured for object.
    String errorMessage;

    // Parameters structure
    struct ParametersStruct
    {
      float TORQUE_ARM;             // [m]. Proportional gain for transfer thrust force [N] to torque moment [N.m]. The distance of loadcell point force and center of motor mount.
      uint8_t SAMPLE_USE;           // Number of Sample of loadcell for Moving average filter
      float THRUST_SCALE;           // Loadcell Measurement scale @5.1 volt   // 3.19, 105.35108
      float THORQUE_SCALE;          // Loadcell Measurement scale @5.1 volt    // 3.3*2, 218.3545
      uint16_t TARE_TIME;           // tare time duration in [ms]
      bool TARE_FLAG;               // flag for enable/disable zero loadcell offset at initialization. 
      float GRAVITY;                // Gravity of the earth. [Approximately in tehran]
      uint8_t THRUST_DOUT_PIN;      //mcu > HX711 dout pin
      uint8_t THRUST_SCK_PIN;       //mcu > HX711 sck pin
      uint8_t TORQUE_DOUT_PIN;      //mcu > HX711 dout pin
      uint8_t TORQUE_SCK_PIN;       //mcu > HX711 sck pin
    }parameters;

    // Value structure
    struct ValueStruct
    {
      int32_t rawThrust;                            // loadcell force. [gr]
      int32_t rawTorque;
      float thrust;                                // Thrust and Torque calculated from loadcells. [gr],[N.m]
      float torque;
    }value;

    HX711_ADC* thrustLoadcell;    // HX711 Object for loadcell_1
    HX711_ADC* torqueLoadcell;    // HX711 Object for loadcell_2

    /**
     * Constructor.
     */
    ThrustTorqueHX711();

    /**
     * Destructor.
     */
    ~ThrustTorqueHX711();

    bool init(void);

    void update(void);

    void calibration(void);

    void read(void);

  private:

    bool _checkParameters(void);

    void _thrustCalculate(void);

    void _torqueCalculate(void);

};


#endif
