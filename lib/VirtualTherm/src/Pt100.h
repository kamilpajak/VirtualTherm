// Pt100.h
#ifndef PT100_H
#define PT100_H

#include "RTD.h"

class Pt100 : public RTD {
public:
  Pt100() : RTD(100.0) {} // Set R0 specific for Pt100
};

#endif // PT100_H