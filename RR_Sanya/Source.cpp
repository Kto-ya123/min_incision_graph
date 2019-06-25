#include<set>
#include<tuple>
#include<vector>
#include<fstream>
#include<conio.h>
#include<iostream>

using namespace std;

int main()
{
	ifstream fin("in.txt"); // Ввод из файла с именем in в формате вершина_вершина_вес   где _ - пробел, первая строка кол-во ребёр
	ofstream fout("out.txt"); // Вывод в файл с именем out в формате: первая строка общий вес разреза, последующие строки рёбра разреза;
	vector<pair<pair<int, int>, int>> graph; //Список инцидентности
	vector<int> value_versh; // Вектор отвечающий за вес каждой вершины
	set<int> versh_raz; // Подмножество полученное в результате разреза
	int sum_value = 0; // Переменная - суммарный вес разреза
	int N; // кол-во рёбер в графе

	fin >> N;
	{                 // Заполнение списка инцидентности
		int size = N;
		while (size)
		{
			int first_v; // первая вершина в ребре
			int second_v;//вторая вершина в ребре
			int value;//вес ребра
			fin >> first_v;
			fin >> second_v;
			fin >> value;
			graph.push_back(pair<pair<int, int>, int>(pair<int, int>(first_v, second_v), value));//добавление ребра в список инцидентности
			size--;
		}
	}
	{
		value_versh.push_back(0); // добавление нулевой вершины, чтобы общий отсчёт вершины шёл с единицы
		for(int i(1), value(0);  ;i++, value = 0) // заполнение веса вершин
		{
			for (int j(0); j < graph.size(); j++)
			{
				if (graph[j].first.first == i || graph[j].first.second == i) // если веришна принадлжежит ребру
					value += graph[j].second;   // то добавить вес вершине
			}
			if (value == 0) //если вес равен нулю, значит мы искали вес несуществующей вершины, значит прошлая вершина была последняя и поэтому 
				break; //выходим из цикла
							value_versh.push_back(value); //иначе добавляем вес вершины в вектор, номер веришины это её индекс в векторе

		} 
	}
	{
		
		do{
			int max = 0;
			for (int i(1); i < value_versh.size(); i++) {
				if (value_versh[i] > value_versh[max])			//ищем веришну с максимальным весом
					max = i;
			}
			if (value_versh[max] > 0) // если вес вершины с максимальным весом больше нуля, значит работаем, иначе выходим из цикла
			{
				sum_value += value_versh[max];   //прибавляем вес веришны в итоговый вес
				value_versh[max] = 0;			//обнуляем вес вершины, чтобы не взять её снова, 
				versh_raz.insert(max);      //но и не удаляем, чтобы не сбить порядковые номера оставшихся вершин и добавляем эту вершину в множество
				for (int i(0); i < graph.size(); i++) //ищём рёбра инцдентные вершине с максимальным весом
				{									//Чтобы отнять эти веса у вершин смежных с данной
					if (graph[i].first.first == max)
					{									//отнимаем дважды, один раз потому что при добавлении вершины данное ребро не пойдёт в счёт
						value_versh[graph[i].first.second] -= graph[i].second*2;  // а второй раз потому что если мы добавим вершину смежную с ней
					}														// то и вес это ребра тоже пропадёт из суммарного веса разреза
								//здесь две условных конструкции потому что веришна может стоять как на первом месте ребра так и на втором
					if (graph[i].first.second == max)	//поэтому вторая конструкция такая-же только так сказать зеркальная
					{
						value_versh[graph[i].first.first] -= graph[i].second * 2;
					}
				}

			}
			else break;
		} while (1);
	} 
	fout << sum_value << endl; //выводим суммарный вес разреза
	for (const int& a : versh_raz)
	{
		for (int i(0); i < graph.size(); i++) // выводим все рёбра относящиеся к разрезу
		{
			if (graph[i].first.first == a && versh_raz.find(graph[i].first.second) == versh_raz.end()) //если вершина стоит на первом месте ребра, значит проверяем,
				fout << graph[i].first.first << ' ' << graph[i].first.second << ' ' << graph[i].second << endl; //чтобы вершина на втором месте не относилась к тому же множеству
			if (graph[i].first.second == a && versh_raz.find(graph[i].first.first) == versh_raz.end())//если вершина стоит на втором месте ребра, значит проверяем,
				fout << graph[i].first.first << ' ' << graph[i].first.second << ' ' << graph[i].second << endl; //чтобы вершина на первом месте не относилась к тому же множеству
		}
	}



	_getch();
	return 0;
}