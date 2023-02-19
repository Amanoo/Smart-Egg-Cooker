#include <functional>
#include <string>
#include <vector>

using ServiceFunction = std::function<void()>;


class Component {};
class CustomAPIDevice {
public:
  virtual void setup();
  virtual void loop();
};
class Sensor {
public:
  void publish_state(int i){};
};
class TextSensor {
public:
  void publish_state(String i){};
};

//void register_service(ServiceFunction function, String i, std::vector<std::string> options){};