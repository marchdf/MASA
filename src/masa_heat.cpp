 /*--------------------------------------------------------------------------
  *--------------------------------------------------------------------------
  *
  * Copyright (C) 2010 The PECOS Development Team
  *
  * Please see http://pecos.ices.utexas.edu for more information.
  *
  * This file is part of MASA.
  *
  * MASA is free software: you can redistribute it and/or modify it under
  * the terms of the GNU Lesser General Public License as published by the Free
  * Software Foundation, either version 3 of the License, or (at your option)
  * any later version.
  *
  * MASA is distributed in the hope that it will be useful, but WITHOUT ANY
  * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
  * FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more
  * details.
  *
  * You should have received a copy of the GNU Lesser General Public License along 
  * with MASA.  If not, see <http://www.gnu.org/licenses/>.
  *
  *--------------------------------------------------------------------------
  
  MASA -- Manufactured Analytical Solutions Abstraction Library

  A software interface that provides access to all manufactured solutions to 
  be used by various models throughout the center.
  
  *--------------------------------------------------------------------------
  */  

//
//   These are the MASA class member functions and constructors
//   For the HEAT EQUATION

#include <masa_internal.h> 

using namespace MASA;

/* ------------------------------------------------
 *
 *         HEAT EQUATION
 *
 *   steady -- constant coeff
 *
 * -----------------------------------------------
 */ 

MASA::heateq_1d_steady_const::heateq_1d_steady_const()
{
    mmsname = "heateq_1d_steady_const";
    dimension=1;

    register_var("A_x",&A_x);   
    register_var("k_0",&k_0);

}//done with constructor

void MASA::heateq_1d_steady_const::init_var()
{

}

double MASA::heateq_1d_steady_const::eval_q_t(double x)
{
  double Q_T;
  Q_T = A_x * A_x * k_0 * cos(A_x * x);
  return Q_T;
}

double MASA::heateq_1d_steady_const::eval_an(double x)
{
  double T_an;
  T_an = cos(A_x * x);
  return T_an;
}

MASA::heateq_2d_steady_const::heateq_2d_steady_const()
{
    mmsname = "heateq_2d_steady_const";
    dimension=2;

    register_var("A_x",&A_x);   
    register_var("k_0",&k_0);
    register_var("B_y",&B_y);
    
}//done with constructor

void MASA::heateq_2d_steady_const::init_var()
{

} // done with variable initializer

double MASA::heateq_2d_steady_const::eval_q_t(double x,double y)
{
  double Q_T = k_0 * cos(A_x * x) * cos(B_y * y) * (A_x * A_x + B_y * B_y);
  return Q_T;
}


MASA::heateq_3d_steady_const::heateq_3d_steady_const()
{
    mmsname = "heateq_3d_steady_const";
    dimension=3;

    register_var("A_x",&A_x);   
    register_var("k_0",&k_0);
    register_var("B_y",&B_y);
    register_var("C_z",&C_z);

}//done with constructor

void MASA::heateq_3d_steady_const::init_var()
{

} // done with variable initializer

double MASA::heateq_3d_steady_const::eval_q_t(double x,double y,double z)
{
  double Q_T = k_0 * cos(A_x * x) * cos(B_y * y) * cos(C_z * z) * (A_x * A_x + B_y * B_y + C_z * C_z);
  return Q_T;
}


/* ------------------------------------------------
 *
 *         HEAT EQUATION
 *
 *   Unsteady -- Const Coeff
 *
 * -----------------------------------------------
 */ 

MASA::heateq_1d_unsteady_const::heateq_1d_unsteady_const()
{
  mmsname = "heateq_1d_unsteady_const";
  dimension=1;

  register_var("A_x",&A_x);   
  register_var("k_0",&k_0);
  register_var("D_t",&D_t);
  register_var("cp_0",&cp_0);
  register_var("A_t",&A_t);
  register_var("rho",&rho);

}//done with constructor

void MASA::heateq_1d_unsteady_const::init_var()
{

} // done with variable initializer

double MASA::heateq_1d_unsteady_const::eval_q_t(double x,double t)
{
  double Q_T = cos(A_x * x + A_t * t) * cos(D_t * t) * k_0 * A_x * A_x - (sin(A_x * x + A_t * t) * cos(D_t * t) * A_t + cos(A_x * x + A_t * t) * sin(D_t * t) * D_t) * rho * cp_0;
  return Q_T;
}


