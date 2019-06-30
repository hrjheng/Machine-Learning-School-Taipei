#include <iostream>
#include <vector>

#include <TTree.h>
#include <TFile.h>
#include <TObject.h>
#include "Event.h"
#include "Minitree.h"
using namespace std;

Minitree::Minitree() {
      _tree = new TTree("EventTree","EventTree");
      _pt.clear();
      _eta.clear();
      _phi.clear();
      _charge.clear();
      _PID.clear();
      _tree->Branch("ev",&_ev);
      _tree->Branch("centrality", &_centrality);
      _tree->Branch("Nparticipant", &_Nparticipant);
      _tree->Branch("Ncoll", &_Ncoll);
      _tree->Branch("Nparticle", &_Nparticle);
      _tree->Branch("pT",&_pt);
      _tree->Branch("eta",&_eta);
      _tree->Branch("phi",&_phi);
      _tree->Branch("charge",&_charge);
      _tree->Branch("PID",&_PID);
}

void Minitree::FillEvent(Event *evt, int ev) {
      _ev = ev;
      _centrality = evt->Centrality();
      _Nparticipant = evt->Nparticipant();
      _Ncoll = evt->Ncollision();
      _Nparticle = evt->Nparticle();
      _pt = evt->pT();
      _eta = evt->eta();
      _phi = evt->phi();
      _charge = evt->Charge();
      _PID = evt->PID();
      _tree->Fill();
}

void Minitree::SaveToFile(TString filename) {
      TFile *outfile = TFile::Open(filename.Data(), "RECREATE");
      outfile->cd();
      _tree->Write("", TObject::kOverwrite);
      outfile->Close();
}
