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

  
  //reco photons (Need to add this part)

  
  //reco higgs (need to add this part)
  


  
  
  //data variables to be filled in the data loop
  float h_px, h_py, h_pz, h_e,
    ph1_px, ph1_py, ph1_pz,
    ph2_px, ph2_py, ph2_pz,
    ph1_px_reco, ph1_py_reco, ph1_pz_reco,
    ph2_px_reco, ph2_py_reco, ph2_pz_reco;

  ///read the file
  ifstream file;
  file.open("higgs_signal.dat");
  if (!file.is_open()){
    std::cout << "Unable to open file"<<std::endl;
    return;
  }
  std::string line;
  int counter=0;//use for counting the number of lines
  while (std::getline(file,line)){
    std::stringstream iss(line);
    iss>>h_px>>h_py>>h_pz>>h_e
       >>ph1_px>>ph1_py>>ph1_pz
       >>ph2_px>>ph2_py>>ph2_pz
       >>ph1_px_reco>>ph1_py_reco>>ph1_pz_reco
       >>ph2_px_reco>>ph2_py_reco>>ph2_pz_reco;
    
    //cout<<h_e<<" "<<h_p<<" "<<h_t<<" "<<h_f<<endl;
    
    //Constructed the 4-vectors
    TLorentzVector H_P4;
    H_P4.SetPx(h_px);
    H_P4.SetPy(h_py);
    H_P4.SetPz(h_pz);
    H_P4.SetE(h_e);

    TLorentzVector Ph1_P4;
    Ph1_P4.SetPx(ph1_px); 
    Ph1_P4.SetPy(ph1_py); 
    Ph1_P4.SetPz(ph1_pz);
    Ph1_P4.SetE(sqrt(ph1_px*ph1_px + ph1_py*ph1_py + ph1_pz*ph1_pz)); 

    TLorentzVector Ph2_P4;
    Ph2_P4.SetPx(ph2_px); 
    Ph2_P4.SetPy(ph2_py); 
    Ph2_P4.SetPz(ph2_pz);
    Ph2_P4.SetE(sqrt(ph2_px*ph2_px + ph2_py*ph2_py + ph2_pz*ph2_pz)); 

    
    //fill histograms with generated (true) quantities
    HHiggs_eta.Fill(H_P4.Eta());
    HHiggs_pt.Fill(H_P4.Pt()); 
    HPhoton1_eta.Fill(Ph1_P4.Eta());
    HPhoton1_pt.Fill(Ph1_P4.Pt());
    HPhoton2_eta.Fill(Ph2_P4.Eta());
    HPhoton2_pt.Fill(Ph2_P4.Pt());

    ///now you need to do the Higgs reconstruction
    //construct the photons reco 4-momentum and then the Higgs
    //then fill the graphs
    
    
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
  File.Write();


  // here can also use a TCanvas to create images for each graph and publish

  
  
}
