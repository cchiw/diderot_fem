/*---------- begin lib-cxx-head.in ----------*/
/*! \file simple.cxx
 *
 * Generated from simple.diderot.
 *
 * Command: /home/teodoro/gitcode/again/femprime/bin/diderotc --namespace=simple --target=pthread --debug simple.diderot
 * Version: vis15:2016-07-29
 */
/*---------- end lib-cxx-head.in ----------*/

#define DIDEROT_NO_INPUTS
#define DIDEROT_STRAND_ARRAY
/*---------- begin lib-cxx-incl.in ----------*/
#include "simple.h"
#include "diderot/diderot.hxx"

#ifdef DIDEROT_ENABLE_LOGGING
#define IF_LOGGING(...)         __VA_ARGS__
#else
#define IF_LOGGING(...)
#endif

static std::string ProgramName = "simple";
/*---------- end lib-cxx-incl.in ----------*/

// ***** No synthesized types *****

/*---------- begin namespace-open.in ----------*/
namespace simple {

static std::string ProgramName = "simple";

struct world;
struct sample_strand;
/*---------- end namespace-open.in ----------*/

/*---------- begin nrrd-save-helper.in ----------*/
/* helper function for saving output to nrrd file */
inline bool nrrd_save_helper (std::string const &file, Nrrd *nrrd)
{
    if (nrrdSave (file.c_str(), nrrd, nullptr)) {
        std::cerr << "Error saving \"" << file << "\":\n" << biffGetDone(NRRD) << std::endl;
        return true;
    }
    else {
        return false;
    }
}
/*---------- end nrrd-save-helper.in ----------*/

struct globals {
    int32_t gv_imgRes;
};
struct sample_strand {
    float sv_out;
};
/*---------- begin par-sarr.in ----------*/
// forward declarations of strand methods
#ifdef DIDEROT_HAS_START_METHOD
static diderot::strand_status sample_start (sample_strand *self);
#endif // DIDEROT_HAS_START_METHOD
static diderot::strand_status sample_update (sample_strand *self);
#ifdef DIDEROT_HAS_STABILIZE_METHOD
static void sample_stabilize (sample_strand *self);
#endif // DIDEROT_HAS_STABILIZE_METHOD

// strand_array for PARALLEL_TARGET/NO BSP/SINGLE STATE/DIRECT ACCESS
//
struct strand_array {
    typedef sample_strand strand_t;
    typedef uint32_t index_t;
    typedef index_t sid_t;              // strand ID (index into strand-state storage)

    // scheduling block of strands
    //
    struct CACHE_ALIGN sched_block {
        index_t         _start;         // first index in block
        index_t         _stop;          // last index in block + 1
        uint32_t        _nStable;       // number of stable strands in block
        uint32_t        _nDead;         // current number of active strands

      // return the number of strands in the block
        uint32_t num_strands () const { return this->_stop - this->_start; }
      // return the number of active strands in the block
        uint32_t num_active () const
        {
#ifdef DIDEROT_HAS_STRAND_DIE
            return this->num_strands() - (this->_nStable + this->_nDead);
#else
            return this->num_strands() - this->_nStable;
#endif
        }
    };

    uint8_t             *_status;       // the array of status information for the strands
    char                *_storage;      // points to array of sample_strand structs
    sched_block         *_schedBlks;    // blocks of strands for parallel scheduling
    uint32_t            _nItems;        // number of items in the _storage and _status arrays
    uint32_t            _nStable;       // global number of stable strands
    uint32_t            _nActive;       // global number of active strands
    uint32_t            _nFresh;        // number of fresh strands (new strands from create_strands)
    uint32_t            _nBlks;         // number of scheduling blocks
    uint32_t            _blkSz;         // size of scheduling blocks
    atomic_uint32_t     _nextBlk CACHE_ALIGN;
                                        // next block to schedule

    strand_array ()
        : _status(nullptr), _storage(nullptr), _schedBlks(nullptr), _nItems(0),
          _nStable(0), _nActive(0), _nFresh(0), _nBlks(0), _blkSz(0), _nextBlk(0)
    { }
    ~strand_array ();

    uint32_t in_state_index () const { return 0; /* dummy */ }

