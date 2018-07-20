//
//  esperienza5.c
//  Analisi dati esperienza 5 , Filtro RLC
//
//  Created by Simone on 29/02/16.
//
//

#include "esperienza5.h"


#include <TFitResultPtr.h>    // per estrarre la matrice di covarianza
#include <TFitResult.h>       // per estrarre la matrice di covarianza
#include <iostream>
#include <TGraphErrors.h>     // ci serve per istanziare grafici
#include <TAxis.h>            // ci serve per manipolare gli assi dei grafici
#include <TCanvas.h>          // ci serve per disegnare i grafici
#include <TF1.h>              // ci serve per scrivere le funzioni con cui fittare i grafici
#include "TVirtualFitter.h"   // ci serve come supporto per i fit
#include <iomanip>            // ci serve per manipolare l'output a video

using namespace std;


void esperienza5()
{
    
    // --------------------------- DATI ------------------------------- //
    
    // Dati presi in laboratorio: f = frequenza , sf = incertezza frequenza , Vin = tensione in entrata, sVin = incertezza tensione in entrata, Vout tensione uscita, sVout = incertezza tensione in uscita.
    float f[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 9.5, 9.6, 9.7, 9.8, 9.9, 10, 10.1, 10.2, 10.3, 10.4, 10.5, 11, 12, 13,14, 15, 16, 17, 18, 19, 20};
    float sf[] = {0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1};
    float Vin[]  = {17.6, 17.6, 17.8, 18.2, 18.6, 18.8, 19, 19.4, 19.4, 19.6, 19.6, 19.6, 19.6, 19.4, 19.6, 19.6, 19.6, 19.6, 19.4, 19.4, 19.4, 19.2, 19.2, 19, 18.8, 18.6, 18.4, 18.4, 18.4, 18.2};
    float sVin[] = {0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2};
    float Vout[]  = {2.8, 5.4, 7.6, 9.8, 12.4, 14.8, 16.6, 18, 18.4, 18.6, 18.6, 18.6, 18.6, 18.8, 18.6, 18.6, 18.6, 18.6, 18.4, 18.4, 18.2, 17.4, 16.8, 15.8, 15, 14.2, 13.2, 12.6, 12, 11.4};
    float sVout[] = {0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2};
    
    // numero misure prese
    int nmisure = 30;
    // ---------------------------------------------------------------- //
    
    
    // ---------------------- Quantità derivate ----------------------- //
    
    
    // Array che conterrà i valori calcolati delle potenze e loro incertezze (rapporto Vout/Vin)
    float G[nmisure];
    float sG[nmisure];
    
    // Array che conterrà i valori dei logaritmi delle potenze e loro incertezze (log frequenza)
    float logf[nmisure];
    float slogf[nmisure];
    
    
    
    // ciclo for (loop) sulle misure
    for(int j=0; j<nmisure;++j){
        G[j]  = Vout[j] / Vin[j];
        sG[j] = sqrt(pow(sVin[j]/Vin[j],2) + pow(sVout[j]*Vout[j]/(Vin[j]*Vin[j]),2));
        
        // Stampa a video dei valori. \t inserisce un tab nel print out. Mettendo \n si va a capo invece
        cout << "Measurement number " << j << ":\t Vin = (" << Vin[j] << " +- " << sVin[j] << ") Vin, \t Vout = (" << Vout[j] << " +- " << sVout[j] << ") V, \t G = ("<< G[j] << " +- " << sG[j] << ") , \t f = ("<< f[j] << " +- " << sf[j] << ") KHz." << endl;
        
     
    }
    // ----------------------------------------------------------------- //
    
    
    
    
    // --------------------- Grafico Vout/Vin(f) ------------------------------ //
    // Creo il canvas (la tela) su cui disegnare il grafico. "ciV" è il il suo nome in memoria
    // è bene che sia unico dentro al programma. "i(v)" è semplicemente il titolo del canvas
    // le due coppie di numeri che seguono sono le coordinate dell'angolo superiore sinistro e le seconde
    // la dimensione in pixel lungo x e lungo y
    TCanvas *cG = new TCanvas("cG","G(f)",200,10,600,400);
    // Mi assicuro che la tela sia bianca (0 corrisponde al bianco, per altri colori vedi https://root.cern.ch/doc/master/classTColor.html)
    cG->SetFillColor(0);
    // Mi assicuro che disegni su questa tela e non su un altra. Ciò è particolarmente importante quando ho tanti canvas aperti.
    cG->cd();
      cG->SetLogx(1);
    // Istanzio il grafico. Il costruttore che noi usiamo prende come argomenti:
    // il numero di misure da disegnare, l'array di misure x (=V), l'array di misure y (=i), e gli
    // array delle  rispettive incertezze
    TGraphErrors *gG = new TGraphErrors(nmisure,f,G,sf,sG);
    // Nelle due righe successive disegno i punti del grafico con lo stile che più mi piace.
    // Vedi anche https://root.cern.ch/doc/master/classTAttMarker.html
    gG->SetMarkerSize(0.6);
    gG->SetMarkerStyle(21);
    // Facile, titolo del grafico
    gG->SetTitle("Vout/Vin(f)");
    // Titoli degli assi
    gG->GetXaxis()->SetTitle("f [KHz]");
    gG->GetYaxis()->SetTitle("G");
    // Do istruzioni al grafico di disegnarsi sul canvas che ho selezionato preventivamente con cd()
    // Esistono diverse opzioni di disegno, vedi anche https://root.cern.ch/doc/master/classTGraphPainter.html
    // "AP" è molto semplice, gli stiamo chiedendo di disegnare gli assi (A) e i punti (P)
    gG->Draw("AP");

    // ----------------------------------------------------------------- //
    
    
    // ---------------- Analisi dati più approfondita ------------------ //
    
    

    
    //RICAVARE FUNZIONE PER FIT
    

    cout << "\n\n --- II) Ipotesi polinomiale con grado da determinare --- \n" <<endl;
    // funzione più complessa, qui voglio trovare l'esponente del polinomio che minimizza (lo scarto etc... de) la funzione
    TF1 *poli = new TF1("poli","([0]*x/sqrt((pow(x*x -[1],2)+[2]*x*x)))");
    // Inizializzo il valore del parametro 0 (provate a commentare la linea seguente e vedete che cosa succede...)
  poli->SetParameter(0, 3.4*pow(10,2));
    // impongo che gli altri due parametri siano in un determinato intervallo
poli->SetParameter(1, 1.37*pow(10,3));
poli->SetParameter(2,1.5*pow(10, 5));
    // cambio colore alla linea della funzione in modo da distinguerla da pol4 quando la disegno
    poli->SetLineColor(4);
    // + significa che voglio aggiungere la funzione poli alla lista delle funzioni già disegnate sul canvas, in questo caso pol4
    gG->Fit(poli,"M+");
    cout << "Chi^2:" << poli->GetChisquare() << ", number of DoF: " << poli->GetNDF() << " (Probability: " << poli->GetProb() << ")." << endl;
    cout << "--------------------------------------------------------------------------------------------------------" << endl;

      
}