MASA::heateq_2d_unsteady_const::heateq_2d_unsteady_const()
{
  mmsname = "heateq_2d_unsteady_const";
  dimension=2;
    
  register_var("A_x",&A_x);   
  register_var("k_0",&k_0);
  register_var("D_t",&D_t);
  register_var("cp_0",&cp_0);
  register_var("A_t",&A_t);
  register_var("rho",&rho);
  register_var("B_y",&B_y);
  register_var("B_t",&B_t);

}//done with constructor

double MASA::heateq_2d_unsteady_const::eval_q_t(double x,double y, double t)
{
  double Q_T = -(sin(A_x * x + A_t * t) * cos(B_y * y + B_t * t) * cos(D_t * t) * A_t + cos(A_x * x + A_t * t) * sin(B_y * y + B_t * t) * cos(D_t * t) * B_t + cos(A_x * x + A_t * t) * cos(B_y * y + B_t * t) * sin(D_t * t) * D_t) * rho * cp_0 + (A_x * A_x + B_y * B_y) * cos(A_x * x + A_t * t) * cos(B_y * y + B_t * t) * cos(D_t * t) * k_0;
  return Q_T;
}

MASA::heateq_3d_unsteady_const::heateq_3d_unsteady_const()
{
  mmsname = "heateq_3d_unsteady_const";
  dimension=3;
  
  register_var("A_x",&A_x);   
  register_var("k_0",&k_0);
  register_var("D_t",&D_t);
  register_var("cp_0",&cp_0);
  register_var("A_t",&A_t);
  register_var("rho",&rho);
  register_var("B_y",&B_y);
  register_var("B_t",&B_t);
  register_var("C_z",&C_z);
  register_var("C_t",&C_t);

}//done with constructor

void MASA::heateq_3d_unsteady_const::init_var()
{

} // done with variable initializer

double MASA::heateq_3d_unsteady_const::eval_q_t(double x,double y, double z,double t)
{
  double Q_T = -(sin(A_x * x + A_t * t) * cos(B_y * y + B_t * t) * cos(C_z * z + C_t * t) * cos(D_t * t) * A_t + cos(A_x * x + A_t * t) * sin(B_y * y + B_t * t) * cos(C_z * z + C_t * t) * cos(D_t * t) * B_t + cos(A_x * x + A_t * t) * cos(B_y * y + B_t * t) * sin(C_z * z + C_t * t) * cos(D_t * t) * C_t + cos(A_x * x + A_t * t) * cos(B_y * y + B_t * t) * cos(C_z * z + C_t * t) * sin(D_t * t) * D_t) * rho * cp_0 + (A_x * A_x + B_y * B_y + C_z * C_z) * cos(A_x * x + A_t * t) * cos(B_y * y + B_t * t) * cos(C_z * z + C_t * t) * cos(D_t * t) * k_0;
  return Q_T;
}

/* ------------------------------------------------
 *
 *         HEAT EQUATION
 *
 *   Unsteady -- Variable Coef
 *
 * -----------------------------------------------
 */ 

MASA::heateq_1d_unsteady_var::heateq_1d_unsteady_var()
{
  mmsname = "heateq_1d_unsteady_var";
  dimension=1;

  register_var("A_x",&A_x);   
  register_var("k_0",&k_0);
  register_var("D_t",&D_t);
  register_var("cp_0",&cp_0);
  register_var("A_t",&A_t);
  register_var("rho",&rho);
  register_var("cp_1",&cp_1);
  register_var("cp_2",&cp_2);
  register_var("k_1",&k_1);
  register_var("k_2",&k_2);

}//done with constructor

void MASA::heateq_1d_unsteady_var::init_var()
{

} // done with variable initializer

double MASA::heateq_1d_unsteady_var::eval_q_t(double x, double t)
{
  double Q_T = -pow(cos(D_t * t), 0.2e1) * A_x * A_x * k_1 + 0.3e1 * pow(cos(A_x * x + A_t * t), 0.3e1) * pow(cos(D_t * t), 0.3e1) * A_x * A_x * k_2 - sin(A_x * x + A_t * t) * cos(D_t * t) * A_t * rho * cp_0 - cos(A_x * x + A_t * t) * sin(D_t * t) * D_t * rho * cp_0 + (A_x * A_x * k_0 - 0.2e1 * pow(cos(D_t * t), 0.2e1) * A_x * A_x * k_2 - sin(A_x * x + A_t * t) * cos(D_t * t) * A_t * rho * cp_1 - cos(A_x * x + A_t * t) * sin(D_t * t) * D_t * rho * cp_1) * cos(A_x * x + A_t * t) * cos(D_t * t) + (0.2e1 * A_x * A_x * k_1 - sin(A_x * x + A_t * t) * cos(D_t * t) * A_t * rho * cp_2 - cos(A_x * x + A_t * t) * sin(D_t * t) * D_t * rho * cp_2) * pow(cos(A_x * x + A_t * t), 0.2e1) * pow(cos(D_t * t), 0.2e1);
  return Q_T;
}

