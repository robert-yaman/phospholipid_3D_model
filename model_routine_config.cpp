/*

Copyright © 2013 Battelle Memorial Institute. All Rights Reserved.

NOTICE:  These data were produced by Battelle Memorial Institute (BATTELLE) under Contract No. DE-AC05-76RL01830 with the U.S. Department of Energy (DOE).  For a five year period from May 28, 2013, the Government is granted for itself and others acting on its behalf a nonexclusive, paid-up, irrevocable worldwide license in this data to reproduce, prepare derivative works, and perform publicly and display publicly, by or on behalf of the Government.  There is provision for the possible extension of the term of this license.  Subsequent to that period or any extension granted, the Government is granted for itself and others acting on its behalf a nonexclusive, paid-up, irrevocable worldwide license in this data to reproduce, prepare derivative works, distribute copies to the public, perform publicly and display publicly, and to permit others to do so.  The specific term of the license can be identified by inquiry made to BATTELLE or DOE.  NEITHER THE UNITED STATES NOR THE UNITED STATES DEPARTMENT OF ENERGY, NOR BATTELLE, NOR ANY OF THEIR EMPLOYEES, MAKES ANY WARRANTY, EXPRESS OR IMPLIED, OR ASSUMES ANY LEGAL LIABILITY OR RESPONSIBILITY FOR THE ACCURACY, COMPLETENESS, OR USEFULNESS OF ANY DATA, APPARATUS, PRODUCT, OR PROCESS DISCLOSED, OR REPRESENTS THAT ITS USE WOULD NOT INFRINGE PRIVATELY OWNED RIGHTS.

*/

/* DO NOT USE FUNCTIONS THAT ARE NOT THREAD SAFE (e.g. rand(), use Util::getModelRand() instead) */

#include "biocellion.h"

#include "model_routine.h"

/* MODEL START */

#include "model_define.h"

/* MODEL END */

using namespace std;

void ModelRoutine::updateIfGridSpacing( REAL& ifGridSpacing ) {
	/* MODEL START */

	ifGridSpacing = IF_GRID_SPACING;/* sets the grid resolution */

	/* MODEL END */

	return;
}

void ModelRoutine::updateOptModelRoutineCallInfo( OptModelRoutineCallInfo& callInfo ) {
	/* MODEL START */

	callInfo.numComputeMechIntrctIters = 1;
	callInfo.numUpdateIfGridVarPreStateAndGridStepIters = 0;
	callInfo.numUpdateIfGridVarPostStateAndGridStepIters = 0;

	/* MODEL END */

	return;
}

void ModelRoutine::updateDomainBdryType( domain_bdry_type_e a_domainBdryType[DIMENSION] ) {
	/* MODEL START */

	CHECK( DIMENSION == 3 );

	for( S32 dim = 0 ; dim < DIMENSION ; dim++ ) {
		a_domainBdryType[dim] = DOMAIN_BDRY_TYPE_NONPERIODIC_HARD_WALL;
	}

	/* MODEL END */

	return;
}

void ModelRoutine::updatePDEBufferBdryType( pde_buffer_bdry_type_e& pdeBufferBdryType ) {
	/* MODEL START */

	pdeBufferBdryType = PDE_BUFFER_BDRY_TYPE_HARD_WALL;/* relevant to agents only ( not a PDE boundary condition), agents cannot penetrate into the PDE buffer region */

	/* MODEL END */

	return;
}

void ModelRoutine::updateTimeStepInfo( TimeStepInfo& timeStepInfo ) {
	/* MODEL START */

	timeStepInfo.durationBaselineTimeStep = BASELINE_TIME_STEP_DURATION;
	timeStepInfo.numStateAndGridTimeStepsPerBaseline = 0;

	/* MODEL END */

	return;
}

void ModelRoutine::updateSyncMethod( sync_method_e& mechIntrctSyncMethod, sync_method_e& updateIfGridVarSyncMethod/* dummy if both callUpdateIfGridVarPreStateAndGridStep and callUpdateIfGridVarPostStateAndGridStep are set to false in ModelRoutine::updateOptModelRoutineCallInfo */ ) {
	/* MODEL START */

	mechIntrctSyncMethod = SYNC_METHOD_PER_ATTR;
	updateIfGridVarSyncMethod = SYNC_METHOD_PER_ATTR;

	/* MODEL END */

	return;
}

