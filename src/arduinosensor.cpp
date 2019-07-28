#include <arduinosensor.h>

namespace gos {
namespace sensor {
const char* error(const uint8_t& status) {
  switch(status) {
  case GOS_SENSOR_STATUS_OK:
    return "Ok";
  case GOS_SENSOR_STATUS_BELOW_MINIMUM:
    return "Below Min";
  case GOS_SENSOR_STATUS_ABOVE_MAXIMUM:
    return "Above Min";
  default:
    return nullptr;
  }
}
namespace range {
int check(double& reading, const double& minimum, const double& maximum) {
  if(
    reading >= minimum &&
    reading <= maximum) {
      return GOS_SENSOR_STATUS_OK;
  } else if (reading < minimum) {
    reading = minimum;
    return GOS_SENSOR_STATUS_BELOW_MINIMUM;
  } else {
    reading = maximum;
    return GOS_SENSOR_STATUS_ABOVE_MAXIMUM;
  }
}
#ifdef GOS_SENSOR_GLOBAL
double Minimum;
double Maximum;
int check(double& reading);
  return check(reading, Minimum, Maximum);
}
}

#ifdef GOS_SENSOR_CLASS
Sensor::Sensor(const double& minimum, const double& maximum) :
  Minimum(minimum),
  Maximum(maximum) {
}
int Sensor::check(double& reading) {
  return ::gos::sensor::range::check(reading, Minimum, Maximum);
}
#endif
}
