//
//  esperienza7parte1.c
//  
//
//  Created by Simone on 21/03/16.
//
//

#include "esperienza7parte1.h"

#include <iostream>
#include <TGraphErrors.h>     // ci serve per istanziare grafici
#include <TAxis.h>            // ci serve per manipolare gli assi dei grafici
#include <TCanvas.h>          // ci serve per disegnare i grafici
#include <TF1.h>              // ci serve per scrivere le funzioni con cui fittare i grafici
#include "TVirtualFitter.h"   // ci serve come supporto per i fit
#include <iomanip>            // ci serve per manipolare l'output a video
#include <TMultiGraph.h>      // per unire i grafici


using namespace std;

void esperienza7parte1()
{
    
    //------------- Dati ----------------//
    
    // I dati sono gli stessi del file esperienza7.c , unica differenza è aver definito diverse variabili per ogni Ib inserita, in questo modo otteniamo ogni singola curva invece che tutte insieme//
    
    //0.014, 0.5058 primi due valori tolti per avere Linear fit
    
    float V1[] ={ 1.0007, 1.498, 2.025, 2.509, 3.029, 3.516, 4.025, 4.507, 5.005, 5.517, 6.02, 6.506, 7.003, 7.505, 8.006, 8.505, 9.008, 9.499, 10.02, 10.51, 11, 11.52, 12.04};
    
    //0.006, 0.5125
    
    float V2[] = { 1.005, 1.522, 2.01, 2.999, 4.02, 5.012, 6.005, 7.001, 8.03, 9.019, 10.05, 11.04, 12.02};
    
    //0.315, 0.273,
    
    float V3[] = { 0.6887, 1.271, 1.73, 2.706, 4.068, 5.11, 5.989, 6.656, 7.686, 8.578, 9.723, 10.7};
    
    //0.001, 0.1713,
    
    float V4[] = { 0.6437, 1.131, 1.616, 3.026, 3.787, 5.11, 6.959, 8.103, 8.976, 10.03, 11.3};
    
    //0.0057, 0.1522,
    
    float V5[] = { 0.7213, 2.021, 3.274, 4.604, 5.479, 6.74, 7.96, 8.843, 9.716, 10.49, 11.35};
    
    //0.0056, 0.124,
    
    float V6[] = { 0.2954, 2.197, 5.754, 9.04};
    
    //---
    
    // 0.001, 0.001 uguale per tutti gli altri
    float sV1[] = { 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001 ,0.001, 0.001, 0.001, 0.001 ,0.001, 0.001, 0.001, 0.001, 0.001, 0.01, 0.01, 0.01, 0.01, 0.01};
    
    float sV2[] = { 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.01, 0.01, 0.01};
    
    float sV3[] = {  0.0001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.01};
    
    float sV4[] = {  0.0001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.01, 0.01};
    
    float sV5[] = { 0.0001 ,0.001, 0.001, 0.001 ,0.001, 0.001,  0.001, 0.001, 0.001, 0.01, 0.01};
    
    float sV6[] = {0.0001, 0.001, 0.001, 0.001};
    
    //----
    
    //0 , 8,
    
    float i1[] = { 9, 9, 10, 10, 10, 10, 10, 10, 11, 11, 11, 12, 12, 12, 12, 12, 12, 12.5, 13, 13 ,13, 13, 13};
    
    
    // 0, 23,
    
    float i2[] = { 23, 23, 24, 24.5, 25, 26, 26.5, 27, 28, 29, 29, 30, 31};
    
    //35, 35,
    
    float i3[] = { 36, 37, 37.5, 38.5, 40, 41, 42, 43, 44, 46, 47.5, 49};
    
    
    // 0, 34,
    
    
    float i4[] = {43, 44, 45, 47 , 48 ,50, 52, 54, 56, 58, 60};
    
    //0, 37,
    
    float i5[] = { 56, 58, 60, 62, 64, 66, 68, 70, 72, 74, 76};
    
    //0, 40,
    
    float i6[] = {92, 100, 110, 120};
    
    //----
    
    //1, 1
    
    
    float si1[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,1};
    
    float si2[] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    
    float si3[] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    
    float si4[] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    
    float si5[] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    
    float si6[] = { 1, 1, 1, 1};
    
    //numero misure
    
    int nmisure1 = 23;
    int nmisure2 = 13;
    int nmisure3 = 12 ;
    int nmisure4 = 11 ;
    int nmisure5 = 11 ;
    int nmisure6 = 4 ;
    
    
    
    
    
    // --------------------- Grafici ----------------//
    
    // - - - - --  - - -Grafico i1(V1) --- - - - -- - -//
    
    // Per brevità non riporto i significati dei comandi in quanto uguali a quelli del file esperienza7.c //
    
    
   // TCanvas *ci1V1 = new TCanvas("ci1V1","i1(v1)",200,10,600,400);
    
    //ci1V1->SetFillColor(0);
    
    //ci1V1->cd();
    
    TGraphErrors *gi1V1 = new TGraphErrors(nmisure1,V1,i1,sV1,si1);
    
    gi1V1->SetMarkerSize(0.6);
    gi1V1->SetMarkerStyle(21);

    //gi1V1->SetTitle("i(V)");

    //gi1V1->GetXaxis()->SetTitle("V [V]");
   // gi1V1->GetYaxis()->SetTitle("i [mA]");
   
    //gi1V1->Draw("AP");
    // ----------------------------------------------------------------- //
    
    
    
    
    // - - - - --  - - -Grafico i2(V2) --- - - - -- - -//
    
    // Per brevità non riporto i significati dei comandi in quanto uguali a quelli del file esperienza7.c //
    
    
    //TCanvas *ci2V2 = new TCanvas("ci2V2","i2(v2)",200,10,600,400);
    
    //ci2V2->SetFillColor(0);
    
    //ci2V2->cd();
    
    TGraphErrors *gi2V2 = new TGraphErrors(nmisure2,V2,i2,sV2,si2);
    
    gi2V2->SetMarkerSize(0.6);
    gi2V2->SetMarkerStyle(21);
    gi2V2->SetMarkerColor(5);
    //gi2V2->SetTitle("i2(V2)");
    
    //gi2V2->GetXaxis()->SetTitle("V2 [V]");
   // gi2V2->GetYaxis()->SetTitle("i2 [mA]");
    

    // ----------------------------------------------------------------- //
    
    
    
    
    // - - - - --  - - -Grafico i3(V3) --- - - - -- - -//
    
    // Per brevità non riporto i significati dei comandi in quanto uguali a quelli del file esperienza7.c //
    
    
    //TCanvas *ci3V3 = new TCanvas("ci3V3","i3(v3)",200,10,600,400);
    
   // ci3V3->SetFillColor(0);
    
    //ci3V3->cd();
    
    TGraphErrors *gi3V3 = new TGraphErrors(nmisure3,V3,i3,sV3,si3);
    
    gi3V3->SetMarkerSize(0.6);
    gi3V3->SetMarkerStyle(20);
     gi3V3->SetMarkerColor(2);
    //gi3V3->SetTitle("i3(V3)");
    
    //gi3V3->GetXaxis()->SetTitle("V3 [V]");
    //gi3V3->GetYaxis()->SetTitle("i3 [mA]");
    

    // ----------------------------------------------------------------- //
    
    
    
    
    // - - - - --  - - -Grafico i4(V4) --- - - - -- - -//
    
    // Per brevità non riporto i significati dei comandi in quanto uguali a quelli del file esperienza7.c //
    
    
    //TCanvas *ci4V4 = new TCanvas("ci4V4","i4(v4)",200,10,600,400);
    
  //  ci4V4->SetFillColor(0);
    
    //ci4V4->cd();
    
    TGraphErrors *gi4V4 = new TGraphErrors(nmisure4,V4,i4,sV4,si4);
    
    gi4V4->SetMarkerSize(0.6);
    gi4V4->SetMarkerStyle(21);
     gi4V4->SetMarkerColor(4);
   // gi4V4->SetTitle("i4(V4)");
    
   // gi4V4->GetXaxis()->SetTitle("V4 [V]");
   // gi4V4->GetYaxis()->SetTitle("i4 [mA]");
    

    // ----------------------------------------------------------------- //
    
    
    
    
    // - - - - --  - - -Grafico i5(V5) --- - - - -- - -//
    
    // Per brevità non riporto i significati dei comandi in quanto uguali a quelli del file esperienza7.c //
    
    
   // TCanvas *ci5V5 = new TCanvas("ci5V5","i5(v5)",200,10,600,400);
    
   // ci5V5->SetFillColor(0);
    
   // ci5V5->cd();
    
    TGraphErrors *gi5V5 = new TGraphErrors(nmisure5,V5,i5,sV5,si5);
    
    gi5V5->SetMarkerSize(0.6);
    gi5V5->SetMarkerStyle(21);
     gi5V5->SetMarkerColor(6);
    
   // gi5V5->SetTitle("i5(V5)");
    
    //gi5V5->GetXaxis()->SetTitle("V5 [V]");
    //gi5V5->GetYaxis()->SetTitle("i5 [mA]");
    

    // ----------------------------------------------------------------- //
    
    
    
    
    // - - - - --  - - -Grafico i6(V6) --- - - - -- - -//
    
    // Per brevità non riporto i significati dei comandi in quanto uguali a quelli del file esperienza7.c //
    
    
   // TCanvas *ci6V6 = new TCanvas("ci6V6","i6(v6)",200,10,600,400);
    
    //ci6V6->SetFillColor(0);
    
   // ci6V6->cd();
    
    TGraphErrors *gi6V6 = new TGraphErrors(nmisure6,V6,i6,sV6,si6);
    
    gi6V6->SetMarkerSize(0.6);
    gi6V6->SetMarkerStyle(21);
     gi6V6->SetMarkerColor(7);
    
    //gi6V6->SetTitle("i6(V6)");
    
    //gi6V6->GetXaxis()->SetTitle("V6 [V]");
    //gi6V6->GetYaxis()->SetTitle("i6 [mA]");
    
    //gi6V6->Draw("same");
    
    
    
    //---- - -- - - - -  - Unire Grafici
    
    TMultiGraph *mg = new TMultiGraph();
    mg->Add(gi1V1);
     mg->Add(gi2V2);
     mg->Add(gi3V3);
     mg->Add(gi4V4);
     mg->Add(gi5V5);
     mg->Add(gi6V6);
    
    
    mg->Draw("AP");
    
    
    
    
    
    
//// -_- - - - - - --  - -   Fits - - - - -  - -  - --- -  //
    
    // Togliere primi due punti per ogni curva in modo da ottenere delle rette e fare linear fit
    //Fit I1V1
    
    TF1 *linear = new TF1("linear", "[1] * x + [0]");
    // Chiedi al grafico di effettuare il fit con la funzione "linear" definita sopra.
     gi1V1->Fit(linear);
    // Stampa a video il valore del coefficiente angolare e dell'incertezza su di esso
    cout << "Angular coefficient: " << linear->GetParameter(1) << " +- " << linear->GetParError(1) << endl;
    // Stampa a video i risultati del test di chi2 sulla bontà del fit
    cout << "Chi^2:" << linear->GetChisquare() << ", number of DoF: " << linear->GetNDF() << " (Probability: " << linear->GetProb() << ")." << endl;
    cout << "--------------------------------------------------------------------------------------------------------" << endl;
    
    
    
    //- . --  . . - . -  .  Ipotesi esponenziale Possibile confronto con linear fit , ma linear risulta migliore .
    
    
    //cout << "\n\n --- II) Ipotesi esponenziale --- \n" <<endl;
    // funzione più complessa, qui voglio trovare l'esponente del polinomio che minimizza (lo scarto etc... de) la funzione
    //TF1 *poli = new TF1("poli","([0]*(pow((2.7182818284590),(x/[1])) - 1))");
    // Inizializzo il valore del parametro 0 (provate a commentare la linea seguente e vedete che cosa succede...)
   // poli->SetParameter(0, 1.3*pow(10, 6));
    //poli->SetParameter(1, 1.01*pow(10,6));
    // cambio colore alla linea della funzione in modo da distinguerla da pol4 quando la disegno
    //poli->SetLineColor(6);
    // + significa che voglio aggiungere la funzione poli alla lista delle funzioni già disegnate sul canvas, in questo caso pol4
   // gi1V1->Fit(poli,"M+");
   // cout << "Chi^2:" << poli->GetChisquare() << ", number of DoF: " << poli->GetNDF() << " (Probability: " << poli->GetProb() << ")." << endl;
   // cout << "--------------------------------------------------------------------------------------------------------" << endl;

    //Fit I2V2
    
    TF1 *linear2 = new TF1("linear2", "[1] * x + [0]");
    // Chiedi al grafico di effettuare il fit con la funzione "linear" definita sopra.
    gi2V2->Fit(linear2);
    linear2->SetLineColor(4);
    // Stampa a video il valore del coefficiente angolare e dell'incertezza su di esso
    cout << "Angular coefficient: " << linear2->GetParameter(1) << " +- " << linear2->GetParError(1) << endl;
    // Stampa a video i risultati del test di chi2 sulla bontà del fit
    cout << "Chi^2:" << linear2->GetChisquare() << ", number of DoF: " << linear2->GetNDF() << " (Probability: " << linear2->GetProb() << ")." << endl;
    cout << "--------------------------------------------------------------------------------------------------------" << endl;
    
    
    //Fit I3V3
    
    TF1 *linear3 = new TF1("linear3", "[1] * x + [0]");
    // Chiedi al grafico di effettuare il fit con la funzione "linear" definita sopra.
    gi3V3->Fit(linear3);
    // Stampa a video il valore del coefficiente angolare e dell'incertezza su di esso
    cout << "Angular coefficient: " << linear3->GetParameter(1) << " +- " << linear3->GetParError(1) << endl;
    // Stampa a video i risultati del test di chi2 sulla bontà del fit
    cout << "Chi^2:" << linear3->GetChisquare() << ", number of DoF: " << linear3->GetNDF() << " (Probability: " << linear3->GetProb() << ")." << endl;
    cout << "--------------------------------------------------------------------------------------------------------" << endl;

    
    //Fit I4V4
    
    TF1 *linear4 = new TF1("linear4", "[1] * x + [0]");
    // Chiedi al grafico di effettuare il fit con la funzione "linear" definita sopra.
    gi4V4->Fit(linear4);
    // Stampa a video il valore del coefficiente angolare e dell'incertezza su di esso
    cout << "Angular coefficient: " << linear4->GetParameter(1) << " +- " << linear4->GetParError(1) << endl;
    // Stampa a video i risultati del test di chi2 sulla bontà del fit
    cout << "Chi^2:" << linear4->GetChisquare() << ", number of DoF: " << linear4->GetNDF() << " (Probability: " << linear4->GetProb() << ")." << endl;
    cout << "--------------------------------------------------------------------------------------------------------" << endl;
    
    
    //Fit I5V5
    
    TF1 *linear5 = new TF1("linear5", "[1] * x + [0]");
    // Chiedi al grafico di effettuare il fit con la funzione "linear" definita sopra.
    gi5V5->Fit(linear5);
    // Stampa a video il valore del coefficiente angolare e dell'incertezza su di esso
    cout << "Angular coefficient: " << linear5->GetParameter(1) << " +- " << linear5->GetParError(1) << endl;
    // Stampa a video i risultati del test di chi2 sulla bontà del fit
    cout << "Chi^2:" << linear5->GetChisquare() << ", number of DoF: " << linear5->GetNDF() << " (Probability: " << linear5->GetProb() << ")." << endl;
    cout << "--------------------------------------------------------------------------------------------------------" << endl;
    
    
    //Fit I6V6
    
    TF1 *linear6 = new TF1("linear6", "[1] * x + [0]");
    // Chiedi al grafico di effettuare il fit con la funzione "linear" definita sopra.
    gi6V6->Fit(linear6);
    // Stampa a video il valore del coefficiente angolare e dell'incertezza su di esso
    cout << "Angular coefficient: " << linear6->GetParameter(1) << " +- " << linear6->GetParError(1) << endl;
    // Stampa a video i risultati del test di chi2 sulla bontà del fit
    cout << "Chi^2:" << linear6->GetChisquare() << ", number of DoF: " << linear6->GetNDF() << " (Probability: " << linear6->GetProb() << ")." << endl;
    cout << "--------------------------------------------------------------------------------------------------------" << endl;



    
    
    
    

}
    
    

