//
//  esperienza7parte2.c
//  
//
//  Created by Simone on 23/03/16.
//
//In questo file è presente il grafico Vbe(Ib) dell' esperienza 7 (Transistor BJT)

#include "esperienza7parte2.h"
#include <iostream>
#include <TGraphErrors.h>     // ci serve per istanziare grafici
#include <TAxis.h>            // ci serve per manipolare gli assi dei grafici
#include <TCanvas.h>          // ci serve per disegnare i grafici
#include <TF1.h>              // ci serve per scrivere le funzioni con cui fittare i grafici
#include "TVirtualFitter.h"   // ci serve come supporto per i fit
#include <iomanip>            // ci serve per manipolare l'output a video
#include <TMultiGraph.h>

using namespace std;

void esperienza7parte2()

{
    // Dati parte 2
    
    float Ib1[] = {50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50};
    
    float Ib2[] = {100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100};
    
    float Ib3[] = {150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150};
    
    float Ib4[] = {200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200};
    
    float Ib5[] = {250, 250, 250 ,250, 250, 250, 250, 250, 250, 250, 250, 250, 250};
    
    float Ib6[] = {400, 400, 400, 400, 400, 400};
    
    //----
    
    float sIb1[] = {5,  5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5};
    
    float sIb2[] = {5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5};
    
    float sIb3[] = {5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5};
    
    float sIb4[] = {5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5};
    
    float sIb5[] = {5, 5, 5, 5 , 5, 5, 5, 5, 5, 5, 5, 5, 5};
    
    float sIb6[]= {5, 5, 5, 5 ,5, 5};
    
    //---
    
    float Vbe1[] = {0.440, 0.537, 0.540, 0.539, 0.541, 0.541, 0.541, 0.541, 0.541, 0.541, 0.543, 0.543, 0.542, 0.542, 0.542, 0.542, 0.542, 0.541, 0.541, 0.541, 0.540, 0.540, 0.540, 0.540, 0.540};
    
    float Vbe2[] = {0.448 ,0.563, 0.564, 0.565, 0.565, 0.565, 0.565, 0.565, 0.565, 0.564 ,0.564, 0.563, 0.562, 0.561, 0.560};
    
    float Vbe3[] = { 0.583, 0.580, 0.582, 0.582, 0.582, 0.582, 0.582, 0.581, 0.580, 0.579, 0.578, 0.574, 0.572, 0.570};
    
    float Vbe4[] = {0.462, 0.586, 0.593, 0.593, 0.593, 0.593, 0.592, 0.591, 0.587, 0.585, 0.582, 0.580, 0.578};
    
    float Vbe5[] = {0.468, 0.581, 0.598, 0.599, 0.598, 0.597, 0.596, 0.595, 0.593, 0.590, 0.589, 0.586, 0.583};
    
    float Vbe6[] = {0.465, 0.570, 0.609, 0.611, 0.606, 0.601};
    
    //----
    
    float sVbe1[] = {0.0001, 0.0001, 0.0001, 0.0001, 0.0001, 0.0001, 0.0001, 0.0001, 0.0001, 0.0001, 0.0001, 0.0001, 0.0001, 0.0001, 0.0001, 0.0001, 0.0001, 0.0001, 0.0001, 0.0001, 0.0001, 0.0001, 0.0001, 0.0001, 0.0001};
    
    float sVbe2[] = {0.0001, 0.0001, 0.0001, 0.0001, 0.0001, 0.0001, 0.0001, 0.0001, 0.0001, 0.0001, 0.0001, 0.0001, 0.0001, 0.0001, 0.0001};
    
    float sVbe3[] = {0.0001, 0.0001, 0.0001, 0.0001, 0.0001, 0.0001, 0.0001, 0.0001, 0.0001, 0.0001, 0.0001, 0.0001, 0.0001};
    
    float sVbe4[] = {0.0001, 0.0001, 0.0001, 0.0001, 0.0001, 0.0001, 0.0001, 0.0001, 0.0001, 0.0001, 0.0001, 0.0001, 0.0001};
    
    float sVbe5[] = {0.0001, 0.0001, 0.0001, 0.0001, 0.0001, 0.0001, 0.0001, 0.0001, 0.0001, 0.0001, 0.0001, 0.0001, 0.0001};
    
    float sVbe6[] = {0.0001, 0.0001, 0.0001, 0.0001, 0.0001, 0.0001};
    
    
    //numero misure
    
    int nmisure1 = 23;
    int nmisure2 = 13;
    int nmisure3 = 12 ;
    int nmisure4 = 11 ;
    int nmisure5 = 11 ;
    int nmisure6 = 4 ;

    
    
    //  - -- - --  - - Grafici 2 parte ------//
    
    // - - - - --  - - -Grafico Vbe1(Ib1) --- - - - -- - -//
    
    // Per brevità non riporto i significati dei comandi in quanto uguali a quelli del file esperienza7.c //
    
    
    //TCanvas *cVbe1Ib1 = new TCanvas("cVbe1Ib1","Vbe1(Ib1)",200,10,600,400);
    
    //cVbe1Ib1->SetFillColor(0);
    
    // cVbe1Ib1->cd();
    
    TGraphErrors *gVbe1Ib1 = new TGraphErrors(nmisure1,Ib1,Vbe1,sIb1,sVbe1);
    
    gVbe1Ib1->SetMarkerSize(0.6);
    gVbe1Ib1->SetMarkerStyle(21);
    
    //gVbe1Ib1->SetTitle("Vbe1(Ib1)");
    
    // gVbe1Ib1->GetXaxis()->SetTitle("Ib1 [mA]");
    //gVbe1Ib1->GetYaxis()->SetTitle("Vbe1 [mV]");
    
    
    // ----------------------------------------------------------------- //
    
    
    // - - - - --  - - -Grafico Vbe2(Ib2) --- - - - -- - -//
    
    // Per brevità non riporto i significati dei comandi in quanto uguali a quelli del file esperienza7.c //
    
    
    //TCanvas *cVbe2Ib2 = new TCanvas("cVbe2Ib2","Vbe2(Ib2)",200,10,600,400);
    
    //cVbe2Ib2->SetFillColor(0);
    
    //cVbe2Ib2->cd();
    
    TGraphErrors *gVbe2Ib2 = new TGraphErrors(nmisure2,Ib2,Vbe2,sIb2,sVbe2);
    
    gVbe2Ib2->SetMarkerSize(0.6);
    gVbe2Ib2->SetMarkerStyle(21);
    
    //gVbe2Ib2->SetTitle("Vbe2(Ib2)");
    
    //gVbe2Ib2->GetXaxis()->SetTitle("Ib2 [mA]");
    //gVbe2Ib2->GetYaxis()->SetTitle("Vbe2 [mV]");
    
    
    // ----------------------------------------------------------------- //
    
    // - - - - --  - - -Grafico Vbe3(Ib3) --- - - - -- - -//
    
    // Per brevità non riporto i significati dei comandi in quanto uguali a quelli del file esperienza7.c //
    
    
    //TCanvas *cVbe3Ib3 = new TCanvas("cVbe3Ib3","Vbe3(Ib3)",200,10,600,400);
    
    //cVbe3Ib3->SetFillColor(0);
    
    //cVbe3Ib3->cd();
    
    TGraphErrors *gVbe3Ib3 = new TGraphErrors(nmisure3,Ib3,Vbe3,sIb3,sVbe3);
    
    gVbe3Ib3->SetMarkerSize(0.6);
    gVbe3Ib3->SetMarkerStyle(21);
    
    //gVbe3Ib3->SetTitle("Vbe3(Ib3)");
    
    //gVbe3Ib3->GetXaxis()->SetTitle("Ib3 [mA]");
    //gVbe3Ib3->GetYaxis()->SetTitle("Vbe3 [mV]");
    
    
    // ----------------------------------------------------------------- //
    
    // - - - - --  - - -Grafico Vbe4(Ib4) --- - - - -- - -//
    
    // Per brevità non riporto i significati dei comandi in quanto uguali a quelli del file esperienza7.c //
    
    
    //TCanvas *cVbe4Ib4 = new TCanvas("cVbe4Ib4","Vbe4(Ib4)",200,10,600,400);
    
    //cVbe4Ib4->SetFillColor(0);
    
    // cVbe4Ib4->cd();
    
    TGraphErrors *gVbe4Ib4 = new TGraphErrors(nmisure4,Ib4,Vbe4,sIb4,sVbe4);
    
    gVbe4Ib4->SetMarkerSize(0.6);
    gVbe4Ib4->SetMarkerStyle(21);
    
    //gVbe4Ib4->SetTitle("Vbe4(Ib4)");
    
    //gVbe4Ib4->GetXaxis()->SetTitle("Ib4 [mA]");
    //gVbe4Ib4->GetYaxis()->SetTitle("Vbe4 [mV]");
    
    
    // ----------------------------------------------------------------- //
    
    
    
    // - - - - --  - - -Grafico Vbe5(Ib5) --- - - - -- - -//
    
    // Per brevità non riporto i significati dei comandi in quanto uguali a quelli del file esperienza7.c //
    
    
    //TCanvas *cVbe5Ib5 = new TCanvas("cVbe5Ib5","Vbe5(Ib5)",200,10,600,400);
    
    // cVbe5Ib5->SetFillColor(0);
    
    //cVbe5Ib5->cd();
    
    TGraphErrors *gVbe5Ib5 = new TGraphErrors(nmisure5,Ib5,Vbe5,sIb5,sVbe5);
    
    gVbe5Ib5->SetMarkerSize(0.6);
    gVbe5Ib5->SetMarkerStyle(21);
    
    //gVbe5Ib5->SetTitle("Vbe5(Ib5)");
    
    //gVbe5Ib5->GetXaxis()->SetTitle("Ib5 [mA]");
    // gVbe5Ib5->GetYaxis()->SetTitle("Vbe5 [mV]");
    
    
    // ----------------------------------------------------------------- //
    
    
    
    // - - - - --  - - -Grafico Vbe6(Ib6) --- - - - -- - -//
    
    // Per brevità non riporto i significati dei comandi in quanto uguali a quelli del file esperienza7.c //
    
    
    //TCanvas *cVbe6Ib6 = new TCanvas("cVbe6Ib6","Vbe6(Ib6)",200,10,600,400);
    
    //cVbe6Ib6->SetFillColor(0);
    
    //cVbe6Ib6->cd();
    
    TGraphErrors *gVbe6Ib6 = new TGraphErrors(nmisure6,Ib6,Vbe6,sIb6,sVbe6);
    
    gVbe6Ib6->SetMarkerSize(0.6);
    gVbe6Ib6->SetMarkerStyle(21);
    
    //gVbe6Ib6->SetTitle("Vbe6(Ib6)");
    
    //gVbe6Ib6->GetXaxis()->SetTitle("Ib6 [mA]");
    //gVbe6Ib6->GetYaxis()->SetTitle("Vbe6 [mV]");
    
    
    // ----------------------------------------------------------------- //
    
    
    TMultiGraph *mg = new TMultiGraph();
    mg->Add(gVbe1Ib1);
    mg->Add(gVbe2Ib2);
    mg->Add(gVbe3Ib3);
    mg->Add(gVbe4Ib4);
    mg->Add(gVbe5Ib5);
    mg->Add(gVbe6Ib6);
    
    
    mg->Draw("AP");
    
}

    

    
