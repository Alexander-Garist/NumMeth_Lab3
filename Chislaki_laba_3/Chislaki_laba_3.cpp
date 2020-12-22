#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
	setlocale(LC_ALL, "rus");
	const double Tau_Max = 0.1; //максимальный шаг
	double U[3] = { 1 , 1, 1 };// начальные условия функций u1, u2, u3
	int T = 1; //[0,1]
	const double eps = 1e-3;//допустимая погрешность

	double vector_f[3] = {0}; //вектор f

	double Tau[3] = { 0 }; // варианты шагов	
	double Tau_Min = 0; // шаг
	double t = 0; // аргумент

	int counter_iteration = 0;

	for (double a = 1, k = 2; (a <= 2)&&(k <= 3); a += 0.25, k += 0.25)
	{
		t = 0;
		cout << "При a = " << a << " и k = " << k << endl;
		cout << "Номер итерации:" << "           t" << "        U1" << "        U2" << "        U3" << endl;
		while (t < T)
		{
			//вычисление вектора f
			vector_f[0] = (k - a)*U[1] * U[2] / a;
			vector_f[1] = (a + k)* U[0] * U[2] / k;
			vector_f[2] = (a - k) * U[0] * U[1] / a;

			for (int i = 0; i < 3; i++)
			{
				Tau[i] = eps / (abs(vector_f[i]) + eps / Tau_Max);
			}
			Tau_Min = Tau[0];//выбор наименьшего шага
			if (Tau[1] < Tau_Min) Tau_Min = Tau[1];
			if (Tau[2] < Tau_Min) Tau_Min = Tau[2];

			for (int i = 0; i < 3; i++)
			{
				U[i] += Tau_Min * vector_f[i];
			}

			t += Tau_Min;

			counter_iteration++;

			cout << setw(15) << counter_iteration << setw(12) << t << setw(10) << U[0] << setw(10) << U[1] << setw(10) << U[2] << endl;
		}
	}
}