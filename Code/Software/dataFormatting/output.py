import csv

dataOne = {"Time": "1:14", "Date": "1/2/25"}
dataTwo = {"Operator": "Adam/Asad", "Tire Pressure": "1000 psi", "Wheel Type": "Round"}
dataThree = [{"Distance": 100, "Water Flow": 43}, {"Speed": 23, "Water Flow": 198}, {"Distance": -12, "Water Flow": -.123}]
headData = [{'Name': 'X', '0': 0, '1': 500, '2': 1000, '5': 71, '8': 230},{'Name': 'Y', '1': 0, '2': 500, '3': 1000, '5': 71, '12': 230}]

def initFileArr(inputFile): #  reads template file and returns array containing rows of template file
    fileArr = []
    with open(inputFile, mode="r", newline="") as file:  # reading head template file, populating a head with the header values
        reader = csv.reader(file, delimiter=',')
        for line in reader:
            proLine = []
            for item in line:
                if item != '':
                    proLine.append(item)
            fileArr.append(proLine)
    return fileArr

def writeHead(fileArr, headData, outputFile):  # input fileArr array, headData dict with actual data, and output csv file 
    with open(outputFile, mode="w", newline="") as file:
        writer = csv.writer(file, delimiter=',')
        writer.writerow(fileArr[0])

        writer = csv.DictWriter(file, fieldnames=fileArr[1], restval="N/A")   # default value is N/A
        # fileArr[1] is the list containing headers of data in this specific template 
        writer.writeheader()
        writer.writerows(headData)

def writeMetaData(fileArr, metaDataOne, metaDataTwo, outputFile):  # input fileArr array, two rows of meta data as separate lists, and output file
    with open(outputFile, mode="a", newline="") as file:
        writer = csv.DictWriter(file, fieldnames=fileArr[5], restval="N/A")    # metadata section is rows 5-8 of template
        writer.writeheader()
        writer.writerow(metaDataOne)
        writer.fieldnames=fileArr[7] 
        writer.writeheader()
        writer.writerow(metaDataTwo)

def writeLaserData(fileArr, laserData, outputFile):
    with open(outputFile, mode="a", newline="") as file:
        writer = csv.DictWriter(file, fieldnames=fileArr[9], restval="N/A")    # metadata section is rows 5-8 of template
        writer.writeheader()
        writer.writerows(laserData)
        

output_file = "output.csv"
#writeMetaData(output_file)
fileArr = initFileArr("outputTemplate.csv")
writeHead(fileArr, headData, output_file)
writeMetaData(fileArr, dataOne, dataTwo, output_file)
writeLaserData(fileArr, dataThree, output_file)

print("done")
