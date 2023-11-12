#include <assert.h>
#include <sstream>
#include "qna_tool.h"

using namespace std;

#define HashTableSize 300023
#define baseformultiplication 97

vector<int> pow1 = {1 , 97 , 9409 , 12604 , 22496 , 81951 , 148649 , 17849 , 231238 , 228384 , 251569 , 100330 , 131274 , 132612 , 262398 , 250674 , 13515 , 110863 , 252906 , 230019 , 110141 , 182872 , 37227 , 10743 , 142002 , 273159 , 94399 , 156013 , 132111 , 213801 , 37110 , 299417 , 241241 , 298606 , 162574 , 168482 , 141512 , 225629 , 284357 , 280536 , 209922 , 260893 , 104689 , 254074 , 43292 , 299025 , 203217 , 210554 , 22174 , 50717 , 119181 , 159683 , 188078 , 242186 , 90248 , 53389 , 78342 , 98599 , 263390 , 46875 , 46530 , 13065 , 67213 , 219178 , 258656 , 187723 , 207751 , 50306 , 79314 , 192883 , 108225 , 297043 , 10963 , 163342 , 242978 , 167072 , 4742 , 159951 , 214074 , 63591 , 167867 , 81857 , 139531 , 33472 , 246554 , 213921 , 48750 , 228405 , 253606 , 297919 , 95935 , 4982 , 183231 , 72050 , 88321 , 166493 , 248602 , 112554 , 116910 , 239419};

unsigned long long hash_value(string input) {
    
    int hash =0;
    for (int i = 0; i < input.size(); i++)
    {
        hash += (1LL*pow1[i]*input[i])%HashTableSize;
        
    }
    hash = (hash + HashTableSize)%HashTableSize;

    return hash;
    
}

QNA_tool::book::book()
{
    hashtable = vector<vector<boobs>>(HashTableSize);
}


QNA_tool::boobs::boobs()
{
    word = "";
}

QNA_tool::boobs::boobs(string w)
{
    word = w;
    instances = vector<page>();
}

QNA_tool::QNA_tool(){
    // Implement your function here  
    bookshelf = vector<book>();
}

QNA_tool::~QNA_tool(){
    // Implement your function here  
}


vector<string> ppr(std::string pat) {

    vector<string> ret;
    string word = "";
    for (int i = 0; i < pat.size(); i++) {
        char s = pat[i];

        if( s == '!' || s == '\"' || s == '[' || s == '.' || s == ',' || s == '?' ||
            s == ']' || s == '(' || s == ')' || s == '@' || s == ';' || s == ':' || 
            s == '\'' || s == '-' || s == ' ')
            {
                if(word.size() != 0)
                {
                    ret.push_back(word);
                    word = "";

                }

            }
        
        else {
            if(s - 'A' >=0 and s - 'Z' <= 0) {
                word += (char)(s + 32);

            }

            else{word += s;}
        }
    }

    if(word.size() !=0) {
        ret.push_back(word);
        word = "";
    }

    return ret;
    
}


void QNA_tool::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence)
{
    vector<string> words = ppr(sentence);
    int index_of_book = -1;
    for (int i = 0; i < bookshelf.size(); i++)
    {
        if (bookshelf[i].book_no == book_code)
        {
            index_of_book = i;
            break;
        }
    }

    if (index_of_book == -1)
    {
        bookshelf.push_back(book());
        index_of_book = bookshelf.size()-1;
        bookshelf[index_of_book].book_no = book_code;
    }
    //book aux_book = bookshelf[index_of_book];


    for (int i = 0; i < words.size(); i++)
    {
        unsigned long long hashvalue = hash_value(words[i]);
        
        if (bookshelf[index_of_book].hashtable[hashvalue].size() == 0)
        {
            boobs a(words[i]);
            a.total_count += 1;
            if (a.instances.size() <= page)
            {
                a.instances.resize(page +1);
            }

            if (a.instances[page].paras.size() <= paragraph)
            {
                a.instances[page].paras.resize(paragraph +1);
            }
            
            
            a.instances[page].page_no = page;
            a.instances[page].paras[paragraph].paragraph_no = paragraph;
            a.instances[page].paras[paragraph].count_in_para += 1;
            bookshelf[index_of_book].hashtable[hashvalue].push_back(a);
            
        }

        else
        {
            int k2 = 0;
            for (size_t j = 0; j < bookshelf[index_of_book].hashtable[hashvalue].size(); j++)
            {
                if (bookshelf[index_of_book].hashtable[hashvalue][j].word == words[i])
                {
                    if (bookshelf[index_of_book].hashtable[hashvalue][j].instances.size() <= page)
                    {
                        bookshelf[index_of_book].hashtable[hashvalue][j].instances.resize(page+1);
                    }

                    if (bookshelf[index_of_book].hashtable[hashvalue][j].instances[page].paras.size() <= paragraph)
                    {
                       bookshelf[index_of_book].hashtable[hashvalue][j].instances[page].paras.resize(paragraph+1);                    
                    }
                    
                    
                    bookshelf[index_of_book].hashtable[hashvalue][j].instances[page].paras[paragraph].count_in_para += 1;
                    bookshelf[index_of_book].hashtable[hashvalue][j].total_count += 1;
                    break;
                }
                k2++;

                
            }

            if (k2 == bookshelf[index_of_book].hashtable[hashvalue].size())
            {
                boobs a(words[i]);
                a.total_count += 1;
                if (a.instances.size() <= page)
                {
                    a.instances.resize(2*page +1);
                }

                if (a.instances[page].paras.size() <= paragraph)
                {
                    a.instances[page].paras.resize(2*paragraph +1);
                }
            
                a.instances[page].page_no = page;
                a.instances[page].paras[paragraph].paragraph_no = paragraph;
                a.instances[page].paras[paragraph].count_in_para += 1;
                bookshelf[index_of_book].hashtable[hashvalue].push_back(a);
            }   
        }
    }   
    // Implement your function here  
    return;
}

