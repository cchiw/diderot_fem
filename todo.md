# Fem Prime
High priority items are marked with a "&#x1F525;" symbol.

Charisee is working on items with a &#127801; symbol.

##Compiler Development
* differentiation &#x1F525;
* inside test  &#x1F525;
	- surface to high-to-mid  &#127801; 
* create a richer support for elements
* surface syntax clean up 
	- create tuple? for description and pointer
* EIN params should reflect mesh/element/space
* Tighten type checker for different input
	- Do we still need three pointers? Teo: No.
* code generation optimization
	- (need benchmarks)
	- some clean up should help
* investigate locality issues with regard to mesh
* Push to mid (discuss as it might make differentiation easier)
* merge
	- backend in sync &#127801;
	- flux with chiw branch 
	

##Examples
### self-contained  and demonstrative 
* probe field at a position (various syntax) &#127801; 
* visualize a sample of a pde solution (helmholtz) &#127801; 
* volume render a pde solution
	- need inside test 


### comparative 
* crest lines or some vis feature with high level of tensor math (needs differentiation)
* higher order vs. lower order
* Demonstrate need by showing improvement on examples that paraview cannot visualize well.
** Teo has a question about plotting things and is putting this here for memory.

### benchmarks 
* timing between fem and femprime branch

##testing 
* regression tests for point-eval: Teo: There are a lot of tests being run via testing/test.py as of this moment.
* visualization correctness 
	- symmetry
* list of pdes with known solutions that FEM can solve: Evans and Andrei D. Polyanin, Vladimir E. Nazaikinskii Handbook of Linear Partial Differential Equations for Engineers and Scientists (I have PDFs)
* talk about metamorphic testing



## Writing
* few paragraphs on 
	- point eval
	- related work
	- application ideas 
	
