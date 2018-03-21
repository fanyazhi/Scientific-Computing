#include <iostream>
#define n 100
// system will break if n is too big like 50,000
    using namespace std;
    class matrix3
    {
        int a[n][n],b[n][n],c[n][n],d[n][n],x,y,i,j,k,l;
        public :
            void values();
            void rowPermute(int k, int l);
            void rowScale(int k, int l, double b);
            void productAx();
    };
    void matrix3::values()
    {
        cout << "Enter the rows   "; cin >> x;
        cout << "Enter the columns   "; cin >> y;
        cout << "Enter elements of first matrix\n\n";
        for (i=1; i<=x; i++){
            for ( j=1; j<=y; j++){
                cin >> a[i][j];
            }
        }
        cout << "input -1 if not need the vector, 0 if needed x\n\n";
        cin >> k;
        if(k==-1){
        	for (i=1; i<=x; i++){
            	for (j=1; j<=y; j++){
                c[i][j] = 0;
            	}
        	}
		}
        else {
        	cout << "Enter elements of the vector\n\n";//c[1][y] is a vector with dimention 1*y
        	for (i=1; i<=1; i++){
            	for (j=1; j<=y; j++){
                cin >> c[i][j];
            	}
       		}        	
		}        
    }
    
    // Switch row[i] and row[j] for matrix A and vector x
	void matrix3::rowPermute(int k, int l){
		cout << "the matrix after permuting is\n";
		for (i=1; i<=x; i++){   
            if(i==k){
            	for( j=1; j<=y; j++){
            		b[i][j] = a[l][j];
            		cout << b[i][j] << " ";
				}
			}
			else if(i==l){
				for( j=1; j<=y; j++){
					b[i][j] = a[k][j];
					cout << b[i][j] << " ";
				}
			}
			else{
				for ( j=1; j<=y; j++){
               		b[i][j] = a[i][j];
                	cout << b[i][j] << " ";
            	}	
            }
            cout << endl;
        }			
	} 
	
	// Add q*row[k] to row[l] for matrix A and vector x
	void matrix3::rowScale(int k, int l, double q){
		cout << "the matrix after scaling is\n";
		for (i=1; i<=x; i++ ){   
            if(i==l){
            	for( j=1; j<=y; j++){
            		b[i][j] = q*a[k][j]+a[i][j];
            		cout << b[i][j] << " ";
				}
			}
			else{
				for ( j=1; j<=y; j++){
                	b[i][j] = a[i][j];
                	cout << b[i][j] << " ";
            	}	
            }
            cout << endl;
        }		
	}
    // Return the product of Ax = b
	void matrix3::productAx(){
		for( j=1; j<=y; j++){
			d[1][j] = 0;
		}
		cout << "Product of Ax is b=\n";
		for( i=1; i<=x; i++){
			for( j=1; j<=y; j++){
				d[1][i] += a[i][j]*c[1][j];
			}
			cout << d[1][i] << endl; 
		}	
	}
	
    int main()
    {
        int input,k,l;
        double q;
        char ch;    
        matrix3 m;
        m.values();
        do
         {
        cout << "Enter your choice\n";
        cout << " 1. Row permute\n" << " 2. Row scaling\n" << " 3. Vector product\n";
        cin >> input;
        switch (input)
        {
            case 1:
            	cout << "Enter two row indecs,Switch row[k] and row[l] for matrix A\n";
            	cin >> k;
            	cin >> l;
                m.rowPermute(k, l);
                break;

            case 2:
            	cout << "Add q*row[k] to row[l],order:k,l,q\n";
            	cin >> k;
            	cin >> l;
            	cin >> q;
                m.rowScale(k,l,q);
                break;

            case 3:
            	cout << "Return the product of Ax\n";
                m.productAx();
                break;
        }
        cout << "\nDo another y/n?";
        cin >> ch;
        }
        while (ch!= 'n');
        cout << "\n";
        system ("pause");
    return 0;
    }
