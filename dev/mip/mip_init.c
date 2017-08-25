/*! \file init.c
 *
 * \author Charisee
 */

/*
 * This code is part of the Diderot Project (http://diderot-language.cs.uchicago.edu)
 *
 * COPYRIGHT (c) 2015 The University of Chicago
 * All rights reserved.
 */

#include <stdlib.h>
#include <stdio.h>
#include "mip.h"

void fail (const char *msg, mip_world_t *wrld)
{
    if ((wrld == 0) || !mip_any_errors(wrld)) {
        fprintf(stderr, "Error: %s\n", msg);
    }
    else {
        fprintf(stderr, "Error: %s\n%s\n", msg, mip_get_errors(wrld));
    }
    exit (1);
}

//struct Function;
struct Function {
  int Gdmin;
  int Sdmin;
  int NumCells;
  int ** CellToNode;
  int ** NodeToCoords;
  float ** NodeToPoint;
  float * Coords;
};

void callDiderot_mip(char *Outfile, int type, void *valM, int imgRes,  float rayStep){
  
    mip_world_t *wrld = mip_new_world ();
    if (wrld == 0) {
      fail ("unable to create world",0);
    }

    if (mip_init_world(wrld)){
      fail ("unable to init world",wrld);
    }

    if (mip_input_set_imgResU (wrld, imgRes)) {
        fail ("unable to initialize imgRes", wrld);
    }
    if (mip_input_set_imgResV (wrld, imgRes)) {
        fail ("unable to initialize imgRes", wrld);
    }
    if (mip_input_set_rayStep (wrld,  rayStep)) {
        fail ("unable to initialize  rayStep", wrld);
    }
    if (mip_input_set_f (wrld, valM)) {
        fail ("unable to initialize imgRed", wrld);
    }

    if (mip_create_strands (wrld)) {
        fail ("unable to create initial strands", wrld);
    }
    
    uint32_t nsteps = mip_run (wrld, 0);
    if (nsteps == 0) {
        fail ("no steps taken", wrld);
    }
    
    Nrrd *nData = nrrdNew();
    if (nData == 0) {
        fail ("unable to allocate nrrd for output", 0);
    }
    if (mip_output_get_out (wrld, nData)) {
        fail ("problem getting output", wrld);
    }
    if (nrrdSave(Outfile, nData, 0)) {
        char *err = biffGetDone(NRRD);
        fprintf (stderr, "Error: trouble writing output:\n%s", err);
        free (err);
        exit (1);
    }
    
    nrrdNuke (nData);
    mip_shutdown (wrld);
    
}
