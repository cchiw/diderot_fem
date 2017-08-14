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

#include "simple.h"
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

int main(){
  
  int type = 0;
  void *valM = 0;
  int  imgRes = 10;
    simple_world_t *wrld = simple_new_world ();
    /* struct Function *g = (struct Function *) valM; */
    /* printf("cell pt agg: %d\n",g->NumCells); */
    printf("callDiderot 1!");

    
    if (wrld == 0) {
	//fprintf (stderr, "Unable to create Diderot world\n");
	exit (1);
    }
    simple_init_world (wrld);//initialize it.
    simple_set_verbose(wrld,true);
    //initialize input vars
    printf("callDiderot 2!");
    // simpleinput_set_f (wrld, valM);
    //simpleinput_set_imgRes(wrld, imgRes);

    // need to add datafile to input
    
    // nrrd for getting computational state
    Nrrd *nData = nrrdNew();
    printf("callDiderot 3!");
    /* if (simpleinit_world (wrld)) {//intialize set of strands */
    /*     // error */
    /*     fprintf(stderr, "Error initializing world: %s", simpleget_errors(wrld)); */
    /*     exit(1); */
    /* } */
    /* if (simplecreate_strands (wrld)) {//intialize set of strands */
    /*     // error */
    /*     fprintf(stderr, "Error initializing world: %s", simpleget_errors(wrld)); */
    /*     exit(1); */
    /* } */
    printf("callDiderot 4!");
    int nSteps = simple_run (wrld, 0);
    printf("callDiderot 5!");

    nrrdSave("kitten1", nData, NULL);
    
    //second paramter is the limit to # of steps.
    //0-to termination
    printf("callDiderot 5!");
    // change here for output var
    if (simple_output_get_out(wrld, nData)) {
        // error
        fprintf(stderr, "Error getting nrrd data: %s", simple_get_errors(wrld));
        exit(1);
    }
    printf("callDiderot 6!");
    WriteFile(nData, 0, "kitten2");
    simple_shutdown (wrld);
    printf("callDiderot 7!");

}
//
