#include <iostream>
#include <fstream>
#include <string>
#include <TApplication.h>
#include <TF1.h>
#include <TH1.h>
#include <TCanvas.h>
#include <TStyle.h>
using namespace std;
bool ReadData(char * fileName, TH1D*  myHisto){
        string file = fileName;
        ifstream InFile(file.c_str());
        if(InFile.good()==0)
                return false;

        double x;
        while(true){
                InFile >> x;
                myHisto->Fill(x);
                if(InFile.eof()==true)
                        break;
        }
        return true;
}
int main(int argc, char ** argv){
        TApplication * app = new TApplication("myApp",NULL,NULL);
        TCanvas* cnv=new TCanvas("myCanv","myCanv",0,0,800,500);
        TH1D * histo= new TH1D("name","title",100,0,200);
        //gStyle->SetOptFit(111);
        TF1 * myFun = new TF1("fun", "[p0]*exp(-0.5*pow(((x-[p1])/[p2]),2))+[p3]*exp(-0.5*pow(((x-[p4])/[p5]),2))+exp([p6]*x)*[p7]",0,200);
        myFun->SetParameter(0,1);
        myFun->SetParameter(1,135);
        myFun->SetParameter(2,2.545);
        myFun->SetParameter(4,170);
        myFun->SetParameter(5,-2.665);

        myFun->SetParameter(6,-0.01);
        myFun->SetParameter(7,2284);

        if(!ReadData(argv[1], histo)){
                cout << "Errore";
        }
        cnv->cd();
        histo->Draw();
        histo->Fit("fun");
        cout<< myFun->GetChisquare()/myFun->GetNDF()<<endl;
        cnv->Modified();
        cnv->Update();
        cnv->Print("istogramma_fittato.png", "png");
        app->Run();
}
