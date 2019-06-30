#include <iostream>
#include <vector>

#include "Event.h"
using namespace std;

Event::Event(int centrality, int Npart, int Ncoll, int Nparticle, std::vector<float> pt, std::vector<float> eta, std::vector<float> phi, std::vector<int> charge, std::vector<int> particleID) {
      _pt.clear();
      _eta.clear();
      _phi.clear();
      _Charge.clear();
      _PID.clear();

      _pt = pt;
      _eta = eta;
      _phi = phi;
      _Charge = charge;
      _PID = particleID;

      _Centrality = centrality;
      _Nparticipant = Npart;
      _Ncollision = Ncoll;
      _Nparticle = Nparticle;
}

std::vector<float> Event::pT() {
      return (_pt);
}

std::vector<float> Event::eta() {
      return (_eta);
}

std::vector<float> Event::phi() {
      return (_phi);
}

std::vector<int> Event::Charge() {
      return (_Charge);
}

std::vector<int> Event::PID() {
      return (_PID);
}

int Event::Centrality() {
      return (_Centrality);
}

int Event::Nparticipant() {
      return (_Nparticipant);
}

int Event::Ncollision() {
      return (_Ncollision);
}

int Event::Nparticle() {
      return (_Nparticle);
}
