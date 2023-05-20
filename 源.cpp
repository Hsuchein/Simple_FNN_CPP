#include <iostream>
#include <ctime>
#include <cmath>
using namespace std;

	const int input_num = 1;//输入数目
	const int output_num = 1;//输出数目
	const int hidden_num = 10;//隐层神经元数目
	const float yita = 0.25;//学习率

	const int train_step_max = 1000;//最大迭代步数
	const int limit_gradient = 0.1;//最小梯度限度

void decrease(float& x,float& y)
	{
		x =x+ y;
     }
float sigmod(float x)
{
	return (float)1 / (1 + exp(-x));
}

	class neuron
	{
	public:
		float *w=new float [output_num * hidden_num];
		float v[input_num * hidden_num];
		float theta[output_num];
		float gamma[hidden_num];

			float* alpha = new float[hidden_num];
			float* beta = new float[output_num];
			float output_predict[output_num];

			float* b = new float[hidden_num];//对alpha的sigmoid

		void num_giving_all()
		{
			cout << "Loading the Random Num...\n\n";
			//w赋值
			int i = 0, j = 0;
			for (i; i < output_num; i++)
			{
				int j = 0;
				for (j; j < hidden_num; j++)
				{
					w[i * hidden_num + j] = rand() % 3 - 1;
					cout << "w(" << i+1<<"," << j + 1 << ")=" << w[i * hidden_num + j] << "  ";
				}
			}
			cout << endl<<endl;
			cout << "w num_giving is compeleted.\n\n";

			//v赋值
			i = 0, j = 0;
			for (i; i < hidden_num; i++)
			{
				j = 0;
				for (j; j <input_num; j++)
				{
					v[i * input_num + j] = rand() % 3 - 1;
					cout << "v(" << i +1<<"," << j + 1 << ")=" << v[i * input_num + j] << "  ";
				}
			}
			cout << endl<<endl;
			cout << "v num_giving is compeleted.\n\n";

			//gamma赋值
			i = 0, j = 0;
			for (i; i < hidden_num; i++)
			{
					gamma[i] = rand() % 3 - 1;
					cout << "gamma" << i + 1<< "=" << gamma[i] << "  ";
			}
			cout << endl<<endl;
			cout << "gamma num_giving is compeleted.\n\n";

			//theta赋值
			i = 0, j = 0;
			for (i; i < output_num; i++)
			{
				theta[i] = rand() % 3 - 1;
				cout << "theta" << i + 1 << "=" << theta[i] << "  ";
			}
			cout << endl<<endl;
			cout << "theta num_giving is compeleted.\n\n";

		}

		void data_trans(float *input)
		{

			cout << endl << "Doing the Data_Trans Mission now.\n\n";
			//alpha generate
			int i = 0, j;
			for (i;i<hidden_num;i++)
			{
				alpha[i] = 0;
				j = 0;
				for (j;j<input_num;j++)
				{
					alpha[i] += v[i * input_num + j]*input[j];
				}
				cout << "alpha[" << i << "]=" << alpha[i]<<" ";
			}
			cout << endl << endl << "alpha generation is compeleted.\n\n";

			//beta generate
			i = 0, j;
			for (i; i < output_num; i++)
			{
				beta[i] = 0;
				j = 0;
				for (j; j < hidden_num; j++)
				{
					b[j] = sigmod(alpha[j] - gamma[j]);
					beta[i] +=w[i*hidden_num+j]*b[j];
				}
				cout << "beta[" << i << "]=" << beta[i] << " ";

			}
			cout << endl << endl << "beta generation is compeleted.\n\n";

			//output_predict generate
				j = 0;
				
				for (j; j < output_num; j++)
				{
					output_predict[j] = 0;
					output_predict[j] += sigmod(beta[j] - theta[j]);
					cout << "output_predict[" << j << "]=" << output_predict[j] << " ";
				}
			cout << endl << endl << "output_predict generation is compeleted.\n\n";



		}

		void gradient_descent(float *output_standard,float *input)
		{
        //decrease step following:
		float *delta_w=new float [output_num * hidden_num];
		float *delta_v=new float[input_num * hidden_num];
		float *delta_theta=new float[output_num];
		float *delta_gamma=new float[hidden_num];
		
			cout <<endl<< "Doing Gradient_Descent Mission Now.\n";

		    // g process
			int i, j;
			float *g=new float [output_num];
			cout << endl << "Calculating gradient(g) Now.\n";
			for (i = 0; i < output_num; i++)
			{
				g[i] = output_predict[i] * (1 - output_predict[i]) * (output_standard[i] - output_predict[i]);
				cout<< "g=" << g[i] << endl;
			}

			//e process
			float* e = new float[hidden_num];
			float sum;
			cout << endl << "Calculating gradient(e) Now.\n";
			for (i = 0; i < hidden_num; i++)
			{
				e[i] = b[i] * (1 - b[i]);
				sum = 0;
				for (j = 0; j < output_num; j++)
				{
					sum += w[j*hidden_num+i] * g[j];
				}
				e[i] = sum * e[i];
				cout << "e=" << e[i] << endl;
			}

			//delta w process
			cout << endl << "Calculating Delta_w and Decreasing w Now.\n";
			for (i = 0; i < output_num; i++)
			{
				for (j = 0; j < hidden_num; j++)
				{
					delta_w[i*hidden_num+j] = yita * g[i] * b[j];
					decrease(w[i * hidden_num + j], delta_w[i * hidden_num + j]);
					cout << "new_w(" << i+1 << "," << j+1 << ")=" << w[i * hidden_num + j]<<endl;
				}
				
			}
			delete[] delta_w;

			//delta theta process
			cout << endl << "Calculating Delta_w and Decreasing theta Now.\n";
				for (i = 0; i < output_num; i++)
				{
					delta_theta[i] =(-1)* yita * g[i];
					decrease(theta[i], delta_theta[i]);
					cout << "new_theta(" << i + 1 << ")=" << delta_theta[i] << endl;
				}
				delete[] delta_theta;
				delete[] g;

            //delta gamma process
				cout << endl << "Calculating Delta_w and Decreasing gamma Now.\n";
				for (i = 0; i < hidden_num; i++)
				{
					delta_gamma[i] = (-1) * yita * e[i];
					decrease(gamma[i], delta_gamma[i]);
					cout << "new_gamma(" << i + 1 << ")=" << delta_gamma[i] << endl;
				}
				delete[] delta_gamma;

				//delta v process
				cout << endl << "Calculating Delta_w and Decreasing w Now.\n";
				for (i = 0; i < hidden_num; i++)
				{
					for (j = 0; j < input_num; j++)
					{
						delta_v[i * input_num + j] = yita * e[i] * input[j];
						decrease(v[i * input_num + j], delta_v[i * input_num + j]);
						cout << "new_v(" << i + 1 << "," << j + 1 << ")=" << w[i * input_num + j] << endl;
					}

				}



			delete[] e;
			delete [] delta_v;
	    }
    			

	};




int main()
{
    srand(unsigned(time(0)));

	float *input = new float [input_num];
	float *output_standard=new float [output_num];
	float x;
	int i;


	    neuron func;
		func.num_giving_all();

	

	for (i=1;i<= train_step_max;i++)
	{
		cout << "\n\nThe " << i << " Cycle Now\n\n";
		x = (rand() % 10 -20)/1.33;
        input[0] = x;
		output_standard[0] = 0.5*x;

		cout << "\nx=" << x<<endl;
		func.data_trans(input);

		func.gradient_descent(output_standard,input);
		

     }
	float *real_input = new float[input_num];
	real_input[0] = 0.25;
	func.data_trans(real_input);
	
	    




		cin.get();
	return 0;
}