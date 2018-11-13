#include "analyzer.h"
/*ATTENZIONE! Se l'istogramma non contiene tutti i valori è da controllare
minX_ e maxX_ in quanto è possibile che il valore 0 iniziale sia da spostare*/

analyzer::analyzer(int x){
        //setto tutte le variabili a zero e i pointer a NULL
        n=x;
        dataNumber_=0;
        minX_=numeric_limits<double>::max();
        maxX_=-std::numeric_limits<double>::max();
        meanX_=0;
        stdDevX_=0;
        meanError_=0;
        xMeas_.clear();
        yMeas_.clear();
        xErr_.clear();
        yErr_.clear();
        histo_=NULL;
        graph_=NULL;
        app_=NULL;
        cnv_=NULL;
        fit_ = NULL;
        fitType_ = "";

}
analyzer::~analyzer (){
        //elimino i pointer
        if (histo_!=NULL)    delete histo_;
        if (graph_!=NULL)   delete graph_;
        if (app_!=NULL)      delete app_;
        if (cnv_!=NULL)      delete cnv_;
}
bool analyzer::setData (const string fileName, string type, string fitType_){
      //questa funzione leggi i dati da un file, li memorizza in uno o più vettori
      //calcola il massimo, il minimo, il numero di dati e poi crea un istogrammma
      //o un TGraph
      ifstream InFile(fileName.c_str());
      if(!InFile.good()){
            cerr <<"Errore nell'apertura del file"<<endl;
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
            cerr << "Tipo sbagliato"<<endl;
            return false;
      }
      if(InFile.eof()){
            //costruisco istogramma e TGraph
            if(type=="counts"){
                    int nBins=100;
                    string init= "Counts ";
                    string init2= "Plot ";
                    string fin= init+to_string(n);
                    string fin2= init2+to_string(n);

                    histo_=new TH1D(fin.c_str(), fin2.c_str(), nBins, minX_, maxX_);
                    for(int j=0;j<dataNumber_; ++j){
                            histo_->Fill(xMeas_.at(j));
                    }
                    //fitto l'istogramma per il chi2
                    if(fitType_ != "null"){
                            fit_ = fitType_.c_str();
                            histo_->Fit(fit_);
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

                    if(fitType_ != "null"){
                            fit_ = fitType_.c_str();
                            graph_->Fit(fit_);
                    }
            }
      }
      return true;
}
TH1D* analyzer::getHisto(void){
        if(histo_!=NULL){
                return histo_;
                delete histo_;
        }
        else{
                cerr << "Non è ancora stato inizializzato correttamente l'istogramma"<<endl;
                return NULL;
        }
}
TGraphErrors* analyzer::getGraph(void){
        if(graph_!=NULL){
                return graph_;
                delete graph_;
        }
        else{
                cerr << "Non è ancora stato inizializzato correttamente il grafico"<<endl;
                return NULL;
        }
}


/*
void analyzer::computeMoments (vector<double>* values, vector<double>*  errors, double& mean, double& stdDev, double& meanError){

}
*/
//parametro opzionale, già settato nel file .h, permette sia di inserire una funzione TF1 definita
//dall'utente (o comunque non legata ad un grafico), sia di ricavarla da un grafico già plottato
//NB: è necessario che il grafico sia stato Fittato. Può essere estesa a tutti i tipi di grafico
//Restituisce gli stessi risultati del fit fatto da ROOT nel FitPanel della TApplication
void analyzer::computeChi2(TF1* fitFunc){

        int ndf = 0;
        double chi2 = 0, chiRed = 0;

        if(fitFunc == NULL && fitType_ == "null"){
            try{
                throw std::invalid_argument("Error: the argument provided are not valid.");
            }
            catch(const exception& e){
                cerr << e.what() << endl;
                exit(-1);
            }

        }
        //se l'argomento di default non viene cambiato
        if (fitFunc == NULL && fitType_ != "null"){
                //per l'istogramma
                if(histo_){
                        fitFunc = histo_->GetFunction(fit_);
                        ndf = fitFunc->GetNDF();
                        chi2 = fitFunc->GetChisquare();
                        chiRed = chi2 / ndf;

                        cout << "CHI: "<<chi2 << endl;
                        cout <<"CHI/NDF: "<<chiRed<<endl;
                }
                //per il TGraph
                if(graph_){
                        fitFunc = graph_->GetFunction(fit_);
                        ndf = fitFunc->GetNDF();
                        chi2 = fitFunc->GetChisquare();
                        chiRed = chi2 / ndf;

                        cout << "CHI: "<<chi2 << endl;
                        cout <<"CHI/NDF: "<<chiRed<<endl;
                }
        }
        //per la funzione inserita dall'utente
        else {
                ndf = fitFunc->GetNDF();
                chi2 = fitFunc->GetChisquare();
                chiRed = chi2 / ndf;

                cout << "CHI: "<<chi2 << endl;
                cout <<"CHI/NDF: "<<chiRed<<endl;
        }

}

/*
void analyzer::fitData (TF1* fitFunc, double xMin, double xMax){

}

bool analyzer::testCompatibility (double& pvalue, double meas1, double err1, double meas2, double err2, double significance, string testType, double n1 = 1, double n2 = 1){
  //lo lascio
}

TGraph* analyzer::computeContour (TF1* myFun, double delta, unsigned int parA, unsigned int parB){
  //lo lascio
}*/
/*void analyzer::Display(){
        app_ = new TApplication("myApp",NULL,NULL);
        cnv_ = new TCanvas("myCanv","myCanv",0,0,700,500);
        cnv_->cd();
        if(histo_!=NULL) histo_->Draw();
        if(graph_!=NULL) graph_->Draw("AP");
        cnv_->Modified();
        cnv_->Update();
        app_->Run();
}*/
