#include "generate_signal.h"


TH1F HNPho("HNPho","",3,-0.5,2.5);

TLorentzVector generate_higgs();
void decay_higgs(TLorentzVector & Higgs_p4, TLorentzVector & Photon1_p4, TLorentzVector & Photon2_p4);
bool detector_efficiency(float ph1_eta, float ph2_eta);
void detector_resolution(TLorentzVector & Photon1_p4, TLorentzVector & Photon2_p4, TLorentzVector & Photon1_p4_reco, TLorentzVector & Photon2_p4_reco);


void generate_signal_TTree(int N=100){

  create_tree("signal");

  //event loop
  for(int e=0;e<N;e++){
    if(e%100==0)cout<<"event "<<e<<endl;

    
    //////////////////////////////////
    /// Theory model
    /////////////////////////////////
    
    ///Production
    TLorentzVector Higgs_p4 = generate_higgs();
    
    ///Decay 
    TLorentzVector Photon1_p4;
    TLorentzVector Photon2_p4;
    decay_higgs(Higgs_p4, Photon1_p4, Photon2_p4);

    
    //////////////////////////
    /// Detector acceptance and efficiency
    //////////////////////////
    bool pass = detector_efficiency(Photon1_p4.Eta(), Photon2_p4.Eta());

    ///Detector Resolution
    TLorentzVector Photon1_p4_reco;
    TLorentzVector Photon2_p4_reco;
    if(pass)  ///in case photons did not pass detection set energy to 0, all events will be saved but reconstruced objects will be 0
      detector_resolution(Photon1_p4, Photon2_p4, Photon1_p4_reco, Photon2_p4_reco);
    
    
    //////////////////////////////
    /// Data acquisition
    ////////////////////////////

    ///Save to tree
    h_gen_px=Higgs_p4.Px();
    h_gen_py=Higgs_p4.Py();
    h_gen_pz=Higgs_p4.Pz();
    h_gen_e=Higgs_p4.E();
    h_gen_m=Higgs_p4.Mag();

    if(Photon1_p4.Pt()>Photon2_p4.Pt()){
      ph1_gen_px=Photon1_p4.Px();
      ph1_gen_py=Photon1_p4.Py();
      ph1_gen_pz=Photon1_p4.Pz();
      ph2_gen_px=Photon2_p4.Px();
      ph2_gen_py=Photon2_p4.Py();
      ph2_gen_pz=Photon2_p4.Pz();
      ph1_reco_px=Photon1_p4_reco.Px();
      ph1_reco_py=Photon1_p4_reco.Py();
      ph1_reco_pz=Photon1_p4_reco.Pz();
      ph2_reco_px=Photon2_p4_reco.Px();
      ph2_reco_py=Photon2_p4_reco.Py();
      ph2_reco_pz=Photon2_p4_reco.Pz();
    }else{
      ph1_gen_px=Photon2_p4.Px();
      ph1_gen_py=Photon2_p4.Py();
      ph1_gen_pz=Photon2_p4.Pz();
      ph2_gen_px=Photon1_p4.Px();
      ph2_gen_py=Photon1_p4.Py();
      ph2_gen_pz=Photon1_p4.Pz();
      ph1_reco_px=Photon2_p4_reco.Px();
      ph1_reco_py=Photon2_p4_reco.Py();
      ph1_reco_pz=Photon2_p4_reco.Pz();
      ph2_reco_px=Photon1_p4_reco.Px();
      ph2_reco_py=Photon1_p4_reco.Py();
      ph2_reco_pz=Photon1_p4_reco.Pz();
    }

    tree->Fill();
  }
  
  TFile OFile("generation_signal.root","recreate");
  tree->Write();  
  OFile.ls();
  OFile.Close();
  delete tree;

  gStyle->SetOptStat(0);
  TCanvas C;
  C.Clear();
  HNPho.GetXaxis()->SetTitle("# of photons in detector acceptance");
  HNPho.SetMarkerStyle(8);
  HNPho.SetMarkerSize(1);
  HNPho.Draw("histtext");
  C.Print("generation_signal_NPho.png");
  cout<<HNPho.GetBinContent(1)<<" "<<HNPho.GetBinContent(2)<<" "<<HNPho.GetBinContent(3)<<" "<<endl;
  
}



