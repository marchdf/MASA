// -*-c++-*-
//
//-----------------------------------------------------------------------bl-
//--------------------------------------------------------------------------
//
// MASA - Manufactured Analytical Solutions Abstraction Library
//
// Copyright (C) 2010 The PECOS Development Team
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the Version 2.1 GNU Lesser General
// Public License as published by the Free Software Foundation.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc. 51 Franklin Street, Fifth Floor,
// Boston, MA  02110-1301  USA
//
//-----------------------------------------------------------------------el-
// $Author$
// $Id$
//
// ns3d.cpp: program that tests navier-stokes-3d against known source term
//
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------

#include <config.h> // for MASA_STRICT_REGRESSION
#include <masa.h>
#include <math.h>

#include <iostream>
#include <stdlib.h>

using namespace std;
using namespace MASA;

const double pi = acos(-1);
const double threshold = 1.0e-15; // should be small enough to catch any obvious problems

double anQ_p (double x,double y,double z,double p_0,double p_x,double p_y,double p_z,double a_px,double a_py,double a_pz,double L)
{
  double p_an = p_0 + p_x * cos(a_px * pi * x / L) + p_y * sin(a_py * pi * y / L) + p_z * cos(a_pz * pi * z / L);
  return p_an;
}
 
double anQ_u (double x,double y,double z,double u_0,double u_x,double u_y,double u_z,double a_ux,double a_uy,double a_uz,double L)
{
  double u_an = u_0 + u_x * sin(a_ux * pi * x / L) + u_y * cos(a_uy * pi * y / L) + u_z * cos(a_uz * pi * z / L);  
  return u_an;
} 
 
double anQ_v (double x,double y,double z,double v_0,double v_x,double v_y,double v_z,double a_vx,double a_vy,double a_vz,double L)
{
  double v_an = v_0 + v_x * cos(a_vx * pi * x / L) + v_y * sin(a_vy * pi * y / L) + v_z * sin(a_vz * pi * z / L);
  return v_an;
}

double anQ_w (double x,double y,double z,double w_0,double w_x,double w_y,double w_z,double a_wx,double a_wy,double a_wz,double L)
{
  double w_an = w_0 + w_x * sin(a_wx * pi * x / L) + w_y * sin(a_wy * pi * y / L) + w_z * cos(a_wz * pi * z / L);
  return w_an;
}

double anQ_rho (double x,double y,double z,double rho_0,double rho_x,double rho_y,double rho_z,double a_rhox,double a_rhoy,double a_rhoz,double L)
{ 
  double rho_an = rho_0 + rho_x * sin(a_rhox * pi * x / L) + rho_y * cos(a_rhoy * pi * y / L) + rho_z * sin(a_rhoz * pi * z / L);
  return rho_an;
}

double SourceQ_e (
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double);


double SourceQ_u (
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double);


double SourceQ_v (
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double);

double SourceQ_w (
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double);

double SourceQ_rho(
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double,
  double);

