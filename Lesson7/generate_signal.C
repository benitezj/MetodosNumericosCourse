float H_mass = 125;

float EtaFromTheta(float theta){ return -log(tan(theta/2));}
float ThetaFromEta(float eta){ return 2*atan(exp(-eta));}

float det_length = 4;//meters, full extent
float det_r1 = 0.2;//meters, endcap calorimeter radius from beam line
float det_r2 = 1.0;//meters, barrel calorimeter radius from beam line
float det_rapidity_max = EtaFromTheta( 3.14159/2 -  atan(det_length/(2*(det_r1))) );//this is the detector angular acceptance  
bool det_accept(float rap){
  if( fabs(rap)>det_rapidity_max ) return 0;
  return 1;
}

void generate_signal(int N=100){

  bool apply_efficiency = 1;

  //signal model (Higgs production)
  TF1 FHiggs_eta("FHiggs_eta","exp(-0.5*x*x/9)",-20,20); 
  TF1 FHiggs_pt("FHiggs_pt","x*exp(-x/100)",0,1000);

  //Higgs decay model (scalar decay to two photons -> uniform angle)
  TF1 FPhoton_angle("FPhoton_angle","1",0,3.14159);

  //Detector
  TF1 FDetector_eff("FDetector_eff","1",0,1);//this will be used to apply detector efficiency
  TF1 FDetector_e_res("FDetector_e_res","exp(-0.5*(x-1)^2/(0.1*0.1))",0.5,1.5);//10% energy resolution
  TF1 FDetector_rap_res("FDetector_rap_res","exp(-0.5*x*x/(0.05*0.05))",-0.4,0.4);//+/- 0.05 resolution on the rapidity (angle) 

  
  //data file
  ofstream of;
  of.open("higgs_signal.dat");
  
  
  //event loop
  for(int e=0;e<N;e++){
    if(e%100==0)cout<<"event "<<e<<endl;

    ////////////////////////
    ///Generate the Higgs
    float eta = FHiggs_eta.GetRandom();
    float p = FHiggs_pt.GetRandom();
    TLorentzVector Higgs_p4;
    Higgs_p4.SetPtEtaPhiM(p,eta,0,H_mass);

    ///////////////////////
    ///Decay of the Higgs
    //step 1: in Higgs rest frame, photons get half the Higgs mass and random angles in theta
    TLorentzVector Photon1_p4;
    Photon1_p4.SetPtEtaPhiM(H_mass/2, EtaFromTheta(FPhoton_angle.GetRandom()), 0, 0);
    TLorentzVector Photon2_p4;
    Photon2_p4.SetPtEtaPhiM(H_mass/2, EtaFromTheta(FPhoton_angle.GetRandom()), 0, 0);
    //step 2: boost along Higgs generated momentum to get photons in lab frame
    Photon1_p4.Boost(Higgs_p4.BoostVector());
    Photon2_p4.Boost(Higgs_p4.BoostVector());

    ////////////////////////
    //Apply detector acceptance, save event if both photons are in the detector coverage
    if(apply_efficiency && !det_accept(Photon1_p4.Eta())) continue;
    if(apply_efficiency && !det_accept(Photon2_p4.Eta())) continue;

    ///////////////////////
    ////apply detector response
    //step 1: detection efficiency, not all photons will be detected by the sensor and electronics, apply 95% sensor efficiency
    if(apply_efficiency && FDetector_eff.GetRandom()>0.95) continue; //first photon
    if(apply_efficiency && FDetector_eff.GetRandom()>0.95) continue; //second photon
    
    //step 2: detector resolution, apply energy and angular resolution to each photon
    float ph1_e_res = FDetector_e_res.GetRandom();
    float ph2_e_res = FDetector_e_res.GetRandom();
    float ph1_rap_res = FDetector_rap_res.GetRandom();
    float ph2_rap_res = FDetector_rap_res.GetRandom();
	

    /////////////////////
    //// Save to data file, first the true quantities, then the reconstructed quantities
    of<<Higgs_p4.Pt()<<" "<<Higgs_p4.Eta();

    if(Photon1_p4.Pt()>Photon2_p4.Pt()){//Because photons are identical particles we must not be able to identify ph1 vs ph2, therefore save using momentum ordering instead
      of<<" "<<Photon1_p4.Pt()<<" "<<Photon1_p4.Eta()
	<<" "<<Photon2_p4.Pt()<<" "<<Photon2_p4.Eta()
	<<" "<<Photon1_p4.Pt()*ph1_e_res<<" "<<(Photon1_p4.Eta()+ph1_rap_res)
	<<" "<<Photon2_p4.Pt()*ph2_e_res<<" "<<(Photon2_p4.Eta()+ph2_rap_res);
    }else{
      of<<" "<<Photon2_p4.Pt()<<" "<<Photon2_p4.Eta()
	<<" "<<Photon1_p4.Pt()<<" "<<Photon1_p4.Eta()
	<<" "<<Photon2_p4.Pt()*ph2_e_res<<" "<<(Photon2_p4.Eta()+ph2_rap_res)
	<<" "<<Photon1_p4.Pt()*ph1_e_res<<" "<<(Photon1_p4.Eta()+ph1_rap_res);	
    }
    of<<std::endl;
    
    
  }
  of.close();

  
}
