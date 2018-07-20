//
//  esperienza6.c
//  Analisi dati Diodo Silicio e Led
//
//
//
//

#include "esperienza6.h"
#include <iostream>
#include <TGraphErrors.h>     // ci serve per istanziare grafici
#include <TAxis.h>            // ci serve per manipolare gli assi dei grafici
#include <TCanvas.h>          // ci serve per disegnare i grafici
#include <TF1.h>              // ci serve per scrivere le funzioni con cui fittare i grafici
#include "TVirtualFitter.h"   // ci serve come supporto per i fit
#include <iomanip>            // ci serve per manipolare l'output a video

using namespace std;

void esperienza6()
{
    
    //---------------------------Parte 1 ------------------------//
    
    
    
    // --------------------------- DATI diodo silicio------------------------------- //
    
    // Dati presi in laboratorio: V = tensione, sV = incertezza tensione, i = intensità di corrente, si = incertezza intensità di corrente

    float V[]  = {673.4, 672.6, 670.4, 668.3, 665.7, 663.5, 660.9, 658, 654.4, 649.3 ,644.4, 640.5 ,635.5, 629.9, 622.7, 613.5, 604.3, 589.8, 569.8 ,548.2 ,541 ,533.3 ,528.6 ,524.6, 518.1, 511.5, 502.6, 492.8, 480.9, 466.7, 451.9, 421, 404.7};
    float sV[] = {6.7, 6.7, 6.7, 6.7, 6.7, 6.6, 6.6, 6.6, 6.5, 6.5, 6.4, 6.4, 6.4, 6.3, 6.2, 6.1, 6.0 , 5.9, 5.7, 5.5, 5.4, 5.3, 5.3, 5.2, 5.2, 5.1, 5.0, 4.9, 4.8, 4.6, 4.5, 4.2, 4.0};
    float i[]  = {14, 14, 13, 12, 12, 11, 10, 9, 8.6, 7.8, 7, 6.4, 5.6, 4.8, 4, 3.3, 3.1, 1.8, 1.1, 0.66, 0.56, 0.46, 0.42, 0.38, 0.32, 0.27, 0.22, 0.17, 0.12, 0.08, 0.05, 0.02, 0.01};
    float si[] = {1, 1, 1, 1, 1, 1, 1, 1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01};
    
    // numero misure silicio
    int nmisure = 33;
    
     // --------------------------- DATI LED------------------------------ //
    
   // Dati presi in laboratorio: Vl = tensione led, sVl = incertezza tensione led , il = intensità di corrente led, sil = incertezza intensità di corrente led

    
    float Vl[] = {2.090, 2.078, 2.068, 2.057, 2.046,2.035, 2.019, 2.009, 1.998, 1.985, 1.972, 1.957, 1.945, 1.930, 1.912, 1.893, 1.869, 1.836, 1.829, 1.824, 1.822, 1.801, 1.795, 1.788 ,1.783, 1.775, 1.761, 1.747, 1.706, 1.660, 1.602};
    float sVl[] = {0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02,0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02 };
    float il[] = {13.0, 12.5, 12.0, 11.0, 10.5, 10.0, 9.00, 8.40, 7.60, 6.80, 6.00, 5.20, 4.60, 3.80, 3.20, 2.40, 1.60, 0.90, 0.80 ,0.70, 0.65, 0.45, 0.39, 0.33, 0.29, 0.24, 0.18, 0.13, 0.05, 0.02, 0.005};
    float sil[] = {1, 1, 1, 1, 1, 1, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3 };
    
    //numero misure led
    
    int nledmisure = 31;

    // ---------------------------------------------------------------- //
    
    
    // --------------------- Grafico i(V) Diodo silicio  ------------------------------ //
    // Creo il canvas (la tela) su cui disegnare il grafico. "ciV" è il il suo nome in memoria
    TCanvas *ciV = new TCanvas("ciV","i(v)",200,10,600,400);
    // Mi assicuro che la tela sia bianca (0 corrisponde al bianco, per altri colori vedi https://root.cern.ch/doc/master/classTColor.html)
    ciV->SetFillColor(0);
    // Mi assicuro che disegni su questa tela e non su un altra. Ciò è particolarmente importante quando ho tanti canvas aperti.
    ciV->cd();
    // Istanzio il grafico. Il costruttore che noi usiamo prende come argomenti:
    // il numero di misure da disegnare, l'array di misure x (=V), l'array di misure y (=i), e gli
    // array delle  rispettive incertezze
    TGraphErrors *giV = new TGraphErrors(nmisure,V,i,sV,si);
    // Nelle due righe successive disegno i punti del grafico con lo stile che più mi piace.
    // Vedi anche https://root.cern.ch/doc/master/classTAttMarker.html
    giV->SetMarkerSize(0.6);
    giV->SetMarkerStyle(21);
    // Facile, titolo del grafico
    giV->SetTitle("i(V)");
    // Titoli degli assi
    giV->GetXaxis()->SetTitle("V [mV]");
    giV->GetYaxis()->SetTitle("i [mA]");
    // Do istruzioni al grafico di disegnarsi sul canvas che ho selezionato preventivamente con cd()
    // Esistono diverse opzioni di disegno, vedi anche https://root.cern.ch/doc/master/classTGraphPainter.html
    // "AP" è molto semplice, gli stiamo chiedendo di disegnare gli assi (A) e i punti (P)
    giV->Draw("AP");
    // ----------------------------------------------------------------- //

    
   
    
    // --------------------- Grafico il(Vl) LED  ------------------------------ //
// Creo il canvas (la tela) su cui disegnare il grafico. "cilVl" è il il suo nome in memoria
TCanvas *cilVl = new TCanvas("cilVl","il(vl)",200,10,600,400);
// Mi assicuro che la tela sia bianca (0 corrisponde al bianco, per altri colori vedi https://root.cern.ch/doc/master/classTColor.html)
cilVl->SetFillColor(0);
// Mi assicuro che disegni su questa tela e non su un altra. Ciò è particolarmente importante quando ho tanti canvas aperti.
cilVl->cd();
// Istanzio il grafico. Il costruttore che noi usiamo prende come argomenti:
// il numero di misure da disegnare, l'array di misure x (=V), l'array di misure y (=i), e gli
// array delle  rispettive incertezze
TGraphErrors *gilVl = new TGraphErrors(nledmisure,Vl,il,sVl,sil);
// Nelle due righe successive disegno i punti del grafico con lo stile che più mi piace.
// Vedi anche https://root.cern.ch/doc/master/classTAttMarker.html
gilVl->SetMarkerSize(0.6);
gilVl->SetMarkerStyle(21);
// Facile, titolo del grafico
gilVl->SetTitle("i(V)");
// Titoli degli assi
gilVl->GetXaxis()->SetTitle("V [V]");
gilVl->GetYaxis()->SetTitle("i [mA]");
// Do istruzioni al grafico di disegnarsi sul canvas che ho selezionato preventivamente con cd()
gilVl->Draw("AP");
// ----------------------------------------------------------------- //


//--------------- FIT Dati

// -  - . - - . - - . - - Fit i (V) silicio -- . - - . - - - -  -//

//RICAVARE FUNZIONE PER FIT


cout << "\n\n --- II) Ipotesi esponenziale (teorica) --- \n" <<endl;

TF1 *poli = new TF1("poli","([0]*(pow((2.7182818284590),(x/[1])) + 1))");
// Inizializzo il valore dei parametri 0 , 1
    poli->SetParameter(0, pow(10, -6));
poli->SetParameter(1, 52);
// cambio colore alla linea della funzione in modo da distinguerla da poli quando la disegno
poli->SetLineColor(1);

    
// + significa che voglio aggiungere la funzione poli alla lista delle funzioni già disegnate sul canvas
    
giV->Fit(poli,"M+");
    
    
cout << "Chi^2:" << poli->GetChisquare() << ", number of DoF: " << poli->GetNDF() << " (Probability: " << poli->GetProb() << ")." << endl;
cout << "--------------------------------------------------------------------------------------------------------" << endl;
    
  
    
    // -  - . - - . - - . - - Fit il(Vl) LED -- . - - . - - - -  -//
    
    
    
    
    //Ipotesi migliore
    
    
    cout << "\n\n --- II) Ipotesi esponenziale (teorica con Rint) --- \n" <<endl;
    

   
    TF1 *polil = new TF1("polil","([0]*(pow((2.7182818284590),((x - [1])/[2]))-1))");
    // Inizializzo il valore dei parametri 0 , 1
    polil->SetParameter(0, 2.05*pow(10, -23 ));
    polil->SetParameter(1, 1.72);
    polil->SetParameter(2, 5.2*pow(10, 1));

    // cambio colore alla linea della funzione in modo da distinguerla da polil quando la disegno
    polil->SetLineColor(2);
    // + significa che voglio aggiungere la funzione poli alla lista delle funzioni già disegnate sul canvas
    
    gilVl->Fit(polil,"M+");
    cout << "Chi^2:" << polil->GetChisquare() << ", number of DoF: " << polil->GetNDF() << " (Probability: " << polil->GetProb() << ")." << endl;
    cout << "--------------------------------------------------------------------------------------------------------" << endl;
    
    //Ipotesi come precedente , senza tenere conto della R int
    
    
    
    cout << "\n\n --- II) Ipotesi esponenziale --- \n" <<endl;
    
    
    
    TF1 *polil2 = new TF1("polil","expo");
    // Inizializzo il valore dei parametri 0 , 1
    //polil2->SetParameter(0, 2.05*pow(10, -23 ));
    //polil2->SetParameter(1, 1.72);
    
    
    // cambio colore alla linea della funzione in modo da distinguerla da polil quando la disegno
    polil2->SetLineColor(8);
    // + significa che voglio aggiungere la funzione poli alla lista delle funzioni già disegnate sul canvas
    
    gilVl->Fit(polil2,"M+");
    cout << "Chi^2:" << polil2->GetChisquare() << ", number of DoF: " << polil2->GetNDF() << " (Probability: " << polil2->GetProb() << ")." << endl;
    cout << "--------------------------------------------------------------------------------------------------------" << endl;



    
   }








