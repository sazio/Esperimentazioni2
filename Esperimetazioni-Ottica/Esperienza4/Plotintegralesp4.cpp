//
//  Plotintegralesp4.cpp
//  
//
//  Created by Simone Azeglio on 17/06/16.
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




void Plotintegralesp4(){

   //
    
    float x1[] = {185, 175, 167, 160, 156, 152, 148, 143, 140, 136, 131, 128, 126, 121, 114, 107,101, 84.3, 68.8, 62.3};
    float sx1[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    
    float I_R[] = {0.0289,0.0281, 0.0272, 0.0269,0.0266, 0.0262, 0.0257, 0.0254, 0.0250, 0.0246, 0.0242, 0.0238, 0.0236, 0.0231, 0.0222, 0.0214, 0.0206, 0.0182, 0.0158, 0.0145};
    float sI_R[] = {0.0008, 0.0007, 0.0007, 0.0007, 0.0007, 0.0007, 0.0006, 0.0006, 0.0006, 0.0006, 0.0006, 0.0006, 0.0006, 0.0005, 0.0005, 0.0005, 0.0005, 0.0005, 0.0005, 0.0005};
    
   // numero misure
    int nmisure = 20 ;
    
    
   //--------- Grafico
    
    TCanvas *cIx1 = new TCanvas("cIx1","IR(x)", 200,10,600,400);
    
    cIx1-> SetFillColor(0);
    
    cIx1->cd();
    
    TGraphErrors *gIx1 = new TGraphErrors(nmisure, x1, I_R, sx1, sI_R);
    
    gIx1->SetMarkerSize(0.6);
    gIx1->SetMarkerStyle(21) ;
    gIx1-> SetTitle("IR(x)");
    
    gIx1->GetXaxis()->SetTitle("x[mm]");
    gIx1->GetYaxis()->SetTitle("IR");
    
    gIx1->Draw("AP");
    
    // --------- Fit ----
    cout<< "-----------------------------------Fit ipotesi parabolica ----------------------------------" ;
    
    TF1 *ipotesi = new TF1("ipotesi", "[1]+[0]*sqrt(x)");
    
    ipotesi->SetParameter(0, 2.659*pow(10,-3));
   /// ipotesi->SetParameter(1, 2.953*pow(10,-3));

   
    gIx1->Fit(ipotesi, "M+");

    cout << "Chi^2:" << ipotesi->GetChisquare() << ", number of DoF: " << ipotesi->GetNDF() << " (Probability: " << ipotesi->GetProb() << ")." << endl;
    cout << "--------------------------------------------------------------------------------------------------------" << endl;
    
   // ----------------------------------------------------------------- //

    // A questo punto possiamo iniziare l' analisi dell' esperienza , come se non avessimo posto il beker nel posto sbagliato
    
    //Ora scriviamo i dati raccolti
    
    float x[] = {0, 9.93, 17.65, 24.90, 28.52, 32.96, 37.30, 40.89, 44.59, 48.60, 52.87, 56.59, 58.44, 62.82, 69.87, 76.67, 82.81, 99.66, 115.16, 121.68};
    float sx[] = {1.5, 1.5, 1.5, 1.5, 1.5, 1.5, 1.5, 1.5, 1.5, 1.5, 1.5, 1.5, 1.5, 1.5, 1.5, 1.5, 1.5, 1.5, 1.5, 1.5};
    
    float I[] = {87.65, 28.80, 15.15, 8.10, 6.40, 5.00, 3.60, 2.92, 2.40, 1.90, 1.60, 1.25, 0.90, 0.80, 0.60, 0.40, 0.20, 0.15, 0.09, 0.01};
    float sI[] = {0.35, 0.35, 0.35, 0.35, 0.35, 0.35, 0.35, 0.35, 0.35, 0.35, 0.35, 0.35, 0.35, 0.35, 0.35,0.35,0.35, 0.35, 0.35, 0.35 };
    
    // numero misure
    int nmisure1 = 20 ;
    
    
    // GRafico
    
    TCanvas *cIx = new TCanvas("cIx","I(x)", 200,10,600,400);
    
    cIx-> SetFillColor(0);
    
    cIx->cd();
    
    TGraphErrors *gIx = new TGraphErrors(nmisure1, x, I, sx, sI);
    
    gIx->SetMarkerSize(0.6);
    gIx->SetMarkerStyle(21) ;
    gIx-> SetTitle("I(theta)");
    
    gIx->GetXaxis()->SetTitle("x [mm]");
    gIx->GetYaxis()->SetTitle("I");
    
    gIx->Draw("AP");
    
    
    

    
    // Fit con esp normale
    
    TF1 *exp_normale = new TF1("exp_normale","[0]*(TMath::Exp(-[1]*x))") ;
    
    exp_normale->FixParameter(0,87.65);
    exp_normale->SetParLimits(1, 0.0680, 0.0700);
    
    exp_normale->SetLineColor(3);
    
    gIx->Fit(exp_normale, "M+");
    
    
    cout << "Chi^2:" << exp_normale->GetChisquare() << ", number of DoF: " << exp_normale->GetNDF() << " (Probability: " << exp_normale->GetProb() << ")." << endl;
    cout << "--------------------------------------------------------------------------------------------------------" << endl;

    
    // --------- Fit con esp corretto----
    //const double esponenziale = 2.718281828;
    
    TF1 *expo_corretto = new TF1("expo_corretto", "([1]+ [0]*sqrt(x))*(TMath::Exp(-[2]*x))");
    
   // expo_corretto->SetParameter(0,7.205);
    expo_corretto->SetParLimits(1, 87.6300,87.6500);
    expo_corretto->SetParLimits(2,0.0676,0.0684);

    expo_corretto->SetParName(1,"I0");
    expo_corretto->SetParName(2,"Absorption coefficient");
    
    expo_corretto->SetLineColor(4);
    
    
    
    gIx->Fit(expo_corretto, "M+");
    
    cout << "Chi^2:" << expo_corretto->GetChisquare() << ", number of DoF: " << expo_corretto->GetNDF() << " (Probability: " << expo_corretto->GetProb() << ")." << endl;
    cout << "--------------------------------------------------------------------------------------------------------" << endl;
    

        
        }
    
    

    
    



