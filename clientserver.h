// clientserver.h : включаемый файл для стандартных системных включаемых файлов
// или включаемые файлы для конкретного проекта.


#include <iostream>
#include <vector>
#pragma once
#include "server.cpp"
#include "constants.h"
#include "client.cpp"
#include <thread>
void getport(int argc, char** argv) {
	int res = 0;
	for (int i = 0; i < argc; ++i) {
		size_t j = 0;
		while (argv[i][j] >= '0' && argv[i][j] <= '9' && j < sizeof(argv[i])) {
			res *= 10;
			res += (static_cast<int>(argv[i][j]) - static_cast<int>('0'));
			++j;
		}
		parameters::arg.push_back(res);
		res = 0;
	}
	parameters::port = parameters::arg[0];
	return;
}
// TODO: установите здесь ссылки на дополнительные заголовки, требующиеся для программы.
