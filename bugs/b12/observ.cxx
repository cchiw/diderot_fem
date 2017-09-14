/*---------- begin cxx-head.in ----------*/
/*! \file observ.cxx
 *
 * Generated from observ.diderot.
 *
 * Command: /Users/chariseechiw/diderot/femprime/bin/diderotc --log --double --namespace=observ observ.diderot
 * Version: vis15:2016-07-29
 */
/*---------- end cxx-head.in ----------*/

#define DIDEROT_STRAND_HAS_CONSTR
#define DIDEROT_STRAND_ARRAY
/*---------- begin lib-cxx-incl.in ----------*/
#include "observ.h"
#include "diderot/diderot.hxx"

#ifdef DIDEROT_ENABLE_LOGGING
#define IF_LOGGING(...)         __VA_ARGS__
#else
#define IF_LOGGING(...)
#endif

static std::string ProgramName = "observ";
/*---------- end lib-cxx-incl.in ----------*/

// ***** Begin synthesized types *****

namespace observ {
    typedef double vec3 __attribute__ ((vector_size (32)));
    struct tensor_ref_3 : public diderot::tensor_ref<double,3> {
        tensor_ref_3 (const double *src);
        tensor_ref_3 (struct tensor_3 const & ten);
        tensor_ref_3 (tensor_ref_3 const & ten);
    };
    struct tensor_ref_3_3 : public diderot::tensor_ref<double,9> {
        tensor_ref_3_3 (const double *src);
        tensor_ref_3_3 (struct tensor_3_3 const & ten);
        tensor_ref_3_3 (tensor_ref_3_3 const & ten);
        tensor_ref_3 last (uint32_t i)
        {
            return &this->_data[i];
        }
    };
    struct tensor_3 : public diderot::tensor<double,3> {
        tensor_3 ()
            : diderot::tensor<double,3>()
        { }
        tensor_3 (std::initializer_list< double > const & il)
            : diderot::tensor<double,3>(il)
        { }
        tensor_3 (const double *src)
            : diderot::tensor<double,3>(src)
        { }
        tensor_3 (tensor_3 const & ten)
            : diderot::tensor<double,3>(ten._data)
        { }
        ~tensor_3 () { }
        tensor_3 & operator= (tensor_3 const & src);
        tensor_3 & operator= (tensor_ref_3 const & src);
        tensor_3 & operator= (std::initializer_list< double > const & il);
        tensor_3 & operator= (const double *src);
    };
    struct tensor_3_3 : public diderot::tensor<double,9> {
        tensor_3_3 ()
            : diderot::tensor<double,9>()
        { }
        tensor_3_3 (std::initializer_list< double > const & il)
            : diderot::tensor<double,9>(il)
        { }
        tensor_3_3 (const double *src)
            : diderot::tensor<double,9>(src)
        { }
        tensor_3_3 (tensor_3_3 const & ten)
            : diderot::tensor<double,9>(ten._data)
        { }
        ~tensor_3_3 () { }
        tensor_3_3 & operator= (tensor_3_3 const & src);
        tensor_3_3 & operator= (tensor_ref_3_3 const & src);
        tensor_3_3 & operator= (std::initializer_list< double > const & il);
        tensor_3_3 & operator= (const double *src);
        tensor_ref_3 last (uint32_t i)
        {
            return &this->_data[i];
        }
    };
    inline tensor_ref_3::tensor_ref_3 (const double *src)
        : diderot::tensor_ref<double,3>(src)
    { }
    inline tensor_ref_3::tensor_ref_3 (struct tensor_3 const & ten)
        : diderot::tensor_ref<double,3>(ten._data)
    { }
    inline tensor_ref_3::tensor_ref_3 (tensor_ref_3 const & ten)
        : diderot::tensor_ref<double,3>(ten._data)
    { }
    inline tensor_ref_3_3::tensor_ref_3_3 (const double *src)
        : diderot::tensor_ref<double,9>(src)
    { }
    inline tensor_ref_3_3::tensor_ref_3_3 (struct tensor_3_3 const & ten)
        : diderot::tensor_ref<double,9>(ten._data)
    { }
    inline tensor_ref_3_3::tensor_ref_3_3 (tensor_ref_3_3 const & ten)
        : diderot::tensor_ref<double,9>(ten._data)
    { }
    inline tensor_3 & tensor_3::operator= (tensor_3 const & src)
    {
        this->copy(src._data);
        return *this;
    }
    inline tensor_3 & tensor_3::operator= (tensor_ref_3 const & src)
    {
        this->copy(src._data);
        return *this;
    }
    inline tensor_3 & tensor_3::operator= (std::initializer_list< double > const & il)
    {
        this->copy(il);
        return *this;
    }
    inline tensor_3 & tensor_3::operator= (const double *src)
    {
        this->copy(src);
        return *this;
    }
    inline tensor_3_3 & tensor_3_3::operator= (tensor_3_3 const & src)
    {
        this->copy(src._data);
        return *this;
    }
    inline tensor_3_3 & tensor_3_3::operator= (tensor_ref_3_3 const & src)
    {
        this->copy(src._data);
        return *this;
    }
    inline tensor_3_3 & tensor_3_3::operator= (std::initializer_list< double > const & il)
    {
        this->copy(il);
        return *this;
    }
    inline tensor_3_3 & tensor_3_3::operator= (const double *src)
    {
        this->copy(src);
        return *this;
    }
} // namespace observ
// ***** End synthesized types *****

/*---------- begin namespace-open.in ----------*/
namespace observ {

static std::string ProgramName = "observ";

struct world;
struct f_strand;
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

typedef struct {
    bool gv_FF0;
} defined_inputs;
struct globals {
    FEMSrcTy gv_FF0;
    int32_t gv_length;
};
struct f_strand {
    tensor_3_3 sv_out;
    int32_t sv_i;
};
/*---------- begin seq-sarr.in ----------*/
// forward declarations of strand methods
#ifdef DIDEROT_HAS_START_METHOD
static diderot::strand_status f_start (f_strand *self);
#endif // DIDEROT_HAS_START_METHOD
static diderot::strand_status f_update (globals *glob, f_strand *self);
#ifdef DIDEROT_HAS_STABILIZE_METHOD
static void f_stabilize (f_strand *self);
#endif // DIDEROT_HAS_STABILIZE_METHOD

// if we have both communication and "die", then we need to track when strands die
// so that we can rebuild the list of strands use to construct the kd-tree
#if defined(DIDEROT_HAS_STRAND_COMMUNICATION) && !defined(DIDEROT_HAS_STRAND_DIE)
#  define TRACK_STRAND_DEATH
#endif

// strand_array for SEQUENTIAL/NO BSP/SINGLE STATE/DIRECT ACCESS
//
struct strand_array {
    typedef f_strand strand_t;
    typedef uint32_t index_t;
    typedef index_t sid_t;              // strand ID (index into strand-state storage)

    uint8_t             *_status;       // the array of status information for the strands
    char                *_storage;      // points to array of f_strand structs
    uint32_t            _nItems;        // number of items in the _storage and _status arrays
    uint32_t            _nStable;       // number of stable strands
    uint32_t            _nActive;       // number of active strands
    uint32_t            _nFresh;        // number of fresh strands (new strands from create_strands)
#ifdef TRACK_STRAND_DEATH
    bool                _died;          // a strand died in the current superstep.
#endif

    strand_array () : _status(nullptr), _storage(nullptr), _nItems(0) { }
    ~strand_array ();

    uint32_t in_state_index () const { return 0; /* dummy */ }

    uint32_t num_active () const { return this->_nActive; }
    uint32_t num_stable () const { return this->_nStable; }
    uint32_t num_alive () const { return this->_nActive+this->_nStable; }

  // return the ID of a strand, which is the same as the ix index
    sid_t id (index_t ix) const
    {
        assert (ix < this->_nItems);
        return ix;
    }
  // return a pointer to the strand with the given ID
    f_strand *id_to_strand (sid_t id) const
    {
        assert (id < this->_nItems);
        return reinterpret_cast<f_strand *>(this->_storage + id * sizeof(f_strand));
    }

  // return a strand's status
    diderot::strand_status status (index_t ix) const
    {
        assert (ix < this->_nItems);
        return static_cast<diderot::strand_status>(this->_status[ix]);
    }
  // return a pointer to the given strand
    f_strand *strand (index_t ix) const
    {
        return this->id_to_strand(this->id(ix));
    }
  // return a pointer to the local state of strand ix
    f_strand *local_state (index_t ix) const
    {
        return this->strand(ix);
    }
  // return a pointer to the local state of strand with the given ID
    f_strand *id_to_local_state (sid_t id) const
    {
        return this->id_to_strand(id);
    }

  // is an index valid for the strand array?
    bool validIndex (index_t ix) const { return (ix < this->_nItems); }

  // is a given strand alive?
    bool isAlive (index_t ix) const
    {
#ifdef DIDEROT_HAS_STRAND_DIE
        return aliveSts(this->status(ix));
#else
        return true;
#endif
    }

  // allocate space for nItems
    bool alloc (uint32_t nItems)
    {
        this->_storage = static_cast<char *>(std::malloc (nItems * sizeof(f_strand)));
        if (this->_storage == nullptr) {
            return true;
        }
        this->_status = static_cast<uint8_t *>(std::malloc (nItems * sizeof(uint8_t)));
        if (this->_status == nullptr) {
            std::free (this->_storage);
            return true;
        }
        this->_nItems = nItems;
        this->_nActive = 0;
        this->_nStable = 0;
        this->_nFresh = 0;
        return false;
    }

  // initialize the first nStrands locations as new active strands
    void create_strands (uint32_t nStrands)
    {
        assert (this->_nActive == 0);
        assert (this->_nItems == nStrands);
        for (index_t ix = 0;  ix < nStrands;  ix++) {
            this->_status[ix] = diderot::kActive;
            new (this->strand(ix)) f_strand;
        }
        this->_nActive = nStrands;
        this->_nFresh = nStrands;
#ifdef TRACK_STRAND_DEATH
        this->_died = false;
#endif
    }

  // swap in and out states (NOP for this version)
    void swap () { }

#ifdef DIDEROT_HAS_START_METHOD
  // invoke strand's start method
    diderot::strand_status strand_start (index_t ix)
    {
        return f_start(this->strand(ix));
    }
#endif // DIDEROT_HAS_START_METHOD

  // invoke strand's update method
    diderot::strand_status strand_update (globals *glob, index_t ix)
    {
        return f_update(glob, this->strand(ix));
    }

  // invoke strand's stabilize method
    index_t strand_stabilize (index_t ix)
    {
#ifdef DIDEROT_HAS_STABILIZE_METHOD
        f_stabilize (this->strand(ix));
#endif // DIDEROT_HAS_STABILIZE_METHOD
        this->_status[ix] = diderot::kStable;
        this->_nActive--;
        this->_nStable++;
      // skip to next active strand
        do {
            ix++;
        } while ((ix < this->_nItems) && notActiveSts(this->status(ix)));
        return ix;
    }

  // mark the given strand as dead
    index_t kill (index_t ix)
    {
#ifdef TRACK_STRAND_DEATH
        this->_died = true;
#endif
        this->_status[ix] = diderot::kDead;
        this->_nActive--;
      // skip to next active strand
        do {
            ix++;
        } while ((ix < this->_nItems) && notActiveSts(this->status(ix)));
        return ix;
    }

  // finish the local-phase of a superstep (NOP)
#ifdef TRACK_STRAND_DEATH
    bool finish_step ()
    {
        bool res = this->_died;
        this->_died = false;
        return res;
    }
#else
    bool finish_step () { return false; }
#endif

  // finish a kill_all operation (NOP)
    void finish_kill_all () { }

  // finish a stabilize_all operation (NOP)
    void finish_stabilize_all () { }

