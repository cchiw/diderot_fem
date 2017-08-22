The idea here is to use PDEs whose solutions are of the form $(cos(ay)+sin(ax))/a^2$. The reason to pick this is that for large $a$, this function behaves likes dividing the grid up into a bunch of square and placing a mountain in each square. To see this, we take the gradient: (Cos(ax)/a,-sin(ay)/a). Solving this gives you four classes of solution for each pair of integer (n1,n2):

(-pi/2 + 2*pi*n1)/a, (2*pi*n2/a)
(-pi/2 + 2*pi*n1)/a, ((pi+2*pi*n2)/a)
(pi/2 + 2*pi*n1)/a, (2*pi*n2/a)
(pi/2 + 2*pi*n1)/a, ((pi+2*pi*n2)/a)

From this, it is not hard to see that the critical points are evenly spaced across some grid i.e the mins and maxes occur in predictable places that we can imagine placing boxes around. 

Another observation is that for a box, say the unit box ([0,1]^2), we increase the number of mountains by increasing a as this means there are more integers $(n1,n2)$ so that $(-pi/2 + 2*pi*n1)/a, (2*pi*n2/a)\in [0,1]^2$. 

An example with $a=40$ is included as a40.pdf.


This screws with visualization in two ways. To demonstrate this, we plot the a=40 case various levels of discretaiztion using paraview. Essneitally, using all integers $(i,j)\in(1..16,1..16)$, we partitioend a mesh and then looked at the best guess for $f$ on it. We place all of our results in the pvd dir. Note that to find file i,j, look for output(i*16+j).pvd

Looking at the case $i=j$, you see two things. First, most of the early ones are quite inaccurate. We should expect to see lots of mountains yet only small portion of those are showing at even 8 by 8. The second thing, is that even in the latter examples, there are horrible inaccuracies. Look at 13 and 14. here, we can see mountains, but they are clearly disorted/hiding other ones. The reason for this is that the placement of the mesh grids is not nice enough and so certain phenomenums are washed out. This is even worse when you consider uneven examples. Take i=4,j=7. This gives us something that could look right yet it is quite innaccurate.

We now note too more things. First, we can make the above analysis more precise by counting visible critical points versus the expected ones. Second, for any level of mesh discretization, I believe we can alwalys come up with an $a$ large enough so this error alwalys happens.


Now, we can do a try of our own with Diderot. We do polynomials of size 5 on a 8 by 8 mesh. We can clearly see a lot more of the up and down structure as well as a lot more of the mesh structure. Some better coloration and maybe 3 graphs might make these comparisoins better. I need to spend more time on generating good graphics.

We are also going to try to make an example that shows breakage in a not so mesh dependent way. That will be 2.
