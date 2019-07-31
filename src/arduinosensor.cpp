#include "arduinosensor.h"

#define _GOS_ARDUINO_SENSOR_TEXT_OK_ "Ok"
#define _GOS_ARDUINO_SENSOR_TEXT_BELOW_MINIMUM_ "Below Min"
#define _GOS_ARDUINO_SENSOR_TEXT_ABOVE_MAXIMUM_ "Above Max"

namespace gos {
namespace sensor {
static uint8_t last_status_;
const char* error(const uint8_t& status, uint8_t& length) {
  switch (status) {
  case GOS_SENSOR_STATUS_OK:
    length = sizeof(_GOS_ARDUINO_SENSOR_TEXT_OK_);
    return _GOS_ARDUINO_SENSOR_TEXT_OK_;
  case GOS_SENSOR_STATUS_BELOW_MINIMUM:
    length = sizeof(_GOS_ARDUINO_SENSOR_TEXT_BELOW_MINIMUM_);
    return _GOS_ARDUINO_SENSOR_TEXT_BELOW_MINIMUM_;
  case GOS_SENSOR_STATUS_ABOVE_MAXIMUM:
    length = sizeof(_GOS_ARDUINO_SENSOR_TEXT_ABOVE_MAXIMUM_);
    return _GOS_ARDUINO_SENSOR_TEXT_ABOVE_MAXIMUM_;
  default:
    return nullptr;
  }
}
const char* error(uint8_t& length) {
  return error(last_status_, length);
}
double value;
namespace range {
uint8_t check(double& reading, const double& minimum, const double& maximum) {
  if (
    reading >= minimum &&
    reading <= maximum) {
    return last_status_ = GOS_SENSOR_STATUS_OK;
  }
  else if (reading < minimum) {
    reading = minimum;
    return last_status_ = GOS_SENSOR_STATUS_BELOW_MINIMUM;
  }
  else {
    reading = maximum;
    return last_status_ = GOS_SENSOR_STATUS_ABOVE_MAXIMUM;
  }
}
#ifndef GOS_SENSOR_GLOBAL_DISMISS
double Minimum = GOS_SENSOR_DEFAULT_MINIMUM;
double Maximum = GOS_SENSOR_DEFAULT_MAXIMUM;
uint8_t check(double& reading) {
  return check(reading, Minimum, Maximum);
}
#endif
}
}

#ifndef GOS_SENSOR_CLASS_DISMISS
Sensor::Sensor(const double& minimum, const double& maximum) :
  Minimum(minimum),
  Maximum(maximum) {
}
uint8_t Sensor::check(double& reading) {
  return ::gos::sensor::range::check(reading, Minimum, Maximum);
}
#endif
}
