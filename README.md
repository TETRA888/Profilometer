#  <div> Open Road Profiler (ORP) </div>

 ![Static Badge](https://img.shields.io/badge/Language-C-blue)
 ![Static Badge](https://img.shields.io/badge/Language-Python-red)
 ![Static Badge](https://img.shields.io/badge/Tech-RaspberryPi-hotpink)
 ![Static Badge](https://img.shields.io/badge/Tech-Arduino-darkblue)
 ![Static Badge](https://img.shields.io/badge/Tech-LiDAR-purple)
 ![Static Badge](https://img.shields.io/badge/Tech-64MP%20Camera-purple)
 ![Static Badge](https://img.shields.io/badge/Tech-%20Class%20II%20Precision%20Laser-purple)
 ![Static Badge](https://img.shields.io/badge/Precision-Submilimeter-green)

An advanced, open-source system engineered to map the degradation of theoretical road designs for Caltrans. Leveraging a robust integration of **computer vision**, **LiDAR sensing**, and 
**optical measurement** technologies to capture sub-millimeter road surface deformations under simulated traffic loads.

<div align="center">
  <img src="https://github.com/user-attachments/assets/0f8856cc-a083-4535-b870-cc8844e09d20" alt="title image" width="550">
</div>
<div align = "Center"> Figure 4.2 (Frame with Electronics) </div>

## Table of Contents
- [Purpose](#purpose)
- [Core Team](#core-team)
- [Electrical System Design](#high-level-electrical-system-design-overview)
  - [Schematic Overview](#electronic-schematic-overview)
  - [Assembled Electronics](#assembled-data-acquisition-electronics-overview)
- [Software System Design](#high-level-software-system-design-overview)
  - [Simple GUI for Version 1.1](#simple-gui-for-version-11)
  - [Sample Software Code](#sample-software-code)
  - [Sample Firmware Code](#sample-firmware-code)
- [Mechanical Design](#mechanical-frame-cad-design-overview)
  - [Assembled Frame](#assembled-sample-frame)
  - [Mounted Electronics](#electronics-mounted-on-frame)
- [Documentation](#documentation-and-implementation)
- [Tech Stack and Specs](#tech-stack-and-specs)
- [Parts](#parts)
- [Historical Context](#profiler-from-30-years-ago)

## Purpose

Purpose-built to work with the **Heavy Vehicle Simulator (HVS) system**, the ORP delivers end-to-end **systems engineering** for tracking pavement wear under simulated traffic conditions. Through repeated verification via external encoder sensors and validation via a 24/7 HVS Crew, the ORP system collects accurate degradation metrics, creating highly detailed point clouds and digital maps of road surfaces. These insights are pivotal in optimizing roads for the state of California. The end goal of this project is to enable all road research labs in the world with the ability to accurately assess how their road design degrades and performs overtime.

<p align="center">
  <img src="https://github.com/user-attachments/assets/80c31641-4dbb-49a7-ad4e-a4b5ba6d7d86" alt="1-s2 0-S1996681417300354-gr6" width="500">
</p>
<div align="center"> Figure 1.0 (Heavy Vehicle Simulator) </div>


## How to Get Started
1. Clone the repository
```bash
git clone https://github.com/TETRA888/Profilometer.git
cd Profilometer
```
2. Set up the hardware as described in the [Hardware Design section](#mechanical-frame-cad-design-overview)
* [Parts list](https://docs.google.com/spreadsheets/d/1ZoPqY9_Fw6rnbfQ8UKPL65L5WncEJa40W8i2KiA_dJQ/edit?gid=0#gid=0)

## Sofware Design

# <div align ="center"> Software Design Overview/Simple Gui 1.1</div>
<p align="center">
 <img src = "https://github.com/user-attachments/assets/fe528e88-6bc0-46dd-bb4b-45c65ca7cced" alt="1-s2 0-S1996681417300354-gr6">
 <img src = "https://github.com/user-attachments/assets/32ccac83-22e0-466b-923a-43ae7843b1e9" alt="1-s2 0-S1996681417300354-gr6">
</p>



## Hardware Design

# <div align ="center"> High-Level Electrical System Design/Schematic </div>

<div style="display: flex; justify-content: center; gap: 20px;">
  <img src="https://github.com/user-attachments/assets/d2793204-312c-4bae-87c7-b930093b7640" alt="System Design" width="200">
  <img src="https://github.com/user-attachments/assets/e47172af-e0ef-41ed-a5eb-c84660c2853c" alt="Electrical Schematic" width="200">
</div>


# Core Team
- [**Asad Melibaev**](https://github.com/TETRA888)
- [**Adam Wu**](https://github.com/adamhwu)



# <div align ="center"> Assembled Data Acquisition Electronics Overview </div>
![image](https://github.com/user-attachments/assets/57f5ed04-3421-409e-b34d-de18fb0aa7bf)
### <div align="center"> Figure 2.2 (Assembled electronics) </div>



### <div align="center"> Figure 3.0 (Data flow) </div>


## Simple Gui for version 1.1
![unnamed](https://github.com/user-attachments/assets/32ccac83-22e0-466b-923a-43ae7843b1e9)


# <div align ="center"> Mechanical Frame CAD Design Overview </div>
![370409415-1df8b744-70b0-4bfa-a11d-afa3a9b27c9c](https://github.com/user-attachments/assets/2b34529f-097a-49ef-b5af-636d91c5e30e)
### <div align = "Center" > Figure 4.0 (3D Blender Render) </div>

## Assembled Sample Frame
![image](https://github.com/user-attachments/assets/19168a9b-73d9-4032-93db-c142c46b60a5)
### <div align = "Center" > Figure 4.1 (2nd Design Iteration Of Frame) </div>



# Documentation and Implementation:
1. [Wiki](https://github.com/TETRA888/Profilometer/wiki)

## Future Work and Integrating OpenUSD for more efficient road degradation tracking in California
To integrate ORP’s point cloud data into OpenUSD, the UsdGeomPoints schema will be used to represent sub-millimeter road surface deformations. Each point will include attributes like position (X,Y,ZX,Y,Z), normals, color, and custom degradation metrics. The data pipeline starts with preprocessing raw outputs from ORP (e.g., .txt, .ply), which are then converted into USD files using Python’s USD libraries. Surface reconstruction algorithms, such as Poisson reconstruction, can transform point clouds into detailed meshes stored as UsdGeomMesh. Time-series visualization of road degradation over simulated traffic cycles will leverage USD’s animation capabilities, enabling dynamic analysis. Once generated, USD files can be validated with tools like USDView or NVIDIA Omniverse for real-time visualization and shared for collaborative research. This pipeline enables scalable, accurate modeling of road performance, paving the way for global adoption in road research. Furthermore, OpenUSD could perhaps be even used to generate synthetic data. A similar usecase for generating synthetic data for license plate detection using OpenUSD is showcased here:https://developer.nvidia.com/blog/developing-smart-city-traffic-management-systems-with-openusd-and-synthetic-data/

![image](https://github.com/user-attachments/assets/0236c53d-0974-4850-a30e-3736df479050)


# Profiler from 30 years ago:


### <div align = "Center" > Figure 5.0 (The First Profiler) </div>
