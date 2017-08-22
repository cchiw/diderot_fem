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
#include "inside.h"

void fail (const char *msg, inside_world_t *wrld)
{
    if ((wrld == 0) || !inside_any_errors(wrld)) {
        fprintf(stderr, "Error: %s\n", msg);
    }
    else {
        fprintf(stderr, "Error: %s\n%s\n", msg, inside_get_errors(wrld));
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

void callDiderot_inside(char *Outfile, int type, void *valM, int imgRes, float stepSize){
  
    inside_world_t *wrld = inside_new_world ();
    if (wrld == 0) {
      fail ("unable to create world",0);
    }

    if (inside_init_world(wrld)){
      fail ("unable to init world",wrld);
    }

    if (inside_input_set_imgRes (wrld, imgRes)) {
        fail ("unable to initialize imgRes", wrld);
    }
    if (inside_input_set_stepSize (wrld, stepSize)) {
        fail ("unable to initialize stepSize", wrld);
    }    
    if (inside_input_set_f (wrld, valM)) {
        fail ("unable to initialize imgRed", wrld);
    }

    if (inside_create_strands (wrld)) {
        fail ("unable to create initial strands", wrld);
    }
    
    uint32_t nsteps = inside_run (wrld, 0);
    if (nsteps == 0) {
        fail ("no steps taken", wrld);
    }
    
    Nrrd *nData = nrrdNew();
    if (nData == 0) {
        fail ("unable to allocate nrrd for output", 0);
    }
    if (inside_output_get_out (wrld, nData)) {
        fail ("problem getting output", wrld);
    }
    if (nrrdSave(Outfile, nData, 0)) {
        char *err = biffGetDone(NRRD);
        fprintf (stderr, "Error: trouble writing output:\n%s", err);
        free (err);
        exit (1);
    }
    
    nrrdNuke (nData);
    inside_shutdown (wrld);
    
}
