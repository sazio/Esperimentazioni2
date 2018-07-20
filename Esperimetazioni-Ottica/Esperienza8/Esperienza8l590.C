//
//  Esperienza8l590.cpp
//  
//
//  Created by Simone on 17/05/16.
//
//

//Esperienza8 (Planck) led



#include <iostream>
#include <TGraphErrors.h>
#include <TAxis.h>
#include<TCanvas.h>
#include <TF1.h>
#include "TVirtualFitter.h"
#include <iomanip>

//raccolta dati
//590 nm

using namespace std;


void Esperienza8l590()
{
    
    
    float Vc[]= {1.1,200.5,300.3,400.6,449.5,475.4,487.7,466.3,600.5,1004,2003,3004};
    float I[]={151.6, 55.1,28.3,9.4, 2.7,0,-1,1.1,-9.5,-17.9,-19.3,-19.4};
    
    float sVc[]={0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,};
    float sI[]={0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,1,1,1,};
    
    
    
    //numero misure prese
    
    int nmisure = 12;
    
    
    
    
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