#if HAS_SPAGENT
void ModelRoutine::updateSpAgentInfo( Vector<SpAgentInfo>& v_spAgentInfo ) {/* set the mechanical interaction range & the numbers of model specific variables */
	/* MODEL START */

	MechModelVarInfo modelVarInfo;

/* Since dist is modified for many different mechanical interacitons, specfiy that we want to sum them all here. */
	modelVarInfo.syncMethod = VAR_SYNC_METHOD_DELTA;/* computeMechIntrct */

	v_spAgentInfo.resize( NUM_CELL_TYPES );

	for( S32 i = 0 ; i < NUM_CELL_TYPES ; i++ ) {
		SpAgentInfo info;

		info.dMax = A_CELL_D_MAX[i];
		CHECK( info.dMax <= IF_GRID_SPACING );
		info.numBoolVars = 0;
		info.numStateModelReals = 0;
		info.numStateModelInts = 0;
		/* |assign| repeats modelVarInfo the specified number of times. */
		info.v_mechIntrctModelRealInfo.assign( NUM_CELL_MECH_REALS, modelVarInfo );
		info.v_mechIntrctModelIntInfo.clear();
		info.v_odeNetInfo.clear();

		v_spAgentInfo[i] = info;
	}

	/* MODEL END */

	return;
}
#endif

void ModelRoutine::updateJunctionEndInfo( Vector<JunctionEndInfo>& v_junctionEndInfo ) {/* set the numbers of model specific variables */
	/* MODEL START */

	v_junctionEndInfo.clear();

	/* MODEL END */

	return;
}

void ModelRoutine::updatePhiPDEInfo( Vector<PDEInfo>& v_phiPDEInfo ) {
	/* MODEL START */

	v_phiPDEInfo.clear();

	/* MODEL END */

	return;
}

void ModelRoutine::updateIfGridModelVarInfo( Vector<IfGridModelVarInfo>& v_ifGridModelRealInfo, Vector<IfGridModelVarInfo>& v_ifGridModelIntInfo ) {
	/* MODEL START */

	v_ifGridModelRealInfo.clear();
	v_ifGridModelIntInfo.clear();

	/* MODEL END */

	return;
}

void ModelRoutine::updateRNGInfo( Vector<RNGInfo>& v_rngInfo ) {
	/* MODEL START */

	CHECK( NUM_MODEL_RNGS == 1 );

	RNGInfo rngInfo;

	rngInfo.type = RNG_TYPE_UNIFORM;
	rngInfo.param0 = 0.0;
	rngInfo.param1 = 1.0;
	rngInfo.param2 = 0.0;/* dummy */

	v_rngInfo.push_back( rngInfo );

	/* MODEL END */

	return;
}

void ModelRoutine::updateFileOutputInfo( FileOutputInfo& fileOutputInfo ) {
	/* MODEL START */

	fileOutputInfo.particleOutput = true;
	fileOutputInfo.v_particleExtraOutputScalarVarName.clear();
	fileOutputInfo.v_particleExtraOutputVectorVarName.clear();
	fileOutputInfo.v_gridPhiOutput.clear();
	fileOutputInfo.v_gridPhiOutputDivideByKappa.clear();

	/* MODEL END */

	return;
}

void ModelRoutine::updateSummaryOutputInfo( Vector<SummaryOutputInfo>& v_summaryOutputRealInfo, Vector<SummaryOutputInfo>& v_summaryOutputIntInfo ) {
	/* MODEL START */

	v_summaryOutputRealInfo.clear();
	v_summaryOutputIntInfo.clear();

	/* MODEL END */

	return;
}

void ModelRoutine::initGlobal( Vector<U8>& v_globalData ) {/* called once per simulation */
	/* MODEL START */

	/* nothing to do */

	/* MODEL END */

	return;
}

void ModelRoutine::init( void ) {/* called once per (MPI) process */
	/* MODEL START */

	/* nothing to do */

	/* MODEL END */

	return;
}

void ModelRoutine::term( void ) {/* called once per (MPI) process */
	/* MODEL START */

	/* nothing to do */

	/* MODEL END */

	return;
}

void ModelRoutine::setPDEBuffer( const VIdx& startVIdx, const VIdx& regionSize, BOOL& isPDEBuffer ) {
	/* MODEL START */

	isPDEBuffer = false;

	/* MODEL END */

	return;
}

void ModelRoutine::setHabitable( const VIdx& vIdx, BOOL& isHabitable ) {
	/* MODEL START */

	isHabitable = true;

	/* MODEL END */

	return;
}

