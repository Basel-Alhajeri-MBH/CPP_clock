/**
 * [C](Basel Alhajri) -> MBH {};
 */

#include <iostream>
#include <thread>
#include <chrono>
#include <ctime>
#include <string>

#ifdef _WIN32

#define ISWIN true

#else

#define ISWIN false

#endif

auto await = [](const int ms) -> void {
	using std::this_thread::sleep_for;
	using std::chrono::milliseconds;
	sleep_for(milliseconds(ms));
};

const int width = 3 + 3 * 7;

typedef std::time_t date;
typedef std::tm tm;
typedef std::string str;

std::ostream &log = std::cout;
std::ostream &(*line)(std::ostream &) = std::endl;

void init();

int main()
{
	std::thread trd(init);
	trd.join();
}

inline void clr()
{
	if (!ISWIN)
		system("clear");
	else
		system("cls");
}

str str_2digs(int num)
{
	return num < 10 ? "0" + std::to_string(num) : std::to_string(num);
}

template <typename S, typename E, typename... N>
constexpr void draw_digital_clock(S s, E e, N... args)
{
	const int x = 3, y = sizeof...(N), z = 2.;
	int ***data_nums = new int **[x];
	int graph_data[10][x] = {{121, 313, 323}, {111, 113, 113}, {121, 123, 321}, {121, 123, 123}, {111, 323, 113}, {121, 321, 123}, {121, 321, 323}, {121, 113, 113}, {121, 323, 323}, {121, 323, 123}};
	//int size = sizeof...(N);
	int $i = 0;
	for (int i = 0; i < x; i++) data_nums[i] = new int *[y];
	auto generate = [&$i, data_nums, graph_data](auto n) {
		str nums = str_2digs(n);
		//data_nums[$i] = new int *[size * 3];
		for (int i = 0; i < x; i++)
		for (int j = $i; j < y; j++)
		{
			data_nums[i][j] = new int[z];
			for (int k = 0; k < z; k++)
			{
				int num = std::stoi(nums.substr(k, k + 1));
				data_nums[i][j][k] = graph_data[num][i];
			}
		}
		$i++;
	};
	auto decode = [](int num) -> str {
		str from = std::to_string(num) , to = "";
		char c[3] = {' ', '_', '|'};
		for (int i = 0; i < 3; i++) {
			to += c[from[i] - '1'];
		}
		return to;
	};
	(generate(args), ...);
	log << line;
	log << ' ' << str(width, '_') << line;
	for (int i = 0; i < x; i++)
	{
		log << s;
		for (int j = 0; j < y; j++) {
			for (int k = 0; k < z; k++) {
				log << decode(data_nums[i][j][k]);
			}
			if (i != 0 && j != y - 1) log << '.';
			else log << ' ';
		}
		log << e << line;
	}
	log << s << str(width/4 - 2, ' ') << str(width/2, '_') << str(width/4 - 1, ' ') << e << line;
	log << s << str(width - 3, ' ') << e << line;
	log << str(width + 2, '|');
}

void init()
{
	date time = std::time(nullptr);
	tm *to_local = std::localtime(&time);
	char *format = std::ctime(&time);
	//date time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

	clr();
	draw_digital_clock("|| ", " |", to_local->tm_hour, to_local->tm_min, to_local->tm_sec);
	//f();
	log << line;
	//log << format;
	await(900);
	init();
}

