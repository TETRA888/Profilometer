import numpy as np
import open3d as o3d

# Load point data from a text file
def load_point_data(file_path):
    points_data = np.loadtxt(file_path, delimiter=' ', dtype=float)
    return points_data

# Load points from the text file
file_path = 'datapoints.txt'
points_data = load_point_data(file_path)

# Ensure the data is in the correct shape
if points_data.shape[1] != 7:
    raise ValueError("Each line in the file must contain 7 values: x, y, z, r, g, b, a")

# Convert points to NumPy array
points = points_data[:, :3]  # x, y, z
colors = points_data[:, 3:6] / 255.0  # r, g, b (normalize to [0, 1])

# Create Open3D point cloud
pcd = o3d.geometry.PointCloud()
pcd.points = o3d.utility.Vector3dVector(points)
pcd.colors = o3d.utility.Vector3dVector(colors)

# Estimate normals for the point cloud
pcd.estimate_normals(search_param=o3d.geometry.KDTreeSearchParamHybrid(radius=0.1, max_nn=30))

# Perform Poisson reconstruction
mesh, densities = o3d.geometry.TriangleMesh.create_from_point_cloud_poisson(pcd, depth=9)

# Optionally, you can simplify the mesh or perform other operations here

# Visualize the result
o3d.visualization.draw_geometries([mesh])

# Optionally save the mesh to a file
o3d.io.write_triangle_mesh("output_mesh.ply", mesh)
