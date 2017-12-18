/*---------- begin cxx-head.in ----------*/
/*! \file squaremesh.cxx
 *
 * Generated from squaremesh.diderot.
 *
 * Command: /home/teodoro/gitcode/again/femprime/bin/diderotc --log --double --debug --namespace=squaremesh squaremesh.diderot
 * Version: vis15:2016-07-29
 */
/*---------- end cxx-head.in ----------*/

#define DIDEROT_STRAND_HAS_CONSTR
#define DIDEROT_STRAND_ARRAY
/*---------- begin lib-cxx-incl.in ----------*/
#include "squaremesh.h"
#include "diderot/diderot.hxx"

#ifdef DIDEROT_ENABLE_LOGGING
#define IF_LOGGING(...)         __VA_ARGS__
#else
#define IF_LOGGING(...)
#endif

static std::string ProgramName = "squaremesh";
/*---------- end lib-cxx-incl.in ----------*/

// ***** Begin synthesized types *****

namespace squaremesh {
    typedef double vec2 __attribute__ ((vector_size (16)));
    struct tensor_ref_2 : public diderot::tensor_ref<double,2> {
        tensor_ref_2 (const double *src);
        tensor_ref_2 (struct tensor_2 const & ten);
        tensor_ref_2 (tensor_ref_2 const & ten);
    };
    struct tensor_2 : public diderot::tensor<double,2> {
        tensor_2 ()
            : diderot::tensor<double,2>()
        { }
        tensor_2 (std::initializer_list< double > const & il)
            : diderot::tensor<double,2>(il)
        { }
        tensor_2 (const double *src)
            : diderot::tensor<double,2>(src)
        { }
        tensor_2 (tensor_2 const & ten)
            : diderot::tensor<double,2>(ten._data)
        { }
        ~tensor_2 () { }
        tensor_2 & operator= (tensor_2 const & src);
        tensor_2 & operator= (tensor_ref_2 const & src);
        tensor_2 & operator= (std::initializer_list< double > const & il);
        tensor_2 & operator= (const double *src);
    };
    inline tensor_ref_2::tensor_ref_2 (const double *src)
        : diderot::tensor_ref<double,2>(src)
    { }
    inline tensor_ref_2::tensor_ref_2 (struct tensor_2 const & ten)
        : diderot::tensor_ref<double,2>(ten._data)
    { }
    inline tensor_ref_2::tensor_ref_2 (tensor_ref_2 const & ten)
        : diderot::tensor_ref<double,2>(ten._data)
    { }
    inline tensor_2 & tensor_2::operator= (tensor_2 const & src)
    {
        this->copy(src._data);
        return *this;
    }
    inline tensor_2 & tensor_2::operator= (tensor_ref_2 const & src)
    {
        this->copy(src._data);
        return *this;
    }
    inline tensor_2 & tensor_2::operator= (std::initializer_list< double > const & il)
    {
        this->copy(il);
        return *this;
    }
    inline tensor_2 & tensor_2::operator= (const double *src)
    {
        this->copy(src);
        return *this;
    }
} // namespace squaremesh
// ***** End synthesized types *****

/*---------- begin namespace-open.in ----------*/
namespace squaremesh {

static std::string ProgramName = "squaremesh";

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

typedef struct {
    bool gv_imgRes;
    bool gv_f;
} defined_inputs;
struct globals {
    int32_t gv_imgRes;
    FEMSrcTy gv_f;
};
struct sample_strand {
    double sv_uu;
    double sv_vv;
    tensor_2 sv_pos;
    double sv_out;
};
/*---------- begin seq-sarr.in ----------*/
// forward declarations of strand methods
#ifdef DIDEROT_HAS_START_METHOD
static diderot::strand_status sample_start (sample_strand *self);
#endif // DIDEROT_HAS_START_METHOD
static diderot::strand_status sample_update (sample_strand *self);
#ifdef DIDEROT_HAS_STABILIZE_METHOD
static void sample_stabilize (sample_strand *self);
#endif // DIDEROT_HAS_STABILIZE_METHOD

// if we have both communication and "die", then we need to track when strands die
// so that we can rebuild the list of strands use to construct the kd-tree
#if defined(DIDEROT_HAS_STRAND_COMMUNICATION) && !defined(DIDEROT_HAS_STRAND_DIE)
#  define TRACK_STRAND_DEATH
#endif

// strand_array for SEQUENTIAL/NO BSP/SINGLE STATE/DIRECT ACCESS
//
struct strand_array {
    typedef sample_strand strand_t;
    typedef uint32_t index_t;
    typedef index_t sid_t;              // strand ID (index into strand-state storage)

