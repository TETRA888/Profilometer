import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from scipy.interpolate import griddata

def plot_data(filename = "profileData.csv"):
    # Reading in the CSV file
    df = pd.read_csv(filename)

    # Extracting the data
    x = df['X'].values
    y = df['Y'].values
    z = df['Z'].values

    # 3D visual
    fig = plt.figure(figsize=(12, 8))

    # Creating a 3D plot
    ax = fig.add_subplot(211, projection='3d')

    # Color points by Z value
    scatter = ax.scatter(x, y, z, c=z, cmap='plasma', s=5)

    ax.set_xlim(0, 2500) # X axis limit
    ax.set_ylim(0, 10000) # Y axis limit
    ax.set_zlim(0, 30) # Z axis limit

    # labels
    ax.set_xlabel('X Position (mm)')
    ax.set_ylabel('Y Position (mm)')
    ax.set_zlabel('Z Height (mm)')
    ax.set_title('3D Scan Profile')

    # Grids
    ax.grid(True)

    # Add colorbar
    cbar = fig.colorbar(scatter, ax=ax, shrink=0.5, aspect=5)
    cbar.set_label('Height (mm)')
    
    plt.savefig("3DProfile.png", dpi=dpi, bbox_inches='tight')
    #print(f"Plot saved as {"3DProfile.png"}")