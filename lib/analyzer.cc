#include "analyzer.h"
/*ATTENZIONE! Se l'istogramma non contiene tutti i valori è da controllare
minX_ e maxX_ in quanto è possibile che il valore 0 iniziale sia da spostare*/

analyzer::analyzer(){
        //setto tutte le variabili a zero e i pointer a NULL
        dataNumber_=0;
        minX_=0;
        maxX_=0;
        meanX_=0;
        stdDevX_=0;
        meanError_=0;
        xMeas_.clear();
        yMeas_.clear();
        xErr_.clear();
        yErr_.clear();
        histo_=NULL;
        graph_=NULL;
}
analyzer::~analyzer (){
        //elimino i pointer
        if (histo_!=NULL)    delete histo_;
        if (graph_!=NULL)   delete graph_;
}
bool analyzer::setData (const string fileName, string type){
      //questa funzione leggi i dati da un file, li memorizza in uno o più vettori
      //calcola il massimo, il minimo, il numero di dati e poi crea un istogrammma
      //o un TGraph
      ifstream InFile(fileName.c_str());
      if(InFile.good()==false){
            cout <<"Errore nell'apertura del file"<<endl;
            return false;
      }
      double x;
      int i=0;
      if(type=="counts"){
            while(true){
                    InFile >> x;
                    i++;
                    xMeas_.push_back(x);
                    if(minX_>x)      minX_=x;
                    if(maxX_<x)      maxX_=x;
                    if(InFile.eof()==true)
                            break;
            }
            InFile.close();
            dataNumber_=i;
      }
      else if (type=="measurement"){
            //prendo i dati per il TGraph
            double y, xerr, yerr;
            while(true){
                    InFile >> x >> y>> xerr>> yerr;
                    i++;
                    xMeas_.push_back(x);
                    yMeas_.push_back(y);
                    xErr_.push_back(xerr);
                    yErr_.push_back(yerr);
                    if(InFile.eof()==true)
                            break;
            }
            InFile.close();
            dataNumber_=i;
      }
      else{
            cout << "Tipo sbagliato"<<endl;
            return false;
      }
      if(InFile.eof()==true){
            //costruisco istogramma e TGraph
            if(type=="counts"){
                    int nBins=100;
                    histo_=new TH1D("Counts", "Titolo", nBins, minX_, maxX_);
                    for(int j=0;j<dataNumber_;j++){
                            histo_->Fill(xMeas_.at(j));
                    }
                    //computeMoments(&xMeas_,&xErr_,meanX_,stdDevX_,meanError_);
            }
            else{
                    //sono certo che sia un TGraph in questo caso
                    graph_=new TGraphErrors(fileName.c_str());
                    graph_->SetTitle("Measurements");
                    graph_->GetXaxis()->SetTitle("x (units)");
                    graph_->GetYaxis()->SetTitle("y (units)");
                    graph_->SetMarkerStyle(20);
                    graph_->SetMarkerSize(0.5);
            }
      }
      return true;
}
/*
void computeMoments (vector<double>* values, vector<double>*  errors, double& mean, double& stdDev, double& meanError){

}

void computeChi2 (TF1* fitFunc, double& chi2, int& NDF, double& pValue){

}

void fitData (TF1* fitFunc, double xMin, double xMax){

}

bool testCompatibility (double& pvalue, double meas1, double err1, double meas2, double err2, double significance, string testType, double n1 = 1, double n2 = 1){
  //lo lascio
}

TGraph* computeContour (TF1* myFun, double delta, unsigned int parA, unsigned int parB){
  //lo lascio
}*/
TH1D* analyzer::getHisto(void){
        if(histo_!=NULL)
                return histo_;
        else
                cout << "Non è ancora stato inizializzato correttamente l'istogramma"<<endl;
                return NULL;
}
TGraphErrors* analyzer::getGraph(void){
    if(graph_!=NULL)
            return graph_;
    else
            cout << "Non è ancora stato inizializzato correttamente il grafico"<<endl;
            return NULL;
}
