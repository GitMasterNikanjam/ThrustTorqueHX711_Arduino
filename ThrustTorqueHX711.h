#ifndef FORCE_MOMENT_HX711_H
#define FORCE_MOMENT_HX711_H

#include <HX711_ADC.h>                    // For the HX711 24-bit ADC for weight scales. https://github.com/olkal/HX711_ADC


class ForceMomentHX711
{
  public:

    // Last error accured for object.
    String errorMessage;

    // Parameters structure
    struct ParametersStruct
    {
      float MOMENT_FACTOR;          // [m]. Proportional gain for transfer thrust force [N] to torque moment [N.m]. The distance of loadcell point force and center of motor mount.
      uint8_t SAMPLE_USE;           // Number of Sample of loadcell for Moving average filter
      float THRUST_SCALE;           // Loadcell Measurement scale @5.1 volt   // 3.19, 105.35108
      float MOMENT_SCALE;           // Loadcell Measurement scale @5.1 volt    // 3.3*2, 218.3545
      uint16_t TARE_TIME;           // tare time duration in [ms]
      bool TARE_FLAG;               // flag for enable/disable zero loadcell offset at initialization. 
      float GRAVITY;                // Gravity of the earth. [Approximately in tehran]

      uint8_t THRUST_DOUT;          //mcu > HX711 dout pin
      uint8_t THRUST_SCK;           //mcu > HX711 sck pin
      uint8_t MOMENT_DOUT;          //mcu > HX711 dout pin
      uint8_t MOMENT_SCK;           //mcu > HX711 sck pin
    }parameters;

    // Value structure
    struct ValueStruct
    {
      int32_t rawThrust;                            // loadcell force. [gr]
      int32_t rawMoment;
      float thrust;                                // Thrust and Torque calculated from loadcells. [gr],[N.m]
      float moment;
    }value;

    HX711_ADC thrustLoadcell;    // HX711 Object for loadcell_1
    HX711_ADC momentLoadcell;    // HX711 Object for loadcell_2

    /**
     * Constructor.
     */
    ForceMomentHX711();

    /**
     * Destructor.
     */
    ~ForceMomentHX711();

    bool init(void);

    void update(void);

    void calibration(void);

    void read(void);

  private:

    bool _checkParameters(void);

    void _forceCalculate(void);

    void _momentCalculate(void);

};


#endif