    uint32_t num_active () const { return this->_nActive; }
    uint32_t num_stable () const { return this->_nStable; }
    uint32_t num_alive () const { return this->_nActive+this->_nStable; }

  // return the ID of a strand, which is the value of the _idx array
    sid_t id (index_t ix) const
    {
        assert (ix < this->_nItems);
        return ix;
    }
  // return a pointer to the strand with the given ID
    sample_strand *id_to_strand (sid_t id) const
    {
        assert (id < this->_nItems);
        return reinterpret_cast<sample_strand *>(this->_storage + id * sizeof(sample_strand));
    }

  // return a strand's status
    diderot::strand_status status (index_t ix) const
    {
        return static_cast<diderot::strand_status>(this->_status[ix]);
    }
  // return a pointer to the given strand
    sample_strand *strand (index_t ix) const
    {
        return this->id_to_strand(this->id(ix));
    }
  // return a pointer to the local state of strand ix
    sample_strand *local_state (index_t ix) const
    {
        return this->strand(ix);
    }
  // return a pointer to the local state of strand with the given ID
    sample_strand *id_to_local_state (sid_t id) const
    {
        return this->id_to_strand(id);
    }

  // set the scheduling block size based on the number of workers and the number of
  // strands.  This should be called before alloc.
    void set_block_size (uint32_t nWorkers, uint32_t nStrands);

  // allocate space for nItems organized into blkSz sized blocks of strands
    bool alloc (uint32_t nItems);

  // initialize the first nStrands locations as new active strands
    void create_strands (uint32_t nStrands);

  // swap in and out states (NOP for this version)
    void swap () { }

  // invoke strand's stabilize method (single-thread version)
    index_t strand_stabilize (index_t ix)
    {
#ifdef DIDEROT_HAS_STABILIZE_METHOD
        sample_stabilize (this->strand(ix));
#endif // DIDEROT_HAS_STABILIZE_METHOD
        this->_status[ix] = diderot::kStable;
        this->_nActive--;
        this->_nStable++;
      // skip to next active strand
        do {
            ix++;
        } while ((ix < this->_nItems) && (this->_status[ix] > diderot::kNew));
        return ix;
    }

  // mark the given strand as dead (single-thread version)
    index_t kill (index_t ix)
    {
        this->_status[ix] = diderot::kDead;
        this->_nActive--;
      // skip to next active strand
        do {
            ix++;
        } while ((ix < this->_nItems) && (this->_status[ix] > diderot::kNew));
        return ix;
    }

  // prepare to run the workers
    void prepare_run ()
    {
	this->_nextBlk = 0;
    }

  // finish the local-phase of a superstep (NOP)
    void finish_step () { }

  // finish a kill_all operation (NOP)
    void finish_kill_all () { }

  // finish a stabilize_all operation (NOP)
    void finish_stabilize_all () { }

  // iterator over all alive strands (single-threaded version)
    index_t begin_alive () const
    {
        index_t ix = 0;
#ifdef DIDEROT_HAS_STRAND_DIE
        while ((ix < this->_nItems) && (this->_status[ix] == diderot::kDead)) {
            ix++;
        }
#endif
        return ix;
    }
    index_t end_alive () const { return this->_nItems; }
    index_t next_alive (index_t &ix) const
    {
        ix++;
#ifdef DIDEROT_HAS_STRAND_DIE
        while ((ix < this->_nItems) && (this->_status[ix] == diderot::kDead)) {
            ix++;
        }
#endif
        return ix;
    }

  // iterator over all active strands (single-threaded version)
    index_t begin_active () const
    {
        index_t ix = 0;
        while ((ix < this->_nItems) && (this->_status[ix] > diderot::kNew)) {
            ix++;
        }
        return ix;
    }
    index_t end_active () const { return this->_nItems; }
    index_t next_active (index_t &ix) const
    {
        do {
            ix++;
        } while ((ix < this->_nItems) && (this->_status[ix] > diderot::kNew));
        return ix;
    }

  // iterator over stable strands
    index_t begin_stable () const
    {
        index_t ix = 0;
        while ((ix < this->_nItems) && (this->_status[ix] != diderot::kStable)) {
            ix++;
        }
        return ix;
    }
    index_t end_stable () const { return this->_nItems; }
    index_t next_stable (index_t &ix) const
    {
        do {
            ix++;
        } while ((ix < this->_nItems) && (this->_status[ix] != diderot::kStable));
        return ix;
    }

