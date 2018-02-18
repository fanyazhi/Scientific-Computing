
b = [199; 197];
e = 10E-2;
while e >=10E-9
    A = [100 99; 99 98.01-e];
    x=fullMatrixSolver(A, b);
    disp(x)
    e=e/10;
end