/*******************************************************************************************************************//**
 *  @file    jacobian.cpp
 *  @brief   Defines the generation of jacobians for various degrees of freedom.
 *
 *  @author  Fletcher Talbot (fletcher.talbot@csiro.au)
 *  @date    June 2017
 *  @version 0.5.0
 *
 *  CSIRO Autonomous Systems Laboratory
 *  Queensland Centre for Advanced Technologies
 *  PO Box 883, Kenmore, QLD 4069, Australia
 *
 *  (c) Copyright CSIRO 2017
 *
 *  All rights reserved, no part of this program may be used
 *  without explicit permission of CSIRO
 *
***********************************************************************************************************************/

#include "../include/syropod_highlevel_controller/standard_includes.h"

/*******************************************************************************************************************//**
 * Generates a Jacobian matrix for a 1 degree of freedom leg from input DH parameters (derived analytically)
 * @param[in] dh A vector containing a map of DH parameter strings and values for each degree of freedom.
***********************************************************************************************************************/
MatrixXd createJacobian1DOF(const vector<map<string, double>>& dh)
{
  //double d1 = dh[0].at("d"); //Unused
  double r1 = dh[0].at("r");
  double sT1 = sin(dh[0].at("theta"));
  double cT1 = cos(dh[0].at("theta"));
  //double sA1 = sin(dh[0].at("alpha")); //Unused
  //double cA1 = cos(dh[0].at("alpha")); //Unused
  MatrixXd j(3, 1);
  j(0,0) = -r1*sT1;
  j(1,0) = r1*cT1;
  j(2,0) = 0.0;
  return j;
}

/*******************************************************************************************************************//**
 * Generates a Jacobian matrix for a 2 degree of freedom leg from input DH parameters (derived analytically)
 * @param[in] dh A vector containing a map of DH parameter strings and values for each degree of freedom.
***********************************************************************************************************************/
MatrixXd createJacobian2DOF(const vector<map<string, double>>& dh)
{
  //double d1 = dh[0].at("d"); //Unused
  double d2 = dh[1].at("d");
  double r1 = dh[0].at("r");
  double r2 = dh[1].at("r");
  double sT1 = sin(dh[0].at("theta"));
  double sT2 = sin(dh[1].at("theta"));
  double cT1 = cos(dh[0].at("theta"));
  double cT2 = cos(dh[1].at("theta"));
  double sA1 = sin(dh[0].at("alpha"));
  //double sA2 = sin(dh[1].at("alpha")); //Unused
  double cA1 = cos(dh[0].at("alpha"));
  //double cA2 = cos(dh[1].at("alpha")); //Unused
  MatrixXd j(3, 2);
  j(0,0) = -(sT1*r2*cT2) - (cT1*cA1*r2*sT2) + (cT1*sA1*d2) - (r1*sT1);
  j(0,1) = -(cT1*r2*sT2) - (sT1*cA1*r2*cT2);
  j(1,0) = (cT1*r2*cT2) - (sT1*cA1*r2*sT2) + (sT1*sA1*d2)+(r1*cT1);
  j(1,1) = -(sT1*r2*sT2) + (cT1*cA1*r2*cT2);
  j(2,0) = 0.0;
  j(2,1) = (sA1*r2*cT2);
  return j;
}

/*******************************************************************************************************************//**
 * Generates a Jacobian matrix for a 3 degree of freedom leg from input DH parameters (derived analytically)
 * @param[in] dh A vector containing a map of DH parameter strings and values for each degree of freedom.
***********************************************************************************************************************/
MatrixXd createJacobian3DOF(const vector<map<string, double>>& dh)
{
  //double d1 = dh[0].at("d"); //Unused
  double d2 = dh[1].at("d");
  double d3 = dh[2].at("d");
  double r1 = dh[0].at("r");
  double r2 = dh[1].at("r");
  double r3 = dh[2].at("r");
  double sT1 = sin(dh[0].at("theta"));
  double sT2 = sin(dh[1].at("theta"));
  double sT3 = sin(dh[2].at("theta"));
  double cT1 = cos(dh[0].at("theta"));
  double cT2 = cos(dh[1].at("theta"));
  double cT3 = cos(dh[2].at("theta"));
  double sA1 = sin(dh[0].at("alpha"));
  double sA2 = sin(dh[1].at("alpha"));
  //double sA3 = sin(dh[2].at("alpha")); //Unused
  double cA1 = cos(dh[0].at("alpha"));
  double cA2 = cos(dh[1].at("alpha"));
  //double cA3 = cos(dh[2].at("alpha")); //Unused
  MatrixXd j(3,3);
  j(0,0) = -(sT1*cT2*r3*cT3)-(cT1*cA1*sT2*r3*cT3)+(sT1*sT2*cA2*r3*sT3)-(cT1*cA1*cT2*cA2*r3*sT3)+(cT1*sA1*sA2*r3*sT3)
           -(sT1*sT2*sA2*d3)+(cT1*cA1*cT2*sA2*d3)+(cT1*sA1*cA2*d3)-(sT1*r2*cT2)-(cT1*cA1*r2*sT2)+(cT1*sA1*d2)-(r1*sT1);
  j(0,1) = -(cT1*sT2*r3*cT3)-(sT1*cA1*cT2*r3*cT3)-(cT1*cT2*cA2*r3*sT3)+(sT1*cA1*sT2*cA2*r3*sT3)+(cT1*cT2*sA2*d3)
           -(sT1*cA1*sT2*sA2*d3)-(cT1*r2*sT2)-(sT1*cA1*r2*cT2);
  j(0,2) = -(cT1*cT2*r3*sT3)+(sT1*cA1*sT2*r3*sT3)-(cT1*sT2*cA2*r3*cT3)-(sT1*cA1*cT2*cA2*r3*cT3)+(sT1*sA1*sA2*r3*cT3);
  j(1,0) = +(cT1*cT2*r3*cT3)-(sT1*cA1*sT2*r3*cT3)-(cT1*sT2*cA2*r3*sT3)-(sT1*cA1*cT2*cA2*r3*sT3)+(sT1*sA1*sA2*r3*sT3)
           +(cT1*sT2*sA2*d3)+(sT1*cA1*cT2*sA2*d3)+(sT1*sA1*cA2*d3)+(cT1*r2*cT2)-(sT1*cA1*r2*sT2)+(sT1*sA1*d2)+(r1*cT1);
  j(1,1) = -(sT1*sT2*r3*cT3)+(cT1*cA1*cT2*r3*cT3)-(sT1*cT2*cA2*r3*sT3)-(cT1*cA1*sT2*cA2*r3*sT3)+(sT1*cT2*sA2*d3)
           +(cT1*cA1*sT2*sA2*d3)-(sT1*r2*sT2)+(cT1*cA1*r2*cT2);
  j(1,2) = -(sT1*cT2*r3*sT3)-(cT1*cA1*sT2*r3*sT3)-(sT1*sT2*cA2*r3*cT3)+(cT1*cA1*cT2*cA2*r3*cT3)-(cT1*sA1*sA2*r3*cT3);
  j(2,0) = 0;
  j(2,1) = +(sA1*cT2*r3*cT3)-(sA1*sT2*cA2*r3*sT3)+(sA1*sT2*sA2*d3)+(sA1*r2*cT2);
  j(2,2) = -(sA1*sT2*r3*sT3)+(sA1*cT2*cA2*r3*cT3)+(cA1*sA2*r3*cT3);
  return j;
}

