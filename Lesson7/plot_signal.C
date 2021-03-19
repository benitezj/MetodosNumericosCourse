#include "generate_signal.C"

void plot_signal(){

  //generated higgs
  TH1F HHiggs_eta("HHiggs_eta","",100,-10,10);
  TH1F HHiggs_pt("HHiggs_pt","",100,0,1000);

  //generated photons
  TH1F HPhoton1_eta("HPhoton1_eta","",100,-10,10);
  TH1F HPhoton1_pt("HPhoton1_pt","",100,0,1000);
  TH1F HPhoton2_eta("HPhoton2_eta","",100,-10,10);
  TH1F HPhoton2_pt("HPhoton2_pt","",100,0,1000);

  //reco photons
  TH1F HPhoton1_eta_reco("HPhoton1_eta_reco","",100,-10,10);
  TH1F HPhoton1_pt_reco("HPhoton1_pt_reco","",100,0,1000);
  TH1F HPhoton2_eta_reco("HPhoton2_eta_reco","",100,-10,10);
  TH1F HPhoton2_pt_reco("HPhoton2_pt_reco","",100,0,1000);

  // reco higgs (need to add this part)
  



  
  //data file
  ifstream file;
  file.open("higgs_signal.dat");
  if (!file.is_open()){
    std::cout << "Unable to open file"<<std::endl;
    return;
  }
  
  //event loop
  std::string line;
  float h_pt, h_eta, ph1_pt, ph1_eta, ph2_pt, ph2_eta, ph1_pt_reco, ph1_eta_reco, ph2_pt_reco, ph2_eta_reco;
  int counter=0;//use for counting the number of lines
  while (std::getline(file,line)){
    std::stringstream iss(line);
    iss>>h_pt>>h_eta
       >>ph1_pt>>ph1_eta
       >>ph2_pt>>ph2_eta
       >>ph1_pt_reco>>ph1_eta_reco
       >>ph2_pt_reco>>ph2_eta_reco;
   
    HHiggs_eta.Fill(h_eta);
    HHiggs_pt.Fill(h_pt);

    HPhoton1_eta.Fill(ph1_eta);
    HPhoton1_pt.Fill(ph1_pt);
    HPhoton2_eta.Fill(ph2_eta);
    HPhoton2_pt.Fill(ph2_pt);

    HPhoton1_eta_reco.Fill(ph1_eta_reco);
    HPhoton1_pt_reco.Fill(ph1_pt_reco);
    HPhoton2_eta_reco.Fill(ph2_eta_reco);
    HPhoton2_pt_reco.Fill(ph2_pt_reco);
    
    
  }
  file.close();


  ///store plots in a root file
  TFile File("signal.root","recreate");
  HHiggs_eta.Write();
  HHiggs_pt.Write();

  HPhoton1_eta.Write();
  HPhoton1_pt.Write();
  HPhoton2_eta.Write();
  HPhoton2_pt.Write();
  
  HPhoton1_eta_reco.Write();
  HPhoton1_pt_reco.Write();
  HPhoton2_eta_reco.Write();
  HPhoton2_pt_reco.Write();
  File.Write();


  // here can also use a TCanvas to create images for each graph and publish

  
  
}
