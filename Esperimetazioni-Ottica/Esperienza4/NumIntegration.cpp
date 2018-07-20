//
//  NumIntegration.cpp
//  
//
//  Created by Simone Azeglio on 07/06/16.
// Il programma integra numericamente la funzione riportata in fondo , funzione trovata nell' esperienza 4 (misura del coefficiente di estinzione) , essa permette poi di calcolare la potenza totale riflessa dal becker (in Pyrex) con n = 1.473
//

#include <stdio.h>
#include <iostream>
#include <math.h>
#include <iomanip>
#include <string>
#include <fstream>

using namespace std;

double f(double x) ; //Funzione da integrare
double seno_inc (double theta_inc);
double coeff_S ( double spessore_becker , double lass, double theta_inc);
double coeff_S_per2_ ( double spessore_becker , double lass, double theta_inc);
void theta_min(double theta_fixed, double lato1 , double lato3[20], double lato2[20], double h_becker, double mm_l[20],double estremo_inf,double for_integral[20], double uprad );
void outfile(double data[],int n) ; // By alessandro.grondona@edu.unito.it



int main()
   {
       double part ; // numero partizioni
       
       double low , up , R , Rtot, h , lowrad , uprad ,lass, spessore_becker; // low = estremo inferiore , up = estr sup , R  = coeff riflessione , Rtot = potenza riflessa totale , lowrad e uprad sono gli estremi convertiti in radianti poichè le funzioni trigonometriche di <math.h> presuppongono un angolo in radianti , lass = lunghezza di assorbimento (discussa nell' ultima parte del main) ; spessore_becker = spessore del becker (HP : 5mm) //
       
       const double pi = 3.1415926535 ; // pi greco per conversione in radianti
       
       const float n = 1.5263 ; //coefficiente rifrazione Pyrex, 0.6552 è il suo inverso, per semplicità e visto che esso è constante, l'ho mantenuto come coefficiente nelle operazioni svolte più in basso --- info : http://refractiveindex.info/?shelf=glass&book=SCHOTT-BK&page=N-BK7
       
       const double k = 1.1003*pow(10,-8); // k è la parte immaginaria dell' indice di rifrazione complesso --- info : http://refractiveindex.info/?shelf=glass&book=SCHOTT-BK&page=N-BK7

       
       const double c = 299792458 ; // velocità luce
       
       const double abs_lenght = 440*pow(10, -9); //lunghezza d'onda di assorbimento
       /* fonte https://books.google.it/books?id=vtZECgAAQBAJ&pg=PA356&lpg=PA356&dq=absorption+length+borosilicate+glass&source=bl&ots=WNjHU7FG2Z&sig=OqaHOCpDsSiAgO6eQ3oqDtCKB5A&hl=en&sa=X&ved=0ahUKEwjq65n89ZbNAhUJKcAKHUf3B9gQ6AEIKTAC#v=onepage&q=absorption%20length%20borosilicate%20glass&f=false */
       
       
       
       cout << "\n                           ============      Exp 4      ============ \n\n" ;
       
       cout << "What is the lower bound? " ;
       cin >> low ;
       
       cout << "What is the upper bound? " ;
       cin >> up ;
       
       cout << "How many partitions do you want to use? " ;
       cin >> part ;
       
       
       cout << "\nEnter becker's thickness (in meters): " ;
       cin >> spessore_becker ;
       
     
       
      
       uprad = (up * pi) / 180.0 ;
       lowrad =  (low * pi)/ 180.0 ;
       
       h =  ( uprad - lowrad ) / part ; //larghezza di ogni partizione
       
        // ----------- Rectangle-rule for numerical integration -----------------//
       
       R =( f(lowrad) + f(uprad) )   ;
       
       
       for (int i = 1 ; i < part ; i++) {
           
           R += 2*f(lowrad+ i*h) ;
           
       }
       
       R *= h/2 ;
       
       // Ora tengo anche conto del secondo (o anche terzo?) raggio riflesso -- Rtot = R + ( 1 - R)^2(R + R^3 + R^5 ...)
       
       Rtot = R + (1-R)*(1-R)*R ;  
       
       cout << "\n\n                  -------------------- RECTANGLE-RULE ------------------- \n" ;
       
       cout << "\nThe value of the integral of f(x) = R  is: " << setprecision(15) << R << "\n" ;
       
       cout << "\nThe total reflecting-power Rtot is: " << setprecision(15) << Rtot <<"         And the percentage of the total power is: " << setprecision(3)<< Rtot*100<<"%" << "\n\n" ;
       
       
       
       
       
       // A questo punto possiamo tenere conto dell' assorbimento della lastra , ad ogni attraversamento va conteggiato un fattore e ^ -(h/cos(xtrasmesso))/lass con h = spessore e l ass = lunghezza di assorbimento --- ipotizzando che h= spessore_becker = 5 mm  (da controllare) , e lass = 1 / coeffass = lambda/ 4*pi*n
       
       cout << "            ___ Approximation with Pyrex's absorption coefficient ___ \n" ;
       
       double coeff=0 , coeff2 ;
       
       
       
       lass = abs_lenght/(4*pi*n*k);

       
        coeff = exp(-(spessore_becker*lass)/(sqrt(1-0.6552*0.6552*(seno_inc(lowrad))*(seno_inc(lowrad))))) + exp( -(spessore_becker*lass)/(sqrt(1-0.6552*0.6552*(seno_inc(uprad))*( seno_inc(uprad) )))) ;
       coeff2 = exp(-2*(spessore_becker*lass)/(sqrt(1-0.6552*0.6552*(seno_inc(lowrad))*(seno_inc(lowrad))))) + exp( -(spessore_becker*lass)/(sqrt(1-0.6552*0.6552*(seno_inc(uprad))*( seno_inc(uprad) )))) ;
       
         for (int i = 1 ; i < part ; i++) {
       
         coeff += exp( -(spessore_becker*lass)/(sqrt(1-0.6552*0.6552*(seno_inc(lowrad+ i*h))*(seno_inc(lowrad+ i*h)))));
             coeff2 += exp( -(spessore_becker*lass)/(sqrt(1-0.6552*0.6552*(seno_inc(lowrad+ i*h))*(seno_inc(lowrad+ i*h)))));
             
             
         }
       
        coeff *= h/2 ;
       coeff2 *=h/2 ;
       

       Rtot = Rtot  + (Rtot*(1-Rtot)*(1-Rtot)*coeff)/(1-Rtot*Rtot*coeff2) - (1-R)*(1-R)*R;
       
       cout << "\nThe total reflecting power (with absorption-correction) Rtot is: " << setprecision(15) << Rtot << "         And the percentage of the total power is: " << setprecision(3)<< Rtot*100<<"%" <<"\n\n" ;
       
       
       
       
       // ************ REGOLA DEI TRAPEZI ***************//
       
       //Viste le possibili instabilità nella successiva approssimazione integrale , provo a inserire tra le due un altro metodo dell' analisi numerica, che va sotto il nome di regola dei trapezi
       
       cout << "\n\n                  -------------------- TRAPEZOIDAL-RULE ------------------- \n" ;
       
       double R_trap, R_trap_tot ;
       
       R_trap = ( f(lowrad) + f(uprad) )/2;
       
       for (int i = 1 ; i < part ; i++) {
           
           R_trap += f(lowrad+ i*(h)) ;
           
       }
       
       R_trap *= h;
       
       R_trap_tot = R_trap + (1-R_trap)*(1-R_trap)*R_trap ;
       
       
       cout << "\nThe value of the integral of f(x) = R  is: " << setprecision(15) << R_trap << "\n" ;
       
       cout << "\nThe total reflecting-power Rtot is: " << setprecision(15) << R_trap_tot <<"         And the percentage of the total power is: " << setprecision(3)<< R_trap_tot*100<<"%" << "\n\n" ;

       
    
       
       
    // Ho pensato di tentare l'approssimazione con un altro algoritmo (più preciso) , che va sotto il nome di metodo delle parabole o di Cavalieri-Simpson , poichè a questo metodo è applicabile una valutazione dell' errore (metodo di Runge-Kutta o di raddoppiamento del passo) che prescinde dall' utilizzo della derivata quarta della funzione (cosa abbastanza difficile da calcolare)
       
       
       //-------------- Cavalieri- Simpson's rule -------------//
       // Per info : https://it.wikipedia.org/wiki/Regola_di_Cavalieri-Simpson
       
        cout << "\n\n              ---------------------- CAVALIERI-SIMPSON'S RULE ----------------------- \n" ;

       double R_S ; //R_S è la R determinata con questo metodo
       
       R_S = f(lowrad) + f(uprad) ;
       
       for (int i = 2, j=1; i<= part-2 || j<= part-1; i+=2, j+=2) { //meglio or || , perchè nell' ultimo giro solo la seconda è rispettata , cambiarlo anche più avanti
           
           R_S += 2*f(lowrad+i*h) + 4*f(lowrad+j*h);
       
        }

       
       R_S *= h/3;
       
       double N1 ;
       
       N1 = R_S ;
       
       
       // Ora tengo anche conto del secondo raggio riflesso -- Rtot = R + ( 1 - R)^2(R + R^3 + R^5 ...)
       
       double Rtot_S ;
       
       Rtot_S = R_S + (1-R_S)*(1-R_S)*R_S ;
       
       
       cout << "\nThe value of the integral of f(x) = R is: " << setprecision(15) << R_S << "\n" ;
       
       cout << "\nThe total reflecting-power Rtot is: " << setprecision(15) << Rtot_S <<"         And the percentage of the total power is: " << setprecision(3)<< Rtot_S*100<<"%" << "\n\n" ;
       
       
       
  
       
       // A questo punto possiamo tenere conto dell' assorbimento della lastra , ad ogni attraversamento va conteggiato un fattore e ^ -(h/cos(xtrasmesso))/lass con h = spessore e l ass = lunghezza di assorbimento --- ipotizzando che h= spessore_becker = 5 mm  (da controllare) , e lass = 1 / coeffass = lambda/ 4*pi*n
       /* Per info sul fattore : https://www.researchgate.net/profile/Jishi_Du/publication/236148001_Reflectivity_and_absorption_coefficient_of_a_borosilicate_glass_during_60Co-g_irradiation_calculated_from_data_measured_by_an_integrating_sphere/links/0046351665577cf633000000.pdf/download?version=vrp */
       
       cout << "                 ___ Approximation with Pyrex's absorption coefficient ___ \n" ;
       
       // Integriamo il fattore che tiene conto della lunghezza di assorbimento con il metodo di Cavalieri-Simpson
       
  
       double coeff_ass_S,coeff_ass_Sper2 ;
       
       coeff_ass_S = coeff_S(spessore_becker,lass,lowrad)+coeff_S(spessore_becker,lass,uprad);
       coeff_ass_Sper2 = coeff_S_per2_(spessore_becker,lass,lowrad)+coeff_S_per2_(spessore_becker,lass,uprad);
       
       for (int i = 2, j=1; i<= part-2 || j<= part-1; i= i+2, j=j+2) {
           
         coeff_ass_S += 2*coeff_S(spessore_becker,lass,lowrad+i*h)+ 4*coeff_S(spessore_becker,lass,lowrad+j*h) ;
           coeff_ass_Sper2 += 2*coeff_S_per2_(spessore_becker,lass,lowrad+i*h) + 4*coeff_S_per2_(spessore_becker,lass,lowrad+j*h);
       }

       double N3 ; //per calcolare errore su fattore (metodo Runge)
       
       coeff_ass_S *= h/3;
       coeff_ass_Sper2 *= h/3;
    
       N3 = coeff_ass_S;
       
       

       
       Rtot_S = N1 + ((R_S*(1-R_S)*(1-R_S)*coeff_ass_S) /(1-R_S*R_S*coeff_ass_Sper2))  ;
       
       cout << "\nThe total reflecting power (with absorption-correction) Rtot is: " << setprecision(15) << Rtot_S << "         And the percentage of the total power is: " << setprecision(3)<< Rtot_S*100<<"%" <<"\n\n" ;
       
       
      
       
       
       
       
       //------------- Runge Error ------------- //
       
       /* Si applica la formula di Cavalieri Simpson una prima volta, poi si dimezza il passo e si riapplica la stessa formula , a questo punto si calcola la differenza tra i due valori (in valore assoluto) e si divide per 15 -- >  err = |N1 -N2| / 15 */
       
       cout << "\n\n                  +++++++++ RUNGE ERROR CALCULATION +++++++++\n" ;
       
        cout << "\n              ----------Error Reflective's power integral----------";
       
       
       double err ;
       
       part /= 2 ;
       
       R_S = f(lowrad) + f(uprad) ;
       
       for (int i = 2, j=1; i<= part-2 || j<= part-1; i= i+2, j=j+2) {
           
           R_S += 2*f(lowrad+i*h) + 4*f(lowrad+j*h);
           
       }
       part *=2;
       
       R_S *= h/3;
       
       
       double N2 ;
       
       N2 = R_S ;
       
       
       
       err = fabs(N1-N2)/15 ;
       
       cout << "\nThe error estimation with Runge algorithm is: "<<setprecision(15)<< err <<"\n\n" << endl ;
       
       
       
       //+++++++++++++++++++++++Runge su fattore assorbimento ++++++++++++++++++++++
       
       
       double err_fatt_assorbimento ;
       
       coeff_ass_S = coeff_S(spessore_becker,lass,lowrad)+coeff_S(spessore_becker,lass,uprad)  ;
       
       for (int i = 2, j=1; i<= part-2 || j<= part-1; i= i+2, j=j+2)
       {
           
        coeff_ass_S += 2*coeff_S(spessore_becker,lass,lowrad+i*h) + 4*coeff_S(spessore_becker,lass,lowrad+j*h) ;
           
       }
       
       double N4 ;
       
      coeff_ass_S *= h/3;
       
       N4 = coeff_ass_S;
       
       err_fatt_assorbimento = fabs(N3-N4)/15 ;
       
        cout << "\n                    ----------Error on absorption coefficient----------";
       
       cout << "\nThe error estimation with Runge algorithm is: "<<setprecision(15)<< err_fatt_assorbimento <<"\n\n" << endl ;
       
       
       // Ora tramite la propagazione degli errori calcoliamo l' errore sulla potenza riflessa
       
       cout<<"\n\n              ************TOTAL ERROR (Propagation of uncertainty)************\n\n";
       
       
       double err_1 ; // E' l'errore sul secondo componente di Rtot_S , esso tiene conto della seconda riflessione e del fattore che ingloba la lunghezza di assorbimento
       
       
       err_1 = sqrt(((((((1-R_S*R_S*coeff_ass_S)*(3*R_S*R_S-4*R_S+1)*coeff_ass_S+2*R_S*coeff_ass_S*R_S*(1-R_S)*(1-R_S)))/(((1-R_S*R_S*coeff_ass_S)*(1-R_S*R_S*coeff_ass_S))))*err)*(((((1-R_S*R_S*coeff_ass_S)*(3*R_S*R_S-4*R_S+1)*coeff_ass_S+2*R_S*coeff_ass_S*R_S*(1-R_S)*(1-R_S)))/(((1-R_S*R_S*coeff_ass_S)*(1-R_S*R_S*coeff_ass_S))))*err))
                    
                    + (((((R_S*(1-R_S)*(1-R_S)*(1-R_S)*(1-R_S)*coeff_ass_S)+R_S*R_S*R_S*(1-R_S)*(1-R_S))/((1-R_S*R_S*coeff_ass_S)*(1-R_S*R_S*coeff_ass_S)))*err_fatt_assorbimento)*((((R_S*(1-R_S)*(1-R_S)*(1-R_S)*(1-R_S)*coeff_ass_S)+R_S*R_S*R_S*(1-R_S)*(1-R_S))/((1-R_S*R_S*coeff_ass_S)*(1-R_S*R_S*coeff_ass_S)))*err_fatt_assorbimento))) ;
       
       double err_tot ; // Somma tramite propagazione degli errori del primo fattore di R_S e di err_1
       
       err_tot = sqrt(err*err+err_1*err_1);
       
       cout<<"\nThe final error on R (reflective power), is: "<<err_tot<< "--------> Then, in percentage: "<<setprecision(3)<<err_tot*100<<"%\n\n"<<endl ;
       
       
       
       
       
            //***********************************************************************************//
       
       
       
       
       
       
           //------------------------------------PARTE 2 ------------------------------------ //
       
       cout<<"\n\n                  _________________________________________PART 2_________________________________________\n\n\n";
       
       // A questo punto modificherò l'estremo inferiore del mio integrale poichè il liquido nel becker viene aggiunto gradualmente di 100ml in 100ml per i primi m passi e successivamente di 50ml in 50 ml per poi ritornare a passi di 100ml e passare a passi di 200ml fino al riempimento del becker //
       
       const double h_becker = 185;
       
       double  theta_fixed, lato1=87.5 ; //mm_l[] associa l'altezza del liquido per ogni aggiunta fatta nel becker; mL_l[] associa la quantità di liquido per ogni aggiunta fatta nel becker ; theta_fixed corrisponde all' angolo tra il raggio incidente (che colpisce l' orlo del becker) e la superficie laterale del becker, lato2 è il "lato" del triangolo che collega sorgente a altezza liquido ; lato1 è il lato che misura 87 mm -- collega sorgente e orlo becker;   //
       
      double mm_l[20] = {0, 9.93, 17.65, 24.90, 28.52, 32.96, 37.30, 40.98, 44.59, 48.60, 52.87, 56.59, 58.44, 62.82, 69.87, 76.67, 82.81, 99.66, 115.16, 121.68}; //tutto in mm
       
       double mL_l[20] = {0, 100, 200, 300, 350, 400, 450, 500, 550, 600, 650, 700, 750, 800, 900, 1000, 1100, 1200,1300, 1400} ;
       
       theta_fixed = pi - uprad  ; // è in radianti
       
       double lato2[20];
       double lato3[20] ;
       double estremo_inf ; // estremo inferiore integrale
       double for_integral[20]; //array con i valori di theta min vedi funzione theta_min
       
       cout<<"                                                +++++++++Assegnazione θmin+++++++++\n\n";
       
    
       theta_min(theta_fixed ,lato1, lato3, lato2,  h_becker, mm_l,estremo_inf,for_integral,uprad) ;
       
       // Ora abbiamo un elenco con i vari estremi inferiori , a questo punto calcoliamo i valori di R per ogni altezza del liquido
       
       
       cout<<"\n\n\n                    +++++++++++++++++++++Potenza riflessa finale+++++++++++++++++++++\n\n" ;
       
       
       double Result[20] ; //Array che associa risultato dell' integrale a ogni theta min
       double Result_tot[20] ; //Array che associa risultato dell' integrale a ogni theta min e delle prime due riflessioni
       double N5, N6 , N7, N8; //valori per runge kutta ; N5 e N6 per R , N7 e N8 per coeff_abs
       
       double err_2 , err_3, err_4, final_error ; //errori
       
       coeff_ass_S = 0 ;
       coeff_ass_Sper2 = 0 ;
       h=0 ; 
       
       //Calcolo dei vari integrali
       
       for (int  k=0; k<20; k++ ){
           
           
       
     Result[k] = f(for_integral[k]) + f(uprad) ;
           
           h = (uprad - for_integral[k])/part ;
           
           coeff_ass_S = coeff_S(spessore_becker,lass,for_integral[k])+coeff_S(spessore_becker,lass,uprad)  ;
           
           coeff_ass_Sper2 = coeff_S_per2_(spessore_becker,lass,for_integral[k])+coeff_S_per2_(spessore_becker,lass,uprad)  ;
      
       
       for (int i = 2, j=1; i<= part-2 || j<= part-1 ; i= i+2, j=j+2) {
           
           Result[k] += 2*f(for_integral[k]+i*h) + 4*f(for_integral[k]+j*h);
           
           coeff_ass_S += 2*coeff_S(spessore_becker,lass,for_integral[k]+i*h) + 4*coeff_S(spessore_becker,lass,for_integral[k]+j*h);
           
           coeff_ass_Sper2 += 2*coeff_S_per2_(spessore_becker,lass,for_integral[k]+i*h) + 4*coeff_S_per2_(spessore_becker,lass,for_integral[k]+j*h) ;
           
       }
           Result[k]*=h/3 ;
           
           coeff_ass_S *=h/3 ;
         
           
           
           coeff_ass_Sper2 *=h/3 ;
           
        
           Result_tot[k] = Result[k] +  (((1-Result[k])*(1-Result[k])*Result[k]*coeff_ass_S)/(1-Result[k]*Result[k]*coeff_ass_Sper2)) ;
           
           
           cout << k<<". "<<"The total reflecting power R["<<k<<"] is: " << setprecision(5) << Result_tot[k]<<"         And the percentage of the total power is: " << setprecision(3)<< Result_tot[k]*100<<"%" ;
           
           // Ricalcolo con metà numero di partizioni per errore
           
           N5 = Result[k] ;
           N7 = coeff_ass_S ;
           
           part /=2 ;
           
           Result[k] = f(for_integral[k]) + f(uprad) ;
           
           h = (uprad - for_integral[k])/part ;
           
           coeff_ass_S = coeff_S(spessore_becker,lass,for_integral[k])+coeff_S(spessore_becker,lass,uprad);
           coeff_ass_Sper2 = coeff_S_per2_(spessore_becker,lass,for_integral[k])+coeff_S_per2_(spessore_becker,lass,uprad)  ;
           
           
           for (int i = 2, j=1; i<= part-2 || j<= part-1 ; i= i+2, j=j+2) {
               
               Result[k] += 2*f(for_integral[k]+i*h) + 4*f(for_integral[k]+j*h);
               
               coeff_ass_S += 2*coeff_S(spessore_becker,lass,for_integral[k]+i*h) + 4*coeff_S(spessore_becker,lass,for_integral[k]+j*h);
               
               coeff_ass_Sper2 += 2*coeff_S_per2_(spessore_becker,lass,for_integral[k]+i*h) + 4*coeff_S_per2_(spessore_becker,lass,for_integral[k]+j*h) ;
               
           }

           Result[k]*=h/3 ;
           
           coeff_ass_S *=h/3 ;
           
           coeff_ass_Sper2 *=h/3 ;
           
          N6 = Result[k] ;
          N8 = coeff_ass_S ;
           
           err_2 = fabs(N5-N6)/15 ;
           err_3 = fabs(N7-N8)/15 ;
           
           
           err_4 = sqrt(((((((1-Result[k]*Result[k]*coeff_ass_S)*(3*Result[k]*Result[k]-4*Result[k]+1)*coeff_ass_S+2*Result[k]*coeff_ass_S*Result[k]*(1-Result[k])*(1-Result[k])))/(((1-Result[k]*Result[k]*coeff_ass_S)*(1-Result[k]*Result[k]*coeff_ass_Sper2))))*err_2)*(((((1-Result[k]*Result[k]*coeff_ass_S)*(3*Result[k]*Result[k]-4*Result[k]+1)*coeff_ass_S+2*Result[k]*coeff_ass_S*Result[k]*(1-Result[k])*(1-Result[k])))/(((1-Result[k]*Result[k]*coeff_ass_S)*(1-Result[k]*Result[k]*coeff_ass_Sper2))))*err_2))
                        +
                        
                        (((((Result[k]*(1-Result[k])*(1-Result[k])*(1-Result[k])*(1-Result[k])*coeff_ass_S)+Result[k]*Result[k]*Result[k]*(1-Result[k])*(1-Result[k]))/((1-Result[k]*Result[k]*coeff_ass_S)*(1-Result[k]*Result[k]*coeff_ass_Sper2)))*err_3)*((((Result[k]*(1-Result[k])*(1-Result[k])*(1-Result[k])*(1-Result[k])*coeff_ass_S)+Result[k]*Result[k]*Result[k]*(1-Result[k])*(1-Result[k]))/((1-Result[k]*Result[k]*coeff_ass_S)*(1-Result[k]*Result[k]*coeff_ass_Sper2)))*err_3))) ;
           
           final_error = sqrt(err_2*err_2+err_4*err_4);
           
           
           cout<<" ± "<<final_error*100<<"%"<< endl ;
           
           part *=2 ; //Ristabiliamo part al valore iniziale poichè nella prima parte del calcolo dell' errore lo avevamo dimezzato
       
       }
       
      
       

   cout<<"\n\n";
  
       outfile( Result_tot, 20) ;
       // outfile( [], 20)
       
       
   }