MASA::heateq_2d_unsteady_var::heateq_2d_unsteady_var()
{
  mmsname = "heateq_2d_unsteady_var";
  dimension=2;

  register_var("A_x",&A_x);   
  register_var("k_0",&k_0);
  register_var("D_t",&D_t);
  register_var("cp_0",&cp_0);
  register_var("A_t",&A_t);
  register_var("rho",&rho);
  register_var("cp_1",&cp_1);
  register_var("cp_2",&cp_2);
  register_var("k_1",&k_1);
  register_var("k_2",&k_2);
  register_var("B_y",&B_y);
  register_var("B_t",&B_t);

}//done with constructor

void MASA::heateq_2d_unsteady_var::init_var()
{

} // done with variable initializer

double MASA::heateq_2d_unsteady_var::eval_q_t(double x,double y,double t)
{
  double Q_T = -pow(cos(B_y * y + B_t * t), 0.2e1) * pow(cos(D_t * t), 0.2e1) * A_x * A_x * k_1 - sin(A_x * x + A_t * t) * cos(B_y * y + B_t * t) * cos(D_t * t) * A_t * rho * cp_0 - pow(cos(A_x * x + A_t * t), 0.2e1) * pow(cos(D_t * t), 0.2e1) * B_y * B_y * k_1 - cos(A_x * x + A_t * t) * sin(B_y * y + B_t * t) * cos(D_t * t) * B_t * rho * cp_0 - cos(A_x * x + A_t * t) * cos(B_y * y + B_t * t) * sin(D_t * t) * D_t * rho * cp_0 + 0.3e1 * pow(cos(A_x * x + A_t * t), 0.3e1) * pow(cos(B_y * y + B_t * t), 0.3e1) * pow(cos(D_t * t), 0.3e1) * (A_x * A_x + B_y * B_y) * k_2 + (0.2e1 * A_x * A_x * k_1 - sin(A_x * x + A_t * t) * cos(B_y * y + B_t * t) * cos(D_t * t) * A_t * rho * cp_2 + 0.2e1 * B_y * B_y * k_1 - cos(A_x * x + A_t * t) * sin(B_y * y + B_t * t) * cos(D_t * t) * B_t * rho * cp_2 - cos(A_x * x + A_t * t) * cos(B_y * y + B_t * t) * sin(D_t * t) * D_t * rho * cp_2) * pow(cos(A_x * x + A_t * t), 0.2e1) * pow(cos(B_y * y + B_t * t), 0.2e1) * pow(cos(D_t * t), 0.2e1) + (A_x * A_x * k_0 - 0.2e1 * pow(cos(B_y * y + B_t * t), 0.2e1) * pow(cos(D_t * t), 0.2e1) * A_x * A_x * k_2 - sin(A_x * x + A_t * t) * cos(B_y * y + B_t * t) * cos(D_t * t) * A_t * rho * cp_1 + B_y * B_y * k_0 - 0.2e1 * pow(cos(A_x * x + A_t * t), 0.2e1) * pow(cos(D_t * t), 0.2e1) * B_y * B_y * k_2 - cos(A_x * x + A_t * t) * sin(B_y * y + B_t * t) * cos(D_t * t) * B_t * rho * cp_1 - cos(A_x * x + A_t * t) * cos(B_y * y + B_t * t) * sin(D_t * t) * D_t * rho * cp_1) * cos(A_x * x + A_t * t) * cos(B_y * y + B_t * t) * cos(D_t * t);
  return Q_T;
}

MASA::heateq_3d_unsteady_var::heateq_3d_unsteady_var()
{
  mmsname = "heateq_3d_unsteady_var";
  dimension=3;

  register_var("A_x",&A_x);   
  register_var("k_0",&k_0);
  register_var("D_t",&D_t);
  register_var("cp_0",&cp_0);
  register_var("A_t",&A_t);
  register_var("rho",&rho);
  register_var("cp_1",&cp_1);
  register_var("cp_2",&cp_2);
  register_var("k_1",&k_1);
  register_var("k_2",&k_2);
  register_var("B_y",&B_y);
  register_var("B_t",&B_t);
  register_var("C_z",&C_z);
  register_var("C_t",&C_t);

}//done with constructor

void MASA::heateq_3d_unsteady_var::init_var()
{

} // done with variable initializer

