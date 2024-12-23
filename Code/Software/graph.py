import matplotlib.pyplot as plt

x = [1,2,3,5,6]
z = [3,2,3,4,1]

def graphProfile():
    plt.plot(x,z)

    plt.xlabel('X Axis Stroke')
    plt.ylabel('Z Axis Profile')
    plt.title('Test Track #1')

    plt.savefig("profileGraph.png")