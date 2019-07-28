#include "arduinosensor.h"

#define _GOS_ARDUINO_SENSOR_TEXT_OK_ "Ok"
#define _GOS_ARDUINO_SENSOR_TEXT_BELOW_MINIMUM_ "Below Min"
#define _GOS_ARDUINO_SENSOR_TEXT_ABOVE_MAXIMUM_ "Above Max"

namespace gos {
namespace sensor {
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
namespace range {
uint8_t check(double& reading, const double& minimum, const double& maximum) {
  if (
    reading >= minimum &&
    reading <= maximum) {
    return GOS_SENSOR_STATUS_OK;
  }
  else if (reading < minimum) {
    reading = minimum;
    return GOS_SENSOR_STATUS_BELOW_MINIMUM;
  }
  else {
    reading = maximum;
    return GOS_SENSOR_STATUS_ABOVE_MAXIMUM;
  }
}
#ifdef GOS_SENSOR_GLOBAL
double Minimum;
double Maximum;
uint8_t check(double& reading) {
  return check(reading, Minimum, Maximum);
}
}
#endif
}

#ifdef GOS_SENSOR_CLASS
Sensor::Sensor(const double& minimum, const double& maximum) :
  Minimum(minimum),
  Maximum(maximum) {
}
uint8_t Sensor::check(double& reading) {
  return ::gos::sensor::range::check(reading, Minimum, Maximum);
}
#endif
}
