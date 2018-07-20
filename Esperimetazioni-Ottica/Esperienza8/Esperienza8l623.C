//
//  Esperienza8l623.cpp
//  
//
//  Created by Simone on 17/05/16.
//
//

#include <iostream>
#include <TGraph.h>
#include <TGraphErrors.h>     // ci serve per istanziare grafici
#include <TAxis.h>            // ci serve per manipolare gli assi dei grafici
#include <TCanvas.h>          // ci serve per disegnare i grafici
#include <TF1.h>              // ci serve per scrivere le funzioni con cui fittare i grafici
#include "TVirtualFitter.h" // ci serve come supporto per i fit
#include <iomanip>            // ci serve per manipolare l'output a video

using namespace std;

void Esperienza8l623()
{
    
    
    //----------------------------DATI-------------------------
    //Raccolta dati led 623nm
    
    float Vc[] = { 1.3, 200.3, 300.1, 352.1 , 365.1, 350.4, 499.5, 1000, 2001, 3000}; //mV
    float sVc[] = {0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 1, 1, 1};
    
    
    float I[]= {31.8, 9.9, 3.2, 0, -0.5, 0.5, -7.7, -17.6, -19.2, -19,3 }; //pA
    float sI[] = {0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1,0.1, 0.1 };
    
    
    //numero misure prese
    
    int nmisure = 10 ;
    
    
    
    
    //--------------------- Grafico I(Vc) -----------------
    
    TCanvas *cIVc = new TCanvas("cIVc","I(Vc)",200,10,600,400);
    
    // 0 è il colore bianco
    cIVc->SetFillColor(0);
    cIVc->cd();
    
    TGraphErrors *gIVc = new TGraphErrors(nmisure,Vc,I,sVc,sI);
    gIVc->SetMarkerSize(0.6);
    gIVc->SetMarkerStyle(21);
    
    //  Titolo del grafico
    gIVc->SetTitle("I(Vc)");
    
    // Titoli degli assi
    gIVc->GetXaxis()->SetTitle("Vc [mV]");
    gIVc->GetYaxis()->SetTitle("I [pA]");
    
    gIVc->Draw("AP");
    
    
}







