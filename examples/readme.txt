self-contained examples

(short-hand) descriptions of example
SpaceBasic: FunctionSpace(UnitSquareMesh(2,2), Lagrange(), 2)
SpaceCG:    FunctionSpace(UnitSquareMesh(10,10), CG, 3)

FieldPDE : (solves pde)
FieldEXP: (interpolates an expression)

JsonLib: uses premade json file
JsonMke: make json file

ProgFile : Diderot program provides path to specific file
ProgSyntax: Diderot program syntax describes space and provides path to folder

VisSample : visualization just samples field
VisMIP    : MIP volume-rendering 
——————————————————————————————————
ex1.) SpaceBasic, FieldEXP, JsonLib, ProgSyntax, VisSample 
ex2.) SpaceBasic, FieldEXP, JsonLib, ProgFile,   VisSample 
ex3.) SpaceBasic, FieldEXP, JsonMke, ProgFile,   VisSample 
ex4.) SpaceCG,    FieldPDE, JsonMke, ProgFile,   VisSample : HelmHoltz 