Assignment2: Modular Testing in Sparse Matrix Solvers
Author: Yazhi Fan(yf92) and Yijia Chen(yc2366)
Date: 03/15/2018
Platform: CodeLite on mac OS

please change file path in the main.cpp
Organization:

                main.cpp
                   /\
                  /  \
                 /    \
         Jacobi.cpp  modular_tests.cpp
               /           |
	            /            |
	           /             |
        norms.cpp   Jacobi_operations.cpp
                  			   |
	                   		   |
                    crs_operations.cpp
                           |
			                     |
                        list.cpp

