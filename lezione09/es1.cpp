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
        TCanvas* cnv=new TCanvas("myCanv","myCanv",0,0,700,500);
        TH1D * histo= new TH1D("name","title",80, 0, 10);
        gStyle->SetOptFit(1111);
        TF1 * myFun = new TF1("fun", "[p0]*exp(-0.5*pow(((x-[p1])/[p2]),2))+([p3]+[p4]*x+[p5]*x*x)",0,10);
        myFun->SetParameter(0,1);
        myFun->SetParameter(1,5);
        myFun->SetParameter(2,2.7);
        myFun->SetParameter(5,-1);
        myFun->SetParName(0,"Ampl");
        myFun->SetParName(1,"Mean");
        myFun->SetParName(2,"Sigma");
        if(!ReadData(argv[1], histo)){
                cout << "Errore";
        }
        cnv->cd();
        histo->Draw();
        histo->Fit("fun");
        cout<< myFun->GetChisquare()/myFun->GetNDF()<<endl;

        cnv->Modified();
        cnv->Update();
        cnv->Print("isto1.png", "png");
        app->Run();

}
