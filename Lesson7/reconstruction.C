#include "generate_signal.C"

void reconstruction(){

  //Gen photons
  TH1F HPhoton1_gen_eta("HPhoton1_gen_eta","",30,-6,6);
  HPhoton1_gen_eta.GetXaxis()->SetTitle(" Photon 1 #eta ");
  TH1F HPhoton1_gen_pt("HPhoton1_gen_pt","",30,0,600);
  HPhoton1_gen_pt.GetXaxis()->SetTitle(" Photon 1 p_{T} (GeV) ");

  // Gen Higgs
  TH1F HHiggs_gen_eta("HHiggs_gen_eta","",30,-6,6);
  HHiggs_gen_eta.GetXaxis()->SetTitle(" Higgs #eta ");
  TH1F HHiggs_gen_pt("HHiggs_gen_pt","",40,0,2000);
  HHiggs_gen_pt.GetXaxis()->SetTitle(" Higgs transverse momentum (GeV)");

  
  //reco photons 
  TH1F HPhoton1_reco_eta("HPhoton1_reco_eta","",30,-6,6);
  HPhoton1_reco_eta.GetXaxis()->SetTitle(" Photon 1 #eta ");
  TH1F HPhoton1_reco_pt("HPhoton1_reco_pt","",30,0,600);
  HPhoton1_reco_pt.GetXaxis()->SetTitle(" Photon 1 p_{T} (GeV) ");
  TH1F HPhoton2_reco_eta("HPhoton2_reco_eta","",30,-6,6);
  HPhoton2_reco_eta.GetXaxis()->SetTitle(" Photon 2 #eta ");
  TH1F HPhoton2_reco_pt("HPhoton2_reco_pt","",30,0,600);
  HPhoton2_reco_pt.GetXaxis()->SetTitle(" Photon 2 p_{T} (GeV) ");

  
  //reco higgs 
  TH1F HHiggs_reco_eta("HHiggs_reco_eta","",30,-6,6);
  HHiggs_reco_eta.GetXaxis()->SetTitle(" Higgs #eta ");
  TH1F HHiggs_reco_pt("HHiggs_reco_pt","",40,0,2000);
  HHiggs_reco_pt.GetXaxis()->SetTitle(" Higgs transverse momentum (GeV)");
  TH1F HHiggs_reco_m("HHiggs_reco_m","",200,0,200);
  HHiggs_reco_m.GetXaxis()->SetTitle(" Higgs mass (GeV) ");  

  
  //histograms needed for efficiency
  TH1F HPhoton1_gen_eff_eta("HPhoton1_gen_eff_eta","",30,-6,6);
  HPhoton1_gen_eff_eta.GetXaxis()->SetTitle(" Photon 1 #eta ");
  TH1F HPhoton1_gen_eff_pt("HPhoton1_gen_eff_pt","",30,0,600);
  HPhoton1_gen_eff_pt.GetXaxis()->SetTitle(" Photon 1 p_{T} (GeV) ");

  TH1F HHiggs_gen_eff_eta("HHiggs_gen_eff_eta","",30,-6,6); 
  HHiggs_gen_eff_eta.GetXaxis()->SetTitle(" Higgs #eta ");
  TH1F HHiggs_gen_eff_pt("HHiggs_gen_eff_pt","",40,0,2000);
  HHiggs_gen_eff_pt.GetXaxis()->SetTitle(" Higgs transverse momentum (GeV)");

  //histograms needed for resolution
  TH1F HPhoton1_res_eta("HPhoton1_res_eta","",50,-0.1,0.1);
  HPhoton1_res_eta.GetXaxis()->SetTitle(" Photon 1 #eta^{reco} - #eta^{gen} ");
  TH1F HPhoton1_res_pt("HPhoton1_res_pt","",50,-100,100);
  HPhoton1_res_pt.GetXaxis()->SetTitle(" Photon 1 p_{T}^{reco} - p_{T}^{gen} (GeV) ");


  TH1F HHiggs_res_eta("HHiggs_res_eta","",50,-0.1,0.1);
  HHiggs_res_eta.GetXaxis()->SetTitle(" Higgs #eta^{reco} - #eta^{gen} ");
  TH1F HHiggs_res_pt("HHiggs_res_pt","",50,-100,100);
  HHiggs_res_pt.GetXaxis()->SetTitle(" Higgs p_{T}^{reco} - p_{T}^{gen} (GeV) ");

  
  
  

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


    ///generated
    HPhoton1_gen_eta.Fill(Ph1_P4.Eta());
    HPhoton1_gen_pt.Fill(Ph1_P4.Pt());
    HHiggs_gen_eta.Fill(H_P4.Eta());
    HHiggs_gen_pt.Fill(H_P4.Pt());

    
    //now you need to do the Higgs reconstruction
    //construct the photons reco 4-momentum and then the Higgs
    //then fill the graphs
    
    TLorentzVector Ph1_reco_P4;
    Ph1_reco_P4.SetPx(ph1_px_reco); 
    Ph1_reco_P4.SetPy(ph1_py_reco); 
    Ph1_reco_P4.SetPz(ph1_pz_reco);
    Ph1_reco_P4.SetE(sqrt(ph1_px_reco*ph1_px_reco + ph1_py_reco*ph1_py_reco + ph1_pz_reco*ph1_pz_reco)); 

    TLorentzVector Ph2_reco_P4;
    Ph2_reco_P4.SetPx(ph2_px_reco); 
    Ph2_reco_P4.SetPy(ph2_py_reco); 
    Ph2_reco_P4.SetPz(ph2_pz_reco);
    Ph2_reco_P4.SetE(sqrt(ph2_px_reco*ph2_px_reco + ph2_py_reco*ph2_py_reco + ph2_pz_reco*ph2_pz_reco)); 


    //////////cut events with photons not detected
    if(Ph1_reco_P4.E() <= 0. || Ph2_reco_P4.E()<= 0. ) continue;

    ///reconstructed photons
    HPhoton1_reco_eta.Fill(Ph1_reco_P4.Eta());
    HPhoton1_reco_pt.Fill(Ph1_reco_P4.Pt());
    HPhoton2_reco_eta.Fill(Ph2_reco_P4.Eta());
    HPhoton2_reco_pt.Fill(Ph2_reco_P4.Pt());

    //constructed Higgs
    TLorentzVector H_reco_P4 = Ph1_reco_P4 + Ph2_reco_P4;
    HHiggs_reco_eta.Fill(H_reco_P4.Eta());
    HHiggs_reco_pt.Fill(H_reco_P4.Pt());
    HHiggs_reco_m.Fill(H_reco_P4.M());


    ///efficiency
    HPhoton1_gen_eff_eta.Fill(Ph1_P4.Eta());
    HPhoton1_gen_eff_pt.Fill(Ph1_P4.Pt());
    HHiggs_gen_eff_eta.Fill(H_P4.Eta());
    HHiggs_gen_eff_pt.Fill(H_P4.Pt());

    
    //resolution
    HPhoton1_res_eta.Fill(Ph1_reco_P4.Eta() - Ph1_P4.Eta());
    HPhoton1_res_pt.Fill(Ph1_reco_P4.Pt() - Ph1_P4.Pt());
    HHiggs_res_eta.Fill(H_reco_P4.Eta() - H_P4.Eta());
    HHiggs_res_pt.Fill(H_reco_P4.Pt() - H_P4.Pt());
    
    
    
  }
  file.close();


  //Calculate efficiencies
  TH1F*HPhoton1_gen_eff_eta_ratio=(TH1F*)HPhoton1_gen_eff_eta.Clone("HPhoton1_gen_eff_eta_ratio");
  HPhoton1_gen_eff_eta_ratio->Divide(&HPhoton1_gen_eta);
  HPhoton1_gen_eff_eta_ratio->SetMarkerStyle(8);

  TH1F*HPhoton1_gen_eff_pt_ratio=(TH1F*)HPhoton1_gen_eff_pt.Clone("HPhoton1_gen_eff_pt_ratio");
  HPhoton1_gen_eff_pt_ratio->Divide(&HPhoton1_gen_pt);
  HPhoton1_gen_eff_pt_ratio->SetMarkerStyle(8);
  
  TH1F*HHiggs_gen_eff_eta_ratio=(TH1F*)HHiggs_gen_eff_eta.Clone("HHiggs_gen_eff_eta_ratio");
  HHiggs_gen_eff_eta_ratio->Divide(&HHiggs_gen_eta);
  HHiggs_gen_eff_eta_ratio->SetMarkerStyle(8);
  
  TH1F*HHiggs_gen_eff_pt_ratio=(TH1F*)HHiggs_gen_eff_pt.Clone("HHiggs_gen_eff_pt_ratio");
  HHiggs_gen_eff_pt_ratio->Divide(&HHiggs_gen_pt);
  HHiggs_gen_eff_pt_ratio->SetMarkerStyle(8);

  ///store plots in a root file
  TFile File("reconstruction.root","recreate");

  //Generated
  HPhoton1_gen_eta.Write();
  HPhoton1_gen_pt.Write();
  HHiggs_gen_eta.Write();
  HHiggs_gen_pt.Write();

  ///reconstructed 
  HPhoton1_reco_eta.Write();
  HPhoton1_reco_pt.Write();
  HPhoton2_reco_eta.Write();
  HPhoton2_reco_pt.Write();
  HHiggs_reco_eta.Write();
  HHiggs_reco_pt.Write();
  HHiggs_reco_m.Write();


  //efficiency
  HPhoton1_gen_eff_eta.Write();
  HPhoton1_gen_eff_pt.Write();  
  HPhoton1_gen_eff_eta_ratio->Write();
  HPhoton1_gen_eff_pt_ratio->Write();
  HHiggs_gen_eff_eta.Write();
  HHiggs_gen_eff_pt.Write();
  HHiggs_gen_eff_eta_ratio->Write();
  HHiggs_gen_eff_pt_ratio->Write();

  //resolution
  HPhoton1_res_eta.Write();
  HPhoton1_res_pt.Write();
  HHiggs_res_eta.Write();
  HHiggs_res_pt.Write();

  
  File.Write();


  // here can also use a TCanvas to create images for each graph and publish

  
  
}