/*******************************************************************************************************************//**
 * Generates a Jacobian matrix for a 4 degree of freedom leg from input DH parameters (derived analytically)
 * @param[in] dh A vector containing a map of DH parameter strings and values for each degree of freedom.
***********************************************************************************************************************/
MatrixXd createJacobian4DOF(const vector<map<string, double>>& dh)
{
  //double d1 = dh[0].at("d"); //Unused
  double d2 = dh[1].at("d");
  double d3 = dh[2].at("d");
  double d4 = dh[3].at("d");
  double r1 = dh[0].at("r");
  double r2 = dh[1].at("r");
  double r3 = dh[2].at("r");
  double r4 = dh[3].at("r");
  double sT1 = sin(dh[0].at("theta"));
  double sT2 = sin(dh[1].at("theta"));
  double sT3 = sin(dh[2].at("theta"));
  double sT4 = sin(dh[3].at("theta"));
  double cT1 = cos(dh[0].at("theta"));
  double cT2 = cos(dh[1].at("theta"));
  double cT3 = cos(dh[2].at("theta"));
  double cT4 = cos(dh[3].at("theta"));
  double sA1 = sin(dh[0].at("alpha"));
  double sA2 = sin(dh[1].at("alpha"));
  double sA3 = sin(dh[2].at("alpha"));
  //double sA4 = sin(dh[3].at("alpha")); //Unused
  double cA1 = cos(dh[0].at("alpha"));
  double cA2 = cos(dh[1].at("alpha"));
  double cA3 = cos(dh[2].at("alpha"));
  //double cA4 = cos(dh[3].at("alpha")); //Unused
  MatrixXd j(3,4);
  j(0,0) = -(sT1*cT2*cT3*r4*cT4)-(cT1*cA1*sT2*cT3*r4*cT4)+(sT1*sT2*cA2*sT3*r4*cT4)-(cT1*cA1*cT2*cA2*sT3*r4*cT4)
           +(cT1*sA1*sA2*sT3*r4*cT4)+(sT1*cT2*sT3*cA3*r4*sT4)+(cT1*cA1*sT2*sT3*cA3*r4*sT4)+(sT1*sT2*cA2*cT3*cA3*r4*sT4)
           -(cT1*cA1*cT2*cA2*cT3*cA3*r4*sT4)+(cT1*sA1*sA2*cT3*cA3*r4*sT4)-(sT1*sT2*sA2*sA3*r4*sT4)
           +(cT1*cA1*cT2*sA2*sA3*r4*sT4)+(cT1*sA1*cA2*sA3*r4*sT4)-(sT1*cT2*sT3*sA3*d4)-(cT1*cA1*sT2*sT3*sA3*d4)
           -(sT1*sT2*cA2*cT3*sA3*d4)+(cT1*cA1*cT2*cA2*cT3*sA3*d4)-(cT1*sA1*sA2*cT3*sA3*d4)-(sT1*sT2*sA2*cA3*d4)
           +(cT1*cA1*cT2*sA2*cA3*d4)+(cT1*sA1*cA2*cA3*d4)-(sT1*cT2*r3*cT3)-(cT1*cA1*sT2*r3*cT3)+(sT1*sT2*cA2*r3*sT3)
           -(cT1*cA1*cT2*cA2*r3*sT3)+(cT1*sA1*sA2*r3*sT3)-(sT1*sT2*sA2*d3)+(cT1*cA1*cT2*sA2*d3)+(cT1*sA1*cA2*d3)
           -(sT1*r2*cT2)-(cT1*cA1*r2*sT2)+(cT1*sA1*d2)-(r1*sT1);
  j(0,1) = -(cT1*sT2*cT3*r4*cT4)-(sT1*cA1*cT2*cT3*r4*cT4)-(cT1*cT2*cA2*sT3*r4*cT4)+(sT1*cA1*sT2*cA2*sT3*r4*cT4)
           +(cT1*sT2*sT3*cA3*r4*sT4)+(sT1*cA1*cT2*sT3*cA3*r4*sT4)-(cT1*cT2*cA2*cT3*cA3*r4*sT4)
           +(sT1*cA1*sT2*cA2*cT3*cA3*r4*sT4)+(cT1*cT2*sA2*sA3*r4*sT4)-(sT1*cA1*sT2*sA2*sA3*r4*sT4)-(cT1*sT2*sT3*sA3*d4)
           -(sT1*cA1*cT2*sT3*sA3*d4)+(cT1*cT2*cA2*cT3*sA3*d4)-(sT1*cA1*sT2*cA2*cT3*sA3*d4)+(cT1*cT2*sA2*cA3*d4)
           -(sT1*cA1*sT2*sA2*cA3*d4)-(cT1*sT2*r3*cT3)-(sT1*cA1*cT2*r3*cT3)-(cT1*cT2*cA2*r3*sT3)+(sT1*cA1*sT2*cA2*r3*sT3)
           +(cT1*cT2*sA2*d3)-(sT1*cA1*sT2*sA2*d3)-(cT1*r2*sT2)-(sT1*cA1*r2*cT2);
  j(0,2) = -(cT1*cT2*sT3*r4*cT4)+(sT1*cA1*sT2*sT3*r4*cT4)-(cT1*sT2*cA2*cT3*r4*cT4)-(sT1*cA1*cT2*cA2*cT3*r4*cT4)
           +(sT1*sA1*sA2*cT3*r4*cT4)-(cT1*cT2*cT3*cA3*r4*sT4)+(sT1*cA1*sT2*cT3*cA3*r4*sT4)+(cT1*sT2*cA2*sT3*cA3*r4*sT4)
           +(sT1*cA1*cT2*cA2*sT3*cA3*r4*sT4)-(sT1*sA1*sA2*sT3*cA3*r4*sT4)+(cT1*cT2*cT3*sA3*d4)-(sT1*cA1*sT2*cT3*sA3*d4)
           -(cT1*sT2*cA2*sT3*sA3*d4)-(sT1*cA1*cT2*cA2*sT3*sA3*d4)+(sT1*sA1*sA2*sT3*sA3*d4)-(cT1*cT2*r3*sT3)
           +(sT1*cA1*sT2*r3*sT3)-(cT1*sT2*cA2*r3*cT3)-(sT1*cA1*cT2*cA2*r3*cT3)+(sT1*sA1*sA2*r3*cT3);
  j(0,3) = -(cT1*cT2*cT3*r4*sT4)+(sT1*cA1*sT2*cT3*r4*sT4)+(cT1*sT2*cA2*sT3*r4*sT4)+(sT1*cA1*cT2*cA2*sT3*r4*sT4)
           -(sT1*sA1*sA2*sT3*r4*sT4)-(cT1*cT2*sT3*cA3*r4*cT4)+(sT1*cA1*sT2*sT3*cA3*r4*cT4)-(cT1*sT2*cA2*cT3*cA3*r4*cT4)
           -(sT1*cA1*cT2*cA2*cT3*cA3*r4*cT4)+(sT1*sA1*sA2*cT3*cA3*r4*cT4)+(cT1*sT2*sA2*sA3*r4*cT4)
           +(sT1*cA1*cT2*sA2*sA3*r4*cT4)+(sT1*sA1*cA2*sA3*r4*cT4);
  j(1,0) = +(cT1*cT2*cT3*r4*cT4)-(sT1*cA1*sT2*cT3*r4*cT4)-(cT1*sT2*cA2*sT3*r4*cT4)-(sT1*cA1*cT2*cA2*sT3*r4*cT4)
           +(sT1*sA1*sA2*sT3*r4*cT4)-(cT1*cT2*sT3*cA3*r4*sT4)+(sT1*cA1*sT2*sT3*cA3*r4*sT4)-(cT1*sT2*cA2*cT3*cA3*r4*sT4)
           -(sT1*cA1*cT2*cA2*cT3*cA3*r4*sT4)+(sT1*sA1*sA2*cT3*cA3*r4*sT4)+(cT1*sT2*sA2*sA3*r4*sT4)
           +(sT1*cA1*cT2*sA2*sA3*r4*sT4)+(sT1*sA1*cA2*sA3*r4*sT4)+(cT1*cT2*sT3*sA3*d4)-(sT1*cA1*sT2*sT3*sA3*d4)
           +(cT1*sT2*cA2*cT3*sA3*d4)+(sT1*cA1*cT2*cA2*cT3*sA3*d4)-(sT1*sA1*sA2*cT3*sA3*d4)+(cT1*sT2*sA2*cA3*d4)
           +(sT1*cA1*cT2*sA2*cA3*d4)+(sT1*sA1*cA2*cA3*d4)+(cT1*cT2*r3*cT3)-(sT1*cA1*sT2*r3*cT3)-(cT1*sT2*cA2*r3*sT3)
           -(sT1*cA1*cT2*cA2*r3*sT3)+(sT1*sA1*sA2*r3*sT3)+(cT1*sT2*sA2*d3)+(sT1*cA1*cT2*sA2*d3)+(sT1*sA1*cA2*d3)
           +(cT1*r2*cT2)-(sT1*cA1*r2*sT2)+(sT1*sA1*d2)+(r1*cT1);
  j(1,1) = -(sT1*sT2*cT3*r4*cT4)+(cT1*cA1*cT2*cT3*r4*cT4)-(sT1*cT2*cA2*sT3*r4*cT4)-(cT1*cA1*sT2*cA2*sT3*r4*cT4)
           +(sT1*sT2*sT3*cA3*r4*sT4)-(cT1*cA1*cT2*sT3*cA3*r4*sT4)-(sT1*cT2*cA2*cT3*cA3*r4*sT4)
           -(cT1*cA1*sT2*cA2*cT3*cA3*r4*sT4)+(sT1*cT2*sA2*sA3*r4*sT4)+(cT1*cA1*sT2*sA2*sA3*r4*sT4)-(sT1*sT2*sT3*sA3*d4)
           +(cT1*cA1*cT2*sT3*sA3*d4)+(sT1*cT2*cA2*cT3*sA3*d4)+(cT1*cA1*sT2*cA2*cT3*sA3*d4)+(sT1*cT2*sA2*cA3*d4)
           +(cT1*cA1*sT2*sA2*cA3*d4)-(sT1*sT2*r3*cT3)+(cT1*cA1*cT2*r3*cT3)-(sT1*cT2*cA2*r3*sT3)-(cT1*cA1*sT2*cA2*r3*sT3)
           +(sT1*cT2*sA2*d3)+(cT1*cA1*sT2*sA2*d3)-(sT1*r2*sT2)+(cT1*cA1*r2*cT2);
  j(1,2) = -(sT1*cT2*sT3*r4*cT4)-(cT1*cA1*sT2*sT3*r4*cT4)-(sT1*sT2*cA2*cT3*r4*cT4)+(cT1*cA1*cT2*cA2*cT3*r4*cT4)
           -(cT1*sA1*sA2*cT3*r4*cT4)-(sT1*cT2*cT3*cA3*r4*sT4)-(cT1*cA1*sT2*cT3*cA3*r4*sT4)+(sT1*sT2*cA2*sT3*cA3*r4*sT4)
           -(cT1*cA1*cT2*cA2*sT3*cA3*r4*sT4)+(cT1*sA1*sA2*sT3*cA3*r4*sT4)+(sT1*cT2*cT3*sA3*d4)+(cT1*cA1*sT2*cT3*sA3*d4)
           -(sT1*sT2*cA2*sT3*sA3*d4)+(cT1*cA1*cT2*cA2*sT3*sA3*d4)-(cT1*sA1*sA2*sT3*sA3*d4)-(sT1*cT2*r3*sT3)
           -(cT1*cA1*sT2*r3*sT3)-(sT1*sT2*cA2*r3*cT3)+(cT1*cA1*cT2*cA2*r3*cT3)-(cT1*sA1*sA2*r3*cT3);
  j(1,3) = -(sT1*cT2*cT3*r4*sT4)-(cT1*cA1*sT2*cT3*r4*sT4)+(sT1*sT2*cA2*sT3*r4*sT4)-(cT1*cA1*cT2*cA2*sT3*r4*sT4)
           +(cT1*sA1*sA2*sT3*r4*sT4)-(sT1*cT2*sT3*cA3*r4*cT4)-(cT1*cA1*sT2*sT3*cA3*r4*cT4)-(sT1*sT2*cA2*cT3*cA3*r4*cT4)
           +(cT1*cA1*cT2*cA2*cT3*cA3*r4*cT4)-(cT1*sA1*sA2*cT3*cA3*r4*cT4)+(sT1*sT2*sA2*sA3*r4*cT4)
           -(cT1*cA1*cT2*sA2*sA3*r4*cT4)-(cT1*sA1*cA2*sA3*r4*cT4);
  j(2,0) = 0;
  j(2,1) = +(sA1*cT2*cT3*r4*cT4)-(sA1*sT2*cA2*sT3*r4*cT4)-(sA1*cT2*sT3*cA3*r4*sT4)-(sA1*sT2*cA2*cT3*cA3*r4*sT4)
           +(sA1*sT2*sA2*sA3*r4*sT4)+(sA1*cT2*sT3*sA3*d4)+(sA1*sT2*cA2*cT3*sA3*d4)+(sA1*sT2*sA2*cA3*d4)
           +(sA1*cT2*r3*cT3)-(sA1*sT2*cA2*r3*sT3)+(sA1*sT2*sA2*d3)+(sA1*r2*cT2);
  j(2,2) = -(sA1*sT2*sT3*r4*cT4)+(sA1*cT2*cA2*cT3*r4*cT4)+(cA1*sA2*cT3*r4*cT4)-(sA1*sT2*cT3*cA3*r4*sT4)
           -(sA1*cT2*cA2*sT3*cA3*r4*sT4)-(cA1*sA2*sT3*cA3*r4*sT4)+(sA1*sT2*cT3*sA3*d4)+(sA1*cT2*cA2*sT3*sA3*d4)
           +(cA1*sA2*sT3*sA3*d4)-(sA1*sT2*r3*sT3)+(sA1*cT2*cA2*r3*cT3)+(cA1*sA2*r3*cT3);
  j(2,3) = -(sA1*sT2*cT3*r4*sT4)-(sA1*cT2*cA2*sT3*r4*sT4)-(cA1*sA2*sT3*r4*sT4)-(sA1*sT2*sT3*cA3*r4*cT4)
           +(sA1*cT2*cA2*cT3*cA3*r4*cT4)+(cA1*sA2*cT3*cA3*r4*cT4)-(sA1*cT2*sA2*sA3*r4*cT4)+(cA1*cA2*sA3*r4*cT4);
  return j;
}

