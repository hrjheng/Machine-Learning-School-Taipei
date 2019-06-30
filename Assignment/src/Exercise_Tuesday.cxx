#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

#include "Event.h"
#include "Minitree.h"

#include <TH1F.h>
#include <TH2F.h>
#include <TFile.h>
#include <TTree.h>
#include <TMath.h>
#include <TString.h>
#include <TVector2.h>
#include <TCanvas.h>
#include <TStyle.h>
#include <TProfile.h>
#include <TF1.h>
#include <TRandom3.h>

using namespace std;

int main(int argc, char *argv[]) {

      TH2F *hM_etaphi = new TH2F("hM_etaphi","hM_etaphi",100,-5,5,100,-TMath::Pi(),TMath::Pi());
      float sumE_jetregion = 0.; // the assumed jet region
      float sumE_region1 = 0.; // |eta| < 0.2, excluding jet region
      float sumE_region2 = 0.; // 3 < |eta| < 5

      float sumE_bkgregion = 0.;
      float sumE_jetregion_random = 0.;

      std::vector<float> v_sumE_jetregion; v_sumE_jetregion.clear();
      std::vector<float> v_sumE_region1; v_sumE_region1.clear();
      std::vector<float> v_sumE_region2; v_sumE_region2.clear();

      std::vector<float> v_sumE_jetregion_random; v_sumE_jetregion_random.clear();
      std::vector<float> v_sumE_bkgregion; v_sumE_bkgregion.clear();
      std::vector<float> v_jetregion_eta; v_jetregion_eta.clear();
      std::vector<float> v_jetregion_phi; v_jetregion_phi.clear();

      TH2F *hM_pTcorr_region1 = new TH2F("hM_pTcorr_region1","hM_pTcorr_region1",100,0,1200,50,0,100);
      TH2F *hM_pTcorr_region2 = new TH2F("hM_pTcorr_region2","hM_pTcorr_region2",140,0,7000,50,0,100);

      TRandom3 *random = new TRandom3(0);

      TFile *file = new TFile("./data/MinBias_Hydjet_Drum5F_2018_5p02TeV_minPt0p1_cent_merged.root","READ");
      file->cd();
      TTree *tree = (TTree*) file->Get("EventTree");
      int centrality;
      int Nparticipant;
      int Ncoll;
      int Nparticle;
      std::vector<float> *v_pt = 0;
      std::vector<float> *v_eta = 0;
      std::vector<float> *v_phi = 0;
      std::vector<int> *v_Q = 0;
      std::vector<int> *v_PID = 0;
      tree->SetBranchAddress("centrality",&centrality);
      tree->SetBranchAddress("Nparticipant",&Nparticipant);
      tree->SetBranchAddress("Ncoll",&Ncoll);
      tree->SetBranchAddress("Nparticle",&Nparticle);
      tree->SetBranchAddress("pT",&v_pt);
      tree->SetBranchAddress("eta",&v_eta);
      tree->SetBranchAddress("phi",&v_phi);
      tree->SetBranchAddress("charge",&v_Q);
      tree->SetBranchAddress("PID",&v_PID);

      int ev = 0;
      while (ev < tree->GetEntriesFast())
      {
            sumE_jetregion = 0.; // the assumed jet region
            sumE_region1 = 0.; // |eta| < 0.2, excluding jet region
            sumE_region2 = 0.; // 3 < |eta| < 5

            float rand_eta = 0.;
            float rand_phi = 0.;

            tree->GetEntry(ev);

            for(int iobj=0;iobj<Nparticle;iobj++)
            {
                  int binx = hM_etaphi->GetXaxis()->FindBin(v_eta->at(iobj));
                  int biny = hM_etaphi->GetYaxis()->FindBin(v_phi->at(iobj));
                  int binnum = hM_etaphi->GetBin(binx,biny,0);
                  // hM_etaphi.SetBinContent(binnum,tree.pT[iobj])
                  // hM_etaphi.Fill(tree.eta[iobj],tree.phi[iobj],tree.pT[iobj])
                  hM_etaphi->Fill(v_eta->at(iobj),v_phi->at(iobj));

                  if(fabs(v_eta->at(iobj))<0.2 && fabs(v_phi->at(iobj))<0.2)
                  {
                        sumE_jetregion = sumE_jetregion + v_pt->at(iobj);
                  }

                  if(fabs(v_eta->at(iobj))<0.2 && (v_phi->at(iobj)>0.2 || v_phi->at(iobj)<-0.2))
                  {
                        sumE_region1 = sumE_region1 + v_pt->at(iobj);
                  }

                  if(fabs(v_eta->at(iobj))>3. && fabs(v_eta->at(iobj))<5.)
                  {
                        sumE_region2 = sumE_region2 + v_pt->at(iobj);
                  }
            }

            for(int iran=0;iran<20;iran++)
            {
                  rand_eta = -2. + 4.*random->Rndm();
                  rand_phi = -TMath::Pi() + (2.*TMath::Pi())*random->Rndm();
                  // cout << rand_eta << " " << rand_phi << endl;

                  sumE_jetregion_random = 0.;
                  sumE_bkgregion = 0.;
                  for(int iobj=0;iobj<Nparticle;iobj++)
                  {
                        if(fabs(v_eta->at(iobj)-rand_eta)<0.2 && fabs(v_phi->at(iobj)-rand_phi)<0.2)
                        {
                              sumE_jetregion_random = sumE_jetregion_random + v_pt->at(iobj);
                        }

                        if(fabs(v_eta->at(iobj))>3. && fabs(v_eta->at(iobj))<5.)
                        {
                              sumE_bkgregion = sumE_bkgregion + v_pt->at(iobj);
                        }
                  }

                  v_sumE_jetregion_random.push_back(sumE_jetregion_random);
                  v_sumE_bkgregion.push_back(sumE_bkgregion);
                  v_jetregion_eta.push_back(rand_eta);
                  v_jetregion_phi.push_back(rand_phi);
            }

            v_sumE_jetregion.push_back(sumE_jetregion);
            v_sumE_region1.push_back(sumE_region1);
            v_sumE_region2.push_back(sumE_region2);

            hM_pTcorr_region1->Fill(sumE_region1,sumE_jetregion);
            hM_pTcorr_region2->Fill(sumE_region2,sumE_jetregion);

            v_pt->clear();
            v_eta->clear();
            v_phi->clear();
            v_Q->clear();
            v_PID->clear();
            ev++;
      }

      file->Close();

      float _sumE_jetregion, _sumE_bkgregion, _jetregion_eta, _jetregion_phi;
      TFile *fout  = new TFile("../TMVA/files/Test_Sample_MinBias_minPt0p1_cent_merged.root","RECREATE");
      TTree *outtree = new TTree("EventTree","EventTree");
      outtree->Branch("sumE_jetregion",&_sumE_jetregion);
      outtree->Branch("sumE_bkgregion", &_sumE_bkgregion);
      outtree->Branch("jetregion_eta", &_jetregion_eta);
      outtree->Branch("jetregion_phi", &_jetregion_phi);
      for(int i=0;i<v_sumE_jetregion_random.size();i++)
      {
            _sumE_jetregion = v_sumE_jetregion_random[i];
            _sumE_bkgregion = v_sumE_bkgregion[i];
            _jetregion_eta = v_jetregion_eta[i];
            _jetregion_phi = v_jetregion_phi[i];
            outtree->Fill();
      }
      fout->cd();
      outtree->Write("", TObject::kOverwrite);
      fout->Close();

      TProfile *profile_region1 = hM_pTcorr_region1->ProfileX("profile_region1");
      TProfile *profile_region2 = hM_pTcorr_region2->ProfileX("profile_region2");

      TF1 *func_region1 = new TF1("func_region1","pol2",0,1100);
      func_region1->FixParameter(0,0);
      func_region1->SetLineColor(2);
      func_region1->SetLineWidth(2);
      profile_region1->Fit(func_region1,"","",0,1100);

      TF1 *func_region2 = new TF1("func_region2","pol2",0,7000);
      func_region2->FixParameter(0,0);
      func_region2->SetLineColor(2);
      func_region2->SetLineWidth(2);
      profile_region2->Fit(func_region2,"","",0,7000);

      TH2F *hM_pTcorr_ratio_region1 = new TH2F("hM_pTcorr_ratio_region1","hM_pTcorr_ratio_region1",100,0,1200,50,0,5);
      TH1F *hM_ratio_1D_region1 = new TH1F("hM_ratio_1D_region1","hM_ratio_1D_region1",25,0,5);
      for(int i=0;i<v_sumE_region1.size();i++)
      {
            if(v_sumE_jetregion[i] == 0.) continue;

            hM_pTcorr_ratio_region1->Fill(v_sumE_region1[i],v_sumE_jetregion[i]/func_region1->Eval(v_sumE_region1[i]));
            hM_ratio_1D_region1->Fill(v_sumE_jetregion[i]/func_region1->Eval(v_sumE_region1[i]));
      }

      TH2F *hM_pTcorr_ratio_region2 = new TH2F("hM_pTcorr_ratio_region2","hM_pTcorr_ratio_region2",140,0,7000,50,0,5);
      TH1F *hM_ratio_1D_region2 = new TH1F("hM_ratio_1D_region2","hM_ratio_1D_region2",25,0,5);
      for(int i=0;i<v_sumE_region2.size();i++)
      {
            if(v_sumE_jetregion[i] == 0.) continue;

            hM_pTcorr_ratio_region2->Fill(v_sumE_region2[i],v_sumE_jetregion[i]/func_region2->Eval(v_sumE_region2[i]));
            hM_ratio_1D_region2->Fill(v_sumE_jetregion[i]/func_region2->Eval(v_sumE_region2[i]));
      }

      TFile *fout2 = new TFile("./plots/Exercise_cent_merged_histograms.root","RECREATE");
      fout2->cd();
      hM_etaphi->Write();
      hM_pTcorr_region1->Write();
      hM_pTcorr_region2->Write();
      profile_region1->Write();
      profile_region2->Write();
      func_region1->Write();
      func_region2->Write();
      hM_pTcorr_ratio_region1->Write();
      hM_ratio_1D_region1->Write();
      hM_pTcorr_ratio_region2->Write();
      hM_ratio_1D_region2->Write();
      fout2->Close();
}
