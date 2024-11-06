#ifndef THRUST_TORQUE_HX711_H
#define THRUST_TORQUE_HX711_H

// ######################################################################
// Include libraries:

#include <HX711_ADC.h>                    // For the HX711 24-bit ADC for weight scales. https://github.com/olkal/HX711_ADC

// #######################################################################
// ThrustTorqueHX711 class:

/**
  @class ThrustTorqueHX711
  @brief ThrustTorqueHX711 class for thrust torque measurements operations.
*/
class ThrustTorqueHX711
{
  public:

    /// @brief Last error accured for object.
    String errorMessage;

    /**
      @struct ParametersStructure
      @brief Parameters structure
    */
    struct ParametersStructure
    {
      /**
        @brief // The distance between the load cell point force and the center of the motor mount. [m].  
      */
      float TORQUE_ARM;   

      /**
        @brief The number of samples from the load cell for the moving average filter.
      */
      uint8_t SAMPLE_USE;        

      /**
        @brief The load cell measurement scale for thrust measurement.
        @warning If the excitation of the load cell changes or is noisy, it affects the load cell scale measurements.
      */ 
      float THRUST_SCALE;        

      /**
        @brief The load cell measurement scale for torque measurement.
        @warning If the excitation of the load cell changes or is noisy, it affects the load cell scale measurements.
      */
      float TORQUE_SCALE;  

      /**
        @brief The tare time duration in. [ms]
      */
      uint16_t TARE_TIME;        

      /**
        @brief The flag for enabling/disabling zero load cell offset at initialization.
      */
      bool TARE_FLAG;         

      /**
        @brief The gravity of the earth at current locatoin. [m/s^2]
      */
      float GRAVITY;             

      /**
        @brief The HX711 dout pin for thrust loadcell. (-1: means not defined)
      */
      int8_t THRUST_DOUT_PIN;     

      /**
        @brief The HX711 sck pin for thrust loadcell. (-1: means not defined)
      */
      int8_t THRUST_SCK_PIN;      

      /**
        @brief The HX711 dout pin for torque loadcell. (-1: means not defined)
      */
      int8_t TORQUE_DOUT_PIN;     

      /**
        @brief The HX711 sck pin for torque loadcell. (-1: means not defined)
      */
      int8_t TORQUE_SCK_PIN;      
    }parameters;

    /**
      @struct ValuesStructure
      @brief Value structure for variables.
    */ 
    struct ValuesStructure
    {
      /**
        @brief The calculated value of thrust. [gr].
      */
      float thrust;              

      /**
        @brief The calculated value of force on the torque load cell. [gr].
      */
      float torqueForce;          

      /**
        @brief The calculated value of torque. [N.m].
      */
      float torque;          
    }value;

    /**
     * @brief The default constructor. Init parameters and variables.
     */
    ThrustTorqueHX711();

    /**
     * @brief Set the thrust loadcell hx711 GPIO pins.
     * @return true if successed.
     */
    bool setThrustHX711Pins(int8_t dout_pin, int8_t sck_pin);

    /**
     * @brief Set the torque loadcell hx711 GPIO pins.
     * @return true if successed.
     */
    bool setTorqueHX711Pins(int8_t dout_pin, int8_t sck_pin);

    /**
     * @brief Init object. Check parameters validation.
     * @return true if successed.
     */
    bool init(void);

    /**
     * @brief Read the loadcell values then update thrust and torque values. 
     */
    void update(void);

    /**
     * @brief Calibrate and zero the offset values for thrust and torque measurements.
     */
    void calibrate(void);

  private:

    /**
      @brief The flag for successfully creating and initializing the thrust load cell.
    */
    bool _thrustDefinedFlag;        

    /**
      @brief The flag for successfully creating and initializing the torque load cell.
    */
    bool _torqueDefinedFlag;       

    /**
      @brief The HX711 Object for thrust loadcell
    */
    HX711_ADC* _thrustLoadcell;    

    /**
      @brief The HX711 Object for torque loadcell
    */
    HX711_ADC* _torqueLoadcell; 

    /**
     * @brief Check parameters validation.
     * @return true if successed.
     */
    bool _checkParameters(void);

};


#endif
