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
// this is the core set of routines -- the only functions that should be called by users
// all other files are internal
//

#include <masa_internal.h>

using namespace MASA;

// helper functions
int masa_v2o(void* obid, manufactured_solution** manfac)
{ 
  string name;
  manufactured_solution* temp;
  temp=static_cast<manufactured_solution*>(obid); // cast the void ptr back as an obj
  *manfac=temp;
  return 0;

}

// get list mms
//
// this function returns a vector of pointers to 
// manufactured solutions available
//
// adding function because it is called in several places

int get_list_mms(vector<manufactured_solution*>* anim)
{
  anim->push_back(new MASA_Test()); // test function
  
  // register solutions here
  anim->push_back(new heateq_1d_steady_const());
  anim->push_back(new heateq_2d_steady_const());
  anim->push_back(new heateq_3d_steady_const());

  anim->push_back(new heateq_1d_unsteady_const());
  anim->push_back(new heateq_2d_unsteady_const());
  anim->push_back(new heateq_3d_unsteady_const());

  anim->push_back(new heateq_1d_unsteady_var());
  anim->push_back(new heateq_2d_unsteady_var());
  anim->push_back(new heateq_3d_unsteady_var());

  anim->push_back(new heateq_1d_steady_var());
  anim->push_back(new heateq_2d_steady_var());
  anim->push_back(new heateq_3d_steady_var());

  anim->push_back(new euler_2d());
  anim->push_back(new euler_3d());

  anim->push_back(new navierstokes_2d_compressible());
  anim->push_back(new navierstokes_3d_compressible());

  return 0;

}

//
// function that searches all registered masa solutions
// for a selected manufactured solution
//
int MASA::masa_getid(void** objid,string str)
{
  int flag=0;
  string name;
  vector<manufactured_solution*> anim;

  get_list_mms(&anim); //construct list 
 
  // masa_map();  

  for (vector<manufactured_solution*>::const_iterator it = anim.begin(); it != anim.end(); ++it) {
    (*it)->return_name(&name); // get name
    if(str.compare(name) == 0) // strings are identical
      {
	*objid=(*it); // cast object pointer as void
	flag=1;      // set flag
      }
    else // strings not identical
      delete *it; // this calls the deconstructor
    
  }// done with for loop 

  if(flag==1)
    {      
      //cout << "\nMASA got it\n";
    }
  else
    {
      cout << "\nMASA FATAL ERROR: No Manufactured Solutions of that Type\n";
      exit(1); // error code, terminate
    }

  return 0; // steady as she goes
}// done with masa getid


//
// function that prints all registered masa solutions
//
int MASA::masa_printid()
{
  vector<manufactured_solution*> anim;
  string name;

  get_list_mms(&anim); //construct list 

  cout << endl;
  // masa_map();
  for (vector<manufactured_solution*>::const_iterator it = anim.begin(); it != anim.end(); ++it) {
    (*it)->return_name(&name); // get name
    cout << endl << name;
    delete *it; // this calls the deconstructor
  }// done with for loop 
  
  return 0; // steady as she goes
}// done with masa print id

int MASA::masa_set_param(void* objid,string param,double paramval)
{
  manufactured_solution* acobj;
  masa_v2o(objid,&acobj);
  
  acobj->set_var(param,paramval);

  return 0;
}

int MASA::masa_get_param(void* objid,string param,double *paramval)
{
  manufactured_solution* acobj;
  masa_v2o(objid,&acobj);

  acobj->get_var(param,paramval);

  return 0;
}

int MASA::masa_display_param(void* objid)
{
  manufactured_solution* acobj;
  masa_v2o(objid,&acobj);

  acobj->display_var();

  return 0;
}

/* ------------------------------------------------
 *
 *         1D functions
 *
 * -----------------------------------------------
 */ 

int MASA::masa_eval_t_source(void* objid,double x,double* field)
{
  manufactured_solution* acobj;
  masa_v2o(objid,&acobj);

  *field=acobj->eval_q_t(x);

  return 0;
}

int MASA::masa_eval_u_source(void* objid,double x,double* field)
{
  manufactured_solution* acobj;
  masa_v2o(objid,&acobj);

  *field=acobj->eval_q_u(x);

  return 0;
}

