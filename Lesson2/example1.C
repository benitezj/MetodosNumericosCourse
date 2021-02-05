
void example1(){

  ////////////////////////////////////////
  /// Part1: Create histogram to fill with the 1D data 
  TH1F H("HLesson2_example1","",100,0,2);
  ///Arguments: Name, Title, Number of bins, range min, range max
  ///TH1F will hold the data counts on y-axis. x-axis range is partitioned into 100 bins.


  //////////////////////////////
  ///Part2: open and read the data file
  //ifstream input("/home/DATA/MetodosNumericos/Lesson1.dat");
  ifstream input("/home/DATA/MetodosNumericos/Lesson2.dat");
  if (!input.is_open()){
    std::cout << "Unable to open file"<<std::endl;
    return;
  }
  
  std::string line;
  float x;
  int counter=0;//use for counting the number of lines
  while (std::getline(input,line)){
    std::stringstream iss(line);
    iss>>x;//fill x with the value from the data file

    //Fill TH1F histogram
    H.Fill(x);//this will add one count at the bin which contains the value x
    
    counter++; //increment data line counter, number of entries in Histogram should match
  }

  ///////////////////////////////
  ///Part 3: Create Canvas for drawing TH1F
  TCanvas C("C","",500,500);//Arguments: Name, Title, width, height

  //Lets draw the distribution and print to a file
  C.Clear();
  H.Draw("hist");
  C.Print("Lesson2_example1.png");//extension here defines type of file to be created, examples: png, gif, pdf


//  ///////////////////////////////////
//  ///Part 4: create a TFile and save the TH1F object
//  TFile File("Lesson2_example1.root","recreate");//Arguments: file name,  option: create, update, recreate
//  File.cd();//move into the file (similar to bash)
//  H.Write();
//  File.ls();//just show the contents, histogram object should be shown 
//  File.Close();

  
}


 
