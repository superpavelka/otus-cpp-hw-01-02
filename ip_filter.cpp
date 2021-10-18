#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]

using ip_vec = std::vector<std::vector<std::string>>;
using ip = std::vector<std::string>;

ip split(const std::string &str, char d)
{
    std::vector<std::string> r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while(stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}

void print_ip_pool(ip_vec& ip_pool)
{
	for (auto ip = ip_pool.cbegin(); ip != ip_pool.cend(); ++ip)
	{
		for (auto ip_part = ip->cbegin(); ip_part != ip->cend(); ++ip_part)
		{
			if (ip_part != ip->cbegin())
			{
				std::cout << ".";
			}
			std::cout << *ip_part;
		}
		std::cout << std::endl;
	}
}

ip_vec filter(ip_vec& ip_pool, int first_byte, int second_byte = -1)
{
	ip_vec ip_pool_filtered;
	if (first_byte < 0)
		return ip_pool_filtered;
	for (auto ip_addr : ip_pool)
	{
		if (second_byte < 0 && first_byte == std::stoi(ip_addr[0]))
			ip_pool_filtered.push_back(ip_addr);
		else if (first_byte == std::stoi(ip_addr[0]) && second_byte == std::stoi(ip_addr[1]))
			ip_pool_filtered.push_back(ip_addr);
	}

	return ip_pool_filtered;
}

ip_vec filter_any(ip_vec& ip_pool, int any_byte)
{
	ip_vec ip_pool_filtered;
	if (any_byte < 0)
		return ip_pool_filtered;
	for (auto ip_addr : ip_pool)
	{
		if (any_byte == std::stoi(ip_addr[0]) || 
			any_byte == std::stoi(ip_addr[1]) ||
			any_byte == std::stoi(ip_addr[2]) ||
			any_byte == std::stoi(ip_addr[3])
			)
			ip_pool_filtered.push_back(ip_addr);
	}

	return ip_pool_filtered;
}

int main(int argc, char const *argv[])
{
	for (int i = 1; i < argc; i++)
		puts(argv[i]);
    try
    {
		ip_vec ip_pool;

        for(std::string line; std::getline(std::cin, line);)
        {
            ip v = split(line, '\t');
            ip_pool.push_back(split(v.at(0), '.'));
        }

        // reverse lexicographically sort
		
		sort(ip_pool.begin(), ip_pool.end(), [](const ip& a, const ip& b) {
			return (((std::stoi(a[0]) * 255 + std::stoi(a[1])) * 255 + std::stoi(a[2])) * 255 + std::stoi(a[3])) > 
				   (((std::stoi(b[0]) * 255 + std::stoi(b[1])) * 255 + std::stoi(b[2])) * 255 + std::stoi(b[3])); }
		);

		print_ip_pool(ip_pool);

        // 222.173.235.246
        // 222.130.177.64
        // 222.82.198.61
        // ...
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // filter by first byte and output
		ip_vec ip_pool_filtered = filter(ip_pool, 1);
		print_ip_pool(ip_pool_filtered);
		ip_pool_filtered.clear();
		
        // 1.231.69.33
        // 1.87.203.225
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // filter by first and second bytes and output
		ip_pool_filtered = filter(ip_pool, 46, 70);
		print_ip_pool(ip_pool_filtered);
		ip_pool_filtered.clear();		

        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76

        // filter by any byte and output
		ip_pool_filtered = filter_any(ip_pool, 46);
		print_ip_pool(ip_pool_filtered);
		ip_pool_filtered.clear();

        // 186.204.34.46
        // 186.46.222.194
        // 185.46.87.231
        // 185.46.86.132
        // 185.46.86.131
        // 185.46.86.131
        // 185.46.86.22
        // 185.46.85.204
        // 185.46.85.78
        // 68.46.218.208
        // 46.251.197.23
        // 46.223.254.56
        // 46.223.254.56
        // 46.182.19.219
        // 46.161.63.66
        // 46.161.61.51
        // 46.161.60.92
        // 46.161.60.35
        // 46.161.58.202
        // 46.161.56.241
        // 46.161.56.203
        // 46.161.56.174
        // 46.161.56.106
        // 46.161.56.106
        // 46.101.163.119
        // 46.101.127.145
        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76
        // 46.55.46.98
        // 46.49.43.85
        // 39.46.86.85
        // 5.189.203.46
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
