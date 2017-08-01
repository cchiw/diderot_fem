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

#include "data_d2s.h"
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
void callDiderot(char *Outfile, int type, void *valM, int imgResU,int imgResV,  float stepSize){
  
    data_d2s_world_t *wrld = data_d2s_new_world ();
    
    if (wrld == 0) {
	//fprintf (stderr, "Unable to create Diderot world\n");
	exit (1);
    }
    data_d2s_init_world (wrld);//initialize it.
    //initialize input vars
    data_d2s_input_set_f (wrld, valM);
    data_d2s_input_set_stepSize(wrld,stepSize);
    data_d2s_input_set_imgResU(wrld,imgResU);
    data_d2s_input_set_imgResV(wrld,imgResV);
    // need to add datafile to input
    
    // nrrd for getting computational state
    Nrrd *nData = nrrdNew();

    if (data_d2s_init_world (wrld)) {//intialize set of strands
        // error
        fprintf(stderr, "Error initializing world: %s", data_d2s_get_errors(wrld));
        exit(1);
    }

    int nSteps = data_d2s_run (wrld, 0);
    nrrdSave("diderot/data/kitten.txt", nData, NULL);
    
    //second paramter is the limit to # of steps.
    //0-to termination
/*
    // change here for output var
    if (data_d2s_output_get_out(wrld, nData)) {
        // error
        fprintf(stderr, "Error getting nrrd data: %s", data_d2s_get_errors(wrld));
        exit(1);
    }
*/
    WriteFile(nData, type, Outfile);
    data_d2s_shutdown (wrld);

}
//