  // iterator over fresh strands; since the only new strands were created by create_strand
  // we iterate over all of them
    index_t begin_fresh () const { return 0; }
    index_t end_fresh () const { return this->_nFresh; }
    index_t next_fresh (index_t &ix) const { return ++ix; }

  // a local copy of strand state for workers
    struct worker_cache {
        uint8_t             *_status;       // the array of status information for the strands
        char                *_storage;      // points to array of sample_strand structs
        sched_block         *_schedBlks;    // blocks of strands for parallel scheduling
        atomic_uint32_t     *_nextBlkPtr;   // pointer to _nextBlk
        uint32_t            _nBlks;         // number of scheduling blocks
        uint32_t            _blkSz;         // size of scheduling blocks
#ifndef NDEBUG
	uint32_t	    _nItems;        // number of items in the _storage and _status arrays
#endif

        void init (strand_array &sarr)
        {
            this->_status = sarr._status;
            this->_storage = sarr._storage;
            this->_schedBlks = sarr._schedBlks;
            this->_nextBlkPtr = &sarr._nextBlk;
            this->_nBlks = sarr._nBlks;
            this->_blkSz = sarr._blkSz;
#ifndef NDEBUG
	    this->_nItems = sarr._nItems;
#endif
        }

      // return the ID of a strand, which is the value of the _idx array
        sid_t id (index_t ix) const
        {
            assert (ix < this->_nItems);
            return ix;
        }
      // return a pointer to the strand with the given ID
        sample_strand *id_to_strand (sid_t id) const
        {
            return reinterpret_cast<sample_strand *>(this->_storage + id * sizeof(sample_strand));
        }
      // return a strand's status
        diderot::strand_status status (index_t ix) const
        {
            return static_cast<diderot::strand_status>(this->_status[ix]);
        }
      // return a pointer to the given strand
        sample_strand *strand (index_t ix) const
        {
            return this->id_to_strand(this->id(ix));
        }
      // return a pointer to the local state of strand ix
        sample_strand *local_state (index_t ix) const
        {
            return this->strand(ix);
        }
      // return a pointer to the local state of strand with the given ID
        sample_strand *id_to_local_state (sid_t id) const
        {
            return this->id_to_strand(id);
        }

#ifdef DIDEROT_HAS_START_METHOD
      // invoke strand's start method
        diderot::strand_status strand_start (index_t ix)
        {
            return sample_start(this->strand(ix));
        }
#endif // DIDEROT_HAS_START_METHOD

      // invoke strand's update method
        diderot::strand_status strand_update (index_t ix)
        {
            return sample_update(this->strand(ix));
        }

      // invoke strand's stabilize method (multithread version)
        index_t strand_stabilize (sched_block *bp, index_t ix)
        {
#ifdef DIDEROT_HAS_STABILIZE_METHOD
            sample_stabilize (this->strand(ix));
#endif // DIDEROT_HAS_STABILIZE_METHOD
            this->_status[ix] = diderot::kStable;
            bp->_nStable++;
          // skip to next active strand
            do {
                ix++;
            } while ((ix < bp->_stop) && (this->_status[ix] > diderot::kNew));
            return ix;
        }

      // mark the given strand as dead (multithread version)
        index_t kill (sched_block *bp, index_t ix)
        {
            this->_status[ix] = diderot::kDead;
            bp->_nDead++;
          // skip to next active strand
            do {
                ix++;
            } while ((ix < bp->_stop) && (this->_status[ix] > diderot::kNew));
            return ix;
        }

      // iterator over alive strands in a scheduling block
        index_t begin_alive (const sched_block *bp) const
        {
            index_t ix = bp->_start;
#ifdef DIDEROT_HAS_STRAND_DIE
            while ((ix < bp->_stop) && (this->_status[ix] == diderot::kDead)) {
                ix++;
            }
#endif
            return ix;
        }
        index_t end_alive (const sched_block *bp) const { return bp->_stop; }
        index_t next_alive (const sched_block *bp, index_t &ix) const
        {
#ifdef DIDEROT_HAS_STRAND_DIE
            do {
                ix++;
            } while ((ix < bp->_stop) && (this->_status[ix] == diderot::kDead));
#endif
            return ix;
        }

