# Assignment2: Modular Testing in Sparse Matrix Solvers <br />
Author: Yazhi Fan(yf92) and Yijia Chen(yc2366) <br />
Date: 03/15/2018 <br />
Platform: CodeLite on mac OS <br />

please change file path in the main.cpp <br />
Organization: <br />

                main.cpp
                   /\
                  /  \
                 /    \
         Jacobi.cpp  modular_tests.cpp
               /           |
	         /              |
	        /               |
        norms.cpp   Jacobi_operations.cpp
                  	   |
	                   |
                    crs_operations.cpp
                           |
			       |
                        list.cpp

