//
//  Esperienza8l524.cpp
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

void Esperienza8l524()
{
    
    
    //----------------------------DATI-------------------------
    //Raccolta dati led 524nm
    
    float Vc[] = {0.1, 200, 400.4, 600.7, 700.2, 800.0, 833.8, 832.5, 835.7, 899.9, 2700}; //mV
    float sVc[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 10 };
    
    
    float I[]= {5414, 3280, 1680, 616, 277, 52.6, 0.4, 1.9, -2.1, -67.8, -135.8}; //pA
    float sI[] = {10, 10, 10, 10, 10, 1, 0.1, 0.1, 0.1, 0.1, 0.1};
    
    
    //numero misure prese
    
    int nmisure = 11;
    
    
    
    
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






