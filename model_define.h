/*

Copyright © 2013 Battelle Memorial Institute. All Rights Reserved.

NOTICE:  These data were produced by Battelle Memorial Institute (BATTELLE) under Contract No. DE-AC05-76RL01830 with the U.S. Department of Energy (DOE).  For a five year period from May 28, 2013, the Government is granted for itself and others acting on its behalf a nonexclusive, paid-up, irrevocable worldwide license in this data to reproduce, prepare derivative works, and perform publicly and display publicly, by or on behalf of the Government.  There is provision for the possible extension of the term of this license.  Subsequent to that period or any extension granted, the Government is granted for itself and others acting on its behalf a nonexclusive, paid-up, irrevocable worldwide license in this data to reproduce, prepare derivative works, distribute copies to the public, perform publicly and display publicly, and to permit others to do so.  The specific term of the license can be identified by inquiry made to BATTELLE or DOE.  NEITHER THE UNITED STATES NOR THE UNITED STATES DEPARTMENT OF ENERGY, NOR BATTELLE, NOR ANY OF THEIR EMPLOYEES, MAKES ANY WARRANTY, EXPRESS OR IMPLIED, OR ASSUMES ANY LEGAL LIABILITY OR RESPONSIBILITY FOR THE ACCURACY, COMPLETENESS, OR USEFULNESS OF ANY DATA, APPARATUS, PRODUCT, OR PROCESS DISCLOSED, OR REPRESENTS THAT ITS USE WOULD NOT INFRINGE PRIVATELY OWNED RIGHTS.

*/

#ifndef __MY_DEFINE_H__
#define __MY_DEFINE_H__

#include "biocellion.h"

/* define constants to be used inside model functions */

/* MODEL START */

const REAL IF_GRID_SPACING = 10.0;
const REAL EPSILON = 1e-20;

typedef enum _cell_type_e {
	CELL_TYPE_WATER,
	CELL_TYPE_GLYCEROL,
	CELL_TYPE_FATTY_ACIDS,
	NUM_CELL_TYPES
} cell_type_e;

typedef enum _cell_quality_e {
		CELL_QUALITY_HYDROPHOBIC,
		CELL_QUALITY_HYDROPHILIC,
		NUM_CELL_QUALITIES,
} cell_quality_e;

typedef enum _cell_mech_real_e {
        CELL_MECH_REAL_FORCE_X,/* shoving & adhesion */
        CELL_MECH_REAL_FORCE_Y,/* shoving & adhesion */
        CELL_MECH_REAL_FORCE_Z,/* shoving & adhesion */
        NUM_CELL_MECH_REALS
} cell_mech_real_e;

const REAL A_CELL_RADIUS[NUM_CELL_TYPES] = { 4.0, 4.0, 4.0 };
const REAL A_CELL_DENSITY_PER_UB[NUM_CELL_TYPES] = { 0.8, 0.3, 0.3 };
const REAL A_CELL_D_MAX[NUM_CELL_TYPES] = { 10.0, 10.0 };
const REAL A_CELL_QUALITY_MAPPING[NUM_CELL_TYPES] = {
	CELL_QUALITY_HYDROPHILIC,
	CELL_QUALITY_HYDROPHILIC,
	CELL_QUALITY_HYDROPHOBIC,
};

const REAL ADHESION_S = 0.5;
const REAL RANDOM_VIBRATION_SCALE = 0.05;

const REAL BASELINE_TIME_STEP_DURATION = 10.0;

/* MODEL END */

#endif/* #ifndef __MY_DEFINE_H__ */

