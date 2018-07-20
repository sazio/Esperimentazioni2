#include <iostream>
#include <TGraphErrors.h>     // ci serve per istanziare grafici
#include <TAxis.h>            // ci serve per manipolare gli assi dei grafici
#include <TCanvas.h>          // ci serve per disegnare i grafici
#include <TF1.h>              // ci serve per scrivere le funzioni con cui fittare i grafici
#include "TVirtualFitter.h"   // ci serve come supporto per i fit
#include <iomanip>            // ci serve per manipolare l'output a video 

using namespace std; 



void pannello()
{

    //-------------------------- DATI parte 1 -------------------------------//
    
    float D[] = {300, 280, 260, 240, 220, 200, 180, 160, 140, 120, 100, 80, 60, 40, 20, 0};
    float sD[] = {0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01};
    float Icc[] = {5.25, 5.66, 5.91, 6.88, 7.64, 8.65, 9.80, 11.31, 13.22, 15.76, 19.32, 24.28, 31.34, 42.77, 62.19, 99.22};
    float sIcc[] = {0.30, 0.30, 0.30, 0.30,0.30, 0.30, 0.30, 0.30, 1, 1,  1, 1, 1, 2, 2, 3};
    float Vp[] = {205, 215.5, 223, 230, 238.5, 247.5, 256.5, 266.5, 277.5, 290, 304, 318.5, 336, 356, 379, 406};
    float sVp[] = {20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20};
    //-- Potenza prodotta , data da potenza pannello - potenza con copertura luce in Watt//
    float Pprodotta[] = {0.0003, 0.0003, 0.0003, 0.0004, 0.0004, 0.0005, 0.0006, 0.0007, 0.0009, 0.0011, 0.0015, 0.0018, 0.0025, 0.0037, 0.0054, 0.0094};
    float sPprodotta [] = {0.0001, 0.0001, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0003, 0.0003, 0.0003, 0.0004};
    // P prodotta senza ultimo dato , quello a D = 0 , il fit risulta soddisfacente con la funzione che ci aspettiamo ovvero [0]/x
    float D1[] = {300, 280, 260, 240, 220, 200, 180, 160, 140, 120, 100, 80, 60, 40, 20};
    float sD1[] = {0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01};

    float Pprodotta1[] = {0.0003, 0.0003, 0.0003, 0.0004, 0.0004, 0.0005, 0.0006, 0.0007, 0.0009, 0.0011, 0.0015, 0.0018, 0.0025, 0.0037, 0.0054};
    float sPprodotta1 [] = {0.0001, 0.0001, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0003, 0.0003, 0.0003};

        
    //numero misure
    
    int nummisure = 16;
    int nummisure1 = 15;
    
  // --------------------------- DATI parte 2 ------------------------------- //

  // Dati presi in laboratorio: V = tensione, sV = incertezza tensione, i = intensità di corrente, si = incertezza intensità di corrente
    float V[]  = {117, 134, 149, 162, 173, 183, 191, 198, 204, 210, 214 ,218};
  float sV[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
  float i[]  = {11.20, 10.80, 10.30, 9.90, 9.40, 9.00, 8.50, 8.20, 7.80, 7.40, 7.10, 6.70};
  float si[] = {0.10, 0.10, 0.10, 0.10, 0.10, 0.10, 0.10, 0.10, 0.10, 0.10, 0.10, 0.10};

  // numero misure prese
  int nmisure = 12;
  // ---------------------------------------------------------------- //


  // ---------------------- Quantità derivate ----------------------- //

  // Array che conterrà i valori calcolati delle resistenze e loro incertezze
  float R[nmisure];
  float sR[nmisure];
    float VAR[nmisure];
    float Rtot[nmisure];

  // Array che conterrà i valori calcolati delle potenze e loro incertezze
  float P[nmisure];
  float sP[nmisure];


  // ciclo for (loop) sulle misure
  for(int j=0; j<nmisure;++j){
      VAR[j] = 9+j*2;

    R[j]  = V[j]/i[j];  // in ohm
    sR[j] = R[j] * sqrt(pow(sV[j]/V[j],2) + pow(si[j]/i[j],2));
    P[j]  = V[j] * i[j];
    sP[j] = P[j] * sqrt(pow(sV[j]/V[j],2) + pow(si[j]/i[j],2));
      Rtot[j]=VAR[j]+R[j];
      
    // Stampa a video dei valori.
    cout << "Measurement number " << j << ":\t V = (" << V[j] << " +- " << sV[j] << ") V, \t i = (" << i[j] << " +- " << si[j] << ") mA,\t R = (" 
	 << std::setprecision(4) << R[j] << " +- " << sR[j] << ") ohm, \t P = (" 
	 << P[j] << " +- " << sP[j] << ") W." << endl;    
  }
  // ----------------------------------------------------------------- //

      // -------------- - - - grafici 1 parte - - - --------------//
    
    
    //___________________Grafico Pprodotta(D) ----  - - -- - - - -- - -//
    
        cout << "\n\t ********* Fit a Pprodotta(D) ********* " << endl;
    
    TCanvas *cPprodottaD = new TCanvas("cPprodottaD","Pprodotta(D)",200,10,600,400);
    cPprodottaD->SetFillColor(0);
    cPprodottaD->cd();
    TGraphErrors *gPprodottaD = new TGraphErrors(nummisure, D, Pprodotta, sD, sPprodotta);
    gPprodottaD->SetMarkerSize(0.6);
    gPprodottaD->SetMarkerStyle(21);
    gPprodottaD->SetTitle("P(D)");
    gPprodottaD->GetXaxis()->SetTitle("D [mm]");
    gPprodottaD->GetYaxis()->SetTitle("P [W]");
    gPprodottaD->Draw("AP");
    
    
     cout << "\n\n --- II) Ipotesi polinomiale con grado da determinare --- \n" <<endl;
    // funzione più complessa, qui voglio trovare l'esponente del polinomio che minimizza (lo scarto etc... de) la funzione
    TF1 *poli = new TF1("poli","[0]/(pow([1] + x, [2]))");
    // Inizializzo il valore 5 parametro 0 (provate a commentare la linea seguente e vedete che cosa succede...)
    poli->SetParameter(0, 3.42*pow(10,2));
      poli->SetParameter(1, 8.31*pow(10,1));
    poli->SetParameter(2, 2.37);
    // cambio colore alla linea della funzione in modo da distinguerla da pol4 quando la disegno
     poli->SetLineColor(4);
    // + significa che voglio aggiungere la funzione poli alla lista delle funzioni già disegnate sul canvas, in questo caso pol4
    gPprodottaD->Fit(poli,"M+");
    cout << "Chi^2:" << poli->GetChisquare() << ", number of DoF: " << poli->GetNDF() << " (Probability: " << poli->GetProb() << ")." << endl;
    cout << "--------------------------------------------------------------------------------------------------------" << endl;
    
  
    //___________________Grafico Pprodotta1(D) ----  - - -- - - - -- - -//
    
    cout << "\n\t ********* Fit a Pprodotta1(D) ********* " << endl;
    
    TCanvas *cPprodottaD1 = new TCanvas("cPprodottaD1","Pprodotta1(D)",200,10,600,400);
    cPprodottaD1->SetFillColor(0);
    cPprodottaD1->cd();
    TGraphErrors *gPprodottaD1 = new TGraphErrors(nummisure1, D1, Pprodotta1, sD1, sPprodotta1);
    gPprodottaD1->SetMarkerSize(0.6);
    gPprodottaD1->SetMarkerStyle(21);
    gPprodottaD1->SetTitle("P1(D)");
    gPprodottaD1->GetXaxis()->SetTitle("D [mm]");
    gPprodottaD1->GetYaxis()->SetTitle("P [W]");
    gPprodottaD1->Draw("AP");

    
   cout << "\n\n --- II) Ipotesi polinomiale con grado da determinare --- \n" <<endl;
    // funzione più complessa, qui voglio trovare l'esponente del polinomio che minimizza (lo scarto etc... de) la funzione
   TF1 *poli2 = new TF1("poli","[0]/(pow(x, [1]))");
    // Inizializzo il valore 5 parametro 0 (provate a commentare la linea seguente e vedete che cosa succede...)
   poli2->SetParameter(0, 1.08*pow(10,-1));
    poli2->SetParameter(1, 9.71*pow(10,-1));
     //cambio colore alla linea della funzione in modo da distinguerla da pol4 quando la disegno
   poli2->SetLineColor(3);
    // + significa che voglio aggiungere la funzione poli alla lista delle funzioni già disegnate sul canvas, in questo caso pol4
    gPprodottaD1->Fit(poli2,"M+");
    cout << "Chi^2:" << poli2->GetChisquare() << ", number of DoF: " << poli2->GetNDF() << " (Probability: " << poli2->GetProb() << ")." << endl;
    cout << "--------------------------------------------------------------------------------------------------------" << endl;
    
    

    
    cout << "\n\n --- II) Ipotesi polinomiale con grado da determinare --- \n" <<endl;
    // funzione più complessa, qui voglio trovare l'esponente del polinomio che minimizza (lo scarto etc... de) la funzione
    TF1 *poli3 = new TF1("poli3","[0]/(pow([1] + x, [2]))");
    // Inizializzo il valore 5 parametro 0 (provate a commentare la linea seguente e vedete che cosa succede...)
    poli3->SetParameter(0, 3.42*pow(10,2));
    poli3->SetParameter(1, 8.31*pow(10,1));
    poli3->SetParameter(2, 2.37);
    // cambio colore alla linea della funzione in modo da distinguerla da pol4 quando la disegno
    poli3->SetLineColor(4);
    // + significa che voglio aggiungere la funzione poli alla lista delle funzioni già disegnate sul canvas, in questo caso pol4
    gPprodottaD1->Fit(poli3,"M+");
    cout << "Chi^2:" << poli3->GetChisquare() << ", number of DoF: " << poli3->GetNDF() << " (Probability: " << poli3->GetProb() << ")." << endl;
    cout << "--------------------------------------------------------------------------------------------------------" << endl;
    

    
    

    
     // --------------------- Grafico Icc(D) ------------------------------ //
    
    TCanvas *cIccD = new TCanvas("cIccD", "Icc(d)",200,10,600,400);
    
    cIccD->SetFillColor(0);
    
    cIccD->cd();
    
    TGraphErrors *gIccD = new TGraphErrors(nummisure,D,Icc,sD,sIcc);
    
    gIccD->SetMarkerSize(0.6);
    
    gIccD->SetMarkerStyle(21);
    
    gIccD->SetTitle("Icc(D)");
    
    gIccD->GetXaxis()->SetTitle("D [mm]");
    
    gIccD->GetYaxis()->SetTitle("Icc [mA]");
    
    gIccD->Draw("AP");
    
    cout << "\n\t ********* Fit a Icc(D) ********* " << endl;
    
    //Ipotesi polinomiale
    
    cout << "------------------------------Ipotesi polinomiale ------------------------" << endl;
    cout << "\n\n --- II) Ipotesi polinomiale con grado da determinare --- \n" <<endl;
    // funzione più complessa, qui voglio trovare l'esponente del polinomio che minimizza (lo scarto etc... de) la funzione
    TF1 *pollo1 = new TF1("pollo1","[0]/(pow([1] + x, [2]))");
    // Inizializzo il valore 5 parametro 0 (provate a commentare la linea seguente e vedete che cosa succede...)
    pollo1->SetParameter(0, 3.42*pow(10,2));
    pollo1->SetParameter(1, 8.31*pow(10,1));
    pollo1->SetParameter(2, 2.37);
    // cambio colore alla linea della funzione in modo da distinguerla da pol4 quando la disegno
    pollo1->SetLineColor(1);
    // + significa che voglio aggiungere la funzione poli alla lista delle funzioni già disegnate sul canvas, in questo caso pol4
    gIccD->Fit(pollo1,"M+");
    cout << "Chi^2:" << pollo1->GetChisquare() << ", number of DoF: " << pollo1->GetNDF() << " (Probability: " << pollo1->GetProb() << ")." << endl;
    cout << "--------------------------------------------------------------------------------------------------------" << endl;
    
    // --------------------- Grafico Vp(D) ------------------------------ //
    
    TCanvas *cVpD = new TCanvas("cVpD", "Vp(d)",200,10,600,400);
    
    cVpD->SetFillColor(0);
    
    cVpD->cd();
    
    TGraphErrors *gVpD = new TGraphErrors(nummisure,D,Vp,sD,sVp);
    
    gVpD->SetMarkerSize(0.6);
    
    gVpD->SetMarkerStyle(21);
    
    gVpD->SetTitle("Vp(D)");
    
    gVpD->GetXaxis()->SetTitle("D [mm]");
    
    gVpD->GetYaxis()->SetTitle("Vp [mV]");
    
    gVpD->Draw("AP");
    
    //Fit
    
    cout << "\n\t ********* Fit a Vp(D) ********* " << endl;
    
    //ipotesi polinomiale

    cout << "------------------------------Ipotesi polinomiale ------------------------" << endl;
    cout << "\n\n --- II) Ipotesi polinomiale con grado da determinare --- \n" <<endl;
    // funzione più complessa, qui voglio trovare l'esponente del polinomio che minimizza (lo scarto etc... de) la funzione
    TF1 *pollo4 = new TF1("pollo4","[0]/(pow([1] + x, [2]))");
    // Inizializzo il valore 5 parametro 0 (provate a commentare la linea seguente e vedete che cosa succede...)
    pollo4->SetParameter(0, 3.01*pow(10,4));
    pollo4->SetParameter(1, 2.29*pow(10,2));
    pollo4->SetParameter(2, 7.93*pow(10,-1));
    // cambio colore alla linea della funzione in modo da distinguerla da pol4 quando la disegno
    pollo4->SetLineColor(6);
    // + significa che voglio aggiungere la funzione poli alla lista delle funzioni già disegnate sul canvas, in questo caso pol4
    gVpD->Fit(pollo4,"M+");
    cout << "Chi^2:" << pollo4->GetChisquare() << ", number of DoF: " << pollo4->GetNDF() << " (Probability: " << pollo4->GetProb() << ")." << endl;
    cout << "--------------------------------------------------------------------------------------------------------" << endl;

    
   
   //------------------ grafici 2 parte -------------------------//
  
  // --------------------- Grafico i(V) ------------------------------ //
  // Creo il canvas (la tela) su cui disegnare il grafico. "ciV" è il il suo nome in memoria
  // è bene che sia unico dentro al programma. "i(v)" è semplicemente il titolo del canvas
  // le due coppie di numeri che seguono sono le coordinate dell'angolo superiore sinistro e le seconde
  // la dimensione in pixel lungo x e lungo y
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
    

  // --------------------- Grafico P(R) ------------------------------ //
  TCanvas *cPR = new TCanvas("cPR","P(R)",200,10,600,400);
  cPR->SetFillColor(0);
  cPR->cd();
  TGraphErrors *gPR = new TGraphErrors(nmisure,R,P,sR,sP);
  gPR->SetMarkerSize(0.6);
  gPR->SetMarkerStyle(21);
  gPR->SetTitle("P(R)");
  gPR->GetXaxis()->SetTitle("R [#Omega]");
  gPR->GetYaxis()->SetTitle("P [mW]");
  gPR->Draw("AP");
  // ----------------------------------------------------------------- //



  // ---------------- Analisi dati più approfondita ------------------ //

    cout << "\n\t ********* Fit a P(R) ********* " << endl;
    cPR->cd();
    cout << "\n\n --- I) Ipotesi pol4 --- \n" <<endl;
    // Usa una polinomiale di ordine 4. è una funzione built-in in root. Anche quella lineare lo è ma ho voluto mettervela come esempio esplicito.
    TF1 *pol4 = new TF1("pol4","pol4");
    // L'opzione M migliora la stima delle incertezze sui parametri facendo girare un programma, HESSE, dopo aver girato la minimizzazione
    gPR->Fit(pol4,"M");
    cout << "Chi^2:" << pol4->GetChisquare() << ", number of DoF: " << pol4->GetNDF() << " (Probability: " << pol4->GetProb() << ")." << endl;
    cout << "--------------------------------------------------------------------------------------------------------" << endl;


  
}
