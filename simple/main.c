

#include <stdlib.h>
#include <stdio.h>
#include "simple.h"

void fail (const char *msg, simple_world_t *wrld)
{
    if ((wrld == 0) || !simple_any_errors(wrld)) {
        fprintf(stderr, "Error: %s\n", msg);
    }
    else {
        fprintf(stderr, "Error: %s\n%s\n", msg, simple_get_errors(wrld));
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

int main ()
{
    simple_world_t *wrld = simple_new_world ();
    if (wrld == 0) {
        fail ("unable to create world", 0);
    }
    
    if (simple_init_world (wrld)) {
        fail ("unable to initialize world", wrld);
    }
    

     
    if (simple_input_set_imgRes (wrld, 4)) {
        fail ("unable to initialize imgRed", wrld);
    }

    if (simple_create_strands (wrld)) {
        fail ("unable to create initial strands", wrld);
    }
    
    uint32_t nsteps = simple_run (wrld, 0);
    if (nsteps == 0) {
        fail ("no steps taken", wrld);
    }
    
    Nrrd *nData = nrrdNew();
    if (nData == 0) {
        fail ("unable to allocate nrrd for output", 0);
    }
    if (simple_output_get_out (wrld, nData)) {
        fail ("problem getting output", wrld);
    }
    if (nrrdSave("out.nrrd", nData, 0)) {
        char *err = biffGetDone(NRRD);
        fprintf (stderr, "Error: trouble writing output:\n%s", err);
        free (err);
        exit (1);
    }
    
    nrrdNuke (nData);
    simple_shutdown (wrld);
    
    return 0;
}
