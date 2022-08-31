#include <iostream>
#include <vector> //  Dynamic Array
#include <string>
#include <unordered_map> // Dict in python
#include <fstream> 
#include <filesystem> // File size
#include <chrono> // Time count
using namespace std;

void encoding(string file_name, string enc_file)
{
    unordered_map<string, int> table; // Dict string->code
    string p = "", c = "";
    ifstream r_file(file_name);
    int code = 256;
    vector<int> output_code;
    for (int i = 0; i <= 255; i++) // Fill default table
    {
        string ch = "";
        ch += char(i);
        table[ch] = i;
    }
    p += r_file.get(); // LZW process
    while (r_file.peek() != EOF)
    {
        c = r_file.get();
        if (table.find(p + c) != table.end())
        {
            p = p + c;
        }
        else
        {
            output_code.push_back(table[p]);
            table[p + c] = code;
            code++;
            p = c;
        }
        c = "";
    }
    output_code.push_back(table[p]);
    r_file.close();
    ofstream code_out(enc_file);
    for (int i = 0; i < output_code.size(); i++)
    {
        code_out << output_code[i] << " ";
    }
    code_out.close();
}

void decoding(string dec_file, string out_file)
{
    vector<int> codes;                // Encoding codes
    unordered_map<int, string> table; // Dict code->string
    ifstream r_codes(dec_file);
    while (!r_codes.eof())
    {
        int num;
        while (r_codes >> num)
        {
            codes.push_back(num);
        }
    }
    r_codes.close();
    ofstream out(out_file);
    for (int i = 0; i <= 255; i++)
    {
        string ch = "";
        ch += char(i);
        table[i] = ch;
    }
    int old = codes[0], n;
    string s = table[old];
    string c = "";
    c += s[0];
    out << s;
    int count = 256;
    for (int i = 0; i < codes.size() - 1; i++)
    {
        n = codes[i + 1];
        if (table.find(n) == table.end())
        {
            s = table[old];
            s = s + c;
        }
        else
        {
            s = table[n];
        }
        out << s;
        c = "";
        c += s[0];
        table[count] = table[old] + c;
        count++;
        old = n;
    }
    out.close();
}
int main(int argc, char *argv[])
{
    int command;
    cout << "Select option:\n1 - Encoding\n2 - Decoding\n";
    string first_file, second_file;
    cin >> command;
    if (command == 1)
    {
        cout << "Print input file: ";
        cin >> first_file;
        cout << "Print output file: ";
        cin >> second_file;
        auto t1 = std::chrono::high_resolution_clock::now();
        encoding(first_file, second_file);
        auto t2 = std::chrono::high_resolution_clock::now();
        cout << "Data compression ratio: " << double(std::filesystem::file_size(second_file)) / double(std::filesystem::file_size(first_file)) << "\n";
        cout << "Execution time: " << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count() << "ms\n";
    }
    if (command == 2)
    {
        cout << "Print input file: ";
        cin >> first_file;
        cout << "Print output file: ";
        cin >> second_file;
        auto t1 = std::chrono::high_resolution_clock::now();
        decoding(first_file, second_file);
        auto t2 = std::chrono::high_resolution_clock::now();
        cout << "Execution time: " << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count() << "ms\n";
    }
    return 0;
}
