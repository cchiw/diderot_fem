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

#include "mesh_d2s_twofields.h"
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
void callDiderot(char *Outfile, int type, void *valM, void *valN, int imgRes){
  
    mesh_d2s_twofields_world_t *wrld = mesh_d2s_twofields_new_world ();
    
    if (wrld == 0) {
	//fprintf (stderr, "Unable to create Diderot world\n");
	exit (1);
    }
    mesh_d2s_twofields_init_world (wrld);//initialize it.
    //initialize input vars
    mesh_d2s_twofields_input_set_f (wrld, valM);
        mesh_d2s_twofields_input_set_g (wrld, valN);
    mesh_d2s_twofields_input_set_imgRes(wrld, imgRes);

    // need to add datafile to input
    
    // nrrd for getting computational state
    Nrrd *nData = nrrdNew();

    if (mesh_d2s_twofields_init_world (wrld)) {//intialize set of strands
        // error
        fprintf(stderr, "Error initializing world: %s", mesh_d2s_twofields_get_errors(wrld));
        exit(1);
    }

    int nSteps = mesh_d2s_twofields_run (wrld, 0);
    nrrdSave("diderot/data/kitten.txt", nData, NULL);
    
    //second paramter is the limit to # of steps.
    //0-to termination
/*
    // change here for output var
    if (mesh_d2s_twofields_output_get_out(wrld, nData)) {
        // error
        fprintf(stderr, "Error getting nrrd data: %s", mesh_d2s_twofields_get_errors(wrld));
        exit(1);
    }
*/
    WriteFile(nData, type, Outfile);
    mesh_d2s_twofields_shutdown (wrld);

}
//