      // iterator over active strands in a scheduling block
        index_t begin_active (const sched_block *bp) const
        {
            index_t ix = bp->_start;
            while ((ix < bp->_stop) && (this->_status[ix] > diderot::kNew)) {
                ix++;
            }
            return ix;
        }
        index_t end_active (const sched_block *bp) const { return bp->_stop; }
        index_t next_active (const sched_block *bp, index_t &ix) const
        {
            do {
                ix++;
            } while ((ix < bp->_stop) && (this->_status[ix] > diderot::kNew));
            return ix;
        }

      // get a block of strands
        sched_block *get_block ();

    }; // struct worker_cache

}; // struct strand_array

strand_array::~strand_array ()
{
  // run destructors to reclaim any dynamic memory attached to the strand state
    for (auto ix = this->begin_alive();  ix != this->end_alive();  ix = this->next_alive(ix)) {
        this->strand(ix)->~sample_strand();
    }
    if (this->_status != nullptr) std::free (this->_status);
    if (this->_storage != nullptr) std::free (this->_storage);
}

void strand_array::set_block_size (uint32_t nWorkers, uint32_t nStrands)
{
    uint32_t strandsPerWorker = nStrands / nWorkers;
  // compute minimum power of two less than strandsPerWorker and greater than
  // the minimum block size (64)
    int blkSz = 64;
    while (blkSz < strandsPerWorker) { blkSz += blkSz; }
  // we would like there to be a reasonable number of blocks per worker (16), so
  // shrink the blk size while keeping it above the minimum
    for (int i = 0;  (64 < blkSz) && (i < 4);  i++) {
        blkSz >>= 1;
    }
  // lastly, we don't want blocks larger than the maximum block size
    if (blkSz > 4096) {
        blkSz = 4096;
    }
    this->_blkSz = blkSz;
}

bool strand_array::alloc (uint32_t nItems)
{
    if (this->_blkSz == 0) {
        std::cerr << "Internal error: strand_array block size is 0\n";
        return true;
    }
    this->_storage = static_cast<char *>(std::malloc (nItems * sizeof(sample_strand)));
    if (this->_storage == nullptr) {
        return true;
    }
    this->_status = static_cast<uint8_t *>(std::malloc (nItems * sizeof(uint8_t)));
    if (this->_status == nullptr) {
        std::free (this->_storage);
        return true;
    }
    this->_nBlks = (nItems + this->_blkSz - 1) / this->_blkSz;
    this->_schedBlks = static_cast<sched_block *>(std::malloc (this->_nBlks * sizeof(sched_block)));
    if (this->_schedBlks == nullptr) {
        std::free (this->_storage);
        std::free (this->_status);
        return true;
    }
    this->_nItems = nItems;
    this->_nActive = 0;
    this->_nStable = 0;
    this->_nFresh = 0;
    return false;
}

void strand_array::create_strands (uint32_t nStrands)
{
    assert (this->_nActive == 0);
    assert (this->_nItems == nStrands);
    for (uint32_t ix = 0;  ix < nStrands;  ix++) {
#ifdef DIDEROT_HAS_START_METHOD
        this->_status[ix] = diderot::kNew;
#else
        this->_status[ix] = diderot::kActive;
#endif
        new(this->strand(ix)) sample_strand;
    }
    this->_nActive = nStrands;
    this->_nFresh = nStrands;
  // initialize the scheduling blocks
    for (uint32_t ix = 0, i = 0;  i < this->_nBlks;  i++) {
        this->_schedBlks[i]._start = ix;
        ix += this->_blkSz;
        this->_schedBlks[i]._stop = ix;
        this->_schedBlks[i]._nDead = 0;
        this->_schedBlks[i]._nStable = 0;
    }
  // the last block may be incomplete, so adjust it
    this->_schedBlks[this->_nBlks-1]._stop = nStrands;
}

strand_array::sched_block *strand_array::worker_cache::get_block ()
{
    do {
        uint32_t blkId = this->_nextBlkPtr->fetch_add(1);
        if (blkId < this->_nBlks) {
            strand_array::sched_block *bp = &this->_schedBlks[blkId];
            if (bp->num_active() > 0) {
                return bp;
            } // else skip stable block
        }
        else {  // no more blocks
            return nullptr;
        }
    } while (true);

}
/*---------- end par-sarr.in ----------*/

struct world : public diderot::world_base {
    strand_array _strands;
    globals *_globals;
    world ();
    ~world ();
    bool init ();
    bool alloc (int32_t base[2], uint32_t size[2]);
    bool create_strands ();
    uint32_t run (uint32_t max_nsteps);
    void swap_state ();
};
// ***** No synthesized operations *****

static bool init_globals (world *wrld)
{
    globals *glob = wrld->_globals;
    glob->gv_imgRes = 10;
    return false;
}
static void sample_init (sample_strand *self, int32_t p_ui_0, int32_t p_vi_1)
{
    self->sv_out = 0.2e1f;
}
static diderot::strand_status sample_update (sample_strand *self)
{
    return diderot::kStabilize;
}
extern "C" bool simple_output_get_out (simple_world_t *cWrld, Nrrd *nData)
{
    world *wrld = reinterpret_cast<world *>(cWrld);
    // Compute sizes of nrrd file
    size_t sizes[2];
    sizes[0] = wrld->_size[1];
    sizes[1] = wrld->_size[0];
    // Allocate nData nrrd
    if (nrrdMaybeAlloc_nva(nData, nrrdTypeFloat, 2, sizes) != 0) {
        char *msg = biffGetDone(NRRD);
        biffMsgAdd(wrld->_errors, msg);
        std::free(msg);
        return true;
    }
    // copy data to output nrrd
    char *cp = reinterpret_cast<char *>(nData->data);
    for (auto ix = wrld->_strands.begin_alive(); ix != wrld->_strands.end_alive(); ix = wrld->_strands.next_alive(ix)) {
        memcpy(cp, &wrld->_strands.strand(ix)->sv_out, 1 * sizeof(float));
        cp += 1 * sizeof(float);
    }
    nData->axis[0].kind = nrrdKindSpace;
    nData->axis[1].kind = nrrdKindSpace;
    return false;
}
/*---------- begin world-methods.in ----------*/
// Allocate the program's world
//
world::world ()
    : diderot::world_base (ProgramName, true, 2)
{
#ifndef DIDEROT_NO_GLOBALS
    this->_globals = new globals;
#endif

#ifdef DIDEROT_HAS_STRAND_COMMUNICATION
    this->_tree = nullptr;
#endif
} // world constructor

// shutdown and deallocate the world
//
world::~world ()
{
#ifndef DIDEROT_NO_GLOBALS
    delete this->_globals;
#endif

#ifdef DIDEROT_HAS_STRAND_COMMUNICATION
    delete this->_tree;
#endif

} // world destructor

// Initialize the program's world
//
bool world::init ()
{
    if (this->_stage != diderot::POST_NEW) {
        biffMsgAdd (this->_errors, "multiple calls to world::init");
        return true;
    }

#if !defined(DIDEROT_STANDALONE_EXEC) && !defined(DIDEROT_NO_INPUTS)
  // initialize the defined flags for the input globals
    init_defined_inputs (this);
#endif

    this->_stage = diderot::POST_INIT;

    return false;

}

// allocate the initial strands and initialize the rest of the world structure.
//
bool world::alloc (int32_t base[2], uint32_t size[2])
{
    size_t numStrands = 1;
    for (uint32_t i = 0;  i < 2;  i++) {
        numStrands *= size[i];
        this->_base[i] = base[i];
        this->_size[i] = size[i];
    }

    if (this->_verbose) {
        std::cerr << "world::alloc: " << size[0];
        for (uint32_t i = 1;  i < 2;  i++) {
            std::cerr << " x " << size[i];
        }
        std::cerr << std::endl;
    }

#ifdef DIDEROT_TARGET_PARALLEL
  // determine the block size based on the initial number of strands and the
  // number of workers
    this->_strands.set_block_size (this->_sched->_numWorkers, numStrands);
#endif

  // allocate the strand array
    if (this->_strands.alloc (numStrands)) {
        biffMsgAdd (this->_errors, "unable to allocate strand-state array\n");
        return true;
    }

  // initialize strand state pointers etc.
    this->_strands.create_strands (numStrands);

#ifdef DIDEROT_HAS_STRAND_COMMUNICATION
    this->_tree = new diderot::kdtree<0, float, strand_array> (&this->_strands);
#endif

    return false;

} // world::alloc

// swap input and output states
//
inline void world::swap_state ()
{
    this->_strands.swap ();
}

#ifdef DIDEROT_HAS_KILL_ALL
void world::kill_all ()
{
    if (this->_strands.num_active() > 0) {
        for (auto ix = this->_strands.begin_active();
            ix != this->_strands.end_active();
            )
        {
            assert (this->_strands.status(ix) == diderot::kActive);
            ix = this->_strands.kill (ix);
        }
        this->_strands.finish_kill_all();
    }
    assert (this->_strands.num_active() == 0);
}
#endif

#ifdef DIDEROT_HAS_STABILIZE_ALL
void world::stabilize_all ()
{
#ifndef DIDEROT_NO_GLOBALS
    globals *glob = this->_globals;
#endif

    if (this->_strands.num_active() > 0) {
        for (auto ix = this->_strands.begin_active();
            ix != this->_strands.end_active();
            )
        {
            assert (this->_strands.status(ix) == diderot::kActive);
	    this->_strands._status[ix] = diderot::kStable;
            ix = this->_strands.strand_stabilize (ix);
        }
        this->_strands.finish_stabilize_all();
    }
    assert (this->_strands.num_active() == 0);
}
#endif
/*---------- end world-methods.in ----------*/

bool world::create_strands ()
{
    if (init_globals(this)) {
        return true;
    }
    globals *glob = this->_globals;
    int32_t l__t_2 = glob->gv_imgRes - 1;
    int lo_0 = 0;
    int lo_1 = 0;
    int32_t base[2] = {lo_0,lo_1,};
    uint32_t size[2] = {static_cast<uint32_t>(l__t_2 - lo_0 + 1),static_cast<uint32_t>(l__t_2 - lo_1 + 1),};
    if (this->alloc(base, size)) {
        return true;
    }
    uint32_t ix = 0;
    for (int i_vi_3 = lo_0; i_vi_3 <= l__t_2; i_vi_3++) {
        for (int i_ui_4 = lo_1; i_ui_4 <= l__t_2; i_ui_4++) {
            sample_init(this->_strands.strand(ix), i_ui_4, i_vi_3);
            ++ix;
        }
    }
    this->swap_state();
    this->_stage = diderot::POST_CREATE;
    return false;
}
/*---------- begin par-worker-nobsp.in ----------*/
struct CACHE_ALIGN worker_arg {
    world       *_wrld;         //!< world pointer
    uint32_t    _id;            //!< worker ID
    uint32_t    _maxNSteps;     //!< maximum number of steps to take; 0 == infinity
    uint32_t    _nSteps;        //!< max number of steps taken by a strand in call to run
    uint32_t    _nStable;       //!< number of strands that stabilized in call to run
    uint32_t    _nDead;         //!< number of strands that died in call to run
    strand_array::worker_cache _strands;
};

/* Worker task for when we do not need super-step synchronization */
static void worker (void *arg)
{
    worker_arg *myArg = reinterpret_cast<worker_arg *>(arg);
    world *wrld = myArg->_wrld;
#ifndef DIDEROT_NO_GLOBALS
    globals *glob = wrld->_globals;
#endif

  // iterate until there is no more work to do
    uint32_t numDead = 0;
    uint32_t numStabilized = 0;
    uint32_t maxSteps = 0;
    uint32_t maxNSteps = myArg->_maxNSteps;
    strand_array::sched_block *blk;
    IF_LOGGING ( LogGetStrandBlock(wrld, myArg->_id+1); )
    while ((blk = myArg->_strands.get_block()) != nullptr) {
        IF_LOGGING ( LogGotStrandBlock(wrld, myArg->_id+1); )
        uint32_t nStable = blk->_nStable;
#ifdef DIDEROT_HAS_STRAND_DIE
        uint32_t nDead = blk->_nDead;
#endif
      // update the strands
        for (auto ix = myArg->_strands.begin_active(blk);
            ix != myArg->_strands.end_active(blk);
        ) {
          // run the strand to completion, or until the step limit is exceeded
            sample_strand *self = myArg->_strands.strand(ix);
            diderot::strand_status sts = myArg->_strands.status(ix);
#ifdef DIDEROT_HAS_START_METHOD
            if (sts == diderot::kNew) {
                IF_LOGGING ( LogStrandStart(wrld, myArg->_id+1, ix); )
                sts = sample_start(self);
            }
#endif
            uint32_t nSteps = 0;
            while ((! sts) && (nSteps < maxNSteps)) {
                nSteps++;
                sts = sample_update(self);
            }
            switch (sts) {
              case diderot::kStabilize:
              // stabilize the strand's state.
                IF_LOGGING ( LogStrandStabilize(wrld, myArg->_id+1, ix); )
                ix = myArg->_strands.strand_stabilize (blk, ix);
                break;
#ifdef DIDEROT_HAS_STRAND_DIE
              case diderot::kDie:
                IF_LOGGING ( LogStrandDie(wrld, myArg->_id+1, ix); )
                ix = myArg->_strands.kill (blk, ix);
                break;
#endif
              default:
                assert (sts == myArg->_strands.status(ix));
                ix = myArg->_strands.next_active(blk, ix);
                break;
            }
            if (maxSteps < nSteps) maxSteps = nSteps;
        }
        numStabilized += (blk->_nStable - nStable);
#ifdef DIDEROT_HAS_STRAND_DIE
        numDead += (blk->_nDead - nDead);
#endif
        IF_LOGGING ( LogGetStrandBlock(wrld, myArg->_id+1); )
    }
    IF_LOGGING ( LogNoStrandBlock(wrld, myArg->_id+1); )

  // update global counts of active and stable strands
    myArg->_nSteps = maxSteps;
    myArg->_nStable = numStabilized;
    myArg->_nDead = numDead;

}
/*---------- end par-worker-nobsp.in ----------*/
/*---------- begin par-run.in ----------*/
//! Run the Diderot program (parallel version)
//! \param maxNSteps the limit on the number of super steps; 0 means unlimited
//! \return the number of steps taken, or 0 on error.
uint32_t world::run (uint32_t maxNSteps)
{
	printf("Got to run!\n");
    if (this->_stage < diderot::POST_CREATE) {
        this->error ("attempt to run uninitialized program\n");
        return 0;
    }
    else if (this->_stage == diderot::DONE) {
        return 0;
    }
    else if (this->_stage == diderot::POST_CREATE) {
#ifdef DIDEROT_HAS_GLOBAL_START
        this->global_start();
#endif
        this->_stage = diderot::RUNNING;
    }
    assert (this->_stage == diderot::RUNNING);

    diderot::scheduler *sched = this->_sched;

    if (maxNSteps == 0) {
        maxNSteps = 0xffffffff;  // essentially unlimited
    }

  // set task pointer
    sched->_task = worker;

  // initialize per-worker info
    worker_arg *args = new  worker_arg[sched->_numWorkers];
    for (int i = 0;  i < sched->_numWorkers;  i++) {
        worker_arg *p = &args[i];
        p->_wrld = this;
        p->_id = i;
        p->_maxNSteps = maxNSteps;
        p->_nSteps = 0;
#ifndef DIDEROT_BSP
        p->_nStable = 0;
        p->_nDead = 0;
#endif
        p->_strands.init (this->_strands);
        sched->_info[i]._data = p;
    }

    double t0 = airTime();

  // Start worker threads
    if (this->_verbose) {
        std::cerr << "run with " << this->_strands.num_active() << " active strands / "
            << sched->_numWorkers << " workers ..." << std::endl;
    }
    this->_strands.prepare_run ();
    sched->_gate.release_workers (IF_LOGGING( this ));

  // wait for the computation to finish
    sched->_gate.controller_wait (IF_LOGGING( this ));

  // get max # steps and update global counts of active and stable strands when no-bsp
    uint32_t nSteps = 0;
    for (uint32_t i = 0;  i < sched->_numWorkers;  i++) {
        nSteps = std::max (nSteps, args[i]._nSteps);
#ifndef DIDEROT_BSP
      // if there is no BSP, then the controller updates #active and #stable
        this->_strands._nActive -= args[i]._nStable + args[i]._nDead;
        this->_strands._nStable += args[i]._nStable;
#endif
    }
    delete[] args;

    t0 = airTime() - t0;
    if (this->_verbose) {
        std::cerr << nSteps << " steps done in " << t0 << " seconds" << std::endl;
    }
    this->_run_time += t0;

    return nSteps;

} // world::run
/*---------- end par-run.in ----------*/

/*---------- begin namespace-close.in ----------*/

} // namespace simple
/*---------- end namespace-close.in ----------*/

