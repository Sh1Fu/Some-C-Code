#define _CRT_SECURE_NO_WARNINGS
#include <queue>
#include <vector>
#include <iostream>
#include <map>
#include <fstream>
#include <string>
#include <bitset>
#include <filesystem> // File size
#include <chrono>     // Time count
using namespace std;

struct Node
{
    char data;
    unsigned freq;
    unsigned new_code;
    string code;
    Node *left, *right;
    Node(char data, unsigned freq) // Init funcution(constructor kinda :>)
    {
        left = right = NULL;
        this->data = data;
        this->freq = freq;
    }
};

struct compare
{
    bool operator()(Node *l, Node *r)
    {
        return (l->freq > r->freq);
    }
};

void PrintCodes(Node *current_node, string result, map<char, string> *codes)
{
    if (!current_node)
        return; // End of Tree
    if (current_node->left == NULL && current_node->right == NULL) // Leaf
    {
        current_node->code = result;
        (*codes)[current_node->data] = result;
    }
    if (current_node->data == '+' && current_node->left != NULL && current_node->right != NULL)
    {
        PrintCodes(current_node->left, result + "0", codes);
        PrintCodes(current_node->right, result + "1", codes);
    }
}

struct Node *HuffmanTree(map<char, int> symbols, int count_of_diff_symbols)
{
    struct Node *left, *right, *top;                      // Init "structure" of Tree
    priority_queue<Node *, vector<Node *>, compare> heap; // Building Huffman Tree thanks to compare freq of nodes, put nodes in priority_queue
    map<char, int>::iterator it;
    // Fill the Huffman tree with Nodes

    for (it = symbols.begin(); it != symbols.end(); it++)
    {
        Node *tmp = new Node(it->first, it->second);
        heap.push(tmp);
    }
    while (heap.size() != 1)
    { // Define Huffman Codes
        // Take two mins from priority_queue
        left = heap.top();
        heap.pop();
        right = heap.top();
        heap.pop();

        top = new Node('+', left->freq + right->freq);
        top->left = left;
        top->right = right;
        heap.push(top);
    }
    return heap.top();
}

void Encoding(map<char, string> codes, string main_file, string enc_file)
{
    ifstream stream(main_file, ios::binary);
    ofstream w_file(enc_file, ios::binary);
    char current_sym = 0x00;
    string enc_sym;
    string final_enc;
    short j = 0;
    char file_sym = 0;
    while (stream)
    {
        current_sym = stream.get();
        for (int i = 0; i < codes[current_sym].length(); i++)
        {
            enc_sym += codes[current_sym][i];
            j++;
            if (j == 8)
            {
                bitset<8> b1(enc_sym);
                file_sym = b1.to_ulong();
                w_file << file_sym;
                j = 0;
                file_sym = 0;
                enc_sym.clear();
            }
        }
    }
    if (!enc_sym.empty())
    {
        int i = 0;
        for (int j = 0; j < enc_sym.length(); j++)
        {
            final_enc += enc_sym[j];
            i++;
        }
        for (i = 0; i < 8 - enc_sym.length(); i++)
        {
            final_enc += '0';
        }
        bitset<8> b1(final_enc);
        file_sym = b1.to_ulong();
        w_file << file_sym;
        file_sym = 0;
    }
    stream.close();
    w_file.close();

    ofstream enc_table("codes.txt", ios::binary);
    map<char, string>::iterator it;
    for (it = codes.begin(); it != codes.end(); it++)
    {
        enc_table << (short)(unsigned char)it->first << " " << it->second << '\n';
    }
    enc_table.close();
}

void Decoding(string enc_file, string dec_file, string codes_file)
{
    ifstream code_file(codes_file);
    map<char, string> codes;
    string line, code;
    string cur_sym_bin;
    short sym;
    string tmp;
    char cur_sym;

    while (code_file >> sym >> code)
    {
        if (!code.empty())
        {
            codes[(char)sym] = code;
        }
    }
    code_file.close();

    ifstream r_file(enc_file, ios::binary);
    ofstream w_file(dec_file, ios::binary);
    int i = 0;
    map<char, string>::iterator it;

    streampos end_pos = r_file.seekg(0, r_file.end).tellg();
    r_file.seekg(0, r_file.beg);
    while (r_file.peek() != EOF)
    {
        cur_sym = r_file.get();
        cur_sym_bin += std::bitset<8>(cur_sym).to_string();
        for (i = 0; i < cur_sym_bin.size(); i++)
        {
            if (tmp.empty())
            {
                tmp = cur_sym_bin[i];
            }
            else
            {
                tmp += cur_sym_bin[i];
            }
            for (it = codes.begin(); it != codes.end(); it++)
            {
                if (it->second == tmp)
                {
                    if (it->first == EOF && r_file.tellg() == end_pos)
                    {
                        r_file.close();
                        w_file.close();
                        return;
                    }
                    else
                    {
                        w_file << it->first;
                        cur_sym_bin.erase(0, tmp.length());
                        i = -1;
                        tmp.clear();
                        break;
                    }
                }
            }
        }
        if (tmp.length() != 0)
        {
            tmp.clear();
        }
    }
    r_file.close();
    w_file.close();
}

bool cmp(pair<char, int> &a, pair<char, int> &b)
{
    return a.second < b.second;
}

void Sort(map<char, int> &M)
{
    vector<pair<char, int>> A;
    for (auto &it : M)
    {
        A.push_back(it);
    }
    sort(A.begin(), A.end(), cmp);
}

void CalcFreq(map<char, int> *data, string file_name)
{
    char sym = 0x00;
    ifstream stream(file_name, ios::binary);
    while (stream)
    {
        sym = stream.get();
        (*data)[sym]++;
    }
    stream.close();
}

int main(int argc, char **argv)
{
    map<char, int> symbols;
    map<char, string> codes;
    short command = 0;
    cout << "Select option:\n1 - Encoding\n2 - Decoding\n";
    cin >> command;
    string first_file, second_file;
    if (command == 1)
    {
        cout << "Print input file: ";
        cin >> first_file;
        cout << "Print output file: ";
        cin >> second_file;
        CalcFreq(&symbols, first_file);
        Sort(symbols);
        struct Node *result = HuffmanTree(symbols, symbols.size());
        PrintCodes(result, "", &codes);
        auto t1 = std::chrono::high_resolution_clock::now();
        Encoding(codes, first_file, second_file);
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
        Decoding(first_file, second_file, "codes.txt");
        auto t2 = std::chrono::high_resolution_clock::now();
        cout << "Execution time: " << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count() << "ms\n";
    }
    return 0;
}
