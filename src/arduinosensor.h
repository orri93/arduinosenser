#ifndef _GOS_ARDUINO_LIBRARY_MAX_SENSOR_H_
#define _GOS_ARDUINO_LIBRARY_MAX_SENSOR_H_

#include <Arduino.h>

#define GOS_SENSOR_STATUS_OK            0
#define GOS_SENSOR_STATUS_ERROR         1
#define GOS_SENSOR_STATUS_BELOW_MINIMUM 2
#define GOS_SENSOR_STATUS_ABOVE_MAXIMUM 3

namespace gos {
namespace sensor {
const char* error(const uint8_t& status);
namespace range {
uint8_t check(double& reading, const double& minimum, const double& maximum);
#ifdef GOS_SENSOR_GLOBAL
extern double Minimum;
extern double Maximum;
uint8_t check(double& reading);
extern double value;
#endif
}
}

#ifdef GOS_SENSOR_CLASS
class Sensor {
public:
  Sensor(const double& minimum, const double& maximum);
  uint8_t check(double& reading);

  double Minimum;
  double Maximum;
};
#endif
}

#endif /* _FDS_ARDUINO_LIBRARY_DEBUG_SERIAL_H_ */
