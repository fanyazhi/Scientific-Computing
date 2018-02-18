value(12) = [1,2,3,4,5,6,7,8,9,10,11,12];
rowPtr(6) = [0,3,6,9,10,12];
colInd(12) =[0,1,4,0,1,2,1,2,4,3,0,4];
matrixA = CRSmatrix(value, rowPtr, colInd);