//
//  Esperienza3.cpp
//  
//
//  Created by Simone Azeglio on 14/06/16.
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



void Esperienza3()
{
    
    // --------------------------- DATI ------------------------------- //
  
    // Dati presi in laboratorio: V = tensione, sV = incertezza tensione, i = intensità di corrente, si = incertezza intensità di corrente
    // consiglio di non mettere il valore per V = 0 V altrimenti si avranno problemi nella parte in cui si calcolano i logaritmi
    float lambda_merc[]  = {407.539, 431.044, 492.045, 548.338, 581.049, 601.491, 623.8, 415.854, 495.616, 513.928, 570.382, 589.474};
    float slambda_merc[] = {0.185447,0.195814, 0.223267, 0.252095, 0.262597, 0.271376, 0.282189, 0.169737, 0.917383, 1.1005, 0.804327,1.0556};
    float n_merc[]  = {1.650555608 , 1.642132384, 1.631266004, 1.62416705, 1.621106073, 1.619400728, 1.617691957, 1.647263217, 1.638137258, 1.630087102, 1.621617046 , 1.619571454};
    float sn_merc[] = {0.0002357, 0.00023621, 0.00023686, 0.00023727, 0.00023745, 0.00023754, 0.00023764, 0.0002359, 0.00023645, 0.00023693, 0.00023742, 0.00023753};
    
   /* float lambda_sodio[]  = {415.854, 495.616, 513.928, 570.382, 589.474};
    float slambda_sodio[] = {0.169737, 0.917383, 1.1005, 0.804327,
        1.0556};
    float n_sodio[]  = {1.647263217, 1.638137258, 1.630087102, 1.621617046 , 1.619571454 };
    float sn_sodio[] = {0.0002359, 0.00023645, 0.00023693, 0.00023742, 0.00023753};
    
    */
    
    // numero misure prese
    int nmisure1 = 12 ;
   // int nmisure2 = 5 ;
    // ---------------------------------------------------------------- //
    
    
    
    // --------------------- Grafico n(λ) mercurio ------------------------------ //
    // Creo il canvas (la tela) su cui disegnare il grafico. "n(λ)" è il il suo nome in memoria
    // è bene che sia unico dentro al programma. "i(v)" è semplicemente il titolo del canvas
    // le due coppie di numeri che seguono sono le coordinate dell'angolo superiore sinistro e le seconde
    // la dimensione in pixel lungo x e lungo y
    TCanvas *cn_lambdam = new TCanvas("cn_lambdam"," n(L) ",200,10,600,400);
    // Mi assicuro che la tela sia bianca (0 corrisponde al bianco, per altri colori vedi https://root.cern.ch/doc/master/classTColor.html)
    cn_lambdam->SetFillColor(0);
    // Mi assicuro che disegni su questa tela e non su un altra. Ciò è particolarmente importante quando ho tanti canvas aperti.
    cn_lambdam->cd();
    // Istanzio il grafico. Il costruttore che noi usiamo prende come argomenti:
    // il numero di misure da disegnare, l'array di misure x (=V), l'array di misure y (=i), e gli
    // array delle  rispettive incertezze
    TGraphErrors *gn_lambdam = new TGraphErrors(nmisure1,lambda_merc,n_merc,slambda_merc,sn_merc);
    // Nelle due righe successive disegno i punti del grafico con lo stile che più mi piace.
    // Vedi anche https://root.cern.ch/doc/master/classTAttMarker.html
    gn_lambdam->SetMarkerSize(0.6);
    gn_lambdam->SetMarkerStyle(21);
    // Facile, titolo del grafico
    gn_lambdam->SetTitle("n(L)");
    // Titoli degli assi
    gn_lambdam->GetXaxis()->SetTitle(" L[nm]");
    gn_lambdam->GetYaxis()->SetTitle("n");
    // Do istruzioni al grafico di disegnarsi sul canvas che ho selezionato preventivamente con cd()
    // Esistono diverse opzioni di disegno, vedi anche https://root.cern.ch/doc/master/classTGraphPainter.html
    // "AP" è molto semplice, gli stiamo chiedendo di disegnare gli assi (A) e i punti (P)
    gn_lambdam->Draw("AP");
    // ----------------------------------------------------------------- //
    
    

    // -------- Fit con funzione di cauchy a mercurio --- / /

    
    cout<<"\n\n------------Fit con equazione di Cauchy -----------\n\n" ;
    
    TF1 *cauchy = new TF1("cauchy", "[0]+([1]/(x*x))");
    
    gn_lambdam->Fit(cauchy,"M+") ;
    
    cout << "Chi^2:" << cauchy->GetChisquare() << ", number of DoF: " << cauchy->GetNDF() << " (Probability: " << cauchy->GetProb() << ")." << endl;
    cout << "--------------------------------------------------------------------------------------------------------" << endl;

    
    
    
    //
    TCanvas *cn_lambdas = new TCanvas("n_lambdas","n(l) sodio",200,10,600,400);
    cn_lambdas->SetFillColor(0);
    cn_lambdas->cd();
    TGraphErrors *gn_lambdas = new TGraphErrors(nmisure1,lambda_merc,n_merc,slambda_merc,sn_merc);
    gn_lambdas->SetMarkerSize(0.6);
    gn_lambdas->SetMarkerStyle(21);
    gn_lambdas->SetTitle("n(L)");
    gn_lambdas->GetXaxis()->SetTitle("L[nm]");
    gn_lambdas->GetYaxis()->SetTitle("n");
    gn_lambdas->Draw("AP");

                          
    cout<<"\n\n------------Fit con equazione di Cauchy con termine alla quarta-----------\n\n" ;
    
     TF1 *cauchy1 = new TF1("cauchy1", "[0]+([1]/(x*x))+([2]/(x*x*x*x))");
    
    cauchy1->SetLineColor(3);
    gn_lambdas->Fit(cauchy1,"M+") ;
    
    
    cout << "Chi^2:" << cauchy1->GetChisquare() << ", number of DoF: " << cauchy1->GetNDF() << " (Probability: " << cauchy1->GetProb() << ")." << endl;
    cout << "--------------------------------------------------------------------------------------------------------" << endl;
    

    
    
/*
    
    
    // --------------------- Grafico n(λ) sodio ------------------------------ //
    TCanvas *cn_lambdas = new TCanvas("n_lambdas","n(l) sodio",200,10,600,400);
    cn_lambdas->SetFillColor(0);
    cn_lambdas->cd();
    TGraphErrors *gn_lambdas = new TGraphErrors(nmisure2,lambda_sodio,n_sodio,slambda_sodio,sn_sodio);
    gn_lambdas->SetMarkerSize(0.6);
    gn_lambdas->SetMarkerStyle(21);
    gn_lambdas->SetTitle("n(l) sodio");
    gn_lambdas->GetXaxis()->SetTitle("l[nm]");
    gn_lambdas->GetYaxis()->SetTitle("n");
    gn_lambdas->Draw("AP");
    // ----------------------------------------------------------------- //
    
    
    
    
    // -------- Fit con funzione di cauchy a sodio --- / /
    
    cout<<"\n\n------------Fit con equazione di Cauchy (sodio)-----------\n\n" ;
    
    
    gn_lambdas->Fit(cauchy) ;
    
    cout << "Chi^2:" << cauchy->GetChisquare() << ", number of DoF: " << cauchy->GetNDF() << " (Probability: " << cauchy->GetProb() << ")." << endl;
    cout << "--------------------------------------------------------------------------------------------------------" << endl; */

    
}
