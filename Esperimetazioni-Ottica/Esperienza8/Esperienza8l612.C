//
//  Esperienza8l612.cpp
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

void Esperienza8l612()
{
    
    
    //----------------------------DATI-------------------------
    //Raccolta dati led 612nm
    
    float Vc[] = { 99.9, 200, 300, 350.4, 414.8, 424.4, 409.2, 499.6, 1001, 2003, 3003}; //mV
    float sVc[] = {0.1, 0.1, 0.1 ,0.1, 0.1, 0.1,0.1, 0.1, 1, 1, 1};
    
    
    float I[]= {59.2, 36.2, 16.9, 8.6, 0.2, -1.0, 1.0, -8.6, -23.7, -25.1, -25.4 }; //pA
    float sI[] = {0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1};
    
    
    //numero misure prese
    
    int nmisure = 11  ;
    
    
    
    
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





