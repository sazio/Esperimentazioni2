#include <iostream>
#include <TGraphErrors.h>
#include <TAxis.h>
#include <TCanvas.h>
#include <TF1.h>
#include "TVirtualFitter.h"
#include <iomanip>



void spettroscopio()
{
  

  float theta[]= {48.817, 48.483, 50.683, 51.667, 49.684, 49.567, 51.15};
  float l[]={ 545.567,435.367, 577.775, 404.422,589.142,  696.185, 568.302 };

  float stheta[]={0.023,0.023,0.023,0.023, 0.023,0.023,0.023,0.023};
  float sl[]={1.263,1.1055,2.215,1.105, 1.263, 1.100, 1.105, 1.250};



  //numero misure prese
    
int nmisure = 7;
    
    
    
    
    //--------------------- Grafico  -----------------
    
    TCanvas *cltheta = new TCanvas("cltheta","l[theta]",200,10,600,400);
    
    // 0 è il colore bianco
    cltheta->SetFillColor(0);
    cltheta->cd();
    
    TGraphErrors *gltheta = new TGraphErrors(nmisure,theta,l,stheta,sl);
    gltheta->SetMarkerSize(0.6);
    gltheta->SetMarkerStyle(21);
    
    //  Titolo del grafico
    gltheta->SetTitle("l[theta]");
    
    // Titoli degli assi
    gltheta->GetXaxis()->SetTitle("theta [gradi]");
    gltheta->GetYaxis()->SetTitle("lambda [nm]");
    
    gltheta->Draw("AP");
    
  // ------------------- Fit parabolico  ---------------- //

    cout<<"\t------------ Fit Parabolico ----------\n" ;
    
  TF1 *parabola = new TF1("parabola", "[1] * x + [0]+[2]*x*x");

  gltheta->Fit(parabola,"M+");
    
       parabola->SetLineColor(3);
    
    // Stampa a video i risultati del test di chi2 sulla bontÃ  del fit
  cout << "Chi^2:" << parabola->GetChisquare() << ", number of DoF: " << parabola->GetNDF() << " (Probability: " << parabola->GetProb() << ")." << endl;
  cout << "--------------------------------------------------------------------------------------------------------" << endl;
  // ----------------------------------------------------------------- //
     
 
    
    
    
    
    // ------------------- Fit iperbolico  ---------------- //
    
       cout<<"\t------------ Fit Iperbolico ----------\n" ;
  
  TF1 *iperbole = new TF1("iperbole", "[0]+ [1]/x  ");
  
    
       iperbole->SetLineColor(4);
    
  gltheta->Fit(iperbole,"M+");

    
  // Stampa a video i risultati del test di chi2 sulla bontÃ  del fit
  cout << "Chi^2:" << iperbole->GetChisquare() << ", number of DoF: " << iperbole->GetNDF() << " (Probability: " << iperbole->GetProb() << ")." << endl;
  cout << "--------------------------------------------------------------------------------------------------------" << endl;
  // ----------------------------------------------------------------- //

}