// funzione da integrare
/* Per info : https://en.wikipedia.org/wiki/Fresnel_equations#Power_or_intensity_equations */

double f ( double x){
    
    return 0.5* (((cos(x)-1.5263*sqrt(1-0.6552*sin(x)*0.6552*sin(x)))/(cos(x)+1.5263*sqrt(1-0.6552*sin(x)*0.6552*sin(x)))) * ((cos(x)-1.5263*sqrt(1-0.6552*sin(x)*0.6552*sin(x)))/(cos(x)+1.5263*sqrt(1-0.6552*sin(x)*0.6552*sin(x))))
                  
                  + ((((sqrt(1-0.6552*sin(x)*0.6552*sin(x))-1.5263*cos(x))/(sqrt(1-0.6552*sin(x)*0.6552*sin(x))+1.5263*cos(x))))
    
       
       *((sqrt(1-0.6552*sin(x)*0.6552*sin(x))-1.5263*cos(x))/(sqrt(1-0.6552*sin(x)*0.6552*sin(x))+1.5263*cos(x))))) ;
    
    
    // ???Si moltiplica tutto per 2pi poichè in simmetria cilindrica l angolo che mi definisce la superficie laterale viene coperto del tutto ; Devo infatti dare il contributo di ogni circonferenza infinitesima colpita dalla luce???chiedere ma non penso
    
    
    /*(((tan(x - asin(0.679*sin(x)))*
       tan(x - asin(0.679*sin(x))))
      / (tan(x + asin(0.679*sin(x)))
         *tan(x + asin(0.679*sin(x))))) +
     ((sin(x - asin(0.679*sin(x)))*
       sin(x - asin(0.679*sin(x))))
      / (sin(x + asin(0.679*sin(x)))
         *sin(x + asin(0.679*sin(x)))))) ;*/

}

