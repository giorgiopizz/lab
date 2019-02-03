/*
c++ -o esercizio01 esercizio01.cpp
*/

#include <iostream>     
#include <fstream> 
#include <string>
#include <vector>
#include <cmath>

bool readData(std::string fileName, std::vector<double>& valVec, std::vector<double>& errVec)
{
  std::fstream myFile;
  
  myFile.open(fileName.c_str(),std::ios::in);
  if (myFile.good() == false)
    {
      return false;
    }
  
  double val, err;
  while (true)
    {
      myFile >> val >> err;
      if (myFile.eof() == true) break;
      valVec.push_back(val);
      errVec.push_back(err);
    }
  myFile.close();
    
  return true;
}

int main (int argc, char** argv)
{
  // Verifica che vengano passati almeno tre parametri da riga di comando
  if (argc < 3)
    {
      std::cout << "Digitare i nomi dei file da riga di comando" << std::endl;
      std::cout << "\t./esercizio01 dati.txt risultati.txt" << std::endl;
      return 1;
    }
  
  std::string fileInput  = argv[1];
  std::string fileOutput = argv[2];

  
  // ############################
  // # Read data and processing #
  // ############################
  std::vector<double> vec1;
  std::vector<double> vec2;
  if (readData(fileInput, vec1, vec2) == false)
    {
      std::cout << "Problem opening the file: " << fileInput.c_str() << std::endl;
      return 1;
    }

  
  int Nrighe = vec1.size();
  std::cout << "Il vector vec1 contiene " << vec1.size() << " elementi" << std::endl;
  std::cout << "Il vector vec2 contiene " << vec2.size() << " elementi" << std::endl;
  
  double sum = 0., sumSq = 0.;
  double mean, devst;
  
  for (int i = 0; i < Nrighe; i++)
    {
      sum   += vec1[i];
      sumSq += vec1[i]*vec1[i];
    }
  mean  = sum/(float)Nrighe;
  devst = sqrt(sumSq/(float)Nrighe - mean*mean);	
  
  std::ofstream OutFile (fileOutput.c_str());
  OutFile << "Prima colonna di dati:\n";
  OutFile << "\tMedia    = " << mean << std::endl;
  OutFile << "\tDev.Std. = " << devst << std::endl;
  
  // Azzera i contatori
  sum   = 0.;
  sumSq = 0.;
  
  for (int i = 0; i < Nrighe; i++)
    {
      sum   += vec2[i];
      sumSq += vec2[i]*vec2[i];
    }
  mean  = sum/(float)Nrighe;
  devst = sqrt(sumSq/(float)Nrighe - mean*mean);
  
  OutFile << "\nSeconda colonna di dati:\n";
  OutFile << "\tMedia    = " << mean << std::endl;
  OutFile << "\tDev.Std. = " << devst << std::endl;
  OutFile.close();

  return 0;
}
