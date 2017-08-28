import matplotlib.pyplot as plt

with open("unitMeshData","r") as f:
    data = f.read().split("\n")
    l = len(data)/2
    f = lambda x: map(float,x.split(","))
    p1 = map(f,data[0:l])
    p2 = map(f,data[l:])
    g0 = lambda x: x[0]
    g1 = lambda x: x[1]
    t = map(g0,p1)
    tt = map(g1,p1)
    ttt = map(g1,p2)
    fig = plt.figure()
    ax1 = fig.add_axes((0.1, 0.2, 0.8, 0.7))
    ax1.set_xlabel("Number of Cells in UnitSquareMesh(r,r).")
    ax1.set_ylabel("Seconds to execute.")
    fig.text(.5,0.05," Tests were conducted on the UnitSquareMesh(r,r) where r=1...64 using resolution 1000.\n The red is femprime without optimization. The blue is with the optimization.",ha='center')
    fig.set_size_inches(7, 8, forward=True)
    plt.plot(t,tt,"bs",t,ttt,"rs")
    plt.savefig("UnitSquareMeshResult.png")
    
    
        