/*---------- begin c-wrappers.in ----------*/
extern "C" uint32_t simple_num_strands (simple_world_t *wrld)
{
    simple::world *w = reinterpret_cast<simple::world *>(wrld);
#if defined(DIDEROT_TARGET_SEQUENTIAL)
    return w->_strands.num_alive();
#elif defined(DIDEROT_TARGET_PARALLEL)
#endif
}

extern "C" uint32_t simple_num_active_strands (simple_world_t *wrld)
{
    simple::world *w = reinterpret_cast<simple::world *>(wrld);
#if defined(DIDEROT_TARGET_SEQUENTIAL)
    return w->_strands.num_active();
#elif defined(DIDEROT_TARGET_PARALLEL)
#endif
}

extern "C" uint32_t simple_num_stable_strands (simple_world_t *wrld)
{
    simple::world *w = reinterpret_cast<simple::world *>(wrld);
#if defined(DIDEROT_TARGET_SEQUENTIAL)
    return w->_strands.num_stable();
#elif defined(DIDEROT_TARGET_PARALLEL)
#endif
}

extern "C" bool simple_any_errors (simple_world_t *wrld)
{
    simple::world *w = reinterpret_cast<simple::world *>(wrld);
    return (w->_errors->errNum > 0);
}

extern "C" char *simple_get_errors (simple_world_t *wrld)
{
    simple::world *w = reinterpret_cast<simple::world *>(wrld);
    char *msg = biffMsgStrGet (w->_errors);
    biffMsgClear (w->_errors);
    return msg;
}

