//
//  esperienza7parte3.c
//  
//
//  Created by Simone on 23/03/16.
//
//

#include "esperienza7parte3.h"

#include <iostream>
#include <TGraphErrors.h>     // ci serve per istanziare grafici
#include <TAxis.h>            // ci serve per manipolare gli assi dei grafici
#include <TCanvas.h>          // ci serve per disegnare i grafici
#include <TF1.h>              // ci serve per scrivere le funzioni con cui fittare i grafici
#include "TVirtualFitter.h"   // ci serve come supporto per i fit
#include <iomanip>            // ci serve per manipolare l'output a video
#include <TMultiGraph.h>      // per unire i grafici

using namespace std;

void esperienza7parte3()

{
    
    
    // Dati grafico Bf(Ic) dove Ic è la i definita precedentemente
    
    //tolgo primo dato per problemi con fit (0.00,| 0.23,|0.23,|0.00,|0.00,|0.00)
    
    float Bf1[] = {160, 180, 180, 200, 200, 200, 200, 200, 200, 220, 220, 220, 240, 240, 240, 240, 240, 240, 250, 260, 260, 260, 260, 260};
    
    float Bf2[] = { 240, 250, 250, 260, 270, 270, 280 ,290, 290, 300, 310};

    float Bf3[] = { 230, 240, 250, 250, 260, 270, 270, 280, 290, 290, 310, 320, 330};
    
    float Bf4[] = {170, 220, 220 , 230, 240, 240, 250, 260, 270, 280, 290, 300};
    
    float Bf5[]={ 220, 230, 240, 250, 260, 260, 270, 280, 290, 300, 300};
    
    float Bf6[]={100, 230, 250, 280, 300};
    
    //tolgo primo dato per problemi con fit (0.02,| 0.01,| 0.01,|0.01,|0.00,|0.00,)
    
    float sBf1[] = {25.61, 26.91, 26.91, 28.28, 28.28, 28.28, 28.28, 28.28, 28.28, 29.73, 29.73, 29.73, 31.24, 31.24, 31.24, 31.24, 31.24, 31.24, 32.02, 32.80, 32.80, 32.80, 32.80, 32.80};
    
    float sBf2[]={ 15.24, 15.24 ,15.24, 15.62, 15.81, 16.01, 16.40, 16.60, 16.80, 17.20, 17.61, 17.61, 18.03, 18.45};
    
    float sBf3[]={10.24, 10.41, 10.59, 10.67, 10.85, 11.11, 11.29, 11.47, 11.65, 11.83, 12.20, 12.48, 12.77};
    
    float sBf4[]={6.56, 7.34, 7.43, 7.53  ,7.71, 7.81, 8.00, 8.20, 8.40, 8.60, 8.81, 9.01};
    
    float sBf5[]={4.98, 6.01, 6.13, 6.25, 6.37, 6.50, 6.62, 6.75, 6.88, 7.01 , 7.14, 7.28};
    
    float sBf6[]={2.80, 3.81, 4.00, 4.25, 4.51};
    
    
    //----
    
    //tolgo primo dato per problemi con fit (0| 0,| 35,|0,|0,|0,)
    
    float i1[] = { 8, 9, 9, 10, 10, 10, 10, 10, 10, 11, 11, 11, 12, 12, 12, 12, 12, 12, 12.5, 13, 13 ,13, 13, 13};
    
    
    
    
    float i2[] = { 23, 24, 24.5, 25, 26, 26.5, 27, 28, 29, 29, 30, 31};
    
    //
    
    float i3[] = { 35, 36, 37, 37.5, 38.5, 40, 41, 42, 43, 44, 46, 47.5, 49};
    
    
    //
    
    
    float i4[] = {34 , 43, 44, 45, 47 , 48 ,50, 52, 54, 56, 58, 60};
    
    //
    
    float i5[] = { 56, 58, 60, 62, 64, 66, 68, 70, 72, 74, 76};
    
    //
    
    float i6[] = {40, 92, 100, 110, 120};
    
    //----
    
    ////tolgo primo dato per problemi con fit (1 per tutte)
    
    
    float si1[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,1};
    
    float si2[] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    
    float si3[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    
    float si4[] = {1 , 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    
    float si5[] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    
    float si6[] = {1, 1, 1, 1, 1};
    
    // numero misure
    
    int nmisure1 = 24;
    int nmisure2 = 11;
    int nmisure3 = 13 ;
    int nmisure4 = 12 ;
    int nmisure5 = 11 ;
    int nmisure6 = 5;
    
    
    //--------- Grafici -------//
    
    
    // Graph Bf1(i1)
    
    
    TGraphErrors *gBf1i1 = new TGraphErrors(nmisure1,i1,Bf1,si1,sBf1);
    
    gBf1i1->SetMarkerSize(0.6);
    gBf1i1->SetMarkerStyle(21);
    gBf1i1->SetMarkerColor(5);
    
    // Graph Bf2(i2)
    
    
    TGraphErrors *gBf2i2 = new TGraphErrors(nmisure2,i2,Bf2,si2,sBf2);
    
    gBf2i2->SetMarkerSize(0.6);
    gBf2i2->SetMarkerStyle(21);
    gBf2i2->SetMarkerColor(6);
    
    // Graph Bf3(i3)
    
    
    TGraphErrors *gBf3i3 = new TGraphErrors(nmisure3,i3,Bf3,si3,sBf3);
    
    gBf3i3->SetMarkerSize(0.6);
    gBf3i3->SetMarkerStyle(21);
    gBf3i3->SetMarkerColor(7);
    
    
    // Graph Bf4(i4)
    
    
    TGraphErrors *gBf4i4 = new TGraphErrors(nmisure4,i4,Bf4,si4,sBf4);
    
    gBf4i4->SetMarkerSize(0.6);
    gBf4i4->SetMarkerStyle(21);
    gBf4i4->SetMarkerColor(8);
    
    
    // Graph Bf5(i5)
    
    
    TGraphErrors *gBf5i5 = new TGraphErrors(nmisure5,i5,Bf5,si5,sBf5);
    
    gBf5i5->SetMarkerSize(0.6);
    gBf5i5->SetMarkerStyle(21);
    gBf5i5->SetMarkerColor(9);
    
    // Graph Bf6(i6)
    
    
    TGraphErrors *gBf6i6 = new TGraphErrors(nmisure6,i6,Bf6,si6,sBf6);
    
    gBf6i6->SetMarkerSize(0.6);
    gBf6i6->SetMarkerStyle(21);

    
    
    // Unione grafici e disegno
    
    TMultiGraph *mg = new TMultiGraph();
    mg->Add(gBf1i1);
    mg->Add(gBf2i2);
    mg->Add(gBf3i3);
    mg->Add(gBf4i4);
    mg->Add(gBf5i5);
    mg->Add(gBf6i6);
    
   // mg->GetXaxis()->SetTitle("Ic [mA]");
     //   mg->GetYaxis()->SetTitle(" Bf ");
    
    
    
    mg->Draw("AP");
    
    
    //// -_- - - - - - --  - -   Fits - - - - -  - -  - --- -  //
    
    // Togliere primi due punti per ogni curva in modo da ottenere delle rette e fare linear fit
    //Fit I1V1
    
    TF1 *linear = new TF1("linear", "[1] * x + [0]");
    // Chiedi al grafico di effettuare il fit con la funzione "linear" definita sopra.
    gBf1i1->Fit(linear);
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
    gBf2i2->Fit(linear2);
    linear2->SetLineColor(4);
    // Stampa a video il valore del coefficiente angolare e dell'incertezza su di esso
    cout << "Angular coefficient: " << linear2->GetParameter(1) << " +- " << linear2->GetParError(1) << endl;
    // Stampa a video i risultati del test di chi2 sulla bontà del fit
    cout << "Chi^2:" << linear2->GetChisquare() << ", number of DoF: " << linear2->GetNDF() << " (Probability: " << linear2->GetProb() << ")." << endl;
    cout << "--------------------------------------------------------------------------------------------------------" << endl;
    
    
    //Fit I3V3
    
    TF1 *linear3 = new TF1("linear3", "[1] * x + [0]");
    // Chiedi al grafico di effettuare il fit con la funzione "linear" definita sopra.
    gBf3i3->Fit(linear3);
    // Stampa a video il valore del coefficiente angolare e dell'incertezza su di esso
    cout << "Angular coefficient: " << linear3->GetParameter(1) << " +- " << linear3->GetParError(1) << endl;
    // Stampa a video i risultati del test di chi2 sulla bontà del fit
    cout << "Chi^2:" << linear3->GetChisquare() << ", number of DoF: " << linear3->GetNDF() << " (Probability: " << linear3->GetProb() << ")." << endl;
    cout << "--------------------------------------------------------------------------------------------------------" << endl;
    
    
    //Fit I4V4
    
    TF1 *linear4 = new TF1("linear4", "[1] * x + [0]");
    // Chiedi al grafico di effettuare il fit con la funzione "linear" definita sopra.
    gBf4i4->Fit(linear4);
    // Stampa a video il valore del coefficiente angolare e dell'incertezza su di esso
    cout << "Angular coefficient: " << linear4->GetParameter(1) << " +- " << linear4->GetParError(1) << endl;
    // Stampa a video i risultati del test di chi2 sulla bontà del fit
    cout << "Chi^2:" << linear4->GetChisquare() << ", number of DoF: " << linear4->GetNDF() << " (Probability: " << linear4->GetProb() << ")." << endl;
    cout << "--------------------------------------------------------------------------------------------------------" << endl;
    
    
    //Fit I5V5
    
    TF1 *linear5 = new TF1("linear5", "[1] * x + [0]");
    // Chiedi al grafico di effettuare il fit con la funzione "linear" definita sopra.
    gBf5i5->Fit(linear5);
    // Stampa a video il valore del coefficiente angolare e dell'incertezza su di esso
    cout << "Angular coefficient: " << linear5->GetParameter(1) << " +- " << linear5->GetParError(1) << endl;
    // Stampa a video i risultati del test di chi2 sulla bontà del fit
    cout << "Chi^2:" << linear5->GetChisquare() << ", number of DoF: " << linear5->GetNDF() << " (Probability: " << linear5->GetProb() << ")." << endl;
    cout << "--------------------------------------------------------------------------------------------------------" << endl;
    
    
    //Fit I6V6
    
    TF1 *linear6 = new TF1("linear6", "[1] * x + [0]");
    // Chiedi al grafico di effettuare il fit con la funzione "linear" definita sopra.
    gBf6i6->Fit(linear6);
    // Stampa a video il valore del coefficiente angolare e dell'incertezza su di esso
    cout << "Angular coefficient: " << linear6->GetParameter(1) << " +- " << linear6->GetParError(1) << endl;
    // Stampa a video i risultati del test di chi2 sulla bontà del fit
    cout << "Chi^2:" << linear6->GetChisquare() << ", number of DoF: " << linear6->GetNDF() << " (Probability: " << linear6->GetProb() << ")." << endl;
    cout << "--------------------------------------------------------------------------------------------------------" << endl;
    
    
    
    


    
}


    


    

    

    