//////////////////////////////////////////////////////////////////////////
//////// auxiliary functions
/////////////////////////////////////////////////////////////////////////
TLorentzVector generate_higgs(){
    float theta = FHiggs_theta.GetRandom();
    float phi = FHiggs_phi.GetRandom();
    float p = FHiggs_p.GetRandom();
    TLorentzVector Higgs_p4;
    Higgs_p4.SetPx(p*sin(theta)*cos(phi));
    Higgs_p4.SetPy(p*sin(theta)*sin(phi));
    Higgs_p4.SetPz(p*cos(theta));
    Higgs_p4.SetE(sqrt(H_mass*H_mass + p*p));

    return Higgs_p4;
}


void decay_higgs(TLorentzVector & Higgs_p4, TLorentzVector & Photon1_p4, TLorentzVector & Photon2_p4){

  //step 1: in Higgs rest frame, photons get half the Higgs mass and random angles in theta
  float ph_theta=FPhoton_theta.GetRandom();
  float ph_phi=FPhoton_phi.GetRandom();
  Photon1_p4.SetPx((Higgs_p4.Mag()/2)*sin(ph_theta)*cos(ph_phi));
  Photon1_p4.SetPy((Higgs_p4.Mag()/2)*sin(ph_theta)*sin(ph_phi));
  Photon1_p4.SetPz((Higgs_p4.Mag()/2)*cos(ph_theta));
  Photon1_p4.SetE(Higgs_p4.Mag()/2);    
  Photon2_p4.SetPx(-Photon1_p4.Px());
  Photon2_p4.SetPy(-Photon1_p4.Py());
  Photon2_p4.SetPz(-Photon1_p4.Pz());
  Photon2_p4.SetE(Photon1_p4.E());
  
  //step 2: boost along Higgs generated momentum to get photons in lab frame
  Photon1_p4.Boost(Higgs_p4.BoostVector());
  Photon2_p4.Boost(Higgs_p4.BoostVector());

}


bool detector_efficiency(float ph1_eta, float ph2_eta){
   bool pass=1;

   int npass=0;
   //// detector acceptance, 
   if(!det_accept(ph1_eta)) pass=0;
   if(pass)npass++;
   
   if(!det_accept(ph2_eta)) pass=0;
   if(pass) npass++;

   HNPho.Fill(npass);//fill number detected photons
   
   //// detector efficiency
   //step 1: detection efficiency, not all photons will be detected by the sensor and electronics, apply 95% sensor efficiency
   if(FDetector_eff.GetRandom()>0.95) pass=0; //first photon
   if(FDetector_eff.GetRandom()>0.95) pass=0; //second photon
   
   return pass;
}


void detector_resolution(TLorentzVector & Photon1_p4, TLorentzVector & Photon2_p4, TLorentzVector & Photon1_p4_reco, TLorentzVector & Photon2_p4_reco){

    float ph1_e_res = FDetector_e_res.GetRandom();
    float ph2_e_res = FDetector_e_res.GetRandom();    
    float ph1_theta_res = FDetector_angle_res.GetRandom();
    float ph2_theta_res = FDetector_angle_res.GetRandom();
    float ph1_phi_res = FDetector_angle_res.GetRandom();
    float ph2_phi_res = FDetector_angle_res.GetRandom();

    Photon1_p4_reco.SetPx((Photon1_p4.E()*ph1_e_res) * sin(Photon1_p4.Theta() + ph1_theta_res) * cos(Photon1_p4.Phi() + ph1_phi_res));
    Photon1_p4_reco.SetPy((Photon1_p4.E()*ph1_e_res) * sin(Photon1_p4.Theta() + ph1_theta_res) * sin(Photon1_p4.Phi() + ph1_phi_res));
    Photon1_p4_reco.SetPz((Photon1_p4.E()*ph1_e_res) * cos(Photon1_p4.Theta() + ph1_theta_res));
    Photon1_p4_reco.SetE(Photon1_p4.E()*ph1_e_res);    

    Photon2_p4_reco.SetPx((Photon2_p4.E()*ph2_e_res) * sin(Photon2_p4.Theta() + ph2_theta_res) * cos(Photon2_p4.Phi() + ph2_phi_res));
    Photon2_p4_reco.SetPy((Photon2_p4.E()*ph2_e_res) * sin(Photon2_p4.Theta() + ph2_theta_res) * sin(Photon2_p4.Phi() + ph2_phi_res));
    Photon2_p4_reco.SetPz((Photon2_p4.E()*ph2_e_res) * cos(Photon2_p4.Theta() + ph2_theta_res));
    Photon2_p4_reco.SetE(Photon2_p4.E()*ph2_e_res);    
}


