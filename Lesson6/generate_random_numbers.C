
int seed = 1;

float get_random(float xmin, float xmax){

  long a = 40692;
  long mod = 2147483399;
  long rand = (a*seed) % mod; 
  seed = rand;//update the seed

  return (xmin + (xmax - xmin)*(((float)rand)/mod));
}


void generate_random_numbers(){


  TH1F HUniform("HUniform","",10,-1,1);
  TH1F HPDF("HPDF","",10,-1,1);
  TH1F HPDF_ROOT("HPDF_ROOT","",10,-1,1);

  TF1 f("f","(3.0/8.)*(1+x**2)",-1,1);
  float fmax=f.Eval(1);//maximum of f(x) is at the endpoints
  
  
  
  for(int i = 0; i<10000;i++){

    ///////////
    //Accentance - rejection Method
    ////////
    float x = get_random(-1,1);
    HUniform.Fill(x); 

    //generate second random number
    float u = get_random(0,fmax);

    //accept or reject x based on value of u
    if(u<f.Eval(x))
      HPDF.Fill(x);


    /////////////////
    /// cross check with ROOT generator
    ////////////////
    HPDF_ROOT.Fill(f.GetRandom());
    

  } 


  TCanvas C;
  C.Clear();
  HUniform.GetYaxis()->SetRangeUser(0,HUniform.GetMaximum()*1.1);
  HUniform.Draw();
  C.Print("Lesson6_uniform.gif");

  C.Clear();
  HPDF.GetYaxis()->SetRangeUser(0,HUniform.GetMaximum()*1.1);
  HPDF.Draw();
  C.Print("Lesson6_pdf.gif");

  C.Clear();
  HPDF_ROOT.GetYaxis()->SetRangeUser(0,HUniform.GetMaximum()*1.1);
  HPDF_ROOT.Draw();
  C.Print("Lesson6_pdf_ROOT.gif");

  
}
