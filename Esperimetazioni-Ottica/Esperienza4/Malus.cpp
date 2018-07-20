//
//  Malus.cpp
//  
//
//  Created by Simone Azeglio on 24/06/16.
//
//

#include <stdio.h>
#include <iostream>
#include <TGraphErrors.h>     // ci serve per istanziare grafici
#include <TAxis.h>            // ci serve per manipolare gli assi dei grafici
#include <TCanvas.h>          // ci serve per disegnare i grafici
#include <TF1.h>              // ci serve per scrivere le funzioni con cui fittare i grafici
#include "TVirtualFitter.h"   // ci serve come supporto per i fit
#include <iomanip>            // ci serve per manipolare l'output a video


using namespace std;

void Malus(){
    
    // Angoli di 10 in 10 gradi -- -- Trasformati in radianti --
    
    float theta[] = {0.00, 0.17, 0.35, 0.52, 0.70, 0.87, 1.05, 1.22, 1.40, 1.57, 1.75, 1.92, 2.09, 2.27, 2.44, 2.62, 2.79, 2.97, 3.14, 3.32, 3.49, 3.67, 3.84, 4.01, 4.19, 4.36, 4.54, 4.71, 4.89, 5.06, 5.24, 5.41, 5.59, 5.76, 5.93, 6.11, 6.28};

    float stheta[]  ={0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01};
    
    float I_M[] = {0.23, 0.39, 0.6, 0.87, 1.14, 1.39, 1.51, 1.53, 1.47, 1.35, 1.18, 0.93, 0.69, 0.46, 0.27, 0.14, 0.09, 0.19, 0.33, 0.52, 0.81, 1.1, 1.34, 1.53, 1.58, 1.54, 1.46, 1.25, 1.01, 0.77, 0.51, 0.29, 0.16, 0.09, 0.14, 0.27, 0.34};
    
    float sI_M[] = {0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02};
    
    
    // numero misure
    int nmisure = 37 ;
    
    
    //--------- Grafico
    
    TCanvas *cI_Mtheta = new TCanvas("cI_Mtheta","I(theta)", 200,10,600,400);
    
    cI_Mtheta-> SetFillColor(0);
    
    cI_Mtheta->cd();
    
    TGraphErrors *gI_Mtheta = new TGraphErrors(nmisure, theta, I_M, stheta, sI_M);
    
    gI_Mtheta->SetMarkerSize(0.6);
    gI_Mtheta->SetMarkerStyle(21) ;
    gI_Mtheta-> SetTitle("I(theta)");
    
    gI_Mtheta->GetXaxis()->SetTitle("theta[rad]");
    gI_Mtheta->GetYaxis()->SetTitle("I[microA]");
    
    gI_Mtheta->Draw("AP");
    
    // --------- Fit ----
    cout<< "-----------------------------------Fit legge di Malus ----------------------------------" ;
    
    TF1 *malus = new TF1("malus", "[1]*TMath::Cos(x+[3])*TMath::Cos(x+[3]) + [2]");
    
   // malus->SetParLimits(1, 0.27,0.33) ;
    
   
  
    
    
    gI_Mtheta->Fit(malus, "M+");
    
    cout << "Chi^2:" << malus->GetChisquare() << ", number of DoF: " << malus->GetNDF() << " (Probability: " << malus->GetProb() << ")." << endl;
    cout << "--------------------------------------------------------------------------------------------------------" << endl;
    
    // ----------------------------------------------------------------- //



}
