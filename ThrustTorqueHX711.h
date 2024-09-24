#ifndef THRUST_TORQUE_HX711_H
#define THRUST_TORQUE_HX711_H

// ######################################################################
// Include libraries:

#include <HX711_ADC.h>                    // For the HX711 24-bit ADC for weight scales. https://github.com/olkal/HX711_ADC

// #######################################################################
// ThrustTorqueHX711 class:

class ThrustTorqueHX711
{
  public:

    // Last error accured for object.
    String errorMessage;

    // Parameters structure
    struct ParametersStruct
    {
      float TORQUE_ARM;           // [m]. Proportional gain for transfer thrust force [N] to torque moment [N.m]. The distance of loadcell point force and center of motor mount.         
      uint8_t SAMPLE_USE;         // Number of Sample of loadcell for Moving average filter
      float THRUST_SCALE;         // Loadcell Measurement scale @5.1 volt   // 3.19, 105.35108
      float TORQUE_SCALE;         // Loadcell Measurement scale @5.1 volt    // 3.3*2, 218.3545
      uint16_t TARE_TIME;         // Tare time duration in [ms]
      bool TARE_FLAG;             // Flag for enable/disable zero loadcell offset at initialization. 
      float GRAVITY;              // Gravity of the earth. [Approximately in tehran]
      int8_t THRUST_DOUT_PIN;     // HX711 dout pin for thrust loadcell. (-1: means not defined)
      int8_t THRUST_SCK_PIN;      // HX711 sck pin for thrust loadcell. (-1: means not defined)
      int8_t TORQUE_DOUT_PIN;     // HX711 dout pin for torque loadcell. (-1: means not defined)
      int8_t TORQUE_SCK_PIN;      // HX711 sck pin for tirque loadcell. (-1: means not defined)
    }parameters;

    // Value structure
    struct ValueStruct
    {
      float thrust;               // Thrust calculated value. [gr].
      float torqueForce;          // Force on Torque loadcell calculated value. [gr].
      float torque;               // Torque calculated value. [N.m].
    }value;

    HX711_ADC* thrustLoadcell;    // HX711 Object for loadcell_1
    HX711_ADC* torqueLoadcell;    // HX711 Object for loadcell_2

    /**
     * Constructor. Init parameters and variables.
     */
    ThrustTorqueHX711();

    /**
     * Destructor.
     */
    ~ThrustTorqueHX711();

    /**
     * Set thrust loadcell hx711 gpio pins.
     * @return true if successed.
     */
    bool setThrustHX711Pins(int8_t dout_pin, int8_t sck_pin);

    /**
     * Set torque loadcell hx711 gpio pins.
     * @return true if successed.
     */
    bool setTorqueHX711Pins(int8_t dout_pin, int8_t sck_pin);

    /**
     * Init object. Check parameters validation. create and begin HX711 objects.
     * @return true if successed.
     */
    bool init(void);

    /**
     * Update thrust and torque values. read loadcell values.
     */
    void update(void);

    /**
     * Calibrate and zero ofset of thrust and torque values.
     */
    void calibrate(void);

  private:

    bool _thrustDefinedFlag;        // Flag for thrust loadcell create and begin successfully.
    bool _torqueDefinedFlag;        // Flag for torque loadcell create and begin successfully.

    /**
     * Check parameters validation.
     * @return true if successed.
     */
    bool _checkParameters(void);

};


#endif
