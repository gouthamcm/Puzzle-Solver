#include <iostream>
#define MAX_SIZE 26
using namespace std;

class TrieData
{
private:
    TrieData *children_nodes[MAX_SIZE];
    bool end_of_word;
    
public:
    TrieData *root = NULL;
    TrieData *make_node()
    {
        TrieData *new_node = (TrieData *)malloc(sizeof(TrieData));

        for (int i = 0; i < MAX_SIZE; i++)
        {
            new_node->children_nodes[i] = NULL;
        }
        new_node->end_of_word = false;

        return new_node;
    }

    void insert_query(TrieData *root, string query)
    {
        TrieData *temp;
        //temporary variable to store the root node
        int index;

        if (query.length() == 0)
        {
            cout << "No string to be inserted";
            return;
        }
        temp = root;
        for (int i = 0; i < query.length(); i++)
        {
            index = query[i] - 'a';
            if (!temp->children_nodes[index])
            {
                temp->children_nodes[index] = make_node();
            }
            temp = temp->children_nodes[index];
        }
        temp->end_of_word = true;
    }
    bool search_query(TrieData *root, string query)
    {
        if (query.length() == 0)
        {
            return false;
        }
        if (!root)
        {
            cout << "hi\n";
            return false;
        }
        TrieData *temp = root;
        int index;
        for (int i = 0; i < query.length(); i++)
        {
            index = query[i] - 'a';
            if (!temp->children_nodes[index])
            {
                return false;
            }
            else
            {
                temp = temp->children_nodes[index];
            }
        }
        return temp->end_of_word;
    }
    void solver(char **board, int row, int col, TrieData *root){
        int visited[row][col] = {0};
        for(int i=0; i<row; i++){
            for(int j=0; j<col; j++){
                string word="";
                dfs(board, row, col, i, j, root, word);
            }
        }
    }
    void dfs(char **board, int ROW_SIZE, int COL_SIZE, int x_pos, int y_pos, TrieData* node, string word){
        if(x_pos< ROW_SIZE || y_pos < COL_SIZE) return;
        else if(x_pos ==ROW_SIZE || y_pos == COL_SIZE) return;
        else if(board[x_pos][y_pos] == ' ') return;
        else{
            int index = board[x_pos][y_pos]-'a';
            word.push_back((char)(node->children_nodes[index] + 97));
            if(node->end_of_word){
                cout<<word<<endl;
            }
            char temp = board[x_pos][y_pos] = ' ';
            node = node->children_nodes[index];
            dfs(board, ROW_SIZE, COL_SIZE, x_pos+1, y_pos, node, word);
            dfs(board, ROW_SIZE, COL_SIZE, x_pos, y_pos+1, node, word);
            dfs(board, ROW_SIZE, COL_SIZE, x_pos+1, y_pos+1, node, word);
            dfs(board, ROW_SIZE, COL_SIZE, x_pos, y_pos+1, node, word);
            board[x_pos][y_pos] = temp;
        }
    }
    void insert(string query)
    {
        if(!root){
            root=make_node();
        }
        insert_query(root, query);
    }
    bool search(string query)
    {
        return search_query(root, query);
    }
    
};

int main()
{
    
    return 0;
}