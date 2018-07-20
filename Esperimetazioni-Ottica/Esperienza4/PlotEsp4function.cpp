//
//  PlotEsp4function.cpp
//  
//
//  Created by Simone Azeglio on 14/06/16.
//
//

#include <stdio.h>
#include <iostream>
#include <TGraphErrors.h>     // ci serve per istanziare grafici
#include <TAxis.h>            // ci serve per manipolare gli assi dei grafici
#include <TCanvas.h>          // ci serve per disegnare i grafici
#include <TF1.h>              // ci serve per scrivere le funzioni con cui fittare i grafici
#include "TVirtualFitter.h"   // ci serve come supporto per i fit
#include <iomanip>            // ci serve per manipolare l'output a video


using namespace std ;

void PlotEsp4function()

{ TF1 *f1 = new TF1 ("f1","0.5* (((cos(x)-1.5263*sqrt(1-0.6552*sin(x)*0.6552*sin(x)))/(cos(x)+1.5263*sqrt(1-0.6552*sin(x)*0.6552*sin(x))))*(((cos(x)-1.5263*sqrt(1-0.6552*sin(x)*0.6552*sin(x)))/(cos(x)+1.5263*sqrt(1-0.6552*sin(x)*0.6552*sin(x)))) + ((sqrt(1-0.6552*sin(x)*0.6552*sin(x))-1.5263*cos(x))/(sqrt(1-0.6552*sin(x)*0.6552*sin(x))+1.5263*cos(x))))* ((sqrt(1-0.6552*sin(x)*0.6552*sin(x))-1.5263*cos(x))/(sqrt(1-0.6552*sin(x)*0.6552*sin(x))+1.5263*cos(x)))))",0.2656,0.6997);
    
    f1->Draw() ;


}