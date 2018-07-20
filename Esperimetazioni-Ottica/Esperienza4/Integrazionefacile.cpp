//
//  Integrazionefacile.cpp
//  
//
//  Created by Simone Azeglio on 16/06/16.
//
//

#include <stdio.h>
#include <iostream>
#include <math.h>
#include <iomanip>
#include <string>
#include <fstream>

using namespace std;

double f(double x) ; //Funzione da integrare

int main()
{
     double low, up, part , h;
    
    cout << "\n                           ============      Exp 4      ============ \n\n" ;
    
    cout << "What is the lower bound? " ;
    cin >> low ;
    
    cout << "What is the upper bound? " ;
    cin >> up ;
    
    cout << "How many partitions do you want to use? " ;
    cin >> part ;
    
    
    h = (up -low )/part ;
    
   
    // Rettangoli
    
     cout << "\n\n                  -------------------- RECTANGLE-RULE ------------------- \n" ;
    
    double R , Rtot ;
    
    R = f(low) + f(up) ;
    
    for (int i = 1 ; i < part ; i++) {
        
        R += 2*f(low+ i*h) ;
        
    }
    
    R *= h/2 ;
    
     Rtot = R + (1-R)*(1-R)*R ;
    
    cout << "\nThe value of the integral of f(x) = R  is: " << setprecision(15) << R << "\n" ;
    
    cout << "\nThe total reflecting-power Rtot is: " << setprecision(15) << Rtot <<"         And the percentage of the total power is: " << setprecision(3)<< Rtot*100<<"%" << "\n\n" ;


    // TRapezi
    
    cout << "\n\n                  -------------------- TRAPEZOIDAL-RULE ------------------- \n" ;
    
    double R_trap, R_trap_tot ;
    
    R_trap = ( f(low) + f(up) )/2;
    
    for (int i = 1 ; i < part ; i++) {
        
        R_trap += f(low+ i*(h)) ;
        
    }
    
    R_trap *= h;
    
    R_trap_tot = R_trap + (1-R_trap)*(1-R_trap)*R_trap ;
    
    
    cout << "\nThe value of the integral of f(x) = R  is: " << setprecision(15) << R_trap << "\n" ;
    
    cout << "\nThe total reflecting-power Rtot is: " << setprecision(15) << R_trap_tot <<"         And the percentage of the total power is: " << setprecision(3)<< R_trap_tot*100<<"%" << "\n\n" ;
    
    
// Parabole
    
    cout << "\n\n              ---------------------- CAVALIERI-SIMPSON'S RULE ----------------------- \n" ;
    
    double R_S ; //R_S è la R determinata con questo metodo
    
    R_S = f(low) + f(up) ;
    
    for (int i = 2, j=1; i<= part-2 || j<= part-1; i+=2, j+=2) { //meglio or || , perchè nell' ultimo giro solo la seconda è rispettata , cambiarlo anche più avanti
        
        R_S += 2*f(low+i*h) + 4*f(low+j*h);
        
    }
    
    
    R_S *= h/3;
    
    double Rtot_S ;
    
    Rtot_S = R_S + (1-R_S)*(1-R_S)*R_S ;
    
    
    cout << "\nThe value of the integral of f(x) = R is: " << setprecision(15) << R_S << "\n" ;
    
    cout << "\nThe total reflecting-power Rtot is: " << setprecision(15) << Rtot_S <<"         And the percentage of the total power is: " << setprecision(3)<< Rtot_S*100<<"%" << "\n\n" ;
    


}

double f(double x){
    
    return x*x ;
}


