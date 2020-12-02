﻿/*!
 * \file flow_sources.hpp
 * \brief Delarations of numerics classes for source-term integration.
 * \author F. Palacios, T. Economon
 * \version 7.0.8 "Blackbird"
 *
 * SU2 Project Website: https://su2code.github.io
 *
 * The SU2 Project is maintained by the SU2 Foundation
 * (http://su2foundation.org)
 *
 * Copyright 2012-2020, SU2 Contributors (cf. AUTHORS.md)
 *
 * SU2 is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * SU2 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with SU2. If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "../CNumerics.hpp"

/*!
 * \class CSourceBase_Flow
 * \brief Intermediate source term class to allocate the internally
 *        stored residual and Jacobian. Not for stand alone use,
 *        just a helper to build more complicated classes.
 * \ingroup SourceDiscr
 */
class CSourceBase_Flow : public CNumerics {
protected:
  su2double* residual = nullptr;
  su2double** jacobian = nullptr;

  /*!
   * \brief Constructor of the class.
   * \param[in] val_nDim - Number of dimensions of the problem.
   * \param[in] val_nVar - Number of variables of the problem.
   * \param[in] config - Definition of the particular problem.
   */
  CSourceBase_Flow(unsigned short val_nDim, unsigned short val_nVar, const CConfig* config);

public:
  /*!
   * \brief Destructor of the class.
   */
  ~CSourceBase_Flow() override;

};

/*!
 * \class CSourceAxisymmetric_Flow
 * \brief Class for source term for solving axisymmetric problems.
 * \ingroup SourceDiscr
 * \author F. Palacios
 */
class CSourceAxisymmetric_Flow final : public CSourceBase_Flow {
public:
  /*!
   * \brief Constructor of the class.
   * \param[in] val_nDim - Number of dimensions of the problem.
   * \param[in] val_nVar - Number of variables of the problem.
   * \param[in] config - Definition of the particular problem.
   */
  CSourceAxisymmetric_Flow(unsigned short val_nDim, unsigned short val_nVar, const CConfig* config);

  /*!
   * \brief Residual of the rotational frame source term.
   * \param[in] config - Definition of the particular problem.
   * \return Lightweight const-view of residual and Jacobian.
   */
  ResidualType<> ComputeResidual(const CConfig* config) override;

};

/*!
 * \class CSourceIncAxisymmetric_Flow
 * \brief Class for source term for solving incompressible axisymmetric problems.
 * \ingroup SourceDiscr
 * \author T. Economon
 */
class CSourceIncAxisymmetric_Flow final : public CSourceBase_Flow {
  bool implicit, /*!< \brief Implicit calculation. */
  viscous,       /*!< \brief Viscous incompressible flows. */
  energy;        /*!< \brief computation with the energy equation. */

public:
  /*!
   * \brief Constructor of the class.
   * \param[in] val_nDim - Number of dimensions of the problem.
   * \param[in] val_nVar - Number of variables of the problem.
   * \param[in] config - Definition of the particular problem.
   */
  CSourceIncAxisymmetric_Flow(unsigned short val_nDim, unsigned short val_nVar, const CConfig* config);

  /*!
   * \brief Residual of the rotational frame source term.
   * \param[in] config - Definition of the particular problem.
   * \return Lightweight const-view of residual and Jacobian.
   */
  ResidualType<> ComputeResidual(const CConfig* config) override;

};

/*!
 * \class CSourceBodyForce
 * \brief Class for the source term integration of a body force.
 * \ingroup SourceDiscr
 * \author T. Economon
 */
class CSourceBodyForce final : public CSourceBase_Flow {
  su2double Body_Force_Vector[3];

public:
  /*!
   * \param[in] val_nDim - Number of dimensions of the problem.
   * \param[in] val_nVar - Number of variables of the problem.
   * \param[in] config - Definition of the particular problem.
   */
  CSourceBodyForce(unsigned short val_nDim, unsigned short val_nVar, const CConfig* config);

  /*!
   * \brief Source term integration for a body force.
   * \param[in] config - Definition of the particular problem.
   * \return Lightweight const-view of residual and Jacobian.
   */
  ResidualType<> ComputeResidual(const CConfig* config) override;

};

/*!
 * \class CSourceIncBodyForce
 * \brief Class for the source term integration of a body force in the incompressible solver.
 * \ingroup SourceDiscr
 * \author T. Economon
 * \version 7.0.8 "Blackbird"
 */
