
float H_mass = 125;//GeV

float EtaFromTheta(float theta){ return -log(tan(theta/2));}
float ThetaFromEta(float eta){ return 2*atan(exp(-eta));}


//signal model (Higgs production)
TF1 FHiggs_theta("FHiggs_theta","1",0,TMath::Pi()); 
TF1 FHiggs_phi("FHiggs_phi","1",0,2*TMath::Pi()); 
TF1 FHiggs_p("FHiggs_p","x*exp(-x/500)",0,2000);

//Higgs decay model (scalar decay to two photons -> uniform angle)
TF1 FPhoton_theta("FPhoton_theta","1",0,TMath::Pi()); 
TF1 FPhoton_phi("FPhoton_phi","1",0,2*TMath::Pi()); 

//Detector
float det_length = 4;//meters, full extent
float det_r1 = 0.2;//meters, endcap calorimeter radius from beam line
float det_r2 = 1.0;//meters, barrel calorimeter radius from beam line
float det_rapidity_max = EtaFromTheta( 3.14159/2 -  atan(det_length/(2*(det_r1))) );//this is the detector angular acceptance  
bool det_accept(float rap){ return fabs(rap)<det_rapidity_max ; }//function to accept or reject photon, for detector acceptance 
TF1 FDetector_eff("FDetector_eff","1",0,1);//this will be used to apply detector efficiency
TF1 FDetector_e_res("FDetector_e_res","exp(-0.5*(x-1)^2/(0.01*0.01))",0.5,1.5);//1% relative energy resolution
TF1 FDetector_angle_res("FDetector_angle_res","exp(-0.5*x*x/(0.02*0.02))",-0.4,0.4);//+/- 0.02 absolute resolution on angle



////event TTree 
TTree * tree = NULL;
float h_gen_px;
float h_gen_py;
float h_gen_pz;
float h_gen_e;
float h_gen_m;
float ph1_gen_px;
float ph1_gen_py;
float ph1_gen_pz;
float ph2_gen_px;
float ph2_gen_py;
float ph2_gen_pz;
float ph1_reco_px;
float ph1_reco_py;
float ph1_reco_pz;
float ph2_reco_px;
float ph2_reco_py;
float ph2_reco_pz;

void create_tree(TString title){
  tree = new TTree(title,title);
  
  tree->Branch("h_gen_px",&h_gen_px,"h_gen_px/F");
  tree->Branch("h_gen_py",&h_gen_py,"h_gen_py/F");
  tree->Branch("h_gen_pz",&h_gen_pz,"h_gen_pz/F");
  tree->Branch("h_gen_e",&h_gen_e,"h_gen_e/F");
  tree->Branch("h_gen_m",&h_gen_m,"h_gen_m/F");
  
  tree->Branch("ph1_gen_px",&ph1_gen_px,"ph1_gen_px/F");
  tree->Branch("ph1_gen_py",&ph1_gen_py,"ph1_gen_py/F");
  tree->Branch("ph1_gen_pz",&ph1_gen_pz,"ph1_gen_pz/F");
  tree->Branch("ph2_gen_px",&ph2_gen_px,"ph2_gen_px/F");
  tree->Branch("ph2_gen_py",&ph2_gen_py,"ph2_gen_py/F");
  tree->Branch("ph2_gen_pz",&ph2_gen_pz,"ph2_gen_pz/F");

  tree->Branch("ph1_reco_px",&ph1_reco_px,"ph1_reco_px/F");
  tree->Branch("ph1_reco_py",&ph1_reco_py,"ph1_reco_py/F");
  tree->Branch("ph1_reco_pz",&ph1_reco_pz,"ph1_reco_pz/F");
  tree->Branch("ph2_reco_px",&ph2_reco_px,"ph2_reco_px/F");
  tree->Branch("ph2_reco_py",&ph2_reco_py,"ph2_reco_py/F");
  tree->Branch("ph2_reco_pz",&ph2_reco_pz,"ph2_reco_pz/F");

  cout<<"create_tree done: " <<tree<<endl;  
}
  
void set_tree(){
  if(tree==NULL) return;
  
  tree->SetBranchAddress("h_gen_px",&h_gen_px);
  tree->SetBranchAddress("h_gen_py",&h_gen_py);
  tree->SetBranchAddress("h_gen_pz",&h_gen_pz);
  tree->SetBranchAddress("h_gen_e",&h_gen_e);
  tree->SetBranchAddress("h_gen_m",&h_gen_m);
  
  tree->SetBranchAddress("ph1_gen_px",&ph1_gen_px);
  tree->SetBranchAddress("ph1_gen_py",&ph1_gen_py);
  tree->SetBranchAddress("ph1_gen_pz",&ph1_gen_pz);
  tree->SetBranchAddress("ph2_gen_px",&ph2_gen_px);
  tree->SetBranchAddress("ph2_gen_py",&ph2_gen_py);
  tree->SetBranchAddress("ph2_gen_pz",&ph2_gen_pz);

  tree->SetBranchAddress("ph1_reco_px",&ph1_reco_px);
  tree->SetBranchAddress("ph1_reco_py",&ph1_reco_py);
  tree->SetBranchAddress("ph1_reco_pz",&ph1_reco_pz);
  tree->SetBranchAddress("ph2_reco_px",&ph2_reco_px);
  tree->SetBranchAddress("ph2_reco_py",&ph2_reco_py);
  tree->SetBranchAddress("ph2_reco_pz",&ph2_reco_pz);

  cout<<"tree_set done: " <<tree<<endl;
}
