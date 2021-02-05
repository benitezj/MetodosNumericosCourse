
void example3(){
  
  ifstream input("/home/DATA/MetodosNumericos/Lesson1.dat");
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
    counter++; //increment line counter
    std::cout<< counter <<" "<< x <<std::endl;
  }

}


 
