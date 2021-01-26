#ifndef LOWPASSFILTER_HPP
#define LOWPASSFILTER_HPP
#include <cmath>

class LowPassFilter{
public:
  //constructors
  LowPassFilter();
  LowPassFilter(float iCutOffFrequency, float iDeltaTime);
  //functions
  float update(float input);
  float update(float input, float deltaTime, float cutoffFrequency);
  //get and configure funtions
  float getOutput() const{return output;}
  void reconfigureFilter(float deltaTime, float cutoffFrequency);
private:
  float output;
  float ePow;
};

#endif // LOWPASSFILTER_HPP
