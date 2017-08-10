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

#include "mesh_multiplePtr.h"
#include <unistd.h>
#include "teem/air.h"

void WriteFile(Nrrd *nData, int type, char *Outfile){
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
void callDiderot(char *Outfile, int type, void *valF, void *valM, void *valS, int imgRes){
  
    mesh_multiplePtr_world_t *wrld = mesh_multiplePtr_new_world ();
    
    if (wrld == 0) {
	//fprintf (stderr, "Unable to create Diderot world\n");
	exit (1);
    }
    mesh_multiplePtr_init_world (wrld);//initialize it.
    //initialize input vars
    mesh_multiplePtr_input_set_f (wrld, valF);
    mesh_multiplePtr_input_set_m (wrld, valM);
    mesh_multiplePtr_input_set_s (wrld, valS);
    
    
    mesh_multiplePtr_input_set_imgRes(wrld, imgRes);

    // need to add datafile to input
    
    // nrrd for getting computational state
    Nrrd *nData = nrrdNew();

    if (mesh_multiplePtr_init_world (wrld)) {//intialize set of strands
        // error
        fprintf(stderr, "Error initializing world: %s", mesh_multiplePtr_get_errors(wrld));
        exit(1);
    }

    int nSteps = mesh_multiplePtr_run (wrld, 0);
    nrrdSave("diderot/data/kitten.txt", nData, NULL);
    
    //second paramter is the limit to # of steps.
    //0-to termination
/*
    // change here for output var
    if (mesh_multiplePtr_output_get_out(wrld, nData)) {
        // error
        fprintf(stderr, "Error getting nrrd data: %s", mesh_multiplePtr_get_errors(wrld));
        exit(1);
    }
*/
    WriteFile(nData, type, Outfile);
    mesh_multiplePtr_shutdown (wrld);

}
//
