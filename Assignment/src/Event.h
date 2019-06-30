#include <iostream>
#include <vector>

using namespace std;

class Event {
public:
      Event(int, int, int, int, std::vector<float>, std::vector<float>, std::vector<float>, std::vector<int>, std::vector<int>);

      int Centrality();
      int Nparticipant();
      int Ncollision();
      int Nparticle();
      std::vector<float> pT();
      std::vector<float> eta();
      std::vector<float> phi();
      std::vector<int> Charge();
      std::vector<int> PID();


private:
      int _Centrality;
      int _Nparticipant;
      int _Ncollision;
      int _Nparticle;
      std::vector<float> _pt;
      std::vector<float> _eta;
      std::vector<float> _phi;
      std::vector<int> _Charge;
      std::vector<int> _PID;

};
