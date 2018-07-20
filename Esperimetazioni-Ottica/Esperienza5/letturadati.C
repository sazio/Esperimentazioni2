#include <iostream>
#include <fstream>
#include <string>
#include <algorithm> 


#include <TCanvas.h>
#include <TH1F.h>
#include <TLegend.h>
#include <TAxis.h>
#include <TF1.h>
#include <TMath.h>

using namespace std;

  void letturaFile (const string &nome_file, const double & nbins, const double& minb, const double& maxb) {
  ifstream myfile;
  myfile.open(nome_file.c_str(),  ios::out);

  if(!myfile.is_open()) cout << "File " << nome_file << " non trovato." << endl;
  string line;

  TH1F *histogramma = new TH1F("Istogramma","grafico",nbins, minb, maxb);

   while ( getline (myfile,line)){
   
     histogramma->Fill(atof(line.c_str()));
    
   }
   myfile.close();

   TCanvas *cX = new TCanvas("x","x",200,10,600,400);
  cX->cd();

 histogramma->GetYaxis()->SetRangeUser(0,(histogramma->GetMaximum()*1.10));
 histogramma->SetStats(kFALSE);
 histogramma->GetXaxis()->SetTitle("x [mm]");
 histogramma->GetYaxis()->SetTitle("Conteggi");

  histogramma->SetLineColor(2);
  histogramma->SetLineWidth(2);
  histogramma->Draw();
  TF1 *gauss = new TF1("gauss","gaus");
  histogramma->Fit("gauss","ME");
  cout << "Chi^2:" << gauss->GetChisquare() << ", number of DoF: " << gauss->GetNDF() << " (Probability: " << gauss->GetProb() << ")." << endl;
  }

void inputdati(int &n,double &Min, double &Max, string &File){

  cout<<"Inserire nome file"<<endl;cin>> File;cout<<endl;
  cout<<"Inserire numero colonne, minimo e massimo"<<endl;cin>>n>>Min>>Max; cout<<endl;
  }
void letturadati(){
  int n;
  double Min;
  double Max;
  string File;
  inputdati(n,Min,Max,File);
  letturaFile(File,n,Min,Max);
}


