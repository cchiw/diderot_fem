/*---------- begin lib-h-head.in ----------*/
/*! \file mesh_d2s_single.h
 *
 * C interface to library generated from mesh_d2s_single.diderot.
 *
 * Command: /home/teodoro/gitcode/again/femprime/bin/diderotc --log --double --namespace=mesh_d2s_single --double --debug mesh_d2s_single.diderot
 * Version: vis15:2016-07-29
 */

#ifndef _MESH_D2S_SINGLE_H_
#define _MESH_D2S_SINGLE_H_

#define DIDEROT_DOUBLE_PRECISION
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

typedef struct mesh_d2s_single_struct_world mesh_d2s_single_world_t;
/*---------- end lib-h-head.in ----------*/

/**** Functions etc. for input variables ****/
void mesh_d2s_single_input_get_imgRes (mesh_d2s_single_world_t *wrld, int32_t *v);
bool mesh_d2s_single_input_set_imgRes (mesh_d2s_single_world_t *wrld, int32_t v);
bool mesh_d2s_single_input_set_f (mesh_d2s_single_world_t *wrld, void *v);
void mesh_d2s_single_input_get_stepSize (mesh_d2s_single_world_t *wrld, double *v);
bool mesh_d2s_single_input_set_stepSize (mesh_d2s_single_world_t *wrld, double v);
/*---------- begin lib-h-body.in ----------*/

/***** World query operations *****/

//! Return the total number of strands (active+stable) in the world
uint32_t mesh_d2s_single_num_strands (mesh_d2s_single_world_t *wrld);

//! Return the total number of active strands
uint32_t mesh_d2s_single_num_active_strands (mesh_d2s_single_world_t *wrld);

//! Return the total number of stable strands
uint32_t mesh_d2s_single_num_stable_strands (mesh_d2s_single_world_t *wrld);

//! Return true if there are any recorded error conditions
bool mesh_d2s_single_any_errors (mesh_d2s_single_world_t *wrld);

//! Return the pending error message (if any).  This call clears the pending error
//! state.
char *mesh_d2s_single_get_errors (mesh_d2s_single_world_t *wrld);

/***** Program running operations *****/

//! Allocate the program's world
//! \return the new world or NULL if there are any errors
mesh_d2s_single_world_t *mesh_d2s_single_new_world ();

//! Initialize the execution state for the world.  This includes allocating processor
//! and GPU resources for parallel execution.
//! \param wrld the world-state of the Diderot program
//! \return true if there are any errors
bool mesh_d2s_single_init_world (mesh_d2s_single_world_t *wrld);

//! Initiaize the globals and create the initial set of strands
//! \param wrld the world-state of the Diderot program
//! \return true if there are any errors
bool mesh_d2s_single_create_strands (mesh_d2s_single_world_t *wrld);

//! Run the Diderot program
//! \param wrld the world-state of the Diderot program
//! \param maxNSteps the limit on the number of super steps; 0 means unlimited
//! \return the number of steps taken.
uint32_t mesh_d2s_single_run (mesh_d2s_single_world_t *wrld, uint32_t maxNSteps);

//! shutdown and deallocate the world
void mesh_d2s_single_shutdown (mesh_d2s_single_world_t *wrld);

/***** Runtime options *****/

//! Set verbose mode
void mesh_d2s_single_set_verbose (mesh_d2s_single_world_t *wrld, bool mode);

//! Get verbose mode
bool mesh_d2s_single_get_verbose (mesh_d2s_single_world_t *wrld);
/*---------- end lib-h-body.in ----------*/

/**** Getters for output values ****/
bool mesh_d2s_single_output_get_out (mesh_d2s_single_world_t *wrld, Nrrd *data);
/*---------- begin lib-h-foot.in ----------*/

#ifdef __cplusplus
}
#endif

#endif /* !_MESH_D2S_SINGLE_H_ */
/*---------- end lib-h-foot.in ----------*/