class CSourceIncBodyForce final : public CSourceBase_Flow {
  su2double Body_Force_Vector[3];

public:
  /*!
   * \param[in] val_nDim - Number of dimensions of the problem.
   * \param[in] val_nVar - Number of variables of the problem.
   * \param[in] config - Definition of the particular problem.
   */
  CSourceIncBodyForce(unsigned short val_nDim, unsigned short val_nVar, const CConfig* config);

  /*!
   * \brief Source term integration for a body force.
   * \param[in] config - Definition of the particular problem.
   * \return Lightweight const-view of residual and Jacobian.
   */
  ResidualType<> ComputeResidual(const CConfig* config) override;

};

/*!
 * \class CSourceBoussinesq
 * \brief Class for the source term integration of the Boussinesq approximation for incompressible flow.
 * \ingroup SourceDiscr
 * \author T. Economon
 * \version 7.0.8 "Blackbird"
 */
class CSourceBoussinesq final : public CSourceBase_Flow {
  su2double Gravity_Vector[3];

public:
  /*!
   * \param[in] val_nDim - Number of dimensions of the problem.
   * \param[in] val_nVar - Number of variables of the problem.
   * \param[in] config - Definition of the particular problem.
   */
  CSourceBoussinesq(unsigned short val_nDim, unsigned short val_nVar, const CConfig* config);

  /*!
   * \brief Source term integration for the Boussinesq approximation.
   * \param[in] config - Definition of the particular problem.
   * \return Lightweight const-view of residual and Jacobian.
   */
  ResidualType<> ComputeResidual(const CConfig* config) override;

};

/*!
 * \class CSourceGravity
 * \brief Class for the source term integration of the gravity force.
 * \ingroup SourceDiscr
 * \author F. Palacios
 */
class CSourceGravity final : public CSourceBase_Flow {
  su2double Force_Ref;

public:
  /*!
   * \param[in] val_nDim - Number of dimensions of the problem.
   * \param[in] val_nVar - Number of variables of the problem.
   * \param[in] config - Definition of the particular problem.
   */
  CSourceGravity(unsigned short val_nDim, unsigned short val_nVar, const CConfig* config);

  /*!
   * \brief Source term integration for the poissonal potential.
   * \param[in] config - Definition of the particular problem.
   * \return Lightweight const-view of residual and Jacobian.
   */
  ResidualType<> ComputeResidual(const CConfig* config) override;

};

/*!
 * \class CSourceRotatingFrame_Flow
 * \brief Class for a rotating frame source term.
 * \ingroup SourceDiscr
 * \author F. Palacios, T. Economon.
 */
class CSourceRotatingFrame_Flow final : public CSourceBase_Flow {
public:
  /*!
   * \brief Constructor of the class.
   * \param[in] val_nDim - Number of dimensions of the problem.
   * \param[in] val_nVar - Number of variables of the problem.
   * \param[in] config - Definition of the particular problem.
   */
  CSourceRotatingFrame_Flow(unsigned short val_nDim, unsigned short val_nVar, const CConfig* config);

  /*!
   * \brief Residual of the rotational frame source term.
   * \param[in] config - Definition of the particular problem.
   * \return Lightweight const-view of residual and Jacobian.
   */
  ResidualType<> ComputeResidual(const CConfig* config) override;

};

/*!
 * \class CSourceIncRotatingFrame_Flow
 * \brief Class for a rotating frame source term.
 * \ingroup SourceDiscr
 */
class CSourceIncRotatingFrame_Flow final : public CSourceBase_Flow {

private:
  su2double Omega[3];  /*!< \brief Angular velocity */
  bool implicit; /*!< \brief Implicit calculation. */

public:
  /*!
   * \brief Constructor of the class.
   * \param[in] val_nDim - Number of dimensions of the problem.
   * \param[in] val_nVar - Number of variables of the problem.
   * \param[in] config - Definition of the particular problem.
   */
  CSourceIncRotatingFrame_Flow(unsigned short val_nDim, unsigned short val_nVar, const CConfig* config);

  /*!
   * \brief Residual of the rotational frame source term.
   * \param[in] config - Definition of the particular problem.
   * \return Lightweight const-view of residual and Jacobian.
   */
  ResidualType<> ComputeResidual(const CConfig* config) override;

};

/*!
 * \class CSourceWindGust
 * \brief Class for a source term due to a wind gust.
 * \ingroup SourceDiscr
 * \author S. Padrón
 */
