// Do NOT add any other includes
#include "dict.h"


Object1::Object1(int cou , string s){
    count = cou;
    word_obj = s;
}


Object1::Object1(){
    count = 1;
    word_obj = "";
}


Dict::Dict(){
    hashtable.resize(100000);
}


Dict::~Dict(){

}


char charToLower(char c){
    if(c >= 65 && c <= 90){
        return c + 32;
    }
    return c;
}


int pow_selfk(int a,int b){
    if (b==0) return 1;
    return a *pow_selfk(a,b-1);
}





int get_hashVaue(string string_word){
    int h = 0;
    int i = 0;
    while(i<5){
        int sum = 0;
        for(int j = i;j<string_word.size(); j= j+5){
            sum += string_word[j];
        }
        h = h + (sum%10) * pow_selfk(10,i);
        i++;
    }
    return h;
}


// bool checkExistenence(vector <Object1> p , string s){
//     for(auto i : p){
//         if(i.word_obj == s){
//             return true;
//         }
//     }
//     return false;
// }


void Dict::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence){ 
    string wordInitial = "";
    for(char c : sentence){
        // string separators = ". , - : ! " ' ( ) ? [ ] ; @";
        if(c == ' '){
            if(wordInitial != ""){
                int hash = get_hashVaue(wordInitial);
                bool flag = false;
                for(int i = 0; i<hashtable[hash].size();i++){
                    if(hashtable[hash][i].word_obj == wordInitial){
                        hashtable[hash][i].count ++;
                        flag = true;
                        break;
                    }
                }
                if(!flag){
                    Object1 o = Object1();
                    o.word_obj = wordInitial;
                    hashtable[hash].push_back(o);
                }
                wordInitial = "";
            }
        }
        else if((c == '.') || (c == ',') || (c == '-') || (c == ':') || (c == '!') ||(c == '"') || (c == 39) || (c == '(') || (c == ')') || (c == '?') || (c == '[') || (c == ']') || (c == ';') || (c == '@')){
            if(wordInitial != ""){
                int hash = get_hashVaue(wordInitial);
                bool flag = false;
                for(int i = 0; i<hashtable[hash].size();i++){
                    if(hashtable[hash][i].word_obj == wordInitial){
                        hashtable[hash][i].count ++;
                        flag = true;
                        break;
                    }
                }
                if(!flag){
                    Object1 o = Object1();
                    o.word_obj = wordInitial;
                    hashtable[hash].push_back(o);
                }
                wordInitial = "";
            }
        }
        else{
            char temp = charToLower(c);
            wordInitial += temp;
        }
    }
    
    if(wordInitial != ""){
        int hash = get_hashVaue(wordInitial);
        bool flag = false;
        for(int i = 0; i<hashtable[hash].size();i++){
            if(hashtable[hash][i].word_obj == wordInitial){
                hashtable[hash][i].count ++;
                flag = true;
                break;
            }
        }
        if(!flag){
            Object1 o = Object1();
            o.word_obj = wordInitial;
            hashtable[hash].push_back(o);
        }
        wordInitial = "";
    }
}

int Dict::get_word_count(string word){
    string word_lower = "";
    for(char c : word){
        char temp = charToLower(c);
        word_lower += temp;
    }
    // cout<<word_lower<<endl;
    int hash = get_hashVaue(word_lower);
    // cout<<hash<<endl;
    // for(auto i : hashtable[hash]){
    //     if(i.word_obj == word_lower){
    //         return i.count;
    //     }
    // }
    for(int i = 0; i<hashtable[hash].size();i++){
        if(hashtable[hash][i].word_obj== word_lower){
            return hashtable[hash][i].count;
        }
    }
    return 0;
}


void Dict::dump_dictionary(string filename){
    ofstream dump_file;
    dump_file.open(filename);
    for(int i = 0; i<hashtable.size(); i++){
        for(int j = 0; j<hashtable[i].size(); j++){
            dump_file<<hashtable[i][j].word_obj<<", "<<hashtable[i][j].count<<endl;
        }
    }
    dump_file.close();
    return;
}

// int main(){
//     // string separators = ". , - : ! " ' ( ) ? [ ] ; @";
//     Dict a;
//     a.insert_sentence(2,3,4,5,"");

//     a.insert_sentence(2,3,4,5,"1  , mU, c ,  ` , | U: U    `   ||.");
//     a.insert_sentence(2,3,4,5,"VOL.54: 13 OCTOBER, 1931 8 FEBRUARY, 1932 397 ||.");
//     a.insert_sentence(2,3,4,5,"womens prayer. || (B)");


    
//     // a.insert_sentence(2,3,2,1,"coding is BEst BEst BEst BEst kffjrg 9348948 /BEst BEst BEst BEst..");
//     int m = a.get_word_count("||");
//     cout<<m<<endl;
//     // cout<<a.root->right->left->word<<endl;
//     cout<<"======"<<endl;
//     // inorder_traver(a.root);
//     a.dump_dictionary("hii.txt");
//     // cout<<m;
//     return 0;
// }