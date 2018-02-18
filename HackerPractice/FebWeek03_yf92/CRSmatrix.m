function matrixA = CRSmatrix(value, rowPtr, colInd)
    matrixA = zeros(max(colInd+1),max(colInd+1));
    a=1;
    for i=2:1:max(colInd+1)
        for j=1:1:rowPtr(i)
            A(i,j)=value(a);
            a=a+1;
        end
    end
end