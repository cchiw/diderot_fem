/*---------- begin lib-h-head.in ----------*/
/*! \file mesh_step.h
 *
 * C interface to library generated from mesh_step.diderot.
 *
 * Command: /Users/chariseechiw/diderot/femprime/bin/diderotc --log --namespace=mesh_step mesh_step.diderot
 * Version: vis15:2016-07-29
 */

#ifndef _MESH_STEP_H_
#define _MESH_STEP_H_

#define DIDEROT_SINGLE_PRECISION
#define DIDEROT_INT
#define DIDEROT_TARGET_SEQUENTIAL

#include "diderot/config.h"

#if defined(HAVE_STDBOOL_H)
#  include <stdbool.h>
#elif !defined(__bool_true_false_are_defined)
#  ifndef HAVE__BOOL
#    ifdef __cplusplus
       typedef bool _Bool;
#    else
#      define _Bool signed char
#    endif
#  endif
#  define bool _Bool
#  define false 0
#  define true 1
#  define __bool_true_false_are_defined 1
#endif

#include <stdint.h>
#include <string.h>
#include "teem/nrrd.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct mesh_step_struct_world mesh_step_world_t;
/*---------- end lib-h-head.in ----------*/

/**** Functions etc. for input variables ****/
bool mesh_step_input_set_imgRes (mesh_step_world_t *wrld, int32_t v);
bool mesh_step_input_set_stepSize (mesh_step_world_t *wrld, float v);
bool mesh_step_input_set_f (mesh_step_world_t *wrld, void *v);
/*---------- begin lib-h-body.in ----------*/

/***** World query operations *****/

//! Return the total number of strands (active+stable) in the world
uint32_t mesh_step_num_strands (mesh_step_world_t *wrld);

//! Return the total number of active strands
uint32_t mesh_step_num_active_strands (mesh_step_world_t *wrld);

//! Return the total number of stable strands
uint32_t mesh_step_num_stable_strands (mesh_step_world_t *wrld);

//! Return true if there are any recorded error conditions
bool mesh_step_any_errors (mesh_step_world_t *wrld);

//! Return the pending error message (if any).  This call clears the pending error
//! state.
char *mesh_step_get_errors (mesh_step_world_t *wrld);

/***** Program running operations *****/

//! Allocate the program's world
//! \return the new world or NULL if there are any errors
mesh_step_world_t *mesh_step_new_world ();

//! Initialize the execution state for the world.  This includes allocating processor
//! and GPU resources for parallel execution.
//! \param wrld the world-state of the Diderot program
//! \return true if there are any errors
bool mesh_step_init_world (mesh_step_world_t *wrld);

//! Initiaize the globals and create the initial set of strands
//! \param wrld the world-state of the Diderot program
//! \return true if there are any errors
bool mesh_step_create_strands (mesh_step_world_t *wrld);

//! Run the Diderot program
//! \param wrld the world-state of the Diderot program
//! \param maxNSteps the limit on the number of super steps; 0 means unlimited
//! \return the number of steps taken.
uint32_t mesh_step_run (mesh_step_world_t *wrld, uint32_t maxNSteps);

//! shutdown and deallocate the world
void mesh_step_shutdown (mesh_step_world_t *wrld);

/***** Runtime options *****/

//! Set verbose mode
void mesh_step_set_verbose (mesh_step_world_t *wrld, bool mode);

//! Get verbose mode
bool mesh_step_get_verbose (mesh_step_world_t *wrld);
/*---------- end lib-h-body.in ----------*/

/**** Getters for output values ****/
bool mesh_step_output_get_out (mesh_step_world_t *wrld, Nrrd *data);
/*---------- begin lib-h-foot.in ----------*/

#ifdef __cplusplus
}
#endif

#endif /* !_MESH_STEP_H_ */
/*---------- end lib-h-foot.in ----------*/
