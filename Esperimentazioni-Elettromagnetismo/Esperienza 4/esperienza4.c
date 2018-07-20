//
//  esperienza4.c

//  Analisi dati del filtro passa basso
//  
//
//  Created by Simone on 01/03/16.
//
//

#include "esperienza4.h"
#include <iostream> 
#include <TFitResultPtr.h>
#include <TFitResult.h>
#include <TGraphErrors.h>     // ci serve per istanziare grafici
#include <TAxis.h>            // ci serve per manipolare gli assi dei grafici
#include <TCanvas.h>          // ci serve per disegnare i grafici
#include <TF1.h>              // ci serve per scrivere le funzioni con cui fittare i grafici
#include "TVirtualFitter.h"   // ci serve come supporto per i fit
#include <iomanip>  // ci serve per manipolare l'output a video


using namespace std;

void esperienza4()
{
    
    
//------------- DATI Parte 1--------------//
    
    //L' obbiettivo è misurare con l' oscilloscopio la tensione all' ingresso del circuito e all' uscita per varie frequenze
    // f = frequenze , sf = incertezza sulle frequenze, Vin = V entrata sVin = incertezza V entrata, Vout = V uscita, sVout = incertezza V uscita
    float f[] = {500, 1000, 1500, 2000, 2500, 3000, 3500, 4000, 4500, 5000, 6000, 7000, 8000, 9000, 10000, 15000, 20000, 50000};
    float sf[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    float Vin[] = {10.20, 10.20, 10.20, 10.20, 10.20 ,10.20, 10.20, 10.20, 10.20, 10.20, 10.30, 10.40, 10.30, 10.30, 10.30, 10.30, 10.40, 10.20};
    float sVin[] = {0.10, 0.10, 0.10, 0.10, 0.10, 0.10, 0.10, 0.10, 0.10, 0.10, 0.10, 0.10, 0.10, 0.10, 0.10, 0.10, 0.10, 0.10};
    float Vout[] = {9.90, 9.10, 8.20, 7.30, 6.50, 5.80, 5.20, 4.70, 4.30, 3.90, 3.50, 3.10, 2.70, 2.50, 2.30, 1.60, 1.30, 0.42};
    float sVout[] = {0.10, 0.10, 0.10, 0.10, 0.10, 0.10, 0.10, 0.10, 0.10, 0.10, 0.10, 0.10,0.10, 0.10, 0.10, 0.10, 0.10, 0.01};
    
    // numero misure
    int nmisure = 18 ;
//--------------------------------------------//
    

           //-------------Grandezze derivate ----------------//
    
    // rapporto Vout/Vin
    float G[nmisure];
    float sG[nmisure];
    
    // ciclo for
    
    for(int j=0; j<nmisure;++j){
        G[j] = Vout[j]/Vin[j];
        sG[j] = G[j] * sqrt(pow(sVout[j]/Vin[j],2) + pow(sVin[j]/Vin[j]*Vin[j],2));
        
// Stampa a video dei valori
        cout << "Measurement number " << j << ":\t f = (" << f[j] << "+-" << sf[j] << ") KHz,\t Vin = (" << Vin[j] << "+-" << sVin[j] << ") V, \t Vout = (" << Vout[j] << "+-" << sVout[j] << ") V, \t G = (" << std::setprecision(4) << G[j] << "+-" << sG[j] << ") ." <<endl;
    }

    //---------------------------------------------------------------//


//- - - -  - -- - - - -   - - - - -  - Grafico Vout/Vin(f) - - -  -  - - - - - --  -- - - - - -  -- //

    // creo tela su cui disegnare , "cG" è il suo nome nella memoria

TCanvas *cG = new TCanvas("cG","G(f)",200,10,600,400);
    
   // Colore tela : bianca
    cG->SetFillColor(0);
    
    // mi assicuro che disegni su questa tela
    cG->cd();
    cG->SetLogx(1);
    
    //Grafico
    TGraphErrors *gG = new TGraphErrors(nmisure,f,G,sf,sG);
    
    //Disegno i punti del grafico con lo stile che più mi piace.
    // Vedi anche https://root.cern.ch/doc/master/classTAttMarker.html
    gG->SetMarkerSize(0.6);
    gG->SetMarkerStyle(21);
    
    //Titolo del grafico
    gG->SetTitle("Vout/Vin(f)");
    
    // Titoli degli assi
    gG->GetXaxis()->SetTitle("f [kHz]");
    gG->GetYaxis()->SetTitle("G");
    
    // Esistono diverse opzioni di disegno, vedi anche https://root.cern.ch/doc/master/classTGraphPainter.html
    // "AP" è molto semplice, gli stiamo chiedendo di disegnare gli assi (A) e i punti (P)
    gG->Draw("AP");
    
    
    
    //----------------------Fit Vout/Vin(f) ---------------------------//
    
    cout <<"\n\t ************* Fit G(f) ************* " << endl;
    cG->cd();
    
    cout <<"\n\n --- Funzione predefinita con definizione di G --- \n" << endl;
    // Definisco f1 per fit
    TF1 *poli = new TF1("poli","pow([0]*x*x + [1],[2])");
    // Inizializzo il valore del parametro 0 (provate a commentare la linea seguente e vedete che cosa succede...)
    poli->SetParameter(0, 1/(4.02 * pow(10 , 6)));
    // impongo che gli altri due parametri siano in un determinato intervallo
    poli->SetParameter(1, 1);
    poli->SetParameter(2, -0.5);
    // cambio colore alla linea della funzione in modo da distinguerla da pol4 quando la disegno
    poli->SetLineColor(4);
    // + significa che voglio aggiungere la funzione poli alla lista delle funzioni già disegnate sul canvas, in questo caso pol4
    gG->Fit(poli,"MS");
    cout << "Chi^2:" << poli->GetChisquare() << ", number of DoF: " << poli->GetNDF() << " (Probability: " << poli->GetProb() << ")." << endl;
    
    

    

    

}





