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

#include "basic_d2s_sample.h"
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
  
    basic_d2s_sample_World_t *wrld = basic_d2s_sample_New ();
    
    if (wrld == 0) {
	//fprintf (stderr, "Unable to create Diderot world\n");
	exit (1);
    }
    
    basic_d2s_sample_Init (wrld);//initialize it.
    //initialize input vars
    basic_d2s_sample_InVarSet_m (wrld, valM);
    basic_d2s_sample_InVarSet_stepSize(wrld,stepSize);
    basic_d2s_sample_InVarSet_imgResU(wrld,imgResU);
    basic_d2s_sample_InVarSet_imgResV(wrld,imgResV);
    
    // nrrd for getting computational state
    Nrrd *nData = nrrdNew();
    
    if (basic_d2s_sample_Initially (wrld)) {//intialize set of strands
        // error
	fprintf(stderr, "Error initializing world: %s", basic_d2s_sample_GetErrors(wrld));
	exit(1);
    }
    int nSteps = basic_d2s_sample_Run (wrld, 0);
    //second paramter is the limit to # of steps.
    //0-to termination
    
    // change here for output var
    if (basic_d2s_sample_OutputGet_out(wrld, nData)) {
        // error
	fprintf(stderr, "Error getting nrrd data: %s", basic_d2s_sample_GetErrors(wrld));
	exit(1);
    }

    WriteFile(nData, type, Outfile);
    basic_d2s_sample_Shutdown (wrld);

}
//