class CSourceWindGust final : public CSourceBase_Flow {
public:
  /*!
   * \brief Constructor of the class.
   * \param[in] val_nDim - Number of dimensions of the problem.
   * \param[in] val_nVar - Number of variables of the problem.
   * \param[in] config - Definition of the particular problem.
   */
  CSourceWindGust(unsigned short val_nDim, unsigned short val_nVar, const CConfig* config);

  /*!
   * \brief Residual of the wind gust source term.
   * \param[in] config - Definition of the particular problem.
   * \return Lightweight const-view of residual and Jacobian.
   */
  ResidualType<> ComputeResidual(const CConfig* config) override;

};

/*!
 * \class CSourceIncStreamwise_Periodic
 * \brief Class for the source term integration of a streamwise periodic body force in the incompressible solver.
 * \ingroup SourceDiscr
 * \author T. Kattmann
 */
class CSourceIncStreamwise_Periodic final : public CSourceBase_Flow {
private:

  bool turbulent, /*!< \brief Turbulence model used. */
       energy,    /*!< \brief Energy equation on. */
       streamwisePeriodic_temperature; /*!< \brief Periodicity in energy equation */

  vector<su2double> Streamwise_Coord_Vector; /*!< \brief Translation vector between streamwise periodic surfaces. */

  su2double norm2_translation, /*!< \brief Square of distance between the 2 periodic surfaces. */
            integrated_heatflow,  /*!< \brief Total heat added into the domain via heatflux marker. */
            massflow,  /*!< \brief Massflow through streamwise periodic 'outlet' marker. */
            delta_p, /*!< \brief Value of prescribed pressure drop which results in an artificial body force vector. */
            dot_product, /*!< \brief Container for various dot-products. */
            scalar_factor; /*!< \brief Holds scalar factors to simplify final equations. */

  unsigned short iDim, /*!< brief Counts over Dimensions. */
                 iVar, jVar; /*!< brief Count over Variables. */

public:

  /*!
   * \brief Constructor of the class.
   * \param[in] val_nDim - Number of dimensions of the problem.
   * \param[in] val_nVar - Number of variables of the problem.
   * \param[in] config - Definition of the particular problem.
   */
  CSourceIncStreamwise_Periodic(unsigned short val_nDim,
                                unsigned short val_nVar,
                                CConfig        *config);

  /*!
   * \brief Source term integration for a body force.
   * \param[in] config - Definition of the particular problem.
   */
  ResidualType<> ComputeResidual(const CConfig *config) override;

};

/*!
 * \class CSourceIncStreamwisePeriodic_Outlet
 * \brief Class for the outlet heat sink. Acts like a heatflux boundary on the outlet and not as a volume source.
 * \ingroup SourceDiscr
 * \author T. Kattmann
 */
class CSourceIncStreamwisePeriodic_Outlet : public CSourceBase_Flow {
private:

  su2double 
  AxiFactor, /*!< brief Factor for axisymmetric simulations */
  FaceArea, /*!< brief Boundary face area */
  local_Massflow, /*!< brief massflow through that one boundary cell */
  AreaAvgInletTemp; /*!< brief Area avg inlet Temp. Computed in GetStreamwise_Periodic_Properties */

  unsigned short iDim, /*!< brief Counts over Dimensions. */
                 iVar, jVar; /*!< brief Count over Variables. */

public:

  /*!
   * \brief Constructor of the class.
   * \param[in] val_nDim - Number of dimensions of the problem.
   * \param[in] val_nVar - Number of variables of the problem.
   * \param[in] config - Definition of the particular problem.
   */
  CSourceIncStreamwisePeriodic_Outlet(unsigned short val_nDim,
                                      unsigned short val_nVar,
                                      CConfig        *config);

  /*!
   * \brief Source term integration for boundary heat sink.
   * \param[in] config - Definition of the particular problem.
   */
  ResidualType<> ComputeResidual(const CConfig *config) override;

};


/*!
 * \class CSourceRadiation
 * \brief Class for a source term due to radiation.
 * \ingroup SourceDiscr
 * \author Ruben Sanchez
 */
class CSourceRadiation : public CSourceBase_Flow {
private:
  bool implicit;

public:

  CSourceRadiation(unsigned short val_nDim, unsigned short val_nVar, const CConfig *config);

  /*!
   * \brief Source term integration for a radiation source.
   * \param[in] config - Definition of the particular problem.
   * \return Lightweight const-view of residual and Jacobian.
   */
  ResidualType<> ComputeResidual(const CConfig* config) override;

};
