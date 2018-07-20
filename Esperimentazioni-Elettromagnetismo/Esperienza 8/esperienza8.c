//
//  esperienza8.c
//  
//
//  Created by Simone on 21/03/16.
//
//

#include "esperienza8.h"
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

void esperienza8()
{
    // I seguenti grafici servono per dimostrare che l ' amplificatore abbia un comportamento identico al passa-basso
    
    
    // -  - - - - - - - - Dati - - -  - -- - - - - -- //
    
    float f[] = {4, 7, 10, 22, 34, 46, 58, 70, 75, 80, 83};
    float sf[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
    float Vin[] = {1.80, 1.80, 1.80, 1.80, 1.80, 1.80, 1.80, 1.80, 1.80, 1.80, 1.80};
    float sVin[] = {0.04, 0.04, 0.04, 0.04, 0.04, 0.04, 0.04, 0.04, 0.04, 0.04, 0.04};
    float Vout[] = {2.62, 2.62, 2.56, 2.36, 2.10, 1.80, 1.56, 1.36, 1.32, 1.26, 1.22};
    float sVout[] = {0.04, 0.04, 0.04, 0.04, 0.04, 0.04, 0.04, 0.04, 0.04, 0.04, 0.04};

    
    // numero misure
    int nmisure =  11;
    //--------------------------------------------//
    
    
    //-------------Grandezze derivate ----------------//
    
    // Guadagno ( Vout/Vin)
    float G[nmisure];
    float sG[nmisure];
    
    // ciclo for
    
    for(int j=0; j<nmisure;++j){
        G[j] = Vout[j]/Vin[j];
        sG[j] = G[j] * sqrt(pow(sVout[j]/Vin[j],2) + pow(sVin[j]/Vin[j]*Vin[j],2));
        
        // Stampa a video dei valori
        cout << "Measurement number " << j << ":\t f = (" << f[j] << "+-" << sf[j] << ") KHz,\t Vin = (" << Vin[j] << "+-" << sVin[j] << ") V, \t Vout = (" << Vout[j] << "+-" << sVout[j] << ") V, \t G = (" << std::setprecision(4) << G[j] << "+-" << sG[j] << ") ." <<endl;
    }
    
        
        //- - - -  - -- - - - -   - - - - -  - Grafico Vout/Vin(f) - - -  -  - - - - - --  -- - - - - -  -- //
        
        
        TCanvas *cG = new TCanvas("cG","G(f)",200,10,600,400);
        
        // Colore tela : bianca
        cG->SetFillColor(0);
        
        // mi assicuro che disegni su questa tela
        cG->cd();
        cG->SetLogx(1);
        
        //Grafico
        TGraphErrors *gG= new TGraphErrors(nmisure,f,G,sf,sG);
        
        //Disegno i punti del grafico con lo stile che più mi piace.
        // Vedi anche https://root.cern.ch/doc/master/classTAttMarker.html
        gG->SetMarkerSize(0.6);
        gG->SetMarkerStyle(21);
        
        //Titolo del grafico
        gG->SetTitle("G(f)");
        
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
        poli->SetParameter(0, 2.52*pow(10, -4));
        // impongo che gli altri due parametri siano in un determinato intervallo
        poli->SetParameter(1, 1);
        poli->SetParameter(2, -0.5);
        // cambio colore alla linea della funzione in modo da distinguerla da pol4 quando la disegno
        poli->SetLineColor(4);
        // + significa che voglio aggiungere la funzione poli alla lista delle funzioni già disegnate sul canvas, in questo caso pol4
        gG->Fit(poli,"MS");
        cout << "Chi^2:" << poli->GetChisquare() << ", number of DoF: " << poli->GetNDF() << " (Probability: " << poli->GetProb() << ")." << endl;
        
           }
    
    

