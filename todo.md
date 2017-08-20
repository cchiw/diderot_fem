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
* Related Groups
* Background
	- Martin S. Alnaes, Anders Logg, Kristian B. Oelgaard, Marie E. Rognes, and Garth N. Wells. Unified form language: A domain-specific language for weak formulations of par- tial differential equations. ACM Transactions on Mathematical Software, 40, February 2014.
	- Ivo Babuska and J. Tinsley Oden. Verification and validation in computational en- gineering and science: Basic concepts. Computer Methods in Applied Mechanics and Engineering, 193(36-38):4057–4066, 9 2004.
	- Junjie Chen, Wenxiang Hu, Dan Hao, Yingfei Xiong, Hongyu Zhang, Lu Zhang, and Bing Xie. An empirical comparison of compiler testing techniques. In Proceedings of the 38th International Conference on Software Engineering, Austin, TX, USA, May 14-22, 2016, pages 180–190, 2016.
	- Koen Claessen and John Hughes. Quickcheck: A lightweight tool for random testing of Haskell programs. In Proceedings of the Fifth ACM SIGPLAN International Conference on Functional Programming, pages 268–279, New York, NY, USA, 2000. ACM.
	- Alastair F. Donaldson and Andrei Lascu. Metamorphic testing for (graphics) compilers. In Proceedings of the 1st International Workshop on Metamorphic Testing, International Conference on Software Engineering 2016, Austin, Texas, USA, May 16, 2016, pages 44–47, 2016.
	- Tiago Etiene, Carlos Scheidegger, L Gustavo Nonato, Robert M Kirby, and Cl ́audio T Silva. Verifiable visualization for isosurface extraction. Visualization and Computer Graphics, 15(6):1227–1234, 2009.
	- Gordon L. Kindlmann and Carlos Eduardo Scheidegger. An algebraic process for visualization design. IEEE Transactions on Visualization and Computer Graphics, 20(12):2181–2190, 2014.

	- Christian Lindig. Random testing of C calling conventions. In Proceedings of the Sixth International Symposium on Automated Analysis-driven Debugging, pages 3–12, New York, NY, USA, 2005. ACM.
	
	- Cludio T Silva Tiago Etiene, Robert M Kirby. An Introduction to Verification of Vi- sualization Techniques, volume 7. Morgan and Claypool Publishers, Clifton Park, New York, 3rd edition, December 2015.
	
	- Xuejun Yang, Yang Chen, Eric Eide, and John Regehr. Finding and understanding bugs in C compilers. ACM SIGPLAN Conference on Programming Language Design and Implementation, 46(6):283–294, June 2011.