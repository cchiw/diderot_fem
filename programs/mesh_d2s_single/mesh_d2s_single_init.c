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

#include "mesh_d2s_single.h"
#include <unistd.h>
#include "teem/air.h"

void WriteFile(Nrrd *nData, int type, char *Outfile){
  printf("Hello!\n");
    if(type == 0){
        if(nrrdSave(Outfile, nData, NULL)) {
            exit(1);
        }
    }
    else{
        Nrrd *ntmp = nrrdNew();
        nrrdQuantize(ntmp, nData, NULL, 8);
        nrrdSave(Outfile, ntmp, NULL);
    }
    nrrdNuke(nData);
    return;
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

void callDiderot(char *Outfile, int type, void *valM, int imgRes){
  
    mesh_d2s_single_world_t *wrld = mesh_d2s_single_new_world ();
    /* struct Function *g = (struct Function *) valM; */
    /* printf("cell pt agg: %d\n",g->NumCells); */
    printf("callDiderot 1!");

    
    if (wrld == 0) {
	//fprintf (stderr, "Unable to create Diderot world\n");
	exit (1);
    }
    mesh_d2s_single_init_world (wrld);//initialize it.
    mesh_d2s_single_set_verbose(wrld,true);
    //initialize input vars
    printf("callDiderot 2!");
    // mesh_d2s_single_input_set_f (wrld, valM);
    //mesh_d2s_single_input_set_imgRes(wrld, imgRes);

    // need to add datafile to input
    
    // nrrd for getting computational state
    Nrrd *nData = nrrdNew();
    printf("callDiderot 3!");
    /* if (mesh_d2s_single_init_world (wrld)) {//intialize set of strands */
    /*     // error */
    /*     fprintf(stderr, "Error initializing world: %s", mesh_d2s_single_get_errors(wrld)); */
    /*     exit(1); */
    /* } */
    /* if (mesh_d2s_single_create_strands (wrld)) {//intialize set of strands */
    /*     // error */
    /*     fprintf(stderr, "Error initializing world: %s", mesh_d2s_single_get_errors(wrld)); */
    /*     exit(1); */
    /* } */
    printf("callDiderot 4!");
    int nSteps = mesh_d2s_single_run (wrld, 0);
    printf("callDiderot 5!");

    nrrdSave("kitten", nData, NULL);
    
    //second paramter is the limit to # of steps.
    //0-to termination
    printf("callDiderot 5!");
    // change here for output var
    if (mesh_d2s_single_output_get_out(wrld, nData)) {
        // error
        fprintf(stderr, "Error getting nrrd data: %s", mesh_d2s_single_get_errors(wrld));
        exit(1);
    }
    printf("callDiderot 6!");
    WriteFile(nData, type, Outfile);
    mesh_d2s_single_shutdown (wrld);
    printf("callDiderot 7!");

}
//
