#include <iostream>
#include <TGraphErrors.h>     // ci serve per istanziare grafici
#include <TAxis.h>            // ci serve per manipolare gli assi dei grafici
#include <TCanvas.h>          // ci serve per disegnare i grafici
#include <TF1.h>              // ci serve per scrivere le funzioni con cui fittare i grafici
#include "TVirtualFitter.h"   // ci serve come supporto per i fit
#include <iomanip>            // ci serve per manipolare l'output a video 

using namespace std; 

//const float ALPHA = 4.2 * pow(10,-3);
//const float RHO0 = 5.25 * pow(10,-8);


void lampadina()
{

  // --------------------------- DATI ------------------------------- // 
  // Resistenza della lampadina, misurata in laboratorio con il multimetro
  const float R0 = 15; 

  // Dati presi in laboratorio: V = tensione, sV = incertezza tensione, i = intensità di corrente, si = incertezza intensità di corrente
  // consiglio di non mettere il valore per V = 0 V altrimenti si avranno problemi nella parte in cui si calcolano i logaritmi
  float V[]  = {0.413, 0.883, 1.344, 1.820, 2.292, 2.768, 3.243, 3.724, 4.209, 4.689, 5.170, 5.649, 6.133, 6.616, 7.389, 7.895, 8.386, 8.881, 9.384, 9.879, 10.35, 10.85, 11.33, 11.83};
  float sV[] = {0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001,  0.01,  0.01,  0.01,  0.01};
  float i[]  = {10   , 16   , 20   , 24   , 27   , 30   , 33   , 35   , 38   , 40   , 42   , 44   , 46   , 48   , 50   , 50   , 50   , 60   , 60   , 60   , 60   , 60   , 60   , 70   };
  float si[] = {1    , 1    , 1    , 1    , 1    , 1    , 1    , 1    , 1    , 1    , 1    , 1    , 1    , 1    , 10   , 10   , 10   , 10   , 10   , 10   , 10   , 10   , 10   , 10   };

  // numero misure prese
  int nmisure = 24;
  // ---------------------------------------------------------------- //


  // ---------------------- Quantità derivate ----------------------- //

  // Array che conterrà i valori calcolati delle resistenze e loro incertezze
  float R[nmisure];
  float sR[nmisure];

  // Array che conterrà i valori calcolati delle potenze e loro incertezze
  float P[nmisure];
  float sP[nmisure];

  // Array che conterrà i valori dei logaritmi delle potenze e loro incertezze
  float logP[nmisure];
  float slogP[nmisure];

  // Array che conterrà i valori dei logaritmi delle resistenze e loro incertezze
  float logR[nmisure];
  float slogR[nmisure];


  // ciclo for (loop) sulle misure
  for(int j=0; j<nmisure;++j){
    R[j]  = V[j]/i[j]*1000;  // in ohm
    sR[j] = R[j] * sqrt(pow(sV[j]/V[j],2) + pow(si[j]/i[j],2));
    P[j]  = V[j] * i[j];
    sP[j] = P[j] * sqrt(pow(sV[j]/V[j],2) + pow(si[j]/i[j],2));

    // Stampa a video dei valori. \t inserisce un tab nel print out. Mettendo \n si va a capo invece
    cout << "Measurement number " << j << ":\t V = (" << V[j] << " +- " << sV[j] << ") V, \t i = (" << i[j] << " +- " << si[j] << ") mA,\t R = (" 
	 << std::setprecision(4) << R[j] << " +- " << sR[j] << ") ohm, \t P = (" 
	 << P[j] << " +- " << sP[j] << ") W." << endl;    

    // riempio qui gli array con i logaritmi di R e P (ed incertezze su questi)
    logR[j]  = log(R[j]);
    slogR[j] = sR[j]/R[j];
    logP[j]  = log(P[j]);
    slogP[j] = sP[j]/P[j];
  }
  // ----------------------------------------------------------------- //



  
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
  giV->GetXaxis()->SetTitle("V [V]");
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




  // --------------------- Grafico log(P(log(R))) -------------------- //
  cout << "\n\t ********* Fit a log(P(log(R))) ********* " << endl;
  TCanvas *clogPlogR = new TCanvas("clogPlogR","log(P(log(R)))",200,10,600,400);
  clogPlogR->SetFillColor(0);
  clogPlogR->cd();
  TGraphErrors *glogPlogR = new TGraphErrors(nmisure,logR,logP,slogR,slogP);
  glogPlogR->SetMarkerSize(0.6);
  glogPlogR->SetMarkerStyle(21);
  glogPlogR->SetTitle("log(P(log(R)))");
  glogPlogR->GetXaxis()->SetTitle("log(R)");
  glogPlogR->GetYaxis()->SetTitle("log(P)");
  glogPlogR->Draw("AP");
  
  // ------------------- Fit lineare a log(P(log(R))) ---------------- //
  // Creo una funzione. Il primo termine definisce il nome della funzione in memoria, è bene che sia unico
  // il secondo termine definisce la funzione. [0], [1], ... sono i parametri della funzione, x la variabile indipendente
  // In generale i parametri non sono noti a priori o sono noti solo dei valori approssimati (vedi dopo come inizializarli)
  TF1 *linear = new TF1("linear", "[1] * x + [0]");
  // Chiedi al grafico di effettuare il fit con la funzione "linear" definita sopra.
  glogPlogR->Fit(linear);
  // Stampa a video il valore del coefficiente angolare e dell'incertezza su di esso
  cout << "Angular coefficient: " << linear->GetParameter(1) << " +- " << linear->GetParError(1) << endl;
  // Stampa a video i risultati del test di chi2 sulla bontà del fit
  cout << "Chi^2:" << linear->GetChisquare() << ", number of DoF: " << linear->GetNDF() << " (Probability: " << linear->GetProb() << ")." << endl;
  cout << "--------------------------------------------------------------------------------------------------------" << endl;
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


  cout << "\n\n --- II) Ipotesi polinomiale con grado da determinare [0]*pow(x + [1],[2]) --- \n" <<endl;
  // funzione più complessa, qui voglio trovare l'esponente del polinomio che minimizza (lo scarto etc... de) la funzione
  TF1 *poli = new TF1("poli","[0]*pow(x + [1],[2])");
  // Inizializzo il valore del parametro 0 (provate a commentare la linea seguente e vedete che cosa succede...)
  poli->SetParameter(0,pow(10,-7));
  // impongo che gli altri due parametri siano in un determinato intervallo
  poli->SetParLimits(1,0,40);
  poli->SetParLimits(2,0,5);
  // cambio colore alla linea della funzione in modo da distinguerla da pol4 quando la disegno
  poli->SetLineColor(4);
  // + significa che voglio aggiungere la funzione poli alla lista delle funzioni già disegnate sul canvas, in questo caso pol4
  gPR->Fit(poli,"M+");
  cout << "Chi^2:" << poli->GetChisquare() << ", number of DoF: " << poli->GetNDF() << " (Probability: " << poli->GetProb() << ")." << endl;
  cout << "--------------------------------------------------------------------------------------------------------" << endl;


  cout << "\n\n --- III) Ipotesi quartica [0]*pow(x/[1] + 0.14723,4 ---" <<endl;
  // Ipotesi di relazione tra R e T (attenzione che in R = R0 (1+alpha*t),  t = T - 273.15) 
  TF1 *quartic = new TF1("quartic","[0]*pow(x/[1] + 0.14723,4)");
  // La funzione sopra è più complessa da minimizzare e il default di ROOT sul numero di iterazioni non è sufficiente 
  // a far convergere i risultati, quindi aumento il numero di iterazioni
  TVirtualFitter::SetMaxIterations(100000);
  quartic->SetParameters(pow(10,-7),15);
  quartic->SetLineColor(6);
  gPR->Fit(quartic,"M+");
  cout << "Chi^2:" << quartic->GetChisquare() << ", number of DoF: " << quartic->GetNDF() << " (Probability: " << quartic->GetProb() << ")." << endl;
  cout << "--------------------------------------------------------------------------------------------------------" << endl;
  
}
