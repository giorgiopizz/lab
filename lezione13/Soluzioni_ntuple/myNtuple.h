#ifndef MYNTUPLE_H
#define MYNTUPLE_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "TH1D.h"
#include "TH2D.h"
#include "TGraphErrors.h"

class myNtuple
{
 public:
  myNtuple  (int n) : fields(n) {};
  ~myNtuple ();

  void AddEntry     (double* vals);
  bool LoadFromFile (std::string fileName);
  bool Write2File   (std::string fileName);

  void Fill1DHisto (unsigned int varIndx, TH1D* histo);
  void Fill2DHisto (unsigned int varIndxX, unsigned int varIndxY, TH2D* histo);
  void Fill1DGraph (unsigned int varIndxX, unsigned int varIndxY, unsigned int varIndxErrX, unsigned int varIndxErrY, TGraphErrors* graph);

  std::vector<double*>* GetNtuplePtr () { return &ntuple; };
  int GetEntries () { return ntuple.size(); };

 private:
  int fields;
  std::vector<double*> ntuple;
};

#endif
