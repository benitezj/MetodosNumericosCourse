
void example2(){

  ///////////////////////////////////
  ///Part 1: open root file in read mode and extract TH1F object
  TFile File("/home/DATA/MetodosNumericos/Lesson2_example1.root","read");//Arguments: file name,  option: create, update, recreate, read
  if(File.IsZombie()){
    cout<<"!! The file you are trying to open does not exist or is corrupted !!"<<endl;
    return; // terminate the code
  }
  
  File.ls();//just show the contents on terminal 

  ////The following block of code will obtain a pointer to the object inside the file
  TH1F * H = NULL; //here H is a TH1F pointer , created with a *, not full object, 
  H = (TH1F*)File.Get("HLesson2_example1"); // Get returns only address to the full object in the TFile 
  //// Two things happening in the above line:
  // 1) Get finds the object inside file and returns an address,
  // 2) (TH1F*) is a "cast" from TObject to TH1F type.  TFile::Get returns a TObject pointer (general object type), but we know the object is a TH1F. 
  if(H == NULL){
    cout<<"!!! did not find a TH1F called HLesson2_example1 inside TFile !!!"<<endl;
    return;//do not continue, if you try use H the code will crash 
  }
  
  ///////////////////////////////
  ///Part 2: Create Canvas for drawing TH1F (same as Lesson2/example1.C)
  TCanvas C("C","",500,500);
  C.Clear();
  H->Draw("hist"); /// Note how we use -> instead of .  for pointers
  C.Print("Lesson2_example2.png");



  
//  ////////////////////////////
//  ////Part 3: fitting a model to data
//  TF1 F("F","[0]*exp(-0.5*(x-[1])**2/[2]**2)",0,2);
//  F.SetParameter(0,1);//initialize the parameters before fitting otherwise fit may not converge.
//  F.SetParameter(1,1);
//  F.SetParameter(2,0.1);
//  
//  H->Fit(&F); //run the ROOT fitting code that comes with TH1 class:  TH1F::Fit ,  argument is the address of a TF1
//  C.Clear(); // make a graph including the fit function
//  H->Draw("hist"); 
//  F.Draw("same");// "same" means on top of H distribution already in Canvas
//  C.Print("Lesson2_example2_fit.png");
//
//
//
//  /////////////////////////
//  //// Part4: give proper labels to the graph
//  C.Clear();
//  H->SetTitle("Data distribution with fit");
//  H->GetXaxis()->SetTitle(" X ");/// x-axis corresponds to the Random variable X
//  H->GetYaxis()->SetTitle(" counts / bin"); /// y-axis is the number of data counts per bin
//  H->SetStats(0);//turn off the stats box
//  H->Draw("histpe");//Note different option "pe" means show points and stat error
//  F.Draw("same");// "same" means on top of H distribution already in Canvas
//
//  TLegend leg(0.7,0.5,0.9,0.9);///arguments are position coordinates on the Canvas
//  leg.AddEntry(H,"Data","pe");
//  leg.AddEntry(&F,"Model","l");
//  leg.Draw();
// 
//  C.Print("Lesson2_example2_fit_labels.png");
  
  
}


 
