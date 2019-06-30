#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

void TextToTree()
{
      ifstream in;
      in.open("jet_data_NONLIN_FLAT_1_250000.txt");

      // float _sumE_jetregion, _sumE_bkgregion, _eta, _phi;
      float _charged_hadron_pT, _neutral_hadron_pT, _charged_plus_neutral_pT, _em_pT, _eta, _phi, _truth_pT;
      TFile *fout  = new TFile("Training_Sample_jet_NONLIN_FLAT_1.root","RECREATE");
      TTree *outtree = new TTree("EventTree","EventTree");
      outtree->Branch("charged_hadron_pT",&_charged_hadron_pT);
      outtree->Branch("neutral_hadron_pT", &_neutral_hadron_pT);
      outtree->Branch("charged_plus_neutral_pT",&_charged_plus_neutral_pT);
      outtree->Branch("em_pT", &_em_pT);
      outtree->Branch("eta", &_eta);
      outtree->Branch("phi", &_phi);
      outtree->Branch("truth_pT",&_truth_pT);

      Int_t nlines = 0;
      while (1)
      {
            in >> _charged_hadron_pT >> _neutral_hadron_pT >> _charged_plus_neutral_pT >> _em_pT >> _eta >> _phi >> _truth_pT;
            if (!in.good()) break;
            if (nlines < 5) printf("charged_hadron_pT=%3f, neutral_hadron_pT=%3f, charged_plus_neutral_pT=%3f, em_pT=%3f, eta=%3f, phi=%3f, truth_pT=%3f\n",_charged_hadron_pT,_neutral_hadron_pT,_charged_plus_neutral_pT,_em_pT,_eta,_phi,_truth_pT);
            outtree->Fill();
            nlines++;
      }

      fout->cd();
      outtree->Write("", TObject::kOverwrite);
      fout->Close();
}
