#ifndef FORCE_MOMENT_HX711_H
#define FORCE_MOMENT_HX711_H

#include <HX711_ADC.h>                    // For the HX711 24-bit ADC for weight scales. https://github.com/olkal/HX711_ADC


class ForceMomentHX711
{
  public:

    String errorMessage;

    struct ParametersStruct
    {
      #define TORQUE_FACTOR             0.195       // [m]. Proportional gain for transfer thrust force [N] to torque moment [N.m]. The distance of loadcell point force and center of motor mount.
      #define LOADCELL_SAMPLE_USE       3           // Number of Sample of loadcell for Moving average filter
      #define LOADCELL_THRUST_SCALE     105.35108   // Loadcell Measurement scale @5.1 volt   // 3.19, 105.35108
      #define LOADCELL_TORQUE_SCALE     218.3545    // Loadcell Measurement scale @5.1 volt    // 3.3*2, 218.3545
      #define TARE_TIME                 3000        // tare time duration in [ms]
      #define TARE_FLAG                 false       // flag for enable/disable zero loadcell offset at initialization. 
      #define GRAVITY                   9.798       // Gravity of the earth. [Approximately in tehran]
    }parameters;

    // Loadcells:
    // Loadcell HX711 Module pins:
    #define HX711_DOUT_1                  33           //mcu > HX711 dout pin
    #define HX711_SCK_1                   35           //mcu > HX711 sck pin

    #define HX711_DOUT_2                  27           //mcu > HX711 dout pin
    #define HX711_SCK_2                   29           //mcu > HX711 sck pin

    #define HX711_DOUT_3                  23           //mcu > HX711 dout pin
    #define HX711_SCK_3                   25           //mcu > HX711 sck pin

    struct ValueStruct
    {

    }value;

    float loadcell_force[2];                            // loadcell force. [gr]
    float thrust,torque;                                // Thrust and Torque calculated from loadcells. [gr],[N.m]

    ForceMomentHX711();

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
