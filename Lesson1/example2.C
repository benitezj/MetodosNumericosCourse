

void example2(){

  TF1 FGaussian("FGaussian","[0]*exp(-0.5*(x-[1])**2/[2]**2)",0,2); 
  FGaussian.SetParameter(0,1);//normalization
  FGaussian.SetParameter(1,1);//mean
  FGaussian.SetParameter(2,0.1);//sigma

  for(int i=0;i<100;i++){
    std::cout<<FGaussian.GetRandom()<<std::endl;
  }
  
}