Node* QNA_tool::get_top_k_para(string question, int k) {
    // Implement your function here
    return nullptr;
}

void QNA_tool::query(string question, string filename){
    // Implement your function here  
    std::cout << "Q: " << question << std::endl;
    std::cout << "A: " << "Studying COL106 :)" << std::endl;
    return;
}

std::string QNA_tool::get_paragraph(int book_code, int page, int paragraph){

    cout << "Book_code: " << book_code << " Page: " << page << " Paragraph: " << paragraph << endl;
    
    std::string filename = "mahatma-gandhi-collected-works-volume-";
    filename += to_string(book_code);
    filename += ".txt";

    std::ifstream inputFile(filename);

    std::string tuple;
    std::string sentence;

    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open the input file " << filename << "." << std::endl;
        exit(1);
    }

    std::string res = "";

    while (std::getline(inputFile, tuple, ')') && std::getline(inputFile, sentence)) {
        // Get a line in the sentence
        tuple += ')';

        int metadata[5];
        std::istringstream iss(tuple);

        // Temporary variables for parsing
        std::string token;

        // Ignore the first character (the opening parenthesis)
        iss.ignore(1);

        // Parse and convert the elements to integers
        int idx = 0;
        while (std::getline(iss, token, ',')) {
            // Trim leading and trailing white spaces
            size_t start = token.find_first_not_of(" ");
            size_t end = token.find_last_not_of(" ");
            if (start != std::string::npos && end != std::string::npos) {
                token = token.substr(start, end - start + 1);
            }
            
            // Check if the element is a number or a string
            if (token[0] == '\'') {
                // Remove the single quotes and convert to integer
                int num = std::stoi(token.substr(1, token.length() - 2));
                metadata[idx] = num;
            } else {
                // Convert the element to integer
                int num = std::stoi(token);
                metadata[idx] = num;
            }
            idx++;
        }

        if(
            (metadata[0] == book_code) &&
            (metadata[1] == page) &&
            (metadata[2] == paragraph)
        ){
            res += sentence;
        }
    }

    inputFile.close();
    return res;
}

void QNA_tool::query_llm(string filename, Node* root, int k, string API_KEY, string question){

    // first write the k paragraphs into different files

    Node* traverse = root;
    int num_paragraph = 0;

    while(num_paragraph < k){
        assert(traverse != nullptr);
        string p_file = "paragraph_";
        p_file += to_string(num_paragraph);
        p_file += ".txt";
        // delete the file if it exists
        remove(p_file.c_str());
        ofstream outfile(p_file);
        string paragraph = get_paragraph(traverse->book_code, traverse->page, traverse->paragraph);
        assert(paragraph != "$I$N$V$A$L$I$D$");
        outfile << paragraph;
        outfile.close();
        traverse = traverse->right;
        num_paragraph++;
    }

    // write the query to query.txt
    ofstream outfile("query.txt");
    outfile << "These are the excerpts from Mahatma Gandhi's books.\nOn the basis of this, ";
    outfile << question;
    // You can add anything here - show all your creativity and skills of using ChatGPT
    outfile.close();
 
    // you do not need to necessarily provide k paragraphs - can configure yourself

    // python3 <filename> API_KEY num_paragraphs query.txt
    string command = "python3 ";
    command += filename;
    command += " ";
    command += API_KEY;
    command += " ";
    command += to_string(k);
    command += " ";
    command += "query.txt";

    system(command.c_str());
    return;
}

/*
int main()
{
    QNA_tool a;
    //cout << hash_value("the");

    a.insert_sentence(1, 1, 1, 1, "the ");
    a.insert_sentence(1, 1, 1, 2, "the?");
    a.insert_sentence(1, 1, 1, 3, "the,");
    a.insert_sentence(1, 1, 1, 4, "the.");
    a.insert_sentence(1, 1, 1, 5, "the!");
    a.insert_sentence(1, 1, 2, 1, "fuck(");
    a.insert_sentence(1, 1, 2, 2, "fuck)");
    a.insert_sentence(1, 1, 2, 3, "fuck");
    a.insert_sentence(1, 1, 2, 4, "fuck");
    a.insert_sentence(1, 1, 2, 5, "fuck@");
    a.insert_sentence(1, 1, 3, 1, "is");
    a.insert_sentence(1, 1, 3, 2, "is");
    a.insert_sentence(1, 1, 3, 3, "is");
    a.insert_sentence(1, 1, 3, 4, "is");
    a.insert_sentence(1, 1, 3, 5, "is");
    a.insert_sentence(1, 2, 1, 1, "your");
    a.insert_sentence(1, 2, 1, 2, "your");
    a.insert_sentence(1, 2, 1, 3, "your");
    a.insert_sentence(1, 2, 1, 4, "your");
    a.insert_sentence(1, 2, 1, 5, "your");
    a.insert_sentence(1, 3, 1, 1, "name");
    a.insert_sentence(1, 3, 1, 2, "name");
    a.insert_sentence(1, 3, 1, 3, "name");
    a.insert_sentence(1, 3, 1, 4, "name");
    a.insert_sentence(1, 3, 1, 5, "name");
    cout << "done";
}
*/