double MASA::heateq_3d_unsteady_var::eval_q_t(double x,double y,double z,double t)
{
  double Q_T = -sin(A_x * x + A_t * t) * cos(B_y * y + B_t * t) * cos(C_z * z + C_t * t) * cos(D_t * t) * rho * cp_0 * A_t - cos(A_x * x + A_t * t) * sin(B_y * y + B_t * t) * cos(C_z * z + C_t * t) * cos(D_t * t) * rho * cp_0 * B_t - cos(A_x * x + A_t * t) * cos(B_y * y + B_t * t) * sin(C_z * z + C_t * t) * cos(D_t * t) * rho * cp_0 * C_t - cos(A_x * x + A_t * t) * cos(B_y * y + B_t * t) * cos(C_z * z + C_t * t) * sin(D_t * t) * rho * cp_0 * D_t - pow(cos(B_y * y + B_t * t), 0.2e1) * pow(cos(C_z * z + C_t * t), 0.2e1) * pow(cos(D_t * t), 0.2e1) * k_1 * A_x * A_x - pow(cos(A_x * x + A_t * t), 0.2e1) * pow(cos(C_z * z + C_t * t), 0.2e1) * pow(cos(D_t * t), 0.2e1) * k_1 * B_y * B_y - pow(cos(A_x * x + A_t * t), 0.2e1) * pow(cos(B_y * y + B_t * t), 0.2e1) * pow(cos(D_t * t), 0.2e1) * k_1 * C_z * C_z + 0.3e1 * pow(cos(A_x * x + A_t * t), 0.3e1) * pow(cos(B_y * y + B_t * t), 0.3e1) * pow(cos(C_z * z + C_t * t), 0.3e1) * pow(cos(D_t * t), 0.3e1) * (A_x * A_x + B_y * B_y + C_z * C_z) * k_2 + (-sin(A_x * x + A_t * t) * cos(B_y * y + B_t * t) * cos(C_z * z + C_t * t) * cos(D_t * t) * rho * cp_1 * A_t - cos(A_x * x + A_t * t) * sin(B_y * y + B_t * t) * cos(C_z * z + C_t * t) * cos(D_t * t) * rho * cp_1 * B_t - cos(A_x * x + A_t * t) * cos(B_y * y + B_t * t) * sin(C_z * z + C_t * t) * cos(D_t * t) * rho * cp_1 * C_t - cos(A_x * x + A_t * t) * cos(B_y * y + B_t * t) * cos(C_z * z + C_t * t) * sin(D_t * t) * rho * cp_1 * D_t + k_0 * A_x * A_x + k_0 * B_y * B_y + k_0 * C_z * C_z - 0.2e1 * pow(cos(B_y * y + B_t * t), 0.2e1) * pow(cos(C_z * z + C_t * t), 0.2e1) * pow(cos(D_t * t), 0.2e1) * k_2 * A_x * A_x - 0.2e1 * pow(cos(A_x * x + A_t * t), 0.2e1) * pow(cos(C_z * z + C_t * t), 0.2e1) * pow(cos(D_t * t), 0.2e1) * k_2 * B_y * B_y - 0.2e1 * pow(cos(A_x * x + A_t * t), 0.2e1) * pow(cos(B_y * y + B_t * t), 0.2e1) * pow(cos(D_t * t), 0.2e1) * k_2 * C_z * C_z) * cos(A_x * x + A_t * t) * cos(B_y * y + B_t * t) * cos(C_z * z + C_t * t) * cos(D_t * t) + (-sin(A_x * x + A_t * t) * cos(B_y * y + B_t * t) * cos(C_z * z + C_t * t) * cos(D_t * t) * rho * cp_2 * A_t - cos(A_x * x + A_t * t) * sin(B_y * y + B_t * t) * cos(C_z * z + C_t * t) * cos(D_t * t) * rho * cp_2 * B_t - cos(A_x * x + A_t * t) * cos(B_y * y + B_t * t) * sin(C_z * z + C_t * t) * cos(D_t * t) * rho * cp_2 * C_t - cos(A_x * x + A_t * t) * cos(B_y * y + B_t * t) * cos(C_z * z + C_t * t) * sin(D_t * t) * rho * cp_2 * D_t + 0.2e1 * k_1 * A_x * A_x + 0.2e1 * k_1 * B_y * B_y + 0.2e1 * k_1 * C_z * C_z) * pow(cos(A_x * x + A_t * t), 0.2e1) * pow(cos(B_y * y + B_t * t), 0.2e1) * pow(cos(C_z * z + C_t * t), 0.2e1) * pow(cos(D_t * t), 0.2e1);
  return Q_T;
}



