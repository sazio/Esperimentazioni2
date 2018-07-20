//
//  Tstudentdistribution.cpp
//  
//
//  Created by Simone Azeglio on 13/06/16.
//
//root -l -e 'Tstudentdistribution_esp2.cpp++("prisma.txt",10,348.160,348.250)'

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <tgmath.h>
#include <math.h>


#include <TCanvas.h>
#include <TH1F.h>
#include <TLegend.h>
#include <TAxis.h>
#include <TF1.h>
#include <TMath.h>


using namespace std;

//double myfunc(double x) ;


void Tstudentdistribution_esp2(const std::string &nome_file, const double & nbins = 21, const double& minb = 4, const double& maxb = 13) {
    ifstream myfile;
    myfile.open(nome_file.c_str(),  ios::out);
    
    if(!myfile.is_open()) cout << "File " << nome_file << " non trovato." << endl;
    string line;
    
    TH1F *histo_h= new TH1F("histo_h","histoh",nbins, minb, maxb);
    
    
    char serie = 'X';
    
    // Leggi il primo blocco
    while ( getline (myfile,line)){
        if(line == "##A##") {serie = 'A'; continue;}
        
   
        
        if (serie == 'A')  histo_h->Fill(atof(line.c_str()));
    
        
    }  
    myfile.close() ;
    
    
 
    //valori h
    
   // double h[21] = {6.28, 7.61, 7.47, 8.24, 8.14, 7.45, 8.46, 8.49, 11.20, 9.17, 8.29, 6.46, 4.89, 8.01, 5.65, 4.89, 10.40, 7.31, 5.65, 12.00, 9.76};
        
   // TH1F *histo_h = new TH1F("histo_h","histoh",nbins,minb , maxb);
    
    TCanvas *cX = new TCanvas("x","x",200,10,600,400);
    cX->cd();
    
    histo_h->GetYaxis()->SetRangeUser(0,(histo_h->GetMaximum())*1.40);
    histo_h->SetStats(kFALSE);
    histo_h->GetXaxis()->SetTitle("h [J*s]");
    histo_h->GetYaxis()->SetTitle("Conteggi");
    
    
    histo_h->SetLineColor(2);
    histo_h->SetLineWidth(2);
    
    histo_h->Draw();
    
        
    TF1 *myfunc = new TF1 ("myfunc","([0]/((sqrt(3.14*19)*[1]))*pow(1+((x+[2])*(x+[2]))/19, - 10))" , 348.10 ,348.30) ;
   //myfuncfit->Draw() ;
    
    
    //  0 e 1 sono i valori della funzione gamma di eulero 
    myfunc->SetParameter(0, 3.00);
    myfunc->SetParameter(1, 1.33);
    myfunc->SetParameter(2, -348.20);
    
    
    histo_h->Fit("myfunc") ;
    
   // TF1 *myfuncfit = histo_h->GetFunction("myfunc") ;
    myfunc->SetLineColor(1) ;
    
    TLegend *legenda = new TLegend(0.15,0.7,0.4,0.85);
    legenda->AddEntry(histo_h,"serie A");
    legenda->SetFillColor(0);
    legenda->Draw();
    


}


/*double myfunc(double x){
    
    
    return (tgamma(10)/((sqrt(3.14*19)*tgamma(9.5)))*pow(1+(x*x)/19, - 10)) ; } */
    

