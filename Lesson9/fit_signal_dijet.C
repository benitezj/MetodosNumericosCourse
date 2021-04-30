//TF1 Model("Model","[0]+[1]*(x-[3])",0,200);//parameters 0 and 3 will be fixed, only 1 will be scanned
TF1 Model("Model","[0]+[1]*(x-[3]) + [4]*exp(-0.5*(x-125)*(x-125)/8*8)",0,200);//parameters 0 and 3 will be fixed, only 1 will be scanned


float compute_logL(TH1F* H, int bin1, int bin2){

  float ModelNorm=H->Integral(bin1,bin2)/Model.Integral(bin1,bin2);
  float logL=0;
  for(int b=bin1;b<=bin2;b++){
    float v = Model.Eval(b)*ModelNorm;
    logL += H->GetBinContent(b) * log(v);
  }

  return -logL;//return NLL
}


void fit_signal_dijet(){

  TFile InputFile("../Lesson7/signal_plus_dijet.root","read");
  TH1F * H=(TH1F*)InputFile.Get("signal_plus_dijet");//histogram with 200 bins in range 0 - 200
  cout<<H->GetXaxis()->GetNbins()<<" "<<H->GetXaxis()->GetXmin()<<" "<<H->GetXaxis()->GetXmax()<<endl;

  int lowlimit=115;
  int hilimit=140;
  Model.SetParameter(3,lowlimit);//start the fit at m=110
  Model.SetParameter(0,H->GetBinContent(lowlimit));

  float minNLL=100000;
  int NSCANPOINTS=1000;
  float minNLLpar=0;
  
  ///Background scan [1]
  //  float minpar=-25;
  //  float maxpar=-10;
  
  ///Signal scan [4]
  Model.SetParameter(1,-18.3);
  float minpar=-100;
  float maxpar=200;



  TGraph GlogL;
  for(int i=0;i<NSCANPOINTS;i++){
    float par = minpar + i*(maxpar - minpar)/NSCANPOINTS;

    //Model.SetParameter(1,par);//background scan
    Model.SetParameter(4,par);//signal scan

    float NLL = compute_logL(H,lowlimit,hilimit);

    GlogL.SetPoint(i,par,NLL);

    if(NLL<minNLL){//track the values to find minimum
      minNLL=NLL;
      minNLLpar=par;
    }
  }


  
  TCanvas C;

  C.Clear();
  GlogL.Draw("apl");
  C.Print("fit_signal_dijet_logLScan.png");

  cout<<"minimum : "<<minNLLpar<<endl;
  //Model.SetParameter(1,minNLLpar);
  Model.SetParameter(4,minNLLpar);
  
  C.Clear();
  H->Draw();
  Model.Draw("lsame");
  C.Print("fit_signal_dijet.png");

  
  
}
