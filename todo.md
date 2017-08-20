# Fem Prime
High priority items are marked with a "&#x1F525;" symbol.

##Compiler Development
* differentiation &#x1F525;
* create a richer support for elements
* surface syntax clean up 
	- create tuple? for description and pointer
* EIN params should reflect mesh/element/space
* Tighten type checker for different input
	- Do we still need three pointers?
* code generation optimization  
	- (need benchmarks)
	- some clean up should help
* investigate locality issues with regard to mesh1

##Applications
### demonstrative examples
* probe field at a position 
* visualize a sample of a pde solution
* volume render a pde solution

### comparative examples
* crest lines or some vis feature with high level of tensor math (needs differentiation)
* higher order vs. lower order

### benchmarks 
* timing between fem and femprime branch

###testing 
* regression tests for point-eval
* visualization correctness 
	- symmetry
* list of pdes with known solutions 
* talk about metamorphic testing

##Reading and Writing
* related work