/*******************************************************************************************************************//**
 * Generates a Jacobian matrix for a 5 degree of freedom leg from input DH parameters (derived analytically)
 * @param[in] dh A vector containing a map of DH parameter strings and values for each degree of freedom.
***********************************************************************************************************************/
MatrixXd createJacobian5DOF(const vector<map<string, double>>& dh)
{
  //double d1 = dh[0].at("d //Unused
  double d2 = dh[1].at("d");
  double d3 = dh[2].at("d");
  double d4 = dh[3].at("d");
  double d5 = dh[4].at("d");
  double r1 = dh[0].at("r");
  double r2 = dh[1].at("r");
  double r3 = dh[2].at("r");
  double r4 = dh[3].at("r");
  double r5 = dh[4].at("r");
  double sT1 = sin(dh[0].at("theta"));
  double sT2 = sin(dh[1].at("theta"));
  double sT3 = sin(dh[2].at("theta"));
  double sT4 = sin(dh[3].at("theta"));
  double sT5 = sin(dh[4].at("theta"));
  double cT1 = cos(dh[0].at("theta"));
  double cT2 = cos(dh[1].at("theta"));
  double cT3 = cos(dh[2].at("theta"));
  double cT4 = cos(dh[3].at("theta"));
  double cT5 = cos(dh[4].at("theta"));
  double sA1 = sin(dh[0].at("alpha"));
  double sA2 = sin(dh[1].at("alpha"));
  double sA3 = sin(dh[2].at("alpha"));
  double sA4 = sin(dh[3].at("alpha"));
  //double sA5 = sin(dh[4].at("alpha")); //Unused
  double cA1 = cos(dh[0].at("alpha"));
  double cA2 = cos(dh[1].at("alpha"));
  double cA3 = cos(dh[2].at("alpha"));
  double cA4 = cos(dh[3].at("alpha"));
  //double cA5 = cos(dh[4].at("alpha")); //Unused
  MatrixXd j(3,5);
  j(0,0) = -(sT1*cT2*cT3*cT4*r5*cT5)-(cT1*cA1*sT2*cT3*cT4*r5*cT5)+(sT1*sT2*cA2*sT3*cT4*r5*cT5)
           -(cT1*cA1*cT2*cA2*sT3*cT4*r5*cT5)+(cT1*sA1*sA2*sT3*cT4*r5*cT5)+(sT1*cT2*sT3*cA3*sT4*r5*cT5)
           +(cT1*cA1*sT2*sT3*cA3*sT4*r5*cT5)+(sT1*sT2*cA2*cT3*cA3*sT4*r5*cT5)-(cT1*cA1*cT2*cA2*cT3*cA3*sT4*r5*cT5)
           +(cT1*sA1*sA2*cT3*cA3*sT4*r5*cT5)-(sT1*sT2*sA2*sA3*sT4*r5*cT5)+(cT1*cA1*cT2*sA2*sA3*sT4*r5*cT5)
           +(cT1*sA1*cA2*sA3*sT4*r5*cT5)+(sT1*cT2*cT3*sT4*cA4*r5*sT5)+(cT1*cA1*sT2*cT3*sT4*cA4*r5*sT5)
           -(sT1*sT2*cA2*sT3*sT4*cA4*r5*sT5)+(cT1*cA1*cT2*cA2*sT3*sT4*cA4*r5*sT5)-(cT1*sA1*sA2*sT3*sT4*cA4*r5*sT5)
           +(sT1*cT2*sT3*cA3*cT4*cA4*r5*sT5)+(cT1*cA1*sT2*sT3*cA3*cT4*cA4*r5*sT5)+(sT1*sT2*cA2*cT3*cA3*cT4*cA4*r5*sT5)
           -(cT1*cA1*cT2*cA2*cT3*cA3*cT4*cA4*r5*sT5)+(cT1*sA1*sA2*cT3*cA3*cT4*cA4*r5*sT5)
           -(sT1*sT2*sA2*sA3*cT4*cA4*r5*sT5)+(cT1*cA1*cT2*sA2*sA3*cT4*cA4*r5*sT5)+(cT1*sA1*cA2*sA3*cT4*cA4*r5*sT5)
           -(sT1*cT2*sT3*sA3*sA4*r5*sT5)-(cT1*cA1*sT2*sT3*sA3*sA4*r5*sT5)-(sT1*sT2*cA2*cT3*sA3*sA4*r5*sT5)
           +(cT1*cA1*cT2*cA2*cT3*sA3*sA4*r5*sT5)-(cT1*sA1*sA2*cT3*sA3*sA4*r5*sT5)-(sT1*sT2*sA2*cA3*sA4*r5*sT5)
           +(cT1*cA1*cT2*sA2*cA3*sA4*r5*sT5)+(cT1*sA1*cA2*cA3*sA4*r5*sT5)-(sT1*cT2*cT3*sT4*sA4*d5)
           -(cT1*cA1*sT2*cT3*sT4*sA4*d5)+(sT1*sT2*cA2*sT3*sT4*sA4*d5)-(cT1*cA1*cT2*cA2*sT3*sT4*sA4*d5)
           +(cT1*sA1*sA2*sT3*sT4*sA4*d5)-(sT1*cT2*sT3*cA3*cT4*sA4*d5)-(cT1*cA1*sT2*sT3*cA3*cT4*sA4*d5)
           -(sT1*sT2*cA2*cT3*cA3*cT4*sA4*d5)+(cT1*cA1*cT2*cA2*cT3*cA3*cT4*sA4*d5)-(cT1*sA1*sA2*cT3*cA3*cT4*sA4*d5)
           +(sT1*sT2*sA2*sA3*cT4*sA4*d5)-(cT1*cA1*cT2*sA2*sA3*cT4*sA4*d5)-(cT1*sA1*cA2*sA3*cT4*sA4*d5)
           -(sT1*cT2*sT3*sA3*cA4*d5)-(cT1*cA1*sT2*sT3*sA3*cA4*d5)-(sT1*sT2*cA2*cT3*sA3*cA4*d5)
           +(cT1*cA1*cT2*cA2*cT3*sA3*cA4*d5)-(cT1*sA1*sA2*cT3*sA3*cA4*d5)-(sT1*sT2*sA2*cA3*cA4*d5)
           +(cT1*cA1*cT2*sA2*cA3*cA4*d5)+(cT1*sA1*cA2*cA3*cA4*d5)-(sT1*cT2*cT3*r4*cT4)-(cT1*cA1*sT2*cT3*r4*cT4)
           +(sT1*sT2*cA2*sT3*r4*cT4)-(cT1*cA1*cT2*cA2*sT3*r4*cT4)+(cT1*sA1*sA2*sT3*r4*cT4)+(sT1*cT2*sT3*cA3*r4*sT4)
           +(cT1*cA1*sT2*sT3*cA3*r4*sT4)+(sT1*sT2*cA2*cT3*cA3*r4*sT4)-(cT1*cA1*cT2*cA2*cT3*cA3*r4*sT4)
           +(cT1*sA1*sA2*cT3*cA3*r4*sT4)-(sT1*sT2*sA2*sA3*r4*sT4)+(cT1*cA1*cT2*sA2*sA3*r4*sT4)+(cT1*sA1*cA2*sA3*r4*sT4)
           -(sT1*cT2*sT3*sA3*d4)-(cT1*cA1*sT2*sT3*sA3*d4)-(sT1*sT2*cA2*cT3*sA3*d4)+(cT1*cA1*cT2*cA2*cT3*sA3*d4)
           -(cT1*sA1*sA2*cT3*sA3*d4)-(sT1*sT2*sA2*cA3*d4)+(cT1*cA1*cT2*sA2*cA3*d4)+(cT1*sA1*cA2*cA3*d4)-(sT1*cT2*r3*cT3)
           -(cT1*cA1*sT2*r3*cT3)+(sT1*sT2*cA2*r3*sT3)-(cT1*cA1*cT2*cA2*r3*sT3)+(cT1*sA1*sA2*r3*sT3)-(sT1*sT2*sA2*d3)
           +(cT1*cA1*cT2*sA2*d3)+(cT1*sA1*cA2*d3)-(sT1*r2*cT2)-(cT1*cA1*r2*sT2)+(cT1*sA1*d2)-(r1*sT1);
  j(0,1) = -(cT1*sT2*cT3*cT4*r5*cT5)-(sT1*cA1*cT2*cT3*cT4*r5*cT5)-(cT1*cT2*cA2*sT3*cT4*r5*cT5)
           +(sT1*cA1*sT2*cA2*sT3*cT4*r5*cT5)+(cT1*sT2*sT3*cA3*sT4*r5*cT5)+(sT1*cA1*cT2*sT3*cA3*sT4*r5*cT5)
           -(cT1*cT2*cA2*cT3*cA3*sT4*r5*cT5)+(sT1*cA1*sT2*cA2*cT3*cA3*sT4*r5*cT5)+(cT1*cT2*sA2*sA3*sT4*r5*cT5)
           -(sT1*cA1*sT2*sA2*sA3*sT4*r5*cT5)+(cT1*sT2*cT3*sT4*cA4*r5*sT5)+(sT1*cA1*cT2*cT3*sT4*cA4*r5*sT5)
           +(cT1*cT2*cA2*sT3*sT4*cA4*r5*sT5)-(sT1*cA1*sT2*cA2*sT3*sT4*cA4*r5*sT5)+(cT1*sT2*sT3*cA3*cT4*cA4*r5*sT5)
           +(sT1*cA1*cT2*sT3*cA3*cT4*cA4*r5*sT5)-(cT1*cT2*cA2*cT3*cA3*cT4*cA4*r5*sT5)
           +(sT1*cA1*sT2*cA2*cT3*cA3*cT4*cA4*r5*sT5)+(cT1*cT2*sA2*sA3*cT4*cA4*r5*sT5)
           -(sT1*cA1*sT2*sA2*sA3*cT4*cA4*r5*sT5)-(cT1*sT2*sT3*sA3*sA4*r5*sT5)-(sT1*cA1*cT2*sT3*sA3*sA4*r5*sT5)
           +(cT1*cT2*cA2*cT3*sA3*sA4*r5*sT5)-(sT1*cA1*sT2*cA2*cT3*sA3*sA4*r5*sT5)+(cT1*cT2*sA2*cA3*sA4*r5*sT5)
           -(sT1*cA1*sT2*sA2*cA3*sA4*r5*sT5)-(cT1*sT2*cT3*sT4*sA4*d5)-(sT1*cA1*cT2*cT3*sT4*sA4*d5)
           -(cT1*cT2*cA2*sT3*sT4*sA4*d5)+(sT1*cA1*sT2*cA2*sT3*sT4*sA4*d5)-(cT1*sT2*sT3*cA3*cT4*sA4*d5)
           -(sT1*cA1*cT2*sT3*cA3*cT4*sA4*d5)+(cT1*cT2*cA2*cT3*cA3*cT4*sA4*d5)-(sT1*cA1*sT2*cA2*cT3*cA3*cT4*sA4*d5)
           -(cT1*cT2*sA2*sA3*cT4*sA4*d5)+(sT1*cA1*sT2*sA2*sA3*cT4*sA4*d5)-(cT1*sT2*sT3*sA3*cA4*d5)
           -(sT1*cA1*cT2*sT3*sA3*cA4*d5)+(cT1*cT2*cA2*cT3*sA3*cA4*d5)-(sT1*cA1*sT2*cA2*cT3*sA3*cA4*d5)
           +(cT1*cT2*sA2*cA3*cA4*d5)-(sT1*cA1*sT2*sA2*cA3*cA4*d5)-(cT1*sT2*cT3*r4*cT4)-(sT1*cA1*cT2*cT3*r4*cT4)
           -(cT1*cT2*cA2*sT3*r4*cT4)+(sT1*cA1*sT2*cA2*sT3*r4*cT4)+(cT1*sT2*sT3*cA3*r4*sT4)+(sT1*cA1*cT2*sT3*cA3*r4*sT4)
           -(cT1*cT2*cA2*cT3*cA3*r4*sT4)+(sT1*cA1*sT2*cA2*cT3*cA3*r4*sT4)+(cT1*cT2*sA2*sA3*r4*sT4)
           -(sT1*cA1*sT2*sA2*sA3*r4*sT4)-(cT1*sT2*sT3*sA3*d4)-(sT1*cA1*cT2*sT3*sA3*d4)+(cT1*cT2*cA2*cT3*sA3*d4)
           -(sT1*cA1*sT2*cA2*cT3*sA3*d4)+(cT1*cT2*sA2*cA3*d4)-(sT1*cA1*sT2*sA2*cA3*d4)-(cT1*sT2*r3*cT3)
           -(sT1*cA1*cT2*r3*cT3)-(cT1*cT2*cA2*r3*sT3)+(sT1*cA1*sT2*cA2*r3*sT3)+(cT1*cT2*sA2*d3)-(sT1*cA1*sT2*sA2*d3)
           -(cT1*r2*sT2)-(sT1*cA1*r2*cT2);
  j(0,2) = -(cT1*cT2*sT3*cT4*r5*cT5)+(sT1*cA1*sT2*sT3*cT4*r5*cT5)-(cT1*sT2*cA2*cT3*cT4*r5*cT5)
           -(sT1*cA1*cT2*cA2*cT3*cT4*r5*cT5)+(sT1*sA1*sA2*cT3*cT4*r5*cT5)-(cT1*cT2*cT3*cA3*sT4*r5*cT5)
           +(sT1*cA1*sT2*cT3*cA3*sT4*r5*cT5)+(cT1*sT2*cA2*sT3*cA3*sT4*r5*cT5)+(sT1*cA1*cT2*cA2*sT3*cA3*sT4*r5*cT5)
           -(sT1*sA1*sA2*sT3*cA3*sT4*r5*cT5)+(cT1*cT2*sT3*sT4*cA4*r5*sT5)-(sT1*cA1*sT2*sT3*sT4*cA4*r5*sT5)
           +(cT1*sT2*cA2*cT3*sT4*cA4*r5*sT5)+(sT1*cA1*cT2*cA2*cT3*sT4*cA4*r5*sT5)-(sT1*sA1*sA2*cT3*sT4*cA4*r5*sT5)
           -(cT1*cT2*cT3*cA3*cT4*cA4*r5*sT5)+(sT1*cA1*sT2*cT3*cA3*cT4*cA4*r5*sT5)+(cT1*sT2*cA2*sT3*cA3*cT4*cA4*r5*sT5)
           +(sT1*cA1*cT2*cA2*sT3*cA3*cT4*cA4*r5*sT5)-(sT1*sA1*sA2*sT3*cA3*cT4*cA4*r5*sT5)+(cT1*cT2*cT3*sA3*sA4*r5*sT5)
           -(sT1*cA1*sT2*cT3*sA3*sA4*r5*sT5)-(cT1*sT2*cA2*sT3*sA3*sA4*r5*sT5)-(sT1*cA1*cT2*cA2*sT3*sA3*sA4*r5*sT5)
           +(sT1*sA1*sA2*sT3*sA3*sA4*r5*sT5)-(cT1*cT2*sT3*sT4*sA4*d5)+(sT1*cA1*sT2*sT3*sT4*sA4*d5)
           -(cT1*sT2*cA2*cT3*sT4*sA4*d5)-(sT1*cA1*cT2*cA2*cT3*sT4*sA4*d5)+(sT1*sA1*sA2*cT3*sT4*sA4*d5)
           +(cT1*cT2*cT3*cA3*cT4*sA4*d5)-(sT1*cA1*sT2*cT3*cA3*cT4*sA4*d5)-(cT1*sT2*cA2*sT3*cA3*cT4*sA4*d5)
           -(sT1*cA1*cT2*cA2*sT3*cA3*cT4*sA4*d5)+(sT1*sA1*sA2*sT3*cA3*cT4*sA4*d5)+(cT1*cT2*cT3*sA3*cA4*d5)
           -(sT1*cA1*sT2*cT3*sA3*cA4*d5)-(cT1*sT2*cA2*sT3*sA3*cA4*d5)-(sT1*cA1*cT2*cA2*sT3*sA3*cA4*d5)
           +(sT1*sA1*sA2*sT3*sA3*cA4*d5)-(cT1*cT2*sT3*r4*cT4)+(sT1*cA1*sT2*sT3*r4*cT4)-(cT1*sT2*cA2*cT3*r4*cT4)
           -(sT1*cA1*cT2*cA2*cT3*r4*cT4)+(sT1*sA1*sA2*cT3*r4*cT4)-(cT1*cT2*cT3*cA3*r4*sT4)+(sT1*cA1*sT2*cT3*cA3*r4*sT4)
           +(cT1*sT2*cA2*sT3*cA3*r4*sT4)+(sT1*cA1*cT2*cA2*sT3*cA3*r4*sT4)-(sT1*sA1*sA2*sT3*cA3*r4*sT4)
           +(cT1*cT2*cT3*sA3*d4)-(sT1*cA1*sT2*cT3*sA3*d4)-(cT1*sT2*cA2*sT3*sA3*d4)-(sT1*cA1*cT2*cA2*sT3*sA3*d4)
           +(sT1*sA1*sA2*sT3*sA3*d4)-(cT1*cT2*r3*sT3)+(sT1*cA1*sT2*r3*sT3)-(cT1*sT2*cA2*r3*cT3)
           -(sT1*cA1*cT2*cA2*r3*cT3)+(sT1*sA1*sA2*r3*cT3);
  j(0,3) = -(cT1*cT2*cT3*sT4*r5*cT5)+(sT1*cA1*sT2*cT3*sT4*r5*cT5)+(cT1*sT2*cA2*sT3*sT4*r5*cT5)
           +(sT1*cA1*cT2*cA2*sT3*sT4*r5*cT5)-(sT1*sA1*sA2*sT3*sT4*r5*cT5)-(cT1*cT2*sT3*cA3*cT4*r5*cT5)
           +(sT1*cA1*sT2*sT3*cA3*cT4*r5*cT5)-(cT1*sT2*cA2*cT3*cA3*cT4*r5*cT5)-(sT1*cA1*cT2*cA2*cT3*cA3*cT4*r5*cT5)
           +(sT1*sA1*sA2*cT3*cA3*cT4*r5*cT5)+(cT1*sT2*sA2*sA3*cT4*r5*cT5)+(sT1*cA1*cT2*sA2*sA3*cT4*r5*cT5)
           +(sT1*sA1*cA2*sA3*cT4*r5*cT5)-(cT1*cT2*cT3*cT4*cA4*r5*sT5)+(sT1*cA1*sT2*cT3*cT4*cA4*r5*sT5)
           +(cT1*sT2*cA2*sT3*cT4*cA4*r5*sT5)+(sT1*cA1*cT2*cA2*sT3*cT4*cA4*r5*sT5)-(sT1*sA1*sA2*sT3*cT4*cA4*r5*sT5)
           +(cT1*cT2*sT3*cA3*sT4*cA4*r5*sT5)-(sT1*cA1*sT2*sT3*cA3*sT4*cA4*r5*sT5)+(cT1*sT2*cA2*cT3*cA3*sT4*cA4*r5*sT5)
           +(sT1*cA1*cT2*cA2*cT3*cA3*sT4*cA4*r5*sT5)-(sT1*sA1*sA2*cT3*cA3*sT4*cA4*r5*sT5)
           -(cT1*sT2*sA2*sA3*sT4*cA4*r5*sT5)-(sT1*cA1*cT2*sA2*sA3*sT4*cA4*r5*sT5)-(sT1*sA1*cA2*sA3*sT4*cA4*r5*sT5)
           +(cT1*cT2*cT3*cT4*sA4*d5)-(sT1*cA1*sT2*cT3*cT4*sA4*d5)-(cT1*sT2*cA2*sT3*cT4*sA4*d5)
           -(sT1*cA1*cT2*cA2*sT3*cT4*sA4*d5)+(sT1*sA1*sA2*sT3*cT4*sA4*d5)-(cT1*cT2*sT3*cA3*sT4*sA4*d5)
           +(sT1*cA1*sT2*sT3*cA3*sT4*sA4*d5)-(cT1*sT2*cA2*cT3*cA3*sT4*sA4*d5)-(sT1*cA1*cT2*cA2*cT3*cA3*sT4*sA4*d5)
           +(sT1*sA1*sA2*cT3*cA3*sT4*sA4*d5)+(cT1*sT2*sA2*sA3*sT4*sA4*d5)+(sT1*cA1*cT2*sA2*sA3*sT4*sA4*d5)
           +(sT1*sA1*cA2*sA3*sT4*sA4*d5)-(cT1*cT2*cT3*r4*sT4)+(sT1*cA1*sT2*cT3*r4*sT4)+(cT1*sT2*cA2*sT3*r4*sT4)
           +(sT1*cA1*cT2*cA2*sT3*r4*sT4)-(sT1*sA1*sA2*sT3*r4*sT4)-(cT1*cT2*sT3*cA3*r4*cT4)+(sT1*cA1*sT2*sT3*cA3*r4*cT4)
           -(cT1*sT2*cA2*cT3*cA3*r4*cT4)-(sT1*cA1*cT2*cA2*cT3*cA3*r4*cT4)+(sT1*sA1*sA2*cT3*cA3*r4*cT4)
           +(cT1*sT2*sA2*sA3*r4*cT4)+(sT1*cA1*cT2*sA2*sA3*r4*cT4)+(sT1*sA1*cA2*sA3*r4*cT4);
  j(0,4) = -(cT1*cT2*cT3*cT4*r5*sT5)+(sT1*cA1*sT2*cT3*cT4*r5*sT5)+(cT1*sT2*cA2*sT3*cT4*r5*sT5)
           +(sT1*cA1*cT2*cA2*sT3*cT4*r5*sT5)-(sT1*sA1*sA2*sT3*cT4*r5*sT5)+(cT1*cT2*sT3*cA3*sT4*r5*sT5)
           -(sT1*cA1*sT2*sT3*cA3*sT4*r5*sT5)+(cT1*sT2*cA2*cT3*cA3*sT4*r5*sT5)+(sT1*cA1*cT2*cA2*cT3*cA3*sT4*r5*sT5)
           -(sT1*sA1*sA2*cT3*cA3*sT4*r5*sT5)-(cT1*sT2*sA2*sA3*sT4*r5*sT5)-(sT1*cA1*cT2*sA2*sA3*sT4*r5*sT5)
           -(sT1*sA1*cA2*sA3*sT4*r5*sT5)-(cT1*cT2*cT3*sT4*cA4*r5*cT5)+(sT1*cA1*sT2*cT3*sT4*cA4*r5*cT5)
           +(cT1*sT2*cA2*sT3*sT4*cA4*r5*cT5)+(sT1*cA1*cT2*cA2*sT3*sT4*cA4*r5*cT5)-(sT1*sA1*sA2*sT3*sT4*cA4*r5*cT5)
           -(cT1*cT2*sT3*cA3*cT4*cA4*r5*cT5)+(sT1*cA1*sT2*sT3*cA3*cT4*cA4*r5*cT5)-(cT1*sT2*cA2*cT3*cA3*cT4*cA4*r5*cT5)
           -(sT1*cA1*cT2*cA2*cT3*cA3*cT4*cA4*r5*cT5)+(sT1*sA1*sA2*cT3*cA3*cT4*cA4*r5*cT5)
           +(cT1*sT2*sA2*sA3*cT4*cA4*r5*cT5)+(sT1*cA1*cT2*sA2*sA3*cT4*cA4*r5*cT5)+(sT1*sA1*cA2*sA3*cT4*cA4*r5*cT5)
           +(cT1*cT2*sT3*sA3*sA4*r5*cT5)-(sT1*cA1*sT2*sT3*sA3*sA4*r5*cT5)+(cT1*sT2*cA2*cT3*sA3*sA4*r5*cT5)
           +(sT1*cA1*cT2*cA2*cT3*sA3*sA4*r5*cT5)-(sT1*sA1*sA2*cT3*sA3*sA4*r5*cT5)+(cT1*sT2*sA2*cA3*sA4*r5*cT5)
           +(sT1*cA1*cT2*sA2*cA3*sA4*r5*cT5)+(sT1*sA1*cA2*cA3*sA4*r5*cT5);
  j(1,0) = +(cT1*cT2*cT3*cT4*r5*cT5)-(sT1*cA1*sT2*cT3*cT4*r5*cT5)-(cT1*sT2*cA2*sT3*cT4*r5*cT5)
           -(sT1*cA1*cT2*cA2*sT3*cT4*r5*cT5)+(sT1*sA1*sA2*sT3*cT4*r5*cT5)-(cT1*cT2*sT3*cA3*sT4*r5*cT5)
           +(sT1*cA1*sT2*sT3*cA3*sT4*r5*cT5)-(cT1*sT2*cA2*cT3*cA3*sT4*r5*cT5)-(sT1*cA1*cT2*cA2*cT3*cA3*sT4*r5*cT5)
           +(sT1*sA1*sA2*cT3*cA3*sT4*r5*cT5)+(cT1*sT2*sA2*sA3*sT4*r5*cT5)+(sT1*cA1*cT2*sA2*sA3*sT4*r5*cT5)
           +(sT1*sA1*cA2*sA3*sT4*r5*cT5)-(cT1*cT2*cT3*sT4*cA4*r5*sT5)+(sT1*cA1*sT2*cT3*sT4*cA4*r5*sT5)
           +(cT1*sT2*cA2*sT3*sT4*cA4*r5*sT5)+(sT1*cA1*cT2*cA2*sT3*sT4*cA4*r5*sT5)-(sT1*sA1*sA2*sT3*sT4*cA4*r5*sT5)
           -(cT1*cT2*sT3*cA3*cT4*cA4*r5*sT5)+(sT1*cA1*sT2*sT3*cA3*cT4*cA4*r5*sT5)-(cT1*sT2*cA2*cT3*cA3*cT4*cA4*r5*sT5)
           -(sT1*cA1*cT2*cA2*cT3*cA3*cT4*cA4*r5*sT5)+(sT1*sA1*sA2*cT3*cA3*cT4*cA4*r5*sT5)
           +(cT1*sT2*sA2*sA3*cT4*cA4*r5*sT5)+(sT1*cA1*cT2*sA2*sA3*cT4*cA4*r5*sT5)+(sT1*sA1*cA2*sA3*cT4*cA4*r5*sT5)
           +(cT1*cT2*sT3*sA3*sA4*r5*sT5)-(sT1*cA1*sT2*sT3*sA3*sA4*r5*sT5)+(cT1*sT2*cA2*cT3*sA3*sA4*r5*sT5)
           +(sT1*cA1*cT2*cA2*cT3*sA3*sA4*r5*sT5)-(sT1*sA1*sA2*cT3*sA3*sA4*r5*sT5)+(cT1*sT2*sA2*cA3*sA4*r5*sT5)
           +(sT1*cA1*cT2*sA2*cA3*sA4*r5*sT5)+(sT1*sA1*cA2*cA3*sA4*r5*sT5)+(cT1*cT2*cT3*sT4*sA4*d5)
           -(sT1*cA1*sT2*cT3*sT4*sA4*d5)-(cT1*sT2*cA2*sT3*sT4*sA4*d5)-(sT1*cA1*cT2*cA2*sT3*sT4*sA4*d5)
           +(sT1*sA1*sA2*sT3*sT4*sA4*d5)+(cT1*cT2*sT3*cA3*cT4*sA4*d5)-(sT1*cA1*sT2*sT3*cA3*cT4*sA4*d5)
           +(cT1*sT2*cA2*cT3*cA3*cT4*sA4*d5)+(sT1*cA1*cT2*cA2*cT3*cA3*cT4*sA4*d5)-(sT1*sA1*sA2*cT3*cA3*cT4*sA4*d5)
           -(cT1*sT2*sA2*sA3*cT4*sA4*d5)-(sT1*cA1*cT2*sA2*sA3*cT4*sA4*d5)-(sT1*sA1*cA2*sA3*cT4*sA4*d5)
           +(cT1*cT2*sT3*sA3*cA4*d5)-(sT1*cA1*sT2*sT3*sA3*cA4*d5)+(cT1*sT2*cA2*cT3*sA3*cA4*d5)
           +(sT1*cA1*cT2*cA2*cT3*sA3*cA4*d5)-(sT1*sA1*sA2*cT3*sA3*cA4*d5)+(cT1*sT2*sA2*cA3*cA4*d5)
           +(sT1*cA1*cT2*sA2*cA3*cA4*d5)+(sT1*sA1*cA2*cA3*cA4*d5)+(cT1*cT2*cT3*r4*cT4)-(sT1*cA1*sT2*cT3*r4*cT4)
           -(cT1*sT2*cA2*sT3*r4*cT4)-(sT1*cA1*cT2*cA2*sT3*r4*cT4)+(sT1*sA1*sA2*sT3*r4*cT4)-(cT1*cT2*sT3*cA3*r4*sT4)
           +(sT1*cA1*sT2*sT3*cA3*r4*sT4)-(cT1*sT2*cA2*cT3*cA3*r4*sT4)-(sT1*cA1*cT2*cA2*cT3*cA3*r4*sT4)
           +(sT1*sA1*sA2*cT3*cA3*r4*sT4)+(cT1*sT2*sA2*sA3*r4*sT4)+(sT1*cA1*cT2*sA2*sA3*r4*sT4)+(sT1*sA1*cA2*sA3*r4*sT4)
           +(cT1*cT2*sT3*sA3*d4)-(sT1*cA1*sT2*sT3*sA3*d4)+(cT1*sT2*cA2*cT3*sA3*d4)+(sT1*cA1*cT2*cA2*cT3*sA3*d4)
           -(sT1*sA1*sA2*cT3*sA3*d4)+(cT1*sT2*sA2*cA3*d4)+(sT1*cA1*cT2*sA2*cA3*d4)+(sT1*sA1*cA2*cA3*d4)+(cT1*cT2*r3*cT3)
           -(sT1*cA1*sT2*r3*cT3)-(cT1*sT2*cA2*r3*sT3)-(sT1*cA1*cT2*cA2*r3*sT3)+(sT1*sA1*sA2*r3*sT3)+(cT1*sT2*sA2*d3)
           +(sT1*cA1*cT2*sA2*d3)+(sT1*sA1*cA2*d3)+(cT1*r2*cT2)-(sT1*cA1*r2*sT2)+(sT1*sA1*d2)+(r1*cT1);
  j(1,1) = -(sT1*sT2*cT3*cT4*r5*cT5)+(cT1*cA1*cT2*cT3*cT4*r5*cT5)-(sT1*cT2*cA2*sT3*cT4*r5*cT5)
           -(cT1*cA1*sT2*cA2*sT3*cT4*r5*cT5)+(sT1*sT2*sT3*cA3*sT4*r5*cT5)-(cT1*cA1*cT2*sT3*cA3*sT4*r5*cT5)
           -(sT1*cT2*cA2*cT3*cA3*sT4*r5*cT5)-(cT1*cA1*sT2*cA2*cT3*cA3*sT4*r5*cT5)+(sT1*cT2*sA2*sA3*sT4*r5*cT5)
           +(cT1*cA1*sT2*sA2*sA3*sT4*r5*cT5)+(sT1*sT2*cT3*sT4*cA4*r5*sT5)-(cT1*cA1*cT2*cT3*sT4*cA4*r5*sT5)
           +(sT1*cT2*cA2*sT3*sT4*cA4*r5*sT5)+(cT1*cA1*sT2*cA2*sT3*sT4*cA4*r5*sT5)+(sT1*sT2*sT3*cA3*cT4*cA4*r5*sT5)
           -(cT1*cA1*cT2*sT3*cA3*cT4*cA4*r5*sT5)-(sT1*cT2*cA2*cT3*cA3*cT4*cA4*r5*sT5)
           -(cT1*cA1*sT2*cA2*cT3*cA3*cT4*cA4*r5*sT5)+(sT1*cT2*sA2*sA3*cT4*cA4*r5*sT5)
           +(cT1*cA1*sT2*sA2*sA3*cT4*cA4*r5*sT5)-(sT1*sT2*sT3*sA3*sA4*r5*sT5)+(cT1*cA1*cT2*sT3*sA3*sA4*r5*sT5)
           +(sT1*cT2*cA2*cT3*sA3*sA4*r5*sT5)+(cT1*cA1*sT2*cA2*cT3*sA3*sA4*r5*sT5)+(sT1*cT2*sA2*cA3*sA4*r5*sT5)
           +(cT1*cA1*sT2*sA2*cA3*sA4*r5*sT5)-(sT1*sT2*cT3*sT4*sA4*d5)+(cT1*cA1*cT2*cT3*sT4*sA4*d5)
           -(sT1*cT2*cA2*sT3*sT4*sA4*d5)-(cT1*cA1*sT2*cA2*sT3*sT4*sA4*d5)-(sT1*sT2*sT3*cA3*cT4*sA4*d5)
           +(cT1*cA1*cT2*sT3*cA3*cT4*sA4*d5)+(sT1*cT2*cA2*cT3*cA3*cT4*sA4*d5)+(cT1*cA1*sT2*cA2*cT3*cA3*cT4*sA4*d5)
           -(sT1*cT2*sA2*sA3*cT4*sA4*d5)-(cT1*cA1*sT2*sA2*sA3*cT4*sA4*d5)-(sT1*sT2*sT3*sA3*cA4*d5)
           +(cT1*cA1*cT2*sT3*sA3*cA4*d5)+(sT1*cT2*cA2*cT3*sA3*cA4*d5)+(cT1*cA1*sT2*cA2*cT3*sA3*cA4*d5)
           +(sT1*cT2*sA2*cA3*cA4*d5)+(cT1*cA1*sT2*sA2*cA3*cA4*d5)-(sT1*sT2*cT3*r4*cT4)+(cT1*cA1*cT2*cT3*r4*cT4)
           -(sT1*cT2*cA2*sT3*r4*cT4)-(cT1*cA1*sT2*cA2*sT3*r4*cT4)+(sT1*sT2*sT3*cA3*r4*sT4)-(cT1*cA1*cT2*sT3*cA3*r4*sT4)
           -(sT1*cT2*cA2*cT3*cA3*r4*sT4)-(cT1*cA1*sT2*cA2*cT3*cA3*r4*sT4)+(sT1*cT2*sA2*sA3*r4*sT4)
           +(cT1*cA1*sT2*sA2*sA3*r4*sT4)-(sT1*sT2*sT3*sA3*d4)+(cT1*cA1*cT2*sT3*sA3*d4)+(sT1*cT2*cA2*cT3*sA3*d4)
           +(cT1*cA1*sT2*cA2*cT3*sA3*d4)+(sT1*cT2*sA2*cA3*d4)+(cT1*cA1*sT2*sA2*cA3*d4)-(sT1*sT2*r3*cT3)
           +(cT1*cA1*cT2*r3*cT3)-(sT1*cT2*cA2*r3*sT3)-(cT1*cA1*sT2*cA2*r3*sT3)+(sT1*cT2*sA2*d3)+(cT1*cA1*sT2*sA2*d3)
           -(sT1*r2*sT2)+(cT1*cA1*r2*cT2);
  j(1,2) = -(sT1*cT2*sT3*cT4*r5*cT5)-(cT1*cA1*sT2*sT3*cT4*r5*cT5)-(sT1*sT2*cA2*cT3*cT4*r5*cT5)
           +(cT1*cA1*cT2*cA2*cT3*cT4*r5*cT5)-(cT1*sA1*sA2*cT3*cT4*r5*cT5)-(sT1*cT2*cT3*cA3*sT4*r5*cT5)
           -(cT1*cA1*sT2*cT3*cA3*sT4*r5*cT5)+(sT1*sT2*cA2*sT3*cA3*sT4*r5*cT5)-(cT1*cA1*cT2*cA2*sT3*cA3*sT4*r5*cT5)
           +(cT1*sA1*sA2*sT3*cA3*sT4*r5*cT5)+(sT1*cT2*sT3*sT4*cA4*r5*sT5)+(cT1*cA1*sT2*sT3*sT4*cA4*r5*sT5)
           +(sT1*sT2*cA2*cT3*sT4*cA4*r5*sT5)-(cT1*cA1*cT2*cA2*cT3*sT4*cA4*r5*sT5)+(cT1*sA1*sA2*cT3*sT4*cA4*r5*sT5)
           -(sT1*cT2*cT3*cA3*cT4*cA4*r5*sT5)-(cT1*cA1*sT2*cT3*cA3*cT4*cA4*r5*sT5)+(sT1*sT2*cA2*sT3*cA3*cT4*cA4*r5*sT5)
           -(cT1*cA1*cT2*cA2*sT3*cA3*cT4*cA4*r5*sT5)+(cT1*sA1*sA2*sT3*cA3*cT4*cA4*r5*sT5)+(sT1*cT2*cT3*sA3*sA4*r5*sT5)
           +(cT1*cA1*sT2*cT3*sA3*sA4*r5*sT5)-(sT1*sT2*cA2*sT3*sA3*sA4*r5*sT5)+(cT1*cA1*cT2*cA2*sT3*sA3*sA4*r5*sT5)
           -(cT1*sA1*sA2*sT3*sA3*sA4*r5*sT5)-(sT1*cT2*sT3*sT4*sA4*d5)-(cT1*cA1*sT2*sT3*sT4*sA4*d5)
           -(sT1*sT2*cA2*cT3*sT4*sA4*d5)+(cT1*cA1*cT2*cA2*cT3*sT4*sA4*d5)-(cT1*sA1*sA2*cT3*sT4*sA4*d5)
           +(sT1*cT2*cT3*cA3*cT4*sA4*d5)+(cT1*cA1*sT2*cT3*cA3*cT4*sA4*d5)-(sT1*sT2*cA2*sT3*cA3*cT4*sA4*d5)
           +(cT1*cA1*cT2*cA2*sT3*cA3*cT4*sA4*d5)-(cT1*sA1*sA2*sT3*cA3*cT4*sA4*d5)+(sT1*cT2*cT3*sA3*cA4*d5)
           +(cT1*cA1*sT2*cT3*sA3*cA4*d5)-(sT1*sT2*cA2*sT3*sA3*cA4*d5)+(cT1*cA1*cT2*cA2*sT3*sA3*cA4*d5)
           -(cT1*sA1*sA2*sT3*sA3*cA4*d5)-(sT1*cT2*sT3*r4*cT4)-(cT1*cA1*sT2*sT3*r4*cT4)-(sT1*sT2*cA2*cT3*r4*cT4)
           +(cT1*cA1*cT2*cA2*cT3*r4*cT4)-(cT1*sA1*sA2*cT3*r4*cT4)-(sT1*cT2*cT3*cA3*r4*sT4)-(cT1*cA1*sT2*cT3*cA3*r4*sT4)
           +(sT1*sT2*cA2*sT3*cA3*r4*sT4)-(cT1*cA1*cT2*cA2*sT3*cA3*r4*sT4)+(cT1*sA1*sA2*sT3*cA3*r4*sT4)
           +(sT1*cT2*cT3*sA3*d4)+(cT1*cA1*sT2*cT3*sA3*d4)-(sT1*sT2*cA2*sT3*sA3*d4)+(cT1*cA1*cT2*cA2*sT3*sA3*d4)
           -(cT1*sA1*sA2*sT3*sA3*d4)-(sT1*cT2*r3*sT3)-(cT1*cA1*sT2*r3*sT3)-(sT1*sT2*cA2*r3*cT3)+(cT1*cA1*cT2*cA2*r3*cT3)
           -(cT1*sA1*sA2*r3*cT3);
  j(1,3) = -(sT1*cT2*cT3*sT4*r5*cT5)-(cT1*cA1*sT2*cT3*sT4*r5*cT5)+(sT1*sT2*cA2*sT3*sT4*r5*cT5)
           -(cT1*cA1*cT2*cA2*sT3*sT4*r5*cT5)+(cT1*sA1*sA2*sT3*sT4*r5*cT5)-(sT1*cT2*sT3*cA3*cT4*r5*cT5)
           -(cT1*cA1*sT2*sT3*cA3*cT4*r5*cT5)-(sT1*sT2*cA2*cT3*cA3*cT4*r5*cT5)+(cT1*cA1*cT2*cA2*cT3*cA3*cT4*r5*cT5)
           -(cT1*sA1*sA2*cT3*cA3*cT4*r5*cT5)+(sT1*sT2*sA2*sA3*cT4*r5*cT5)-(cT1*cA1*cT2*sA2*sA3*cT4*r5*cT5)
           -(cT1*sA1*cA2*sA3*cT4*r5*cT5)-(sT1*cT2*cT3*cT4*cA4*r5*sT5)-(cT1*cA1*sT2*cT3*cT4*cA4*r5*sT5)
           +(sT1*sT2*cA2*sT3*cT4*cA4*r5*sT5)-(cT1*cA1*cT2*cA2*sT3*cT4*cA4*r5*sT5)+(cT1*sA1*sA2*sT3*cT4*cA4*r5*sT5)
           +(sT1*cT2*sT3*cA3*sT4*cA4*r5*sT5)+(cT1*cA1*sT2*sT3*cA3*sT4*cA4*r5*sT5)+(sT1*sT2*cA2*cT3*cA3*sT4*cA4*r5*sT5)
           -(cT1*cA1*cT2*cA2*cT3*cA3*sT4*cA4*r5*sT5)+(cT1*sA1*sA2*cT3*cA3*sT4*cA4*r5*sT5)
           -(sT1*sT2*sA2*sA3*sT4*cA4*r5*sT5)+(cT1*cA1*cT2*sA2*sA3*sT4*cA4*r5*sT5)+(cT1*sA1*cA2*sA3*sT4*cA4*r5*sT5)
           +(sT1*cT2*cT3*cT4*sA4*d5)+(cT1*cA1*sT2*cT3*cT4*sA4*d5)-(sT1*sT2*cA2*sT3*cT4*sA4*d5)
           +(cT1*cA1*cT2*cA2*sT3*cT4*sA4*d5)-(cT1*sA1*sA2*sT3*cT4*sA4*d5)-(sT1*cT2*sT3*cA3*sT4*sA4*d5)
           -(cT1*cA1*sT2*sT3*cA3*sT4*sA4*d5)-(sT1*sT2*cA2*cT3*cA3*sT4*sA4*d5)+(cT1*cA1*cT2*cA2*cT3*cA3*sT4*sA4*d5)
           -(cT1*sA1*sA2*cT3*cA3*sT4*sA4*d5)+(sT1*sT2*sA2*sA3*sT4*sA4*d5)-(cT1*cA1*cT2*sA2*sA3*sT4*sA4*d5)
           -(cT1*sA1*cA2*sA3*sT4*sA4*d5)-(sT1*cT2*cT3*r4*sT4)-(cT1*cA1*sT2*cT3*r4*sT4)+(sT1*sT2*cA2*sT3*r4*sT4)
           -(cT1*cA1*cT2*cA2*sT3*r4*sT4)+(cT1*sA1*sA2*sT3*r4*sT4)-(sT1*cT2*sT3*cA3*r4*cT4)-(cT1*cA1*sT2*sT3*cA3*r4*cT4)
           -(sT1*sT2*cA2*cT3*cA3*r4*cT4)+(cT1*cA1*cT2*cA2*cT3*cA3*r4*cT4)-(cT1*sA1*sA2*cT3*cA3*r4*cT4)
           +(sT1*sT2*sA2*sA3*r4*cT4)-(cT1*cA1*cT2*sA2*sA3*r4*cT4)-(cT1*sA1*cA2*sA3*r4*cT4);
  j(1,4) = -(sT1*cT2*cT3*cT4*r5*sT5)-(cT1*cA1*sT2*cT3*cT4*r5*sT5)+(sT1*sT2*cA2*sT3*cT4*r5*sT5)
           -(cT1*cA1*cT2*cA2*sT3*cT4*r5*sT5)+(cT1*sA1*sA2*sT3*cT4*r5*sT5)+(sT1*cT2*sT3*cA3*sT4*r5*sT5)
           +(cT1*cA1*sT2*sT3*cA3*sT4*r5*sT5)+(sT1*sT2*cA2*cT3*cA3*sT4*r5*sT5)-(cT1*cA1*cT2*cA2*cT3*cA3*sT4*r5*sT5)
           +(cT1*sA1*sA2*cT3*cA3*sT4*r5*sT5)-(sT1*sT2*sA2*sA3*sT4*r5*sT5)+(cT1*cA1*cT2*sA2*sA3*sT4*r5*sT5)
           +(cT1*sA1*cA2*sA3*sT4*r5*sT5)-(sT1*cT2*cT3*sT4*cA4*r5*cT5)-(cT1*cA1*sT2*cT3*sT4*cA4*r5*cT5)
           +(sT1*sT2*cA2*sT3*sT4*cA4*r5*cT5)-(cT1*cA1*cT2*cA2*sT3*sT4*cA4*r5*cT5)+(cT1*sA1*sA2*sT3*sT4*cA4*r5*cT5)
           -(sT1*cT2*sT3*cA3*cT4*cA4*r5*cT5)-(cT1*cA1*sT2*sT3*cA3*cT4*cA4*r5*cT5)-(sT1*sT2*cA2*cT3*cA3*cT4*cA4*r5*cT5)
           +(cT1*cA1*cT2*cA2*cT3*cA3*cT4*cA4*r5*cT5)-(cT1*sA1*sA2*cT3*cA3*cT4*cA4*r5*cT5)
           +(sT1*sT2*sA2*sA3*cT4*cA4*r5*cT5)-(cT1*cA1*cT2*sA2*sA3*cT4*cA4*r5*cT5)-(cT1*sA1*cA2*sA3*cT4*cA4*r5*cT5)
           +(sT1*cT2*sT3*sA3*sA4*r5*cT5)+(cT1*cA1*sT2*sT3*sA3*sA4*r5*cT5)+(sT1*sT2*cA2*cT3*sA3*sA4*r5*cT5)
           -(cT1*cA1*cT2*cA2*cT3*sA3*sA4*r5*cT5)+(cT1*sA1*sA2*cT3*sA3*sA4*r5*cT5)+(sT1*sT2*sA2*cA3*sA4*r5*cT5)
           -(cT1*cA1*cT2*sA2*cA3*sA4*r5*cT5)-(cT1*sA1*cA2*cA3*sA4*r5*cT5);
  j(2,0) = 0.0;
  j(2,1) = +(sA1*cT2*cT3*cT4*r5*cT5)-(sA1*sT2*cA2*sT3*cT4*r5*cT5)-(sA1*cT2*sT3*cA3*sT4*r5*cT5)
           -(sA1*sT2*cA2*cT3*cA3*sT4*r5*cT5)+(sA1*sT2*sA2*sA3*sT4*r5*cT5)-(sA1*cT2*cT3*sT4*cA4*r5*sT5)
           +(sA1*sT2*cA2*sT3*sT4*cA4*r5*sT5)-(sA1*cT2*sT3*cA3*cT4*cA4*r5*sT5)-(sA1*sT2*cA2*cT3*cA3*cT4*cA4*r5*sT5)
           +(sA1*sT2*sA2*sA3*cT4*cA4*r5*sT5)+(sA1*cT2*sT3*sA3*sA4*r5*sT5)+(sA1*sT2*cA2*cT3*sA3*sA4*r5*sT5)
           +(sA1*sT2*sA2*cA3*sA4*r5*sT5)+(sA1*cT2*cT3*sT4*sA4*d5)-(sA1*sT2*cA2*sT3*sT4*sA4*d5)
           +(sA1*cT2*sT3*cA3*cT4*sA4*d5)+(sA1*sT2*cA2*cT3*cA3*cT4*sA4*d5)-(sA1*sT2*sA2*sA3*cT4*sA4*d5)
           +(sA1*cT2*sT3*sA3*cA4*d5)+(sA1*sT2*cA2*cT3*sA3*cA4*d5)+(sA1*sT2*sA2*cA3*cA4*d5)+(sA1*cT2*cT3*r4*cT4)
           -(sA1*sT2*cA2*sT3*r4*cT4)-(sA1*cT2*sT3*cA3*r4*sT4)-(sA1*sT2*cA2*cT3*cA3*r4*sT4)+(sA1*sT2*sA2*sA3*r4*sT4)
           +(sA1*cT2*sT3*sA3*d4)+(sA1*sT2*cA2*cT3*sA3*d4)+(sA1*sT2*sA2*cA3*d4)+(sA1*cT2*r3*cT3)-(sA1*sT2*cA2*r3*sT3)
           +(sA1*sT2*sA2*d3)+(sA1*r2*cT2);
  j(2,2) = -(sA1*sT2*sT3*cT4*r5*cT5)+(sA1*cT2*cA2*cT3*cT4*r5*cT5)+(cA1*sA2*cT3*cT4*r5*cT5)-(sA1*sT2*cT3*cA3*sT4*r5*cT5)
           -(sA1*cT2*cA2*sT3*cA3*sT4*r5*cT5)-(cA1*sA2*sT3*cA3*sT4*r5*cT5)+(sA1*sT2*sT3*sT4*cA4*r5*sT5)
           -(sA1*cT2*cA2*cT3*sT4*cA4*r5*sT5)-(cA1*sA2*cT3*sT4*cA4*r5*sT5)-(sA1*sT2*cT3*cA3*cT4*cA4*r5*sT5)
           -(sA1*cT2*cA2*sT3*cA3*cT4*cA4*r5*sT5)-(cA1*sA2*sT3*cA3*cT4*cA4*r5*sT5)+(sA1*sT2*cT3*sA3*sA4*r5*sT5)
           +(sA1*cT2*cA2*sT3*sA3*sA4*r5*sT5)+(cA1*sA2*sT3*sA3*sA4*r5*sT5)-(sA1*sT2*sT3*sT4*sA4*d5)
           +(sA1*cT2*cA2*cT3*sT4*sA4*d5)+(cA1*sA2*cT3*sT4*sA4*d5)+(sA1*sT2*cT3*cA3*cT4*sA4*d5)
           +(sA1*cT2*cA2*sT3*cA3*cT4*sA4*d5)+(cA1*sA2*sT3*cA3*cT4*sA4*d5)+(sA1*sT2*cT3*sA3*cA4*d5)
           +(sA1*cT2*cA2*sT3*sA3*cA4*d5)+(cA1*sA2*sT3*sA3*cA4*d5)-(sA1*sT2*sT3*r4*cT4)+(sA1*cT2*cA2*cT3*r4*cT4)
           +(cA1*sA2*cT3*r4*cT4)-(sA1*sT2*cT3*cA3*r4*sT4)-(sA1*cT2*cA2*sT3*cA3*r4*sT4)-(cA1*sA2*sT3*cA3*r4*sT4)
           +(sA1*sT2*cT3*sA3*d4)+(sA1*cT2*cA2*sT3*sA3*d4)+(cA1*sA2*sT3*sA3*d4)-(sA1*sT2*r3*sT3)+(sA1*cT2*cA2*r3*cT3)
           +(cA1*sA2*r3*cT3);
  j(2,3) = -(sA1*sT2*cT3*sT4*r5*cT5)-(sA1*cT2*cA2*sT3*sT4*r5*cT5)-(cA1*sA2*sT3*sT4*r5*cT5)-(sA1*sT2*sT3*cA3*cT4*r5*cT5)
           +(sA1*cT2*cA2*cT3*cA3*cT4*r5*cT5)+(cA1*sA2*cT3*cA3*cT4*r5*cT5)-(sA1*cT2*sA2*sA3*cT4*r5*cT5)
           +(cA1*cA2*sA3*cT4*r5*cT5)-(sA1*sT2*cT3*cT4*cA4*r5*sT5)-(sA1*cT2*cA2*sT3*cT4*cA4*r5*sT5)
           -(cA1*sA2*sT3*cT4*cA4*r5*sT5)+(sA1*sT2*sT3*cA3*sT4*cA4*r5*sT5)-(sA1*cT2*cA2*cT3*cA3*sT4*cA4*r5*sT5)
           -(cA1*sA2*cT3*cA3*sT4*cA4*r5*sT5)+(sA1*cT2*sA2*sA3*sT4*cA4*r5*sT5)-(cA1*cA2*sA3*sT4*cA4*r5*sT5)
           +(sA1*sT2*cT3*cT4*sA4*d5)+(sA1*cT2*cA2*sT3*cT4*sA4*d5)+(cA1*sA2*sT3*cT4*sA4*d5)-(sA1*sT2*sT3*cA3*sT4*sA4*d5)
           +(sA1*cT2*cA2*cT3*cA3*sT4*sA4*d5)+(cA1*sA2*cT3*cA3*sT4*sA4*d5)-(sA1*cT2*sA2*sA3*sT4*sA4*d5)
           +(cA1*cA2*sA3*sT4*sA4*d5)-(sA1*sT2*cT3*r4*sT4)-(sA1*cT2*cA2*sT3*r4*sT4)-(cA1*sA2*sT3*r4*sT4)
           -(sA1*sT2*sT3*cA3*r4*cT4)+(sA1*cT2*cA2*cT3*cA3*r4*cT4)+(cA1*sA2*cT3*cA3*r4*cT4)-(sA1*cT2*sA2*sA3*r4*cT4)
           +(cA1*cA2*sA3*r4*cT4);
  j(2,4) = -(sA1*sT2*cT3*cT4*r5*sT5)-(sA1*cT2*cA2*sT3*cT4*r5*sT5)-(cA1*sA2*sT3*cT4*r5*sT5)+(sA1*sT2*sT3*cA3*sT4*r5*sT5)
           -(sA1*cT2*cA2*cT3*cA3*sT4*r5*sT5)-(cA1*sA2*cT3*cA3*sT4*r5*sT5)+(sA1*cT2*sA2*sA3*sT4*r5*sT5)
           -(cA1*cA2*sA3*sT4*r5*sT5)-(sA1*sT2*cT3*sT4*cA4*r5*cT5)-(sA1*cT2*cA2*sT3*sT4*cA4*r5*cT5)
           -(cA1*sA2*sT3*sT4*cA4*r5*cT5)-(sA1*sT2*sT3*cA3*cT4*cA4*r5*cT5)+(sA1*cT2*cA2*cT3*cA3*cT4*cA4*r5*cT5)
           +(cA1*sA2*cT3*cA3*cT4*cA4*r5*cT5)-(sA1*cT2*sA2*sA3*cT4*cA4*r5*cT5)+(cA1*cA2*sA3*cT4*cA4*r5*cT5)
           +(sA1*sT2*sT3*sA3*sA4*r5*cT5)-(sA1*cT2*cA2*cT3*sA3*sA4*r5*cT5)-(cA1*sA2*cT3*sA3*sA4*r5*cT5)
           -(sA1*cT2*sA2*cA3*sA4*r5*cT5)+(cA1*cA2*cA3*sA4*r5*cT5);
  return j;
}

