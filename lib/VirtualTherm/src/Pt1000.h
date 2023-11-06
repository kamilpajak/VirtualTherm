// Pt1000.h
#ifndef PT1000_H
#define PT1000_H

#include "RTD.h"

class Pt1000 : public RTD {
public:
  Pt1000() : RTD(1000.0) {} // Set R0 specific for Pt1000
};

#endif // PT1000_H