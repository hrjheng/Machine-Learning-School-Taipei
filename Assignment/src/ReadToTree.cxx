#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

#include "Event.h"
#include "Minitree.h"

#include <TH1F.h>

using namespace std;


std::vector<float> getFloats(const std::string& s) {
    std::istringstream iss(s);
    std::string word;
    std::vector<float> result;

    size_t pos = 0;
    while (iss >> word) {
        try {
            float f = std::stof(word, &pos);
            if (pos == word.size()) {
                result.push_back(f);
            }
        }
        catch (std::invalid_argument const& ) {
            // no part of word is a float
            continue;
        }
    }

    return result;
}


int main(int argc, char *argv[]) {
      int ev = -1;
      Minitree *minitree = new Minitree();

      vector<float> v_pt; v_pt.clear();
      vector<float> v_eta; v_eta.clear();
      vector<float> v_phi; v_phi.clear();
      vector<int> v_charge; v_charge.clear();
      vector<int> v_PID; v_PID.clear();

      int Centrality;
      int Nparticipant;
      int Ncollision;
      int Nparticle;

      std::ifstream in("printEvents_MinBias_Hydjet_Drum5F_2018_5p02TeV_cent_0_10.txt");
      if(in.is_open()){
            std::string line;
            while (getline(in, line))
            {
                  std::vector<float> vtmp;
                  vtmp = getFloats(line);
                  if (vtmp.size() == 6)
                  {
                        if(ev>-1)
                        {
                              Event *evt = new Event(Centrality,Nparticipant,Ncollision,Nparticle,v_pt,v_eta,v_phi,v_charge,v_PID);
                              // if (v_pt.size()!=2) cout << ev << " " << v_pt.size() << endl;
                              minitree->FillEvent(evt,ev);
                        }

                        Centrality = vtmp[2];
                        Nparticipant = vtmp[3];
                        Ncollision = vtmp[4];
                        Nparticle = vtmp[5];
                        // cout << ev << " " << Centrality << " " << Nparticipant << " " << Ncollision << " " << Nparticle << endl;

                        v_pt.clear();
                        v_eta.clear();
                        v_phi.clear();
                        v_charge.clear();
                        v_PID.clear();

                        ev++;

                        continue;
                  }

                  std::vector<float> result;
                  result = getFloats(line);
                  v_eta.push_back(result[0]);
                  v_phi.push_back(result[1]);
                  v_pt.push_back(result[2]);
                  v_charge.push_back(result[3]);
                  v_PID.push_back(result[4]);
            }
            Event *evt = new Event(Centrality,Nparticipant,Ncollision,Nparticle,v_pt,v_eta,v_phi,v_charge,v_PID);
            // if (v_pt.size()!=2) cout << ev << " " << v_pt.size() << endl;
            minitree->FillEvent(evt,ev);
      }
      in.close();

      system("mkdir -p ./data");
      minitree->SaveToFile("./data/MinBias_Hydjet_Drum5F_2018_5p02TeV_minPt0p1_cent0to10.root");

      return 0;
}
