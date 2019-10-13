#include "myNtuple.h"

myNtuple::~myNtuple ()
{
  for (unsigned int i = 0; i < ntuple.size(); i++)
    if (ntuple[i] != NULL) delete[] ntuple[i];
}

void myNtuple::AddEntry (double* vals)
{
  double* tmp = new double[fields];
  for (unsigned int i = 0; i < fields; i++)
    {
      tmp[i] = vals[i];
    }
  ntuple.push_back(tmp);
}

bool myNtuple::LoadFromFile (std::string fileName)
{
  std::ifstream inFile (fileName.c_str(),std::ios::in);
  
  if (inFile.good() == false)
    {
      std::cout << __PRETTY_FUNCTION__ << "\tError! Problem opening the file: " << fileName.c_str() << std::endl;
      return false;
    }
  
  double val;
  double vals[fields];
  bool exit = false;
  while (exit == false)
    {
      for (unsigned int j = 0; j < fields; j++)
	{
	  inFile >> val;
	  if (inFile.eof() == true)
	    {
	      exit = true;
	      break;
	    }
	  vals[j] = val;
	}
      AddEntry(vals);
    }
  inFile.close();

  return true;
}

bool myNtuple::Write2File (std::string fileName)
{
  std::ofstream outFile (fileName.c_str(),std::ios::out);
  
  if (outFile.good() == false)
    {
      std::cout << __PRETTY_FUNCTION__ << "\tError! Problem opening the file: " << fileName.c_str() << std::endl;
      return false;
    }
  
  for (unsigned int i = 0; i < ntuple.size(); i++)
    {
      for (unsigned int j = 0; j < fields; j++) outFile << ntuple[i][j] << "\t";
      outFile << "\n";
    }
  outFile.close();

  return true;
}

void myNtuple::Fill1DHisto (unsigned int varIndx, TH1D* histo)
{
  for (unsigned int i = 0; i < ntuple.size(); i++)
    histo->Fill(ntuple[i][varIndx]);
}

void myNtuple::Fill2DHisto (unsigned int varIndxX, unsigned int varIndxY, TH2D* histo)
{
  for (unsigned int i = 0; i < ntuple.size(); i++)
    histo->Fill(ntuple[i][varIndxX],ntuple[i][varIndxY]);
}

void myNtuple::Fill1DGraph (unsigned int varIndxX, unsigned int varIndxY, unsigned int varIndxErrX, unsigned int varIndxErrY, TGraphErrors* graph)
{
  for (unsigned int i = 0; i < ntuple.size(); i++)
    {
      graph->SetPoint(graph->GetN(),ntuple[i][varIndxX],ntuple[i][varIndxY]);
      graph->SetPointError(graph->GetN(),ntuple[i][varIndxErrX],ntuple[i][varIndxErrY]);
    }
}
