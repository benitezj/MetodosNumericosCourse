#include "generate_signal_TTree.C"


//signal model (Higgs production)
TF1 FGluon_theta("FGluon_theta","1",0,TMath::Pi());
TF1 FGluon_phi("FGluon_phi","1",0,2*TMath::Pi());
TF1 FGluon_p("FGluon_p","x*exp(-x/500)",0,2000);
TF1 FGluon_m("FGluon_m","exp(-x/50)",80,180);
TLorentzVector generate_gluon();


TF1 FDetector_e_res_jet("FDetector_e_res_jet","exp(-0.5*(x-1)^2/(0.05*0.05))",0.5,1.5);//5% relative energy resolution
void detector_resolution_jet(TLorentzVector & Photon1_p4, TLorentzVector & Photon2_p4, TLorentzVector & Photon1_p4_reco, TLorentzVector & Photon2_p4_reco);


void generate_dijet_TTree(int N=100){

  create_tree("dijet");

  //event loop
  for(int e=0;e<N;e++){
    if(e%100==0)cout<<"event "<<e<<endl;

    
    //////////////////////////////////
    /// Theory model
    /////////////////////////////////
    
    ///Production
    TLorentzVector Gluon_p4 = generate_gluon();
    
    ///Decay 
    TLorentzVector Jet1_p4;
    TLorentzVector Jet2_p4;
    decay_higgs(Gluon_p4, Jet1_p4, Jet2_p4);

    
    //////////////////////////
    /// Detector acceptance and efficiency
    //////////////////////////
    bool pass = detector_efficiency(Jet1_p4.Eta(), Jet2_p4.Eta());

    ///Detector Resolution
    TLorentzVector Jet1_p4_reco;
    TLorentzVector Jet2_p4_reco;
    if(pass)  ///in case photons did not pass detection set energy to 0, all events will be saved but reconstruced objects will be 0
      detector_resolution_jet(Jet1_p4, Jet2_p4, Jet1_p4_reco, Jet2_p4_reco);
    
    
    //////////////////////////////
    /// Data acquisition
    ////////////////////////////

    ///Save to tree
    h_gen_px=Gluon_p4.Px();
    h_gen_py=Gluon_p4.Py();
    h_gen_pz=Gluon_p4.Pz();
    h_gen_e=Gluon_p4.E();
    h_gen_m=Gluon_p4.Mag();

    if(Jet1_p4.Pt()>Jet2_p4.Pt()){
      ph1_gen_px=Jet1_p4.Px();
      ph1_gen_py=Jet1_p4.Py();
      ph1_gen_pz=Jet1_p4.Pz();
      ph2_gen_px=Jet2_p4.Px();
      ph2_gen_py=Jet2_p4.Py();
      ph2_gen_pz=Jet2_p4.Pz();
      ph1_reco_px=Jet1_p4_reco.Px();
      ph1_reco_py=Jet1_p4_reco.Py();
      ph1_reco_pz=Jet1_p4_reco.Pz();
      ph2_reco_px=Jet2_p4_reco.Px();
      ph2_reco_py=Jet2_p4_reco.Py();
      ph2_reco_pz=Jet2_p4_reco.Pz();
    }else{
      ph1_gen_px=Jet2_p4.Px();
      ph1_gen_py=Jet2_p4.Py();
      ph1_gen_pz=Jet2_p4.Pz();
      ph2_gen_px=Jet1_p4.Px();
      ph2_gen_py=Jet1_p4.Py();
      ph2_gen_pz=Jet1_p4.Pz();
      ph1_reco_px=Jet2_p4_reco.Px();
      ph1_reco_py=Jet2_p4_reco.Py();
      ph1_reco_pz=Jet2_p4_reco.Pz();
      ph2_reco_px=Jet1_p4_reco.Px();
      ph2_reco_py=Jet1_p4_reco.Py();
      ph2_reco_pz=Jet1_p4_reco.Pz();
    }

    tree->Fill();
  }
  
  TFile OFile("generation_dijet.root","recreate");
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
  C.Print("generation_dijet_NPho.png");
  cout<<HNPho.GetBinContent(1)<<" "<<HNPho.GetBinContent(2)<<" "<<HNPho.GetBinContent(3)<<" "<<endl;
  
}



//////////////////////////////////////////////////////////////////////////
//////// auxiliary functions
/////////////////////////////////////////////////////////////////////////
TLorentzVector generate_gluon(){
    float theta = FGluon_theta.GetRandom();
    float phi = FGluon_phi.GetRandom();
    float p = FGluon_p.GetRandom();
    float m = FGluon_m.GetRandom();
    TLorentzVector Gluon_p4;
    Gluon_p4.SetPx(p*sin(theta)*cos(phi));
    Gluon_p4.SetPy(p*sin(theta)*sin(phi));
    Gluon_p4.SetPz(p*cos(theta));
    Gluon_p4.SetE(sqrt(m*m + p*p));

    return Gluon_p4;
}


void detector_resolution_jet(TLorentzVector & Jet1_p4, TLorentzVector & Jet2_p4, TLorentzVector & Jet1_p4_reco, TLorentzVector & Jet2_p4_reco){

    float ph1_e_res = FDetector_e_res_jet.GetRandom();
    float ph2_e_res = FDetector_e_res_jet.GetRandom();    
    float ph1_theta_res = 0; //FDetector_angle_res.GetRandom();
    float ph2_theta_res = 0; //FDetector_angle_res.GetRandom();
    float ph1_phi_res = 0; //FDetector_angle_res.GetRandom();
    float ph2_phi_res = 0; //FDetector_angle_res.GetRandom();

    Jet1_p4_reco.SetPx((Jet1_p4.E()*ph1_e_res) * sin(Jet1_p4.Theta() + ph1_theta_res) * cos(Jet1_p4.Phi() + ph1_phi_res));
    Jet1_p4_reco.SetPy((Jet1_p4.E()*ph1_e_res) * sin(Jet1_p4.Theta() + ph1_theta_res) * sin(Jet1_p4.Phi() + ph1_phi_res));
    Jet1_p4_reco.SetPz((Jet1_p4.E()*ph1_e_res) * cos(Jet1_p4.Theta() + ph1_theta_res));
    Jet1_p4_reco.SetE(Jet1_p4.E()*ph1_e_res);    

    Jet2_p4_reco.SetPx((Jet2_p4.E()*ph2_e_res) * sin(Jet2_p4.Theta() + ph2_theta_res) * cos(Jet2_p4.Phi() + ph2_phi_res));
    Jet2_p4_reco.SetPy((Jet2_p4.E()*ph2_e_res) * sin(Jet2_p4.Theta() + ph2_theta_res) * sin(Jet2_p4.Phi() + ph2_phi_res));
    Jet2_p4_reco.SetPz((Jet2_p4.E()*ph2_e_res) * cos(Jet2_p4.Theta() + ph2_theta_res));
    Jet2_p4_reco.SetE(Jet2_p4.E()*ph2_e_res);    
}