extern "C" simple_world_t *simple_new_world ()
{
    simple::world *w = new (std::nothrow) simple::world();
#ifndef DIDEROT_NO_INPUTS
    if (w != nullptr) {
        init_defined_inputs (w);
        init_defaults (w->_globals);
    }
#endif
    return reinterpret_cast<simple_world_t *>(w);
}

extern "C" bool simple_init_world (simple_world_t *wrld)
{
	printf("AGAGAGAGA");
    simple::world *w = reinterpret_cast<simple::world *>(wrld);
#ifndef DIDEROT_NO_INPUTS
    if (check_defined(w)) {
        return true;
    }
#endif
    return static_cast<bool>(w->init());
}

extern "C" bool simple_create_strands (simple_world_t *wrld)
{
    simple::world *w = reinterpret_cast<simple::world *>(wrld);
    return static_cast<bool>(w->create_strands());
}

extern "C" uint32_t simple_run (simple_world_t *wrld, uint32_t maxNSteps)
{
	printf("\nAgggRun\n");
    simple::world *w = reinterpret_cast<simple::world *>(wrld);
    return w->run(maxNSteps);
}

extern "C" void simple_shutdown (simple_world_t *wrld)
{
    simple::world *w = reinterpret_cast<simple::world *>(wrld);
    delete w;
}

extern "C" void simple_set_verbose (simple_world_t *wrld, bool mode)
{
    simple::world *w = reinterpret_cast<simple::world *>(wrld);
    w->_verbose = (mode ? true : false);
}

extern "C" bool simple_get_verbose (simple_world_t *wrld)
{
    simple::world *w = reinterpret_cast<simple::world *>(wrld);
    return static_cast<bool>(w->_verbose);
}

#ifdef DIDEROT_TARGET_PARALLEL

void simple_set_num_workers (simple_world_t *wrld, uint32_t nw)
{
    simple::world *w = reinterpret_cast<simple::world *>(wrld);
    if (nw == 0)
        w->_sched->_numWorkers = w->_sched->_numHWCores;
    else
        w->_sched->_numWorkers = nw;
}

uint32_t simple_get_num_workers (simple_world_t *wrld)
{
    simple::world *w = reinterpret_cast<simple::world *>(wrld);
    return w->_sched->_numWorkers;
}

#endif /* DIDEROT_TARGET_PARALLEL */
/*---------- end c-wrappers.in ----------*/