    index_t begin_alive () const
    {
        index_t ix = 0;
#ifdef DIDEROT_HAS_STRAND_DIE
        while ((ix < this->_nItems) && notAliveSts(this->status(ix))) {
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
        while ((ix < this->_nItems) && notAliveSts(this->status(ix))) {
            ix++;
        }
#endif
        return ix;
    }

  // iterator over active strands
    index_t begin_active () const
    {
        index_t ix = 0;
        while ((ix < this->_nItems) && notActiveSts(this->status(ix))) {
            ix++;
        }
        return ix;
    }
    index_t end_active () const { return this->_nItems; }
    index_t next_active (index_t &ix) const
    {
        do {
            ix++;
        } while ((ix < this->_nItems) && notActiveSts(this->status(ix)));
        return ix;
    }

  // iterator over stable strands
    index_t begin_stable () const
    {
        index_t ix = 0;
        while ((ix < this->_nItems) && (this->status(ix) != diderot::kStable)) {
            ix++;
        }
        return ix;
    }
    index_t end_stable () const { return this->_nItems; }
    index_t next_stable (index_t &ix) const
    {
        do {
            ix++;
        } while ((ix < this->_nItems) && (this->status(ix) != diderot::kStable));
        return ix;
    }

  // iterator over fresh strands; since the only new strands were created by create_strand
  // we iterate over all of them
    index_t begin_fresh () const { return 0; }
    index_t end_fresh () const { return this->_nFresh; }
    index_t next_fresh (index_t &ix) const { return ++ix; }

}; // struct strand_array

strand_array::~strand_array ()
{
  // run destructors to reclaim any dynamic memory attached to the strand state
    for (auto ix = this->begin_alive();  ix != this->end_alive();  ix = this->next_alive(ix)) {
        this->strand(ix)->~f_strand();
    }
    if (this->_status != nullptr) std::free (this->_status);
    if (this->_storage != nullptr) std::free (this->_storage);
}
/*---------- end seq-sarr.in ----------*/

struct world : public diderot::world_base {
    strand_array _strands;
    globals *_globals;
    defined_inputs _definedInp;
    world ();
    ~world ();
    bool init ();
    bool alloc (int32_t base[1], uint32_t size[1]);
    bool create_strands ();
    uint32_t run (uint32_t max_nsteps);
    void swap_state ();
};
// ***** Begin synthesized operations *****

inline double makePhiDerv_UnitCubeMesh_P_4_1(double H[3], const double* k, double* c){

	H[0] = (0) - (0) - (0) + 42.6666666666667*c[0]*k[0]*k[0]*k[0] + (0) - (0) + 128.0*c[0]*k[0]*k[0]*k[1] - (0) + 128.0*c[0]*k[0]*k[0]*k[2] - 80.0*c[0]*k[0]*k[0] - (0) - (0) + 128.0*c[0]*k[0]*k[1]*k[1] - (0) + 256.000000000001*c[0]*k[0]*k[1]*k[2] - 160.0*c[0]*k[0]*k[1] - (0) + 128.000000000001*c[0]*k[0]*k[2]*k[2] - 160.0*c[0]*k[0]*k[2] + 46.6666666666667*c[0]*k[0] - (0) + (0) + 42.6666666666666*c[0]*k[1]*k[1]*k[1] + (0) + 128.0*c[0]*k[1]*k[1]*k[2] - 80.0*c[0]*k[1]*k[1] + (0) + 128.0*c[0]*k[1]*k[2]*k[2] - 160.0*c[0]*k[1]*k[2] + 46.6666666666667*c[0]*k[1] - (0) + 42.6666666666669*c[0]*k[2]*k[2]*k[2] - 80.0000000000002*c[0]*k[2]*k[2] + 46.6666666666667*c[0]*k[2] - 8.33333333333335*c[0] + (0)*c[10]*k[0]*k[0]*k[0]*k[0] - (0)*c[10]*k[0]*k[0]*k[0]*k[1] + (0)*c[10]*k[0]*k[0]*k[0]*k[2] - (0)*c[10]*k[0]*k[0]*k[0] + (0)*c[10]*k[0]*k[0]*k[1]*k[1] + (0)*c[10]*k[0]*k[0]*k[1]*k[2] + 128.0*c[10]*k[0]*k[0]*k[1] - (0)*c[10]*k[0]*k[0]*k[2]*k[2] - (0)*c[10]*k[0]*k[0]*k[2] + (0)*c[10]*k[0]*k[0] + (0)*c[10]*k[0]*k[1]*k[1]*k[1] + (0)*c[10]*k[0]*k[1]*k[1]*k[2] - (0)*c[10]*k[0]*k[1]*k[1] + (0)*c[10]*k[0]*k[1]*k[2]*k[2] - (0)*c[10]*k[0]*k[1]*k[2] - 63.9999999999999*c[10]*k[0]*k[1] - (0)*c[10]*k[0]*k[2]*k[2]*k[2] + (0)*c[10]*k[0]*k[2]*k[2] + (0)*c[10]*k[0]*k[2] - (0)*c[10]*k[0] + (0)*c[10]*k[1]*k[1]*k[1]*k[1] + (0)*c[10]*k[1]*k[1]*k[1]*k[2] - (0)*c[10]*k[1]*k[1]*k[1] + (0)*c[10]*k[1]*k[1]*k[2]*k[2] - (0)*c[10]*k[1]*k[1]*k[2] + (0)*c[10]*k[1]*k[1] + (0)*c[10]*k[1]*k[2]*k[2]*k[2] - (0)*c[10]*k[1]*k[2]*k[2] + (0)*c[10]*k[1]*k[2] + 5.33333333333325*c[10]*k[1] - (0)*c[10]*k[2]*k[2]*k[2]*k[2] + (0)*c[10]*k[2]*k[2]*k[2] - (0)*c[10]*k[2]*k[2] - (0)*c[10]*k[2] + (0)*c[10] - (0)*c[11]*k[0]*k[0]*k[0]*k[0] + (0)*c[11]*k[0]*k[0]*k[0]*k[1] - (0)*c[11]*k[0]*k[0]*k[0]*k[2] - (0)*c[11]*k[0]*k[0]*k[0] + (0)*c[11]*k[0]*k[0]*k[1]*k[1] + (0)*c[11]*k[0]*k[0]*k[1]*k[2] - (0)*c[11]*k[0]*k[0]*k[1] - (0)*c[11]*k[0]*k[0]*k[2]*k[2] + (0)*c[11]*k[0]*k[0]*k[2] + (0)*c[11]*k[0]*k[0] - (0)*c[11]*k[0]*k[1]*k[1]*k[1] - (0)*c[11]*k[0]*k[1]*k[1]*k[2] + 128.0*c[11]*k[0]*k[1]*k[1] - (0)*c[11]*k[0]*k[1]*k[2]*k[2] + (0)*c[11]*k[0]*k[1]*k[2] - 31.9999999999998*c[11]*k[0]*k[1] - (0)*c[11]*k[0]*k[2]*k[2]*k[2] + (0)*c[11]*k[0]*k[2]*k[2] - (0)*c[11]*k[0]*k[2] + (0)*c[11]*k[0] - (0)*c[11]*k[1]*k[1]*k[1]*k[1] - (0)*c[11]*k[1]*k[1]*k[1]*k[2] + (0)*c[11]*k[1]*k[1]*k[1] + (0)*c[11]*k[1]*k[1]*k[2]*k[2] + (0)*c[11]*k[1]*k[1]*k[2] - 16.0000000000003*c[11]*k[1]*k[1] + (0)*c[11]*k[1]*k[2]*k[2]*k[2] - (0)*c[11]*k[1]*k[2]*k[2] - (0)*c[11]*k[1]*k[2] + 4.00000000000011*c[11]*k[1] + (0)*c[11]*k[2]*k[2]*k[2]*k[2] - (0)*c[11]*k[2]*k[2]*k[2] + (0)*c[11]*k[2]*k[2] - (0)*c[11]*k[2] - (0)*c[11] + (0)*c[12]*k[0]*k[0]*k[0]*k[0] + (0)*c[12]*k[0]*k[0]*k[0]*k[1] - (0)*c[12]*k[0]*k[0]*k[0]*k[2] - (0)*c[12]*k[0]*k[0]*k[0] + (0)*c[12]*k[0]*k[0]*k[1]*k[1] - (0)*c[12]*k[0]*k[0]*k[1]*k[2] - (0)*c[12]*k[0]*k[0]*k[1] - (0)*c[12]*k[0]*k[0]*k[2]*k[2] + (0)*c[12]*k[0]*k[0]*k[2] + (0)*c[12]*k[0]*k[0] + (0)*c[12]*k[0]*k[1]*k[1]*k[1] + (0)*c[12]*k[0]*k[1]*k[1]*k[2] - (0)*c[12]*k[0]*k[1]*k[1] - (0)*c[12]*k[0]*k[1]*k[2]*k[2] + (0)*c[12]*k[0]*k[1]*k[2] + (0)*c[12]*k[0]*k[1] - (0)*c[12]*k[0]*k[2]*k[2]*k[2] + (0)*c[12]*k[0]*k[2]*k[2] - (0)*c[12]*k[0]*k[2] - (0)*c[12]*k[0] + (0)*c[12]*k[1]*k[1]*k[1]*k[1] - (0)*c[12]*k[1]*k[1]*k[1]*k[2] + 42.6666666666662*c[12]*k[1]*k[1]*k[1] - (0)*c[12]*k[1]*k[1]*k[2]*k[2] + (0)*c[12]*k[1]*k[1]*k[2] - 31.9999999999996*c[12]*k[1]*k[1] - (0)*c[12]*k[1]*k[2]*k[2]*k[2] + (0)*c[12]*k[1]*k[2]*k[2] - (0)*c[12]*k[1]*k[2] + 5.33333333333323*c[12]*k[1] - (0)*c[12]*k[2]*k[2]*k[2]*k[2] + (0)*c[12]*k[2]*k[2]*k[2] - (0)*c[12]*k[2]*k[2] + (0)*c[12]*k[2] + (0)*c[12] - (0)*c[13]*k[0]*k[0]*k[0]*k[0] - (0)*c[13]*k[0]*k[0]*k[0]*k[1] + (0)*c[13]*k[0]*k[0]*k[0]*k[2] + (0)*c[13]*k[0]*k[0]*k[0] - (0)*c[13]*k[0]*k[0]*k[1]*k[1] + (0)*c[13]*k[0]*k[0]*k[1]*k[2] + (0)*c[13]*k[0]*k[0]*k[1] + (0)*c[13]*k[0]*k[0]*k[2]*k[2] - 128.000000000001*c[13]*k[0]*k[0]*k[2] - (0)*c[13]*k[0]*k[0] - (0)*c[13]*k[0]*k[1]*k[1]*k[1] + (0)*c[13]*k[0]*k[1]*k[1]*k[2] + (0)*c[13]*k[0]*k[1]*k[1] + (0)*c[13]*k[0]*k[1]*k[2]*k[2] - 256.000000000001*c[13]*k[0]*k[1]*k[2] - (0)*c[13]*k[0]*k[1] + (0)*c[13]*k[0]*k[2]*k[2]*k[2] - 256.000000000001*c[13]*k[0]*k[2]*k[2] + 192.000000000001*c[13]*k[0]*k[2] + (0)*c[13]*k[0] - (0)*c[13]*k[1]*k[1]*k[1]*k[1] - (0)*c[13]*k[1]*k[1]*k[1]*k[2] + (0)*c[13]*k[1]*k[1]*k[1] - (0)*c[13]*k[1]*k[1]*k[2]*k[2] - 127.999999999998*c[13]*k[1]*k[1]*k[2] - (0)*c[13]*k[1]*k[1] - (0)*c[13]*k[1]*k[2]*k[2]*k[2] - 255.999999999999*c[13]*k[1]*k[2]*k[2] + 191.999999999999*c[13]*k[1]*k[2] + (0)*c[13]*k[1] + (0)*c[13]*k[2]*k[2]*k[2]*k[2] - 128.0*c[13]*k[2]*k[2]*k[2] + 192.0*c[13]*k[2]*k[2] - 69.3333333333334*c[13]*k[2] - (0)*c[13] + (0)*c[14]*k[0]*k[0]*k[0]*k[0] + (0)*c[14]*k[0]*k[0]*k[0]*k[1] - (0)*c[14]*k[0]*k[0]*k[0]*k[2] - (0)*c[14]*k[0]*k[0]*k[0] - (0)*c[14]*k[0]*k[0]*k[1]*k[1] + (0)*c[14]*k[0]*k[0]*k[1]*k[2] - (0)*c[14]*k[0]*k[0]*k[1] - (0)*c[14]*k[0]*k[0]*k[2]*k[2] + (0)*c[14]*k[0]*k[0]*k[2] + (0)*c[14]*k[0]*k[0] - (0)*c[14]*k[0]*k[1]*k[1]*k[1] + (0)*c[14]*k[0]*k[1]*k[1]*k[2] + (0)*c[14]*k[0]*k[1]*k[1] + (0)*c[14]*k[0]*k[1]*k[2]*k[2] - (0)*c[14]*k[0]*k[1]*k[2] + (0)*c[14]*k[0]*k[1] - (0)*c[14]*k[0]*k[2]*k[2]*k[2] + 128.000000000001*c[14]*k[0]*k[2]*k[2] - 32.0000000000002*c[14]*k[0]*k[2] - (0)*c[14]*k[0] + (0)*c[14]*k[1]*k[1]*k[1]*k[1] + (0)*c[14]*k[1]*k[1]*k[1]*k[2] - (0)*c[14]*k[1]*k[1]*k[1] + (0)*c[14]*k[1]*k[1]*k[2]*k[2] - (0)*c[14]*k[1]*k[1]*k[2] + (0)*c[14]*k[1]*k[1] + (0)*c[14]*k[1]*k[2]*k[2]*k[2] + 127.999999999999*c[14]*k[1]*k[2]*k[2] - 31.9999999999991*c[14]*k[1]*k[2] - (0)*c[14]*k[1] - (0)*c[14]*k[2]*k[2]*k[2]*k[2] + 128.0*c[14]*k[2]*k[2]*k[2] - 144.0*c[14]*k[2]*k[2] + 28.0*c[14]*k[2] + (0)*c[14] - (0)*c[15]*k[0]*k[0]*k[0]*k[0] - (0)*c[15]*k[0]*k[0]*k[0]*k[1] + (0)*c[15]*k[0]*k[0]*k[0]*k[2] - (0)*c[15]*k[0]*k[0]*k[0] + (0)*c[15]*k[0]*k[0]*k[1]*k[1] + (0)*c[15]*k[0]*k[0]*k[1]*k[2] - (0)*c[15]*k[0]*k[0]*k[1] + (0)*c[15]*k[0]*k[0]*k[2]*k[2] - (0)*c[15]*k[0]*k[0]*k[2] + (0)*c[15]*k[0]*k[0] + (0)*c[15]*k[0]*k[1]*k[1]*k[1] + (0)*c[15]*k[0]*k[1]*k[1]*k[2] - (0)*c[15]*k[0]*k[1]*k[1] + (0)*c[15]*k[0]*k[1]*k[2]*k[2] - (0)*c[15]*k[0]*k[1]*k[2] + (0)*c[15]*k[0]*k[1] + (0)*c[15]*k[0]*k[2]*k[2]*k[2] - (0)*c[15]*k[0]*k[2]*k[2] + (0)*c[15]*k[0]*k[2] - (0)*c[15]*k[0] - (0)*c[15]*k[1]*k[1]*k[1]*k[1] - (0)*c[15]*k[1]*k[1]*k[1]*k[2] + (0)*c[15]*k[1]*k[1]*k[1] - (0)*c[15]*k[1]*k[1]*k[2]*k[2] + (0)*c[15]*k[1]*k[1]*k[2] - (0)*c[15]*k[1]*k[1] - (0)*c[15]*k[1]*k[2]*k[2]*k[2] + (0)*c[15]*k[1]*k[2]*k[2] - (0)*c[15]*k[1]*k[2] + (0)*c[15]*k[1] - (0)*c[15]*k[2]*k[2]*k[2]*k[2] - 42.6666666666667*c[15]*k[2]*k[2]*k[2] + 32.0000000000001*c[15]*k[2]*k[2] - 5.33333333333339*c[15]*k[2] + (0)*c[15] - (0)*c[16]*k[0]*k[0]*k[0]*k[0] - (0)*c[16]*k[0]*k[0]*k[0]*k[1] + (0)*c[16]*k[0]*k[0]*k[0]*k[2] + (0)*c[16]*k[0]*k[0]*k[0] - (0)*c[16]*k[0]*k[0]*k[1]*k[1] + (0)*c[16]*k[0]*k[0]*k[1]*k[2] - 127.999999999999*c[16]*k[0]*k[0]*k[1] + (0)*c[16]*k[0]*k[0]*k[2]*k[2] - (0)*c[16]*k[0]*k[0]*k[2] - (0)*c[16]*k[0]*k[0] + (0)*c[16]*k[0]*k[1]*k[1]*k[1] - (0)*c[16]*k[0]*k[1]*k[1]*k[2] - 255.999999999999*c[16]*k[0]*k[1]*k[1] - (0)*c[16]*k[0]*k[1]*k[2]*k[2] - 255.999999999999*c[16]*k[0]*k[1]*k[2] + 192.0*c[16]*k[0]*k[1] + (0)*c[16]*k[0]*k[2]*k[2]*k[2] - (0)*c[16]*k[0]*k[2]*k[2] + (0)*c[16]*k[0]*k[2] + (0)*c[16]*k[0] + (0)*c[16]*k[1]*k[1]*k[1]*k[1] - (0)*c[16]*k[1]*k[1]*k[1]*k[2] - 128.0*c[16]*k[1]*k[1]*k[1] - (0)*c[16]*k[1]*k[1]*k[2]*k[2] - 255.999999999998*c[16]*k[1]*k[1]*k[2] + 192.0*c[16]*k[1]*k[1] - (0)*c[16]*k[1]*k[2]*k[2]*k[2] - 127.999999999999*c[16]*k[1]*k[2]*k[2] + 191.999999999999*c[16]*k[1]*k[2] - 69.3333333333333*c[16]*k[1] + (0)*c[16]*k[2]*k[2]*k[2]*k[2] - (0)*c[16]*k[2]*k[2]*k[2] + (0)*c[16]*k[2]*k[2] + (0)*c[16]*k[2] - (0)*c[16] + (0)*c[17]*k[0]*k[0]*k[0]*k[0] + (0)*c[17]*k[0]*k[0]*k[0]*k[1] - (0)*c[17]*k[0]*k[0]*k[0]*k[2] - (0)*c[17]*k[0]*k[0]*k[0] + (0)*c[17]*k[0]*k[0]*k[1]*k[1] - (0)*c[17]*k[0]*k[0]*k[1]*k[2] - (0)*c[17]*k[0]*k[0]*k[1] - (0)*c[17]*k[0]*k[0]*k[2]*k[2] + (0)*c[17]*k[0]*k[0]*k[2] + (0)*c[17]*k[0]*k[0] + (0)*c[17]*k[0]*k[1]*k[1]*k[1] - (0)*c[17]*k[0]*k[1]*k[1]*k[2] + 127.999999999999*c[17]*k[0]*k[1]*k[1] - (0)*c[17]*k[0]*k[1]*k[2]*k[2] + (0)*c[17]*k[0]*k[1]*k[2] - 31.9999999999997*c[17]*k[0]*k[1] - (0)*c[17]*k[0]*k[2]*k[2]*k[2] + (0)*c[17]*k[0]*k[2]*k[2] - (0)*c[17]*k[0]*k[2] - (0)*c[17]*k[0] - (0)*c[17]*k[1]*k[1]*k[1]*k[1] + (0)*c[17]*k[1]*k[1]*k[1]*k[2] + 128.0*c[17]*k[1]*k[1]*k[1] + (0)*c[17]*k[1]*k[1]*k[2]*k[2] + 127.999999999999*c[17]*k[1]*k[1]*k[2] - 144.0*c[17]*k[1]*k[1] + (0)*c[17]*k[1]*k[2]*k[2]*k[2] - (0)*c[17]*k[1]*k[2]*k[2] - 31.9999999999998*c[17]*k[1]*k[2] + 28.0*c[17]*k[1] - (0)*c[17]*k[2]*k[2]*k[2]*k[2] + (0)*c[17]*k[2]*k[2]*k[2] - (0)*c[17]*k[2]*k[2] + (0)*c[17]*k[2] + (0)*c[17] - (0)*c[18]*k[0]*k[0]*k[0]*k[0] - (0)*c[18]*k[0]*k[0]*k[0]*k[1] + (0)*c[18]*k[0]*k[0]*k[0]*k[2] + (0)*c[18]*k[0]*k[0]*k[0] - (0)*c[18]*k[0]*k[0]*k[1]*k[1] + (0)*c[18]*k[0]*k[0]*k[1]*k[2] + (0)*c[18]*k[0]*k[0]*k[1] + (0)*c[18]*k[0]*k[0]*k[2]*k[2] - (0)*c[18]*k[0]*k[0]*k[2] - (0)*c[18]*k[0]*k[0] - (0)*c[18]*k[0]*k[1]*k[1]*k[1] - (0)*c[18]*k[0]*k[1]*k[1]*k[2] + (0)*c[18]*k[0]*k[1]*k[1] + (0)*c[18]*k[0]*k[1]*k[2]*k[2] - (0)*c[18]*k[0]*k[1]*k[2] - (0)*c[18]*k[0]*k[1] + (0)*c[18]*k[0]*k[2]*k[2]*k[2] - (0)*c[18]*k[0]*k[2]*k[2] + (0)*c[18]*k[0]*k[2] + (0)*c[18]*k[0] - (0)*c[18]*k[1]*k[1]*k[1]*k[1] + (0)*c[18]*k[1]*k[1]*k[1]*k[2] - 42.6666666666662*c[18]*k[1]*k[1]*k[1] + (0)*c[18]*k[1]*k[1]*k[2]*k[2] - (0)*c[18]*k[1]*k[1]*k[2] + 31.9999999999996*c[18]*k[1]*k[1] + (0)*c[18]*k[1]*k[2]*k[2]*k[2] - (0)*c[18]*k[1]*k[2]*k[2] + (0)*c[18]*k[1]*k[2] - 5.33333333333321*c[18]*k[1] + (0)*c[18]*k[2]*k[2]*k[2]*k[2] - (0)*c[18]*k[2]*k[2]*k[2] + (0)*c[18]*k[2]*k[2] - (0)*c[18]*k[2] - (0)*c[18] + (0)*c[19]*k[0]*k[0]*k[0]*k[0] + (0)*c[19]*k[0]*k[0]*k[0]*k[1] + (0)*c[19]*k[0]*k[0]*k[0]*k[2] - 170.666666666667*c[19]*k[0]*k[0]*k[0] - (0)*c[19]*k[0]*k[0]*k[1]*k[1] + (0)*c[19]*k[0]*k[0]*k[1]*k[2] - 384.0*c[19]*k[0]*k[0]*k[1] + (0)*c[19]*k[0]*k[0]*k[2]*k[2] - 384.000000000001*c[19]*k[0]*k[0]*k[2] + 288.0*c[19]*k[0]*k[0] - (0)*c[19]*k[0]*k[1]*k[1]*k[1] + (0)*c[19]*k[0]*k[1]*k[1]*k[2] - 256.0*c[19]*k[0]*k[1]*k[1] + (0)*c[19]*k[0]*k[1]*k[2]*k[2] - 512.000000000003*c[19]*k[0]*k[1]*k[2] + 384.0*c[19]*k[0]*k[1] + (0)*c[19]*k[0]*k[2]*k[2]*k[2] - 256.000000000002*c[19]*k[0]*k[2]*k[2] + 384.000000000001*c[19]*k[0]*k[2] - 138.666666666667*c[19]*k[0] + (0)*c[19]*k[1]*k[1]*k[1]*k[1] - (0)*c[19]*k[1]*k[1]*k[1]*k[2] - 42.6666666666667*c[19]*k[1]*k[1]*k[1] - (0)*c[19]*k[1]*k[1]*k[2]*k[2] - 128.0*c[19]*k[1]*k[1]*k[2] + 96.0*c[19]*k[1]*k[1] + (0)*c[19]*k[1]*k[2]*k[2]*k[2] - 128.000000000001*c[19]*k[1]*k[2]*k[2] + 192.0*c[19]*k[1]*k[2] - 69.3333333333334*c[19]*k[1] + (0)*c[19]*k[2]*k[2]*k[2]*k[2] - 42.6666666666671*c[19]*k[2]*k[2]*k[2] + 96.0000000000005*c[19]*k[2]*k[2] - 69.3333333333335*c[19]*k[2] + 16.0*c[19] - (0) + (0) + (0) + 42.6666666666665*c[1]*k[0]*k[0]*k[0] + (0) - (0) - (0) + (0) - (0) - 47.9999999999999*c[1]*k[0]*k[0] - (0) - (0) + (0) - (0) + (0) - (0) - (0) + (0) - (0) + 14.6666666666667*c[1]*k[0] - (0) - (0) + (0) - (0) + (0) - (0) - (0) + (0) - (0) + (0) + (0) + (0) - (0) + (0) - 1.00000000000001*c[1] - (0)*c[20]*k[0]*k[0]*k[0]*k[0] - (0)*c[20]*k[0]*k[0]*k[0]*k[1] - (0)*c[20]*k[0]*k[0]*k[0]*k[2] + 256.0*c[20]*k[0]*k[0]*k[0] + (0)*c[20]*k[0]*k[0]*k[1]*k[1] - (0)*c[20]*k[0]*k[0]*k[1]*k[2] + 384.0*c[20]*k[0]*k[0]*k[1] - (0)*c[20]*k[0]*k[0]*k[2]*k[2] + 384.000000000001*c[20]*k[0]*k[0]*k[2] - 384.0*c[20]*k[0]*k[0] + (0)*c[20]*k[0]*k[1]*k[1]*k[1] - (0)*c[20]*k[0]*k[1]*k[1]*k[2] + 128.0*c[20]*k[0]*k[1]*k[1] - (0)*c[20]*k[0]*k[1]*k[2]*k[2] + 256.000000000004*c[20]*k[0]*k[1]*k[2] - 288.0*c[20]*k[0]*k[1] - (0)*c[20]*k[0]*k[2]*k[2]*k[2] + 128.000000000002*c[20]*k[0]*k[2]*k[2] - 288.000000000001*c[20]*k[0]*k[2] + 152.0*c[20]*k[0] + (0)*c[20]*k[1]*k[1]*k[1]*k[1] - (0)*c[20]*k[1]*k[1]*k[1]*k[2] - (0)*c[20]*k[1]*k[1]*k[1] - (0)*c[20]*k[1]*k[1]*k[2]*k[2] + (0)*c[20]*k[1]*k[1]*k[2] - 15.9999999999999*c[20]*k[1]*k[1] - (0)*c[20]*k[1]*k[2]*k[2]*k[2] + (0)*c[20]*k[1]*k[2]*k[2] - 32.0000000000012*c[20]*k[1]*k[2] + 28.0000000000001*c[20]*k[1] - (0)*c[20]*k[2]*k[2]*k[2]*k[2] + (0)*c[20]*k[2]*k[2]*k[2] - 16.0000000000006*c[20]*k[2]*k[2] + 28.0000000000003*c[20]*k[2] - 12.0*c[20] + (0)*c[21]*k[0]*k[0]*k[0]*k[0] - (0)*c[21]*k[0]*k[0]*k[0]*k[1] - (0)*c[21]*k[0]*k[0]*k[0]*k[2] - 170.666666666666*c[21]*k[0]*k[0]*k[0] - (0)*c[21]*k[0]*k[0]*k[1]*k[1] + (0)*c[21]*k[0]*k[0]*k[1]*k[2] - 128.0*c[21]*k[0]*k[0]*k[1] - (0)*c[21]*k[0]*k[0]*k[2]*k[2] - 128.0*c[21]*k[0]*k[0]*k[2] + 224.0*c[21]*k[0]*k[0] - (0)*c[21]*k[0]*k[1]*k[1]*k[1] + (0)*c[21]*k[0]*k[1]*k[1]*k[2] + (0)*c[21]*k[0]*k[1]*k[1] + (0)*c[21]*k[0]*k[1]*k[2]*k[2] - (0)*c[21]*k[0]*k[1]*k[2] + 64.0000000000004*c[21]*k[0]*k[1] + (0)*c[21]*k[0]*k[2]*k[2]*k[2] - (0)*c[21]*k[0]*k[2]*k[2] + 64.0000000000007*c[21]*k[0]*k[2] - 74.6666666666668*c[21]*k[0] - (0)*c[21]*k[1]*k[1]*k[1]*k[1] + (0)*c[21]*k[1]*k[1]*k[1]*k[2] + (0)*c[21]*k[1]*k[1]*k[1] + (0)*c[21]*k[1]*k[1]*k[2]*k[2] - (0)*c[21]*k[1]*k[1]*k[2] + (0)*c[21]*k[1]*k[1] + (0)*c[21]*k[1]*k[2]*k[2]*k[2] - (0)*c[21]*k[1]*k[2]*k[2] + (0)*c[21]*k[1]*k[2] - 5.33333333333346*c[21]*k[1] + (0)*c[21]*k[2]*k[2]*k[2]*k[2] - (0)*c[21]*k[2]*k[2]*k[2] + (0)*c[21]*k[2]*k[2] - 5.33333333333355*c[21]*k[2] + 5.33333333333336*c[21] - (0)*c[22]*k[0]*k[0]*k[0]*k[0] + (0)*c[22]*k[0]*k[0]*k[0]*k[1] + (0)*c[22]*k[0]*k[0]*k[0]*k[2] - (0)*c[22]*k[0]*k[0]*k[0] + (0)*c[22]*k[0]*k[0]*k[1]*k[1] + (0)*c[22]*k[0]*k[0]*k[1]*k[2] - (0)*c[22]*k[0]*k[0]*k[1] + (0)*c[22]*k[0]*k[0]*k[2]*k[2] - (0)*c[22]*k[0]*k[0]*k[2] + (0)*c[22]*k[0]*k[0] - (0)*c[22]*k[0]*k[1]*k[1]*k[1] - (0)*c[22]*k[0]*k[1]*k[1]*k[2] + (0)*c[22]*k[0]*k[1]*k[1] - (0)*c[22]*k[0]*k[1]*k[2]*k[2] + 256.000000000006*c[22]*k[0]*k[1]*k[2] - (0)*c[22]*k[0]*k[1] + (0)*c[22]*k[0]*k[2]*k[2]*k[2] - (0)*c[22]*k[0]*k[2]*k[2] + (0)*c[22]*k[0]*k[2] - (0)*c[22]*k[0] - (0)*c[22]*k[1]*k[1]*k[1]*k[1] - (0)*c[22]*k[1]*k[1]*k[1]*k[2] + (0)*c[22]*k[1]*k[1]*k[1] - (0)*c[22]*k[1]*k[1]*k[2]*k[2] + (0)*c[22]*k[1]*k[1]*k[2] - (0)*c[22]*k[1]*k[1] - (0)*c[22]*k[1]*k[2]*k[2]*k[2] + (0)*c[22]*k[1]*k[2]*k[2] - 32.0000000000045*c[22]*k[1]*k[2] + (0)*c[22]*k[1] - (0)*c[22]*k[2]*k[2]*k[2]*k[2] + (0)*c[22]*k[2]*k[2]*k[2] - (0)*c[22]*k[2]*k[2] + (0)*c[22]*k[2] - (0)*c[22] - (0)*c[23]*k[0]*k[0]*k[0]*k[0] + (0)*c[23]*k[0]*k[0]*k[0]*k[1] - (0)*c[23]*k[0]*k[0]*k[0]*k[2] - (0)*c[23]*k[0]*k[0]*k[0] + (0)*c[23]*k[0]*k[0]*k[1]*k[1] + (0)*c[23]*k[0]*k[0]*k[1]*k[2] - (0)*c[23]*k[0]*k[0]*k[1] - (0)*c[23]*k[0]*k[0]*k[2]*k[2] - (0)*c[23]*k[0]*k[0]*k[2] + (0)*c[23]*k[0]*k[0] + (0)*c[23]*k[0]*k[1]*k[1]*k[1] + (0)*c[23]*k[0]*k[1]*k[1]*k[2] - (0)*c[23]*k[0]*k[1]*k[1] + (0)*c[23]*k[0]*k[1]*k[2]*k[2] - (0)*c[23]*k[0]*k[1]*k[2] + (0)*c[23]*k[0]*k[1] - (0)*c[23]*k[0]*k[2]*k[2]*k[2] - (0)*c[23]*k[0]*k[2]*k[2] + (0)*c[23]*k[0]*k[2] - (0)*c[23]*k[0] + (0)*c[23]*k[1]*k[1]*k[1]*k[1] + (0)*c[23]*k[1]*k[1]*k[1]*k[2] - (0)*c[23]*k[1]*k[1]*k[1] + (0)*c[23]*k[1]*k[1]*k[2]*k[2] + 127.999999999996*c[23]*k[1]*k[1]*k[2] + (0)*c[23]*k[1]*k[1] + (0)*c[23]*k[1]*k[2]*k[2]*k[2] - (0)*c[23]*k[1]*k[2]*k[2] - 31.9999999999978*c[23]*k[1]*k[2] - (0)*c[23]*k[1] - (0)*c[23]*k[2]*k[2]*k[2]*k[2] - (0)*c[23]*k[2]*k[2]*k[2] + (0)*c[23]*k[2]*k[2] - (0)*c[23]*k[2] + (0)*c[23] + (0)*c[24]*k[0]*k[0]*k[0]*k[0] - (0)*c[24]*k[0]*k[0]*k[0]*k[1] - (0)*c[24]*k[0]*k[0]*k[0]*k[2] + (0)*c[24]*k[0]*k[0]*k[0] - (0)*c[24]*k[0]*k[0]*k[1]*k[1] - (0)*c[24]*k[0]*k[0]*k[1]*k[2] + (0)*c[24]*k[0]*k[0]*k[1] - (0)*c[24]*k[0]*k[0]*k[2]*k[2] + (0)*c[24]*k[0]*k[0]*k[2] - (0)*c[24]*k[0]*k[0] - (0)*c[24]*k[0]*k[1]*k[1]*k[1] - (0)*c[24]*k[0]*k[1]*k[1]*k[2] + (0)*c[24]*k[0]*k[1]*k[1] - (0)*c[24]*k[0]*k[1]*k[2]*k[2] + (0)*c[24]*k[0]*k[1]*k[2] - (0)*c[24]*k[0]*k[1] + (0)*c[24]*k[0]*k[2]*k[2]*k[2] - (0)*c[24]*k[0]*k[2]*k[2] - (0)*c[24]*k[0]*k[2] + (0)*c[24]*k[0] - (0)*c[24]*k[1]*k[1]*k[1]*k[1] - (0)*c[24]*k[1]*k[1]*k[1]*k[2] + (0)*c[24]*k[1]*k[1]*k[1] - (0)*c[24]*k[1]*k[1]*k[2]*k[2] + (0)*c[24]*k[1]*k[1]*k[2] - (0)*c[24]*k[1]*k[1] - (0)*c[24]*k[1]*k[2]*k[2]*k[2] + 128.000000000003*c[24]*k[1]*k[2]*k[2] - 32.0000000000016*c[24]*k[1]*k[2] + (0)*c[24]*k[1] + (0)*c[24]*k[2]*k[2]*k[2]*k[2] - (0)*c[24]*k[2]*k[2]*k[2] + (0)*c[24]*k[2]*k[2] + (0)*c[24]*k[2] - (0)*c[24] - (0)*c[25]*k[0]*k[0]*k[0]*k[0] + (0)*c[25]*k[0]*k[0]*k[0]*k[1] - (0)*c[25]*k[0]*k[0]*k[0]*k[2] + (0)*c[25]*k[0]*k[0]*k[0] + (0)*c[25]*k[0]*k[0]*k[1]*k[1] + (0)*c[25]*k[0]*k[0]*k[1]*k[2] - (0)*c[25]*k[0]*k[0]*k[1] + (0)*c[25]*k[0]*k[0]*k[2]*k[2] - (0)*c[25]*k[0]*k[0]*k[2] + (0)*c[25]*k[0]*k[0] + (0)*c[25]*k[0]*k[1]*k[1]*k[1] + (0)*c[25]*k[0]*k[1]*k[1]*k[2] - (0)*c[25]*k[0]*k[1]*k[1] + (0)*c[25]*k[0]*k[1]*k[2]*k[2] + 255.999999999976*c[25]*k[0]*k[1]*k[2] + (0)*c[25]*k[0]*k[1] - (0)*c[25]*k[0]*k[2]*k[2]*k[2] - (0)*c[25]*k[0]*k[2]*k[2] + (0)*c[25]*k[0]*k[2] - (0)*c[25]*k[0] - (0)*c[25]*k[1]*k[1]*k[1]*k[1] + (0)*c[25]*k[1]*k[1]*k[1]*k[2] - (0)*c[25]*k[1]*k[1]*k[1] + (0)*c[25]*k[1]*k[1]*k[2]*k[2] + 255.999999999989*c[25]*k[1]*k[1]*k[2] + (0)*c[25]*k[1]*k[1] + (0)*c[25]*k[1]*k[2]*k[2]*k[2] + 255.999999999989*c[25]*k[1]*k[2]*k[2] - 223.999999999993*c[25]*k[1]*k[2] - (0)*c[25]*k[1] - (0)*c[25]*k[2]*k[2]*k[2]*k[2] + (0)*c[25]*k[2]*k[2]*k[2] + (0)*c[25]*k[2]*k[2] - (0)*c[25]*k[2] + (0)*c[25] + (0)*c[26]*k[0]*k[0]*k[0]*k[0] - (0)*c[26]*k[0]*k[0]*k[0]*k[1] + (0)*c[26]*k[0]*k[0]*k[0]*k[2] + (0)*c[26]*k[0]*k[0]*k[0] - (0)*c[26]*k[0]*k[0]*k[1]*k[1] - (0)*c[26]*k[0]*k[0]*k[1]*k[2] + (0)*c[26]*k[0]*k[0]*k[1] + (0)*c[26]*k[0]*k[0]*k[2]*k[2] + (0)*c[26]*k[0]*k[0]*k[2] - (0)*c[26]*k[0]*k[0] - (0)*c[26]*k[0]*k[1]*k[1]*k[1] - (0)*c[26]*k[0]*k[1]*k[1]*k[2] + (0)*c[26]*k[0]*k[1]*k[1] - (0)*c[26]*k[0]*k[1]*k[2]*k[2] + (0)*c[26]*k[0]*k[1]*k[2] - (0)*c[26]*k[0]*k[1] + (0)*c[26]*k[0]*k[2]*k[2]*k[2] + (0)*c[26]*k[0]*k[2]*k[2] - (0)*c[26]*k[0]*k[2] + (0)*c[26]*k[0] - (0)*c[26]*k[1]*k[1]*k[1]*k[1] - (0)*c[26]*k[1]*k[1]*k[1]*k[2] + (0)*c[26]*k[1]*k[1]*k[1] - (0)*c[26]*k[1]*k[1]*k[2]*k[2] - 127.999999999996*c[26]*k[1]*k[1]*k[2] - (0)*c[26]*k[1]*k[1] - (0)*c[26]*k[1]*k[2]*k[2]*k[2] + (0)*c[26]*k[1]*k[2]*k[2] + 31.9999999999977*c[26]*k[1]*k[2] + (0)*c[26]*k[1] + (0)*c[26]*k[2]*k[2]*k[2]*k[2] + (0)*c[26]*k[2]*k[2]*k[2] - (0)*c[26]*k[2]*k[2] + (0)*c[26]*k[2] - (0)*c[26] - (0)*c[27]*k[0]*k[0]*k[0]*k[0] + (0)*c[27]*k[0]*k[0]*k[0]*k[1] + (0)*c[27]*k[0]*k[0]*k[0]*k[2] - (0)*c[27]*k[0]*k[0]*k[0] + (0)*c[27]*k[0]*k[0]*k[1]*k[1] + (0)*c[27]*k[0]*k[0]*k[1]*k[2] - (0)*c[27]*k[0]*k[0]*k[1] + (0)*c[27]*k[0]*k[0]*k[2]*k[2] - (0)*c[27]*k[0]*k[0]*k[2] + (0)*c[27]*k[0]*k[0] + (0)*c[27]*k[0]*k[1]*k[1]*k[1] + (0)*c[27]*k[0]*k[1]*k[1]*k[2] - (0)*c[27]*k[0]*k[1]*k[1] + (0)*c[27]*k[0]*k[1]*k[2]*k[2] - (0)*c[27]*k[0]*k[1]*k[2] + (0)*c[27]*k[0]*k[1] - (0)*c[27]*k[0]*k[2]*k[2]*k[2] + (0)*c[27]*k[0]*k[2]*k[2] + (0)*c[27]*k[0]*k[2] - (0)*c[27]*k[0] + (0)*c[27]*k[1]*k[1]*k[1]*k[1] + (0)*c[27]*k[1]*k[1]*k[1]*k[2] - (0)*c[27]*k[1]*k[1]*k[1] + (0)*c[27]*k[1]*k[1]*k[2]*k[2] - (0)*c[27]*k[1]*k[1]*k[2] + (0)*c[27]*k[1]*k[1] + (0)*c[27]*k[1]*k[2]*k[2]*k[2] - 128.000000000003*c[27]*k[1]*k[2]*k[2] + 32.0000000000018*c[27]*k[1]*k[2] - (0)*c[27]*k[1] - (0)*c[27]*k[2]*k[2]*k[2]*k[2] + (0)*c[27]*k[2]*k[2]*k[2] - (0)*c[27]*k[2]*k[2] - (0)*c[27]*k[2] + (0)*c[27] + (0)*c[28]*k[0]*k[0]*k[0]*k[0] + (0)*c[28]*k[0]*k[0]*k[0]*k[1] - (0)*c[28]*k[0]*k[0]*k[0]*k[2] - (0)*c[28]*k[0]*k[0]*k[0] + (0)*c[28]*k[0]*k[0]*k[1]*k[1] + (0)*c[28]*k[0]*k[0]*k[1]*k[2] - (0)*c[28]*k[0]*k[0]*k[1] - (0)*c[28]*k[0]*k[0]*k[2]*k[2] + 384.0*c[28]*k[0]*k[0]*k[2] + (0)*c[28]*k[0]*k[0] + (0)*c[28]*k[0]*k[1]*k[1]*k[1] + (0)*c[28]*k[0]*k[1]*k[1]*k[2] - (0)*c[28]*k[0]*k[1]*k[1] + (0)*c[28]*k[0]*k[1]*k[2]*k[2] + 511.999999999993*c[28]*k[0]*k[1]*k[2] + (0)*c[28]*k[0]*k[1] - (0)*c[28]*k[0]*k[2]*k[2]*k[2] + 512.0*c[28]*k[0]*k[2]*k[2] - 447.999999999999*c[28]*k[0]*k[2] - (0)*c[28]*k[0] + (0)*c[28]*k[1]*k[1]*k[1]*k[1] + (0)*c[28]*k[1]*k[1]*k[1]*k[2] - (0)*c[28]*k[1]*k[1]*k[1] + (0)*c[28]*k[1]*k[1]*k[2]*k[2] + 127.999999999993*c[28]*k[1]*k[1]*k[2] + (0)*c[28]*k[1]*k[1] + (0)*c[28]*k[1]*k[2]*k[2]*k[2] + 255.999999999994*c[28]*k[1]*k[2]*k[2] - 223.999999999996*c[28]*k[1]*k[2] - (0)*c[28]*k[1] - (0)*c[28]*k[2]*k[2]*k[2]*k[2] + 128.0*c[28]*k[2]*k[2]*k[2] - 224.0*c[28]*k[2]*k[2] + 95.9999999999997*c[28]*k[2] + (0)*c[28] - (0)*c[29]*k[0]*k[0]*k[0]*k[0] - (0)*c[29]*k[0]*k[0]*k[0]*k[1] - (0)*c[29]*k[0]*k[0]*k[0]*k[2] + (0)*c[29]*k[0]*k[0]*k[0] - (0)*c[29]*k[0]*k[0]*k[1]*k[1] - (0)*c[29]*k[0]*k[0]*k[1]*k[2] + (0)*c[29]*k[0]*k[0]*k[1] - (0)*c[29]*k[0]*k[0]*k[2]*k[2] - 383.999999999998*c[29]*k[0]*k[0]*k[2] - (0)*c[29]*k[0]*k[0] - (0)*c[29]*k[0]*k[1]*k[1]*k[1] - (0)*c[29]*k[0]*k[1]*k[1]*k[2] + (0)*c[29]*k[0]*k[1]*k[1] - (0)*c[29]*k[0]*k[1]*k[2]*k[2] - 255.999999999991*c[29]*k[0]*k[1]*k[2] - (0)*c[29]*k[0]*k[1] - (0)*c[29]*k[0]*k[2]*k[2]*k[2] - 255.999999999998*c[29]*k[0]*k[2]*k[2] + 319.999999999998*c[29]*k[0]*k[2] + (0)*c[29]*k[0] + (0)*c[29]*k[1]*k[1]*k[1]*k[1] - (0)*c[29]*k[1]*k[1]*k[1]*k[2] - (0)*c[29]*k[1]*k[1]*k[1] - (0)*c[29]*k[1]*k[1]*k[2]*k[2] + (0)*c[29]*k[1]*k[1]*k[2] - (0)*c[29]*k[1]*k[1] - (0)*c[29]*k[1]*k[2]*k[2]*k[2] + (0)*c[29]*k[1]*k[2]*k[2] + 31.9999999999965*c[29]*k[1]*k[2] + (0)*c[29]*k[1] + (0)*c[29]*k[2]*k[2]*k[2]*k[2] + (0)*c[29]*k[2]*k[2]*k[2] + 31.9999999999994*c[29]*k[2]*k[2] - 31.9999999999997*c[29]*k[2] - (0)*c[29] - (0) + (0) + (0) - (0) + (0) + (0) - (0) + (0) - (0) + (0) + (0) - (0) - (0) - (0) - (0) + (0) + (0) - (0) + (0) - (0) + (0) - (0) - (0) - (0) - (0) + (0) - (0) - (0) + (0) - (0) - (0) - (0) + (0) - (0) + (0) - (0)*c[30]*k[0]*k[0]*k[0]*k[0] - (0)*c[30]*k[0]*k[0]*k[0]*k[1] - (0)*c[30]*k[0]*k[0]*k[0]*k[2] + (0)*c[30]*k[0]*k[0]*k[0] + (0)*c[30]*k[0]*k[0]*k[1]*k[1] - (0)*c[30]*k[0]*k[0]*k[1]*k[2] + (0)*c[30]*k[0]*k[0]*k[1] - (0)*c[30]*k[0]*k[0]*k[2]*k[2] + (0)*c[30]*k[0]*k[0]*k[2] - (0)*c[30]*k[0]*k[0] - (0)*c[30]*k[0]*k[1]*k[1]*k[1] - (0)*c[30]*k[0]*k[1]*k[1]*k[2] + (0)*c[30]*k[0]*k[1]*k[1] - (0)*c[30]*k[0]*k[1]*k[2]*k[2] + (0)*c[30]*k[0]*k[1]*k[2] - (0)*c[30]*k[0]*k[1] - (0)*c[30]*k[0]*k[2]*k[2]*k[2] - 255.999999999999*c[30]*k[0]*k[2]*k[2] + 63.9999999999986*c[30]*k[0]*k[2] + (0)*c[30]*k[0] - (0)*c[30]*k[1]*k[1]*k[1]*k[1] - (0)*c[30]*k[1]*k[1]*k[1]*k[2] + (0)*c[30]*k[1]*k[1]*k[1] - (0)*c[30]*k[1]*k[1]*k[2]*k[2] + (0)*c[30]*k[1]*k[1]*k[2] - (0)*c[30]*k[1]*k[1] - (0)*c[30]*k[1]*k[2]*k[2]*k[2] - 127.999999999998*c[30]*k[1]*k[2]*k[2] + 31.9999999999982*c[30]*k[1]*k[2] + (0)*c[30]*k[1] + (0)*c[30]*k[2]*k[2]*k[2]*k[2] - 128.0*c[30]*k[2]*k[2]*k[2] + 160.0*c[30]*k[2]*k[2] - 31.9999999999998*c[30]*k[2] - (0)*c[30] + (0)*c[31]*k[0]*k[0]*k[0]*k[0] + (0)*c[31]*k[0]*k[0]*k[0]*k[1] + (0)*c[31]*k[0]*k[0]*k[0]*k[2] - (0)*c[31]*k[0]*k[0]*k[0] + (0)*c[31]*k[0]*k[0]*k[1]*k[1] + (0)*c[31]*k[0]*k[0]*k[1]*k[2] + 383.999999999998*c[31]*k[0]*k[0]*k[1] + (0)*c[31]*k[0]*k[0]*k[2]*k[2] - (0)*c[31]*k[0]*k[0]*k[2] + (0)*c[31]*k[0]*k[0] + (0)*c[31]*k[0]*k[1]*k[1]*k[1] + (0)*c[31]*k[0]*k[1]*k[1]*k[2] + 511.999999999998*c[31]*k[0]*k[1]*k[1] + (0)*c[31]*k[0]*k[1]*k[2]*k[2] + 511.999999999993*c[31]*k[0]*k[1]*k[2] - 447.999999999999*c[31]*k[0]*k[1] + (0)*c[31]*k[0]*k[2]*k[2]*k[2] - (0)*c[31]*k[0]*k[2]*k[2] + (0)*c[31]*k[0]*k[2] - (0)*c[31]*k[0] - (0)*c[31]*k[1]*k[1]*k[1]*k[1] + (0)*c[31]*k[1]*k[1]*k[1]*k[2] + 128.0*c[31]*k[1]*k[1]*k[1] + (0)*c[31]*k[1]*k[1]*k[2]*k[2] + 255.999999999995*c[31]*k[1]*k[1]*k[2] - 224.0*c[31]*k[1]*k[1] + (0)*c[31]*k[1]*k[2]*k[2]*k[2] + 127.999999999995*c[31]*k[1]*k[2]*k[2] - 223.999999999997*c[31]*k[1]*k[2] + 95.9999999999998*c[31]*k[1] - (0)*c[31]*k[2]*k[2]*k[2]*k[2] - (0)*c[31]*k[2]*k[2]*k[2] + (0)*c[31]*k[2]*k[2] - (0)*c[31]*k[2] + (0)*c[31] - (0)*c[32]*k[0]*k[0]*k[0]*k[0] + (0)*c[32]*k[0]*k[0]*k[0]*k[1] - (0)*c[32]*k[0]*k[0]*k[0]*k[2] + (0)*c[32]*k[0]*k[0]*k[0] - (0)*c[32]*k[0]*k[0]*k[1]*k[1] - (0)*c[32]*k[0]*k[0]*k[1]*k[2] - 383.999999999999*c[32]*k[0]*k[0]*k[1] - (0)*c[32]*k[0]*k[0]*k[2]*k[2] + (0)*c[32]*k[0]*k[0]*k[2] - (0)*c[32]*k[0]*k[0] - (0)*c[32]*k[0]*k[1]*k[1]*k[1] - (0)*c[32]*k[0]*k[1]*k[1]*k[2] - 255.999999999998*c[32]*k[0]*k[1]*k[1] - (0)*c[32]*k[0]*k[1]*k[2]*k[2] - 255.999999999992*c[32]*k[0]*k[1]*k[2] + 319.999999999999*c[32]*k[0]*k[1] - (0)*c[32]*k[0]*k[2]*k[2]*k[2] + (0)*c[32]*k[0]*k[2]*k[2] - (0)*c[32]*k[0]*k[2] + (0)*c[32]*k[0] + (0)*c[32]*k[1]*k[1]*k[1]*k[1] - (0)*c[32]*k[1]*k[1]*k[1]*k[2] - (0)*c[32]*k[1]*k[1]*k[1] - (0)*c[32]*k[1]*k[1]*k[2]*k[2] + (0)*c[32]*k[1]*k[1]*k[2] + 31.9999999999997*c[32]*k[1]*k[1] - (0)*c[32]*k[1]*k[2]*k[2]*k[2] + (0)*c[32]*k[1]*k[2]*k[2] + 31.9999999999972*c[32]*k[1]*k[2] - 31.9999999999997*c[32]*k[1] + (0)*c[32]*k[2]*k[2]*k[2]*k[2] + (0)*c[32]*k[2]*k[2]*k[2] - (0)*c[32]*k[2]*k[2] + (0)*c[32]*k[2] - (0)*c[32] - (0)*c[33]*k[0]*k[0]*k[0]*k[0] - (0)*c[33]*k[0]*k[0]*k[0]*k[1] + (0)*c[33]*k[0]*k[0]*k[0]*k[2] + (0)*c[33]*k[0]*k[0]*k[0] - (0)*c[33]*k[0]*k[0]*k[1]*k[1] - (0)*c[33]*k[0]*k[0]*k[1]*k[2] + (0)*c[33]*k[0]*k[0]*k[1] + (0)*c[33]*k[0]*k[0]*k[2]*k[2] - (0)*c[33]*k[0]*k[0]*k[2] - (0)*c[33]*k[0]*k[0] - (0)*c[33]*k[0]*k[1]*k[1]*k[1] + (0)*c[33]*k[0]*k[1]*k[1]*k[2] - 255.999999999999*c[33]*k[0]*k[1]*k[1] + (0)*c[33]*k[0]*k[1]*k[2]*k[2] - (0)*c[33]*k[0]*k[1]*k[2] + 63.9999999999996*c[33]*k[0]*k[1] + (0)*c[33]*k[0]*k[2]*k[2]*k[2] - (0)*c[33]*k[0]*k[2]*k[2] + (0)*c[33]*k[0]*k[2] + (0)*c[33]*k[0] + (0)*c[33]*k[1]*k[1]*k[1]*k[1] - (0)*c[33]*k[1]*k[1]*k[1]*k[2] - 128.0*c[33]*k[1]*k[1]*k[1] - (0)*c[33]*k[1]*k[1]*k[2]*k[2] - 127.999999999999*c[33]*k[1]*k[1]*k[2] + 160.0*c[33]*k[1]*k[1] - (0)*c[33]*k[1]*k[2]*k[2]*k[2] + (0)*c[33]*k[1]*k[2]*k[2] + 32.0*c[33]*k[1]*k[2] - 32.0000000000001*c[33]*k[1] - (0)*c[33]*k[2]*k[2]*k[2]*k[2] + (0)*c[33]*k[2]*k[2]*k[2] - (0)*c[33]*k[2]*k[2] - (0)*c[33]*k[2] + (0)*c[33] + (0)*c[34]*k[0]*k[0]*k[0]*k[0] - (0)*c[34]*k[0]*k[0]*k[0]*k[1] - (0)*c[34]*k[0]*k[0]*k[0]*k[2] + (0)*c[34]*k[0]*k[0]*k[0] - (0)*c[34]*k[0]*k[0]*k[1]*k[1] - (0)*c[34]*k[0]*k[0]*k[1]*k[2] + (0)*c[34]*k[0]*k[0]*k[1] - (0)*c[34]*k[0]*k[0]*k[2]*k[2] + (0)*c[34]*k[0]*k[0]*k[2] - (0)*c[34]*k[0]*k[0] - (0)*c[34]*k[0]*k[1]*k[1]*k[1] - (0)*c[34]*k[0]*k[1]*k[1]*k[2] + (0)*c[34]*k[0]*k[1]*k[1] - (0)*c[34]*k[0]*k[1]*k[2]*k[2] - 511.999999999982*c[34]*k[0]*k[1]*k[2] - (0)*c[34]*k[0]*k[1] - (0)*c[34]*k[0]*k[2]*k[2]*k[2] + (0)*c[34]*k[0]*k[2]*k[2] - (0)*c[34]*k[0]*k[2] + (0)*c[34]*k[0] + (0)*c[34]*k[1]*k[1]*k[1]*k[1] - (0)*c[34]*k[1]*k[1]*k[1]*k[2] - (0)*c[34]*k[1]*k[1]*k[1] - (0)*c[34]*k[1]*k[1]*k[2]*k[2] - 255.999999999997*c[34]*k[1]*k[1]*k[2] + (0)*c[34]*k[1]*k[1] + (0)*c[34]*k[1]*k[2]*k[2]*k[2] - 255.999999999997*c[34]*k[1]*k[2]*k[2] + 255.999999999997*c[34]*k[1]*k[2] + (0)*c[34]*k[1] + (0)*c[34]*k[2]*k[2]*k[2]*k[2] - (0)*c[34]*k[2]*k[2]*k[2] + (0)*c[34]*k[2]*k[2] + (0)*c[34]*k[2] - (0)*c[34] - (0) + (0) + (0) - (0) - (0) - (0) + (0) + (0) - (0) + (0) - (0) - (0) - (0) - (0) - (0) + (0) + (0) - (0) + (0) - (0) + (0) - (0) - (0) - (0) - (0) + (0) - (0) - (0) + (0) - (0) + (0) - (0) + (0) - (0) - (0) + (0) - (0) - (0) - (0) + (0) + (0) + (0) - (0) + (0) + (0) + (0) + (0) + (0) + (0) + (0) - (0) - (0) + (0) - (0) - (0) - (0) + (0) + (0) + (0) + (0) - (0) + (0) + (0) - (0) + (0) - (0) + (0) - (0) + (0) + (0) - (0) + (0) + (0) + (0) + (0) - (0) + (0) + (0) - (0) - (0) + (0) - (0) + (0) - (0) - (0) - (0) + (0) - (0) + (0) + (0) + (0) - (0) + (0) - (0) + (0) - (0) - (0) - (0) + (0) + (0) + (0) - (0) + (0) - (0) - (0) + (0) + (0) - (0) + (0) + (0) + (0) + (0) - (0) + (0) + (0) + (0) + (0) + (0) + (0) + (0) - (0) - (0) + (0) - (0) - (0) - (0) + (0) + (0) + (0) + (0) - (0) + (0) + (0) - (0) + (0) - (0) + (0) - (0) + (0) + (0) + (0) + (0) + (0) - (0) + (0) + (0) - (0) + (0) + 128.0*c[7]*k[0]*k[0]*k[2] + (0) - (0) + (0) - (0) + (0) - (0) + (0) - (0) - (0) - 63.9999999999998*c[7]*k[0]*k[2] - (0) - (0) + (0) + (0) + (0) - (0) - (0) + (0) - (0) + (0) + (0) - (0) + (0) - (0) + 5.33333333333335*c[7]*k[2] - (0) + (0) - (0) + (0) - (0) + (0) + (0) - (0) + (0) - (0) + (0) + (0) + (0) - (0) + (0) - (0) + (0) + (0) + 127.999999999997*c[8]*k[0]*k[2]*k[2] - 31.9999999999983*c[8]*k[0]*k[2] - (0) + (0) + (0) - (0) + (0) - (0) + (0) + (0) - (0) + (0) - (0) - (0) - (0) - 15.9999999999997*c[8]*k[2]*k[2] + 3.99999999999977*c[8]*k[2] + (0) + (0) + (0) - (0) + (0) - (0) - (0) + (0) - (0) + (0) - (0) - (0) - (0) + (0) - (0) + (0) - (0) - (0) + (0) - (0) + (0) + (0) + (0) - (0) + (0) - (0) + (0) + (0) - (0) + (0) - (0) + (0) + 42.6666666666668*c[9]*k[2]*k[2]*k[2] - 32.0000000000001*c[9]*k[2]*k[2] + 5.33333333333341*c[9]*k[2] - (0) + 0;

	H[1] = (0) - (0) - (0) + 42.6666666666667*c[0]*k[0]*k[0]*k[0] + (0) - (0) + 128.0*c[0]*k[0]*k[0]*k[1] - (0) + 128.000000000001*c[0]*k[0]*k[0]*k[2] - 80.0000000000001*c[0]*k[0]*k[0] + (0) - (0) + 128.0*c[0]*k[0]*k[1]*k[1] - (0) + 256.000000000001*c[0]*k[0]*k[1]*k[2] - 160.0*c[0]*k[0]*k[1] - (0) + 128.000000000001*c[0]*k[0]*k[2]*k[2] - 160.0*c[0]*k[0]*k[2] + 46.6666666666668*c[0]*k[0] - (0) + (0) + 42.6666666666666*c[0]*k[1]*k[1]*k[1] + (0) + 128.0*c[0]*k[1]*k[1]*k[2] - 80.0*c[0]*k[1]*k[1] + (0) + 128.0*c[0]*k[1]*k[2]*k[2] - 160.0*c[0]*k[1]*k[2] + 46.6666666666667*c[0]*k[1] - (0) + 42.6666666666668*c[0]*k[2]*k[2]*k[2] - 80.0000000000001*c[0]*k[2]*k[2] + 46.6666666666667*c[0]*k[2] - 8.33333333333335*c[0] + (0)*c[10]*k[0]*k[0]*k[0]*k[0] + (0)*c[10]*k[0]*k[0]*k[0]*k[1] + (0)*c[10]*k[0]*k[0]*k[0]*k[2] + 42.6666666666662*c[10]*k[0]*k[0]*k[0] + (0)*c[10]*k[0]*k[0]*k[1]*k[1] - (0)*c[10]*k[0]*k[0]*k[1]*k[2] - (0)*c[10]*k[0]*k[0]*k[1] - (0)*c[10]*k[0]*k[0]*k[2]*k[2] - (0)*c[10]*k[0]*k[0]*k[2] - 31.9999999999996*c[10]*k[0]*k[0] - (0)*c[10]*k[0]*k[1]*k[1]*k[1] - (0)*c[10]*k[0]*k[1]*k[1]*k[2] + (0)*c[10]*k[0]*k[1]*k[1] - (0)*c[10]*k[0]*k[1]*k[2]*k[2] + (0)*c[10]*k[0]*k[1]*k[2] + (0)*c[10]*k[0]*k[1] - (0)*c[10]*k[0]*k[2]*k[2]*k[2] + (0)*c[10]*k[0]*k[2]*k[2] - (0)*c[10]*k[0]*k[2] + 5.33333333333319*c[10]*k[0] - (0)*c[10]*k[1]*k[1]*k[1]*k[1] - (0)*c[10]*k[1]*k[1]*k[1]*k[2] + (0)*c[10]*k[1]*k[1]*k[1] - (0)*c[10]*k[1]*k[1]*k[2]*k[2] + (0)*c[10]*k[1]*k[1]*k[2] - (0)*c[10]*k[1]*k[1] - (0)*c[10]*k[1]*k[2]*k[2]*k[2] + (0)*c[10]*k[1]*k[2]*k[2] - (0)*c[10]*k[1]*k[2] + (0)*c[10]*k[1] + (0)*c[10]*k[2]*k[2]*k[2]*k[2] - (0)*c[10]*k[2]*k[2]*k[2] - (0)*c[10]*k[2]*k[2] + (0)*c[10]*k[2] + (0)*c[10] - (0)*c[11]*k[0]*k[0]*k[0]*k[0] - (0)*c[11]*k[0]*k[0]*k[0]*k[1] - (0)*c[11]*k[0]*k[0]*k[0]*k[2] + (0)*c[11]*k[0]*k[0]*k[0] - (0)*c[11]*k[0]*k[0]*k[1]*k[1] - (0)*c[11]*k[0]*k[0]*k[1]*k[2] + 128.000000000001*c[11]*k[0]*k[0]*k[1] - (0)*c[11]*k[0]*k[0]*k[2]*k[2] + (0)*c[11]*k[0]*k[0]*k[2] - 16.0000000000003*c[11]*k[0]*k[0] - (0)*c[11]*k[0]*k[1]*k[1]*k[1] - (0)*c[11]*k[0]*k[1]*k[1]*k[2] + (0)*c[11]*k[0]*k[1]*k[1] - (0)*c[11]*k[0]*k[1]*k[2]*k[2] + (0)*c[11]*k[0]*k[1]*k[2] - 32.0000000000009*c[11]*k[0]*k[1] - (0)*c[11]*k[0]*k[2]*k[2]*k[2] + (0)*c[11]*k[0]*k[2]*k[2] - (0)*c[11]*k[0]*k[2] + 4.00000000000023*c[11]*k[0] + (0)*c[11]*k[1]*k[1]*k[1]*k[1] + (0)*c[11]*k[1]*k[1]*k[1]*k[2] - (0)*c[11]*k[1]*k[1]*k[1] - (0)*c[11]*k[1]*k[1]*k[2]*k[2] + (0)*c[11]*k[1]*k[1]*k[2] + (0)*c[11]*k[1]*k[1] - (0)*c[11]*k[1]*k[2]*k[2]*k[2] + (0)*c[11]*k[1]*k[2]*k[2] - (0)*c[11]*k[1]*k[2] + (0)*c[11]*k[1] - (0)*c[11]*k[2]*k[2]*k[2]*k[2] + (0)*c[11]*k[2]*k[2]*k[2] - (0)*c[11]*k[2]*k[2] + (0)*c[11]*k[2] - (0)*c[11] - (0)*c[12]*k[0]*k[0]*k[0]*k[0] + (0)*c[12]*k[0]*k[0]*k[0]*k[1] + (0)*c[12]*k[0]*k[0]*k[0]*k[2] - (0)*c[12]*k[0]*k[0]*k[0] + (0)*c[12]*k[0]*k[0]*k[1]*k[1] + (0)*c[12]*k[0]*k[0]*k[1]*k[2] - (0)*c[12]*k[0]*k[0]*k[1] - (0)*c[12]*k[0]*k[0]*k[2]*k[2] - (0)*c[12]*k[0]*k[0]*k[2] + (0)*c[12]*k[0]*k[0] + (0)*c[12]*k[0]*k[1]*k[1]*k[1] + (0)*c[12]*k[0]*k[1]*k[1]*k[2] + 127.999999999998*c[12]*k[0]*k[1]*k[1] + (0)*c[12]*k[0]*k[1]*k[2]*k[2] - (0)*c[12]*k[0]*k[1]*k[2] - 63.9999999999987*c[12]*k[0]*k[1] - (0)*c[12]*k[0]*k[2]*k[2]*k[2] - (0)*c[12]*k[0]*k[2]*k[2] + (0)*c[12]*k[0]*k[2] + 5.33333333333318*c[12]*k[0] - (0)*c[12]*k[1]*k[1]*k[1]*k[1] + (0)*c[12]*k[1]*k[1]*k[1]*k[2] + (0)*c[12]*k[1]*k[1]*k[1] + (0)*c[12]*k[1]*k[1]*k[2]*k[2] - (0)*c[12]*k[1]*k[1]*k[2] + (0)*c[12]*k[1]*k[1] + (0)*c[12]*k[1]*k[2]*k[2]*k[2] - (0)*c[12]*k[1]*k[2]*k[2] + (0)*c[12]*k[1]*k[2] - (0)*c[12]*k[1] - (0)*c[12]*k[2]*k[2]*k[2]*k[2] - (0)*c[12]*k[2]*k[2]*k[2] + (0)*c[12]*k[2]*k[2] - (0)*c[12]*k[2] + (0)*c[12] - (0)*c[13]*k[0]*k[0]*k[0]*k[0] - (0)*c[13]*k[0]*k[0]*k[0]*k[1] + (0)*c[13]*k[0]*k[0]*k[0]*k[2] + (0)*c[13]*k[0]*k[0]*k[0] - (0)*c[13]*k[0]*k[0]*k[1]*k[1] + (0)*c[13]*k[0]*k[0]*k[1]*k[2] + (0)*c[13]*k[0]*k[0]*k[1] + (0)*c[13]*k[0]*k[0]*k[2]*k[2] - 128.000000000001*c[13]*k[0]*k[0]*k[2] - (0)*c[13]*k[0]*k[0] + (0)*c[13]*k[0]*k[1]*k[1]*k[1] + (0)*c[13]*k[0]*k[1]*k[1]*k[2] - (0)*c[13]*k[0]*k[1]*k[1] + (0)*c[13]*k[0]*k[1]*k[2]*k[2] - 256.000000000002*c[13]*k[0]*k[1]*k[2] + (0)*c[13]*k[0]*k[1] + (0)*c[13]*k[0]*k[2]*k[2]*k[2] - 256.000000000001*c[13]*k[0]*k[2]*k[2] + 192.000000000001*c[13]*k[0]*k[2] - (0)*c[13]*k[0] - (0)*c[13]*k[1]*k[1]*k[1]*k[1] - (0)*c[13]*k[1]*k[1]*k[1]*k[2] + (0)*c[13]*k[1]*k[1]*k[1] - (0)*c[13]*k[1]*k[1]*k[2]*k[2] - 127.999999999999*c[13]*k[1]*k[1]*k[2] - (0)*c[13]*k[1]*k[1] - (0)*c[13]*k[1]*k[2]*k[2]*k[2] - 255.999999999999*c[13]*k[1]*k[2]*k[2] + 192.0*c[13]*k[1]*k[2] + (0)*c[13]*k[1] + (0)*c[13]*k[2]*k[2]*k[2]*k[2] - 128.0*c[13]*k[2]*k[2]*k[2] + 192.0*c[13]*k[2]*k[2] - 69.3333333333334*c[13]*k[2] - (0)*c[13] + (0)*c[14]*k[0]*k[0]*k[0]*k[0] + (0)*c[14]*k[0]*k[0]*k[0]*k[1] - (0)*c[14]*k[0]*k[0]*k[0]*k[2] - (0)*c[14]*k[0]*k[0]*k[0] - (0)*c[14]*k[0]*k[0]*k[1]*k[1] + (0)*c[14]*k[0]*k[0]*k[1]*k[2] - (0)*c[14]*k[0]*k[0]*k[1] - (0)*c[14]*k[0]*k[0]*k[2]*k[2] + (0)*c[14]*k[0]*k[0]*k[2] - (0)*c[14]*k[0]*k[0] - (0)*c[14]*k[0]*k[1]*k[1]*k[1] + (0)*c[14]*k[0]*k[1]*k[1]*k[2] + (0)*c[14]*k[0]*k[1]*k[1] + (0)*c[14]*k[0]*k[1]*k[2]*k[2] - (0)*c[14]*k[0]*k[1]*k[2] + (0)*c[14]*k[0]*k[1] - (0)*c[14]*k[0]*k[2]*k[2]*k[2] + 128.000000000001*c[14]*k[0]*k[2]*k[2] - 32.0*c[14]*k[0]*k[2] + (0)*c[14]*k[0] + (0)*c[14]*k[1]*k[1]*k[1]*k[1] + (0)*c[14]*k[1]*k[1]*k[1]*k[2] - (0)*c[14]*k[1]*k[1]*k[1] + (0)*c[14]*k[1]*k[1]*k[2]*k[2] - (0)*c[14]*k[1]*k[1]*k[2] + (0)*c[14]*k[1]*k[1] + (0)*c[14]*k[1]*k[2]*k[2]*k[2] + 127.999999999999*c[14]*k[1]*k[2]*k[2] - 31.9999999999991*c[14]*k[1]*k[2] - (0)*c[14]*k[1] - (0)*c[14]*k[2]*k[2]*k[2]*k[2] + 128.0*c[14]*k[2]*k[2]*k[2] - 144.0*c[14]*k[2]*k[2] + 28.0*c[14]*k[2] - (0)*c[14] - (0)*c[15]*k[0]*k[0]*k[0]*k[0] - (0)*c[15]*k[0]*k[0]*k[0]*k[1] + (0)*c[15]*k[0]*k[0]*k[0]*k[2] - (0)*c[15]*k[0]*k[0]*k[0] + (0)*c[15]*k[0]*k[0]*k[1]*k[1] + (0)*c[15]*k[0]*k[0]*k[1]*k[2] - (0)*c[15]*k[0]*k[0]*k[1] + (0)*c[15]*k[0]*k[0]*k[2]*k[2] - (0)*c[15]*k[0]*k[0]*k[2] + (0)*c[15]*k[0]*k[0] + (0)*c[15]*k[0]*k[1]*k[1]*k[1] + (0)*c[15]*k[0]*k[1]*k[1]*k[2] - (0)*c[15]*k[0]*k[1]*k[1] + (0)*c[15]*k[0]*k[1]*k[2]*k[2] - (0)*c[15]*k[0]*k[1]*k[2] + (0)*c[15]*k[0]*k[1] + (0)*c[15]*k[0]*k[2]*k[2]*k[2] - (0)*c[15]*k[0]*k[2]*k[2] + (0)*c[15]*k[0]*k[2] - (0)*c[15]*k[0] - (0)*c[15]*k[1]*k[1]*k[1]*k[1] - (0)*c[15]*k[1]*k[1]*k[1]*k[2] + (0)*c[15]*k[1]*k[1]*k[1] - (0)*c[15]*k[1]*k[1]*k[2]*k[2] + (0)*c[15]*k[1]*k[1]*k[2] - (0)*c[15]*k[1]*k[1] - (0)*c[15]*k[1]*k[2]*k[2]*k[2] + (0)*c[15]*k[1]*k[2]*k[2] - (0)*c[15]*k[1]*k[2] + (0)*c[15]*k[1] + (0)*c[15]*k[2]*k[2]*k[2]*k[2] - 42.6666666666667*c[15]*k[2]*k[2]*k[2] + 32.0000000000001*c[15]*k[2]*k[2] - 5.33333333333337*c[15]*k[2] + (0)*c[15] - (0)*c[16]*k[0]*k[0]*k[0]*k[0] + (0)*c[16]*k[0]*k[0]*k[0]*k[1] + (0)*c[16]*k[0]*k[0]*k[0]*k[2] - 42.6666666666666*c[16]*k[0]*k[0]*k[0] - (0)*c[16]*k[0]*k[0]*k[1]*k[1] + (0)*c[16]*k[0]*k[0]*k[1]*k[2] - 256.0*c[16]*k[0]*k[0]*k[1] + (0)*c[16]*k[0]*k[0]*k[2]*k[2] - 128.000000000001*c[16]*k[0]*k[0]*k[2] + 96.0000000000001*c[16]*k[0]*k[0] - (0)*c[16]*k[0]*k[1]*k[1]*k[1] - (0)*c[16]*k[0]*k[1]*k[1]*k[2] - 383.999999999999*c[16]*k[0]*k[1]*k[1] + (0)*c[16]*k[0]*k[1]*k[2]*k[2] - 512.000000000001*c[16]*k[0]*k[1]*k[2] + 384.0*c[16]*k[0]*k[1] + (0)*c[16]*k[0]*k[2]*k[2]*k[2] - 128.000000000001*c[16]*k[0]*k[2]*k[2] + 192.000000000001*c[16]*k[0]*k[2] - 69.3333333333334*c[16]*k[0] + (0)*c[16]*k[1]*k[1]*k[1]*k[1] - (0)*c[16]*k[1]*k[1]*k[1]*k[2] - 170.666666666666*c[16]*k[1]*k[1]*k[1] - (0)*c[16]*k[1]*k[1]*k[2]*k[2] - 383.999999999999*c[16]*k[1]*k[1]*k[2] + 288.0*c[16]*k[1]*k[1] - (0)*c[16]*k[1]*k[2]*k[2]*k[2] - 255.999999999999*c[16]*k[1]*k[2]*k[2] + 384.0*c[16]*k[1]*k[2] - 138.666666666667*c[16]*k[1] + (0)*c[16]*k[2]*k[2]*k[2]*k[2] - 42.6666666666671*c[16]*k[2]*k[2]*k[2] + 96.0000000000002*c[16]*k[2]*k[2] - 69.3333333333334*c[16]*k[2] + 16.0*c[16] + (0)*c[17]*k[0]*k[0]*k[0]*k[0] + (0)*c[17]*k[0]*k[0]*k[0]*k[1] + (0)*c[17]*k[0]*k[0]*k[0]*k[2] - (0)*c[17]*k[0]*k[0]*k[0] + (0)*c[17]*k[0]*k[0]*k[1]*k[1] - (0)*c[17]*k[0]*k[0]*k[1]*k[2] + 128.0*c[17]*k[0]*k[0]*k[1] - (0)*c[17]*k[0]*k[0]*k[2]*k[2] + (0)*c[17]*k[0]*k[0]*k[2] - 15.9999999999999*c[17]*k[0]*k[0] + (0)*c[17]*k[0]*k[1]*k[1]*k[1] - (0)*c[17]*k[0]*k[1]*k[1]*k[2] + 384.0*c[17]*k[0]*k[1]*k[1] - (0)*c[17]*k[0]*k[1]*k[2]*k[2] + 256.000000000002*c[17]*k[0]*k[1]*k[2] - 288.0*c[17]*k[0]*k[1] - (0)*c[17]*k[0]*k[2]*k[2]*k[2] + (0)*c[17]*k[0]*k[2]*k[2] - 32.0000000000005*c[17]*k[0]*k[2] + 28.0*c[17]*k[0] + (0)*c[17]*k[1]*k[1]*k[1]*k[1] + (0)*c[17]*k[1]*k[1]*k[1]*k[2] + 256.0*c[17]*k[1]*k[1]*k[1] - (0)*c[17]*k[1]*k[1]*k[2]*k[2] + 384.0*c[17]*k[1]*k[1]*k[2] - 384.0*c[17]*k[1]*k[1] - (0)*c[17]*k[1]*k[2]*k[2]*k[2] + 128.000000000001*c[17]*k[1]*k[2]*k[2] - 288.0*c[17]*k[1]*k[2] + 152.0*c[17]*k[1] - (0)*c[17]*k[2]*k[2]*k[2]*k[2] + (0)*c[17]*k[2]*k[2]*k[2] - 16.0000000000002*c[17]*k[2]*k[2] + 28.0000000000001*c[17]*k[2] - 12.0*c[17] - (0)*c[18]*k[0]*k[0]*k[0]*k[0] - (0)*c[18]*k[0]*k[0]*k[0]*k[1] - (0)*c[18]*k[0]*k[0]*k[0]*k[2] + (0)*c[18]*k[0]*k[0]*k[0] - (0)*c[18]*k[0]*k[0]*k[1]*k[1] + (0)*c[18]*k[0]*k[0]*k[1]*k[2] + (0)*c[18]*k[0]*k[0]*k[1] - (0)*c[18]*k[0]*k[0]*k[2]*k[2] + (0)*c[18]*k[0]*k[0]*k[2] - (0)*c[18]*k[0]*k[0] + (0)*c[18]*k[0]*k[1]*k[1]*k[1] + (0)*c[18]*k[0]*k[1]*k[1]*k[2] - 128.000000000001*c[18]*k[0]*k[1]*k[1] + (0)*c[18]*k[0]*k[1]*k[2]*k[2] - (0)*c[18]*k[0]*k[1]*k[2] + 64.0000000000002*c[18]*k[0]*k[1] - (0)*c[18]*k[0]*k[2]*k[2]*k[2] + (0)*c[18]*k[0]*k[2]*k[2] + (0)*c[18]*k[0]*k[2] - 5.3333333333333*c[18]*k[0] - (0)*c[18]*k[1]*k[1]*k[1]*k[1] + (0)*c[18]*k[1]*k[1]*k[1]*k[2] - 170.666666666666*c[18]*k[1]*k[1]*k[1] + (0)*c[18]*k[1]*k[1]*k[2]*k[2] - 128.000000000002*c[18]*k[1]*k[1]*k[2] + 224.0*c[18]*k[1]*k[1] + (0)*c[18]*k[1]*k[2]*k[2]*k[2] - (0)*c[18]*k[1]*k[2]*k[2] + 64.000000000001*c[18]*k[1]*k[2] - 74.6666666666667*c[18]*k[1] - (0)*c[18]*k[2]*k[2]*k[2]*k[2] + (0)*c[18]*k[2]*k[2]*k[2] - (0)*c[18]*k[2]*k[2] - 5.33333333333335*c[18]*k[2] + 5.33333333333332*c[18] - (0)*c[19]*k[0]*k[0]*k[0]*k[0] - (0)*c[19]*k[0]*k[0]*k[0]*k[1] + (0)*c[19]*k[0]*k[0]*k[0]*k[2] - 128.0*c[19]*k[0]*k[0]*k[0] - (0)*c[19]*k[0]*k[0]*k[1]*k[1] + (0)*c[19]*k[0]*k[0]*k[1]*k[2] - 256.0*c[19]*k[0]*k[0]*k[1] + (0)*c[19]*k[0]*k[0]*k[2]*k[2] - 256.000000000001*c[19]*k[0]*k[0]*k[2] + 192.0*c[19]*k[0]*k[0] - (0)*c[19]*k[0]*k[1]*k[1]*k[1] - (0)*c[19]*k[0]*k[1]*k[1]*k[2] - 128.0*c[19]*k[0]*k[1]*k[1] + (0)*c[19]*k[0]*k[1]*k[2]*k[2] - 256.000000000001*c[19]*k[0]*k[1]*k[2] + 192.0*c[19]*k[0]*k[1] + (0)*c[19]*k[0]*k[2]*k[2]*k[2] - 128.000000000001*c[19]*k[0]*k[2]*k[2] + 192.000000000001*c[19]*k[0]*k[2] - 69.3333333333335*c[19]*k[0] + (0)*c[19]*k[1]*k[1]*k[1]*k[1] - (0)*c[19]*k[1]*k[1]*k[1]*k[2] + (0)*c[19]*k[1]*k[1]*k[1] - (0)*c[19]*k[1]*k[1]*k[2]*k[2] + (0)*c[19]*k[1]*k[1]*k[2] - (0)*c[19]*k[1]*k[1] - (0)*c[19]*k[1]*k[2]*k[2]*k[2] + (0)*c[19]*k[1]*k[2]*k[2] - (0)*c[19]*k[1]*k[2] - (0)*c[19]*k[1] + (0)*c[19]*k[2]*k[2]*k[2]*k[2] - (0)*c[19]*k[2]*k[2]*k[2] + (0)*c[19]*k[2]*k[2] - (0)*c[19]*k[2] + (0)*c[19] - (0) - (0) + (0) + (0) + (0) + (0) + (0) + (0) - (0) - (0) + (0) - (0) - (0) + (0) - (0) - (0) + (0) - (0) + (0) + (0) + (0) + (0) - (0) + (0) - (0) + (0) + (0) - (0) + (0) + (0) + (0) - (0) + (0) - (0) - (0) + (0)*c[20]*k[0]*k[0]*k[0]*k[0] + (0)*c[20]*k[0]*k[0]*k[0]*k[1] + (0)*c[20]*k[0]*k[0]*k[0]*k[2] + 127.999999999999*c[20]*k[0]*k[0]*k[0] + (0)*c[20]*k[0]*k[0]*k[1]*k[1] + (0)*c[20]*k[0]*k[0]*k[1]*k[2] + 127.999999999998*c[20]*k[0]*k[0]*k[1] + (0)*c[20]*k[0]*k[0]*k[2]*k[2] + 127.999999999997*c[20]*k[0]*k[0]*k[2] - 143.999999999999*c[20]*k[0]*k[0] + (0)*c[20]*k[0]*k[1]*k[1]*k[1] - (0)*c[20]*k[0]*k[1]*k[1]*k[2] - (0)*c[20]*k[0]*k[1]*k[1] - (0)*c[20]*k[0]*k[1]*k[2]*k[2] + (0)*c[20]*k[0]*k[1]*k[2] - 31.9999999999995*c[20]*k[0]*k[1] + (0)*c[20]*k[0]*k[2]*k[2]*k[2] - (0)*c[20]*k[0]*k[2]*k[2] - 31.9999999999993*c[20]*k[0]*k[2] + 27.9999999999999*c[20]*k[0] + (0)*c[20]*k[1]*k[1]*k[1]*k[1] - (0)*c[20]*k[1]*k[1]*k[1]*k[2] - (0)*c[20]*k[1]*k[1]*k[1] - (0)*c[20]*k[1]*k[1]*k[2]*k[2] + (0)*c[20]*k[1]*k[1]*k[2] + (0)*c[20]*k[1]*k[1] - (0)*c[20]*k[1]*k[2]*k[2]*k[2] + (0)*c[20]*k[1]*k[2]*k[2] - (0)*c[20]*k[1]*k[2] + (0)*c[20]*k[1] - (0)*c[20]*k[2]*k[2]*k[2]*k[2] + (0)*c[20]*k[2]*k[2]*k[2] - (0)*c[20]*k[2]*k[2] + (0)*c[20]*k[2] - (0)*c[20] - (0)*c[21]*k[0]*k[0]*k[0]*k[0] - (0)*c[21]*k[0]*k[0]*k[0]*k[1] - (0)*c[21]*k[0]*k[0]*k[0]*k[2] - 42.6666666666663*c[21]*k[0]*k[0]*k[0] - (0)*c[21]*k[0]*k[0]*k[1]*k[1] + (0)*c[21]*k[0]*k[0]*k[1]*k[2] + (0)*c[21]*k[0]*k[0]*k[1] - (0)*c[21]*k[0]*k[0]*k[2]*k[2] + (0)*c[21]*k[0]*k[0]*k[2] + 31.9999999999998*c[21]*k[0]*k[0] + (0)*c[21]*k[0]*k[1]*k[1]*k[1] + (0)*c[21]*k[0]*k[1]*k[1]*k[2] - (0)*c[21]*k[0]*k[1]*k[1] + (0)*c[21]*k[0]*k[1]*k[2]*k[2] - (0)*c[21]*k[0]*k[1]*k[2] + (0)*c[21]*k[0]*k[1] + (0)*c[21]*k[0]*k[2]*k[2]*k[2] - (0)*c[21]*k[0]*k[2]*k[2] + (0)*c[21]*k[0]*k[2] - 5.33333333333333*c[21]*k[0] + (0)*c[21]*k[1]*k[1]*k[1]*k[1] + (0)*c[21]*k[1]*k[1]*k[1]*k[2] - (0)*c[21]*k[1]*k[1]*k[1] + (0)*c[21]*k[1]*k[1]*k[2]*k[2] - (0)*c[21]*k[1]*k[1]*k[2] + (0)*c[21]*k[1]*k[1] + (0)*c[21]*k[1]*k[2]*k[2]*k[2] - (0)*c[21]*k[1]*k[2]*k[2] + (0)*c[21]*k[1]*k[2] - (0)*c[21]*k[1] + (0)*c[21]*k[2]*k[2]*k[2]*k[2] - (0)*c[21]*k[2]*k[2]*k[2] + (0)*c[21]*k[2]*k[2] - (0)*c[21]*k[2] + (0)*c[21] + (0)*c[22]*k[0]*k[0]*k[0]*k[0] + (0)*c[22]*k[0]*k[0]*k[0]*k[1] + (0)*c[22]*k[0]*k[0]*k[0]*k[2] - (0)*c[22]*k[0]*k[0]*k[0] + (0)*c[22]*k[0]*k[0]*k[1]*k[1] + (0)*c[22]*k[0]*k[0]*k[1]*k[2] - (0)*c[22]*k[0]*k[0]*k[1] + (0)*c[22]*k[0]*k[0]*k[2]*k[2] + 127.999999999994*c[22]*k[0]*k[0]*k[2] + (0)*c[22]*k[0]*k[0] - (0)*c[22]*k[0]*k[1]*k[1]*k[1] + (0)*c[22]*k[0]*k[1]*k[1]*k[2] + (0)*c[22]*k[0]*k[1]*k[1] + (0)*c[22]*k[0]*k[1]*k[2]*k[2] - (0)*c[22]*k[0]*k[1]*k[2] + (0)*c[22]*k[0]*k[1] + (0)*c[22]*k[0]*k[2]*k[2]*k[2] - (0)*c[22]*k[0]*k[2]*k[2] - 31.9999999999972*c[22]*k[0]*k[2] - (0)*c[22]*k[0] - (0)*c[22]*k[1]*k[1]*k[1]*k[1] - (0)*c[22]*k[1]*k[1]*k[1]*k[2] + (0)*c[22]*k[1]*k[1]*k[1] - (0)*c[22]*k[1]*k[1]*k[2]*k[2] + (0)*c[22]*k[1]*k[1]*k[2] - (0)*c[22]*k[1]*k[1] - (0)*c[22]*k[1]*k[2]*k[2]*k[2] + (0)*c[22]*k[1]*k[2]*k[2] - (0)*c[22]*k[1]*k[2] + (0)*c[22]*k[1] - (0)*c[22]*k[2]*k[2]*k[2]*k[2] + (0)*c[22]*k[2]*k[2]*k[2] + (0)*c[22]*k[2]*k[2] - (0)*c[22]*k[2] + (0)*c[22] - (0)*c[23]*k[0]*k[0]*k[0]*k[0] + (0)*c[23]*k[0]*k[0]*k[0]*k[1] + (0)*c[23]*k[0]*k[0]*k[0]*k[2] - (0)*c[23]*k[0]*k[0]*k[0] + (0)*c[23]*k[0]*k[0]*k[1]*k[1] - (0)*c[23]*k[0]*k[0]*k[1]*k[2] - (0)*c[23]*k[0]*k[0]*k[1] + (0)*c[23]*k[0]*k[0]*k[2]*k[2] - (0)*c[23]*k[0]*k[0]*k[2] + (0)*c[23]*k[0]*k[0] + (0)*c[23]*k[0]*k[1]*k[1]*k[1] - (0)*c[23]*k[0]*k[1]*k[1]*k[2] + (0)*c[23]*k[0]*k[1]*k[1] - (0)*c[23]*k[0]*k[1]*k[2]*k[2] + 256.000000000007*c[23]*k[0]*k[1]*k[2] - (0)*c[23]*k[0]*k[1] + (0)*c[23]*k[0]*k[2]*k[2]*k[2] - (0)*c[23]*k[0]*k[2]*k[2] - 32.0*c[23]*k[0]*k[2] - (0)*c[23]*k[0] + (0)*c[23]*k[1]*k[1]*k[1]*k[1] - (0)*c[23]*k[1]*k[1]*k[1]*k[2] + (0)*c[23]*k[1]*k[1]*k[1] - (0)*c[23]*k[1]*k[1]*k[2]*k[2] + (0)*c[23]*k[1]*k[1]*k[2] - (0)*c[23]*k[1]*k[1] - (0)*c[23]*k[1]*k[2]*k[2]*k[2] + (0)*c[23]*k[1]*k[2]*k[2] - (0)*c[23]*k[1]*k[2] + (0)*c[23]*k[1] + (0)*c[23]*k[2]*k[2]*k[2]*k[2] - (0)*c[23]*k[2]*k[2]*k[2] - (0)*c[23]*k[2]*k[2] + (0)*c[23]*k[2] - (0)*c[23] - (0)*c[24]*k[0]*k[0]*k[0]*k[0] - (0)*c[24]*k[0]*k[0]*k[0]*k[1] + (0)*c[24]*k[0]*k[0]*k[0]*k[2] - (0)*c[24]*k[0]*k[0]*k[0] + (0)*c[24]*k[0]*k[0]*k[1]*k[1] + (0)*c[24]*k[0]*k[0]*k[1]*k[2] - (0)*c[24]*k[0]*k[0]*k[1] + (0)*c[24]*k[0]*k[0]*k[2]*k[2] - (0)*c[24]*k[0]*k[0]*k[2] + (0)*c[24]*k[0]*k[0] + (0)*c[24]*k[0]*k[1]*k[1]*k[1] + (0)*c[24]*k[0]*k[1]*k[1]*k[2] - (0)*c[24]*k[0]*k[1]*k[1] + (0)*c[24]*k[0]*k[1]*k[2]*k[2] - (0)*c[24]*k[0]*k[1]*k[2] + (0)*c[24]*k[0]*k[1] + (0)*c[24]*k[0]*k[2]*k[2]*k[2] + 127.999999999998*c[24]*k[0]*k[2]*k[2] - 31.999999999999*c[24]*k[0]*k[2] - (0)*c[24]*k[0] + (0)*c[24]*k[1]*k[1]*k[1]*k[1] + (0)*c[24]*k[1]*k[1]*k[1]*k[2] - (0)*c[24]*k[1]*k[1]*k[1] - (0)*c[24]*k[1]*k[1]*k[2]*k[2] + (0)*c[24]*k[1]*k[1]*k[2] + (0)*c[24]*k[1]*k[1] - (0)*c[24]*k[1]*k[2]*k[2]*k[2] + (0)*c[24]*k[1]*k[2]*k[2] - (0)*c[24]*k[1]*k[2] - (0)*c[24]*k[1] + (0)*c[24]*k[2]*k[2]*k[2]*k[2] - (0)*c[24]*k[2]*k[2]*k[2] + (0)*c[24]*k[2]*k[2] - (0)*c[24]*k[2] + (0)*c[24] + (0)*c[25]*k[0]*k[0]*k[0]*k[0] + (0)*c[25]*k[0]*k[0]*k[0]*k[1] - (0)*c[25]*k[0]*k[0]*k[0]*k[2] + (0)*c[25]*k[0]*k[0]*k[0] + (0)*c[25]*k[0]*k[0]*k[1]*k[1] + (0)*c[25]*k[0]*k[0]*k[1]*k[2] - (0)*c[25]*k[0]*k[0]*k[1] - (0)*c[25]*k[0]*k[0]*k[2]*k[2] + 128.000000000002*c[25]*k[0]*k[0]*k[2] - (0)*c[25]*k[0]*k[0] + (0)*c[25]*k[0]*k[1]*k[1]*k[1] + (0)*c[25]*k[0]*k[1]*k[1]*k[2] - (0)*c[25]*k[0]*k[1]*k[1] + (0)*c[25]*k[0]*k[1]*k[2]*k[2] + 511.999999999995*c[25]*k[0]*k[1]*k[2] + (0)*c[25]*k[0]*k[1] - (0)*c[25]*k[0]*k[2]*k[2]*k[2] + 256.000000000001*c[25]*k[0]*k[2]*k[2] - 224.0*c[25]*k[0]*k[2] - (0)*c[25]*k[0] - (0)*c[25]*k[1]*k[1]*k[1]*k[1] + (0)*c[25]*k[1]*k[1]*k[1]*k[2] - (0)*c[25]*k[1]*k[1]*k[1] + (0)*c[25]*k[1]*k[1]*k[2]*k[2] + 383.999999999993*c[25]*k[1]*k[1]*k[2] + (0)*c[25]*k[1]*k[1] + (0)*c[25]*k[1]*k[2]*k[2]*k[2] + 511.999999999994*c[25]*k[1]*k[2]*k[2] - 447.999999999997*c[25]*k[1]*k[2] - (0)*c[25]*k[1] - (0)*c[25]*k[2]*k[2]*k[2]*k[2] + 128.0*c[25]*k[2]*k[2]*k[2] - 224.0*c[25]*k[2]*k[2] + 95.9999999999998*c[25]*k[2] + (0)*c[25] + (0)*c[26]*k[0]*k[0]*k[0]*k[0] - (0)*c[26]*k[0]*k[0]*k[0]*k[1] + (0)*c[26]*k[0]*k[0]*k[0]*k[2] - (0)*c[26]*k[0]*k[0]*k[0] - (0)*c[26]*k[0]*k[0]*k[1]*k[1] - (0)*c[26]*k[0]*k[0]*k[1]*k[2] + (0)*c[26]*k[0]*k[0]*k[1] + (0)*c[26]*k[0]*k[0]*k[2]*k[2] - (0)*c[26]*k[0]*k[0]*k[2] + (0)*c[26]*k[0]*k[0] - (0)*c[26]*k[0]*k[1]*k[1]*k[1] - (0)*c[26]*k[0]*k[1]*k[1]*k[2] + (0)*c[26]*k[0]*k[1]*k[1] - (0)*c[26]*k[0]*k[1]*k[2]*k[2] - 255.999999999986*c[26]*k[0]*k[1]*k[2] - (0)*c[26]*k[0]*k[1] + (0)*c[26]*k[0]*k[2]*k[2]*k[2] - (0)*c[26]*k[0]*k[2]*k[2] + 31.9999999999993*c[26]*k[0]*k[2] + (0)*c[26]*k[0] - (0)*c[26]*k[1]*k[1]*k[1]*k[1] - (0)*c[26]*k[1]*k[1]*k[1]*k[2] + (0)*c[26]*k[1]*k[1]*k[1] - (0)*c[26]*k[1]*k[1]*k[2]*k[2] - 383.999999999989*c[26]*k[1]*k[1]*k[2] - (0)*c[26]*k[1]*k[1] - (0)*c[26]*k[1]*k[2]*k[2]*k[2] - 255.99999999999*c[26]*k[1]*k[2]*k[2] + 319.999999999994*c[26]*k[1]*k[2] + (0)*c[26]*k[1] + (0)*c[26]*k[2]*k[2]*k[2]*k[2] + (0)*c[26]*k[2]*k[2]*k[2] + 31.9999999999992*c[26]*k[2]*k[2] - 31.9999999999995*c[26]*k[2] - (0)*c[26] - (0)*c[27]*k[0]*k[0]*k[0]*k[0] + (0)*c[27]*k[0]*k[0]*k[0]*k[1] - (0)*c[27]*k[0]*k[0]*k[0]*k[2] + (0)*c[27]*k[0]*k[0]*k[0] + (0)*c[27]*k[0]*k[0]*k[1]*k[1] - (0)*c[27]*k[0]*k[0]*k[1]*k[2] - (0)*c[27]*k[0]*k[0]*k[1] + (0)*c[27]*k[0]*k[0]*k[2]*k[2] + (0)*c[27]*k[0]*k[0]*k[2] + (0)*c[27]*k[0]*k[0] + (0)*c[27]*k[0]*k[1]*k[1]*k[1] - (0)*c[27]*k[0]*k[1]*k[1]*k[2] - (0)*c[27]*k[0]*k[1]*k[1] - (0)*c[27]*k[0]*k[1]*k[2]*k[2] + (0)*c[27]*k[0]*k[1]*k[2] + (0)*c[27]*k[0]*k[1] + (0)*c[27]*k[0]*k[2]*k[2]*k[2] - 128.0*c[27]*k[0]*k[2]*k[2] + 32.0*c[27]*k[0]*k[2] - (0)*c[27]*k[0] - (0)*c[27]*k[1]*k[1]*k[1]*k[1] - (0)*c[27]*k[1]*k[1]*k[1]*k[2] + (0)*c[27]*k[1]*k[1]*k[1] + (0)*c[27]*k[1]*k[1]*k[2]*k[2] - (0)*c[27]*k[1]*k[1]*k[2] + (0)*c[27]*k[1]*k[1] + (0)*c[27]*k[1]*k[2]*k[2]*k[2] - 256.000000000001*c[27]*k[1]*k[2]*k[2] + 64.0000000000001*c[27]*k[1]*k[2] - (0)*c[27]*k[1] + (0)*c[27]*k[2]*k[2]*k[2]*k[2] - 128.0*c[27]*k[2]*k[2]*k[2] + 160.0*c[27]*k[2]*k[2] - 32.0*c[27]*k[2] + (0)*c[27] + (0)*c[28]*k[0]*k[0]*k[0]*k[0] + (0)*c[28]*k[0]*k[0]*k[0]*k[1] - (0)*c[28]*k[0]*k[0]*k[0]*k[2] - (0)*c[28]*k[0]*k[0]*k[0] + (0)*c[28]*k[0]*k[0]*k[1]*k[1] + (0)*c[28]*k[0]*k[0]*k[1]*k[2] - (0)*c[28]*k[0]*k[0]*k[1] + (0)*c[28]*k[0]*k[0]*k[2]*k[2] + 255.999999999997*c[28]*k[0]*k[0]*k[2] + (0)*c[28]*k[0]*k[0] + (0)*c[28]*k[0]*k[1]*k[1]*k[1] + (0)*c[28]*k[0]*k[1]*k[1]*k[2] - (0)*c[28]*k[0]*k[1]*k[1] + (0)*c[28]*k[0]*k[1]*k[2]*k[2] + 255.999999999976*c[28]*k[0]*k[1]*k[2] + (0)*c[28]*k[0]*k[1] + (0)*c[28]*k[0]*k[2]*k[2]*k[2] + 255.999999999995*c[28]*k[0]*k[2]*k[2] - 223.999999999996*c[28]*k[0]*k[2] - (0)*c[28]*k[0] + (0)*c[28]*k[1]*k[1]*k[1]*k[1] + (0)*c[28]*k[1]*k[1]*k[1]*k[2] - (0)*c[28]*k[1]*k[1]*k[1] + (0)*c[28]*k[1]*k[1]*k[2]*k[2] - (0)*c[28]*k[1]*k[1]*k[2] + (0)*c[28]*k[1]*k[1] + (0)*c[28]*k[1]*k[2]*k[2]*k[2] - (0)*c[28]*k[1]*k[2]*k[2] + (0)*c[28]*k[1]*k[2] - (0)*c[28]*k[1] - (0)*c[28]*k[2]*k[2]*k[2]*k[2] + (0)*c[28]*k[2]*k[2]*k[2] + (0)*c[28]*k[2]*k[2] - (0)*c[28]*k[2] + (0)*c[28] + (0)*c[29]*k[0]*k[0]*k[0]*k[0] - (0)*c[29]*k[0]*k[0]*k[0]*k[1] - (0)*c[29]*k[0]*k[0]*k[0]*k[2] + (0)*c[29]*k[0]*k[0]*k[0] - (0)*c[29]*k[0]*k[0]*k[1]*k[1] - (0)*c[29]*k[0]*k[0]*k[1]*k[2] + (0)*c[29]*k[0]*k[0]*k[1] - (0)*c[29]*k[0]*k[0]*k[2]*k[2] - 127.999999999994*c[29]*k[0]*k[0]*k[2] - (0)*c[29]*k[0]*k[0] + (0)*c[29]*k[0]*k[1]*k[1]*k[1] - (0)*c[29]*k[0]*k[1]*k[1]*k[2] - (0)*c[29]*k[0]*k[1]*k[1] - (0)*c[29]*k[0]*k[1]*k[2]*k[2] + (0)*c[29]*k[0]*k[1]*k[2] - (0)*c[29]*k[0]*k[1] - (0)*c[29]*k[0]*k[2]*k[2]*k[2] + (0)*c[29]*k[0]*k[2]*k[2] + 31.9999999999978*c[29]*k[0]*k[2] + (0)*c[29]*k[0] + (0)*c[29]*k[1]*k[1]*k[1]*k[1] + (0)*c[29]*k[1]*k[1]*k[1]*k[2] - (0)*c[29]*k[1]*k[1]*k[1] + (0)*c[29]*k[1]*k[1]*k[2]*k[2] - (0)*c[29]*k[1]*k[1]*k[2] + (0)*c[29]*k[1]*k[1] + (0)*c[29]*k[1]*k[2]*k[2]*k[2] - (0)*c[29]*k[1]*k[2]*k[2] + (0)*c[29]*k[1]*k[2] - (0)*c[29]*k[1] + (0)*c[29]*k[2]*k[2]*k[2]*k[2] - (0)*c[29]*k[2]*k[2]*k[2] - (0)*c[29]*k[2]*k[2] + (0)*c[29]*k[2] - (0)*c[29] + (0) + (0) + (0) - (0) + (0) - (0) + (0) + (0) - (0) + (0) + (0) - (0) + (0) - (0) + (0) - (0) + (0) + (0) - (0) + (0) + (0) - (0) + 42.6666666666665*c[2]*k[1]*k[1]*k[1] - (0) + (0) - 48.0*c[2]*k[1]*k[1] - (0) + (0) - (0) + 14.6666666666667*c[2]*k[1] - (0) + (0) - (0) + (0) - 1.00000000000001*c[2] - (0)*c[30]*k[0]*k[0]*k[0]*k[0] + (0)*c[30]*k[0]*k[0]*k[0]*k[1] - (0)*c[30]*k[0]*k[0]*k[0]*k[2] + (0)*c[30]*k[0]*k[0]*k[0] - (0)*c[30]*k[0]*k[0]*k[1]*k[1] - (0)*c[30]*k[0]*k[0]*k[1]*k[2] + (0)*c[30]*k[0]*k[0]*k[1] - (0)*c[30]*k[0]*k[0]*k[2]*k[2] + (0)*c[30]*k[0]*k[0]*k[2] - (0)*c[30]*k[0]*k[0] - (0)*c[30]*k[0]*k[1]*k[1]*k[1] - (0)*c[30]*k[0]*k[1]*k[1]*k[2] + (0)*c[30]*k[0]*k[1]*k[1] - (0)*c[30]*k[0]*k[1]*k[2]*k[2] + (0)*c[30]*k[0]*k[1]*k[2] - (0)*c[30]*k[0]*k[1] - (0)*c[30]*k[0]*k[2]*k[2]*k[2] - 127.999999999997*c[30]*k[0]*k[2]*k[2] + 31.9999999999989*c[30]*k[0]*k[2] + (0)*c[30]*k[0] - (0)*c[30]*k[1]*k[1]*k[1]*k[1] - (0)*c[30]*k[1]*k[1]*k[1]*k[2] + (0)*c[30]*k[1]*k[1]*k[1] + (0)*c[30]*k[1]*k[1]*k[2]*k[2] - (0)*c[30]*k[1]*k[1]*k[2] - (0)*c[30]*k[1]*k[1] + (0)*c[30]*k[1]*k[2]*k[2]*k[2] - (0)*c[30]*k[1]*k[2]*k[2] - (0)*c[30]*k[1]*k[2] + (0)*c[30]*k[1] - (0)*c[30]*k[2]*k[2]*k[2]*k[2] + (0)*c[30]*k[2]*k[2]*k[2] - (0)*c[30]*k[2]*k[2] + (0)*c[30]*k[2] - (0)*c[30] + (0)*c[31]*k[0]*k[0]*k[0]*k[0] - (0)*c[31]*k[0]*k[0]*k[0]*k[1] - (0)*c[31]*k[0]*k[0]*k[0]*k[2] + 128.0*c[31]*k[0]*k[0]*k[0] + (0)*c[31]*k[0]*k[0]*k[1]*k[1] + (0)*c[31]*k[0]*k[0]*k[1]*k[2] + 512.0*c[31]*k[0]*k[0]*k[1] - (0)*c[31]*k[0]*k[0]*k[2]*k[2] + 256.000000000002*c[31]*k[0]*k[0]*k[2] - 224.0*c[31]*k[0]*k[0] + (0)*c[31]*k[0]*k[1]*k[1]*k[1] + (0)*c[31]*k[0]*k[1]*k[1]*k[2] + 383.999999999997*c[31]*k[0]*k[1]*k[1] + (0)*c[31]*k[0]*k[1]*k[2]*k[2] + 511.999999999996*c[31]*k[0]*k[1]*k[2] - 447.999999999999*c[31]*k[0]*k[1] - (0)*c[31]*k[0]*k[2]*k[2]*k[2] + 128.000000000002*c[31]*k[0]*k[2]*k[2] - 224.000000000001*c[31]*k[0]*k[2] + 96.0000000000001*c[31]*k[0] - (0)*c[31]*k[1]*k[1]*k[1]*k[1] + (0)*c[31]*k[1]*k[1]*k[1]*k[2] - (0)*c[31]*k[1]*k[1]*k[1] + (0)*c[31]*k[1]*k[1]*k[2]*k[2] - (0)*c[31]*k[1]*k[1]*k[2] + (0)*c[31]*k[1]*k[1] + (0)*c[31]*k[1]*k[2]*k[2]*k[2] - (0)*c[31]*k[1]*k[2]*k[2] + (0)*c[31]*k[1]*k[2] - (0)*c[31]*k[1] - (0)*c[31]*k[2]*k[2]*k[2]*k[2] - (0)*c[31]*k[2]*k[2]*k[2] + (0)*c[31]*k[2]*k[2] - (0)*c[31]*k[2] - (0)*c[31] - (0)*c[32]*k[0]*k[0]*k[0]*k[0] - (0)*c[32]*k[0]*k[0]*k[0]*k[1] - (0)*c[32]*k[0]*k[0]*k[0]*k[2] - 127.999999999999*c[32]*k[0]*k[0]*k[0] - (0)*c[32]*k[0]*k[0]*k[1]*k[1] + (0)*c[32]*k[0]*k[0]*k[1]*k[2] - 255.999999999998*c[32]*k[0]*k[0]*k[1] - (0)*c[32]*k[0]*k[0]*k[2]*k[2] - 127.999999999999*c[32]*k[0]*k[0]*k[2] + 159.999999999999*c[32]*k[0]*k[0] - (0)*c[32]*k[0]*k[1]*k[1]*k[1] + (0)*c[32]*k[0]*k[1]*k[1]*k[2] + (0)*c[32]*k[0]*k[1]*k[1] + (0)*c[32]*k[0]*k[1]*k[2]*k[2] - (0)*c[32]*k[0]*k[1]*k[2] + 63.9999999999997*c[32]*k[0]*k[1] - (0)*c[32]*k[0]*k[2]*k[2]*k[2] + (0)*c[32]*k[0]*k[2]*k[2] + 31.9999999999998*c[32]*k[0]*k[2] - 31.9999999999999*c[32]*k[0] - (0)*c[32]*k[1]*k[1]*k[1]*k[1] + (0)*c[32]*k[1]*k[1]*k[1]*k[2] + (0)*c[32]*k[1]*k[1]*k[1] + (0)*c[32]*k[1]*k[1]*k[2]*k[2] - (0)*c[32]*k[1]*k[1]*k[2] + (0)*c[32]*k[1]*k[1] + (0)*c[32]*k[1]*k[2]*k[2]*k[2] - (0)*c[32]*k[1]*k[2]*k[2] + (0)*c[32]*k[1]*k[2] - (0)*c[32]*k[1] + (0)*c[32]*k[2]*k[2]*k[2]*k[2] - (0)*c[32]*k[2]*k[2]*k[2] + (0)*c[32]*k[2]*k[2] - (0)*c[32]*k[2] + (0)*c[32] + (0)*c[33]*k[0]*k[0]*k[0]*k[0] + (0)*c[33]*k[0]*k[0]*k[0]*k[1] + (0)*c[33]*k[0]*k[0]*k[0]*k[2] - (0)*c[33]*k[0]*k[0]*k[0] - (0)*c[33]*k[0]*k[0]*k[1]*k[1] - (0)*c[33]*k[0]*k[0]*k[1]*k[2] - 255.999999999999*c[33]*k[0]*k[0]*k[1] + (0)*c[33]*k[0]*k[0]*k[2]*k[2] - (0)*c[33]*k[0]*k[0]*k[2] + 32.0000000000002*c[33]*k[0]*k[0] - (0)*c[33]*k[0]*k[1]*k[1]*k[1] - (0)*c[33]*k[0]*k[1]*k[1]*k[2] - 383.999999999996*c[33]*k[0]*k[1]*k[1] - (0)*c[33]*k[0]*k[1]*k[2]*k[2] - 255.999999999991*c[33]*k[0]*k[1]*k[2] + 319.999999999999*c[33]*k[0]*k[1] + (0)*c[33]*k[0]*k[2]*k[2]*k[2] - (0)*c[33]*k[0]*k[2]*k[2] + 31.9999999999998*c[33]*k[0]*k[2] - 32.0*c[33]*k[0] + (0)*c[33]*k[1]*k[1]*k[1]*k[1] - (0)*c[33]*k[1]*k[1]*k[1]*k[2] - (0)*c[33]*k[1]*k[1]*k[1] - (0)*c[33]*k[1]*k[1]*k[2]*k[2] + (0)*c[33]*k[1]*k[1]*k[2] - (0)*c[33]*k[1]*k[1] - (0)*c[33]*k[1]*k[2]*k[2]*k[2] + (0)*c[33]*k[1]*k[2]*k[2] - (0)*c[33]*k[1]*k[2] + (0)*c[33]*k[1] - (0)*c[33]*k[2]*k[2]*k[2]*k[2] + (0)*c[33]*k[2]*k[2]*k[2] - (0)*c[33]*k[2]*k[2] + (0)*c[33]*k[2] - (0)*c[33] - (0)*c[34]*k[0]*k[0]*k[0]*k[0] - (0)*c[34]*k[0]*k[0]*k[0]*k[1] - (0)*c[34]*k[0]*k[0]*k[0]*k[2] + (0)*c[34]*k[0]*k[0]*k[0] - (0)*c[34]*k[0]*k[0]*k[1]*k[1] - (0)*c[34]*k[0]*k[0]*k[1]*k[2] + (0)*c[34]*k[0]*k[0]*k[1] - (0)*c[34]*k[0]*k[0]*k[2]*k[2] - 255.999999999995*c[34]*k[0]*k[0]*k[2] - (0)*c[34]*k[0]*k[0] - (0)*c[34]*k[0]*k[1]*k[1]*k[1] - (0)*c[34]*k[0]*k[1]*k[1]*k[2] + (0)*c[34]*k[0]*k[1]*k[1] - (0)*c[34]*k[0]*k[1]*k[2]*k[2] - 511.999999999984*c[34]*k[0]*k[1]*k[2] - (0)*c[34]*k[0]*k[1] - (0)*c[34]*k[0]*k[2]*k[2]*k[2] - 255.999999999994*c[34]*k[0]*k[2]*k[2] + 255.999999999996*c[34]*k[0]*k[2] + (0)*c[34]*k[0] - (0)*c[34]*k[1]*k[1]*k[1]*k[1] - (0)*c[34]*k[1]*k[1]*k[1]*k[2] + (0)*c[34]*k[1]*k[1]*k[1] - (0)*c[34]*k[1]*k[1]*k[2]*k[2] + (0)*c[34]*k[1]*k[1]*k[2] - (0)*c[34]*k[1]*k[1] - (0)*c[34]*k[1]*k[2]*k[2]*k[2] + (0)*c[34]*k[1]*k[2]*k[2] - (0)*c[34]*k[1]*k[2] + (0)*c[34]*k[1] + (0)*c[34]*k[2]*k[2]*k[2]*k[2] + (0)*c[34]*k[2]*k[2]*k[2] - (0)*c[34]*k[2]*k[2] + (0)*c[34]*k[2] - (0)*c[34] + (0) + (0) + (0) + (0) - (0) - (0) - (0) + (0) - (0) + (0) - (0) - (0) - (0) - (0) - (0) + (0) + (0) - (0) + (0) - (0) - (0) - (0) - (0) - (0) - (0) + (0) - (0) - (0) + (0) - (0) + (0) - (0) + (0) - (0) + (0) - (0) + (0) - (0) + (0) + (0) + (0) - (0) - (0) + (0) + (0) + (0) + (0) - (0) + (0) - (0) + (0) - (0) + (0) + (0) - (0) + (0) + (0) - (0) + (0) + 127.999999999995*c[4]*k[1]*k[1]*k[2] + (0) + (0) - (0) - 63.9999999999973*c[4]*k[1]*k[2] - (0) - (0) - (0) + (0) + 5.33333333333315*c[4]*k[2] + (0) - (0) - (0) + (0) + (0) - (0) - (0) + (0) + (0) - (0) - (0) - (0) - (0) + (0) - (0) + (0) - (0) + (0) - (0) + (0) - (0) - (0) - (0) + (0) - (0) + (0) - (0) - (0) + 128.000000000002*c[5]*k[1]*k[2]*k[2] - 32.0000000000009*c[5]*k[1]*k[2] + (0) + (0) - (0) - 15.9999999999999*c[5]*k[2]*k[2] + 4.0*c[5]*k[2] - (0) + (0) + (0) - (0) + (0) - (0) - (0) + (0) - (0) + (0) - (0) - (0) - (0) + (0) - (0) + (0) - (0) - (0) + (0) - (0) + (0) + (0) + (0) - (0) + (0) - (0) + (0) + (0) - (0) + (0) - (0) - (0) + 42.6666666666668*c[6]*k[2]*k[2]*k[2] - 32.0000000000001*c[6]*k[2]*k[2] + 5.33333333333338*c[6]*k[2] - (0) - (0) + (0) - (0) + (0) + (0) - (0) - (0) - (0) + (0) - (0) - (0) + (0) - (0) - (0) + (0) + (0) - (0) + (0) - (0) + (0) - (0) - (0) + (0) - (0) + (0) - (0) - (0) + (0) - (0) + (0) + (0) + (0) - (0) + (0) - (0) + (0) + (0) + (0) - (0) + (0) + (0) - (0) + (0) - (0) + (0) + (0) + (0) - (0) + (0) - (0) + (0) + (0) - (0) + (0) - (0) + (0) + (0) - (0) + (0) - (0) + (0) + (0) - (0) + (0) - (0) + (0) - (0) + (0) - (0) + (0) - (0) - (0) - (0) + (0) - (0) - (0) + (0) - (0) + (0) - (0) - (0) - (0) + (0) - (0) + (0) - (0) - (0) + (0) - (0) + (0) + (0) - (0) + (0) - (0) + (0) - (0) - (0) + (0) - (0) + (0) - (0) + (0) - (0) + (0) - (0) + 0;

	H[2] = (0) - (0) - (0) + 42.6666666666667*c[0]*k[0]*k[0]*k[0] + (0) - (0) + 128.0*c[0]*k[0]*k[0]*k[1] - (0) + 128.0*c[0]*k[0]*k[0]*k[2] - 80.0*c[0]*k[0]*k[0] + (0) - (0) + 128.0*c[0]*k[0]*k[1]*k[1] - (0) + 256.0*c[0]*k[0]*k[1]*k[2] - 160.0*c[0]*k[0]*k[1] - (0) + 128.000000000001*c[0]*k[0]*k[2]*k[2] - 160.0*c[0]*k[0]*k[2] + 46.6666666666667*c[0]*k[0] - (0) + (0) + 42.6666666666667*c[0]*k[1]*k[1]*k[1] + (0) + 128.0*c[0]*k[1]*k[1]*k[2] - 80.0*c[0]*k[1]*k[1] + (0) + 128.0*c[0]*k[1]*k[2]*k[2] - 160.0*c[0]*k[1]*k[2] + 46.6666666666667*c[0]*k[1] - (0) + 42.6666666666668*c[0]*k[2]*k[2]*k[2] - 80.0000000000001*c[0]*k[2]*k[2] + 46.6666666666667*c[0]*k[2] - 8.33333333333334*c[0] - (0)*c[10]*k[0]*k[0]*k[0]*k[0] + (0)*c[10]*k[0]*k[0]*k[0]*k[1] - (0)*c[10]*k[0]*k[0]*k[0]*k[2] + (0)*c[10]*k[0]*k[0]*k[0] + (0)*c[10]*k[0]*k[0]*k[1]*k[1] + (0)*c[10]*k[0]*k[0]*k[1]*k[2] - (0)*c[10]*k[0]*k[0]*k[1] + (0)*c[10]*k[0]*k[0]*k[2]*k[2] - (0)*c[10]*k[0]*k[0]*k[2] - (0)*c[10]*k[0]*k[0] - (0)*c[10]*k[0]*k[1]*k[1]*k[1] - (0)*c[10]*k[0]*k[1]*k[1]*k[2] + (0)*c[10]*k[0]*k[1]*k[1] - (0)*c[10]*k[0]*k[1]*k[2]*k[2] + (0)*c[10]*k[0]*k[1]*k[2] + (0)*c[10]*k[0]*k[1] + (0)*c[10]*k[0]*k[2]*k[2]*k[2] - (0)*c[10]*k[0]*k[2]*k[2] + (0)*c[10]*k[0]*k[2] - (0)*c[10]*k[0] - (0)*c[10]*k[1]*k[1]*k[1]*k[1] - (0)*c[10]*k[1]*k[1]*k[1]*k[2] + (0)*c[10]*k[1]*k[1]*k[1] - (0)*c[10]*k[1]*k[1]*k[2]*k[2] + (0)*c[10]*k[1]*k[1]*k[2] + (0)*c[10]*k[1]*k[1] - (0)*c[10]*k[1]*k[2]*k[2]*k[2] + (0)*c[10]*k[1]*k[2]*k[2] - (0)*c[10]*k[1]*k[2] - (0)*c[10]*k[1] + (0)*c[10]*k[2]*k[2]*k[2]*k[2] - (0)*c[10]*k[2]*k[2]*k[2] + (0)*c[10]*k[2]*k[2] - (0)*c[10]*k[2] + (0)*c[10] + (0)*c[11]*k[0]*k[0]*k[0]*k[0] - (0)*c[11]*k[0]*k[0]*k[0]*k[1] + (0)*c[11]*k[0]*k[0]*k[0]*k[2] - (0)*c[11]*k[0]*k[0]*k[0] - (0)*c[11]*k[0]*k[0]*k[1]*k[1] - (0)*c[11]*k[0]*k[0]*k[1]*k[2] + (0)*c[11]*k[0]*k[0]*k[1] + (0)*c[11]*k[0]*k[0]*k[2]*k[2] + (0)*c[11]*k[0]*k[0]*k[2] - (0)*c[11]*k[0]*k[0] - (0)*c[11]*k[0]*k[1]*k[1]*k[1] + (0)*c[11]*k[0]*k[1]*k[1]*k[2] + (0)*c[11]*k[0]*k[1]*k[1] + (0)*c[11]*k[0]*k[1]*k[2]*k[2] + (0)*c[11]*k[0]*k[1]*k[2] - (0)*c[11]*k[0]*k[1] - (0)*c[11]*k[0]*k[2]*k[2]*k[2] + (0)*c[11]*k[0]*k[2]*k[2] - (0)*c[11]*k[0]*k[2] + (0)*c[11]*k[0] - (0)*c[11]*k[1]*k[1]*k[1]*k[1] - (0)*c[11]*k[1]*k[1]*k[1]*k[2] + (0)*c[11]*k[1]*k[1]*k[1] + (0)*c[11]*k[1]*k[1]*k[2]*k[2] + (0)*c[11]*k[1]*k[1]*k[2] - (0)*c[11]*k[1]*k[1] - (0)*c[11]*k[1]*k[2]*k[2]*k[2] + (0)*c[11]*k[1]*k[2]*k[2] - (0)*c[11]*k[1]*k[2] + (0)*c[11]*k[1] - (0)*c[11]*k[2]*k[2]*k[2]*k[2] + (0)*c[11]*k[2]*k[2]*k[2] - (0)*c[11]*k[2]*k[2] + (0)*c[11]*k[2] - (0)*c[11] + (0)*c[12]*k[0]*k[0]*k[0]*k[0] + (0)*c[12]*k[0]*k[0]*k[0]*k[1] + (0)*c[12]*k[0]*k[0]*k[0]*k[2] - (0)*c[12]*k[0]*k[0]*k[0] + (0)*c[12]*k[0]*k[0]*k[1]*k[1] - (0)*c[12]*k[0]*k[0]*k[1]*k[2] - (0)*c[12]*k[0]*k[0]*k[1] - (0)*c[12]*k[0]*k[0]*k[2]*k[2] + (0)*c[12]*k[0]*k[0]*k[2] + (0)*c[12]*k[0]*k[0] + (0)*c[12]*k[0]*k[1]*k[1]*k[1] + (0)*c[12]*k[0]*k[1]*k[1]*k[2] - (0)*c[12]*k[0]*k[1]*k[1] - (0)*c[12]*k[0]*k[1]*k[2]*k[2] - (0)*c[12]*k[0]*k[1]*k[2] + (0)*c[12]*k[0]*k[1] - (0)*c[12]*k[0]*k[2]*k[2]*k[2] + (0)*c[12]*k[0]*k[2]*k[2] - (0)*c[12]*k[0]*k[2] - (0)*c[12]*k[0] + (0)*c[12]*k[1]*k[1]*k[1]*k[1] + (0)*c[12]*k[1]*k[1]*k[1]*k[2] - (0)*c[12]*k[1]*k[1]*k[1] + (0)*c[12]*k[1]*k[1]*k[2]*k[2] - (0)*c[12]*k[1]*k[1]*k[2] + (0)*c[12]*k[1]*k[1] + (0)*c[12]*k[1]*k[2]*k[2]*k[2] - (0)*c[12]*k[1]*k[2]*k[2] + (0)*c[12]*k[1]*k[2] - (0)*c[12]*k[1] + (0)*c[12]*k[2]*k[2]*k[2]*k[2] - (0)*c[12]*k[2]*k[2]*k[2] + (0)*c[12]*k[2]*k[2] - (0)*c[12]*k[2] + (0)*c[12] - (0)*c[13]*k[0]*k[0]*k[0]*k[0] + (0)*c[13]*k[0]*k[0]*k[0]*k[1] + (0)*c[13]*k[0]*k[0]*k[0]*k[2] - 42.6666666666667*c[13]*k[0]*k[0]*k[0] + (0)*c[13]*k[0]*k[0]*k[1]*k[1] + (0)*c[13]*k[0]*k[0]*k[1]*k[2] - 128.0*c[13]*k[0]*k[0]*k[1] + (0)*c[13]*k[0]*k[0]*k[2]*k[2] - 256.000000000002*c[13]*k[0]*k[0]*k[2] + 96.0000000000002*c[13]*k[0]*k[0] + (0)*c[13]*k[0]*k[1]*k[1]*k[1] + (0)*c[13]*k[0]*k[1]*k[1]*k[2] - 128.0*c[13]*k[0]*k[1]*k[1] + (0)*c[13]*k[0]*k[1]*k[2]*k[2] - 512.000000000003*c[13]*k[0]*k[1]*k[2] + 192.0*c[13]*k[0]*k[1] + (0)*c[13]*k[0]*k[2]*k[2]*k[2] - 384.000000000002*c[13]*k[0]*k[2]*k[2] + 384.000000000001*c[13]*k[0]*k[2] - 69.3333333333334*c[13]*k[0] - (0)*c[13]*k[1]*k[1]*k[1]*k[1] - (0)*c[13]*k[1]*k[1]*k[1]*k[2] - 42.6666666666664*c[13]*k[1]*k[1]*k[1] - (0)*c[13]*k[1]*k[1]*k[2]*k[2] - 255.999999999999*c[13]*k[1]*k[1]*k[2] + 95.9999999999999*c[13]*k[1]*k[1] + (0)*c[13]*k[1]*k[2]*k[2]*k[2] - 384.0*c[13]*k[1]*k[2]*k[2] + 384.0*c[13]*k[1]*k[2] - 69.3333333333333*c[13]*k[1] + (0)*c[13]*k[2]*k[2]*k[2]*k[2] - 170.666666666667*c[13]*k[2]*k[2]*k[2] + 288.0*c[13]*k[2]*k[2] - 138.666666666667*c[13]*k[2] + 16.0*c[13] + (0)*c[14]*k[0]*k[0]*k[0]*k[0] + (0)*c[14]*k[0]*k[0]*k[0]*k[1] - (0)*c[14]*k[0]*k[0]*k[0]*k[2] - (0)*c[14]*k[0]*k[0]*k[0] - (0)*c[14]*k[0]*k[0]*k[1]*k[1] - (0)*c[14]*k[0]*k[0]*k[1]*k[2] + (0)*c[14]*k[0]*k[0]*k[1] - (0)*c[14]*k[0]*k[0]*k[2]*k[2] + 128.000000000001*c[14]*k[0]*k[0]*k[2] - 16.0000000000001*c[14]*k[0]*k[0] - (0)*c[14]*k[0]*k[1]*k[1]*k[1] - (0)*c[14]*k[0]*k[1]*k[1]*k[2] + (0)*c[14]*k[0]*k[1]*k[1] - (0)*c[14]*k[0]*k[1]*k[2]*k[2] + 256.000000000007*c[14]*k[0]*k[1]*k[2] - 32.0000000000008*c[14]*k[0]*k[1] - (0)*c[14]*k[0]*k[2]*k[2]*k[2] + 384.000000000002*c[14]*k[0]*k[2]*k[2] - 288.000000000001*c[14]*k[0]*k[2] + 28.0000000000001*c[14]*k[0] + (0)*c[14]*k[1]*k[1]*k[1]*k[1] - (0)*c[14]*k[1]*k[1]*k[1]*k[2] + (0)*c[14]*k[1]*k[1]*k[1] - (0)*c[14]*k[1]*k[1]*k[2]*k[2] + 128.000000000002*c[14]*k[1]*k[1]*k[2] - 16.0000000000002*c[14]*k[1]*k[1] - (0)*c[14]*k[1]*k[2]*k[2]*k[2] + 384.000000000002*c[14]*k[1]*k[2]*k[2] - 288.000000000001*c[14]*k[1]*k[2] + 28.0000000000001*c[14]*k[1] - (0)*c[14]*k[2]*k[2]*k[2]*k[2] + 256.0*c[14]*k[2]*k[2]*k[2] - 384.0*c[14]*k[2]*k[2] + 152.0*c[14]*k[2] - 12.0*c[14] + (0)*c[15]*k[0]*k[0]*k[0]*k[0] - (0)*c[15]*k[0]*k[0]*k[0]*k[1] - (0)*c[15]*k[0]*k[0]*k[0]*k[2] + (0)*c[15]*k[0]*k[0]*k[0] + (0)*c[15]*k[0]*k[0]*k[1]*k[1] + (0)*c[15]*k[0]*k[0]*k[1]*k[2] - (0)*c[15]*k[0]*k[0]*k[1] - (0)*c[15]*k[0]*k[0]*k[2]*k[2] + (0)*c[15]*k[0]*k[0]*k[2] - (0)*c[15]*k[0]*k[0] + (0)*c[15]*k[0]*k[1]*k[1]*k[1] + (0)*c[15]*k[0]*k[1]*k[1]*k[2] - (0)*c[15]*k[0]*k[1]*k[1] + (0)*c[15]*k[0]*k[1]*k[2]*k[2] - (0)*c[15]*k[0]*k[1]*k[2] + (0)*c[15]*k[0]*k[1] + (0)*c[15]*k[0]*k[2]*k[2]*k[2] - 128.000000000001*c[15]*k[0]*k[2]*k[2] + 64.0000000000004*c[15]*k[0]*k[2] - 5.33333333333337*c[15]*k[0] + (0)*c[15]*k[1]*k[1]*k[1]*k[1] + (0)*c[15]*k[1]*k[1]*k[1]*k[2] - (0)*c[15]*k[1]*k[1]*k[1] + (0)*c[15]*k[1]*k[1]*k[2]*k[2] - (0)*c[15]*k[1]*k[1]*k[2] + (0)*c[15]*k[1]*k[1] + (0)*c[15]*k[1]*k[2]*k[2]*k[2] - 128.000000000002*c[15]*k[1]*k[2]*k[2] + 64.0000000000013*c[15]*k[1]*k[2] - 5.33333333333345*c[15]*k[1] - (0)*c[15]*k[2]*k[2]*k[2]*k[2] - 170.666666666667*c[15]*k[2]*k[2]*k[2] + 224.0*c[15]*k[2]*k[2] - 74.6666666666667*c[15]*k[2] + 5.33333333333333*c[15] - (0)*c[16]*k[0]*k[0]*k[0]*k[0] - (0)*c[16]*k[0]*k[0]*k[0]*k[1] + (0)*c[16]*k[0]*k[0]*k[0]*k[2] + (0)*c[16]*k[0]*k[0]*k[0] - (0)*c[16]*k[0]*k[0]*k[1]*k[1] - (0)*c[16]*k[0]*k[0]*k[1]*k[2] - 127.999999999999*c[16]*k[0]*k[0]*k[1] + (0)*c[16]*k[0]*k[0]*k[2]*k[2] - (0)*c[16]*k[0]*k[0]*k[2] - (0)*c[16]*k[0]*k[0] - (0)*c[16]*k[0]*k[1]*k[1]*k[1] - (0)*c[16]*k[0]*k[1]*k[1]*k[2] - 255.999999999999*c[16]*k[0]*k[1]*k[1] - (0)*c[16]*k[0]*k[1]*k[2]*k[2] - 255.999999999999*c[16]*k[0]*k[1]*k[2] + 192.0*c[16]*k[0]*k[1] + (0)*c[16]*k[0]*k[2]*k[2]*k[2] - (0)*c[16]*k[0]*k[2]*k[2] + (0)*c[16]*k[0]*k[2] + (0)*c[16]*k[0] - (0)*c[16]*k[1]*k[1]*k[1]*k[1] - (0)*c[16]*k[1]*k[1]*k[1]*k[2] - 128.0*c[16]*k[1]*k[1]*k[1] - (0)*c[16]*k[1]*k[1]*k[2]*k[2] - 255.999999999998*c[16]*k[1]*k[1]*k[2] + 192.0*c[16]*k[1]*k[1] - (0)*c[16]*k[1]*k[2]*k[2]*k[2] - 127.999999999999*c[16]*k[1]*k[2]*k[2] + 191.999999999999*c[16]*k[1]*k[2] - 69.3333333333332*c[16]*k[1] + (0)*c[16]*k[2]*k[2]*k[2]*k[2] - (0)*c[16]*k[2]*k[2]*k[2] + (0)*c[16]*k[2]*k[2] + (0)*c[16]*k[2] - (0)*c[16] + (0)*c[17]*k[0]*k[0]*k[0]*k[0] + (0)*c[17]*k[0]*k[0]*k[0]*k[1] - (0)*c[17]*k[0]*k[0]*k[0]*k[2] - (0)*c[17]*k[0]*k[0]*k[0] + (0)*c[17]*k[0]*k[0]*k[1]*k[1] - (0)*c[17]*k[0]*k[0]*k[1]*k[2] - (0)*c[17]*k[0]*k[0]*k[1] - (0)*c[17]*k[0]*k[0]*k[2]*k[2] + (0)*c[17]*k[0]*k[0]*k[2] + (0)*c[17]*k[0]*k[0] + (0)*c[17]*k[0]*k[1]*k[1]*k[1] - (0)*c[17]*k[0]*k[1]*k[1]*k[2] + 127.999999999999*c[17]*k[0]*k[1]*k[1] - (0)*c[17]*k[0]*k[1]*k[2]*k[2] + (0)*c[17]*k[0]*k[1]*k[2] - 31.9999999999995*c[17]*k[0]*k[1] - (0)*c[17]*k[0]*k[2]*k[2]*k[2] + (0)*c[17]*k[0]*k[2]*k[2] - (0)*c[17]*k[0]*k[2] - (0)*c[17]*k[0] - (0)*c[17]*k[1]*k[1]*k[1]*k[1] + (0)*c[17]*k[1]*k[1]*k[1]*k[2] + 128.0*c[17]*k[1]*k[1]*k[1] + (0)*c[17]*k[1]*k[1]*k[2]*k[2] + 127.999999999999*c[17]*k[1]*k[1]*k[2] - 144.0*c[17]*k[1]*k[1] + (0)*c[17]*k[1]*k[2]*k[2]*k[2] - (0)*c[17]*k[1]*k[2]*k[2] - 31.9999999999997*c[17]*k[1]*k[2] + 27.9999999999999*c[17]*k[1] + (0)*c[17]*k[2]*k[2]*k[2]*k[2] + (0)*c[17]*k[2]*k[2]*k[2] - (0)*c[17]*k[2]*k[2] - (0)*c[17]*k[2] + (0)*c[17] - (0)*c[18]*k[0]*k[0]*k[0]*k[0] - (0)*c[18]*k[0]*k[0]*k[0]*k[1] + (0)*c[18]*k[0]*k[0]*k[0]*k[2] + (0)*c[18]*k[0]*k[0]*k[0] - (0)*c[18]*k[0]*k[0]*k[1]*k[1] + (0)*c[18]*k[0]*k[0]*k[1]*k[2] + (0)*c[18]*k[0]*k[0]*k[1] + (0)*c[18]*k[0]*k[0]*k[2]*k[2] - (0)*c[18]*k[0]*k[0]*k[2] - (0)*c[18]*k[0]*k[0] - (0)*c[18]*k[0]*k[1]*k[1]*k[1] + (0)*c[18]*k[0]*k[1]*k[1]*k[2] + (0)*c[18]*k[0]*k[1]*k[1] + (0)*c[18]*k[0]*k[1]*k[2]*k[2] - (0)*c[18]*k[0]*k[1]*k[2] - (0)*c[18]*k[0]*k[1] + (0)*c[18]*k[0]*k[2]*k[2]*k[2] - (0)*c[18]*k[0]*k[2]*k[2] + (0)*c[18]*k[0]*k[2] + (0)*c[18]*k[0] - (0)*c[18]*k[1]*k[1]*k[1]*k[1] + (0)*c[18]*k[1]*k[1]*k[1]*k[2] - 42.6666666666663*c[18]*k[1]*k[1]*k[1] + (0)*c[18]*k[1]*k[1]*k[2]*k[2] - (0)*c[18]*k[1]*k[1]*k[2] + 31.9999999999996*c[18]*k[1]*k[1] + (0)*c[18]*k[1]*k[2]*k[2]*k[2] - (0)*c[18]*k[1]*k[2]*k[2] + (0)*c[18]*k[1]*k[2] - 5.3333333333332*c[18]*k[1] + (0)*c[18]*k[2]*k[2]*k[2]*k[2] - (0)*c[18]*k[2]*k[2]*k[2] + (0)*c[18]*k[2]*k[2] - (0)*c[18]*k[2] - (0)*c[18] - (0)*c[19]*k[0]*k[0]*k[0]*k[0] - (0)*c[19]*k[0]*k[0]*k[0]*k[1] + (0)*c[19]*k[0]*k[0]*k[0]*k[2] - 128.0*c[19]*k[0]*k[0]*k[0] - (0)*c[19]*k[0]*k[0]*k[1]*k[1] + (0)*c[19]*k[0]*k[0]*k[1]*k[2] - 256.0*c[19]*k[0]*k[0]*k[1] + (0)*c[19]*k[0]*k[0]*k[2]*k[2] - 256.000000000001*c[19]*k[0]*k[0]*k[2] + 192.0*c[19]*k[0]*k[0] - (0)*c[19]*k[0]*k[1]*k[1]*k[1] + (0)*c[19]*k[0]*k[1]*k[1]*k[2] - 128.0*c[19]*k[0]*k[1]*k[1] + (0)*c[19]*k[0]*k[1]*k[2]*k[2] - 256.000000000001*c[19]*k[0]*k[1]*k[2] + 192.0*c[19]*k[0]*k[1] + (0)*c[19]*k[0]*k[2]*k[2]*k[2] - 128.000000000002*c[19]*k[0]*k[2]*k[2] + 192.000000000001*c[19]*k[0]*k[2] - 69.3333333333335*c[19]*k[0] + (0)*c[19]*k[1]*k[1]*k[1]*k[1] - (0)*c[19]*k[1]*k[1]*k[1]*k[2] + (0)*c[19]*k[1]*k[1]*k[1] - (0)*c[19]*k[1]*k[1]*k[2]*k[2] + (0)*c[19]*k[1]*k[1]*k[2] - (0)*c[19]*k[1]*k[1] + (0)*c[19]*k[1]*k[2]*k[2]*k[2] + (0)*c[19]*k[1]*k[2]*k[2] - (0)*c[19]*k[1]*k[2] - (0)*c[19]*k[1] + (0)*c[19]*k[2]*k[2]*k[2]*k[2] - (0)*c[19]*k[2]*k[2]*k[2] + (0)*c[19]*k[2]*k[2] - (0)*c[19]*k[2] + (0)*c[19] - (0) - (0) - (0) + (0) + (0) + (0) + (0) + (0) + (0) - (0) + (0) + (0) - (0) + (0) - (0) + (0) + (0) - (0) + (0) + (0) + (0) + (0) - (0) + (0) - (0) + (0) + (0) - (0) + (0) - (0) + (0) - (0) + (0) - (0) + (0) + (0)*c[20]*k[0]*k[0]*k[0]*k[0] + (0)*c[20]*k[0]*k[0]*k[0]*k[1] + (0)*c[20]*k[0]*k[0]*k[0]*k[2] + 127.999999999999*c[20]*k[0]*k[0]*k[0] + (0)*c[20]*k[0]*k[0]*k[1]*k[1] + (0)*c[20]*k[0]*k[0]*k[1]*k[2] + 127.999999999998*c[20]*k[0]*k[0]*k[1] + (0)*c[20]*k[0]*k[0]*k[2]*k[2] + 127.999999999997*c[20]*k[0]*k[0]*k[2] - 143.999999999999*c[20]*k[0]*k[0] + (0)*c[20]*k[0]*k[1]*k[1]*k[1] - (0)*c[20]*k[0]*k[1]*k[1]*k[2] - (0)*c[20]*k[0]*k[1]*k[1] - (0)*c[20]*k[0]*k[1]*k[2]*k[2] + (0)*c[20]*k[0]*k[1]*k[2] - 31.9999999999996*c[20]*k[0]*k[1] + (0)*c[20]*k[0]*k[2]*k[2]*k[2] - (0)*c[20]*k[0]*k[2]*k[2] - 31.9999999999995*c[20]*k[0]*k[2] + 27.9999999999999*c[20]*k[0] + (0)*c[20]*k[1]*k[1]*k[1]*k[1] + (0)*c[20]*k[1]*k[1]*k[1]*k[2] - (0)*c[20]*k[1]*k[1]*k[1] - (0)*c[20]*k[1]*k[1]*k[2]*k[2] + (0)*c[20]*k[1]*k[1]*k[2] + (0)*c[20]*k[1]*k[1] - (0)*c[20]*k[1]*k[2]*k[2]*k[2] + (0)*c[20]*k[1]*k[2]*k[2] - (0)*c[20]*k[1]*k[2] + (0)*c[20]*k[1] - (0)*c[20]*k[2]*k[2]*k[2]*k[2] + (0)*c[20]*k[2]*k[2]*k[2] - (0)*c[20]*k[2]*k[2] + (0)*c[20]*k[2] - (0)*c[20] - (0)*c[21]*k[0]*k[0]*k[0]*k[0] - (0)*c[21]*k[0]*k[0]*k[0]*k[1] - (0)*c[21]*k[0]*k[0]*k[0]*k[2] - 42.6666666666662*c[21]*k[0]*k[0]*k[0] - (0)*c[21]*k[0]*k[0]*k[1]*k[1] + (0)*c[21]*k[0]*k[0]*k[1]*k[2] + (0)*c[21]*k[0]*k[0]*k[1] - (0)*c[21]*k[0]*k[0]*k[2]*k[2] + (0)*c[21]*k[0]*k[0]*k[2] + 31.9999999999997*c[21]*k[0]*k[0] - (0)*c[21]*k[0]*k[1]*k[1]*k[1] + (0)*c[21]*k[0]*k[1]*k[1]*k[2] + (0)*c[21]*k[0]*k[1]*k[1] + (0)*c[21]*k[0]*k[1]*k[2]*k[2] - (0)*c[21]*k[0]*k[1]*k[2] - (0)*c[21]*k[0]*k[1] + (0)*c[21]*k[0]*k[2]*k[2]*k[2] - (0)*c[21]*k[0]*k[2]*k[2] + (0)*c[21]*k[0]*k[2] - 5.3333333333333*c[21]*k[0] + (0)*c[21]*k[1]*k[1]*k[1]*k[1] + (0)*c[21]*k[1]*k[1]*k[1]*k[2] - (0)*c[21]*k[1]*k[1]*k[1] + (0)*c[21]*k[1]*k[1]*k[2]*k[2] - (0)*c[21]*k[1]*k[1]*k[2] + (0)*c[21]*k[1]*k[1] + (0)*c[21]*k[1]*k[2]*k[2]*k[2] - (0)*c[21]*k[1]*k[2]*k[2] + (0)*c[21]*k[1]*k[2] - (0)*c[21]*k[1] + (0)*c[21]*k[2]*k[2]*k[2]*k[2] - (0)*c[21]*k[2]*k[2]*k[2] + (0)*c[21]*k[2]*k[2] - (0)*c[21]*k[2] + (0)*c[21] + (0)*c[22]*k[0]*k[0]*k[0]*k[0] + (0)*c[22]*k[0]*k[0]*k[0]*k[1] + (0)*c[22]*k[0]*k[0]*k[0]*k[2] - (0)*c[22]*k[0]*k[0]*k[0] - (0)*c[22]*k[0]*k[0]*k[1]*k[1] + (0)*c[22]*k[0]*k[0]*k[1]*k[2] + 127.999999999999*c[22]*k[0]*k[0]*k[1] + (0)*c[22]*k[0]*k[0]*k[2]*k[2] - (0)*c[22]*k[0]*k[0]*k[2] + (0)*c[22]*k[0]*k[0] - (0)*c[22]*k[0]*k[1]*k[1]*k[1] - (0)*c[22]*k[0]*k[1]*k[1]*k[2] + (0)*c[22]*k[0]*k[1]*k[1] - (0)*c[22]*k[0]*k[1]*k[2]*k[2] + (0)*c[22]*k[0]*k[1]*k[2] - 32.0000000000001*c[22]*k[0]*k[1] - (0)*c[22]*k[0]*k[2]*k[2]*k[2] - (0)*c[22]*k[0]*k[2]*k[2] + (0)*c[22]*k[0]*k[2] - (0)*c[22]*k[0] - (0)*c[22]*k[1]*k[1]*k[1]*k[1] - (0)*c[22]*k[1]*k[1]*k[1]*k[2] + (0)*c[22]*k[1]*k[1]*k[1] - (0)*c[22]*k[1]*k[1]*k[2]*k[2] + (0)*c[22]*k[1]*k[1]*k[2] - (0)*c[22]*k[1]*k[1] - (0)*c[22]*k[1]*k[2]*k[2]*k[2] + (0)*c[22]*k[1]*k[2]*k[2] - (0)*c[22]*k[1]*k[2] + (0)*c[22]*k[1] - (0)*c[22]*k[2]*k[2]*k[2]*k[2] + (0)*c[22]*k[2]*k[2]*k[2] - (0)*c[22]*k[2]*k[2] + (0)*c[22]*k[2] - (0)*c[22] - (0)*c[23]*k[0]*k[0]*k[0]*k[0] + (0)*c[23]*k[0]*k[0]*k[0]*k[1] - (0)*c[23]*k[0]*k[0]*k[0]*k[2] - (0)*c[23]*k[0]*k[0]*k[0] + (0)*c[23]*k[0]*k[0]*k[1]*k[1] + (0)*c[23]*k[0]*k[0]*k[1]*k[2] - (0)*c[23]*k[0]*k[0]*k[1] - (0)*c[23]*k[0]*k[0]*k[2]*k[2] + (0)*c[23]*k[0]*k[0]*k[2] + (0)*c[23]*k[0]*k[0] + (0)*c[23]*k[0]*k[1]*k[1]*k[1] + (0)*c[23]*k[0]*k[1]*k[1]*k[2] + 127.999999999998*c[23]*k[0]*k[1]*k[1] + (0)*c[23]*k[0]*k[1]*k[2]*k[2] - (0)*c[23]*k[0]*k[1]*k[2] - 31.9999999999985*c[23]*k[0]*k[1] + (0)*c[23]*k[0]*k[2]*k[2]*k[2] - (0)*c[23]*k[0]*k[2]*k[2] + (0)*c[23]*k[0]*k[2] - (0)*c[23]*k[0] - (0)*c[23]*k[1]*k[1]*k[1]*k[1] - (0)*c[23]*k[1]*k[1]*k[1]*k[2] + (0)*c[23]*k[1]*k[1]*k[1] - (0)*c[23]*k[1]*k[1]*k[2]*k[2] + (0)*c[23]*k[1]*k[1]*k[2] + (0)*c[23]*k[1]*k[1] + (0)*c[23]*k[1]*k[2]*k[2]*k[2] - (0)*c[23]*k[1]*k[2]*k[2] + (0)*c[23]*k[1]*k[2] - (0)*c[23]*k[1] - (0)*c[23]*k[2]*k[2]*k[2]*k[2] + (0)*c[23]*k[2]*k[2]*k[2] + (0)*c[23]*k[2]*k[2] - (0)*c[23]*k[2] + (0)*c[23] - (0)*c[24]*k[0]*k[0]*k[0]*k[0] - (0)*c[24]*k[0]*k[0]*k[0]*k[1] + (0)*c[24]*k[0]*k[0]*k[0]*k[2] - (0)*c[24]*k[0]*k[0]*k[0] + (0)*c[24]*k[0]*k[0]*k[1]*k[1] - (0)*c[24]*k[0]*k[0]*k[1]*k[2] - (0)*c[24]*k[0]*k[0]*k[1] + (0)*c[24]*k[0]*k[0]*k[2]*k[2] - (0)*c[24]*k[0]*k[0]*k[2] + (0)*c[24]*k[0]*k[0] + (0)*c[24]*k[0]*k[1]*k[1]*k[1] - (0)*c[24]*k[0]*k[1]*k[1]*k[2] + (0)*c[24]*k[0]*k[1]*k[1] - (0)*c[24]*k[0]*k[1]*k[2]*k[2] + 256.000000000005*c[24]*k[0]*k[1]*k[2] - 32.0000000000004*c[24]*k[0]*k[1] + (0)*c[24]*k[0]*k[2]*k[2]*k[2] - (0)*c[24]*k[0]*k[2]*k[2] + (0)*c[24]*k[0]*k[2] - (0)*c[24]*k[0] + (0)*c[24]*k[1]*k[1]*k[1]*k[1] - (0)*c[24]*k[1]*k[1]*k[1]*k[2] + (0)*c[24]*k[1]*k[1]*k[1] - (0)*c[24]*k[1]*k[1]*k[2]*k[2] + (0)*c[24]*k[1]*k[1]*k[2] - (0)*c[24]*k[1]*k[1] - (0)*c[24]*k[1]*k[2]*k[2]*k[2] + (0)*c[24]*k[1]*k[2]*k[2] - (0)*c[24]*k[1]*k[2] + (0)*c[24]*k[1] + (0)*c[24]*k[2]*k[2]*k[2]*k[2] - (0)*c[24]*k[2]*k[2]*k[2] + (0)*c[24]*k[2]*k[2] - (0)*c[24]*k[2] + (0)*c[24] + (0)*c[25]*k[0]*k[0]*k[0]*k[0] - (0)*c[25]*k[0]*k[0]*k[0]*k[1] - (0)*c[25]*k[0]*k[0]*k[0]*k[2] + (0)*c[25]*k[0]*k[0]*k[0] + (0)*c[25]*k[0]*k[0]*k[1]*k[1] + (0)*c[25]*k[0]*k[0]*k[1]*k[2] + 127.999999999999*c[25]*k[0]*k[0]*k[1] - (0)*c[25]*k[0]*k[0]*k[2]*k[2] + (0)*c[25]*k[0]*k[0]*k[2] - (0)*c[25]*k[0]*k[0] + (0)*c[25]*k[0]*k[1]*k[1]*k[1] + (0)*c[25]*k[0]*k[1]*k[1]*k[2] + 255.999999999998*c[25]*k[0]*k[1]*k[1] + (0)*c[25]*k[0]*k[1]*k[2]*k[2] + 511.999999999987*c[25]*k[0]*k[1]*k[2] - 223.999999999998*c[25]*k[0]*k[1] - (0)*c[25]*k[0]*k[2]*k[2]*k[2] + (0)*c[25]*k[0]*k[2]*k[2] + (0)*c[25]*k[0]*k[2] - (0)*c[25]*k[0] + (0)*c[25]*k[1]*k[1]*k[1]*k[1] + (0)*c[25]*k[1]*k[1]*k[1]*k[2] + 127.999999999999*c[25]*k[1]*k[1]*k[1] + (0)*c[25]*k[1]*k[1]*k[2]*k[2] + 511.99999999999*c[25]*k[1]*k[1]*k[2] - 223.999999999999*c[25]*k[1]*k[1] + (0)*c[25]*k[1]*k[2]*k[2]*k[2] + 383.999999999992*c[25]*k[1]*k[2]*k[2] - 447.999999999995*c[25]*k[1]*k[2] + 95.9999999999994*c[25]*k[1] - (0)*c[25]*k[2]*k[2]*k[2]*k[2] + (0)*c[25]*k[2]*k[2]*k[2] + (0)*c[25]*k[2]*k[2] - (0)*c[25]*k[2] + (0)*c[25] - (0)*c[26]*k[0]*k[0]*k[0]*k[0] - (0)*c[26]*k[0]*k[0]*k[0]*k[1] - (0)*c[26]*k[0]*k[0]*k[0]*k[2] + (0)*c[26]*k[0]*k[0]*k[0] - (0)*c[26]*k[0]*k[0]*k[1]*k[1] - (0)*c[26]*k[0]*k[0]*k[1]*k[2] + (0)*c[26]*k[0]*k[0]*k[1] + (0)*c[26]*k[0]*k[0]*k[2]*k[2] + (0)*c[26]*k[0]*k[0]*k[2] - (0)*c[26]*k[0]*k[0] - (0)*c[26]*k[0]*k[1]*k[1]*k[1] - (0)*c[26]*k[0]*k[1]*k[1]*k[2] - 127.999999999999*c[26]*k[0]*k[1]*k[1] - (0)*c[26]*k[0]*k[1]*k[2]*k[2] + (0)*c[26]*k[0]*k[1]*k[2] + 31.9999999999991*c[26]*k[0]*k[1] - (0)*c[26]*k[0]*k[2]*k[2]*k[2] + (0)*c[26]*k[0]*k[2]*k[2] - (0)*c[26]*k[0]*k[2] + (0)*c[26]*k[0] + (0)*c[26]*k[1]*k[1]*k[1]*k[1] - (0)*c[26]*k[1]*k[1]*k[1]*k[2] - 128.0*c[26]*k[1]*k[1]*k[1] - (0)*c[26]*k[1]*k[1]*k[2]*k[2] - 255.999999999997*c[26]*k[1]*k[1]*k[2] + 160.0*c[26]*k[1]*k[1] - (0)*c[26]*k[1]*k[2]*k[2]*k[2] + (0)*c[26]*k[1]*k[2]*k[2] + 63.9999999999982*c[26]*k[1]*k[2] - 31.9999999999998*c[26]*k[1] - (0)*c[26]*k[2]*k[2]*k[2]*k[2] + (0)*c[26]*k[2]*k[2]*k[2] - (0)*c[26]*k[2]*k[2] + (0)*c[26]*k[2] - (0)*c[26] + (0)*c[27]*k[0]*k[0]*k[0]*k[0] + (0)*c[27]*k[0]*k[0]*k[0]*k[1] + (0)*c[27]*k[0]*k[0]*k[0]*k[2] - (0)*c[27]*k[0]*k[0]*k[0] + (0)*c[27]*k[0]*k[0]*k[1]*k[1] - (0)*c[27]*k[0]*k[0]*k[1]*k[2] - (0)*c[27]*k[0]*k[0]*k[1] + (0)*c[27]*k[0]*k[0]*k[2]*k[2] - (0)*c[27]*k[0]*k[0]*k[2] + (0)*c[27]*k[0]*k[0] + (0)*c[27]*k[0]*k[1]*k[1]*k[1] - (0)*c[27]*k[0]*k[1]*k[1]*k[2] + (0)*c[27]*k[0]*k[1]*k[1] - (0)*c[27]*k[0]*k[1]*k[2]*k[2] - 255.999999999988*c[27]*k[0]*k[1]*k[2] + 31.999999999999*c[27]*k[0]*k[1] + (0)*c[27]*k[0]*k[2]*k[2]*k[2] - (0)*c[27]*k[0]*k[2]*k[2] + (0)*c[27]*k[0]*k[2] - (0)*c[27]*k[0] - (0)*c[27]*k[1]*k[1]*k[1]*k[1] - (0)*c[27]*k[1]*k[1]*k[1]*k[2] + (0)*c[27]*k[1]*k[1]*k[1] - (0)*c[27]*k[1]*k[1]*k[2]*k[2] - 255.999999999993*c[27]*k[1]*k[1]*k[2] + 31.999999999999*c[27]*k[1]*k[1] - (0)*c[27]*k[1]*k[2]*k[2]*k[2] - 383.999999999994*c[27]*k[1]*k[2]*k[2] + 319.999999999996*c[27]*k[1]*k[2] - 31.9999999999996*c[27]*k[1] + (0)*c[27]*k[2]*k[2]*k[2]*k[2] - (0)*c[27]*k[2]*k[2]*k[2] + (0)*c[27]*k[2]*k[2] + (0)*c[27]*k[2] - (0)*c[27] + (0)*c[28]*k[0]*k[0]*k[0]*k[0] - (0)*c[28]*k[0]*k[0]*k[0]*k[1] - (0)*c[28]*k[0]*k[0]*k[0]*k[2] + 128.0*c[28]*k[0]*k[0]*k[0] + (0)*c[28]*k[0]*k[0]*k[1]*k[1] + (0)*c[28]*k[0]*k[0]*k[1]*k[2] + 255.999999999999*c[28]*k[0]*k[0]*k[1] - (0)*c[28]*k[0]*k[0]*k[2]*k[2] + 512.000000000003*c[28]*k[0]*k[0]*k[2] - 224.0*c[28]*k[0]*k[0] + (0)*c[28]*k[0]*k[1]*k[1]*k[1] + (0)*c[28]*k[0]*k[1]*k[1]*k[2] + 127.999999999998*c[28]*k[0]*k[1]*k[1] + (0)*c[28]*k[0]*k[1]*k[2]*k[2] + 511.99999999999*c[28]*k[0]*k[1]*k[2] - 223.999999999999*c[28]*k[0]*k[1] - (0)*c[28]*k[0]*k[2]*k[2]*k[2] + 384.000000000002*c[28]*k[0]*k[2]*k[2] - 448.000000000001*c[28]*k[0]*k[2] + 96.0000000000001*c[28]*k[0] + (0)*c[28]*k[1]*k[1]*k[1]*k[1] + (0)*c[28]*k[1]*k[1]*k[1]*k[2] - (0)*c[28]*k[1]*k[1]*k[1] + (0)*c[28]*k[1]*k[1]*k[2]*k[2] - (0)*c[28]*k[1]*k[1]*k[2] + (0)*c[28]*k[1]*k[1] + (0)*c[28]*k[1]*k[2]*k[2]*k[2] - (0)*c[28]*k[1]*k[2]*k[2] + (0)*c[28]*k[1]*k[2] - (0)*c[28]*k[1] - (0)*c[28]*k[2]*k[2]*k[2]*k[2] + (0)*c[28]*k[2]*k[2]*k[2] - (0)*c[28]*k[2]*k[2] - (0)*c[28]*k[2] + (0)*c[28] - (0)*c[29]*k[0]*k[0]*k[0]*k[0] - (0)*c[29]*k[0]*k[0]*k[0]*k[1] - (0)*c[29]*k[0]*k[0]*k[0]*k[2] - 127.999999999999*c[29]*k[0]*k[0]*k[0] - (0)*c[29]*k[0]*k[0]*k[1]*k[1] - (0)*c[29]*k[0]*k[0]*k[1]*k[2] - 127.999999999998*c[29]*k[0]*k[0]*k[1] - (0)*c[29]*k[0]*k[0]*k[2]*k[2] - 255.999999999994*c[29]*k[0]*k[0]*k[2] + 159.999999999999*c[29]*k[0]*k[0] - (0)*c[29]*k[0]*k[1]*k[1]*k[1] - (0)*c[29]*k[0]*k[1]*k[1]*k[2] + (0)*c[29]*k[0]*k[1]*k[1] - (0)*c[29]*k[0]*k[1]*k[2]*k[2] + (0)*c[29]*k[0]*k[1]*k[2] + 31.9999999999992*c[29]*k[0]*k[1] - (0)*c[29]*k[0]*k[2]*k[2]*k[2] + (0)*c[29]*k[0]*k[2]*k[2] + 63.9999999999979*c[29]*k[0]*k[2] - 31.9999999999998*c[29]*k[0] + (0)*c[29]*k[1]*k[1]*k[1]*k[1] + (0)*c[29]*k[1]*k[1]*k[1]*k[2] - (0)*c[29]*k[1]*k[1]*k[1] + (0)*c[29]*k[1]*k[1]*k[2]*k[2] - (0)*c[29]*k[1]*k[1]*k[2] + (0)*c[29]*k[1]*k[1] + (0)*c[29]*k[1]*k[2]*k[2]*k[2] - (0)*c[29]*k[1]*k[2]*k[2] + (0)*c[29]*k[1]*k[2] - (0)*c[29]*k[1] + (0)*c[29]*k[2]*k[2]*k[2]*k[2] - (0)*c[29]*k[2]*k[2]*k[2] + (0)*c[29]*k[2]*k[2] + (0)*c[29]*k[2] + (0)*c[29] + (0) + (0) + (0) - (0) - (0) - (0) + (0) - (0) - (0) + (0) - (0) - (0) + (0) - (0) + (0) + (0) - (0) + (0) + (0) - (0) - (0) - (0) + (0) - (0) + (0) + (0) - (0) + (0) - (0) - (0) - (0) + (0) - (0) + (0) + (0) - (0)*c[30]*k[0]*k[0]*k[0]*k[0] - (0)*c[30]*k[0]*k[0]*k[0]*k[1] + (0)*c[30]*k[0]*k[0]*k[0]*k[2] - (0)*c[30]*k[0]*k[0]*k[0] - (0)*c[30]*k[0]*k[0]*k[1]*k[1] - (0)*c[30]*k[0]*k[0]*k[1]*k[2] + (0)*c[30]*k[0]*k[0]*k[1] + (0)*c[30]*k[0]*k[0]*k[2]*k[2] - 256.000000000005*c[30]*k[0]*k[0]*k[2] + 32.0000000000004*c[30]*k[0]*k[0] - (0)*c[30]*k[0]*k[1]*k[1]*k[1] - (0)*c[30]*k[0]*k[1]*k[1]*k[2] + (0)*c[30]*k[0]*k[1]*k[1] - (0)*c[30]*k[0]*k[1]*k[2]*k[2] - 255.999999999988*c[30]*k[0]*k[1]*k[2] + 31.9999999999984*c[30]*k[0]*k[1] + (0)*c[30]*k[0]*k[2]*k[2]*k[2] - 384.000000000002*c[30]*k[0]*k[2]*k[2] + 320.000000000001*c[30]*k[0]*k[2] - 32.0*c[30]*k[0] - (0)*c[30]*k[1]*k[1]*k[1]*k[1] - (0)*c[30]*k[1]*k[1]*k[1]*k[2] + (0)*c[30]*k[1]*k[1]*k[1] - (0)*c[30]*k[1]*k[1]*k[2]*k[2] + (0)*c[30]*k[1]*k[1]*k[2] - (0)*c[30]*k[1]*k[1] - (0)*c[30]*k[1]*k[2]*k[2]*k[2] + (0)*c[30]*k[1]*k[2]*k[2] - (0)*c[30]*k[1]*k[2] + (0)*c[30]*k[1] + (0)*c[30]*k[2]*k[2]*k[2]*k[2] - (0)*c[30]*k[2]*k[2]*k[2] - (0)*c[30]*k[2]*k[2] + (0)*c[30]*k[2] - (0)*c[30] + (0)*c[31]*k[0]*k[0]*k[0]*k[0] + (0)*c[31]*k[0]*k[0]*k[0]*k[1] + (0)*c[31]*k[0]*k[0]*k[0]*k[2] - (0)*c[31]*k[0]*k[0]*k[0] + (0)*c[31]*k[0]*k[0]*k[1]*k[1] + (0)*c[31]*k[0]*k[0]*k[1]*k[2] + 255.999999999996*c[31]*k[0]*k[0]*k[1] + (0)*c[31]*k[0]*k[0]*k[2]*k[2] - (0)*c[31]*k[0]*k[0]*k[2] + (0)*c[31]*k[0]*k[0] + (0)*c[31]*k[0]*k[1]*k[1]*k[1] + (0)*c[31]*k[0]*k[1]*k[1]*k[2] + 255.999999999996*c[31]*k[0]*k[1]*k[1] + (0)*c[31]*k[0]*k[1]*k[2]*k[2] + 255.999999999981*c[31]*k[0]*k[1]*k[2] - 223.999999999997*c[31]*k[0]*k[1] + (0)*c[31]*k[0]*k[2]*k[2]*k[2] - (0)*c[31]*k[0]*k[2]*k[2] + (0)*c[31]*k[0]*k[2] - (0)*c[31]*k[0] - (0)*c[31]*k[1]*k[1]*k[1]*k[1] + (0)*c[31]*k[1]*k[1]*k[1]*k[2] - (0)*c[31]*k[1]*k[1]*k[1] + (0)*c[31]*k[1]*k[1]*k[2]*k[2] - (0)*c[31]*k[1]*k[1]*k[2] + (0)*c[31]*k[1]*k[1] + (0)*c[31]*k[1]*k[2]*k[2]*k[2] - (0)*c[31]*k[1]*k[2]*k[2] + (0)*c[31]*k[1]*k[2] - (0)*c[31]*k[1] - (0)*c[31]*k[2]*k[2]*k[2]*k[2] - (0)*c[31]*k[2]*k[2]*k[2] + (0)*c[31]*k[2]*k[2] - (0)*c[31]*k[2] + (0)*c[31] + (0)*c[32]*k[0]*k[0]*k[0]*k[0] - (0)*c[32]*k[0]*k[0]*k[0]*k[1] - (0)*c[32]*k[0]*k[0]*k[0]*k[2] + (0)*c[32]*k[0]*k[0]*k[0] + (0)*c[32]*k[0]*k[0]*k[1]*k[1] - (0)*c[32]*k[0]*k[0]*k[1]*k[2] - 127.999999999999*c[32]*k[0]*k[0]*k[1] - (0)*c[32]*k[0]*k[0]*k[2]*k[2] + (0)*c[32]*k[0]*k[0]*k[2] - (0)*c[32]*k[0]*k[0] + (0)*c[32]*k[0]*k[1]*k[1]*k[1] + (0)*c[32]*k[0]*k[1]*k[1]*k[2] - (0)*c[32]*k[0]*k[1]*k[1] + (0)*c[32]*k[0]*k[1]*k[2]*k[2] - (0)*c[32]*k[0]*k[1]*k[2] + 32.0000000000006*c[32]*k[0]*k[1] - (0)*c[32]*k[0]*k[2]*k[2]*k[2] + (0)*c[32]*k[0]*k[2]*k[2] - (0)*c[32]*k[0]*k[2] + (0)*c[32]*k[0] + (0)*c[32]*k[1]*k[1]*k[1]*k[1] + (0)*c[32]*k[1]*k[1]*k[1]*k[2] - (0)*c[32]*k[1]*k[1]*k[1] + (0)*c[32]*k[1]*k[1]*k[2]*k[2] - (0)*c[32]*k[1]*k[1]*k[2] + (0)*c[32]*k[1]*k[1] + (0)*c[32]*k[1]*k[2]*k[2]*k[2] - (0)*c[32]*k[1]*k[2]*k[2] + (0)*c[32]*k[1]*k[2] - (0)*c[32]*k[1] + (0)*c[32]*k[2]*k[2]*k[2]*k[2] - (0)*c[32]*k[2]*k[2]*k[2] + (0)*c[32]*k[2]*k[2] - (0)*c[32]*k[2] + (0)*c[32] + (0)*c[33]*k[0]*k[0]*k[0]*k[0] - (0)*c[33]*k[0]*k[0]*k[0]*k[1] + (0)*c[33]*k[0]*k[0]*k[0]*k[2] + (0)*c[33]*k[0]*k[0]*k[0] - (0)*c[33]*k[0]*k[0]*k[1]*k[1] - (0)*c[33]*k[0]*k[0]*k[1]*k[2] + (0)*c[33]*k[0]*k[0]*k[1] + (0)*c[33]*k[0]*k[0]*k[2]*k[2] - (0)*c[33]*k[0]*k[0]*k[2] - (0)*c[33]*k[0]*k[0] - (0)*c[33]*k[0]*k[1]*k[1]*k[1] - (0)*c[33]*k[0]*k[1]*k[1]*k[2] - 127.999999999997*c[33]*k[0]*k[1]*k[1] - (0)*c[33]*k[0]*k[1]*k[2]*k[2] + (0)*c[33]*k[0]*k[1]*k[2] + 31.9999999999984*c[33]*k[0]*k[1] + (0)*c[33]*k[0]*k[2]*k[2]*k[2] - (0)*c[33]*k[0]*k[2]*k[2] - (0)*c[33]*k[0]*k[2] + (0)*c[33]*k[0] - (0)*c[33]*k[1]*k[1]*k[1]*k[1] - (0)*c[33]*k[1]*k[1]*k[1]*k[2] + (0)*c[33]*k[1]*k[1]*k[1] - (0)*c[33]*k[1]*k[1]*k[2]*k[2] + (0)*c[33]*k[1]*k[1]*k[2] - (0)*c[33]*k[1]*k[1] - (0)*c[33]*k[1]*k[2]*k[2]*k[2] + (0)*c[33]*k[1]*k[2]*k[2] - (0)*c[33]*k[1]*k[2] + (0)*c[33]*k[1] + (0)*c[33]*k[2]*k[2]*k[2]*k[2] - (0)*c[33]*k[2]*k[2]*k[2] + (0)*c[33]*k[2]*k[2] - (0)*c[33]*k[2] - (0)*c[33] + (0)*c[34]*k[0]*k[0]*k[0]*k[0] - (0)*c[34]*k[0]*k[0]*k[0]*k[1] - (0)*c[34]*k[0]*k[0]*k[0]*k[2] + (0)*c[34]*k[0]*k[0]*k[0] - (0)*c[34]*k[0]*k[0]*k[1]*k[1] - (0)*c[34]*k[0]*k[0]*k[1]*k[2] - 255.999999999996*c[34]*k[0]*k[0]*k[1] - (0)*c[34]*k[0]*k[0]*k[2]*k[2] + (0)*c[34]*k[0]*k[0]*k[2] - (0)*c[34]*k[0]*k[0] - (0)*c[34]*k[0]*k[1]*k[1]*k[1] - (0)*c[34]*k[0]*k[1]*k[1]*k[2] - 255.999999999996*c[34]*k[0]*k[1]*k[1] - (0)*c[34]*k[0]*k[1]*k[2]*k[2] - 511.999999999988*c[34]*k[0]*k[1]*k[2] + 255.999999999997*c[34]*k[0]*k[1] - (0)*c[34]*k[0]*k[2]*k[2]*k[2] + (0)*c[34]*k[0]*k[2]*k[2] - (0)*c[34]*k[0]*k[2] + (0)*c[34]*k[0] - (0)*c[34]*k[1]*k[1]*k[1]*k[1] + (0)*c[34]*k[1]*k[1]*k[1]*k[2] + (0)*c[34]*k[1]*k[1]*k[1] + (0)*c[34]*k[1]*k[1]*k[2]*k[2] - (0)*c[34]*k[1]*k[1]*k[2] - (0)*c[34]*k[1]*k[1] - (0)*c[34]*k[1]*k[2]*k[2]*k[2] + (0)*c[34]*k[1]*k[2]*k[2] - (0)*c[34]*k[1]*k[2] + (0)*c[34]*k[1] - (0)*c[34]*k[2]*k[2]*k[2]*k[2] + (0)*c[34]*k[2]*k[2]*k[2] - (0)*c[34]*k[2]*k[2] + (0)*c[34]*k[2] - (0)*c[34] + (0) + (0) + (0) - (0) - (0) - (0) + (0) + (0) - (0) + (0) - (0) - (0) + (0) - (0) + (0) - (0) + (0) - (0) + (0) + (0) + (0) - (0) - (0) - (0) + (0) - (0) - (0) + (0) - (0) + (0) + (0) + 42.6666666666664*c[3]*k[2]*k[2]*k[2] - 47.9999999999999*c[3]*k[2]*k[2] + 14.6666666666667*c[3]*k[2] - 1.0*c[3] + (0) + (0) - (0) - (0) + (0) - (0) - (0) - (0) + (0) + (0) + (0) + (0) - (0) - (0) + (0) + (0) - (0) + (0) - (0) - (0) + (0) - (0) + 42.6666666666663*c[4]*k[1]*k[1]*k[1] - (0) + (0) - 31.9999999999999*c[4]*k[1]*k[1] - (0) + (0) - (0) + 5.33333333333332*c[4]*k[1] - (0) + (0) - (0) - (0) + (0) + (0) - (0) + (0) - (0) - (0) + (0) - (0) + (0) - (0) + (0) - (0) + (0) - (0) + (0) - (0) + (0) + (0) - (0) + (0) - (0) + (0) + (0) - (0) + (0) + 127.999999999997*c[5]*k[1]*k[1]*k[2] - 15.9999999999995*c[5]*k[1]*k[1] + (0) - (0) - 31.9999999999987*c[5]*k[1]*k[2] + 3.99999999999986*c[5]*k[1] - (0) - (0) + (0) - (0) + (0) + (0) - (0) - (0) + (0) + (0) - (0) + (0) - (0) + (0) - (0) - (0) - (0) + (0) + (0) + (0) - (0) - (0) + (0) - (0) + (0) + (0) - (0) - (0) - (0) + (0) - (0) - (0) + 128.0*c[6]*k[1]*k[2]*k[2] - 64.0*c[6]*k[1]*k[2] + 5.33333333333331*c[6]*k[1] - (0) + (0) - (0) + (0) + (0) + (0) + (0) + (0) + 42.6666666666664*c[7]*k[0]*k[0]*k[0] + (0) - (0) - (0) + (0) - (0) - 31.9999999999998*c[7]*k[0]*k[0] - (0) - (0) + (0) - (0) + (0) - (0) - (0) + (0) - (0) + 5.33333333333334*c[7]*k[0] - (0) - (0) + (0) - (0) + (0) - (0) - (0) + (0) - (0) + (0) + (0) + (0) - (0) + (0) - (0) + (0) - (0) + (0) - (0) - (0) + (0) - (0) + (0) + 127.999999999996*c[8]*k[0]*k[0]*k[2] - 15.9999999999996*c[8]*k[0]*k[0] - (0) + (0) - (0) + (0) - (0) + (0) + (0) - (0) - 31.999999999998*c[8]*k[0]*k[2] + 3.99999999999981*c[8]*k[0] + (0) - (0) - (0) + (0) - (0) + (0) - (0) - (0) + (0) - (0) + (0) - (0) + (0) - (0) + (0) - (0) + (0) - (0) + (0) + (0) - (0) - (0) - (0) + (0) - (0) + (0) + (0) - (0) + (0) - (0) + (0) - (0) + 128.000000000002*c[9]*k[0]*k[2]*k[2] - 64.000000000001*c[9]*k[0]*k[2] + 5.33333333333341*c[9]*k[0] - (0) + (0) - (0) + (0) - (0) + (0) + (0) - (0) + (0) - (0) - (0) + (0) - (0) + (0) - (0) + 0;

	return(0);
}

inline double *makeTransformHelp_UnitCubeMesh_P_4(double** C, double* k, const double *modOff, double result[2]){

	result[0] = 0-modOff[0] + (C[3][0])*(1.0*k[2] + 0) + (C[2][0])*(1.0*k[1] - (0) + 0) + (C[1][0])*(1.0*k[0] + 0) + (C[0][0])*(-1.0*k[0] - 1.0*k[1] - 1.0*k[2] + 1.0 + 0);

	result[1] = 0-modOff[1] + (C[3][1])*(1.0*k[2] + 0) + (C[2][1])*(1.0*k[1] - (0) + 0) + (C[1][1])*(1.0*k[0] + 0) + (C[0][1])*(-1.0*k[0] - 1.0*k[1] - 1.0*k[2] + 1.0 + 0);

	result[2] = 0-modOff[2] + (C[3][2])*(1.0*k[2] + 0) + (C[2][2])*(1.0*k[1] - (0) + 0) + (C[1][2])*(1.0*k[0] + 0) + (C[0][2])*(-1.0*k[0] - 1.0*k[1] - 1.0*k[2] + 1.0 + 0);

	return(result);
}
double * makeTransform_UnitCubeMesh_P_4(double * k, int cell, MappTy nM, FloatMapTy pM ){

	double *C[3] = {0,0,0};

	getPoints(cell,nM,pM,C);

	double random[3] = { 0.0 };

	double result[3] = { 0.0 };

	return(makeTransformHelp_UnitCubeMesh_P_4(C,k,random,result));
}
inline double ** helpMakeJacobian_UnitCubeMesh_P_4(double ** C, double *k, double * J[3]){

	J[0][0] = (C[0][0] * ((0) - (0) - (0) - 1.0 + 0)) + (C[1][0] * ((0) + (0) + (0) + 1.0 + 0)) + (C[2][0] * (0 + 0)) + (C[3][0] * (0 + 0)) + 0;

	J[0][1] = (C[0][0] * ((0) - (0) - (0) - 1.0 + 0)) + (C[1][0] * ((0) - (0) + (0) - (0) + 0)) + (C[2][0] * ((0) + (0) + (0) + 1.0 + 0)) + (C[3][0] * (0 + 0)) + 0;

	J[0][2] = (C[0][0] * ((0) - (0) - (0) - 1.0 + 0)) + (C[1][0] * ((0) - (0) + (0) - (0) + 0)) + (C[2][0] * ((0) - (0) - (0) + (0) + 0)) + (C[3][0] * ((0) + (0) - (0) + 1.0 + 0)) + 0;

	J[1][0] = (C[0][1] * ((0) - (0) - (0) - 1.0 + 0)) + (C[1][1] * ((0) + (0) + (0) + 1.0 + 0)) + (C[2][1] * (0 + 0)) + (C[3][1] * (0 + 0)) + 0;

	J[1][1] = (C[0][1] * ((0) - (0) - (0) - 1.0 + 0)) + (C[1][1] * ((0) - (0) + (0) - (0) + 0)) + (C[2][1] * ((0) + (0) + (0) + 1.0 + 0)) + (C[3][1] * (0 + 0)) + 0;

	J[1][2] = (C[0][1] * ((0) - (0) - (0) - 1.0 + 0)) + (C[1][1] * ((0) - (0) + (0) - (0) + 0)) + (C[2][1] * ((0) - (0) - (0) + (0) + 0)) + (C[3][1] * ((0) + (0) - (0) + 1.0 + 0)) + 0;

	J[2][0] = (C[0][2] * ((0) - (0) - (0) - 1.0 + 0)) + (C[1][2] * ((0) + (0) + (0) + 1.0 + 0)) + (C[2][2] * (0 + 0)) + (C[3][2] * (0 + 0)) + 0;

	J[2][1] = (C[0][2] * ((0) - (0) - (0) - 1.0 + 0)) + (C[1][2] * ((0) - (0) + (0) - (0) + 0)) + (C[2][2] * ((0) + (0) + (0) + 1.0 + 0)) + (C[3][2] * (0 + 0)) + 0;

	J[2][2] = (C[0][2] * ((0) - (0) - (0) - 1.0 + 0)) + (C[1][2] * ((0) - (0) + (0) - (0) + 0)) + (C[2][2] * ((0) - (0) - (0) + (0) + 0)) + (C[3][2] * ((0) + (0) - (0) + 1.0 + 0)) + 0;

	return(J);
}
double ** makeJacobian_UnitCubeMesh_P_4(int cell, MappTy nM, FloatMapTy pM, double *k, double * J[3]){

	double *C[3];

	getPoints(cell,nM,pM,C);

	return(helpMakeJacobian_UnitCubeMesh_P_4(C,k,J));
}
inline double ** helpInverseJacobian_UnitCubeMesh_P_4(double ** C, double *k, double * J[3]){

	double t11 = (C[0][0] * ((0) - (0) - (0) - 1.0 + 0)) + (C[1][0] * ((0) + (0) + (0) + 1.0 + 0)) + (C[2][0] * (0 + 0)) + (C[3][0] * (0 + 0)) + 0;

	double t12 = (C[0][0] * ((0) - (0) - (0) - 1.0 + 0)) + (C[1][0] * ((0) - (0) + (0) - (0) + 0)) + (C[2][0] * ((0) + (0) + (0) + 1.0 + 0)) + (C[3][0] * (0 + 0)) + 0;

	double t13 = (C[0][0] * ((0) - (0) - (0) - 1.0 + 0)) + (C[1][0] * ((0) - (0) + (0) - (0) + 0)) + (C[2][0] * ((0) - (0) - (0) + (0) + 0)) + (C[3][0] * ((0) + (0) - (0) + 1.0 + 0)) + 0;

	double t21 = (C[0][1] * ((0) - (0) - (0) - 1.0 + 0)) + (C[1][1] * ((0) + (0) + (0) + 1.0 + 0)) + (C[2][1] * (0 + 0)) + (C[3][1] * (0 + 0)) + 0;

	double t22 = (C[0][1] * ((0) - (0) - (0) - 1.0 + 0)) + (C[1][1] * ((0) - (0) + (0) - (0) + 0)) + (C[2][1] * ((0) + (0) + (0) + 1.0 + 0)) + (C[3][1] * (0 + 0)) + 0;

	double t23 = (C[0][1] * ((0) - (0) - (0) - 1.0 + 0)) + (C[1][1] * ((0) - (0) + (0) - (0) + 0)) + (C[2][1] * ((0) - (0) - (0) + (0) + 0)) + (C[3][1] * ((0) + (0) - (0) + 1.0 + 0)) + 0;

	double t31 = (C[0][2] * ((0) - (0) - (0) - 1.0 + 0)) + (C[1][2] * ((0) + (0) + (0) + 1.0 + 0)) + (C[2][2] * (0 + 0)) + (C[3][2] * (0 + 0)) + 0;

	double t32 = (C[0][2] * ((0) - (0) - (0) - 1.0 + 0)) + (C[1][2] * ((0) - (0) + (0) - (0) + 0)) + (C[2][2] * ((0) + (0) + (0) + 1.0 + 0)) + (C[3][2] * (0 + 0)) + 0;

	double t33 = (C[0][2] * ((0) - (0) - (0) - 1.0 + 0)) + (C[1][2] * ((0) - (0) + (0) - (0) + 0)) + (C[2][2] * ((0) - (0) - (0) + (0) + 0)) + (C[3][2] * ((0) + (0) - (0) + 1.0 + 0)) + 0;

	double det = 1.0/(t11*t22*t33 +  t21*t32*t13 + t31*t12*t23 - t11*t32*t23 - t31*t22*t13 - t21*t12*t33);

	J[0][0] = det*(t22*t33-t23*t32);

	J[0][1] = det*(t13*t32-t12*t33);

	J[0][2] = det*(t12*t23-t13*t22);

	J[1][0] = det*(t23*t31-t21*t33);

	J[1][1] = det*(t11*t33-t13*t31);

	J[1][2] = det*(t13*t21-t11*t23);

	J[2][0] = det*(t21*t32-t22*t31);

	J[2][1] = det*(t12*t31-t11*t32);

	J[2][2] = det*(t11*t22-t12*t21);

	return(0);
}
double ** makeJacobianInverse_UnitCubeMesh_P_4(int cell, MappTy nM, FloatMapTy pM, double *k,double * J[3]){

	double *C[3];

	getPoints(cell,nM,pM,C);

	return(helpInverseJacobian_UnitCubeMesh_P_4(C,k,J));
}
inline void *helpJIs_UnitCubeMesh_P_4(double **C,double J[3][3]){

	double k[3];

	k[0] = 0.25;

	k[1] = 0.25;

	k[2] = 0.25;

	double t11 = (C[0][0] * ((0) - (0) - (0) - 1.0 + 0)) + (C[1][0] * ((0) + (0) + (0) + 1.0 + 0)) + (C[2][0] * (0 + 0)) + (C[3][0] * (0 + 0)) + 0;

	double t12 = (C[0][0] * ((0) - (0) - (0) - 1.0 + 0)) + (C[1][0] * ((0) - (0) + (0) - (0) + 0)) + (C[2][0] * ((0) + (0) + (0) + 1.0 + 0)) + (C[3][0] * (0 + 0)) + 0;

	double t13 = (C[0][0] * ((0) - (0) - (0) - 1.0 + 0)) + (C[1][0] * ((0) - (0) + (0) - (0) + 0)) + (C[2][0] * ((0) - (0) - (0) + (0) + 0)) + (C[3][0] * ((0) + (0) - (0) + 1.0 + 0)) + 0;

	double t21 = (C[0][1] * ((0) - (0) - (0) - 1.0 + 0)) + (C[1][1] * ((0) + (0) + (0) + 1.0 + 0)) + (C[2][1] * (0 + 0)) + (C[3][1] * (0 + 0)) + 0;

	double t22 = (C[0][1] * ((0) - (0) - (0) - 1.0 + 0)) + (C[1][1] * ((0) - (0) + (0) - (0) + 0)) + (C[2][1] * ((0) + (0) + (0) + 1.0 + 0)) + (C[3][1] * (0 + 0)) + 0;

	double t23 = (C[0][1] * ((0) - (0) - (0) - 1.0 + 0)) + (C[1][1] * ((0) - (0) + (0) - (0) + 0)) + (C[2][1] * ((0) - (0) - (0) + (0) + 0)) + (C[3][1] * ((0) + (0) - (0) + 1.0 + 0)) + 0;

	double t31 = (C[0][2] * ((0) - (0) - (0) - 1.0 + 0)) + (C[1][2] * ((0) + (0) + (0) + 1.0 + 0)) + (C[2][2] * (0 + 0)) + (C[3][2] * (0 + 0)) + 0;

	double t32 = (C[0][2] * ((0) - (0) - (0) - 1.0 + 0)) + (C[1][2] * ((0) - (0) + (0) - (0) + 0)) + (C[2][2] * ((0) + (0) + (0) + 1.0 + 0)) + (C[3][2] * (0 + 0)) + 0;

	double t33 = (C[0][2] * ((0) - (0) - (0) - 1.0 + 0)) + (C[1][2] * ((0) - (0) + (0) - (0) + 0)) + (C[2][2] * ((0) - (0) - (0) + (0) + 0)) + (C[3][2] * ((0) + (0) - (0) + 1.0 + 0)) + 0;

	double det = 1.0/(t11*t22*t33 +  t21*t32*t13 + t31*t12*t23 - t11*t32*t23 - t31*t22*t13 - t21*t12*t33);

	J[0][0] = det*(t22*t33-t23*t32);

	J[0][1] = det*(t13*t32-t12*t33);

	J[0][2] = det*(t12*t23-t13*t22);

	J[1][0] = det*(t23*t31-t21*t33);

	J[1][1] = det*(t11*t33-t13*t31);

	J[1][2] = det*(t13*t21-t11*t23);

	J[2][0] = det*(t21*t32-t22*t31);

	J[2][1] = det*(t12*t31-t11*t32);

	J[2][2] = det*(t11*t22-t12*t21);

	return(0);
}
inline void *jIs_UnitCubeMesh_P_4(double J[3][3],MappTy nM, FloatMapTy pM,int cell){

	double *C[4] = {0,0,0,0};

	getPoints(cell,nM,pM,C);

	helpJIs_UnitCubeMesh_P_4(C,J);
	return(0);}
inline double * helpTranslateCoordinates_UnitCubeMesh_P_4(double **C, const  double * x0, int itter, double newpos[3]){

	 newpos[0] = 0.25;

	 newpos[1] = 0.25;

	 newpos[2] = 0.25;

	bool notConverged =true;

	int i = 0;
	double change[3] = {0.0 };

	double * temp;
	double random[3] = { 0.0 };
	double J[3][3] = {{0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f}};

	helpJIs_UnitCubeMesh_P_4(C,J);

	while ((i < itter) && notConverged){

		temp = makeTransformHelp_UnitCubeMesh_P_4(C,newpos, x0,random);

		change[0]=(J[0][0] * temp[0]) + (J[0][1] * temp[1]) + (J[0][2] * temp[2]) + 0;

		change[1]=(J[1][0] * temp[0]) + (J[1][1] * temp[1]) + (J[1][2] * temp[2]) + 0;

		change[2]=(J[2][0] * temp[0]) + (J[2][1] * temp[1]) + (J[2][2] * temp[2]) + 0;

		double test = (change[0] * change[0]) + (change[1] * change[1]) + (change[2] * change[2]) + 0;

		if(test < 1e-12*1e-12){notConverged=false;}

		newpos[0] -=change[0];

		newpos[1] -=change[1];

		newpos[2] -=change[2];

		i+=1;
}

	return(newpos);
}

void *affineDerv_UnitCubeMesh_P_4_1(int cell, NodeTy nodes, newposTy b, coordTy c, MappTy nM, FloatMapTy pM,double H [3],int start,int mult){

	double J[3][3] = {{0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f}};

	jIs_UnitCubeMesh_P_4(J,nM,pM,cell);
	double Phi[3];
	double array[35] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

	brevTy weights = ProbeNodeC(nodes,c,array,start,mult);
	makePhiDerv_UnitCubeMesh_P_4_1(Phi,b,weights.data);

	H[0] = Phi[0]*J[0][0]+Phi[1]*J[1][0]+Phi[2]*J[2][0];

	H[1] = Phi[0]*J[0][1]+Phi[1]*J[1][1]+Phi[2]*J[2][1];

	H[2] = Phi[0]*J[0][2]+Phi[1]*J[1][2]+Phi[2]*J[2][2];

	return(0);
}
observ::tensor_ref_3 s_makeEval_UnitCubeMesh_P_4_1(NodeTy nodes, newposTy b, coordTy c,int cell,MappTy nM, FloatMapTy pM,int start,int mult ){

	double H1[3];
 
	affineDerv_UnitCubeMesh_P_4_1(cell,nodes,b,c,nM,pM,H1,start,mult);
	delete(b);
	return(observ::tensor_ref_3((double*) H1));
}observ::tensor_ref_3_3 s_3makeEval_UnitCubeMesh_P_4_1(NodeTy nodes, newposTy b, coordTy c,int cell,MappTy nM, FloatMapTy pM ){

	double* P = new double[9];
	double (&H)[3][3] = *reinterpret_cast<double (*)[3][3]>(P);
	double const * H0 = s_makeEval_UnitCubeMesh_P_4_1(nodes, b, c , cell, nM, pM,0, 3)._data;
	H[0][0] = H0[0];
	H[0][1] = H0[1];
	H[0][2] = H0[2];
	double const * H1 = s_makeEval_UnitCubeMesh_P_4_1(nodes, b, c , cell, nM, pM,1, 3)._data;
	H[1][0] = H1[0];
	H[1][1] = H1[1];
	H[1][2] = H1[2];
	double const * H2 = s_makeEval_UnitCubeMesh_P_4_1(nodes, b, c , cell, nM, pM,2, 3)._data;
	H[2][0] = H2[0];
	H[2][1] = H2[1];
	H[2][2] = H2[2];
	return(observ::tensor_ref_3_3((double*) H));
}
fcTy wrapcell_UnitCubeMesh_P_4 (const double* vp,  int32_t vL, MappTy nM, FloatMapTy pM, optStruct opt)
	{
	int32_t * tracker = opt.tracker;
 if(*tracker > vL || *tracker < 0)
	{*tracker=0;}
;

	
	int range = 1;
	double *C[4] = {0,0,0,0};

	double * newposAllocate = new double[3]();
	int lastCell = *opt.tracker;

	int32_t * nbrs = &opt.Nbrs[vL*lastCell];

	for (int cellIndex = 0;  cellIndex < vL;  cellIndex+=1) {
		int32_t cell = nbrs[cellIndex];

		getPoints(cell,nM,pM,C);

		newposTy newpos = helpTranslateCoordinates_UnitCubeMesh_P_4(C,vp,range,newposAllocate);
		bool test = (newpos[0] + 1.0e-14 >= 0) && (newpos[1] + 1.0e-14 >= 0) && (newpos[2] + 1.0e-14 >= 0) && (newpos[0] + newpos[1] + newpos[2] - 1.0e-14 <= 1);

			if(test){*tracker=cell;return {cell,newpos};}
		}
	for (int cell = 0;  cell < vL;  cell+=1) {
		getPoints(cell,nM,pM,C);

		newposTy newpos = helpTranslateCoordinates_UnitCubeMesh_P_4(C,vp,range,newposAllocate);
		bool test = (newpos[0] + 1.0e-14 >= 0) && (newpos[1] + 1.0e-14 >= 0) && (newpos[2] + 1.0e-14 >= 0) && (newpos[0] + newpos[1] + newpos[2] - 1.0e-14 <= 1);

			if(test){*tracker=cell;return {cell,newpos};}
		}
		return {-1,NULL};
	}
 bool checkCell(fcTy cellinfo){return (cellinfo.cell>=0);}
inline vec3 vcons3 (double r0, double r1, double r2)
{
    return __extension__ (vec3){r0, r1, r2, 0.0};
}
inline void vpack3 (tensor_3 &dst, vec3 v0)
{
    dst._data[0] = v0[0];
    dst._data[1] = v0[1];
    dst._data[2] = v0[2];
}
// ***** End synthesized operations *****

extern "C" bool observ_input_set_FF0 (observ_world_t *cWrld, void *v)
{
    world *wrld = reinterpret_cast<world *>(cWrld);
    wrld->_definedInp.gv_FF0 = true;
    std::memcpy(&wrld->_globals->gv_FF0, &v, sizeof(void *));
    return false;
}
static bool check_defined (world *wrld)
{
    if (!wrld->_definedInp.gv_FF0) {
        biffMsgAdd(wrld->_errors, "undefined input \"FF0\"\n");
        return true;
    }
    return false;
}
static void init_defined_inputs (world *wrld)
{
    wrld->_definedInp.gv_FF0 = false;
}
static void init_defaults (globals *glob)
{
}
static bool init_globals (world *wrld)
{
    globals *glob = wrld->_globals;
    diderot::array< int32_t, 1 > t_0;
    t_0[0] = 3;
    glob->gv_length = 7;
    return false;
}
static void f_init (f_strand *self, int32_t p_i_1)
{
    self->sv_out[0] = 0.0;
    self->sv_out[1] = 0.0;
    self->sv_out[2] = 0.0;
    self->sv_out[3] = 0.0;
    self->sv_out[4] = 0.0;
    self->sv_out[5] = 0.0;
    self->sv_out[6] = 0.0;
    self->sv_out[7] = 0.0;
    self->sv_out[8] = 0.0;
    self->sv_i = p_i_1;
}
static diderot::strand_status f_update (globals *glob, f_strand *self)
{
    vec3 v_3;
    bool l__t_19;
    tensor_3_3 l_out_24;
    vec3 v_2 = vcons3(0.0, 0.0, 0.0);
    if (self->sv_i == 0) {
        v_3 = vcons3(0.12e0, 0.53e0, 0.54e0);
    }
    else {
        vec3 v_4;
        if (self->sv_i == 1) {
            v_4 = vcons3(0.12e0, 0.53e0, 0.54e0);
        }
        else {
            vec3 v_5;
            if (self->sv_i == 2) {
                v_5 = vcons3(0.85e0, 0.44e0, 0.82e0);
            }
            else {
                vec3 v_6;
                if (self->sv_i == 3) {
                    v_6 = vcons3(0.61e0, 0.44e0, 0.2e0);
                }
                else {
                    vec3 v_7;
                    if (self->sv_i == 4) {
                        v_7 = vcons3(0.59e0, 0.48e0, 0.22e0);
                    }
                    else {
                        vec3 v_8;
                        if (self->sv_i == 5) {
                            v_8 = vcons3(0.65e0, 0.12e0, 0.24e0);
                        }
                        else {
                            vec3 v_9;
                            if (self->sv_i == 6) {
                                v_9 = vcons3(0.41e0, 0.79e0, 0.31e0);
                            }
                            else {
                                vec3 v_10;
                                if (self->sv_i == 7) {
                                    v_10 = vcons3(0.73e0, 0.44e0, 0.55e0);
                                }
                                else {
                                    v_10 = v_2;
                                }
                                v_9 = v_10;
                            }
                            v_8 = v_9;
                        }
                        v_7 = v_8;
                    }
                    v_6 = v_7;
                }
                v_5 = v_6;
            }
            v_4 = v_5;
        }
        v_3 = v_4;
    }
    int32_t l_numcell_11 = NumCells1(glob->gv_FF0);
    MappTy l_celltonode_12 = CellToNode1(glob->gv_FF0);
    FloatMapTy l_nodetopoint_13 = NodeToPoint1(glob->gv_FF0);
    std::string l_JIs_14 = "none;printf(\"Reached a checkpoint;\n\");";
    tensor_3 _arg_15;
    vpack3(_arg_15, v_3);
    fcTy l_fc_16 = wrapcell_UnitCubeMesh_P_4(_arg_15.base(), l_numcell_11, l_celltonode_12, l_nodetopoint_13,
        GetTracker(glob->gv_FF0));
    MappTy l_nodetocoord_17 = NodeToCoord1(glob->gv_FF0);
    coordTy l_coordinates_18 = Coordinates1(glob->gv_FF0);
    if (checkCell(l_fc_16)) {
        l__t_19 = true;
    }
    else {
        l__t_19 = false;
    }
    if (l__t_19) {
        tensor_3 _arg_20;
        vpack3(_arg_20, v_3);
        std::string l_makeBasisEvaluation_21 = "none;printf(\"Reached a checkpoint;\n\");";
        int32_t l_cell_22 = GetCell(l_fc_16);
        tensor_ref_3_3 l_probe_l_4_23 = s_3makeEval_UnitCubeMesh_P_4_1(
            GetNode(l_cell_22, l_celltonode_12, l_nodetocoord_17), GetPos(l_fc_16), l_coordinates_18, l_cell_22,
            l_celltonode_12, l_nodetopoint_13);
        l_out_24[0] = l_probe_l_4_23[0];
        l_out_24[1] = l_probe_l_4_23[1];
        l_out_24[2] = l_probe_l_4_23[2];
        l_out_24[3] = l_probe_l_4_23[3];
        l_out_24[4] = l_probe_l_4_23[4];
        l_out_24[5] = l_probe_l_4_23[5];
        l_out_24[6] = l_probe_l_4_23[6];
        l_out_24[7] = l_probe_l_4_23[7];
        l_out_24[8] = l_probe_l_4_23[8];
    }
    else {
        l_out_24[0] = 0.72e1;
        l_out_24[1] = 0.72e1;
        l_out_24[2] = 0.72e1;
        l_out_24[3] = 0.72e1;
        l_out_24[4] = 0.72e1;
        l_out_24[5] = 0.72e1;
        l_out_24[6] = 0.72e1;
        l_out_24[7] = 0.72e1;
        l_out_24[8] = 0.72e1;
    }
    self->sv_out = l_out_24;
    return diderot::kStabilize;
}
extern "C" bool observ_output_get_out (observ_world_t *cWrld, Nrrd *nData)
{
    world *wrld = reinterpret_cast<world *>(cWrld);
    // Compute sizes of nrrd file
    size_t sizes[2];
    sizes[0] = 9;
    sizes[1] = wrld->_size[0];
    // Allocate nData nrrd
    if (nrrdMaybeAlloc_nva(nData, nrrdTypeDouble, 2, sizes) != 0) {
        char *msg = biffGetDone(NRRD);
        biffMsgAdd(wrld->_errors, msg);
        std::free(msg);
        return true;
    }
    // copy data to output nrrd
    char *cp = reinterpret_cast<char *>(nData->data);
    for (auto ix = wrld->_strands.begin_alive(); ix != wrld->_strands.end_alive(); ix = wrld->_strands.next_alive(ix)) {
        memcpy(cp, &wrld->_strands.strand(ix)->sv_out, 9 * sizeof(double));
        cp += 9 * sizeof(double);
    }
    nData->axis[0].kind = nrrdKind3DMatrix;
    nData->axis[1].kind = nrrdKindSpace;
    return false;
}
/*---------- begin world-methods.in ----------*/
// Allocate the program's world
//
world::world ()
    : diderot::world_base (ProgramName, true, 1)
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
    assert (this->_stage == diderot::POST_NEW);

#if !defined(DIDEROT_STANDALONE_EXEC) && !defined(DIDEROT_NO_INPUTS)
  // initialize the defined flags for the input globals
    init_defined_inputs (this);
#endif

#ifdef DIDEROT_TARGET_PARALLEL
  // get CPU info
    if (this->_sched->get_cpu_info (this)) {
        return true;
    }
#endif