/* ------------------------------------------------
 *
 *         HEAT EQUATION
 *
 *        steady
 *
 *        variable coefficients
 *
 * -----------------------------------------------
 */ 

MASA::heateq_1d_steady_var::heateq_1d_steady_var()
{
  mmsname = "heateq_1d_steady_var";
  dimension=1;

  register_var("A_x",&A_x);   
  register_var("k_0",&k_0);
  register_var("k_1",&k_1);
  register_var("k_2",&k_2);

}//done with constructor

void MASA::heateq_1d_steady_var::init_var()
{

} // done with variable initializer

double MASA::heateq_1d_steady_var::eval_q_t(double x)
{
  double Q_T = 0.3e1 * A_x * A_x * k_2 * pow(cos(A_x * x), 0.3e1) + 0.2e1 * A_x * A_x * k_1 * pow(cos(A_x * x), 0.2e1) - A_x * A_x * k_1 + (k_0 - 0.2e1 * k_2) * A_x * A_x * cos(A_x * x);
  return Q_T;
}

MASA::heateq_2d_steady_var::heateq_2d_steady_var()
{
  mmsname = "heateq_2d_steady_var";
  dimension=2;

  register_var("A_x",&A_x);   
  register_var("k_0",&k_0);
  register_var("k_1",&k_1);
  register_var("k_2",&k_2);
  register_var("B_y",&B_y);

}//done with constructor

void MASA::heateq_2d_steady_var::init_var()
{

} // done with variable initializer


double MASA::heateq_2d_steady_var::eval_q_t(double x,double y)
{
  double Q_T = (0.3e1 * A_x * A_x + 0.3e1 * B_y * B_y) * k_2 * pow(cos(A_x * x), 0.3e1) * pow(cos(B_y * y), 0.3e1) + (0.2e1 * A_x * A_x + 0.2e1 * B_y * B_y) * k_1 * pow(cos(A_x * x), 0.2e1) * pow(cos(B_y * y), 0.2e1) - (pow(cos(B_y * y), 0.2e1) * A_x * A_x + pow(cos(A_x * x), 0.2e1) * B_y * B_y) * k_1 + (k_0 * A_x * A_x + k_0 * B_y * B_y - 0.2e1 * pow(cos(B_y * y), 0.2e1) * k_2 * A_x * A_x - 0.2e1 * pow(cos(A_x * x), 0.2e1) * k_2 * B_y * B_y) * cos(A_x * x) * cos(B_y * y);
  return Q_T;
}


MASA::heateq_3d_steady_var::heateq_3d_steady_var()
{
  mmsname = "heateq_3d_steady_var";
  dimension=3;

  register_var("A_x",&A_x);   
  register_var("k_0",&k_0);
  register_var("k_1",&k_1);
  register_var("k_2",&k_2);
  register_var("B_y",&B_y);
  register_var("C_z",&C_z);

}//done with constructor

void MASA::heateq_3d_steady_var::init_var()
{

} // done with variable initializer

double MASA::heateq_3d_steady_var::eval_q_t(double x,double y,double z)
{
  double Q_T = (0.3e1 * A_x * A_x + 0.3e1 * B_y * B_y + 0.3e1 * C_z * C_z) * k_2 * pow(cos(A_x * x), 0.3e1) * pow(cos(B_y * y), 0.3e1) * pow(cos(C_z * z), 0.3e1) + (0.2e1 * A_x * A_x + 0.2e1 * B_y * B_y + 0.2e1 * C_z * C_z) * k_1 * pow(cos(A_x * x), 0.2e1) * pow(cos(B_y * y), 0.2e1) * pow(cos(C_z * z), 0.2e1) - (pow(cos(B_y * y), 0.2e1) * pow(cos(C_z * z), 0.2e1) * A_x * A_x + pow(cos(A_x * x), 0.2e1) * pow(cos(C_z * z), 0.2e1) * B_y * B_y + pow(cos(A_x * x), 0.2e1) * pow(cos(B_y * y), 0.2e1) * C_z * C_z) * k_1 + (k_0 * A_x * A_x + k_0 * B_y * B_y + k_0 * C_z * C_z - 0.2e1 * pow(cos(B_y * y), 0.2e1) * pow(cos(C_z * z), 0.2e1) * k_2 * A_x * A_x - 0.2e1 * pow(cos(A_x * x), 0.2e1) * pow(cos(C_z * z), 0.2e1) * k_2 * B_y * B_y - 0.2e1 * pow(cos(A_x * x), 0.2e1) * pow(cos(B_y * y), 0.2e1) * k_2 * C_z * C_z) * cos(A_x * x) * cos(B_y * y) * cos(C_z * z);
  return Q_T;
}