/*******************************************************************************************************************//**
 * Generates a Jacobian matrix for a 6 degree of freedom leg from input DH parameters (derived analytically)
 * @param[in] dh A vector containing a map of DH parameter strings and values for each degree of freedom.
 * @todo Develop analytical solution to generate Jacobian from dh parameters for 6 degrees of freedom
***********************************************************************************************************************/
MatrixXd createJacobian6DOF(const vector<map<string, double>>& dh) //TODO
{
  //double d1 = dh[0].at("d");
  //double d2 = dh[1].at("d");
  //double d3 = dh[2].at("d");
  //double d4 = dh[3].at("d");
  //double d5 = dh[4].at("d");
  //double d6 = dh[5].at("d");
  //double r1 = dh[0].at("r");
  //double r2 = dh[1].at("r");
  //double r3 = dh[2].at("r");
  //double r4 = dh[3].at("r");
  //double r5 = dh[4].at("r");
  //double r6 = dh[5].at("r");
  //double sT1 = sin(dh[0].at("theta"));
  //double sT2 = sin(dh[1].at("theta"));
  //double sT3 = sin(dh[2].at("theta"));
  //double sT4 = sin(dh[3].at("theta"));
  //double sT5 = sin(dh[4].at("theta"));
  //double sT6 = sin(dh[5].at("theta"));
  //double cT1 = cos(dh[0].at("theta"));
  //double cT2 = cos(dh[1].at("theta"));
  //double cT3 = cos(dh[2].at("theta"));
  //double cT4 = cos(dh[3].at("theta"));
  //double cT5 = cos(dh[4].at("theta"));
  //double cT6 = cos(dh[5].at("theta"));
  //double sA1 = sin(dh[0].at("alpha"));
  //double sA2 = sin(dh[1].at("alpha"));
  //double sA3 = sin(dh[2].at("alpha"));
  //double sA4 = sin(dh[3].at("alpha"));
  //double sA5 = sin(dh[4].at("alpha"));
  //double sA6 = sin(dh[5].at("alpha"));
  //double cA1 = cos(dh[0].at("alpha"));
  //double cA2 = cos(dh[1].at("alpha"));
  //double cA3 = cos(dh[2].at("alpha"));
  //double cA4 = cos(dh[3].at("alpha"));
  //double cA5 = cos(dh[4].at("alpha"));
  //double cA6 = cos(dh[5].at("alpha"));
  MatrixXd j(3,6);
  j(0,0) = 0.0;
  j(0,1) = 0.0;
  j(0,2) = 0.0;
  j(0,3) = 0.0;
  j(0,4) = 0.0;
  j(0,5) = 0.0;
  j(1,0) = 0.0;
  j(1,1) = 0.0;
  j(1,2) = 0.0;
  j(1,3) = 0.0;
  j(1,4) = 0.0;
  j(1,5) = 0.0;
  j(2,0) = 0.0;
  j(2,1) = 0.0;
  j(2,2) = 0.0;
  j(2,3) = 0.0;
  j(2,4) = 0.0;
  j(2,5) = 0.0;
  return j;
}

/***********************************************************************************************************************
***********************************************************************************************************************/
