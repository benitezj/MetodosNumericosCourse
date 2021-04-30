

void plot_reconstruction(){

  TFile Fsignal("reconstruction_signal.root","read");
  TFile Fdijet("reconstruction_dijet.root","read");

  TH1F* HHiggs_reco_m_signal = (TH1F*) Fsignal.Get("HHiggs_reco_m");
  TH1F* HHiggs_reco_m_dijet = (TH1F*) Fdijet.Get("HHiggs_reco_m");


  TCanvas C;
  C.Clear();
  HHiggs_reco_m_signal->Draw("hist");
  HHiggs_reco_m_dijet->Draw("histsame");
  C.Print("HHiggs_reco_m.png");


  HHiggs_reco_m_signal->Scale(100./HHiggs_reco_m_signal->GetBinContent(125));
  HHiggs_reco_m_dijet->Scale(1500/HHiggs_reco_m_dijet->GetBinContent(100));
  C.Clear();
  HHiggs_reco_m_dijet->Draw("hist");
  HHiggs_reco_m_signal->Draw("histsame");
  C.Print("HHiggs_reco_m_scaled.png");

  
  HHiggs_reco_m_signal->Add(HHiggs_reco_m_dijet);
  HHiggs_reco_m_signal->GetXaxis()->SetRangeUser(90,170);
  HHiggs_reco_m_signal->GetYaxis()->SetRangeUser(0,2000);
  HHiggs_reco_m_signal->SetMarkerStyle(8);
  HHiggs_reco_m_signal->SetMarkerSize(0.8);
  C.Clear();
  HHiggs_reco_m_signal->Draw("histpe");
  HHiggs_reco_m_dijet->Draw("histsame");
  C.Print("HHiggs_reco_m_scaled_added.png");
  

  TFile OutputF("signal_plus_dijet.root","recreate");
  HHiggs_reco_m_signal->SetName("signal_plus_dijet");
  HHiggs_reco_m_signal->Write();
  OutputF.ls();
  OutputF.Close();

}