int main()
{
  //variables
  double u_0;
  double u_x;
  double u_y;
  double u_z;
  double v_0;
  double v_x;
  double v_y;
  double v_z;
  double w_0;
  double w_x;
  double w_y;
  double w_z;
  double rho_0;
  double rho_x;
  double rho_y;
  double rho_z;
  double p_0;
  double p_x;
  double p_y;
  double p_z;
  double a_px;
  double a_py;
  double a_pz;
  double a_rhox;
  double a_rhoy;
  double a_rhoz;
  double a_ux;
  double a_uy;
  double a_uz;
  double a_vx;
  double a_vy;
  double a_vz;
  double a_wx;
  double a_wy;
  double a_wz;
  double mu;
  double Gamma;
  double L;    
  double k;

  double R;
  double K;    

  // parameters
  double x;
  double y;
  double z;

  // solutions
  double ufield,ufield2,ufield3;
  double vfield,vfield2,vfield3;
  double wfield,wfield2,wfield3;
  double efield,efield2,efield3;
  double rho,rho2,rho3;

  double u_an,u_an2,u_an3;
  double v_an,v_an2,v_an3;
  double w_an,w_an2,w_an3;
  double p_an,p_an2,p_an3;
  double rho_an,rho_an2,rho_an3;

  // initalize
  int nx = 20;             // number of points
  int ny = 10;
  int nz = 30;
  int lx=1;                // length
  int ly=2; 
  int lz=3;     
  double dx=double(lx)/double(nx);
  double dy=double(ly)/double(ny);
  double dz=double(lz)/double(nz);

  masa_init("navier-stokes-test","navierstokes_3d_compressible");

  masa_init_param();

  // check all vars are initialized
  int err = masa_sanity_check();
  if(err != 0)
    {
      cout << "MASA :: Sanity Check Failed!\n";
      exit(1);
    }
  
  // evaluate source terms (3D)
  for(int i=0;i<nx;i++)
    for(int j=0;j<ny;j++)    
      for(int k=0;k<nz;k++)
	{
	  x=i*dx;
	  y=j*dy;
	  z=k*dz;

	  // evalulate source terms
	  ufield = masa_eval_u_source  (x,y,z);
	  vfield = masa_eval_v_source  (x,y,z);
	  wfield = masa_eval_w_source  (x,y,z);
	  efield = masa_eval_e_source  (x,y,z);
	  rho    = masa_eval_rho_source(x,y,z);
	  
	  // evaluate analytical terms
	  u_an = masa_eval_u_an        (x,y,z);
	  v_an = masa_eval_v_an        (x,y,z);
	  w_an = masa_eval_w_an        (x,y,z);
	  p_an = masa_eval_p_an        (x,y,z);
	  rho_an = masa_eval_rho_an    (x,y,z);

	  // check against maple output
	  ufield2   = SourceQ_u  (x,y,z,u_0,u_x,u_y,u_z,v_0,v_x,v_y,v_z,w_0,w_x,w_y,w_z,rho_0,rho_x,rho_y,rho_z,p_0,p_x,p_y,p_z,a_px,a_py,a_pz,a_rhox,a_rhoy,a_rhoz,a_ux,a_uy,a_uz,a_vx,a_vy,a_vz,a_wx,a_wy,a_wz,mu,L,R,K);
	  vfield2   = SourceQ_v  (x,y,z,u_0,u_x,u_y,u_z,v_0,v_x,v_y,v_z,w_0,w_x,w_y,w_z,rho_0,rho_x,rho_y,rho_z,p_0,p_x,p_y,p_z,a_px,a_py,a_pz,a_rhox,a_rhoy,a_rhoz,a_ux,a_uy,a_uz,a_vx,a_vy,a_vz,a_wx,a_wy,a_wz,mu,L,R,K);
	  wfield2   = SourceQ_w  (x,y,z,u_0,u_x,u_y,u_z,v_0,v_x,v_y,v_z,w_0,w_x,w_y,w_z,rho_0,rho_x,rho_y,rho_z,p_0,p_x,p_y,p_z,a_px,a_py,a_pz,a_rhox,a_rhoy,a_rhoz,a_ux,a_uy,a_uz,a_vx,a_vy,a_vz,a_wx,a_wy,a_wz,mu,L,R,K);
	  rho2      = SourceQ_rho(x,y,z,u_0,u_x,u_y,u_z,v_0,v_x,v_y,v_z,w_0,w_x,w_y,w_z,rho_0,rho_x,rho_y,rho_z,p_0,p_x,p_y,p_z,a_px,a_py,a_pz,a_rhox,a_rhoy,a_rhoz,a_ux,a_uy,a_uz,a_vx,a_vy,a_vz,a_wx,a_wy,a_wz,mu,L,R,K);
	  efield2   = SourceQ_e  (x,y,z,u_0,u_x,u_y,u_z,v_0,v_x,v_y,v_z,w_0,w_x,w_y,w_z,rho_0,rho_x,rho_y,rho_z,p_0,p_x,p_y,p_z,a_px,a_py,a_pz,a_rhox,a_rhoy,a_rhoz,a_ux,a_uy,a_uz,a_vx,a_vy,a_vz,a_wx,a_wy,a_wz,mu,Gamma,L,R,K);

	  u_an2     = anQ_u   (x,y,z,u_0,u_x,u_y,u_z,a_ux,a_uy,a_uz,L);
	  cout << "u_an2: " << u_an2 << endl;
	  v_an2     = anQ_v   (x,y,z,v_0,v_x,v_y,v_z,a_vx,a_vy,a_vz,L);
	  w_an2     = anQ_w   (x,y,z,w_0,w_x,w_y,w_z,a_wx,a_wy,a_wz,L);
	  rho_an2   = anQ_rho (x,y,z,rho_0,rho_x,rho_y,rho_z,a_rhox,a_rhoy,a_rhoz,L);
	  p_an2     = anQ_p   (x,y,z,p_0,p_x,p_y,p_z,a_px,a_py,a_pz,L);

	  // test the result is roughly zero
	  // choose between abs and rel error
#ifdef MASA_STRICT_REGRESSION

	  ufield3 = fabs(ufield-ufield2);
	  vfield3 = fabs(vfield-vfield2);
	  wfield3 = fabs(wfield-wfield2);
	  efield3 = fabs(efield-efield2);
	  rho3    = fabs(rho-rho2);

	  u_an3   = fabs(u_an-u_an2);
	  v_an3   = fabs(v_an-v_an2);
	  w_an3   = fabs(w_an-w_an2);
	  rho_an3 = fabs(rho_an-rho_an2);
	  p_an3   = fabs(p_an-p_an2);

#else
	  // adding a hack in the event one of the source terms is zero...

	  ufield3 = fabs(ufield-ufield2)/fabs(ufield2);
	  vfield3 = fabs(vfield-vfield2)/fabs(vfield2);
	  wfield3 = fabs(wfield-wfield2)/fabs(wfield2);
	  efield3 = fabs(efield-efield2)/fabs(efield2);
	  rho3    = fabs(rho-rho2)/fabs(rho2);
 	  cout << "u_an : " << u_an << endl;
	  cout << "u_an2: " << u_an2 << endl;
	  u_an3   = fabs(u_an-u_an2)/fabs(u_an2);
	  v_an3   = fabs(v_an-v_an2)/fabs(v_an2);
	  w_an3   = fabs(w_an-w_an2)/fabs(w_an2);
	  rho_an3 = fabs(rho_an-rho_an2)/fabs(rho_an2);
	  p_an3   = fabs(p_an-p_an2)/fabs(p_an2);
#endif

	  if(ufield3 > threshold)
	    {
	      cout << "\nMASA REGRESSION TEST FAILED: Navier-Stokes (Physical) 3d\n";
	      cout << "U Field Source Term\n";
	      cout << "Exceeded Threshold by: " << ufield3 << endl;
	      cout << x << " " << y << " " << z << endl;
	      exit(1);
	    }

	  if(u_an3 > threshold)
	    {
	      cout << "\nMASA REGRESSION TEST FAILED: Navier-Stokes (Physical) 3d\n";
	      cout << "U Field Analytical Term\n";
	      cout << "Exceeded Threshold by: " << u_an3 << endl;
	      cout << x << " " << y << " " << z << endl;
	      exit(1);
	    }

	  if(vfield3 > threshold)
	    {
	      cout << "\nMASA REGRESSION TEST FAILED: Navier-Stokes (Physical) 3d\n";
	      cout << "V Field Source Term\n";
	      cout << "Exceeded Threshold by: " << vfield3 << endl;
	      cout << x << " " << y << " " << z << endl;
	      exit(1);
	    }
	  
	  if(v_an3 > threshold)
	    {
	      cout << "\nMASA REGRESSION TEST FAILED: Navier-Stokes (Physical) 3d\n";
	      cout << "V Field Analytical Term\n";
	      cout << "Exceeded Threshold by: " << v_an3 << endl;
	      cout << x << " " << y << " " << z << endl;
	      exit(1);
	    }

	  if(wfield3 > threshold)
	    {
	      cout << "\nMASA REGRESSION TEST FAILED: Navier-Stokes (Physical) 3d\n";
	      cout << "W Field Source Term\n";
	      cout << "Exceeded Threshold by: " << wfield3 << endl;
	      cout << x << " " << y << " " << z << endl;
	      exit(1);
	    }
	  
	  if(w_an3 > threshold)
	    {
	      cout << "\nMASA REGRESSION TEST FAILED: Navier-Stokes (Physical) 3d\n";
	      cout << "W Field Analytical Term\n";
	      cout << "Exceeded Threshold by: " << w_an3 << endl;
	      cout << x << " " << y << " " << z << endl;
	      exit(1);
	    }

	  if(efield3 > threshold)
	    {
	      cout << "\nMASA REGRESSION TEST FAILED: Navier-Stokes (Physical) 3d\n";
	      cout << "Energy Source Term\n";
	      cout.precision(16);
	      cout << "Exceeded Threshold by: " << efield3 << endl;
	      cout << "Source term is:                   " << efield2 << endl;
	      cout << "MASA term is:                     " << efield << endl;
	      cout << x << " " << y << " " << z << endl;
	      exit(1);
	    }

	  if(p_an3 > threshold)
	    {
	      cout << "\nMASA REGRESSION TEST FAILED: Navier-Stokes (Physical) 3d\n";
	      cout << "P Field Analytical Term\n";
	      cout << "Exceeded Threshold by: " << p_an3 << endl;
	      cout << x << " " << y << " " << z << endl;
	      exit(1);
	    }

	  if(rho3 > threshold)
	    {
	      cout << "\nMASA REGRESSION TEST FAILED: Navier-Stokes (Physical) 3d\n";
	      cout << "RHO Source Term\n";
	      cout << "Exceeded Threshold by: " << rho3 << endl;
	      cout << x << " " << y << " " << z << endl;
	      exit(1);
	    }

	  if(rho_an3 > threshold)
	    {
	      cout << "\nMASA REGRESSION TEST FAILED: Navier-Stokes (Physical) 3d\n";
	      cout << "RHO Analytical Term\n";
	      cout << "Exceeded Threshold by: " << rho_an3 << endl;
	      cout << x << " " << y << " " << z << endl;
	      exit(1);
	    }

	  // need to add realizability test here

	} // done iterating

  // tests passed
  return 0;
}