    uint8_t             *_status;       // the array of status information for the strands
    char                *_storage;      // points to array of sample_strand structs
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
    sample_strand *id_to_strand (sid_t id) const
    {
        assert (id < this->_nItems);
        return reinterpret_cast<sample_strand *>(this->_storage + id * sizeof(sample_strand));
    }

  // return a strand's status
    diderot::strand_status status (index_t ix) const
    {
        assert (ix < this->_nItems);
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
        this->_storage = static_cast<char *>(std::malloc (nItems * sizeof(sample_strand)));
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
            new (this->strand(ix)) sample_strand;
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
        return sample_start(this->strand(ix));
    }
#endif // DIDEROT_HAS_START_METHOD

  // invoke strand's update method
    diderot::strand_status strand_update (index_t ix)
    {
        return sample_update(this->strand(ix));
    }

  // invoke strand's stabilize method
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
        this->strand(ix)->~sample_strand();
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
    bool alloc (int32_t base[2], uint32_t size[2]);
    bool create_strands ();
    uint32_t run (uint32_t max_nsteps);
    void swap_state ();
};
// ***** Begin synthesized operations *****

inline double *makeTransformHelp_UnitSquareMesh_Lagrange_2(double** C, double* k, const double *modOff, double result[2]){

	result[0] = 0-modOff[0] + (C[2][0])*(1.0*k[1] + 0) + (C[1][0])*(1.0*k[0] + (0) + 0) + (C[0][0])*(-1.0*k[0] - 1.0*k[1] + 1.0 + 0);

	result[1] = 0-modOff[1] + (C[2][1])*(1.0*k[1] + 0) + (C[1][1])*(1.0*k[0] + (0) + 0) + (C[0][1])*(-1.0*k[0] - 1.0*k[1] + 1.0 + 0);

	return(result);
}
double * makeTransform_UnitSquareMesh_Lagrange_2(double * k, int cell, MappTy nM, FloatMapTy pM ){

	double *C[2] = {0,0};

	getPoints(cell,nM,pM,C);

	double random[2] = { 0.0 };

	double result[2] = { 0.0 };

	return(makeTransformHelp_UnitSquareMesh_Lagrange_2(C,k,random,result));
}
inline double ** helpMakeJacobian_UnitSquareMesh_Lagrange_2(double ** C, double *k, double * J[2]){

	J[0][0] = (C[0][0] * ((0) - (0) - 0.999999999999999 + 0)) + (C[1][0] * ((0) + (0) + 0.999999999999999 + 0)) + (C[2][0] * (0 + 0)) + 0;

	J[0][1] = (C[0][0] * ((0) + (0) - 1.0 + 0)) + (C[1][0] * ((0) + (0) + (0) + 0)) + (C[2][0] * ((0) - (0) + 1.0 + 0)) + 0;

	J[1][0] = (C[0][1] * ((0) - (0) - 0.999999999999999 + 0)) + (C[1][1] * ((0) + (0) + 0.999999999999999 + 0)) + (C[2][1] * (0 + 0)) + 0;

	J[1][1] = (C[0][1] * ((0) + (0) - 1.0 + 0)) + (C[1][1] * ((0) + (0) + (0) + 0)) + (C[2][1] * ((0) - (0) + 1.0 + 0)) + 0;

	return(J);
}
double ** makeJacobian_UnitSquareMesh_Lagrange_2(int cell, MappTy nM, FloatMapTy pM, double *k, double * J[2]){

	double *C[2];

	getPoints(cell,nM,pM,C);

	return(helpMakeJacobian_UnitSquareMesh_Lagrange_2(C,k,J));
}
inline double ** helpInverseJacobian_UnitSquareMesh_Lagrange_2(double ** C, double *k, double * J[2]){

	double t11 = (C[0][0] * ((0) - (0) - 0.999999999999999 + 0)) + (C[1][0] * ((0) + (0) + 0.999999999999999 + 0)) + (C[2][0] * (0 + 0)) + 0;

	double t12 = (C[0][0] * ((0) + (0) - 1.0 + 0)) + (C[1][0] * ((0) + (0) + (0) + 0)) + (C[2][0] * ((0) - (0) + 1.0 + 0)) + 0;

	double t21 = (C[0][1] * ((0) - (0) - 0.999999999999999 + 0)) + (C[1][1] * ((0) + (0) + 0.999999999999999 + 0)) + (C[2][1] * (0 + 0)) + 0;

	double t22 = (C[0][1] * ((0) + (0) - 1.0 + 0)) + (C[1][1] * ((0) + (0) + (0) + 0)) + (C[2][1] * ((0) - (0) + 1.0 + 0)) + 0;

	double det = 1.0/(t11*t22-t12*t21);

	J[0][0]= t22*det;

	J[0][1] = 0 - t12*det;

	J[1][0] = 0 - t21*det;

	J[1][1] = t11*det;

	return(0);
}
double ** makeJacobianInverse_UnitSquareMesh_Lagrange_2(int cell, MappTy nM, FloatMapTy pM, double *k,double * J[2]){

	double *C[2];

	getPoints(cell,nM,pM,C);

	return(helpInverseJacobian_UnitSquareMesh_Lagrange_2(C,k,J));
}
inline void *helpJIs_UnitSquareMesh_Lagrange_2(double **C,double J[2][2]){

	double k[2];

	k[0] = 0.333333333333;

	k[1] = 0.333333333333;

	double t11 = (C[0][0] * ((0) - (0) - 0.999999999999999 + 0)) + (C[1][0] * ((0) + (0) + 0.999999999999999 + 0)) + (C[2][0] * (0 + 0)) + 0;

	double t12 = (C[0][0] * ((0) + (0) - 1.0 + 0)) + (C[1][0] * ((0) + (0) + (0) + 0)) + (C[2][0] * ((0) - (0) + 1.0 + 0)) + 0;

	double t21 = (C[0][1] * ((0) - (0) - 0.999999999999999 + 0)) + (C[1][1] * ((0) + (0) + 0.999999999999999 + 0)) + (C[2][1] * (0 + 0)) + 0;

	double t22 = (C[0][1] * ((0) + (0) - 1.0 + 0)) + (C[1][1] * ((0) + (0) + (0) + 0)) + (C[2][1] * ((0) - (0) + 1.0 + 0)) + 0;

	double det = 1.0/(t11*t22-t12*t21);

	J[0][0]= t22*det;

	J[0][1] = 0 - t12*det;

	J[1][0] = 0 - t21*det;

	J[1][1] = t11*det;

	return(0);
}
inline void *jIs_UnitSquareMesh_Lagrange_2(double J[2][2],MappTy nM, FloatMapTy pM,int cell){

	double *C[3] = {0,0,0};

	getPoints(cell,nM,pM,C);

	helpJIs_UnitSquareMesh_Lagrange_2(C,J);
	return(0);}
inline double * helpTranslateCoordinates_UnitSquareMesh_Lagrange_2(double **C, const  double * x0, int itter, double newpos[2]){

	 newpos[0] = 0.333333333333;

	 newpos[1] = 0.333333333333;

	bool notConverged =true;

	int i = 0;
	double change[2] = {0.0 };

	double * temp;
	double random[2] = { 0.0 };
	double J[2][2] = {{0.0f,0.0f},{0.0f,0.0f}};

	helpJIs_UnitSquareMesh_Lagrange_2(C,J);

	while ((i < itter) && notConverged){

		temp = makeTransformHelp_UnitSquareMesh_Lagrange_2(C,newpos, x0,random);

		change[0]=(J[0][0] * temp[0]) + (J[0][1] * temp[1]) + 0;

		change[1]=(J[1][0] * temp[0]) + (J[1][1] * temp[1]) + 0;

		double test = (change[0] * change[0]) + (change[1] * change[1]) + 0;

		if(test < 1e-12*1e-12){notConverged=false;}

		newpos[0] -=change[0];

		newpos[1] -=change[1];

		i+=1;
}

	return(newpos);
}

fcTy wrapcell_UnitSquareMesh_Lagrange_2 (const double* vp,  int32_t vL, MappTy nM, FloatMapTy pM, optStruct opt)
	{
	int32_t * tracker = opt.tracker;
 if(*tracker > vL || *tracker < 0)
	{*tracker=0;}
;

	
	int range = 1;
	double *C[3] = {0,0,0};

	double * newposAllocate = new double[2]();
	int lastCell = *opt.tracker;

	int32_t * nbrs = &opt.Nbrs[vL*lastCell];

	for (int cellIndex = 0;  cellIndex < vL;  cellIndex+=1) {
		int32_t cell = nbrs[cellIndex];

		getPoints(cell,nM,pM,C);

		newposTy newpos = helpTranslateCoordinates_UnitSquareMesh_Lagrange_2(C,vp,range,newposAllocate);
		bool test = (newpos[0] + 1.0e-14 >= 0) && (newpos[1] + 1.0e-14 >= 0) && (newpos[0] + newpos[1] - 1.0e-14 <= 1);

			if(test){*tracker=cell;return {cell,newpos};}
		}
	for (int cell = 0;  cell < vL;  cell+=1) {
		getPoints(cell,nM,pM,C);

		newposTy newpos = helpTranslateCoordinates_UnitSquareMesh_Lagrange_2(C,vp,range,newposAllocate);
		bool test = (newpos[0] + 1.0e-14 >= 0) && (newpos[1] + 1.0e-14 >= 0) && (newpos[0] + newpos[1] - 1.0e-14 <= 1);

			if(test){*tracker=cell;return {cell,newpos};}
		}
		return {-1,NULL};
	}
inline double * helpEvalBasis_UnitSquareMesh_Lagrange_2(const double *k, double *result){

	result[0] = 2.0*k[0]*k[0] + 4.0*k[0]*k[1] - 3.0*k[0] + 2.0*k[1]*k[1] - 3.0*k[1] + 1.0 + 0;

	result[1] = 2.0*k[0]*k[0] - 1.0*k[0] + (0) + (0) + 0;

	result[2] = 2.0*k[1]*k[1] - 1.0*k[1] + 0;

	result[3] = 4.0*k[0]*k[1] + (0) + 0;

	result[4] = -4.0*k[0]*k[1] - (0) - 4.0*k[1]*k[1] + 4.0*k[1] + 0;

	result[5] = -4.0*k[0]*k[0] - 4.0*k[0]*k[1] + 4.0*k[0] - (0) + (0) - (0) + 0;

	return(result);
}

inline double ProbePhi_UnitSquareMesh_Lagrange_2(brevTy a, newposTy b) {

	double result = 0;

	double *weights = a.data;

	int len = a.col;

	double res[6] = {0,0,0,0,0,0};

	double * basisAtPos = helpEvalBasis_UnitSquareMesh_Lagrange_2(b,res);

	for(int itter = 0; itter < len; itter++){

		result += res[itter]*weights[itter];

	}

	return(result);
}

inline double lerp (double a, double b, double t)
{
    return a + t * (b - a);
}
inline vec2 vcons2 (double r0, double r1)
{
    return __extension__ (vec2){r0, r1};
}
inline void vpack2 (tensor_2 &dst, vec2 v0)
{
    dst._data[0] = v0[0];
    dst._data[1] = v0[1];
}
inline double s_makeEval_UnitSquareMesh_Lagrange_2_(NodeTy nodes, newposTy b, coordTy c){

	if (nodes.data ==0){return(0);}
	double array[6] = {0,0,0,0,0,0};

	brevTy weights = ProbeNodeC(nodes,c,array,0,1);
	double result = ProbePhi_UnitSquareMesh_Lagrange_2(weights,b);
	return(result);
}

// ***** End synthesized operations *****

extern "C" void squaremesh_input_get_imgRes (squaremesh_world_t *cWrld, int32_t *v)
{
    world *wrld = reinterpret_cast<world *>(cWrld);
    *v = wrld->_globals->gv_imgRes;
}
extern "C" bool squaremesh_input_set_imgRes (squaremesh_world_t *cWrld, int32_t v)
{
    world *wrld = reinterpret_cast<world *>(cWrld);
    wrld->_definedInp.gv_imgRes = true;
    wrld->_globals->gv_imgRes = v;
    return false;
}
extern "C" bool squaremesh_input_set_f (squaremesh_world_t *cWrld, void *v)
{
    world *wrld = reinterpret_cast<world *>(cWrld);
    wrld->_definedInp.gv_f = true;
    std::memcpy(&wrld->_globals->gv_f, &v, sizeof(void *));
    return false;
}
static bool check_defined (world *wrld)
{
    if (!wrld->_definedInp.gv_f) {
        biffMsgAdd(wrld->_errors, "undefined input \"f\"\n");
        return true;
    }
    return false;
}
static void init_defined_inputs (world *wrld)
{
    wrld->_definedInp.gv_imgRes = false;
    wrld->_definedInp.gv_f = false;
}
static void init_defaults (globals *glob)
{
    glob->gv_imgRes = 10;
}
static bool init_globals (world *wrld)
{
    globals *glob = wrld->_globals;
    return false;
}
static void sample_init (globals *glob, sample_strand *self, int32_t p_ui_0, int32_t p_vi_1)
{
    double l_op1_e3_l_7_2 = static_cast<double>(glob->gv_imgRes) - 0.5e0 - (-0.5e0);
    double l_uu_3 = lerp(0.0, 0.1e1, (static_cast<double>(p_ui_0) - (-0.5e0)) / l_op1_e3_l_7_2);
    double l_vv_4 = lerp(0.0, 0.1e1, (static_cast<double>(p_vi_1) - (-0.5e0)) / l_op1_e3_l_7_2);
    vec2 v_5 = vcons2(l_uu_3, l_vv_4);
    int32_t l_numcell_6 = NumCells1(glob->gv_f);
    MappTy l_celltonode_7 = CellToNode1(glob->gv_f);
    FloatMapTy l_nodetopoint_8 = NodeToPoint1(glob->gv_f);
    std::string l_JIs_9 = "none;printf(\"Reached a checkpoint;\n\");";
    tensor_2 _arg_10;
    vpack2(_arg_10, v_5);
    fcTy l_fc_11 = wrapcell_UnitSquareMesh_Lagrange_2(_arg_10.base(), l_numcell_6, l_celltonode_7, l_nodetopoint_8,
        GetTracker(glob->gv_f));
    tensor_2 _arg_12;
    vpack2(_arg_12, v_5);
    std::string l_makeBasisEvaluation_13 = "none;printf(\"Reached a checkpoint;\n\");";
    self->sv_uu = l_uu_3;
    self->sv_vv = l_vv_4;
    vpack2(self->sv_pos, v_5);
    self->sv_out = s_makeEval_UnitSquareMesh_Lagrange_2_(
        GetNode(GetCell(l_fc_11), l_celltonode_7, NodeToCoord1(glob->gv_f)), GetPos(l_fc_11), Coordinates1(glob->gv_f));
}
static diderot::strand_status sample_update (sample_strand *self)
{
    return diderot::kStabilize;
}
extern "C" bool squaremesh_output_get_out (squaremesh_world_t *cWrld, Nrrd *nData)
{
    world *wrld = reinterpret_cast<world *>(cWrld);
    // Compute sizes of nrrd file
    size_t sizes[2];
    sizes[0] = wrld->_size[1];
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
        memcpy(cp, &wrld->_strands.strand(ix)->sv_out, 1 * sizeof(double));
        cp += 1 * sizeof(double);
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
    int32_t l__t_15 = glob->gv_imgRes - 1;
    int lo_0 = 0;
    int lo_1 = 0;
    int32_t base[2] = {lo_0,lo_1,};
    uint32_t size[2] = {static_cast<uint32_t>(l__t_15 - lo_0 + 1),static_cast<uint32_t>(l__t_15 - lo_1 + 1),};
    if (this->alloc(base, size)) {
        return true;
    }
    uint32_t ix = 0;
    for (int i_vi_16 = lo_0; i_vi_16 <= l__t_15; i_vi_16++) {
        for (int i_ui_17 = lo_1; i_ui_17 <= l__t_15; i_ui_17++) {
            sample_init(this->_globals, this->_strands.strand(ix), i_ui_17, i_vi_16);
            ++ix;
        }
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
            sts = this->_strands.strand_update(ix);
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

} // namespace squaremesh
/*---------- end namespace-close.in ----------*/

/*---------- begin c-wrappers.in ----------*/
extern "C" uint32_t squaremesh_num_strands (squaremesh_world_t *wrld)
{
    squaremesh::world *w = reinterpret_cast<squaremesh::world *>(wrld);
    return w->_strands.num_alive();
}

extern "C" uint32_t squaremesh_num_active_strands (squaremesh_world_t *wrld)
{
    squaremesh::world *w = reinterpret_cast<squaremesh::world *>(wrld);
    return w->_strands.num_active();
}

extern "C" uint32_t squaremesh_num_stable_strands (squaremesh_world_t *wrld)
{
    squaremesh::world *w = reinterpret_cast<squaremesh::world *>(wrld);
    return w->_strands.num_stable();
}

extern "C" bool squaremesh_any_errors (squaremesh_world_t *wrld)
{
    squaremesh::world *w = reinterpret_cast<squaremesh::world *>(wrld);
    return (w->_errors->errNum > 0);
}

extern "C" char *squaremesh_get_errors (squaremesh_world_t *wrld)
{
    squaremesh::world *w = reinterpret_cast<squaremesh::world *>(wrld);
    char *msg = biffMsgStrGet (w->_errors);
    biffMsgClear (w->_errors);
    return msg;
}

extern "C" squaremesh_world_t *squaremesh_new_world ()
{
    squaremesh::world *w = new (std::nothrow) squaremesh::world();
    return reinterpret_cast<squaremesh_world_t *>(w);
}

extern "C" bool squaremesh_init_world (squaremesh_world_t *wrld)
{
    squaremesh::world *w = reinterpret_cast<squaremesh::world *>(wrld);

    if (w->_stage != diderot::POST_NEW) {
        w->error ("multiple calls to squaremesh_init_world");
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

extern "C" bool squaremesh_create_strands (squaremesh_world_t *wrld)
{
    squaremesh::world *w = reinterpret_cast<squaremesh::world *>(wrld);

    if (w->_stage < diderot::POST_INIT) {
        w->error ("must call squaremesh_init_world before squaremesh_create_strands");
        return true;
    }
    else if (w->_stage > diderot::POST_INIT) {
        w->error ("multiple calls to squaremesh_create_strands");
        return true;
    }

#ifndef DIDEROT_NO_INPUTS
    if (check_defined(w)) {
        return true;
    }
#endif
    return static_cast<bool>(w->create_strands());
}

extern "C" uint32_t squaremesh_run (squaremesh_world_t *wrld, uint32_t maxNSteps)
{
    squaremesh::world *w = reinterpret_cast<squaremesh::world *>(wrld);

    if (w->_stage < diderot::POST_CREATE) {
        w->error ("attempt to run uninitialized program");
        return 0;
    }
    else if (w->_stage == diderot::DONE) {
        return 0;
    }

    return w->run(maxNSteps);
}

extern "C" void squaremesh_shutdown (squaremesh_world_t *wrld)
{
    squaremesh::world *w = reinterpret_cast<squaremesh::world *>(wrld);
    delete w;
}

extern "C" void squaremesh_set_verbose (squaremesh_world_t *wrld, bool mode)
{
    squaremesh::world *w = reinterpret_cast<squaremesh::world *>(wrld);
    w->_verbose = (mode ? true : false);
}

extern "C" bool squaremesh_get_verbose (squaremesh_world_t *wrld)
{
    squaremesh::world *w = reinterpret_cast<squaremesh::world *>(wrld);
    return static_cast<bool>(w->_verbose);
}

#ifdef DIDEROT_TARGET_PARALLEL

bool squaremesh_set_num_workers (squaremesh_world_t *wrld, uint32_t nw)
{
    squaremesh::world *w = reinterpret_cast<squaremesh::world *>(wrld);
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

uint32_t squaremesh_get_num_workers (squaremesh_world_t *wrld)
{
    squaremesh::world *w = reinterpret_cast<squaremesh::world *>(wrld);
    return w->_sched->_numWorkers;
}

#endif /* DIDEROT_TARGET_PARALLEL */
/*---------- end c-wrappers.in ----------*/

