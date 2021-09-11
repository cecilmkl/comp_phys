#include <iostream>
#include <cmath>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <armadillo>
using namespace std;

double f(double x); ///    BRUKE Denne?
arma::vec general_algorithm(arma::vec a, arma::vec b, arma::vec c, arma::vec g, int n);


int main(int argc, const char * argv[]) {

<<<<<<< HEAD
=======
    if (argc != 2)
    {
      // Get the name of the executable file
      std::string executable_name = argv[0];

      std::cerr << "Error: Wrong number of input arguments." << std::endl;
      std::cerr << "Usage: " << executable_name << " <integer number of steps>" << std::endl;
      return 1;
    }
    int n = 15; // legg inn atoi !!!!!!
    // int n = atoi(argv[1]);
>>>>>>> f881e16d76e4f86a12e249c3e364f68a06c6b450
    int i;

    arma::vec u = arma::vec(n+1);
    arma::vec x = arma::vec(n+1);
    double x_min = 0.0;
    double x_max = 1.0;
    double h = (x_max - x_min) / n;
    // Boundary conditions:
    double u_0 = 0; // u(0) = 0 // nye navn?
    double u_1 = 0;  // u(1)=0

    int width = 12;
    int prec = 4;

    //opening file
    ofstream ofile;
    ofile.open ("data.txt");

    //setting up the x-array and the solutions to the function u, and printing it to file

    for (i=0 ; i <= n ; i++){

        x(i) = h*i;
        u(i) = 1 - (1 - exp(-10)) * x(i) - exp(-10 * x(i));
        ofile << setw(width) << setprecision(prec) << scientific << x(i)
              << setw(width) << setprecision(prec) << scientific << u(i) << endl;

    }
    //close file
    ofile.close();


    // Problem 7
    n = n-1; // now letting

    arma::vec a = arma::vec(n).fill(-1.);
    arma::vec b = arma::vec(n).fill(2.);
    arma::vec c = arma::vec(n).fill(-1.);

    // Making sure a and c only have n-1 values, but corresponding indices
    a(0) = 0.;
    c(n-1) = 0.;


    // Defining the g vector:
    arma::vec g = arma::vec(n);
    g(0) = h*h*100*exp(-10*x(1)) + u_0; // h^2*f1 + u(0)
    g(n-1) = h*h*100*exp(-10*x(n)) + u_1; // h^2*fn + u(1)

    for (int i = 1; i <= n-2; i++){
      g(i) = h*h*100*exp(-10*x(i+1));
    }

    arma::vec v = general_algorithm(a,b,c,g,n);


    //opening file
    ofstream ofile2;
    ofile2.open ("approx_general.txt");

    //setting up the x-array and the solutions to the function u, and printing it to file
    for (i=0 ; i <= n-1 ; i++){
        ofile2 << setw(width) << setprecision(prec) << scientific << x(i+1)
              << setw(width) << setprecision(prec) << scientific << v(i) << endl;
    }
    //close file
    ofile2.close();

    return 0;
}

arma::vec general_algorithm(arma::vec a, arma::vec b, arma::vec c, arma::vec g, int n){

    // Helpful new variables
    arma::vec btilde = arma::vec(n);
    arma::vec gtilde = arma::vec(n);
    btilde(0) = b(0);
    gtilde(0) = g(0);

    arma::vec v = arma::vec(n); // solution vector
    double tmp; // variable to reduce FLOPs

    for (int i = 1; i <= n - 1; i++){
      tmp = a(i) / btilde(i-1);
      btilde(i) = b(i) - tmp * c(i-1) ;
      gtilde(i) = g(i) - tmp * gtilde(i-1);
    }

    v(n-1) = gtilde(n-1) / btilde(n-1); // Last element can now be found directly

    for (int j = n-2; j >= 0; j--){ // n-1 elements
      v(j) = (gtilde(j) - (c(j) * v(j+1))) / btilde(j);
    }
    return v;

}

double f(double x){
  return 100*exp(-10*x);
}