    this->_stage = diderot::POST_INIT;

    return false;

}

// allocate the initial strands and initialize the rest of the world structure.
//
bool world::alloc (int32_t base[1], uint32_t size[1])
{
    size_t numStrands = 1;
    for (uint32_t i = 0;  i < 1;  i++) {
        numStrands *= size[i];
        this->_base[i] = base[i];
        this->_size[i] = size[i];
    }

    if (this->_verbose) {
        std::cerr << "world::alloc: " << size[0];
        for (uint32_t i = 1;  i < 1;  i++) {
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
    this->_tree = new diderot::kdtree<0, double, strand_array> (&this->_strands);
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
    int lo_0 = 0;
    int hi_1 = glob->gv_length;
    int32_t base[1] = {lo_0,};
    uint32_t size[1] = {static_cast<uint32_t>(hi_1 - lo_0 + 1),};
    if (this->alloc(base, size)) {
        return true;
    }
    uint32_t ix = 0;
    for (int i_i_25 = lo_0; i_i_25 <= hi_1; i_i_25++) {
        f_init(this->_strands.strand(ix), i_i_25);
        ++ix;
    }
    this->swap_state();
    this->_stage = diderot::POST_CREATE;
    return false;
}
/*---------- begin seq-run-nobsp.in ----------*/
//! Run the Diderot program (sequential version without BSP semantics)
//! \param max_nsteps the limit on the number of super steps; 0 means unlimited
//! \return the number of steps taken, or 0 on error.
uint32_t world::run (uint32_t max_nsteps)
{
    if (this->_stage == diderot::POST_CREATE) {
#ifdef DIDEROT_HAS_GLOBAL_START
        this->global_start();
#endif
        this->_stage = diderot::RUNNING;
    }
    assert (this->_stage == diderot::RUNNING);

#ifndef DIDEROT_NO_GLOBALS
    globals *glob = this->_globals;
#endif

    if (max_nsteps == 0) {
        max_nsteps = 0xffffffff;  // essentially unlimited
    }

    double t0 = airTime();

    if (this->_verbose) {
        std::cerr << "run with " << this->_strands.num_alive() << " strands ..." << std::endl;
    }

#ifdef DIDEROT_HAS_START_METHOD
    this->run_start_methods();
#endif

  // iterate until all strands are stable
    uint32_t maxSteps = 0;
    for (auto ix = this->_strands.begin_active();
         ix != this->_strands.end_active();
         )
    {
        diderot::strand_status sts = this->_strands.status(ix);
        uint32_t nSteps = 0;
        while ((! sts) && (nSteps < max_nsteps)) {
            nSteps++;
            sts = this->_strands.strand_update(glob, ix);
        }
        switch (sts) {
          case diderot::kStabilize:
          // stabilize the strand's state.
            ix = this->_strands.strand_stabilize (ix);
            break;
#ifdef DIDEROT_HAS_STRAND_DIE
          case diderot::kDie:
            ix = this->_strands.kill (ix);
            break;
#endif
          default:
            assert (sts == this->_strands.status(ix));
	    ix = this->_strands.next_active(ix);
            break;
        }
        if (maxSteps < nSteps) maxSteps = nSteps;
    }

    this->_run_time += airTime() - t0;

    if (this->_strands.num_active() == 0)
        this->_stage = diderot::DONE;

    return maxSteps;

} // world::run
/*---------- end seq-run-nobsp.in ----------*/

/*---------- begin namespace-close.in ----------*/

} // namespace observ
/*---------- end namespace-close.in ----------*/

/*---------- begin c-wrappers.in ----------*/
extern "C" uint32_t observ_num_strands (observ_world_t *wrld)
{
    observ::world *w = reinterpret_cast<observ::world *>(wrld);
    return w->_strands.num_alive();
}

extern "C" uint32_t observ_num_active_strands (observ_world_t *wrld)
{
    observ::world *w = reinterpret_cast<observ::world *>(wrld);
    return w->_strands.num_active();
}

extern "C" uint32_t observ_num_stable_strands (observ_world_t *wrld)
{
    observ::world *w = reinterpret_cast<observ::world *>(wrld);
    return w->_strands.num_stable();
}

extern "C" bool observ_any_errors (observ_world_t *wrld)
{
    observ::world *w = reinterpret_cast<observ::world *>(wrld);
    return (w->_errors->errNum > 0);
}

extern "C" char *observ_get_errors (observ_world_t *wrld)
{
    observ::world *w = reinterpret_cast<observ::world *>(wrld);
    char *msg = biffMsgStrGet (w->_errors);
    biffMsgClear (w->_errors);
    return msg;
}

extern "C" observ_world_t *observ_new_world ()
{
    observ::world *w = new (std::nothrow) observ::world();
    return reinterpret_cast<observ_world_t *>(w);
}

extern "C" bool observ_init_world (observ_world_t *wrld)
{
    observ::world *w = reinterpret_cast<observ::world *>(wrld);

    if (w->_stage != diderot::POST_NEW) {
        w->error ("multiple calls to observ_init_world");
        return true;
    }

    if (w->init()) {
        return true;
    }

#ifndef DIDEROT_NO_INPUTS
    if (w != nullptr) {
        init_defined_inputs (w);
        init_defaults (w->_globals);
    }
#endif

    return false;
}

extern "C" bool observ_create_strands (observ_world_t *wrld)
{
    observ::world *w = reinterpret_cast<observ::world *>(wrld);

    if (w->_stage < diderot::POST_INIT) {
        w->error ("must call observ_init_world before observ_create_strands");
        return true;
    }
    else if (w->_stage > diderot::POST_INIT) {
        w->error ("multiple calls to observ_create_strands");
        return true;
    }

#ifndef DIDEROT_NO_INPUTS
    if (check_defined(w)) {
        return true;
    }
#endif
    return static_cast<bool>(w->create_strands());
}

extern "C" uint32_t observ_run (observ_world_t *wrld, uint32_t maxNSteps)
{
    observ::world *w = reinterpret_cast<observ::world *>(wrld);

    if (w->_stage < diderot::POST_CREATE) {
        w->error ("attempt to run uninitialized program");
        return 0;
    }
    else if (w->_stage == diderot::DONE) {
        return 0;
    }

    return w->run(maxNSteps);
}

extern "C" void observ_shutdown (observ_world_t *wrld)
{
    observ::world *w = reinterpret_cast<observ::world *>(wrld);
    delete w;
}

extern "C" void observ_set_verbose (observ_world_t *wrld, bool mode)
{
    observ::world *w = reinterpret_cast<observ::world *>(wrld);
    w->_verbose = (mode ? true : false);
}

extern "C" bool observ_get_verbose (observ_world_t *wrld)
{
    observ::world *w = reinterpret_cast<observ::world *>(wrld);
    return static_cast<bool>(w->_verbose);
}

#ifdef DIDEROT_TARGET_PARALLEL

bool observ_set_num_workers (observ_world_t *wrld, uint32_t nw)
{
    observ::world *w = reinterpret_cast<observ::world *>(wrld);
    if (w->_sched->_numHWCores < nw) {
        w->_sched->_numWorkers = w->_sched->_numHWCores;
        return true;
    }
    else if (nw > 0) {
        w->_sched->_numWorkers = nw;
    }
    else {
        w->_sched->_numWorkers = w->_sched->_numHWCores;
    }
    return false;
}

uint32_t observ_get_num_workers (observ_world_t *wrld)
{
    observ::world *w = reinterpret_cast<observ::world *>(wrld);
    return w->_sched->_numWorkers;
}

#endif /* DIDEROT_TARGET_PARALLEL */
/*---------- end c-wrappers.in ----------*/

