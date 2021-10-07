#include "PenningTrap.hpp"
#include "Particle.hpp"


//q = particle_[0].q_;


// Constructor
PenningTrap::PenningTrap(double B0_in, double V0_in, double d_in){
  B0_ = B0_in; // definer disse
  V0_ = V0_in;
  d_ = d_in;
  double ke = 1.38935333 * pow (10 , 5);
  double v0d = 9.65;
}

// Add a particle to the trap
void PenningTrap::add_particle(Particle p_in){
  particles_.push_back(p_in);
}

// External electric field at point r=(x,y,z)
arma::vec PenningTrap::external_E_field(arma::vec r){
  arma::vec E_field = arma::vec(3).fill(0);
  E_field(0) = r(0)*v0d;
  E_field(1) = r(1)*v0d;
  E_field(2) = -2*r(2)*v0d;
  return E_field;

}

// External magnetic field at point r=(x,y,z)
arma::vec PenningTrap::external_B_field(arma::vec r){
  arma::vec B_field = arma::vec(3).fill(0);
  B_field(2) = B0_;
  return B_field;

}

// Force on particle_i from particle_j, ignoring the magnetic forces
arma::vec PenningTrap::force_particle(int i, int j){

  arma::vec qj = particles_[j].q_;
  arma::vec ipos = particles_[i].pos_;
  arma::vec jpos = paraticles_[j].pos_;
  return ke*qj*(ipos - jpos)/(pow(abs(ipos - jpos) , 3));

}

// The total force on particle_i from the external fields
arma::vec PenningTrap::total_force_external(int i){
  // Lorentz force
  double q = particles_[i].q_;
  arma::vec v = particles_[i].vel_;
  arma::vec E = external_E_field(particles_[i].pos_);
  arma::vec B =external_B_field(particles_[i].pos_);
  return q*E + cross(q*v,B);

}

// The total force on particle_i from the other particles
arma::vec PenningTrap::total_force_particles(int i){
  arma::vec total_force_internal = arma::vec(3);
  for(int j=0 ; j<=particles_.size()-1 ; j++){
    total_force_internal += force_particle(i, j);
  }
  return total_force_internal;


}

// The total force on particle_i from both external fields and other particles
arma::vec PenningTrap::total_force(int i){
  arma::vec Fexternal = total_force_external;
  arma::vec Finternal = total_force_particles;
  return Fexternal+Finternal;
}

// Evolve the system one time step (dt) using Runge-Kutta 4th order
void PenningTrap::evolve_RK4(double dt){

}

// Evolve the system one time step (dt) using Euler-Cromer
void PenningTrap::evolve_Euler_Cromer(double dt){
  for (int p = 0; p < particles_.size(); p++){
    arma::vec r = particle_[p].pos_;
    arma::vec v = particle_[p].vel_;
    double m = particle_[p].m_;

    v = v + dt * total_force(p)/m;
    x = x + dt*v;

  }

}
