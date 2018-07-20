//
//  Esperienza8.C
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

void Esperienza8l470()
{
    
    
    //----------------------------DATI-------------------------
    //Raccolta dati led 470nm
    
    float Vc[] = {7.3, 200.5, 400.4, 600.6, 760.2, 800.4, 850.2, 900.5, 951.3, 1001.0, 1050.0, 1061.0, 1099.0, 1300.0, 1510.0, 2001.0, 2504.0, 3000.0  }; //mV
    float sVc[] = {0.1, 2.1, 4.1, 6.1, 7.1, 8.1, 8.6, 9.1, 9.6, 10.1, 10.6, 10.7, 11.1, 13.1, 15.2, 20.1, 25.1, 30.1};
    
    
    float I[]= { 50.1, 34.9, 21.7, 11.8, 8.0, 4.9, 3.5, 2.9, 1.7, 0.8, 0.2, 0, -0.2, -1, -1.4, -1.5, -1.5, -1.5}; //pA
    float sI[] = {0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1 };
    
    
    //numero misure prese
    
    int nmisure = 18;
    
    
    
    
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





