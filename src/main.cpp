#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <cctype>
using namespace std;

class Database
{
public:
    string handle(const string &line);

private:
    unordered_map<string, string> db;
};

int main()
{
    Database db;

    while (true)
    {
        string text;
        cout << "> ";
        if (!(getline(cin, text)))
        {
            break;
        }
        cout << db.handle(text) << endl;
    }
    return 0;
}

string Database::handle(const string &line)
{
    istringstream stream(line);
    string command;

    if (!(stream >> command))
    {
        return "-ERR empty command";
    }
    else
    {
        for (char &c : command)
        {
            c = toupper(static_cast<unsigned char>(c));
        }
        if (command == "SET")
        {
            string key, value;

            if (stream >> key)
            {
                stream >> ws;
                getline(stream, value);
                if (value.empty())
                {
                    return "-ERR syntax error (missing value)";
                }
                else
                {
                    db[key] = value;
                    return "OK";
                }
            }
            else
            {
                return "-ERR syntax error (missing key and value)";
            }
        }
        else if (command == "GET")
        {
            string key;
            if (stream >> key)
            {
                auto it = db.find(key);
                if (it != db.end())
                {
                    return it->second;
                }
                else
                {
                    return "(nil)";
                }
            }
            else
            {
                return "-ERR syntax error (missing key)";
            }
        }
        else if (command == "DEL")
        {
            string key;
            if (stream >> key)
            {
                auto it = db.find(key);
                if (it != db.end())
                {
                    db.erase(it);
                    return "1";
                }
                else
                {
                    return "0";
                }
            }
            else
            {
                return "-ERR syntax error (missing key)";
            }
        }
        else
        {
            return "-ERR unknown command";
        }
    }
}