int MASA::masa_eval_rho_source(void* objid,double x,double* field)
{
  manufactured_solution* acobj;
  masa_v2o(objid,&acobj);

  *field=acobj->eval_q_rho(x);

  return 0;
}

int MASA::masa_eval_e_source(void* objid,double x,double* field)
{
  manufactured_solution* acobj;
  masa_v2o(objid,&acobj);

  *field=acobj->eval_q_e(x);

  return 0;
}

/* ------------------------------------------------
 *
 *         2D functions
 *
 * -----------------------------------------------
 */ 

int MASA::masa_eval_t_source(void* objid,double x,double y,double* field)
{
  manufactured_solution* acobj;
  masa_v2o(objid,&acobj);

  *field=acobj->eval_q_t(x,y);

  return 0;
}

int MASA::masa_eval_u_source(void* objid,double x,double y,double* field)
{
  manufactured_solution* acobj;
  masa_v2o(objid,&acobj);

  *field=acobj->eval_q_u(x,y);

  return 0;
}

int MASA::masa_eval_v_source(void* objid,double x,double y,double* field)
{
  manufactured_solution* acobj;
  masa_v2o(objid,&acobj);

  *field=acobj->eval_q_v(x,y);

  return 0;
}

int MASA::masa_eval_rho_source(void* objid,double x,double y,double* field)
{
  manufactured_solution* acobj;
  masa_v2o(objid,&acobj);

  *field=acobj->eval_q_rho(x,y);

  return 0;
}

int MASA::masa_eval_e_source(void* objid,double x,double y,double* field)
{
  manufactured_solution* acobj;
  masa_v2o(objid,&acobj);

  *field=acobj->eval_q_e(x,y);

  return 0;
}

/* ------------------------------------------------
 *
 *         3D functions
 *
 * -----------------------------------------------
 */ 

int MASA::masa_eval_t_source(void* objid,double x,double y,double z,double* field)
{
  manufactured_solution* acobj;
  masa_v2o(objid,&acobj);

  *field=acobj->eval_q_t(x,y,z);

  return 0;
}

int MASA::masa_eval_u_source(void* objid,double x,double y,double z,double* field)
{
  manufactured_solution* acobj;
  masa_v2o(objid,&acobj);

  *field=acobj->eval_q_u(x,y,z);

  return 0;
}

int MASA::masa_eval_v_source(void* objid,double x,double y,double z,double* field)
{
  manufactured_solution* acobj;
  masa_v2o(objid,&acobj);

  *field=acobj->eval_q_v(x,y,z);

  return 0;
}

int MASA::masa_eval_w_source(void* objid,double x,double y,double z,double* field)
{
  manufactured_solution* acobj;
  masa_v2o(objid,&acobj);

  *field=acobj->eval_q_v(x,y,z);

  return 0;
}

int MASA::masa_eval_rho_source(void* objid,double x,double y,double z,double* field)
{
  manufactured_solution* acobj;
  masa_v2o(objid,&acobj);

  *field=acobj->eval_q_rho(x,y,z);

  return 0;
}

int MASA::masa_eval_e_source(void* objid,double x,double y,double z,double* field)
{
  manufactured_solution* acobj;
  masa_v2o(objid,&acobj);

  *field=acobj->eval_q_e(x,y,z);

  return 0;
}

/* ------------------------------------------------
 *
 *         utility functions
 *
 * -----------------------------------------------
 */ 

int MASA::masa_get_name(void* objid,string* name)
{
  manufactured_solution* acobj;
  masa_v2o(objid,&acobj);
  acobj->return_name(name); // set string to name
  return 0;
}

int MASA::masa_get_dimension(void* objid,int* dim)
{
  manufactured_solution* acobj;
  masa_v2o(objid,&acobj);
  acobj->return_dim(dim); // set string to name
  return 0;
}

int MASA::masa_sanity_check(void* objid)
{
  manufactured_solution* acobj;
  masa_v2o(objid,&acobj);
  acobj->sanity_check(); // set string to name
  return 0;
}