double seno_inc (double theta_inc){
    
    return sin(theta_inc) ; }



//Funzione che tiene conto della lunghezza di assorbimento del Pyrex


double coeff_S ( double spessore_becker , double lass, double theta_inc){
    
    return  exp( -(spessore_becker*lass)/(sqrt(1-0.6552*0.6552*(sin(theta_inc))*(sin(theta_inc))))) ;
    
}

double coeff_S_per2_( double spessore_becker , double lass, double theta_inc){
    
    return  exp( -2*(spessore_becker*lass)/(sqrt(1-0.6552*0.6552*(sin(theta_inc))*(sin(theta_inc))))) ;
    
}


void theta_min(double theta_fixed, double lato1 , double lato3[20], double lato2[20], double h_becker, double mm_l[20],double estremo_inf, double for_integral[20],double uprad){
    
    
    for(int i=0; i<20; i++){
        
        lato3[i] = h_becker - mm_l[i];
        
        lato2[i] = sqrt(lato1*lato1 + lato3[i]*lato3[i] -2*lato1*lato3[i]*cos(theta_fixed)); // in mm
        
        estremo_inf =  uprad - asin((lato3[i]/lato2[i])*sin(theta_fixed)) ;
        
        for_integral[i] = uprad -  asin((lato3[i]/lato2[i])*sin(theta_fixed));
        
        cout<<i<<". "<<"La distanza dall' orlo all' altezza del liquido è: " <<lato3[i]<<" mm" ;
        cout <<"\t\tL'estremo inferiore di integrazione (θmin) è: "<<estremo_inf<<" rad"; ;
        cout<<"\n" ;
        
        
        
    }

    cout<<"\n\n"<<endl;
    
}

//Crea un file in cui scrive i dati dell'array passato.
//Vuole: array dati, numero dati.
void outfile(double data[],int n){
    string name;
    cout<<"Nome da dare al file (con estensione): ";
    cin>>name;
    ofstream filedati(name.c_str());
    for (int i=0;i<n;i++)
        filedati<<data[i]<<endl;
    filedati<<"\n";
    filedati.close();
    return;
}

