#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {}
BitcoinExchange::BitcoinExchange(const BitcoinExchange& copy) { *this = copy; }
BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other) {
    if(this != &other) {
        _rates = other._rates;
    }
    return (*this);
}
BitcoinExchange::~BitcoinExchange() {}

void BitcoinExchange::fillRates(const std::string& file)
{
    std::ifstream inf(file.c_str());
    if(!inf)
        throw std::invalid_argument("Error: cannot open file");
    
    std::string line;
    std::string date;
    std::string str_value;
    double d_value;
    std::getline(inf, line);
    while(std::getline(inf, line)) 
    {
        std::istringstream line_stream(line);
        std::getline(line_stream, date, ',');
        std::getline(line_stream, str_value);
        d_value = strtod(str_value.c_str(), NULL);
        if(errno != 0)
            throw std::out_of_range("Error: value out of range in data.csv");
        _rates[date] = d_value;
    }
}   

double BitcoinExchange::findRateForDate(const std::string& date) const
{
    std::map<std::string, double>::const_iterator it;

    it = _rates.upper_bound(date);
    if(it == _rates.begin())
        std::cerr << "Error: no rate available before this date => " << date << std::endl;
    --it;
    return(it->second);
}

static std::string checkFileContent(std::ifstream& file) {
    std::string line;
    if (!std::getline(file, line)) {
        throw std::invalid_argument("Error: cannot open file");
    } 
    return(line);
}

static bool isValidDate(const std::string& date) {
    if(date.size() != 10)
        return(false);
    if(date[4] != '-'  && date[7] != '-')
        return(false);

    int year, month, day;
    std::istringstream s_year(date.substr(0, 4));
    std::istringstream s_month(date.substr(5, 2));
    std::istringstream s_day(date.substr(8, 2));
    s_year >> year;
    s_month >> month;
    s_day >> day;
    if(year > 2025 || month < 1 || month > 12)
        return (false);

    int days_by_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if(year % 4 == 0 && month == 2)
        days_by_month[1] = 29;

    if(day < 1 || day > days_by_month[month - 1])
        return (false);
    return(true);
}

static bool isValidValue(const std::string& str_value, double& value)
{
    std::istringstream v_stream(str_value);
    v_stream >> value;
    if(v_stream.fail()) 
        std::cerr << "Error: bad value => " << str_value << std::endl;
    else if(value < 0) 
        std::cerr << "Error: not a positive number." << std::endl;
    else if(value > 1000) 
        std::cerr << "Error: too large a number." << std::endl;
    else
        return (true);
    return (false);

}

void BitcoinExchange::parseLine(std::string& line) const {
    line.erase(std::remove(line.begin(), line.end(), ' '), line.end());
    std::istringstream line_stream(line);
    std::string date;
    std::string str_value;

    if(!std::getline(line_stream, date, '|') 
        || line_stream.eof() == true 
        || !std::getline(line_stream, str_value))
        {
            std::cerr << "Error: bad input => " << line << std::endl;
            return;
        }

    if(isValidDate(date) == false)
    {
        std::cerr << "Error: invalid date => " << line << std::endl;
        return;
    }

    double value;

    if(isValidValue(str_value, value) == false)
        return;

    double rate = findRateForDate(date);
    std::cout << date << " => " << value << " = " 
        << (value * rate) << std::endl;
}

void BitcoinExchange::manageInput(const std::string& input_file) const
{
    std::ifstream file(input_file.c_str());
    if(!file)
        throw std::invalid_argument("Error: cannot open file");

    std::string line = checkFileContent(file);
    if(line != "date | value")
        this->parseLine(line);
    while(std::getline(file, line)) 
        parseLine(line);
}
